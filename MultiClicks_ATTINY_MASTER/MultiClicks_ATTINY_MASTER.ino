// NodeMCU

#include <Wire.h>

#define SLAVE_ADDR 0x27

void setup() {
  Serial.begin(115200);                    // petit debug via le port série
  Serial.println("I2C Test Application");  // hop on affiche le start (pratique sur les reset)
  Wire.begin();                            // I2C bus is on pin D1

}

void loop() {
  Wire.beginTransmission(SLAVE_ADDR); // transmit to device 0x27
  Wire.write('A');                    // Request 
  Wire.endTransmission();             // stop transmitting

  while (Wire.available()) {          // slave may send less than requested
    char c = Wire.read();             // receive a byte as character
    Serial.print(c);                  // print the character
  }
  delayMicroseconds(1000);            // on glande une seconde
}
