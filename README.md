# Arduino-Remote-Control #
A touchscreen remote control made using Arduino.

This project is a remote control using a touchscreen interface made using an Arduino. A touchscreen was used to make the project more flexible so that the buttons could easily be added, removed or modified for different devices. The code uses several Adafruit libraries to handle the dirty work of controlling the touchscreen.
  
Fortunately for me, it will work with my Toshiba TV. Unfortunately for you, it sends signals only compatible with my Toshiba TV. Modifications can be made to work with your TV, stereo, VCR...pretty much any consumer electronic device that uses infrared-based remote controls.
 
### Components ###
Arduino Uno - https://www.adafruit.com/product/50  
Adafruit 2.8" TFT Capacitive Touch Shield - https://www.adafruit.com/product/1947  
5mm IR LED (940nm wavelength) - https://www.adafruit.com/product/387  
1 kOhm resistor

### Instructions ###
1. To change the buttons, modify the constructor for `RemoteControl` in `RemoteControl.cpp`. You'll add a new instance of `Button` for any new buttons, or modify existing buttons.
2. Set the IR sequences for a given action (e.g. power on, volume up, volume down...) for the desired device. Getting this info can be tricky. I'll see if I can find a source.
3. Upload the code in the `ArduinoRemoteControl.ino` sketch to your Arduino.
4. Assemble the components, power on the Arduino and you're set!
