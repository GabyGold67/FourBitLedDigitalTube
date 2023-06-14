/*
  oneDisplaysExample.ino - Example file to demonstrate TM74HC595LedTube class use with a single display
  Created by Gabriel D. Goldman, May 2, 2023.
  Updated by Gabriel D. Goldman, May 24, 2023.
  Released into the public domain in accordance with "GPL-3.0-or-later" license terms.
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
int testNum{0};
const int firstTest{-5};
const int lastTest{0};
bool testResult{};
const long testTime{1800};
unsigned long timer{millis() - (testTime + 1)};

//Display instance creation
// Creating the instance of the display, the only parameters needed are
// the pins that will be connected to the display module, usually marked as:
// SCLK
// RCLK
// DIO
TM74HC595LedTube myLedDisp(sclk, rclk, dio);

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
    if (testNum == firstTest)
      //Attaching the display refresh to an ISR trough the begin() method
      myLedDisp.begin();

    switch (testNum)
    {
    case -5:
      //print() with a string argument, two characters long, all characters included in the representable characters list
      testResult = myLedDisp.print("On");
      break;
    case -4:
      //print() with a string argument, four characters long, all characters included in the representable characters list
      testResult = myLedDisp.print("Strt");
      break;
    case -3:
      //print() with a string argument, fails to represent as it is 5 chars long (enough to fail), AND has a non-representable char included (!)
      testResult = myLedDisp.print("Hello!");
      break;
    case -2:
      testResult = myLedDisp.print("thiS");
      break;
    case -1:
      testResult = myLedDisp.print("teSt");
      break;
    case 0:
      //print() with a string argument, four characters long AND usable dots, all characters included in the representable characters list
      //Each valid character might be followed by a "." if needed, without being counted as a character, even spaces and special chars
      testResult = myLedDisp.print("I.F.Y.I.");
      break;
    case 1:
      //print() with a floating point argument, one decimal digit argument, ONE decimal digit place to display, no alignment specified
      testResult = myLedDisp.print(2.3, 1);
      break;
    case 2:
      //print() with a floating point argument, one decimal digit argument, TWO decimal digit places to display, no alignment specified
      testResult = myLedDisp.print(2.3, 2);
      break;
    case 3:
      //print() with a floating point argument, one decimal digit argument, TWO decimal digit places to display, right alignment specified
      testResult = myLedDisp.print(2.3, 2, true);
      break;
    case 4:
      //print() with a floating point argument, one decimal digit argument, TWO decimal digit places to display, right alignment specified, zero padded specified
      testResult = myLedDisp.print(2.3, 2, true, true);
      break;
    case 5:
      //print() with a negative floating point argument, one decimal digit argument, TWO decimal digit places to display, no alignment specified
      testResult = myLedDisp.print(-2.3, 2);
      break;
    case 6:
      //print() with a floating point argument, one decimal digit argument, ONE decimal digit place to display, right alignment specified
      testResult = myLedDisp.print(-2.3, 1, true);
      break;
    case 7:
      //print() with a floating point argument, one decimal digit argument, ONE decimal digit place to display, right alignment specified, zero padded specified
      testResult = myLedDisp.print(-2.3, 1, true, true);
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
      testResult = myLedDisp.gauge(1.0, 'b');
      break;
    case 9:
      //gauge() with a floating point argument, 3rd range
      testResult = myLedDisp.gauge(0.74, 'b');
      break;
    case 10:
      //gauge() with an integer argument, 0 <= value <= 3, ranges are:
      // 0: 1st range
      // 1: 2nd range
      // 2: 3rd range
      // 3: 4rd range
      //A character to show ahead of the value is an option, 
      //if not specified will be a blank space, in this case 'b', or any other representable char, for example:
      //b for battery, F for fuel, t for temperature, r for remaining...
      testResult = myLedDisp.gauge(1, 'b');
      break;
    case 11:
      //gauge() with an integer argument, 1st range
      testResult = myLedDisp.gauge(0, 'b');
      break;
    case 12:
      //blink() activates the option to make the present data and any further data printed to de display to blink until noBlink() is invoked, the initial blink rate is set to 500 milliseconds
      //setBlinkRate() modifies the blink rate to the argument -in milliseconds- speed
      myLedDisp.blink();
      testResult = myLedDisp.setBlinkRate(600);
      break;
    case 13:
      // blinking speedup to 300 milliseconds on - same time off sequence
      testResult = myLedDisp.setBlinkRate(300);
      break;
    case 14:
      //more blinking speedup to 150 milliseconds each
      testResult = myLedDisp.setBlinkRate(150);
      break;
    case 15:
      //noBlink() stops the blinking option for the display
      //and use of the limited display capabilities to show a message
      myLedDisp.noBlink();      
      testResult = myLedDisp.print("You");
      break;
    case 16:
      testResult = myLedDisp.print("ran");
      break;
    case 17:
      testResult = myLedDisp.print("out");
      break;
    case 18:
        testResult = myLedDisp.print("oF");
      break;
    case 19:
        testResult = myLedDisp.print("batt.");
      break;
    case 20:
      //gauge() with an integer argument, and without the optional heading character parameter, uses de default SPACE character
      testResult = myLedDisp.gauge(3);
      break;
    case 21:
      //This counts show: negative integers 3 digits to positive numbers 3 digits
      //Alignment: left
      //Zero Padding: No
      for (int i{-150}; i < 151; i++)
      {
        testResult = myLedDisp.print(i);
        delay(20);
      }

      delay(1000);

      //Alignment: right
      //Zero Padding: No
      for (int i{-150}; i < 151; i++)
      {
        testResult = myLedDisp.print(i, true);
        delay(20);
      }

      delay(1000);

      //Alignment: left
      //Zero Padding: Yes (useless as the left alignment doesn't leave space for the extra 0's)
      for (int i{-150}; i < 151; i++)
      {
        testResult = myLedDisp.print(i, false, true);
        delay(20);
      }

      delay(1000);

      //Alignment: right
      //Zero Padding: Yes
      for (int i{150}; i > -151; i--)
      {
        testResult = myLedDisp.print(i, true, true);
        delay(20);
      }
      break;
    case 22:
      //This counts show: positive integers 3 digits to positive integers 4 digits
      //Alignment: left
      //Zero Padding: No
      for (int i{950}; i < 1051; i++)
      {
        testResult = myLedDisp.print(i);
        delay(20);
      }
      
      delay(1000);
      
      //Alignment: right
      //Zero Padding: No
      for (int i{950}; i < 1051; i++)
      {
        testResult = myLedDisp.print(i, true);
        delay(20);
      }
      
      delay(1000);
      
      //Alignment: left
      //Zero Padding: Yes (useless as the left alignment doesn't leave space for the extra 0's)
      for (int i{950}; i < 1051; i++)
      {
        testResult = myLedDisp.print(i, false, true);
        delay(20);
      }
      
      delay(1000);
      
      //Alignment: right
      //Zero Padding: Yes
      for (int i{950}; i < 1051; i++)
      {
        testResult = myLedDisp.print(i, true, true);
        delay(20);
      }
      break;
    case 23:
      //This counts show: positive integers 4 digits to positive integers 5 digits. When the count reaches 10,000 the print() returns false,
      //and an Error message stating the Error and number of test is displayed
      for (int i{9900}; i < 10001; i++)
      {
        testResult = myLedDisp.print(i, true, true);
        delay(20);
      }
      break;
    case 24:
      //This counts show: negative integers 3 digits to negative integers 4 digits. When the count reaches -1,000 the print() returns false,
      //and an Error message stating the Error and number of test is displayed
      for (int i{-900}; i > -1001; i--)
      {
        testResult = myLedDisp.print(i, true, true);
        delay(20);
      }
      break;
    case 25:
      //Use of the degrees symbol (°) by using the * ASCII character
      testResult = myLedDisp.print("36.7*");
      break;
    case 26:
      //Use of the c character to express a value in centigrade degrees
      testResult = myLedDisp.print("36.7c");
      break;
    case 27:
      //Use of the F character to express a value in Fahrenheit degrees
      testResult = myLedDisp.print("98.6F");
      break;
    case 28:
      //An easy way to use the display to show that a process is ongoing or a "Waiting State"
      testResult = myLedDisp.print("-");
      break;
    case 29:
      testResult = myLedDisp.print("--");
      break;
    case 30:
      testResult = myLedDisp.print("---");
      break;
    case 31:
      testResult = myLedDisp.print("----");
      break;
    case 32:
      //Also possible using the dots, here showing the 4 dots lit with independence of other characters
      testResult = myLedDisp.print("....");
      break;
    case 33:
      testResult = myLedDisp.print("bYe");
      break;
    case 34:
      testResult = myLedDisp.print("End");
      break;
    case 35:
      testResult = myLedDisp.print("StOP");
      break;
    case 36:
      testResult = myLedDisp.print("OFF");
      break;
    default:
      //Blanking the display
      myLedDisp.clear();
      //Disattaching the display refresh from the ISR
      myLedDisp.stop();
      testNum = firstTest - 1;
      break;
    }

    if (testResult == false)
      //Use of a combination of characters and an integer converted to a string to display the test that produced an Error.
      myLedDisp.print("Er" + String(testNum));

    if ((lastTest > 0) && (testNum > lastTest))
      testNum = firstTest - 1;
    timer = millis();
  }
}
