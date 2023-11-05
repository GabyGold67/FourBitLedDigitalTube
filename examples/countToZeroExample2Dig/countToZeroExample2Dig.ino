/*
  countToZeroExample2Dig.ino - Example file to demonstrate ClickCounter class countToZero() method
  Created by Gabriel D. Goldman, May, 2023.
  Updated by Gabriel D. Goldman, October, 2023.
  Released into the public domain in accordance with "GPL-3.0-or-later" license terms.
*/
#include <Arduino.h>
#include <FourBitLedDigitalTube.h>

//Pin connection for Display
// Pin connected to DS of 74HC595 AKA DIO
const uint8_t dsp1Dio {2}; // Pin A3 of Arduino Nano
// Pin connected to ST_CP of 74HC595 AKA RCLK
const uint8_t dsp1Rclk {3}; // Pin A4 of Arduino Nano
// Pin connected to SH_CP of 74HC595 AKA SCLK
const uint8_t dsp1Sclk {4}; // Pin A5 of Arduino Nano

//Pin connection for a push button/switch to count clicks.
//The other pin of the push button/switch must be connected to GND
const uint8_t mpbClick {6};

//Set of variables and constants needed just for Demo purposes
bool testResult{};
unsigned long int dbncTimer{0}; //Will hold the time the push button has to be held before considering pushed
bool wasPressed {false};  //Records the previous condition of the push button to know when the state changes
const unsigned long int dbncWaitTime {20};  //Time to consider a push button condition changed (debouncing). Empirically to be arround 20 milliseconds
bool pressCounted {false};
int countStart {5};

// Display instances creation
// Creating an instances of the display, the only parameters needed are
// the pins that will be connected to the display module usually marked as:
// SCLK
// RCLK
// DIO

//Click counter object instantiation
ClickCounter myClickCounter(dsp1Sclk, dsp1Rclk, dsp1Dio, true, true, true,2);

void setup()
{
  pinMode(mpbClick, INPUT_PULLUP);  //The button input
  myClickCounter.countBegin(countStart); //Start a Click counter from 0
}

void loop()
{  

  if (digitalRead(mpbClick) == LOW){
    if(wasPressed == false){
      dbncTimer = millis();
      wasPressed = true;
    }
    else{
      if (millis() - dbncTimer >= dbncWaitTime){
        if (pressCounted == false){

          testResult = myClickCounter.countToZero();  //Count to zero, no matter if the current count holds a negative or positive value.
          
          if (testResult == false){
            if(myClickCounter.getCount() == 0){
              // Failed because it reached 0
              countStart = (-1) * (countStart + ((countStart > 0)? 1 : -1));
              testResult = myClickCounter.countRestart(countStart);  //Each time it reaches 0, restarts from 5 more than previous restart and changes sign to show the opposite case
              if(!testResult){
                myClickCounter.clear();
              }
            }
            else{
              //Failed because the current value can't be represented in this display
              myClickCounter.clear();
              
            }
          }

          pressCounted = true;

        }
      }
    }
  }
  else{
    wasPressed = false;
    pressCounted = false;    
  }


}