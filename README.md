This is my first program / arduino project. Please Enjoy. 

Here is a video of the project in it's current state: https://youtube.com/shorts/csgArc6coVU?feature=share

Arduino Alarm:  lidar sensor and alarm project. This is where I will record my findings and progress. I am unsure if this is the best place to do this, but it seems to be the easiest so far. 

This project is for detecting something within range.
When the lidar decetcs something within a meter it waits for 3 seconds and if the lidar is still detecthing something within 100cm it will make the alarm sonnd.

Because the code runs over and over, if the lidar is still blocked on the next pass around it will sound the alarm again.
If the beam is no longer blocked the alarm is supposed to stop sounding.

This currently plays a klaxon themed buzzer noise as an alarm. This will need to be adjusted to have an audio file play in the future.

Additional goals for the next step of this project include:
testing it with a laser and a solar panel, or something capable of detecing a beam pointed at it from 10 feet away. 

Currently it's a very small photoresistor with an LED against it. When you cover the photoresistor, blocks the light from the LED.
