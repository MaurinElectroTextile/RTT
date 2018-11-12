/* PiezoHits & ATTiny-DIGISPARK

  https://www.youtube.com/watch?v=ZDDcz9buKgM

  DIGISPARK slave
  Sample a pezo sensor and send char to Arduino NodeMCU master.

 ** UNDER MACKINTOSH YOU WILL NEED A USB HUB TO PROGRAM THE DIGISPARK BOARD! **
  Instaling Digispark support for Arduino
    - Add this link to the Arduino Préférences : http://digistump.com/package_digistump_index.json
    - Look for Digispark into the Arduino bord manager

  Digispark digital I/O PINs
    Pin 0 → I2C_SDA, PWM (LED_BUILTIN on Model B)
    Pin 1 → PWM (LED_BUILTIN on Model A)
    Pin 2 → I2C_SCL, Analog
    Pin 3 → Analog In (also used for USB+ when USB is in use)
    Pin 4 → PWM, Analog (also used for USB- when USB is in use)
    Pin 5 → Analog In

  Single click -> send char 'A'
  Double click -> send char 'B'
  Triple click -> send char 'C'
*/

#include <elapsedMillis.h>        // Library to take care of the timer overflow
#include "TinyWireS.h"            // Wire lib for ATTiny85

elapsedMillis timer;

#define I2C_SLAVE_ADDR      0x27  // I2C slave address

#define PIEZO_PIN_INPUT     1     // Piezo input PIN P3
#define CALL_PIN            4     // Pin to call (wake up) the Master     

#define THRESHOLD           100   // Threshold for the piezo analog readings
#define DEBOUNCE_TIME       50    // Debounce time to avoid parasitics impuls
#define TIME_OUT            300   // Timeout to output the hits sum   

boolean piezoState = false;
boolean lastPiezoState = false;
uint8_t hitsSum = 0;
uint8_t hitsCount = 0;

byte incomingByte = 0;

void requestEvent() {
  TinyWireS.send(hitsCount);
}

///////////////////////// SETUP
void setup() {
  analogReference(DEFAULT);

  pinMode(PIEZO_PIN_INPUT, INPUT);

  // pinMode(CALL_PIN, INPUT_PULLUP); // NOT WORKING!?
  pinMode(CALL_PIN, OUTPUT);
  digitalWrite(CALL_PIN, HIGH);

  TinyWireS.begin(I2C_SLAVE_ADDR);
  TinyWireS.onRequest(requestEvent);

  timer = 0;
}

///////////////////////// LOOP
void loop() {

  boolean sensorReading = digitalRead(PIEZO_PIN_INPUT);  // Get current state

  if ( sensorReading == true ) {
    piezoState = HIGH;
  }
  else {
    piezoState = LOW;
  }
  // Catch the rizing adge and reset the timer
  if ( piezoState != lastPiezoState && lastPiezoState == LOW ) {
    // Debounce fonction
    if ( timer > DEBOUNCE_TIME ) {
      digitalWrite(CALL_PIN, HIGH);
      // digitalWrite(LED_PIN, LOW);
      hitsSum++;
      timer = 0;
    }
  }
  // If the button released state is stable, report number of clicks and start new cycle
  if ( timer > TIME_OUT && hitsSum != 0 ) {
    hitsCount = hitsSum;
    hitsSum = 0;
    digitalWrite(CALL_PIN, LOW); // Call the Master (Wake up!)
    delayMicroseconds(10);
    digitalWrite(CALL_PIN, HIGH); // Call the Master (Wake up!)
    // digitalWrite(LED_PIN, HIGH);
  }
  lastPiezoState = piezoState;
}
