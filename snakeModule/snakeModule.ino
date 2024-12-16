#include <micro_ros_arduino.h>

#include <stdio.h>
#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>

#include <geometry_msgs/msg/twist.h>

rcl_subscription_t module_subscriber;
geometry_msgs__msg__Twist module_msg;

rclc_executor_t executor;
rcl_allocator_t allocator;
rclc_support_t support;
rcl_node_t node;

#define RCCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){error_loop();}}
#define RCSOFTCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){error_loop();}}

void error_loop(){
  while(1){
    delay(100);
  }
}

#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

//char * ssid     = "INFINITUMA888";
//char * password = "hNxNF6kX7P";
//char * pc_ip = "192.168.1.68";

char * ssid     = "finder-network";
char * password = "finder-network-psswd";
char * pc_ip = "192.168.100.103";

//char * ssid     = "Redmi Note 10S";
//char * password = "Sasamuri8";
//char * pc_ip = "192.168.176.200";

//char * ssid     = ".:PC Puma FI:.";
//char * password = "";
//char * pc_ip = "10.103.6.117";

//char * ssid     = "Alexis";
//char * password = "08052002";
//char * pc_ip = "172.20.10.6";

//char * ssid     = "Escuela_Guest_A";
//char * password = "kyakuAMJ";
//char * pc_ip = "192.168.0.108";

//cambiar dependiendo del modulo
const char * topic_name = "module_3";
uint port = 8003;
const char * node_name = "snake_module_3_node";

//#define LED_PIN 23
// SPEED PINS
const uint8_t SPEED_PWM_PIN = 26;
const uint8_t SPEED_DIR_1 = 27;
const uint8_t SPEED_DIR_2 = 14;
const uint8_t SPEED_PWM_CHANNEL = 1;

// YAW PINS
const uint8_t YAW_PWM_PIN = 19;
const uint8_t YAW_DIR_1 = 23;
const uint8_t YAW_DIR_2 = 18;
const uint8_t YAW_PWM_CHANNEL = 2;

// PITCH PINS
const uint8_t PITCH_PWM_PIN = 2;
const uint8_t PITCH_DIR = 4;
const uint8_t PITCH_PWM_CHANNEL = 3;

// ENCODER SPEED PINS
const uint8_t SPEED_ENCODER_A = 12;
const uint8_t SPEED_ENCODER_B = 13;

// ENCODER PITCH PINS
const uint8_t PITCH_ENCODER_A = 16;
const uint8_t PITCH_ENCODER_B = 17;

// ENCODER YAW PINS
const uint8_t YAW_ENCODER_A = 34;
const uint8_t YAW_ENCODER_B = 35;

// Encoder pulse counter variables
volatile double yaw_counter = 0;
volatile double pitch_counter = 0;

// Sample time
const uint8_t SAMPLE_TIME = 10;

// Desired pitch and yaw angles
double desired_pitch_angle = 0;
double desired_yaw_angle = 0;

double speed_value;
double yaw_value;
double pitch_value;

int motorCorrection = 0;
float turnCorrection = 0.5;

void module_callback(const void * msgin) {
  const geometry_msgs__msg__Twist * msg = (const geometry_msgs__msg__Twist *)msgin;
    
  speed_value = msg->linear.x;
  yaw_value = msg->angular.z;
  pitch_value = msg->angular.y;

  desired_yaw_angle = yaw_value;
  desired_pitch_angle = pitch_value;
  write_pwm_speed(speed_value);

  Serial.print("Speed: ");
  Serial.println(speed_value);
  Serial.print("Yaw: ");
  Serial.println(yaw_value);
  Serial.print("Pitch: ");
  Serial.println(pitch_value);
  Serial.println("");
}

void setup() {  
  //set_microros_transports();
  set_microros_wifi_transports(ssid, password, pc_ip, port);

  //pinMode(LED_PIN, OUTPUT);
  //digitalWrite(LED_PIN, HIGH);
   
  Serial.begin(9600);
  Serial.println("");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP()); 
  //for(int i=0; i<numOut; i++)
  //  pinMode(out[i],OUTPUT);

  // SPEED
  ledcSetup(SPEED_PWM_CHANNEL, 12000, 8); // 12 kHz PWM, 8-bit resolution
  ledcAttachPin(SPEED_PWM_PIN, SPEED_PWM_CHANNEL);
  pinMode(SPEED_DIR_1, OUTPUT);
  pinMode(SPEED_DIR_2, OUTPUT);
  pinMode(SPEED_ENCODER_A, INPUT);
  pinMode(SPEED_ENCODER_B, INPUT);

  // YAW
  ledcSetup(YAW_PWM_CHANNEL, 12000, 8); // 12 kHz PWM, 8-bit resolution
  ledcAttachPin(YAW_PWM_PIN, YAW_PWM_CHANNEL);
  pinMode(YAW_DIR_1, OUTPUT);
  pinMode(YAW_DIR_2, OUTPUT);
  pinMode(YAW_ENCODER_A, INPUT);
  pinMode(YAW_ENCODER_B, INPUT);

  // PITCH
  ledcSetup(PITCH_PWM_CHANNEL, 12000, 8); // 12 kHz PWM, 8-bit resolution
  ledcAttachPin(PITCH_PWM_PIN, PITCH_PWM_CHANNEL);
  pinMode(PITCH_DIR, OUTPUT);
  pinMode(PITCH_ENCODER_A, INPUT);
  pinMode(PITCH_ENCODER_B, INPUT);

  // Interrupt routines
  attachInterrupt(
    digitalPinToInterrupt(SPEED_ENCODER_A), speedEncoderEvent, RISING);
  attachInterrupt(
    digitalPinToInterrupt(PITCH_ENCODER_A), pitchEncoderEvent, RISING);
  attachInterrupt(
    digitalPinToInterrupt(YAW_ENCODER_A), yawEncoderEvent, RISING);

  // Set up tasks to run independently.
  xTaskCreatePinnedToCore(
    pitchPID,
    "compute pitch PID", // A name just for humans
    8000, // This stack size can be checked & adjusted by reading the Stack Highwater
    NULL,
    1, // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    NULL,
    ARDUINO_RUNNING_CORE);

  xTaskCreatePinnedToCore(
    yawPID,
    "compute yaw PID", // A name just for humans
    8000, // This stack size can be checked & adjusted by reading the Stack Highwater
    NULL,
    1, // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    NULL,
    ARDUINO_RUNNING_CORE);

  delay(2000);

  allocator = rcl_get_default_allocator();

   //create init_options
  RCCHECK(rclc_support_init(&support, 0, NULL, &allocator));

  // create node
  RCCHECK(rclc_node_init_default(&node, node_name, "", &support));

  // create subscriber
  RCCHECK(rclc_subscription_init_default(
    &module_subscriber,
    &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(geometry_msgs, msg, Twist),
    topic_name));

  // create executor
  RCCHECK(rclc_executor_init(&executor, &support.context, 1, &allocator));
  RCCHECK(rclc_executor_add_subscription(&executor, &module_subscriber, &module_msg, &module_callback, ON_NEW_DATA));
}

void loop() {
  delay(100);
  RCCHECK(rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100)));
}

void write_pwm_speed(double pwm) {
  bool dir = pwm > 1 ? LOW : HIGH;
  //Serial.println(dir);
  digitalWrite(SPEED_DIR_1, dir);
  digitalWrite(SPEED_DIR_2, !dir);
  ledcWrite(SPEED_PWM_CHANNEL, abs(pwm));
  //Serial.println(abs(pwm));
}

void write_pwm_yaw(float pwm) {
  bool dir = pwm > 1 ? LOW : HIGH;
  //Serial.println(dir);
  digitalWrite(YAW_DIR_1, dir);
  digitalWrite(YAW_DIR_2, !dir);
  ledcWrite(YAW_PWM_CHANNEL, abs(pwm));
  //Serial.println(abs(pwm));
}

void write_pwm_pitch(float pwm) {
  bool dir = pwm > 1 ? LOW : HIGH;
  //Serial.println(dir);
  digitalWrite(PITCH_DIR, dir);
  ledcWrite(PITCH_PWM_CHANNEL, abs(pwm));
  //Serial.println(abs(pwm));
}

void stop_motors() {
  ledcWrite(SPEED_PWM_CHANNEL, 0);
  ledcWrite(PITCH_PWM_CHANNEL, 0);
  ledcWrite(YAW_PWM_CHANNEL, 0);
}

void speedEncoderEvent(){
  // do nothing by now
}

void yawEncoderEvent(){
  if(digitalRead(YAW_ENCODER_B))
    yaw_counter--;
  else
    yaw_counter++;
}

void pitchEncoderEvent(){
  if(digitalRead(PITCH_ENCODER_B))
    pitch_counter--;
  else
    pitch_counter++;
}

void yawPID(void *pvParameters){
  (void) pvParameters;
  /*/
  const uint8_t K_P = 12;
  const uint8_t K_I = 2;
  float acc_error = 0;
  //*/
  ///////otra opcion/////////////
  float integral_error = 0, deriv_error, current_angle, error, error_prev = 0, u;
  float kp = 12, ki = 0, kd = 0;
  int dt;
  unsigned long t, t_prev = 0;
  /////////////////////////////*/
  
  while(true){
    /*/
    float current_angle = yaw_counter * 100 * 12 / (360 * 3);
    float error = desired_yaw_angle - current_angle;
    float integral_error = 0.001 * SAMPLE_TIME * (error - acc_error) / 2;
    float u = K_P * error + K_I * integral_error;
    acc_error = integral_error;
    //*/
    ///////////////////////////////////////////
    t = millis();
    dt = t - t_prev;
    current_angle = yaw_counter * 100 * 12 / (360 * 3);
    error = desired_yaw_angle - current_angle;
    integral_error += (dt * ((error + error_prev) / 2));
    deriv_error = (error - error_prev) / dt;
    u = kp * error + ki * integral_error + kd * deriv_error;

    t_prev = t;
    error_prev = error;
    /////////////////////////////////////////*/
    
    write_pwm_yaw(u);
    //Serial.print("Computed yaw");
    vTaskDelay(SAMPLE_TIME);
  }
}

void pitchPID(void *pvParameters){
  (void) pvParameters;
  /*/
  const uint8_t K_P = 12;
  const uint8_t K_I = 2;
  float acc_error = 0;
  //*/
  ///////otra opcion/////////////
  float integral_error = 0, deriv_error, current_angle, error, error_prev = 0, u;
  float kp = 12, ki = 0, kd = 0;
  int dt;
  unsigned long t, t_prev = 0;
  /////////////////////////////*/
  
  while(true){
    /*/
    float current_angle = pitch_counter * 100 * 12 / (360 * 3);
    float error = desired_pitch_angle - current_angle;
    float integral_error = 0.001 * SAMPLE_TIME * (error - acc_error) / 2;
    float u = K_P * error + K_I * integral_error;
    acc_error = integral_error;
    //*/
    ///////////////////////////////////////////
    t = millis();
    dt = t - t_prev;
    current_angle = pitch_counter * 100 * 12 / (360 * 3);
    error = desired_pitch_angle - current_angle;
    integral_error += (dt * ((error + error_prev) / 2));
    deriv_error = (error - error_prev) / dt;
    u = kp * error + ki * integral_error + kd * deriv_error;

    t_prev = t;
    error_prev = error;
    /////////////////////////////////////////*/
    
    write_pwm_pitch(u);
    //Serial.print("Computed pitch");
    vTaskDelay(SAMPLE_TIME);
  }
}
