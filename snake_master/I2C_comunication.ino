void sendI2C(){
  byte byteReturn;
  
  Wire.beginTransmission(static_cast<int>(module_value));  
  Wire.write((uint8_t*)&speed_value, sizeof(speed_value));
  Wire.write((uint8_t*)&module_yaw[(int)module_value-1], sizeof(module_yaw[(int)module_value-1]));
  Wire.write((uint8_t*)&module_pitch[(int)module_value-1], sizeof(module_pitch[(int)module_value-1]));
  byteReturn = Wire.endTransmission();

  if (byteReturn == 0){
    Serial.print("Valores enviados a 0x");
    Serial.println(static_cast<int>(module_value), HEX);
  }
  else {
    Serial.print("Error al enviar a 0x");
    Serial.println(static_cast<int>(module_value), HEX);
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