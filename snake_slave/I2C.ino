void receiveEvent(int numBytes) {
  if (numBytes == 3 * sizeof(double)) {  // Verifica que se hayan recibido 3 flotantes
    Wire.readBytes((uint8_t*)&speed_value, sizeof(speed_value));
    Wire.readBytes((uint8_t*)&yaw_value, sizeof(yaw_value));
    Wire.readBytes((uint8_t*)&pitch_value, sizeof(pitch_value));

    write_pwm_speed(speed_value);
    desired_yaw_angle = yaw_value;
    desired_pitch_angle = pitch_value;
    
    // Imprime los valores recibidos
    Serial.print("Speed: ");
    Serial.print(speed_value);
    Serial.print(" Yaw: ");
    Serial.print(yaw_value);
    Serial.print(" Pitch: ");
    Serial.println(pitch_value);
  } 
  else {
    Serial.println("Error: Número de bytes inesperado.");
  }
}