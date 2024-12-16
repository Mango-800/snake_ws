#include <Wire.h>

const int slaveAddress = 2;  // Dirección del esclavo
// Variables para almacenar los valores recibidos
double speedValue, yawValue, pitchValue;

void setup() {
  Wire.begin(slaveAddress); // Inicializa el Arduino como esclavo con dirección 8
  Wire.onReceive(receiveEvent); // Registra la función de manejo para recibir datos

  Serial.begin(9600); // Inicializa la comunicación serie para debug
  Serial.println("Arduino configurado como esclavo I2C.");
}

void loop() {
  // Aquí puedes usar `received_values` como sea necesario
  delay(100); // Agrega un pequeño retraso para estabilidad
}

void receiveEvent(int bytes) {
  if (bytes == sizeof(double) * 3) { // Verifica que hay suficientes bytes para tres doubles
    uint8_t buffer[sizeof(double) * 3];

    // Lee los bytes recibidos y almacénalos en el buffer
    for (size_t i = 0; i < sizeof(double) * 3; i++) {
      buffer[i] = Wire.read();
    }

    // Convierte los bytes en tres doubles
    memcpy(&speedValue, buffer + 0 * sizeof(double), sizeof(double));
    memcpy(&yawValue, buffer + 1 * sizeof(double), sizeof(double));
    memcpy(&pitchValue, buffer + 2 * sizeof(double), sizeof(double));

    // Imprime los valores recibidos para verificación
    Serial.print("Speed: ");
    Serial.print(speedValue);
    Serial.print(" Yaw: ");
    Serial.print(yawValue);
    Serial.print(" Pitch: ");
    Serial.println(pitchValue);
  } 
  else {
    Serial.println("Error: Datos insuficientes recibidos.");
  }
}
