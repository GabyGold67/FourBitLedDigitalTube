#include <Arduino.h>
#include <FourBitLedDigitalTube.h>

// Pin connected to DS of 74HC595 AKA DIO
const uint8_t dio {A3}; // Pin A3 of Arduino Nano
// Pin connected to ST_CP of 74HC595 AKA RCLK
const uint8_t rclk {A4}; // Pin A4 of Arduino Nano
// Pin connected to SH_CP of 74HC595 AKA SCLK
const uint8_t sclk {A5}; // Pin A5 of Arduino Nano

TM74HC595LedTube myLedDisp(sclk, rclk, dio);

int testNum{0};
const int firstTest{-5};
const int lastTest{0};
bool testResult{};
const long testTime{1800};
unsigned long timer{millis() - (testTime + 1)};

void setup()
{
  testNum = firstTest - 1;
}

void loop()
{
  // A mishmash of tests for showing the library methods provided
  if ((millis() - timer) >= testTime)
  {
    // time to change the test
    testNum++;
    if (testNum == firstTest)
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
      //Each valid character might be followed by a "." if needed, whitout being counted as a character, even spaces and special chars
      testResult = myLedDisp.print("I.F.Y.I.");
      break;
    case 1:
      //print() with a floating point argument, one decimal digit argument, ONE decimal digit place to display, no alignement specified
      testResult = myLedDisp.print(2.3, 1);
      break;
    case 2:
      //print() with a floating point argument, one decimal digit argument, TWO decimal digit place to display, no alignement specified
      testResult = myLedDisp.print(2.3, 2);
      break;
    case 3:
      //print() with a floating point argument, one decimal digit argument, TWO decimal digit place to display, right alignement specified
      testResult = myLedDisp.print(2.3, 2, true);
      break;
    case 4:
      //print() with a floating point argument, one decimal digit argument, TWO decimal digit place to display, right alignement specified, zero padded specified
      testResult = myLedDisp.print(2.3, 2, true, true);
      break;
    case 5:
      //print() with a negative floating point argument, one decimal digit argument, TWO decimal digit place to display, no alignement specified
      testResult = myLedDisp.print(-2.3, 2);
      break;
    case 6:
      //print() with a floating point argument, one decimal digit argument, ONE decimal digit place to display, right alignement specified
      testResult = myLedDisp.print(-2.3, 1, true);
      break;
    case 7:
      //print() with a floating point argument, one decimal digit argument, ONE decimal digit place to display, right alignement specified, zero padded specified
      testResult = myLedDisp.print(-2.3, 1, true, true);
      break;
    case 8:
      //gauge() with a floating point argument, 0 <= value <= 1.0, representing a percentage, ranges are:
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
      //blink() activates the option to make the present data and any further data printed to de display to blink until noBlink() is invoked, the initial blink rate is set to 500 millisecs
      //setBlinkRate() modifies the blink rate to the argument -in milliseconds- argument
      myLedDisp.blink();
      testResult = myLedDisp.setBlinkRate(600);
      break;
    case 13:
      // blinking speedup
      testResult = myLedDisp.setBlinkRate(300);
      break;
    case 14:
      //more blinking speedup
      testResult = myLedDisp.setBlinkRate(150);
      break;
    case 15:
      //noBlink() stops the blinking option for the display
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
      break;
    case 21:
      for (int i{-150}; i < 151; i++)
      {
        testResult = myLedDisp.print(i);
        delay(20);
      }

      delay(1000);

      for (int i{-150}; i < 151; i++)
      {
        testResult = myLedDisp.print(i, true);
        delay(20);
      }

      delay(1000);

      for (int i{-150}; i < 151; i++)
      {
        testResult = myLedDisp.print(i, false, true);
        delay(20);
      }

      delay(1000);

      for (int i{150}; i > -151; i--)
      {
        testResult = myLedDisp.print(i, true, true);
        delay(20);
      }
      break;
    case 22:
      for (int i{950}; i < 1051; i++)
      {
        testResult = myLedDisp.print(i);
        delay(20);
      }
      
      delay(1000);
      
      for (int i{950}; i < 1051; i++)
      {
        testResult = myLedDisp.print(i, true);
        delay(20);
      }
      
      delay(1000);
      
      for (int i{950}; i < 1051; i++)
      {
        testResult = myLedDisp.print(i, false, true);
        delay(20);
      }
      
      delay(1000);
      
      for (int i{950}; i < 1051; i++)
      {
        testResult = myLedDisp.print(i, true, true);
        delay(20);
      }
      break;
    case 23:
      for (int i{9900}; i < 10001; i++)
      {
        testResult = myLedDisp.print(i, true, true);
        delay(20);
      }
      break;
    case 24:
      for (int i{-900}; i > -1001; i--)
      {
        testResult = myLedDisp.print(i, true, true);
        delay(20);
      }
      break;
    case 25:
      testResult = myLedDisp.print("36.7*");
      break;
    case 26:
      testResult = myLedDisp.print("36.7c");
      break;
    case 27:
      testResult = myLedDisp.print("98.6F");
      break;
    case 28:
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
      myLedDisp.clear();
      myLedDisp.stop();
      testNum = firstTest - 1;
      break;
    }

    if (testResult == false)
      myLedDisp.print("Er" + String(testNum));

    if ((lastTest > 0) && (testNum > lastTest))
      testNum = firstTest - 1;
    timer = millis();
  }
}
