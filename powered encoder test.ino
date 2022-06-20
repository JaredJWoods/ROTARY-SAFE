/* Encoder Library - TwoKnobs Example
*/

#include <Encoder.h>
#include <Mouse.h>

// Change these pin numbers to the pins connected to your encoder.
Encoder knobLeft(2, 3);


void setup() {
  Serial.begin(9600);
  Mouse.begin();
}

long rotaryPosition  = -999;


void loop() {
  long newRotaryPosition;
  newRotaryPosition = knobLeft.read();

  if (newRotaryPosition != rotaryPosition) {
    Serial.print("Position = ");
    Serial.print(newRotaryPosition);
    
    Serial.println();
    if(newRotaryPosition > rotaryPosition){
      Mouse.move(0,1,0);
    }
    else if(newRotaryPosition < rotaryPosition){
      Mouse.move(0,-1,0);
    }
    rotaryPosition = newRotaryPosition;
  }
  // if a character is sent from the serial monitor,
  // reset both back to zero.
  if (Serial.available()) {
    Serial.read();
    Serial.println("Reset both knobs to zero");
    knobLeft.write(0);
  }
}
