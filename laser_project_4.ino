#define NOTE_F6  1397 // This is the note of the first half of the alarm
#define NOTE_G4  392 // This is the note of the second half of the alarm

//define the various items used
int Laser = 12; //Laser's positive is plugged into Pin 12
int alarmSpeaker = 7; // AlarmSpeaker's positive is in pin 7
int LED = 13; // Light or LED is in pin 13 for notifications on status.
int light; // The Light Sensor

void setup() {
  pinMode(Laser, OUTPUT);
  pinMode(alarmSpeaker, OUTPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(9600); // initialize serial communication with the arduino at 9600 bits per second
}
// Code to make noise out of the buzzer
void alarmTone() {
  tone(7,  NOTE_F6, 400); //First note of AlarmTone
  delay(100);
  tone(7,  NOTE_G4, 400); //Second note of Alarmtone
  delay(100);
}
// The code to play the alarm and how often
void alarm() {
  delay(500); //Time before  alarm starts
  alarmTone();
  alarmTone();
  delay(1000); //Time waiting after alarm starts
}

void loop() {
  light = analogRead(A0); // Label the port A0 as sensor
  Serial.println(light); // Print sensor's (A0) through serial port to control panel
  digitalWrite(Laser, HIGH); // Initialize the Laser's Power
  if (light < 400) // Wait for the console to read below 400
  {
    digitalWrite(LED, HIGH); // if the console to read below 400 turn the LED on
    delay(1000); // wait 1 seconds to wait for beam to establish
// There is an issue in this area. The console stops pushing data when it drops below 400. 
// I need it to continue or the alarm goes off because no new numbers have shown up in the console that it's reading from. it just stopped and the previous readout is still the current readout. 
    if (light < 400) // if the console does not say above 400 turn on the alarm.
    {
      alarm(); // sound the alarm
    }
    delay(3000); //Time after  alarm ends - wait 3 seconds
    digitalWrite(LED, LOW); // turn the LED off
  }
  else
    digitalWrite(LED, LOW);
}
