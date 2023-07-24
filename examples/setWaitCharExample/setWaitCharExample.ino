/*
  setWaitCharExample.ino - Example file to demonstrate TM74HC595LedTube class wait() methods
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

bool testResult{};

// Display instances creation
// Creating an instances of the display, the only parameters needed are
// the pins that will be connected to the display module usually marked as:
// SCLK
// RCLK
// DIO
TM74HC595LedTube myLedDispOne(dsp1Sclk, dsp1Rclk, dsp1Dio);

void setup(){

}

void loop(){  
  myLedDispOne.begin();

//====================================>> First example
  //Print a message telling a "configuration" will take place
  testResult = myLedDispOne.print("JuSt");
  delay(1000);
  testResult = myLedDispOne.print(3, false);
  delay(1000);
  testResult = myLedDispOne.print("SeCS");
  delay(1000);
  testResult = myLedDispOne.print("to");
  delay(1000);
  testResult = myLedDispOne.print("CnFG");
  delay(1000);

  //Setting the wait() method to keep the display alive while configuring
  testResult = myLedDispOne.wait(250);
  delay(3000);

  //Stop de waiting displayed
  testResult = myLedDispOne.noWait();

//====================================>> Second example

  //Change de wait character to _
  testResult = myLedDispOne.print("chnG");
  delay(1000);
  testResult = myLedDispOne.print("char");
  delay(1000);
  testResult = myLedDispOne.print("to _");
  delay(1000);
  testResult = myLedDispOne.setWaitChar('_');
  
  testResult = myLedDispOne.wait();
  delay(3000);
  testResult = myLedDispOne.noWait();

//====================================>> Third example
  //Change de wait character to o
  testResult = myLedDispOne.print("chnG");
  delay(1000);
  testResult = myLedDispOne.print("char");
  delay(1000);
  testResult = myLedDispOne.print("to o");
  delay(1000);
  testResult = myLedDispOne.setWaitChar('o');
  
  testResult = myLedDispOne.wait();
  delay(3000);

  //Stop de waiting displayed
  testResult = myLedDispOne.noWait();
  
//====================================>> Fourth example
  //Change de wait character to 8
  testResult = myLedDispOne.print("chnG");
  delay(1000);
  testResult = myLedDispOne.print("char");
  delay(1000);
  testResult = myLedDispOne.print("to 8");
  delay(1000);
  testResult = myLedDispOne.setWaitChar('8');
  
  testResult = myLedDispOne.wait();
  delay(3000);

  //Stop de waiting displayed
  testResult = myLedDispOne.noWait();  

//====================================>> Ending examples, make general cleanup and resetting values
  //Set back the waiting rate to the original value
  testResult = myLedDispOne.setWaitRate(250);
  testResult = myLedDispOne.setWaitChar('-');
  
  testResult = myLedDispOne.print("the");
  delay(2000);
  testResult = myLedDispOne.print("End");
  delay(2000);

  //Stop and disengage the display from the ISR... and this is the end of the loop()
  myLedDispOne.clear();
  myLedDispOne.stop();
  delay(1000);
}