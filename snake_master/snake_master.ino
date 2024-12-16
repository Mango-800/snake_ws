#include <micro_ros_arduino.h>
#include <stdio.h>
#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <rmw_microros/rmw_microros.h>

#include <geometry_msgs/msg/twist.h>
#include <std_msgs/msg/int32.h>

#include <Wire.h>

#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

#define RCCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){return false;}}
#define EXECUTE_EVERY_N_MS(MS, X)  do { \
  static volatile int64_t init = -1; \
  if (init == -1) { init = uxr_millis();} \
  if (uxr_millis() - init > MS) { X; init = uxr_millis();} \
} while (0)\

rclc_executor_t executor;
rcl_allocator_t allocator;
rclc_support_t support;
rcl_node_t node;
rcl_timer_t timer;

rcl_subscription_t module_subscriber;
geometry_msgs__msg__Twist module_msg;

rcl_publisher_t publisher;
std_msgs__msg__Int32 msg;
bool micro_ros_init_successful;

char * ssid     = "INFINITUMA888";
char * password = "hNxNF6kX7P";
char * pc_ip = "192.168.1.255";

//char * ssid     = "finder-network";
//char * password = "finder-network-psswd";
//char * pc_ip = "192.168.100.103";

//char * ssid     = "Redmi Note 10S";
//char * password = "Sasamuri8";
//char * pc_ip = "192.168.183.255";

uint port = 8001;

const char * topic_name = "module_master";
const char * node_name = "snake_module_master_node";

// SPEED PINS
#define SPEED_PWM_PIN 26
#define SPEED_DIR_1 27
#define SPEED_DIR_2 14
#define SPEED_ENCODER_A 12
#define SPEED_ENCODER_B 13

// YAW PINS
#define YAW_PWM_PIN 19
#define YAW_DIR_1 23
#define YAW_DIR_2 18
#define YAW_ENCODER_A 34
#define YAW_ENCODER_B 35

// PITCH PINS
#define PITCH_PWM_PIN 2
#define PITCH_DIR 4
#define PITCH_ENCODER_A 16
#define PITCH_ENCODER_B 17

// Encoder pulse counter variables
volatile double yaw_counter = 0;
volatile double pitch_counter = 0;

// Sample time
const uint8_t SAMPLE_TIME = 10;

// Desired pitch and yaw angles
double desired_pitch_angle = 0.0;
double desired_yaw_angle = 0.0;

double speed_value, yaw_value, pitch_value, module_value, slave_value;

#define LED_PIN 32
int ledPins[2] = {5, 15};

const int max_retries = 5;
int retry_count = 0;
bool is_connected = false;

enum states {
  WAITING_AGENT,
  AGENT_AVAILABLE,
  AGENT_CONNECTED,
  AGENT_DISCONNECTED
} state;

void setup() {
  set_microros_wifi_transports(ssid, password, pc_ip, port);

  Serial.begin(9600);
  Serial.println("");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP()); 

  pinMode(LED_PIN, OUTPUT);
  for(int i=0; i<2; i++)    pinMode(ledPins[i], OUTPUT);
  
  Wire.begin();  // Inicia el maestro

  // SPEED
  pinMode(SPEED_DIR_1, OUTPUT);
  pinMode(SPEED_DIR_2, OUTPUT);
  pinMode(SPEED_ENCODER_A, INPUT);
  pinMode(SPEED_ENCODER_B, INPUT);
  ledcAttach(SPEED_PWM_PIN, 12000, 8); // 12 kHz PWM, 8-bit resolution

  // YAW
  pinMode(YAW_DIR_1, OUTPUT);
  pinMode(YAW_DIR_2, OUTPUT);
  pinMode(YAW_ENCODER_A, INPUT);
  pinMode(YAW_ENCODER_B, INPUT);
  ledcAttach(YAW_PWM_PIN, 12000, 8); // 12 kHz PWM, 8-bit resolution

  // PITCH
  pinMode(PITCH_DIR, OUTPUT);
  pinMode(PITCH_ENCODER_A, INPUT);
  pinMode(PITCH_ENCODER_B, INPUT);
  ledcAttach(PITCH_PWM_PIN, 12000, 8); // 12 kHz PWM, 8-bit resolution

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

  // Set up tasks to run independently.
  xTaskCreatePinnedToCore(
    scanI2C,
    "scan I2C devices", // A name just for humans
    2000, // This stack size can be checked & adjusted by reading the Stack Highwater
    NULL,
    1, // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    NULL,
    ARDUINO_RUNNING_CORE);

  state = WAITING_AGENT;
  msg.data = 0;
}

void loop() {
  verify_agent();
}