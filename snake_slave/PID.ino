void write_pwm_speed(double pwm) {
  bool dir = pwm > 1 ? LOW : HIGH;
  digitalWrite(SPEED_DIR_1, dir);
  digitalWrite(SPEED_DIR_2, !dir);
  ledcWrite(SPEED_PWM_PIN, abs(pwm));
}

void write_pwm_yaw(float pwm) {
  bool dir = pwm > 1 ? LOW : HIGH;
  digitalWrite(YAW_DIR_1, dir);
  digitalWrite(YAW_DIR_2, !dir);
  ledcWrite(YAW_PWM_PIN, abs(pwm));
}

void write_pwm_pitch(float pwm) {
  bool dir = pwm > 1 ? LOW : HIGH;
  digitalWrite(PITCH_DIR, dir);
  ledcWrite(PITCH_PWM_PIN, abs(pwm));
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
  float integral_error = 0, deriv_error, current_angle, error, error_prev = 0, u;
  float kp = 12, ki = 0, kd = 0;
  int dt;
  unsigned long t, t_prev = 0;  
  while(true){
    t = millis();
    dt = t - t_prev;
    current_angle = yaw_counter * 100 * 12 / (360 * 3);
    error = desired_yaw_angle - current_angle;
    integral_error += (dt * ((error + error_prev) / 2));
    deriv_error = (error - error_prev) / dt;
    u = kp * error + ki * integral_error + kd * deriv_error;

    t_prev = t;
    error_prev = error;
    
    write_pwm_yaw(u);
    vTaskDelay(SAMPLE_TIME);
  }
}

void pitchPID(void *pvParameters){
  (void) pvParameters;
  float integral_error = 0, deriv_error, current_angle, error, error_prev = 0, u;
  float kp = 12, ki = 0, kd = 0;
  int dt;
  unsigned long t, t_prev = 0;  
  while(true){
    t = millis();
    dt = t - t_prev;
    current_angle = pitch_counter * 100 * 12 / (360 * 3);
    error = desired_pitch_angle - current_angle;
    integral_error += (dt * ((error + error_prev) / 2));
    deriv_error = (error - error_prev) / dt;
    u = kp * error + ki * integral_error + kd * deriv_error;

    t_prev = t;
    error_prev = error;
    
    write_pwm_pitch(u);
    vTaskDelay(SAMPLE_TIME);
  }
}