/*
  refreshUseExample.ino - Example file to demonstrate TM74HC595LedTube class uses
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

//Display instance creation
// Creating the instance of the display, the only parameters needed are
// the pins that will be connected to the display module, usually marked as:
// SCLK
// RCLK
// DIO
TM74HC595LedTube myLedDisp(sclk, rclk, dio);

void setup(){
  //myLedDisp.begin();  //This example refreshes the display without the use of a timer interrupt
  testResult = myLedDisp.print("GabY");
}

void loop()
{
  myLedDisp.refresh();
  delay(5);   //This value is just to demonstrate the display tolerates keeping the data visible and have some time before starts to show a ghosting image

}
