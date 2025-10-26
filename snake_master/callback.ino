void module_callback(const void * msgin) {
  const geometry_msgs__msg__Twist * msg = (const geometry_msgs__msg__Twist *)msgin;
    
  module_value = msg->linear.y;
  speed_value = msg->linear.x;
  yaw_value = msg->angular.z;
  pitch_value = msg->angular.y;

  if (module_value != 1.0){
    sendI2C();
  }
  else {
    desired_yaw_angle = yaw_value;
    desired_pitch_angle = pitch_value;
    write_pwm_speed(speed_value);

    Serial.print("Speed: ");
    Serial.print(speed_value);
    Serial.print(" Yaw: ");
    Serial.print(yaw_value);
    Serial.print(" Pitch: ");
    Serial.println(pitch_value);
  }
}

void timer_callback(rcl_timer_t * timer, int64_t last_call_time)
{
  (void) last_call_time;
  if (timer != NULL) {
    rcl_publish(&publisher, &msg, NULL);
    msg.data++;
  }
}