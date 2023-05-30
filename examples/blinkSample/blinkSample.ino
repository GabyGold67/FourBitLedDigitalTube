/*
  blinkSample.ino - Example file to demonstrate FourBitLedDigitalTube.h blink related methods
  Created by Gabriel D. Goldman, May 2, 2023.
  Updated by Gabriel D. Goldman, May 24, 2023.
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
const long testTime{4000};

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
  
  //Start the mechanism to keep the display refreshed
  myLedDispOne.begin();

  //print() with a string argument, all characters included in the representable characters list
  //No blinkig
  testResultOne = myLedDispOne.print("Strt");
  delay(2000);  
  testResultOne = myLedDispOne.print("teSt");
  delay(2000);

  //Start blinking, symmetric blink with the default rate (500 ms.)
  testResultOne = myLedDispOne.blink();
  delay(3000);

  //Speed up the symmetric blinking to 350ms.
  testResultOne = myLedDispOne.print("FStr");
  testResultOne = myLedDispOne.setBlinkRate(350);
  delay(3000);
  
  //Speed up the symmetric blinking to 200ms.
  testResultOne = myLedDispOne.setBlinkRate(200);
  delay(3000);
  
  //Speed up the symmetric blinking to 100ms.
  testResultOne = myLedDispOne.setBlinkRate(100);
  delay(3000);

  //Stop blinking
  testResultOne = myLedDispOne.noBlink();
  testResultOne = myLedDispOne.print("See");
  delay(3000);
  
  //Start blinking assymetrically, 400ms. on, 600ms. off
  testResultOne = myLedDispOne.blink(400, 600);
  testResultOne = myLedDispOne.print("ASSY");
  delay(3000);
  
  //Modify blinking assymetrically speed to  300ms. on, 700ms. off
  testResultOne = myLedDispOne.setBlinkRate(300, 700);
  delay(3000);
  
  //Modify blinking assymetrically speed to  200ms. on, 800ms. off
  testResultOne = myLedDispOne.setBlinkRate(200, 800);
  delay(3000);
  
  //Modify blinking assymetrically speed to  100ms. on, 900ms. off
  testResultOne = myLedDispOne.setBlinkRate(100, 900);
  delay(3000);

  //Stop blinking
  testResultOne = myLedDispOne.noBlink();
  testResultOne = myLedDispOne.print("StOP");
  delay(3000);


  //gauge() with a floating point argument, 0 <= value <= 1.0, representing a percentage, the four ranges are:
  // 0 <= 1st range <0.25
  //0.25 <= 2nd range < 0.50
  //0.50 <= 3rd range < 0.75
  //0.75 <= 4rd range <= 1.0
  //A character to show ahead of the value is an option, 
  //if not specified will be a blank space, in this case 'b', or any other representable char, for example:
  //b for battery, F for fuel, t for temperature, r for remaining...
  testResultOne = myLedDispOne.gauge(1.0, 'b');
  delay(3000);
  
  //Start blinking assymetrically, 600ms. on, 400ms. off
  testResultOne = myLedDispOne.blink(600, 400);
  testResultOne = myLedDispOne.gauge(0.74, 'b');
  delay(3000);
  
  //Modify blinking assymetrically speed to  700ms. on, 300ms. off
  testResultOne = myLedDispOne.setBlinkRate(700, 300);
  testResultOne = myLedDispOne.gauge(0.49, 'b');
  delay(3000);
  
  //Modify blinking assymetrically speed to  800ms. on, 200ms. off
  testResultOne = myLedDispOne.setBlinkRate(800, 200);
  testResultOne = myLedDispOne.gauge(0.24, 'b');
  delay(3000);
  
  //Modify blinking assymetrically speed to  900ms. on, 100ms. off
  testResultOne = myLedDispOne.setBlinkRate(900, 100);
  testResultOne = myLedDispOne.gauge(0.0, 'b');
  delay(3000);

  //Ending the test
  //Stop blinking
  testResultOne = myLedDispOne.noBlink();
  testResultOne = myLedDispOne.print("bYe");
  
  //Setting the blink rate to the symmetric original value
  testResultOne = myLedDispOne.setBlinkRate(500);
  delay(000);


}