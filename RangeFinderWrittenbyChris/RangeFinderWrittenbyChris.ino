#define USE_TIMER_1 true

#include "TimerInterrupt.h"


#include <TFMPlus.h>  // Include TFMini Plus Library v1.5.0
TFMPlus tfmP;         // Create a TFMini Plus object
#include "printf.h"   // Modified to support Intel based Arduino

#define NOTE_F6  1397 // This is the note of the first half of the alarm
#define NOTE_G4  392 // This is the note of the second half of the alarm

//define the various items used
int alarmSpeaker = 7; // AlarmSpeaker's positive is in pin 7
int LED = 13; // Light or LED is in pin 13 for notifications on status.

// Initialize variables
int16_t tfDist = 0;    // Distance to object in centimeters
int16_t tfFlux = 0;    // Strength or quality of return signal
int16_t tfTemp = 0;    // Internal temperature of Lidar sensor chip

int16_t inFrontCounter = 0;
int16_t clearCounter = 0;

bool sensorBlocked;
bool alarming = false;
bool tone1 = true;



#define TIMER1_INTERVAL_MS 100UL

// Use the 'getData' function to pass back device data.
// Code to make noise out of the buzzer
// this code runs every 100 ms on a timer
void alarmToneInterrupt() {
  if (alarming) {
    if (tone1) {
      tone(7,  NOTE_F6, 400); //First note of AlarmTone
    } else {
      tone(7,  NOTE_G4, 400); //Second note of Alarmtone
    }
    tone1 = !tone1;
  }
}

void setup()
{

  pinMode(alarmSpeaker, OUTPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(115200); // initialize serial communication with the arduino at 9600 bits per second
  delay(20);               // Give port time to initalize
  printf_begin();          // Initialize printf.
  printf("\r\nLiDar Range Project - 5MAY2022 - By Daniel B\r\n");  // say 'hello'
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
  // delay(500);            // And wait for half a second.

  
  // Select Timer 1-2 for UNO, 1-5 for MEGA, 1,3,4 for 16u4/32u4
  // Timer 2 is 8-bit timer, only for higher frequency
  // Timer 4 of 16u4 and 32u4 is 8/10-bit timer, only for higher frequency
  ITimer1.init();

  // Using ATmega328 used in UNO => 16MHz CPU clock ,
  // For 16-bit timer 1, 3, 4 and 5, set frequency from 0.2385 to some KHz
  // For 8-bit timer 2 (prescaler up to 1024, set frequency from 61.5Hz to some KHz

  if (ITimer1.attachInterruptInterval(TIMER1_INTERVAL_MS, alarmToneInterrupt))
  {
    Serial.print(F("Starting  ITimer1 OK, millis() = ")); Serial.println(millis());
  }
  else
    Serial.println(F("Can't set ITimer1. Select another freq. or timer"));
}


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
  delay(50); //Time before  alarm starts
  alarmTone();
  alarmTone();
  delay(1000); //Time waiting after alarm finishes
}


void loop() {
  sensorBlocked = false;

  // Always get data from sensor every single loop
  if ( tfmP.getData( tfDist, tfFlux, tfTemp)) // Get data from the device.
  {
    printf( "Dist:%04icm ", tfDist);   // display distance,
    printf( "Flux:%05i ",   tfFlux);   // display signal strength/quality,
    printf( "Temp:%2i%s",  tfTemp, "C");   // display temperature,
    printf( "\r\n");    // end-of-line.
    // if object within 100cm, set sensorBlocked to true
    if (tfDist < 100 && tfDist > 10) {
      sensorBlocked = true;
    }
  }

  // if sensorBlocked
  if (sensorBlocked) {
    if (inFrontCounter < 350) { // be careful not to overflow variable
      inFrontCounter++; // increment a counter to accumulate time that sensor is blocked
    }
  } else if (!sensorBlocked) { // when sensor isn't blocked, clear the time accumulator
    inFrontCounter = 0;
  }
  
  if (inFrontCounter >= 300) { // if we have accumulated 3 seconds (300*10ms) of object blocking
    alarming = true; // alarm on
    clearCounter = 300; // set clearTimer
  } else if (alarming && !sensorBlocked) { // if we're currently alarming and nothing is in front of the sensor
   if (--clearCounter <= 0) { // prevent underflow of clearCounter
     inFrontCounter = 0; // reset sensor blocked accumulator
     clearCounter = 0; // reset clear timer
     alarming = false; // turn off alarm
   }
  }


  // every 10 ms
  delay(10);
  /*
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
    if (tfDist < 100) // Get data from the device. if the console STILL says below 100 cm turn on the alarm.
    {
    digitalWrite(LED, HIGH); // if the console reads below 100CM turn the LED on
    delay(3000); // wait 3 seconds to wait for beam to establish
    {
      // This is all to get data from the device working again before it makes an alarm noise
      if ( tfmP.getData( tfDist, tfFlux, tfTemp)) // Get data from the device.
        printf( "Dist:%04icm ", tfDist);   // display distance,
      printf( "Flux:%05i ",   tfFlux);   // display signal strength/quality,
      printf( "Temp:%2i%s",  tfTemp, "C");   // display temperature,
      printf( "\r\n");                   // end-of-line.
      delay(500);   // This is to wait for the readings to start working again
    }
    if (tfDist < 100) // Get data from the device. if the console STILL does not say above 100 cm turn on the alarm.
    {
      printf ( "There is something in the way of the beam!" );
      printf( "\r\n");                   // end-of-line.
      alarm(); // sound the alarm
    }
    digitalWrite(LED, LOW); // turn the LED off
    return;
    }
    else
    digitalWrite(LED, LOW);
  */
}
