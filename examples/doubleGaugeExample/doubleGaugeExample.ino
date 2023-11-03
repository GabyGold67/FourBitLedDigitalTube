/*
  doubleGaugeExample.ino - Example file to demonstrate TM74HC595LedTube class doubleGauge() vs gauge() related methods
  Created by Gabriel D. Goldman, May, 2023.
  Updated by Gabriel D. Goldman, August, 2023.
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

  //gauge() with a floating point argument, 0.0 <= value <= 1.0, representing a percentage, the four ranges are:
  // 0 <= 1st range <0.25
  //0.25 <= 2nd range < 0.50
  //0.50 <= 3rd range < 0.75
  //0.75 <= 4rd range <= 1.0
  //A character to show ahead of the value is an option, 
  //if not specified will be a blank space, in this case 'b', or any other representable char, for example:
  //b for battery, F for fuel, t for temperature, r for remaining...
  testResultOne = myLedDispOne.gauge(1.0, 'b');
  delay(2000);

  //Reduce the ammount displayed to 65%
  testResultOne = myLedDispOne.gauge(0.65, 'b');
  delay(2000);

  //Reduce the ammount displayed to 40%
  testResultOne = myLedDispOne.gauge(0.40, 'b');
  delay(2000);

  //Reduce the ammount displayed to 20%
  testResultOne = myLedDispOne.gauge(0.20, 'b');
  delay(2000);

  // Set up a display for a temperature reading, using the gauge() with an integer argument, 0 <= value <= 3,
  //Set to level 0
  testResultOne = myLedDispOne.gauge(0, 't');
  delay(2000);

  //Make the display show a rise in the temperature to level 1
  testResultOne = myLedDispOne.gauge(1, 't');
  delay(2000);
  
  //Make the display show a rise in the temperature to level 2
  testResultOne = myLedDispOne.gauge(2, 't');
  delay(2000);
  
  //Make the display show a rise in the temperature to level 3, and set it to blink to show the high level of temperature
  testResultOne = myLedDispOne.gauge(3, 't');
  // testResultOne = myLedDispOne.blink(500);
  delay(2000);
  
  //doubleGauge() with integer arguments, 0 <= value <= 3:
  //A character to show ahead of each value is an option, 
  //if not specified will be a blank space, in this case 'b', or any other representable char, for example:
  //b for battery, F for fuel, t for temperature, r for remaining...

  testResultOne = myLedDispOne.doubleGauge(0, 3,'b', 't');
  delay(2000);

  testResultOne = myLedDispOne.doubleGauge(1, 2,'b', 't');
  delay(2000);

  testResultOne = myLedDispOne.doubleGauge(2, 1,'b', 't');
  delay(2000);

  testResultOne = myLedDispOne.doubleGauge(3, 0,'b', 't');
  delay(2000);

  testResultOne = myLedDispOne.doubleGauge(0, 3,' ', 't');
  delay(2000);

  testResultOne = myLedDispOne.doubleGauge(1, 2,' ', 't');
  delay(2000);

  testResultOne = myLedDispOne.doubleGauge(2, 1,' ', 't');
  delay(2000);

  testResultOne = myLedDispOne.doubleGauge(3, 0,' ', 't');
  delay(2000);

 //Stop and disengage the display from the ISR... and this is the end of the loop()
  myLedDispOne.clear();
  myLedDispOne.stop();
  delay(1000);
}