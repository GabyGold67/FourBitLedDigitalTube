/*
  waitExample.ino - Example file to demonstrate TM74HC595LedTube class wait() methods
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

//Set of variables and constants needed just for Demo purposes

bool testResult{};

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

//====================================>> First example
  //Print a message telling a "configuration" will take place
  testResult = myLedDispOne.print("JuSt");
  delay(2000);
  testResult = myLedDispOne.print(6, false);
  delay(2000);
  testResult = myLedDispOne.print("SeCS");
  delay(2000);
  testResult = myLedDispOne.print("to");
  delay(2000);
  testResult = myLedDispOne.print("CnFG");
  delay(2000);

  //Setting the wait() method to keep the display alive while configuring
  testResult = myLedDispOne.wait();
  delay(6000);

  //Stop de waiting displayed
  testResult = myLedDispOne.noWait();

//====================================>> Second example
  testResult = myLedDispOne.print("note");
  delay(2000);
  testResult = myLedDispOne.print("tHIS");
  delay(2000);
  testResult = myLedDispOne.print("CASE");
  delay(2000);

  
  //Trying to print while the display is in wait condition makes the message
  //printed to be immediately overwritten. The .wait() method must be stopped
  //to resume the usual display by a .noWait(method)
  testResult = myLedDispOne.wait(600);
  testResult = myLedDispOne.print("cant");
  delay(1000);
  testResult = myLedDispOne.print("Prnt");
  delay(1000);
  testResult = myLedDispOne.print("till");
  delay(1000);
  testResult = myLedDispOne.print("StOP");
  delay(1000);

  //Stop de waiting displayed
  testResult = myLedDispOne.noWait();
  
  //Repeat the .print() executed while waiting...
  testResult = myLedDispOne.print("cant");
  delay(2000);
  testResult = myLedDispOne.print("Prnt");
  delay(2000);
  testResult = myLedDispOne.print("till");
  delay(2000);
  testResult = myLedDispOne.print("StOP");
  delay(3000);

//====================================>> Third example
  //Now normal display by other methods can be resumed
  //Show message by print() to the display
  testResult = myLedDispOne.print("LetS");
  delay(2000);
  testResult = myLedDispOne.print("do");
  delay(2000);
  testResult = myLedDispOne.print("thiS");
  delay(2000);
  testResult = myLedDispOne.print("FStr");
  delay(2000);

  //Setting the wait() method to keep the display alive with a new rate
  testResult = myLedDispOne.wait(100);
  delay(5000);

  //Stop de waiting displayed
  testResult = myLedDispOne.noWait();


//====================================>> Ending examples, make general cleanup and resetting values
  //Set back the waiting rate to the original value
  testResult = myLedDispOne.setWaitRate(250);
  
  testResult = myLedDispOne.print("the");
  delay(2000);
  testResult = myLedDispOne.print("End");
  delay(2000);

  //Stop and disengage the display from the ISR... and this is the end of the loop()
  myLedDispOne.clear();
  myLedDispOne.stop();
  delay(1000);
}