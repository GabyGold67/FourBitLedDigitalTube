/*
  twoDisplaysExample.ino - Example file to demonstrate FourBitLedDigitalTube.h use with two displays simultaneously
  Created by Gabriel D. Goldman, May 2, 2023.
  Updated by Gabriel D. Goldman, May 24, 2023.
  Released into the public domain in accordance with "GPL-3.0-or-later" license terms.
*/
#include <Arduino.h>
#include <FourBitLedDigitalTube.h>

//Pin connection for Display #1
// Pin connected to DS of 74HC595 AKA DIO
const uint8_t dsp1Dio {2}; // Pin A3 of Arduino Nano
// Pin connected to ST_CP of 74HC595 AKA RCLK
const uint8_t dsp1Rclk {3}; // Pin A4 of Arduino Nano
// Pin connected to SH_CP of 74HC595 AKA SCLK
const uint8_t dsp1Sclk {4}; // Pin A5 of Arduino Nano

//Pin connection for Display #2
const uint8_t dsp2Dio {A3}; // Pin A3 of Arduino Nano
const uint8_t dsp2Rclk {A4}; // Pin A4 of Arduino Nano
const uint8_t dsp2Sclk {A5}; // Pin A5 of Arduino Nano

//Set of variables and constants needed just for Demo purposes
int testNum{0};
const int firstTest{-5};
const int lastTest{0};
bool testResultOne{};
bool testResultTwo{};
const long testTime{1800};
unsigned long timer{millis() - (testTime + 1)};

// Display instances creation
// Creating two instances of the displays, the only parameters needed are
// the pins that will be connected to the display module usually marked as:
// SCLK
// RCLK
// DIO
TM74HC595LedTube myLedDispOne(dsp1Sclk, dsp1Rclk, dsp1Dio);
TM74HC595LedTube myLedDispTwo(dsp2Sclk, dsp2Rclk, dsp2Dio);

void setup()
{
  testNum = firstTest - 1;
}

void loop()
{
  // A mishmash of tests for showing the library methods provided
  // Some of this tests try to display non supported values, to show the response of the methods.
  // These failed method calls will display "Er" + testNum to help to identify why this message was set.
  
  if ((millis() - timer) >= testTime)
  {
    // time to change the test
    testNum++;
    if (testNum == firstTest){
      //Attaching the display refresh to an ISR trough the begin() method
      myLedDispOne.begin();
      myLedDispTwo.begin();
    }
    switch (testNum)
    {
    case -5:
      //print() with a string argument, composed partially as a result of calling the .getInstanceNbr()
      //that returns a value stating the sequencial order of the display instantiation
      testResultOne = myLedDispOne.print("On " + String(myLedDispOne.getInstanceNbr() + 1));
      testResultTwo = myLedDispTwo.print("On " + String(myLedDispTwo.getInstanceNbr() + 1));
      break;
    case -4:
      //print() with a string argument, all characters included in the representable characters list
      testResultOne = myLedDispOne.print("Strt");
      testResultTwo = myLedDispTwo.print("HeY");
      break;
    case -3:
      //print() with a string argument, fails to represent as it is 5 chars long (enough to fail), AND has a non-representable char included (!)
      testResultOne = myLedDispOne.print("Hello!");
      //while this print() is OK
      testResultTwo = myLedDispTwo.print("Here");
      break;
    case -2:
      testResultOne = myLedDispOne.print("thiS");
      testResultTwo = myLedDispTwo.print("You");
      break;
    case -1:
      testResultOne = myLedDispOne.print("teSt");
      testResultTwo = myLedDispTwo.print("See");
      break;
    case 0:
      //print() with a string argument, four characters long AND usable dots, all characters included in the representable characters list
      //Each valid character might be followed by a "." if needed, without being counted as a character, even spaces and special chars
      testResultOne = myLedDispOne.print("I.F.Y.I.");

      testResultTwo = myLedDispTwo.print("the");
      break;
    case 1:
      //print() with a floating point argument, one decimal digit argument, ONE decimal digit place to display, no alignment specified
      testResultOne = myLedDispOne.print(2.3, 1);
      //print() with a string argument, four characters long AND a dot, all characters included in the representable characters list
      testResultTwo = myLedDispTwo.print("dIFF.");
      break;
    case 2:
      //print() with a floating point argument, one decimal digit argument, TWO decimal digit places to display, no alignment specified
      testResultOne = myLedDispOne.print(2.3, 2);
      //print() with a string argument
      myLedDispTwo.print("OFF");
      break;
    case 3:
      //print() with a floating point argument, one decimal digit argument, TWO decimal digit places to display, right alignment specified
      testResultOne = myLedDispOne.print(2.3, 2, true);
      break;
    case 4:
      //print() with a floating point argument, one decimal digit argument, TWO decimal digit places to display, right alignment specified, zero padded specified
      testResultOne = myLedDispOne.print(2.3, 2, true, true);
      //.clear() one of the displays while keeping the other active
      myLedDispTwo.clear();
      break;
    case 5:
      //print() with a negative floating point argument, one decimal digit argument, TWO decimal digit places to display, no alignment specified
      testResultOne = myLedDispOne.print(-2.3, 2);
      break;
    case 6:
      //print() with a floating point argument, one decimal digit argument, ONE decimal digit place to display, right alignment specified
      testResultOne = myLedDispOne.print(-2.3, 1, true);
      break;
    case 7:
      //print() with a floating point argument, one decimal digit argument, ONE decimal digit place to display, right alignment specified, zero padded specified
      testResultOne = myLedDispOne.print(-2.3, 1, true, true);
      testResultTwo= myLedDispTwo.print("On");
      break;
    case 8:
      //gauge() with a floating point argument, 0 <= value <= 1.0, representing a percentage, the four ranges are:
      // 0 <= 1st range <0.25
      //0.25 <= 2nd range < 0.50
      //0.50 <= 3rd range < 0.75
      //0.75 <= 4rd range <= 1.0
      //A character to show ahead of the value is an option, 
      //if not specified will be a blank space, in this case 'b', or any other representable char, for example:
      //b for battery, F for fuel, t for temperature, r for remaining...
      testResultOne = myLedDispOne.gauge(1.0, 'b');

      //gauge() with an integer argument, 0 <= value <= 3, ranges are:
      // 0: 1st range
      // 1: 2nd range
      // 2: 3rd range
      // 3: 4rd range
      //A character to show ahead of the value is an option, 
      //if not specified will be a blank space, or any other representable char, for example:
      //b for battery, F for fuel, t for temperature, r for remaining...
      //gauge() with an integer argument, 1st range
      testResultTwo = myLedDispTwo.gauge(0);

      break;
    case 9:
      //gauge() with a floating point argument, 3rd range
      testResultOne = myLedDispOne.gauge(0.74, 'b');
      //gauge() with an integer argument, 2nd range
      testResultTwo = myLedDispTwo.gauge(1);
      break;
    case 10:
      testResultOne = myLedDispOne.gauge(1, 'b');
      testResultTwo = myLedDispTwo.gauge(2);
      break;
    case 11:
      //gauge() with an integer argument, 1st range
      testResultOne = myLedDispOne.gauge(0, 'b');
      testResultTwo = myLedDispTwo.gauge(3);
      break;
    case 12:
      //blink() activates the option to make the present data and any further data printed to de display to blink until noBlink() is invoked, the initial blink rate is set to 500 milliseconds
      //setBlinkRate() modifies the blink rate to the argument -in milliseconds- speed
      myLedDispOne.blink();
      testResultOne = myLedDispOne.setBlinkRate(600);
      testResultTwo = myLedDispTwo.gauge(3, 'F');
      break;
    case 13:
      // blinking speedup to 300 milliseconds on - same time off sequence
      testResultOne = myLedDispOne.setBlinkRate(300);
      testResultTwo = myLedDispTwo.gauge(2, 'F');
      break;
    case 14:
      //more blinking speedup to 150 milliseconds each
      testResultOne = myLedDispOne.setBlinkRate(150);
      testResultTwo = myLedDispTwo.gauge(1, 'F');
      break;
    case 15:
      //noBlink() stops the blinking option for the display
      //and use of the limited display capabilities to show a message
      myLedDispOne.noBlink();      
      testResultOne = myLedDispOne.print("You");
      testResultTwo = myLedDispTwo.gauge(0, 'F');
      break;
    case 16:
      testResultOne = myLedDispOne.print("ran");
      break;
    case 17:
      testResultOne = myLedDispOne.print("out");
      testResultTwo = myLedDispTwo.print("out");
      break;
    case 18:
        testResultOne = myLedDispOne.print("oF");
        testResultTwo = myLedDispTwo.print("oF");
      break;
    case 19:
        testResultOne = myLedDispOne.print("batt.");
        testResultTwo = myLedDispTwo.print("FUEL");
      break;
    case 20:
      //gauge() with an integer argument, and without the optional heading character parameter, uses de default SPACE character
      testResultOne = myLedDispOne.print("ouch");
      testResultTwo = myLedDispTwo.print("Good");
      break;
    case 21:
      //This counts show: negative integers 3 digits to positive numbers 3 digits
      //Alignment: left
      //Zero Padding: No

      for (int i{-150}; i < 151; i++)
      {
        testResultOne = myLedDispOne.print(i);
        testResultTwo = myLedDispTwo.print((-1)*i);
        delay(20);
      }

      delay(1000);

      //Alignment: right
      //Zero Padding: No
      for (int i{-150}; i < 151; i++)
      {
        testResultOne = myLedDispOne.print(i, true);
        testResultTwo = myLedDispTwo.print((-2)*i, true);
        delay(20);
      }

      delay(1000);

      //Alignment: left
      //Zero Padding: Yes (useless as the left alignment doesn't leave space for the extra 0's)
      for (int i{-150}; i < 151; i++)
      {
        testResultOne = myLedDispOne.print(i, false, true);
        testResultTwo = myLedDispTwo.print((-3)*i, false, true);
        delay(20);
      }

      delay(1000);

      //Alignment: right
      //Zero Padding: Yes
      for (int i{150}; i > -151; i--)
      {
        testResultOne = myLedDispOne.print(i, true, true);
        testResultTwo = myLedDispTwo.print((-4)*i, true, true);
        delay(20);
      }
      break;
    case 22:
      testResultTwo = myLedDispTwo.print(".");
      //This counts show: positive integers 3 digits to positive integers 4 digits
      //Alignment: left
      //Zero Padding: No
      for (int i{950}; i < 1051; i++)
      {
        testResultOne = myLedDispOne.print(i);
        delay(20);
      }
      
      testResultTwo = myLedDispTwo.print("..");
      delay(1000);
      testResultTwo = myLedDispTwo.print("...");
      
      //Alignment: right
      //Zero Padding: No
      for (int i{950}; i < 1051; i++)
      {
        testResultOne = myLedDispOne.print(i, true);
        delay(20);
      }

      testResultTwo = myLedDispTwo.print("....");
      delay(1000);
      testResultTwo = myLedDispTwo.print("o");
      
      //Alignment: left
      //Zero Padding: Yes (useless as the left alignment doesn't leave space for the extra 0's)
      for (int i{950}; i < 1051; i++)
      {
        testResultOne = myLedDispOne.print(i, false, true);
        delay(20);
      }

      testResultTwo = myLedDispTwo.print("oo");
      delay(1000);
      testResultTwo = myLedDispTwo.print("ooo");
      
      //Alignment: right
      //Zero Padding: Yes
      for (int i{950}; i < 1051; i++)
      {
        testResultOne = myLedDispOne.print(i, true, true);
        delay(20);
      }
      testResultTwo = myLedDispTwo.print("oooo");
      break;
    case 23:
      testResultTwo = myLedDispTwo.print("0");

      //This counts show: positive integers 4 digits to positive integers 5 digits. When the count reaches 10,000 the print() returns false,
      //and an Error message stating the Error and number of test is displayed
      for (int i{9900}; i < 10001; i++)
      {
        testResultOne = myLedDispOne.print(i, true, true);
        delay(20);
      }
      testResultTwo = myLedDispTwo.print("00");
      break;
    case 24:
      testResultTwo = myLedDispTwo.print("000");

      //This counts show: negative integers 3 digits to negative integers 4 digits. When the count reaches -1,000 the print() returns false,
      //and an Error message stating the Error and number of test is displayed
      for (int i{-900}; i > -1001; i--)
      {
        testResultOne = myLedDispOne.print(i, true, true);
        delay(20);
      }
      testResultTwo = myLedDispTwo.print("0000");
      break;
    case 25:
      //Use of the degrees symbol (°) by using the * ASCII character
      testResultOne = myLedDispOne.print("36.7*");
      testResultTwo = myLedDispTwo.print("98.6*");
      break;
    case 26:
      //Use of the c character to express a value in centigrade degrees
      testResultOne = myLedDispOne.print("36.7c");
      testResultTwo = myLedDispTwo.print("98.6F");
      break;
    case 27:
      //Use of the F character to express a value in Fahrenheit degrees
      testResultOne = myLedDispOne.print("25*c");
      testResultTwo = myLedDispTwo.print("77*F");
      break;
    case 28:
      //An easy way to use the display to show that a process is ongoing or a "Waiting State"
      testResultOne = myLedDispOne.print("-");
      break;
    case 29:
      testResultOne = myLedDispOne.print("--");
      break;
    case 30:
      testResultOne = myLedDispOne.print("---");
      break;
    case 31:
      testResultTwo = myLedDispTwo.print("I");
      testResultOne = myLedDispOne.print("----");
      break;
    case 32:
      //Also possible using the dots, here showing the 4 dots lit with independence of other characters
      testResultOne = myLedDispOne.print("Feel");
      testResultTwo = myLedDispTwo.print("bord");
      break;
    case 33:
      testResultOne = myLedDispOne.print("bYe");
      testResultTwo = myLedDispTwo.print("LetS");

      break;
    case 34:
      testResultOne = myLedDispOne.print("End");
      testResultTwo = myLedDispTwo.print("Go");
      break;
    case 35:
      testResultOne = myLedDispOne.print("StOP");
      testResultTwo = myLedDispTwo.print("Once");
      break;
    case 36:
      testResultOne = myLedDispOne.print("OFF");
      testResultTwo = myLedDispTwo.print("aGin");
      break;
    default:
      //Blanking the display
      myLedDispOne.clear();
      myLedDispTwo.clear();
      //Disataching the display refresh from the ISR
      myLedDispOne.stop();
      myLedDispTwo.stop();
      testNum = firstTest - 1;
      break;
    }

    if (testResultOne == false)
      //Use of a combination of characters and an integer converted to a string to display the test that produced an Error.
      myLedDispOne.print("Er" + String(testNum));

    if (testResultTwo == false)
      //Use of a combination of characters and an integer converted to a string to display the test that produced an Error.
      myLedDispTwo.print("Er" + String(testNum));

    if ((lastTest > 0) && (testNum > lastTest))
      testNum = firstTest - 1;
    timer = millis();
  }
}
