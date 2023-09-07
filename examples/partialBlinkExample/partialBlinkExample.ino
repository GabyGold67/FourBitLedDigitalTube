/*
  partialBlinkExample.ino - Example file to demonstrate TM74HC595LedTube class use with a single display
  Created by Gabriel D. Goldman, May 2, 2023.
  Updated by Gabriel D. Goldman, September, 2023.
  Released into the public domain in accordance with "GPL-3.0-or-later" license terms.
*/
#include <Arduino.h>
#include <FourBitLedDigitalTube.h>

// Pin connected to DS of 74HC595 AKA DIO
const uint8_t dio {2}; // Pin A3 of Arduino Nano
// Pin connected to ST_CP of 74HC595 AKA RCLK
const uint8_t rclk {3}; // Pin A4 of Arduino Nano
// Pin connected to SH_CP of 74HC595 AKA SCLK
const uint8_t sclk {4}; // Pin A5 of Arduino Nano

//Set of variables and constants needed just for Demo purposes
bool testResult{};
const long testTime{3000};

//Display instance creation
// Creating the instance of the display, the only parameters needed are
// the pins that will be connected to the display module, usually marked as:
// SCLK
// RCLK
// DIO

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
  myLedDisp.setBlinkMask(true, false, false, false);
  delay(testTime);
  myLedDisp.setBlinkMask(false, true,  false, false);
  delay(testTime);
  myLedDisp.setBlinkMask(false, false, true,  false);
  delay(testTime);
  myLedDisp.setBlinkMask(false, false, false, true);
  delay(testTime);
  testResult = myLedDisp.noBlink();
  myLedDisp.resetBlinkMask();
  testResult = myLedDisp.print("abcd");
  delay(testTime);
  testResult = myLedDisp.blink();
  myLedDisp.setBlinkMask(true, false, false, false);
  delay(testTime);
  myLedDisp.setBlinkMask(true, true, false, false);
  delay(testTime);
  myLedDisp.setBlinkMask(true, true, true, false);
  delay(testTime);
  myLedDisp.setBlinkMask(true, true, true, true);
  delay(testTime);
  testResult = myLedDisp.noBlink();
  myLedDisp.clear();
  delay(testTime);
}
