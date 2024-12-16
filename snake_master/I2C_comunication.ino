void sendI2C(){
  byte byteReturn;
  
  Wire.beginTransmission(static_cast<int>(slave_value));  
  Wire.write((uint8_t*)&speed_value, sizeof(speed_value));
  Wire.write((uint8_t*)&yaw_value, sizeof(yaw_value));
  Wire.write((uint8_t*)&pitch_value, sizeof(pitch_value));
  byteReturn = Wire.endTransmission();

  if (byteReturn == 0){
    Serial.print("Valores enviados a 0x");
    Serial.println(static_cast<int>(slave_value), HEX);
  }
  else {
    Serial.print("Error al enviar a 0x");
    Serial.println(static_cast<int>(slave_value), HEX);
  }
}

void scanI2C(void *pvParameters){
  (void) pvParameters;
  while(true){
    byte error, address;

    for (address = 1; address < 3; address++) { 
      Wire.beginTransmission(address);
      error = Wire.endTransmission();

      if (error == 0) {
        //if (address < 16) Serial.print("0x");
        //Serial.print(address, HEX);
        //Serial.println(": ON");
        digitalWrite(ledPins[address - 1], HIGH);
      } 
      else {
        //if (address < 16) Serial.print("0x");
        //Serial.print(address, HEX);
        //Serial.println(": OFF");
        digitalWrite(ledPins[address - 1], LOW);
      }
    }
    
    vTaskDelay(5000 / portTICK_PERIOD_MS);
  }
}