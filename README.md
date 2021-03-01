# arduino-remote-volume-control
This project enables you to use an Arduino and an IR remote to control a motorised potentiometer, as typically found in stereo amplifiers with remote volume control.  
The benefit of this approach is that you don't need a separate board (and PSU for that board) to drive the motor. The motorised version of the popular Alps blue potentiometers require 100 mA to turn the pot. Each Arduino pin can provide up to 20 mA, so 5 pins combined is enough to turn the pot.  
  
In my own setup, I used an Arduino Nano Every with a 12v PSU. The code is written for using pins D2 - D6 for motor up commands, and pins D7 - D11 for motor down commands. The IR receiver is connected to D12.  
  
The inspiration for this project came from a post on the HiFiVision forum:  
https://www.hifivision.com/threads/simple-ir-remote-for-motorized-alps-pot-directly-using-arduino.44275/
