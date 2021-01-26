/*******************************************************************************
 * File: RemoteControl.cpp
 * Author: Scott Polansky
 * Description: The RemoteControl class represents a touchscreen remote control.
 *              It displays a user interface and handles the interaction with
 *              the user
 ******************************************************************************/

#include "RemoteControl.h"


/*******************************************************************************
 * Function: RemoteControl
 * Return Value: n/a
 * Description: Default constructor. Initializes the screen and the user
 *              interface with the buttons
  ******************************************************************************/
RemoteControl::RemoteControl() : tft(TFT_CS, TFT_DC)
{
  // Setup the screen
  Adafruit_FT6206 ts = Adafruit_FT6206();

  // Set the colors of the buttons
  inactiveColor.red = DEFAULT_INACTIVE_RED;
  inactiveColor.green = DEFAULT_INACTIVE_GREEN;
  inactiveColor.blue = DEFAULT_INACTIVE_BLUE;

  activeColor.red = DEFAULT_ACTIVE_RED;
  activeColor.green = DEFAULT_ACTIVE_GREEN;
  activeColor.blue = DEFAULT_ACTIVE_BLUE;

  background.red = BACKGROUND_COLOR_RED;
  background.green = BACKGROUND_COLOR_GREEN;
  background.blue = BACKGROUND_COLOR_BLUE;
  
  // Instantiate the buttons
  uint16_t intColorInactive = inactiveColor.convertColor();
  uint16_t intColorActive = activeColor.convertColor();
 
  power       = Button(POWER_X, POWER_Y, BUTTON_HEIGHT, BUTTON_WIDTH, "POWER", intColorInactive, intColorActive, &tft);
  channelUp   = Button(CHANNEL_UP_X, CHANNEL_UP_Y, BUTTON_HEIGHT, BUTTON_WIDTH, "UP", intColorInactive, intColorActive, &tft);
  channelDown = Button(CHANNEL_DOWN_X, CHANNEL_DOWN_Y, BUTTON_HEIGHT, BUTTON_WIDTH, "DOWN", intColorInactive, intColorActive, &tft);
  volumeUp    = Button(VOLUME_UP_X, VOLUME_UP_Y, BUTTON_HEIGHT, BUTTON_WIDTH, "UP", intColorInactive, intColorActive, &tft);
  volumeDown  = Button(VOLUME_DOWN_X, VOLUME_DOWN_Y, BUTTON_HEIGHT, BUTTON_WIDTH, "DOWN", intColorInactive, intColorActive, &tft);
  input       = Button(INPUT_X, INPUT_Y, BUTTON_HEIGHT, BUTTON_WIDTH, "INPUT", intColorInactive, intColorActive, &tft);

  uint8_t powerSequence[6]       = {0xFD, 0xAA, 0xAD, 0xBB, 0xDA, 0xD5};
  uint8_t channelDownSequence[6] = {0xFD, 0xAA, 0xAA, 0x55, 0x7F, 0xD5};
  uint8_t channelUpSequence[6]   = {0xFD, 0xAA, 0xAD, 0x5A, 0xFD, 0xD5};
  uint8_t volumeDownSequence[6]  = {0xFD, 0xAA, 0xAD, 0xAA, 0xF7, 0xD5};
  uint8_t volumeUpSequence[6]    = {0xFD, 0xAA, 0xAD, 0xB5, 0xED, 0xD5};
  
  
  power.setActionSequence(powerSequence, 6);
  channelUp.setActionSequence(channelUpSequence, 6);
  channelDown.setActionSequence(channelDownSequence, 6);
  volumeUp.setActionSequence(volumeUpSequence, 6);
  volumeDown.setActionSequence(volumeDownSequence, 6);

  
  wasTouched = false;
  lastButton = nullptr;
  
  return;
}

/*******************************************************************************
 * Function: draw
 * Return Value: n/a
 * Description: Initializes the screen and draws the remote control on the screen.
 *               This should be called only in the setup() function of the sketch.
  ******************************************************************************/
void RemoteControl::draw()
{
  tft.begin();
  
  if (!ts.begin(40))
  {
    Serial.println("Unable to start touchscreen.");
  }
  else
  {
    Serial.println("Touchscreen started.");
  }

  
  // Fill the background of the screen and set the text settings
  uint16_t intBackground = background.convertColor();
  tft.fillScreen(intBackground);
  tft.setTextColor(ILI9341_WHITE);
  tft.setFont(&FreeSans9pt7b);
  tft.setTextSize(1);
  
  // Draw the buttons
  power.drawButton();
  channelUp.drawButton();
  channelDown.drawButton();
  volumeUp.drawButton();
  volumeDown.drawButton();
  input.drawButton();

  // Calculate the dimensions of the labels so they can be centered above the buttons
  int16_t x1, y1;
  uint16_t w, h;
  int channelTextWidth, channelTextHeight, volumeTextWidth, volumeTextHeight;
  tft.getTextBounds("Channel", 0, 0, &x1, &y1, &w, &h);
  channelTextWidth = w;
  tft.getTextBounds("Channel", 0, 0, &x1, &y1, &w, &h);
  volumeTextWidth = w;
  
  // Calculate the locations of the labels so they're centered above the buttons
  int xCoordChannel = CHANNEL_UP_X + BUTTON_WIDTH / 2 - channelTextWidth / 2;
  int yCoordChannel = CHANNEL_UP_Y - 10;
  int xCoordVolume = VOLUME_UP_X + BUTTON_WIDTH / 2 - volumeTextWidth / 2;
  int yCoordVolume = VOLUME_UP_Y - 10;
  
  // Draw the labels above the channel and volume buttons
  tft.setCursor(xCoordVolume, yCoordVolume);
  tft.println("Volume");
  tft.setCursor(xCoordChannel, yCoordChannel);
  tft.println("Channel");
}


/*******************************************************************************
 * Function: loop
 * Return Value: n/a
 * Description: Loops through repeatedly to see if the user has pushed a button
 *              and handles the necessary interaction like sending signals and
 *              changing the display.
 *              
 * Note: The buttons do not currently send any signals--that will be added later
  ******************************************************************************/
void RemoteControl::loop()
{
  // See if the screen has been touched
  bool currentTouch = ts.touched();

  if ((currentTouch && !wasTouched) || (!currentTouch && wasTouched))
  {
    // Get the location of the spot that was pushed
    TS_Point p = ts.getPoint();
    p.x = tft.width() - p.x;
    p.y = tft.height() - p.y;


    // See if the user just released a button
    if (!currentTouch && wasTouched)
    {
      if (lastButton != nullptr)
      {
        lastButton->flipColor();
      }
      wasTouched = false;
      return;
    }

    // Check to see what button was pushed
    if (power.inButton(p.x, p.y))
    {
      power.flipColor();
      lastButton = &power;
      delay(BUTTON_DELAY);
      power.performActionSequence();
    }
    else if (channelUp.inButton(p.x, p.y))
    {
      channelUp.flipColor();
      lastButton = &channelUp;
      delay(BUTTON_DELAY);
      channelUp.performActionSequence();
    }
    else if (channelDown.inButton(p.x, p.y))
    {
      channelDown.flipColor();
      lastButton = &channelDown;
      delay(BUTTON_DELAY);
      channelDown.performActionSequence();
    }
    else if (volumeUp.inButton(p.x, p.y))
    {
      volumeUp.flipColor();
      lastButton = &volumeUp;
      delay(BUTTON_DELAY);
      volumeUp.performActionSequence();
    }
    else if (volumeDown.inButton(p.x, p.y))
    {
      volumeDown.flipColor();
      lastButton = &volumeDown;
      delay(BUTTON_DELAY);
      volumeDown.performActionSequence();
    }
    else if (input.inButton(p.x, p.y))
    {
      input.flipColor();
      lastButton = &input;
      delay(BUTTON_DELAY);
    }
    else
    {
      Serial.println("here");
      lastButton = nullptr;
    }

    wasTouched = true;
  }
    
  return;
}
