// NodeMCU

#include <Wire.h>

#define SLAVE_ADDR  0x27
#define ANSWER_PIN  7

boolean setMode = false;

void setup() {
  Serial.begin(115200);                    // petit debug via le port série
  Serial.println("I2C Test Application");  // hop on affiche le start (pratique sur les reset)
  attachInterrupt(digitalPinToInterrupt(ANSWER_PIN), requestMode, RISING);
  Wire.begin();                            // I2C bus is on pin D1
}

void loop() {


  if (setMode) {
    Wire.beginTransmission(SLAVE_ADDR); // transmit to device 0x27
    Wire.write('A');                    // Request
    Wire.endTransmission();             // stop transmitting

    while (Wire.available()) {          // slave may send less than requested
      char c = Wire.read();             // receive a byte as character
      Serial.print(c);                  // print the character
    }
    setMode = false;
  }
}

void requestMode() {
  setMode = true;
}
