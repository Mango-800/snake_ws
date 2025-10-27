#include <Wire.h>

#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

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

const int moduleAddress = 2;  // Cambiar dependiendo del esclavo
double speed_value, yaw_value, pitch_value;

void setup() {
  Wire.begin(moduleAddress);  // Inicia el esclavo en la dirección especificada
  Wire.onReceive(receiveEvent);  // Registra el evento de recepción
  Serial.begin(9600);

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
}

void loop() {
  delay(100); 
}
