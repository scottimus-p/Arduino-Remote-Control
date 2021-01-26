/*******************************************************************************
 * File: Button.h
 * Author: Scott Polansky
 * Description: The Button class represents a button on the touchscreen. It
 *              displays the button and performes the appropriate action when
 *              pressed.
 ******************************************************************************/

#ifndef BUTTON_H
#define BUTTON_H

#include <Adafruit_ILI9341.h>
#include "Arduino.h"
#include "Action.h"

#define IR_TRANSMIT_PIN 3   // The pin that the transimtting LED is on
#define PULSE_LENGTH 550
#define DELAY_LENGTH 600

class Button
{
private:
	int x_coord;
	int y_coord;
	int height;
	int width;
  String label;
  uint16_t inactiveColor;
  uint16_t activeColor;
  uint16_t currentColor;
  Action buttonAct;

	Adafruit_ILI9341* tft; // The screen that the button is on

public:
	Button();
	Button(int x, int y, int height, int width, String label, uint16_t inactiveColor, uint16_t activeColor, Adafruit_ILI9341* tft);
	~Button();
  void drawButton();
	void flipColor();
  bool inButton(int x, int y);
  void setActionSequence(uint8_t *sequence, int bytes); // Sounds exciting!!!

};

#endif