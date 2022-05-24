#include <TFMPlus.h>  // Include TFMini Plus Library v1.5.0
TFMPlus tfmP;         // Create a TFMini Plus object
#include "printf.h"   // Modified to support Intel based Arduino

#define NOTE_F6  1397 // This is the note of the first half of the alarm
#define NOTE_G4  392 // This is the note of the second half of the alarm

//define the various items used
int alarmSpeaker = 7; // AlarmSpeaker's positive is in pin 7
int LED = 13; // Light or LED is in pin 13 for notifications on status.


void setup()
{
  pinMode(alarmSpeaker, OUTPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(115200); // initialize serial communication with the arduino at 9600 bits per second
  delay(20);               // Give port time to initalize
  printf_begin();          // Initialize printf.
  printf("\r\nTFMPlus Library Example - 10SEP2021\r\n");  // say 'hello'
  Serial2.begin( 115200);  // Initialize TFMPLus device serial port.
  delay(20);               // Give port time to initalize
  tfmP.begin( &Serial2);   // Initialize device library object and...
  // pass device serial port to the object.
  printf( "Firmware version: ");
  if ( tfmP.sendCommand( GET_FIRMWARE_VERSION, 0))
  {
    printf( "%1u.", tfmP.version[ 0]); // print three single numbers
    printf( "%1u.", tfmP.version[ 1]); // each separated by a dot
    printf( "%1u\r\n", tfmP.version[ 2]);
  }
  else tfmP.printReply();
  // - - Set the data frame-rate to 20Hz - - - - - - - -
  printf( "Data-Frame rate: ");
  if ( tfmP.sendCommand( SET_FRAME_RATE, FRAME_20))
  {
    printf( "%2uHz.\r\n", FRAME_20);
  }
  else tfmP.printReply();
  // - - - - - - - - - - - - - - - - - - - - - - - -
  delay(500);            // And wait for half a second.
}
// Initialize variables
int16_t tfDist = 0;    // Distance to object in centimeters
int16_t tfFlux = 0;    // Strength or quality of return signal
int16_t tfTemp = 0;    // Internal temperature of Lidar sensor chip


// Use the 'getData' function to pass back device data.
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
  if ( tfmP.getData( tfDist, tfFlux, tfTemp)) // Get data from the device.
  {
    printf( "Dist:%04icm ", tfDist);   // display distance,
    printf( "Flux:%05i ",   tfFlux);   // display signal strength/quality,
    printf( "Temp:%2i%s",  tfTemp, "C");   // display temperature,
    printf( "\r\n");                   // end-of-line.
    delay(50);   // Loop delay to match the 20Hz data frame rate
  }
  else                  // If the command fails...
  {
    tfmP.printFrame();  // display the error and HEX data
  }
  if (tfDist < 100) // Wait for the console to read below 100cm
  {
    digitalWrite(LED, HIGH); // if the console reads below 100CM turn the LED on
    delay(3000); // wait 3 seconds to wait for beam to establish
    if (tfDist < 100) // Get data from the device. if the console STILL does not say above 100 cm turn on the alarm.
    
    {
      alarm(); // sound the alarm
    }
    digitalWrite(LED, LOW); // turn the LED off
    return;
  }
  else
    digitalWrite(LED, LOW);
}
