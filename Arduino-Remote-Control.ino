// Include the library files for the touchscreen
#include <Adafruit_ILI9341.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_FT6206.h>

// Include the file for the RemoteControl
#include "RemoteControl.h"


// This RemoteControl object that will control the user interface and
// send the signals to the TV
RemoteControl r;


// Run setup to draw the buttons
void setup()
{
  Serial.begin(9600);
  r.draw();
}


// Loop repeatedly to receive button inputs and perform actions
void loop()
{
  // Have the RemoteControl listen for touches on the screen
  // Loop will also send the signals when the appropriate buttons are pushed (not implemented yet).
  r.loop();
}