/*
  writeExample.ino - Example file to demonstrate TM74HC595LedTube class write() methods
  Created by Gabriel D. Goldman, May 02, 2023.
  Updated by Gabriel D. Goldman, June 04, 2023.
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

//Set of variables and constants needed just for Demo purposes

bool testResultOne{};

// Display instances creation
// Creating an instances of the display, the only parameters needed are
// the pins that will be connected to the display module usually marked as:
// SCLK
// RCLK
// DIO
TM74HC595LedTube myLedDispOne(dsp1Sclk, dsp1Rclk, dsp1Dio);

void setup()
{

}

void loop()
{  
  myLedDispOne.begin();

  //Print a "ruler" indicating the position of each "port"
  testResultOne = myLedDispOne.print(3210);
  delay(3000);

  //Writing the word "burn" character by character in a random way just to show how we can address each
  //display positon without the need of ".print()" the whole display...
  //Put a 'u' in the port #2
  testResultOne = myLedDispOne.write(0xE3, 2);
  delay(3000);

  //Put a 'n' in the port #0
  testResultOne = myLedDispOne.write(0xAB, 0);
  delay(3000);

  //Put a 'b' in the port #3
  testResultOne = myLedDispOne.write(0x83, 3);
  delay(3000);

  //Put a 'r' in the port #1
  testResultOne = myLedDispOne.write(0xAF, 1);
  delay(3000);


  //Now restore the original display one by one using the string overloaded write() method
  testResultOne = myLedDispOne.write("0", 0);
  delay(3000);
  testResultOne = myLedDispOne.write("2", 2);
  delay(3000);
  testResultOne = myLedDispOne.write("1", 1);
  delay(3000);
  testResultOne = myLedDispOne.write("3", 3);
  delay(3000);


  //Stop and disengage the display from the ISR... and this is the end of the loop()
  myLedDispOne.clear();
  myLedDispOne.stop();
  delay(1000);
}