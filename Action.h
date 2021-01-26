/*******************************************************************************
 * File: Action.h
 * Author: Scott Polansky
 * Description: This class performs a specific remote control action, e.g. turn
 *              on/off a TV, change the channel, etc.
 ******************************************************************************/


#ifndef ACTION_H
#define ACTION_H

#include "Arduino.h"

#define INTRO_1 9440        // IR LED should be on for this many microseconds in the intro section
#define INTRO_2 4660        // IR LED should be off for this many microseconds in the intro section
#define ENDING_1 41200      // IR exit sequence
#define ENDING_2 9420       // IR exit sequence
#define ENDING_3 2100       // IR exit sequence
#define ENDING_4 760        // IR exit sequence
#define PULSE_LENGTH 760    // Each bit in the signal is represented by either being on or off for this many usec
#define PAUSE_LENGTH 380    // Each bit is separated by this many usec
#define SWITCH_DURATION 3   // It takes 3 microseconds to switch on/off the LED
#define LED_PIN 30          // The pin that the IR LED is hooked up to
#define FREQUENCY 38        // The frequency of the IR pulse in kHz

class Action
{
private:
  uint8_t *hexCode;
  void pulseIR(long microsecs);
  int sequenceBytes; // The size of hexCode in bytes -- basically the length of the IR sequence

public:
  Action();
  ~Action();
  void setSequence(uint8_t *sequence, int bytes);
  void performAction();
  
};


#endif
