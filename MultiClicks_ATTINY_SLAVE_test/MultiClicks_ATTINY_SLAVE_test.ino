/* PiezoHits & ATTiny-DIGISPARK

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
#include "TinyWireS.h"            // Get this from https://github.com/rambo/TinyWire

elapsedMillis timer;

#define I2C_SLAVE_ADDR      0x27  // I2C slave address

#define LED_PIN             1     // LED_BUILTIN
#define PIEZO_PIN_INPUT     5     // Piezo input PIN
#define CALL_PIN            4     // Pin to call (wake up) the Master     

#define THRESHOLD           10   // Threshold for the piezo analog readings
#define DEBOUNCE_TIME       20    // Debounce time to avoid parasitics impuls
#define TIME_OUT            800   // Timeout to output the hits sum   

boolean piezoState = false;
boolean lastPiezoState = false;
uint8_t hitsCount = 0;
uint8_t hits = 2;

byte incomingByte = 0;

void requestEvent() {
  TinyWireS.send(hits);
}

///////////////////////// SETUP
void setup() {  
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // pinMode(CALL_PIN, INPUT_PULLUP);
  pinMode(CALL_PIN, OUTPUT);
  digitalWrite(CALL_PIN, HIGH);
  
  TinyWireS.begin(I2C_SLAVE_ADDR);
  TinyWireS.onRequest(requestEvent);
  
  timer = 0;
}

///////////////////////// LOOP
void loop() {
  
  digitalWrite(LED_PIN, LOW);
  digitalWrite(CALL_PIN, LOW);
  tws_delay(1000);
  digitalWrite(LED_PIN, HIGH);
  digitalWrite(CALL_PIN, HIGH);
  tws_delay(1000);
}
