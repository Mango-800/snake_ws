void module_callback(const void * msgin) {
  const geometry_msgs__msg__Twist * msg = (const geometry_msgs__msg__Twist *)msgin;
  geometry_msgs__msg__Twist serial_msg;

  speed_value = msg->linear.x;
  
  for (int modules = 0; modules < 7; modules++){
    module_value = (double)modules+1;
    if (module_value == msg->linear.y){
        module_yaw[modules] = msg->angular.z;
        module_pitch[modules] = msg->angular.y;
    }
    
    if (module_value == 1.0){
      write_pwm_speed(speed_value);
      desired_yaw_angle = module_yaw[modules];
      desired_pitch_angle = module_pitch[modules];

      Serial.print("Speed: ");
      Serial.print(speed_value);
      Serial.print(" Yaw: ");
      Serial.print(yaw_value);
      Serial.print(" Pitch: ");
      Serial.println(pitch_value);
    }
    else{
      sendI2C();
    }
    
    serial_msg.linear.y = module_value;
    serial_msg.linear.x = speed_value;
    serial_msg.linear.z = 0.0;
    serial_msg.angular.z = module_yaw[modules];
    serial_msg.angular.y = module_pitch[modules];
    serial_msg.angular.x = 0.0;
    rcl_publish(&serial_publisher, &serial_msg, NULL);
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