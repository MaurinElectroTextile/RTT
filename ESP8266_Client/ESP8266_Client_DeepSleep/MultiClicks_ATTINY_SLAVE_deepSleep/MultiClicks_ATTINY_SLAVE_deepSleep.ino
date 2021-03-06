/* tapSens & ATTiny-DIGISPARK

  https://www.youtube.com/watch?v=ZDDcz9buKgM

  DIGISPARK slave
  Flash with Digispark (1mhz - No USB).
  Sample a "pezo sensor" and send hits count to NodeMCU master.

  PIN

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

  Single click -> send int '1'
  Double click -> send int '2'
  Triple click -> send int '3'
*/

#include <elapsedMillis.h>        // Library to take care of the timer overflow
#include "TinyWireS.h"            // Wire lib for ATTiny85

elapsedMillis timer;

#define I2C_SLAVE_ADDR      0x27  // I2C slave address

#define PIEZO_PIN_INPUT     1     // Piezo input PIN P3
#define WAKE_PIN            4     // Pin to wake up the NodeMCU-Master connected to NodeMCU RST_PIN

#define THRESHOLD           100   // Threshold for the piezo analog readings
#define DEBOUNCE_TIME       50    // Debounce time to avoid parasitics impuls
#define TIME_OUT            300   // Timeout to output the hits sum   

boolean piezoState = false;
boolean lastPiezoState = false;
uint8_t hitsSum = 0;
uint8_t hitsCount = 0;

void requestEvent() {
  TinyWireS.send(hitsCount);
}

///////////////////////// SETUP
void setup() {
  analogReference(DEFAULT);

  pinMode(PIEZO_PIN_INPUT, INPUT);

  // pinMode(WAKE_PIN, INPUT_PULLUP); // DO NOT WORKI!?
  pinMode(WAKE_PIN, OUTPUT);
  digitalWrite(WAKE_PIN, HIGH);

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
      hitsSum++;
      timer = 0;
    }
  }
  // If the button released state is stable, report number of clicks and start new cycle
  if ( timer > TIME_OUT && hitsSum != 0 && hitsSum < 4) {
    hitsCount = hitsSum;
    hitsSum = 0;
    digitalWrite(WAKE_PIN, LOW);   // Wake up the Master
    delay(1000);                   // Wake up the Master
    digitalWrite(WAKE_PIN, HIGH);  // Wake up the Master
  } else if (hitsSum > 3) {
    hitsSum = 0;
  }
  lastPiezoState = piezoState;
}
