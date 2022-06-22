ABOUT: 
This is my first program / arduino project. Please Enjoy. 
This is where I will record my findings and progress. I am unsure if this is the best place to do this, but it seems to be the easiest so far. 

Arduino Alarm:  lidar sensor and alarm project. 

Because the code runs over and over, if the lidar is still blocked on the next pass around it will sound the alarm again.
If the beam is no longer blocked the alarm is supposed to stop sounding.




REQUIRED GOALS: 
To determine if an object is blocking a path. If the path is blocked an alarm goes off.

ADDITIONAL GOALS:
- Test powering the project with a battery and solar panel
- Install a speaker
- Install a dedicated sound board to trigger an audio file to play instead of a buzzer noise: https://www.adafruit.com/product/2342
- Develop a XOD node for TF-Luna so I can use a visual programming tool instead. My current Xodball is also uplaoded to this repository.



STATUS:
Currently a Elegoo Mega2560 is being used.
TF-Luna Lidar sensor is in use. When it measures an object under 200cm an accumulator will start and if you do not get out of the path of the beam it will sound an alarm after 3 seconds. If you get out of the path before 3 seconds, the accumulator will decrement back to zero. If something is closer than 10cm it will not sound. This is to prevent the alarm from sounding when nothing is detected in the path or if the sensor fails. The sensor reads 000cm at it's max distance is why.
Here is a video of the project at one point: https://youtube.com/shorts/csgArc6coVU?feature=share 
 
 
 
 
PINOUT:

TF-LUNA LIDAR:
1 +5V Power supply
2 RXD/SDA Receiving/Data
3 TXD/SCL Transmitting/Clock
4 GND Ground
5 Configuration Input - (Not used with UART. GND when I2C is in use supposedly)
Ground: I2C mode
/3.3V: Serial port
Communications mode
6 Multiplexing output - (Not used for our purposes) 
Default: on/off mode output
I2C mode: Data availability
signal on but not switching 
value mode



Buzzer: Pin O7 IN. GND out

ARDUINO ELEGOO PINOUT A2560 TO Lidar (UART):  RX PIN into TX1 18 / TX PIN into RX1 19
ARDUINO ELEGOO PINOUT A2560 TO Lidar (i2C): (RX)SDA PIN into SDA20
Speaker: Pin 07 IN. GND OUT
