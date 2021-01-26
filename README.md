# Arduino-Remote-Control #
A touchscreen remote control made using Arduino.

This project is a remote control using a touchscreen interface made using an Arduino. A touchscreen was used to make the project more flexible so that the buttons could easily be added, removed or modified for different devices. The code uses several Adafruit libraries to handle the dirty work of controlling the touchscreen.
  
Fortunately for me, it will work with my Toshiba TV. Unfortunately for you, it sends signals only compatible with my Toshiba TV. Modifications can be made to work with your TV, stereo, VCR...pretty much any consumer electronic device that uses infrared-based remote controls.
 
### Components ###
- Arduino Mega - https://www.adafruit.com/product/191 
- Adafruit 2.8" TFT Capacitive Touch Shield - https://www.adafruit.com/product/1947  
- 5mm IR LED (940nm wavelength) - https://www.adafruit.com/product/387  
- 1 kOhm resistor*

* A different resistor may work better by providing a "brighter" (humans can't actually see infrared light) light

### Instructions ###
1. To change the buttons, modify the constructor for `RemoteControl` in `RemoteControl.cpp`. It should be pretty obvious what to change. The constructor for each `Button` has the coordinates for the button's position, the text displayed on the button and the color. A few lines below that are the sequences for defining the IR pulses that are transmitted when the button is pushed.
2. Set the IR sequences for a given action (e.g. power on, volume up, volume down...) for the desired device. They're defined by 6-byte sequences, where the IR led pulses `ON` for each 1-bit and `OFF` for each 0-bit. Frequently, the sequences are the same for all/most devices from a given manufacturer but will vary from one manufacturer to the next.
3. Upload the code in the `ArduinoRemoteControl.ino` sketch along with the rest of the `.cpp` and `.h` files to your Arduino.
4. Assemble the components according to the diagram below, power on the Arduino and you're all set. The LED should be hooked up to pin 30 unless the `#define` for `LED_PIN` is changed in `Action.h`.

<img src="https://github.com/scottimus-p/arduino-remote-control/blob/main/Arduino-Remote.png" width="450">

### IR Pulsing ###
Each signal is consists of the following sequence:  
1. An intro sequence where the IR led is `ON` for approximately 9440 microseconds followed by an `OFF` for approximately 4660 microseconds. This lets the device know to start listening. Think of it as the "Hey Google" or "Hey Siri" for your device.
2. A sequence of `ON` and `OFF` pulses which define the command. `ON`s are represented by a `1` in the command sequence and `OFF`s are represented by a `0`. Each `1` and `0` 760 microseconds is separated from the preceding `1` or `0` by 380 microseconds.
3. An exit sequence which tells the device it can stop listening. The exit sequence consists of an `OFF` for approximately 41200 microseconds, followed by an `ON` for 9420 microseconds, an `OFF` for 2120 microseconds and one final `ON` for 760 microseconds.

Each `ON` pulse is not a continuous flash of IR. Rather it is itself a high-frequency pulsing of IR light occuring at 38 kHz.
