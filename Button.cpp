/*******************************************************************************
 * File: Button.cpp
 * Author: Scott Polansky
 * Description: The Button class represents a button on the touchscreen. It
 *              displays the button and performes the appropriate action when
 *              pressed.
 ******************************************************************************/


#include "Button.h"


/*******************************************************************************
 * Function: Button
 * Return Value: n/a
 * Description: Default constructor. Shouldn't be used because the button won't
 *              do anything or be able to be displayed.
  ******************************************************************************/
Button::Button()
{
	x_coord = 0;
	y_coord = 0;
	height = 0;
	width = 0;

	tft = nullptr;
	return;
}


/*******************************************************************************
 * Function: Button
 * Return Value: n/a
 * Description: Constructor that specifies the required information
 *              needed for displaying and operating a button
 *              
 * Notes: Buttons do not do anything yet. That code will be added later
  ******************************************************************************/
Button::Button(int x, int y, int height, int width, String label, uint16_t inactiveColor, uint16_t activeColor, Adafruit_ILI9341* tft)
{
  // Set the attributes of the button
	this->x_coord = x;
	this->y_coord = y;
	this->height = height;
	this->width = width;
  this->label = label;

  // Set the colors
  this->activeColor = activeColor;
  this->inactiveColor = inactiveColor;

  currentColor = inactiveColor;
  
	// Setup the TFT and touchscreen
	this->tft = tft;

	return;
}


/*******************************************************************************
 * Function: ~Button
 * Return Value: n/a
 * Description: Destructor. Nothing much to do here
  ******************************************************************************/
Button::~Button()
{
  return;
}


/*******************************************************************************
 * Function: drawButton
 * Return Value: n/a
 * Description: Draws the button on the screen
  ******************************************************************************/
void Button::drawButton()
{
	tft->fillRoundRect(x_coord, y_coord, width, height, 4, currentColor);

  // Determine the size of the label so that it can be center in the button
  int16_t x1, y1;
  uint16_t h, w;
  tft->getTextBounds(label.c_str(), 0, 0, &x1, &y1, &w, &h);

  // Figure out where it should go
  int xCoordText = (x_coord + width / 2) - w / 2;
  int yCoordText = (y_coord + height / 2) + h / 2;
  tft->setCursor(xCoordText, yCoordText);
  tft->println(label);
	return;
}


/*******************************************************************************
 * Function: inButton
 * Return Value: TRUE if (x,y) is within the boundaries of the button,
 *               FALSE otherwise
 * Description:  Used for determining whether a the spot touched on the
 *               touchscreen is on the button
  ******************************************************************************/
bool Button::inButton(int x, int y)
{
  if ((x >= x_coord)
      && (x <= x_coord + width)
      && (y >= y_coord)
      && (y <= y_coord + height))
  {
    return true;
  }
  else
  {
    return false;  
  }
}

/*******************************************************************************
 * Function: flipColor
 * Return Value: n/a
 * Description: Flips the displayed color of the button from inactive --> active
 *              or vice versa
  ******************************************************************************/
void Button::flipColor()
{
  if (currentColor == inactiveColor)
  {
    currentColor = activeColor;
  }
  else
  {
    currentColor = inactiveColor;
  }

  drawButton();

  return;
}


/*******************************************************************************
 * Function: setActionSequence
 * Return Value: n/a
 * Description: Sets the sequence of pulses for the action.
 * 
 * Parameters:  sequence - an array of 8-bit numbers (or 2- digit hexadecimals) 
 *                         that represent the IR pulses for command
 *              bytes -    the number of bytes in the sequence, i.e. the number
 *                         of elements in the array
  ******************************************************************************/
void Button::setActionSequence(uint8_t *sequence, int bytes)
{
  buttonAct.setSequence(sequence, bytes);
}