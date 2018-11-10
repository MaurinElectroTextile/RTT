#include <Wire.h>

// Arduino UNO I2C_SDA - A4
// Arduino UNO I2C_SCL - A5
// ESP8266     I2C_SDA - D1 (GPIO5)
// ESP8266     I2C_SCL - D2 (GPIO4)

// #define REQUEST_PIN  2 // ARDUINO PIN 2 || 3 // ESP8266 ALL except D0 (GPIO16)
#define LED_PIN       13

#define REQUEST_PIN   D8  // ESP8266 ALL except D0 (GPIO16)
#define SDA_PIN       D1  // Go to Digispark pin P0
#define SCL_PIN       D2  // Go to Digispark pin P2

#define SLAVE_ADDR  0x27

boolean setMode = false;
byte incomingByte = 0;

void setup() {
  Serial.begin(115200);        // Debug via le port série
  Serial.println("I2C Test");  //
  
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  
  pinMode(REQUEST_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(REQUEST_PIN), requestMode, FALLING);
  Wire.begin(SDA_PIN, SCL_PIN);
}

void loop() {

  if (setMode) {
    digitalWrite(LED_PIN, HIGH);
    delay(500);
    
    Wire.requestFrom(SLAVE_ADDR, 1);     // request 4 byte from slave (float = 4 bytes)
    while (Wire.available()) {
      incomingByte = Wire.read();
      Serial.println(incomingByte);
    }
    digitalWrite(LED_PIN, LOW);
    setMode = false;
  }
}

void requestMode() {
  setMode = true;
}
