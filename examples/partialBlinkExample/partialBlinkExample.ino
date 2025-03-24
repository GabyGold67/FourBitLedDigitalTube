/*
  partialBlinkExample.ino - Example file to demonstrate TM74HC595LedTube class use with a single display
  Created by Gabriel D. Goldman, May 2, 2023.
  Updated by Gabriel D. Goldman, September, 2023.
  Released into the public domain in accordance with "GPL-3.0-or-later" license terms.
  
  WOKWI simulation available at: https://wokwi.com/projects/414799772454823937
*/
#include <Arduino.h>
#include <FourBitLedDigitalTube.h>

// Pin connected to DS of 74HC595 AKA DIO
const uint8_t dio {A3}; // Pin A3 of Arduino Nano
// Pin connected to ST_CP of 74HC595 AKA RCLK
const uint8_t rclk {A4}; // Pin A4 of Arduino Nano
// Pin connected to SH_CP of 74HC595 AKA SCLK
const uint8_t sclk {A5}; // Pin A5 of Arduino Nano

//Set of variables and constants needed just for Demo purposes
bool tstMask[4]{true, true, true, true};
bool testResult{};
const long testTime{3000};

//Display instance creation
TM74HC595LedTube myLedDisp(sclk, rclk, dio);

void setup(){
   myLedDisp.begin();  //Attaching the display refresh to an ISR trough the begin() method
}

void loop()
{
   testResult = myLedDisp.print(3210);
   delay(testTime);

   testResult = myLedDisp.blink();
   delay(testTime);

   tstMask[0] = true;
   tstMask[1] = false;
   tstMask[2] = false;
   tstMask[3] = false;
   myLedDisp.setBlinkMask(tstMask);
   delay(testTime);

   tstMask[0] = false;
   tstMask[1] = true;
   myLedDisp.setBlinkMask(tstMask);
   delay(testTime);

   tstMask[1] = false;
   tstMask[2] = true;
   myLedDisp.setBlinkMask(tstMask);
   delay(testTime);

   tstMask[2] = false;
   tstMask[3] = true;
   myLedDisp.setBlinkMask(tstMask);
   delay(testTime);

   testResult = myLedDisp.noBlink();
   myLedDisp.resetBlinkMask();
   testResult = myLedDisp.print("abcd");
   testResult = myLedDisp.blink();
   delay(testTime);

   tstMask[0] = true;
   tstMask[1] = false;
   tstMask[2] = false;
   tstMask[3] = false;
   myLedDisp.setBlinkMask(tstMask);
   delay(testTime);

   tstMask[1] = true;
   myLedDisp.setBlinkMask(tstMask);
   delay(testTime);

   tstMask[2] = true;
   myLedDisp.setBlinkMask(tstMask);
   delay(testTime);

   tstMask[3] = true;
   myLedDisp.setBlinkMask(tstMask);
   delay(testTime);

   testResult = myLedDisp.noBlink();
   myLedDisp.clear();
   delay(testTime);
}
