This is my first program / arduino project. Please Enjoy. 

Arduino Alarm:  sensor and alarm project. This is where I will record my findings and progress. I am unsure if this is the best place to do this, but it seems to be the easiest so far. 

It is for detecting a laser's beam on a photoresistor. 
When the beam is removed it waits for 3 seconds and if the beam is still removed from the sensor it will make alarm sonnd.

Because the code runs over and over, if the beam is still blocked on the next pass around it will sound the alarm again.
If the beam is no longer blocked the alarm will stop sounding.

This currently plays a klaxon themed buzzer noise as an alarm. 

Additional goals for the next step of this project include:
testing it with a laser and a solar panel, or something capable of detecing a beam pointed at it from 10 feet away. 

Currently it's a very small photoresistor with an LED against it. When you cover the photoresistor, blocks the light from the LED.
