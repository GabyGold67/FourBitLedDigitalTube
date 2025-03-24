/*
  setDigitsOrderExample8bits.ino - 
  Created by Gabriel D. Goldman, May, 2023.
  Updated by Gabriel D. Goldman, October, 2023.
  Released into the public domain in accordance with "GPL-3.0-or-later" license terms.
*/
#include <Arduino.h>
#include <FourBitLedDigitalTube.h>

// Pin connected to DS of 74HC595 AKA DIO
const uint8_t dio8 {A3}; // // Board pin # of Arduino Nano dev Board
// Pin connected to ST_CP of 74HC595 AKA RCLK
const uint8_t rclk8 {A4}; // Board pin # of Arduino Nano dev Board
// Pin connected to SH_CP of 74HC595 AKA SCLK
const uint8_t sclk8 {A5}; // Board pin # of Arduino Nano dev Board

//Set of variables and constants needed just for Demo purposes
bool testResult{false};

//Display instance creation
// Creating the instance of the display, the only parameters needed are
// the pins that will be connected to the display module, usually marked as:
// SCLK
// RCLK
// DIO
TM74HC595LedTube myLedDisp8(sclk8, rclk8, dio8, true, 8);

uint8_t diyMore8Bits[8] {3, 2, 1, 0, 7, 6, 5, 4};
uint8_t standard[8] {0, 1, 2, 3, 4, 5, 6, 7};
bool sortedToggle{false};


void setup(){
// myLedDisp8.setDigitsOrder(diyMore8Bits);  //Start with the digits sorted for the DIY More (R) wiring
myLedDisp8.setDigitsOrder(standard);
myLedDisp8.begin();
Serial.begin(9600);
}

void loop(){
  myLedDisp8.clear();
  delay(500);

  testResult = myLedDisp8.print("0.");
  delay(500);

  testResult = myLedDisp8.print("0.1.");
  delay(500);

  testResult = myLedDisp8.print("0.1.2.");
  delay(500);

  testResult = myLedDisp8.print("0.1.2.3.");
  delay(500);

  testResult = myLedDisp8.print("0.1.2.3.4.");
  delay(500);

  testResult = myLedDisp8.print("0.1.2.3.4.5.");
  delay(500);

  testResult = myLedDisp8.print("0.1.2.3.4.5.6.");
  delay(500);

  testResult = myLedDisp8.print("0.1.2.3.4.5.6.7.");
  delay(500);

  myLedDisp8.clear();
  myLedDisp8.setWaitChar('-');
  myLedDisp8.setWaitRate(250);

  testResult = myLedDisp8.wait();
  delay(4000);
  testResult = myLedDisp8.noWait();

  myLedDisp8.clear();
  myLedDisp8.setWaitChar('.');
  testResult = myLedDisp8.wait(150);
  delay(4000);
  testResult = myLedDisp8.noWait();

  testResult = myLedDisp8.print("reSettin");
  delay(1000);

  sortedToggle = !sortedToggle;
  if(sortedToggle)
    myLedDisp8.setDigitsOrder(diyMore8Bits);  //Sort to the DIY More (R) wiring
  else
    myLedDisp8.setDigitsOrder(standard);  ///Sort to the more usual right to left wiring
}

