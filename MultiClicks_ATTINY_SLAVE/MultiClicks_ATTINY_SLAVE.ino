/* PiezoHits & ATTiny-DIGISPARK

  DIGISPARK slave
  Sample a pezo sensor and send char to Arduino NodeMCU master.

 ** UNDER MACKINTOSH YOU WILL NEED A USB HUB TO PROGRAM THE DIGISPARK BOARD! **
  Instaling Digispark support for Arduino
    - Add this link to the Arduino Préférences : http://digistump.com/package_digistump_index.json
    - Look for Digispark into the Arduino bord manager

  Digispark digital I/O PINs
    Pin 0 → I2C SDA, PWM (LED_BUILTIND on Model B)
    Pin 1 → PWM (LED_BUILTIN on Model A)
    Pin 2 → I2C SCK, Analog
    Pin 3 → Analog In (also used for USB+ when USB is in use)
    Pin 4 → PWM, Analog (also used for USB- when USB is in use)
    Pin 5 → Analog In

  Hardware Digispark Arduino



  Single click -> send char 'A'
  Double click -> send char 'B'
  Triple click -> send char 'C'
*/

#include <elapsedMillis.h>        // Library to take care of the timer overflow
#include "TinyWireS.h"            // Wire lib for ATTiny85

elapsedMillis timer;
elapsedMillis timerLed;

#define I2C_BUS_PIN         0     // Bus PIN
#define I2C_SLAVE_ADDR      0x27  // I2C slave address
#define LED_PIN             1     // Bus PIN

#define PIEZO_PIN_INPUT     5     // Piezo input PIN
#define THRESHOLD           100   // Threshold for the piezo analog readings
#define DEBOUNCE_TIME       20    // Debounce time to avoid parasitics impuls
#define TIME_OUT            800   // Timeout to output the hits sum     
#define CALL_PIN            3     // Timeout to output the hits sum     

boolean piezoState = false;
boolean lastPiezoState = false;
uint8_t hitsCount = 0;
uint8_t hits = 0;

boolean ledState = false;
int blinkDelay = 10000;

///////////////////////// SETUP
void setup() {
  TinyWireS.begin(I2C_SLAVE_ADDR);
  // Serial.begin(115200);
  digitalWrite(CALL_PIN, LOW);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  timer = 0;
  timerLed = 0;
}

///////////////////////// LOOP
void loop() {

  int sensorReading = analogRead( PIEZO_PIN_INPUT );  // Get current state

  if ( sensorReading > THRESHOLD ) {
    // Serial.println(sensorReading);
    piezoState = HIGH;
    // digitalWrite(LED_PIN, HIGH);
    // delay(100);
  }
  else {
    piezoState = LOW;
    // digitalWrite(LED_PIN, LOW);
  }

  // Catch the rizing adge and reset the timer
  if ( piezoState != lastPiezoState && lastPiezoState == LOW ) {
    // Debounce fonction
    if ( timer > DEBOUNCE_TIME ) {
      hitsCount++;
      timer = 0;
    }
  }

  // If the button released state is stable, report number of clicks and start new cycle
  if ( timer > TIME_OUT && hitsCount != 0 ) {
    hits = hitsCount;
    hitsCount = 0;
    digitalWrite(CALL_PIN, HIGH);
  }

  if (TinyWireS.available() > 0) {      // if we get an I2C message
    if (hits == 1) blinkDelay = 250; TinyWireS.send('A'); // Sends requested byte to the master
    if (hits == 2) blinkDelay = 500; TinyWireS.send('B'); // Sends requested byte to the master
    if (hits == 3) blinkDelay = 1000; TinyWireS.send('C'); // Sends requested byte to the master
    digitalWrite(CALL_PIN, LOW);
  }

  if (timerLed > blinkDelay) {
    timerLed = 0;
    ledState = ! ledState;
    digitalWrite(LED_PIN, ledState);
  }

  lastPiezoState = piezoState;
}
