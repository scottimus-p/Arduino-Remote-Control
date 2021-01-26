/*******************************************************************************
 * File: Action.cpp
 * Author: Scott Polansky
 * Description: This class performs a specific remote control action, e.g. turn
 *              on/off a TV, change the channel, etc.
 ******************************************************************************/


#include "Action.h"

/*******************************************************************************
 * Function: Action
 * Return Value: n/a
 * Description: Default constructor
  ******************************************************************************/
Action::Action()
{
  hexCode = nullptr;
  return;
}

Action::~Action()
{
  // Free the memory allocated to hexCode
  delete [] hexCode;
  return;
}
/*******************************************************************************
 * Function: setSequence
 * Return Value: n/a
 * Description: Sets the sequence of IR pulses that the LED should perform. The
 *              sequence is an array of 8-bit instructions. Each 1-bit
 *              represents an IR pulse and 0-bit represents no IR pulse. Each
 *              bit is separated by a short pause represented by PAUSE_LENGTH
 *              microseconds. Each bit has a duration of PULSE_LENGTH 
 *              microseconds.
  ******************************************************************************/
void Action::setSequence(uint8_t *sequence, int bytes)
{
  // Allocate the memory for hexCode
  hexCode = new uint8_t[bytes];

  // Now fill the array
  for (int i = 0; i < bytes; i++)
  {
    hexCode[i] = sequence[i];
  }

  sequenceBytes = bytes;
  
  return;
}


/*******************************************************************************
 * Function: performAction
 * Return Value: n/a
 * Description: Performs the action by running through the sequence. The IR LED
 *              is should be hooked up to the pin number defined by the const
 *              LED_PIN.
  ******************************************************************************/
void Action::performAction()
{
  // First check that we've set a sequence
  if (hexCode == nullptr)
  {
    // Looks like there's nothing to do
    return;
  }
  
  /*****************************************************************************
  *  Perform the intro sequence -- this section should be improved to be more
  *  flexible. Will need to see how the intro sequences differ by electronic
  *  manufacturer/device
  *****************************************************************************/
  digitalWrite(LED_PIN, LOW);     // Make sure the LED is off to start
  pulseIR(INTRO_1);
  delayMicroseconds(INTRO_2);
  pulseIR(PULSE_LENGTH);


  // Send the main signal
  for (int i = 0; i < sequenceBytes; i++)
  {
    // Pulse the LED if a 1 otherwise leave it off for a 0
    if (((hexCode[i] >> i) & 1) == 1)
    {
      pulseIR(PULSE_LENGTH);
    }

    // Pause in between the bits
    delayMicroseconds(PAUSE_LENGTH); 
  }

  /*****************************************************************************
  *  Perform the ending sequence -- this section should also be improved to be
  *  more flexible.
  *****************************************************************************/
  delayMicroseconds(ENDING_1 - PAUSE_LENGTH);
  pulseIR(ENDING_2);
  delayMicroseconds(ENDING_3);
  pulseIR(ENDING_4);

  return;
}


/*******************************************************************************
 * Function: pulseIR
 * Return Value: n/a
 * Description: Pulses the IR LED at 38kHz. The LED should be connected to the
 *              pin number defined by the constant LED pin. The pulse will last
 *              for the specified number of microseconds.
 *              
 *              I got this code from someone else online...I can't remember 
 *              the source.
  ******************************************************************************/
 void Action::pulseIR(long microsecs)
 {
  // This procedure sends a 38KHz pulse to the LED_PIN
 // for a certain # of microseconds.

  // The length of the pulse, from beginning to end, in microseconds
  int pulseLength = 1 / FREQUENCY * 1000;
  int pauseLength = pulseLength / 2 - SWITCH_DURATION;

  
  cli();  // this turns off any background interrupts

  while (microsecs > 0)
  {
    digitalWrite(LED_PIN, HIGH);
    delayMicroseconds(pauseLength);
    digitalWrite(LED_PIN, LOW);
    delayMicroseconds(pauseLength);

    // so 26 microseconds altogether
    microsecs -= PULSE_LENGTH;
  }

   sei();  // this turns them back on
 }