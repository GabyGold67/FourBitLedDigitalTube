# **A Seven Segment Led Digital Tube Module display easy to use library**
### (For the ESP32 (ESP-RTOS) Arduino version Library check https://github.com/GabyGold67/SevenSegDisplaysRTOSLib )  
[![arduino-library-badge](https://www.ardu-badge.com/badge/FourBitLedDigitalTube.svg?)](https://www.ardu-badge.com/FourBitLedDigitalTube)  
[![PlatformIO Registry](https://badges.registry.platformio.org/packages/gabygold/library/FourBitLedDigitalTube.svg)](https://registry.platformio.org/libraries/gabygold/FourBitLedDigitalTube) 
![Build with PlatformIO](https://img.shields.io/badge/build%20with-PlatformIO-orange?logo=data%3Aimage%2Fsvg%2Bxml%3Bbase64%2CPHN2ZyB3aWR0aD0iMjUwMCIgaGVpZ2h0PSIyNTAwIiB2aWV3Qm94PSIwIDAgMjU2IDI1NiIgeG1sbnM9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIiBwcmVzZXJ2ZUFzcGVjdFJhdGlvPSJ4TWlkWU1pZCI+PHBhdGggZD0iTTEyOCAwQzkzLjgxIDAgNjEuNjY2IDEzLjMxNCAzNy40OSAzNy40OSAxMy4zMTQgNjEuNjY2IDAgOTMuODEgMCAxMjhjMCAzNC4xOSAxMy4zMTQgNjYuMzM0IDM3LjQ5IDkwLjUxQzYxLjY2NiAyNDIuNjg2IDkzLjgxIDI1NiAxMjggMjU2YzM0LjE5IDAgNjYuMzM0LTEzLjMxNCA5MC41MS0zNy40OUMyNDIuNjg2IDE5NC4zMzQgMjU2IDE2Mi4xOSAyNTYgMTI4YzAtMzQuMTktMTMuMzE0LTY2LjMzNC0zNy40OS05MC41MUMxOTQuMzM0IDEzLjMxNCAxNjIuMTkgMCAxMjggMCIgZmlsbD0iI0ZGN0YwMCIvPjxwYXRoIGQ9Ik0yNDkuMzg2IDEyOGMwIDY3LjA0LTU0LjM0NyAxMjEuMzg2LTEyMS4zODYgMTIxLjM4NkM2MC45NiAyNDkuMzg2IDYuNjEzIDE5NS4wNCA2LjYxMyAxMjggNi42MTMgNjAuOTYgNjAuOTYgNi42MTQgMTI4IDYuNjE0YzY3LjA0IDAgMTIxLjM4NiA1NC4zNDYgMTIxLjM4NiAxMjEuMzg2IiBmaWxsPSIjRkZGIi8+PHBhdGggZD0iTTE2MC44NjkgNzQuMDYybDUuMTQ1LTE4LjUzN2M1LjI2NC0uNDcgOS4zOTItNC44ODYgOS4zOTItMTAuMjczIDAtNS43LTQuNjItMTAuMzItMTAuMzItMTAuMzJzLTEwLjMyIDQuNjItMTAuMzIgMTAuMzJjMCAzLjc1NSAyLjAxMyA3LjAzIDUuMDEgOC44MzdsLTUuMDUgMTguMTk1Yy0xNC40MzctMy42Ny0yNi42MjUtMy4zOS0yNi42MjUtMy4zOWwtMi4yNTggMS4wMXYxNDAuODcybDIuMjU4Ljc1M2MxMy42MTQgMCA3My4xNzctNDEuMTMzIDczLjMyMy04NS4yNyAwLTMxLjYyNC0yMS4wMjMtNDUuODI1LTQwLjU1NS01Mi4xOTd6TTE0Ni41MyAxNjQuOGMtMTEuNjE3LTE4LjU1Ny02LjcwNi02MS43NTEgMjMuNjQzLTY3LjkyNSA4LjMyLTEuMzMzIDE4LjUwOSA0LjEzNCAyMS41MSAxNi4yNzkgNy41ODIgMjUuNzY2LTM3LjAxNSA2MS44NDUtNDUuMTUzIDUxLjY0NnptMTguMjE2LTM5Ljc1MmE5LjM5OSA5LjM5OSAwIDAgMC05LjM5OSA5LjM5OSA5LjM5OSA5LjM5OSAwIDAgMCA5LjQgOS4zOTkgOS4zOTkgOS4zOTkgMCAwIDAgOS4zOTgtOS40IDkuMzk5IDkuMzk5IDAgMCAwLTkuMzk5LTkuMzk4em0yLjgxIDguNjcyYTIuMzc0IDIuMzc0IDAgMSAxIDAtNC43NDkgMi4zNzQgMi4zNzQgMCAwIDEgMCA0Ljc0OXoiIGZpbGw9IiNFNTcyMDAiLz48cGF0aCBkPSJNMTAxLjM3MSA3Mi43MDlsLTUuMDIzLTE4LjkwMWMyLjg3NC0xLjgzMiA0Ljc4Ni01LjA0IDQuNzg2LTguNzAxIDAtNS43LTQuNjItMTAuMzItMTAuMzItMTAuMzItNS42OTkgMC0xMC4zMTkgNC42Mi0xMC4zMTkgMTAuMzIgMCA1LjY4MiA0LjU5MiAxMC4yODkgMTAuMjY3IDEwLjMxN0w5NS44IDc0LjM3OGMtMTkuNjA5IDYuNTEtNDAuODg1IDIwLjc0Mi00MC44ODUgNTEuODguNDM2IDQ1LjAxIDU5LjU3MiA4NS4yNjcgNzMuMTg2IDg1LjI2N1Y2OC44OTJzLTEyLjI1Mi0uMDYyLTI2LjcyOSAzLjgxN3ptMTAuMzk1IDkyLjA5Yy04LjEzOCAxMC4yLTUyLjczNS0yNS44OC00NS4xNTQtNTEuNjQ1IDMuMDAyLTEyLjE0NSAxMy4xOS0xNy42MTIgMjEuNTExLTE2LjI4IDMwLjM1IDYuMTc1IDM1LjI2IDQ5LjM2OSAyMy42NDMgNjcuOTI2em0tMTguODItMzkuNDZhOS4zOTkgOS4zOTkgMCAwIDAtOS4zOTkgOS4zOTggOS4zOTkgOS4zOTkgMCAwIDAgOS40IDkuNCA5LjM5OSA5LjM5OSAwIDAgMCA5LjM5OC05LjQgOS4zOTkgOS4zOTkgMCAwIDAtOS4zOTktOS4zOTl6bS0yLjgxIDguNjcxYTIuMzc0IDIuMzc0IDAgMSAxIDAtNC43NDggMi4zNzQgMi4zNzQgMCAwIDEgMCA0Ljc0OHoiIGZpbGw9IiNGRjdGMDAiLz48L3N2Zz4=)

Developed originally to easily display numeric and text data on the cheap and popular 7-segment led displays or "tubes", from 1 to 8 digits, like the "4-Bits LED Digital Tube Module" (**_and for all the custom made displays as: GIANTS COUNTERS, TIMERS, PRICING DISPLAYS, etc._**) based on two 74HC595 (or similar) shift registers wired to manage the exhibition in a dynamic or animated fashion, the main focus was set on: ease of use, flexibility and basic prevention of 'misrepresentation' errors.

![4-Bits LED Digital Tube Module](https://github.com/GabyGold67/FourBitLedDigitalTube/blob/master/extras/4-BitsLedDigitalTubeModule01.jpg "4-Bits LED Digital Tube Module")

## Ease of use:
_ Instance the class passing just 3 parameters (the 3 pins connected to the display module)  
_ Notify the object and it's ready to go  
_ start ``.print()``ing the data to the display.  
There's no need of even setting the pin modes.  

## Flexibility:
Integers, floating point or strings they'll show as long as the display is capable of doing so in a trustworthy way. If you need to represent a percentage or level of completeness a ``.gauge()`` and a ``.doubleGauge()`` methods are included to represent them in a "Old Motorola brick cell phones' style".

## Trustworthy representation basic checking:
The representation of different data types in this kind of displays is limited, and many implementations of the libraries to drive them take arbitrary or personally biased decisions on how to handle the problem.
The danger of misrepresenting values in the display are usually ignored so when a value can't be faithfully represented by the display, the data is rounded, floored, ceiled, sliced, characters are replaced by others or whatever criteria the developer defined. When trying to display the value __"90153"__ through a 4 digits  module, displaying __"9015"__ is no better (nor worse) than displaying __"0153"__, those are __misrepresentations__. This library returns a boolean value indicating if it was able to display a trustworthy representation of the value, as long as it is able to. If a trustworthy representation was not possible it will return a **false** value and blank the display.  
## Crossplatform:
This kind of displays need to be periodically refreshed, as it can actively turn on only one digit at a time, so to keep all de digits visible the user must activate periodically each digit one by one independently to generate a "cinematic effect". The library takes care of this, and offers two solutions to do so.  
* The first is to attach the refreshing methods to a timer interrupt service (ISR) of the microcontroller.  
* The second is through methods that the user can call from the main code.  

The first mechanism frees the user from the load of calling the refreshing methods periodically, specially considering that long looping times (when executing **`for`**, **`while`** and **`do`** loops included), or the use of **`delay()`** could make the display flicker or simply stop until next refresh. The second option is given in the case that the timer/interrupt library used (see de dependencies information provided as it might be changed in a future) doesn't support the architecture being used by the developer, or too many displays are already attached to the ISR that makes the system unstable. In any case the library is capable of working in any platform, using one way when possible, or the other always.  

Another class is implemented in this library: the _**ClickCounter**_ class, designed as a **subclass** of the TM74HC595 class.  
The _inheritance_ relation between this two classes presented in this library are far from the optimal relation that must have been used, a Dependency might describe better the relation between these classes, but the porpouse of this implementation is to give the user not only the optimal version, but to illustrate some aspects of the inheritance, specially about the access to the attributes of the **superclass** by the **subclass**, in this case limiting the access to the _**`.wait()`**_ method and it's associated attributes as they make no sense in a clickcounter mechanism implemented by this class. If the developer using this library finds out he needs to use the `.wait()` method and the associated methods and attributes feel free to modify it's access.  
Anyway, feel free to change the relation between those two classes at your own will. The change is implemented in the **SevenSegDisplays** library v3.0.0 and up ([text](https://github.com/GabyGold67/SevenSegDisplaysRTOSLib)).  

This library is now in **Maintenance Stage**, no new features are planned, software and documentation bugs will be solved by requests if needed through the **Issues** mechanisms of the Github repository.  

---  
# **Included Methods for TM74HC595LedTube class**

|Method | Parameters|
|---|---|
|**_TM74HC595LedTube_** |uint8_t **sclk**, uint8_t **rclk**, uint8_t **dio**(, bool **commAnode**(, uint8_t **dspDigits**))|
|**begin()**|None|
|**blink()**|None|
||unsigned long **onRate** (,unsigned long **offRate**)|
|**clear()**|None|
|**doubleGauge()**|int **levelLeft**, int **levelRight** (, char **labeLeft**(, char **labelRight**))|
|**fastRefresh()**|None|
|**fastSend()**|uint8_t **segments**, uint8_t **port**|
|**gauge()**|int **level** (, char **label**)|
||double **level** (, char **label**)|
|**getDigitsQty()**|None|
|**getDspValMax()**|None|
|**getDspValMin()**|None|
|**getInstanceNbr()**|None|
|**getMaxBlinkRate()**|None|
|**getMinBlinkRate()**|None|
|**isBlank()**|None|
|**isBlinking()**|None|
|**isWaiting()**|None|
|**noBlink()**|None|
|**noWait()**|None|
|**print()**|String **text**|
||int **value** (, bool **rgtAlgn** (, bool **zeroPad**))|
||double **value** (, unsigned int **decPlaces** (, bool **rgtAlgn** (, bool **zeroPad**)))|
|**refresh()**|None|
|**resetBlinkMask()**|None|
|**send()**|uint8_t **segments**, uint8_t **port**|
|**setBlinkMask()**|bool **blnkPort[]**|
|**setBlinkRate()**|unsigned long **newOnRate**, (unsigned long **newOffRate**)|
|**setDigitsOrder()**|uint8_t* **newOrder**|
|**setWaitChar()**|char **newWaitChar**|
|**setWaitRate()**|unsigned long **newWaitRate**|
|**stop()**|None|
|**wait()**|(unsigned long **waitRate**)|
|**write()**|uint8_t **segments**, uint8_t **port**|
||String **character**, uint8_t **port**|  

---  
## **Methods definition and use description**
---  

### **TM74HC595LedTube**(uint8_t **sclk**, uint8_t **rclk**, uint8_t **dio**, bool **commAnode**, uint8_t **dspDigits**)
### Description:  
Class constructor, create an instance of the class for each display to use. There's no need to configure the pins before calling the method, as the constructor takes care of the task.  
### Parameters:  
**sclk:** uint8_t (unsigned char), passes the pin number that is connected to the sclk pin of the display (the **SH_CP** pin of the shift register if working in a custom display). The pin must be free to be used as a digital output.  
**rclk:** uint8_t (unsigned char), passes the pin number that is connected to the rclk pin of the display (the **ST_CP** pin of the shift register if working in a custom display). The pin must be free to be used as a digital output.  
**dio:** uint8_t (unsigned char), passes the pin number that is connected to the dio pin of the display (the **DS** pin of the shift register if working in a custom display). The pin must be free to be used as a digital output.  
**commAnode:** bool, indicates if the display uses common anode seven segment LED digits (**true** value, default to keep the implementation backwards compatible), or  common cathode kind (**false** value). The use of one kind or the other makes a difference in the fact that one is complementary of the other, meaning a translation must be done on the information sent to the display. Each display instantiated by the class might be independently set up as one kind or the other.  
**dspDigits:** uint8_t (unsigned char), passes the number of digits in the instantiated display, the default value is 4, to keep the implementation backwards compatible.  

### Return value:  
The object created.

### Use example:  
**`TM74HC595LedTube myLedDisp(6, 7, 10);`**  
**`TM74HC595LedTube myLedDisp(6, 7, 10, false);`**  // Create a common cathode display  
**`TM74HC595LedTube myLedDisp(6, 7, 10, true, 8);`**  // Create a common anode, 8 digits display  

---
### **begin**();
### Description:
Attaches the display to a timer interrupt service, which takes care of refreshing the display regularly. Up to four displays (including all classes defined in this library) can be attached to the ISR, at least theoretically, as the refreshing work takes time, and the time taken is proportional to the quantity of displays attached. And as ISRs literally interrupts other tasks done by the microcontroller, the time taken by the ISRs must be kept to minimal or the stability of the whole system will be compromised. As the time available to execute the ISRs without risking the stability of the system depends on various factors, the number of supported displays has to be tested in each development environment at development time. If the stability of the system is compromised then the displays exceeding the number of tolerated units will have to be refreshed by periodically using the **`refresh()`** method.
### Parameters:  
None
### Return value:  
true: If the display could be attached to the ISR, or if the display was already attached to it. This not ensures system stability.  
false: If the display couldn't be attached to the ISR, due to lack of free slots.  
### Use example:  
**`myLedDisp.begin();`**  

---
### **blink**();
### Description:
Makes the display blink the contents it is showing until a **`noBlink()`** method is invoked. The display will continue blinking even if the contents are changed. By default all the digits blink, but each digit might be configured individually to blink or not by using the **`.setBlinkMask()`** method. When invoking the **`.blink()`** method with no parameters the blinking is symmetrical, meaning that the time the display shows the contents and the time the display is blank are equal. The blinking starts at a preset rate the first time the method is invoked. The blinking rate can be changed by using the **`.setBlinkRate()`** method. After changing the blinking rate, the new blinking rate will be kept after a **`.noBlink()`** or new **`.blink()`** without parameters call is done, until it is modified with a new **`.setBlinkRate()`** call, or it is restarted by a **`.blink()`** with parameters. Note that to restart the blinking with a **`.blink()`** the service must first be stopped, as the method call makes no changes if the blinking service was already running.  
### Parameters:  
None
### Return value:  
true: If the display was not already set to blink (so now the blinking was started).  
false: The display was already set to blink.  
### Use example:  
**`myLedDisp.blink();`**

---
### **blink**(unsigned long **onRate**(, unsigned long **offRate**));
### Description:
Makes the display blink the contents it shows until a **`noBlink()`** method is invoked. The blinking is **symmetrical** if only one parameter is passed, **asymmetrical** if two different parameters are passed, meaning that the time the display shows the contents and the time the display is blank will be equal (symmetrical) or not (asymmetrical), depending of those two parameters. The blinking starts at a passed rate when the method is invoked. The blinking rate can be changed by using the **`.setBlinkRate()`** method. The blink rate set will be kept after a **`.noBlink()`** or new **`.blink()`** without parameters call is done, until it is modified with a new **`.setBlinkRate()`** call, or it is restarted by a **`.blink()`** with parameters. Note that to restart the blinking with a **`.blink()`** the service must first be stopped, as the method makes no changes if the blinking service was already running.  
### Parameters:  
**onRate**: unsigned long integer containing the time (in milliseconds) the display must stay on, the value must be in the range _minBlinkRate <= onRate <= _maxBlinkRate. Those preset values might be known by the use of the **`getMinBlinkRate()`** and the **`getMaxBlinkRate()`** methods.  
**offRate**: optional unsigned long integer containing the time (in milliseconds) the display must stay off, the value must be in the range _minBlinkRate <= offRate <= _maxBlinkRate. Those preset values might be known by the use of the **`getMinBlinkRate()`** and the **`getMaxBlinkRate()`** methods. If no offRate value is provided the method will assume it's a symmetric blink call and use a value for offRate equal to the value passed for onRate. 
### Return value:  
true: If the display was not already set to blink (so now the blinking was started).  
false: The display was already set to blink, and/or one or more of the parameters passed were out of range.  
### Use example:  
**`myLedDisp.blink(400);`** //Returns true and sets the blinking rate to 400 millisecs on, 400 millisecs off (symmetrical blink).  
**`myLedDisp.blink(800, 200);`** //Returns true and sets the blinking rate to 800 millisecs on, 200 millisecs off (asymmetrical blink)  
**`myLedDisp.blink(3000);`** //Returns false and the display stays without change.  

---
### **clear**();
### Description:
Clears the display, turning off all the segments and dots.
### Parameters:  
None
### Return value:  
None   
### Use example:  
**`myLedDisp.clear();`**

---
### **doubleGauge**(int **levelLeft**,int **levelRight**(, char **labelLeft**(, char **labelRight**)));
### Description:
Displays a basic graphical representation of the level of fulfillment or completeness of two segmented values or tasks, gives a general fast notion on the matter, as a battery charge level, liquids deposit level, time remaining, tasks completeness and so on. The levels are represented by the horizontal segments (0, 1, 2 or 3 from bottom to top), and a character might be added before each of the graphical representations to give an indication of what the display is showing, passed through the **labelLeft** and **labelRight** parameters. As four 7 segments digit ports wiil be used, this method only applies to displays with 4 to 8 LED digits, the display is splitted in two sectors, the left side and the right side, and each one of them must have a valid value (0 <= value <= 3) to enable to be displayed, and might have (or not) a single character to give a visual hint to what the value is showing. For more information check the **gauge()** method.
### Parameters:  
**levelLeft:** The integer value to display must be in the range 0 <= level <= 3 for the two leftside 7 segments displays.  
**levelRight:** The integer value to display must be in the range 0 <= level <= 3 for the two rightside 7 segments displays.  
**labelLeft:** A char, optional parameter (if not specified the default value, a Space, will be assumed), that will be displayed in the leftmost digit of the display. The character must be one of the "displayable" characters, as listed in the **`.print()`** method description.
**labelRight:** A char, optional parameter (if not specified the default value, a Space, will be assumed), that will be displayed in the position left to the **levelRight** display, just before the levelRight value. The character must be one of the "displayable" characters, as listed in the **`.print()`** method description.
### Return value:  
true: If the values could be represented.  
false: Otherwise, being that the **levelLeft** and/or **levelRight** parameter was out of range and/or the **labelLeft** and/or **labelRight** parameter was not in the list of displayable characters, and the display will be blanked.

### Use example:  
**`myLedDisp.gauge(3, 2);`**  
**`myLedDisp.**gauge(2, 1, 'b', 't');`**  
**`myLedDisp.**gauge(1, 3, 'F');`**
**`myLedDisp.**gauge(4, 2,'d', 'b');`** //Error  
**`myLedDisp.**gauge(3, 0, 'X');`** //Error  

---
### **fastRefresh**();
### Description:
Refreshes the display, **only one digit per call**, the method takes care of registering which digit was redrawn last and move to the next until the last is reached and then restart from the first, and uses direct pin handling instead of using pre-built `shiftOut()` kind of methods. This working criteria has two consequences:
* The method works faster than redrawing all the digits each time and using the call to `shiftOut()` methods, so it is less time consuming and so is the most appropriate to be used within an ISR.
* When used by the developer to refresh the display from the code it must be called more frequently (starting with time needed to refresh each one of all the digits of the display, and then doing those calls periodically) to keep the display's cinematic effect. Failing to do so will be seen as display flickering, or some of the digits displayed more brighter than others.  
### Parameters:  
None
### Return value:  
None   
### Use example:  
**`myLedDisp.fastRefresh();`**

---
### **fastSend**(uint8_t **segments**, uint8_t **port**);
### Description:
Sends one character to the display, using direct pin handling instead of using pre-built `shiftOut()` kind of methods. The parameters indicate which character and to which digit will be sent. This is the method used by fastRefresh() to send the digit when it has to be refreshed. **_Keep in mind_** that sending a character directly to the display has no connection to keep it displayed as it must be resent periodically to keep the cinematic effect. Also the refresh() and fastRefresh() methods will overwrite the character sent, explicitly called or by the ISR service if started by the **`begin()`** method. If the display is being kept by the provided timer (after a `.begin()`), the characters sent by this methods will be overwritten in the next ISR callback.  
### Parameters:  
**segments:** An unsigned short integer value representing which segments to turn on and which off to get the graphic representation of a character in the seven segment display, the corresponding value can be looked up in the **_charLeds[]** array definition in the header file of the library. In the case of a common cathode display the values there listed must be complemented.  
**port:** An unsigned short integer value representing the digit where the character will be sent, being the range of valid values 0 <= port <= dspDigits, the 0 value is the rightmost digit, the 1 value the second from the right and so on.
### Return value:  
None   
### Use example:  
**`myLedDisp.fastSend(0x88, 1);`** // Sends a capital A to the second digit from right to left.

---
### **gauge**(int **level**(, char **label**));
### Description:
Displays a basic graphical representation of the level of fulfillment or completeness of a segmented value or task, gives a general fast notion on the matter, as a battery charge level, liquids deposit level, time remaining, tasks completeness and so on. The levels are represented by the horizontal segments (0, 1, 2 or 3 from bottom to top, and from left to right), and a character might be added before the graphical representation to give an indication of what the display is showing, passed through the **label** parameter. This method is usable in displays which have from 4 and up to 8 digits, and the representation  always makes use of exactly 4 digits.  
### Parameters:  
**level:** The integer value to display must be in the range 0 <= level <= 3.  
**label:** char, optional parameter (if not specified the default value, a Space, will be assumed), that will be displayed in the leftmost digit of the display. The character must be one of the "displayable" characters, as listed in the **`.print()`** method description.
### Return value:  
true: If the value could be represented.  
false: Otherwise, being that the **level** parameter was out of range and/or the **label** parameter was not in the list of displayable characters, and the display will be blanked.

### Use example:  
**`myLedDisp.gauge(3);`**  
**`myLedDisp.**gauge(2, 'b');`**  
**`myLedDisp.**gauge(1, 'F');`**
**`myLedDisp.**gauge(4, 'd');`** //Error  
**`myLedDisp.**gauge(3, 'X');`** //Error  

---
### **gauge**(double **level**(, char **label**));
### Description:
Displays a basic graphical representation of the level of fulfillment or completeness of a segmented value or task, gives a general fast notion on the matter, as a battery charge level, liquids deposit level, time remaining, tasks completeness and so on. The levels are represented by the horizontal segments (0, 1, 2 or 3 from bottom to top, and from left to right), and a character might be added before the graphical representation to give an indication of what the display is showing, passed through the **label** parameter. 
### Parameters:  
**level:** The double value to display must be in the range 0.0 <= level <= 1.0, being the range the representation of the percentage of the 'full' level, so that the ranges are:  
0.0 <= level < 0.25 for the first level,  
0.25 <= level < 0.50 for the second level,  
0.50 <= level < 0.75 for the third level, and  
0.75 <= level <= 1.00 for the fourth and upper level.  
**label:** char, optional parameter (if not specified the default value, a Space, will be assumed), that will be displayed in the leftmost digit of the display. The character must be one of the "displayable" characters, as listed in the **`.print()`** method description.
### Return value:  
true: If the value could be represented.  
false: Otherwise, being that the **level** parameter was out of range and/or the **label** parameter was not in the list of displayable characters, and the display will be blanked.

### Use example:  
**`myLedDisp.gauge(0.0);`**  
**`myLedDisp.gauge(0.4);`**  
**`myLedDisp.gauge(0.55, 'b');`**  
**`myLedDisp.gauge(1.0, 'F');`**  
**`myLedDisp.gauge(1.5, 'd');`** //Error  
**`myLedDisp.gauge(3.0, 'X');`** //Error  

---
### **getDigitsQty**();
### Description:
Returns an unsigned short integer value indicating the the quantity of digits, or ports, the display have as indicated at the object instantiation. Each time the class is instantiated the object is created with the needed resources and the range of values are calculated based on the dspDigits parameter, and that value is the returned by this method.  
### Parameters:  
**None**  
### Return value:  
The unsigned short number indicating the quantity of digits of the instantiated display.  
### Use example:  
**`myLedDisp.getDigistsQty();`**

---
### **getInstanceNbr**();
### Description:
Returns an unsigned short integer value indicating the instantiation number it was given to the object. Each time the class is instantiated the created object receives a serial instantiation number that can be used in order to identify each object in case of need.
### Parameters:  
**None**  
### Return value:  
The unsigned short number indicating the identification Instance Number.  
### Use example:  
**`myLedDisp.getInstanceNbr();`**

---
### **getMaxBlinkRate**();
### Description:
Returns the maximum time the display can be configured to blink, helps keeping the blinkRate setters inside the accepted range. The main concept behind this value is to keep the rythm at wich the display turns on and off as part of the information that it provides, and doesn't make it look like a display failure or any other kind of bug.  
### Parameters:  
**None**  
### Return value:  
unsigned long integer: The maximum time, in milliseconds, the display can be set to blink. This value is the maximum to set as the turned-on or the turned-off stage of the blinking process started by a **`.blink()`** method.  
### Use example:  
**`myLedDisp.getMaxBlinkRate();`**

---
### **getMinBlinkRate**();
### Description:
Returns the minimum time the display can be configured to blink, helps keeping the BlinkRate setters inside the accepted range.The main concept behind this value is to keep the rythm at wich the display turns on and off as part of the information that it provides, and doesn't make it look like a display failure or any other kind of bug.  
### Parameters:  
**None**  
### Return value:  
unsigned long integer: The minimum time, in milliseconds, the display can be set to blink. This value is the minimum to set as the turned-on or the turned-off stage of the blinking process started by a **`.blink()`** method.  
### Use example:  
**`myLedDisp.getMinBlinkRate();`**

---
### **isBlank**();
### Description:
Returns a boolean value indicating if the display is blank or not. The condition to be blank is that all the display ports are exhibiting the _space character, not to be confused with '\0'.  
### Parameters:  
**None**  
### Return value:  
true: All the display ports hold a _space value.    
false: One or more of the display ports hold a value different to _space value.  
### Use example:  
**`myLedDisp.isBlank();`**

---
### **isBlinking**();
### Description:
Returns a boolean value indicating if the display is set to blink or not.
### Parameters:  
**None**  
### Return value:  
true: If the display is set to blink.  
false: If the display is set not to blink.   
### Use example:  
**`myLedDisp.isBlinking();`**

---
### **isWaiting**();
### Description:
Returns a boolean value indicating if the display is set to wait or not. This might be useful as the display is unavailable to other **`.print()`**, **`write()`**, **`gauge()`**, etc. methods while its on "waiting" mode.
### Parameters:  
**None**  
### Return value:  
true: If the display is set to wait.  
false: If the display is set not to wait.   
### Use example:  
**`myLedDisp.isWaiting();`**

---
### **noBlink**();
### Description:
Stops the display blinking, if it was doing so, leaving the display turned on.
### Parameters:  
**None**  
### Return value:  
true: If the display was set to blink, and the blinking is stopped.   
false: If the display was not set to blink, no changes will be done.
### Use example:  
**`myLedDisp.noBlink();`**

---
### **noWait**();
### Description:
Stops the waiting in process display, if it was doing so, leaving the display turned on, blanked.
### Parameters:  
**None**  
### Return value:  
true: If the display was set to wait, and the waiting is stopped.   
false: If the display was not set to wait, no changes will be done.
### Use example:  
**`myLedDisp.noWait();`**

---
### **print**(String **text**);
### Description:
Displays the string text if it contains all "displayable" characters, which are the ones included in the following list: **0123456789AabCcdEeFGHhIiJLlnOoPqrStUuY-_.** and the **space**.  
There are other 3 characters that can be represented in the display, but the conversion from a character to use while programming is "host language setting dependant", so those where assigned to available ASCII non displayable characters of easy access in any keyboard layout in most languages, they can be used as part of the text string to display, and they are:  
* **=** Builds a character formed by lighting the lower 2 horizontal segments of the digit display, can be described as a "lower equal" symbol.  
* **~** Builds a character formed by lighting the 3 horizontal segments of the digit display, can be described as an "equivalent" symbol.  
* **'*'** (asterisk) Builds a character by lighting the upper 4 segments, forming a little square, can be described as the "degrees" symbol or º.  
### Parameters:  
**text:** String, up to **dspDigits** displayable characters long PLUS usable dots, all characters included in the representable characters list. Each valid character might be followed by a "." if needed, without being counted as a character, even spaces and special chars. If two or more consecutive dots are passed, an intermediate space is considered to be included between each pair of them, and that space counts as one of the available characters to display.  
### Return value:  
true: If the text could be represented.  
false: Otherwise, and the display will be blanked.

### Use example:  
**`myLedDisp.print("Hi");`** //Valid for 2 or more digits displays  
**`myLedDisp.print("Strt");`** //Valid for 4 or more digits displays  
**`myLedDisp.print("L.O.L.");`**  //Valid for 3 or more digits displays  
**`myLedDisp.print("36.70*");`** //Valid for 5 or more digits displays  
**`myLedDisp.print("........");`**  //Valid for 8 digits displays

---
### **print**(int **value**(, bool **rgtAlgn**(, bool **zeroPad**)));
### Description:
Displays an integer value as long as the length representation fits the available space of the display.
### Parameters:  
**value:** The integer value to display which must be in the range (-1)*(pow(10, (dspDigits - 1)) - 1) <= value <= (pow(10, dspDigits) - 1).  
**rgtAlgn:** Boolean, optional parameter (if not specified the default value, false, will be assumed), indicates if the represented value must be displayed right aligned, with the missing heading characters being completed with spaces or zeros, depending in the zeroPad optional parameter. When a negative value is displayed and it's less than (dspDigits - 1) digits long, a right aligned display will keep the '-' sign in the leftmost position, and the free space to the leftmost digit will be filled with spaces or zeros, depending in the zeroPad optional parameter.  
**zeroPad:** Boolean, optional parameter (if not specified the default value, false, will be assumed), indicates if the heading free spaces of the integer right aligned displayed must be filled with zeros (true) or spaces (false). In the case of a negative integer the spaces or zeros will fill the gap between the '-' sign kept in the leftmost position, and the first digit.  
### Return value:  
true: If the value could be represented.  
false: Otherwise, and the display will be blanked.

### Use example:  
**`myLedDisp.print(12);`** //Displays '**``12  ``**' on a 4 digits display  
**`myLedDisp.print(12, true);`** //Displays '**``  12``**' on a 4 digits display  
**`myLedDisp.print(12, true, true);`** //Displays '**``0012``**' on a 4 digits display  
**`myLedDisp.print(-12);`** //Displays '**``-12     ``**' on a 8 digits display  
**`myLedDisp.print(-12, true);`** //Displays '**``-   12``**' on a 6 digits display  
**`myLedDisp.print(-12, true, true);`** //Displays '**``-012``**' on a 4 digits display    

---
### **print**(double **value**, unsigned int **decPlaces**(, bool **rgtAlgn**(, bool **zeroPad**)));
### Description:
Displays a floating point value as long as the length representation fits the available space of the display. If the integer part of value is not in the displayable range or if the sum of the spaces needed by the integer part plus the indicated decimal places to display is greater than the available digits space, the **`print()`** will fail, returning a false value and clearing the display.
### Parameters:  
**value:** The floating point value which must be in the range ((-1)*(pow(10, ((dspDigits - decPlaces) - 1)) - 1)) <= value <= (pow(10, (dspDigits - decPlaces)) - 1).  
**decPlaces:** Decimal places to be displayed after the decimal point, ranging 0 <= decPlaces <= dspDigits, selecting 0 value will display the number as an integer, with no '.' displayed. In any case the only modification that will be applied if value has a decimal part longer than the decPlaces number of digits is **truncation**, if any other rounding criteria is desired the developer must apply it to **value** before calling this method.
**rgtAlgn:** Boolean, optional parameter (if not specified the default value, false, will be assumed), indicates if the represented value must be displayed right aligned, with the missing heading characters being completed with spaces or zeros, depending in the zeroPad optional parameter. When a negative value is displayed and it's less than (dspDigits - 1) digits long, a right aligned display will keep the '-' sign in the leftmost position, and the free space to the leftmost digit will be filled with spaces or zeros, depending in the zeroPad optional parameter.  
**zeroPad:** Boolean, optional parameter (if not specified the default value, false, will be assumed), indicates if the heading free spaces of the value right aligned displayed must be filled with zeros (true) or spaces (false). In the case of a negative value the spaces or zeros will fill the gap between the '-' sign kept in the leftmost position, and the first digit.  
### Return value:  
true: If the value could be represented.  
false: Otherwise, and the display will be blanked.
### Use example (on a 4-bits display):  
**`myLedDisp.print(1.2, 2);`** //Displays '**``1.20 ``**'  
**`myLedDisp.print(1.2, 2, true);`** //Displays '**`` 1.20``**'  
**`myLedDisp.print(12, 2, true, true);`** //Displays '**``01.20``**'    
**`myLedDisp.print(-1.2, 2);`** //Displays '**``-1.20``**'  
**`myLedDisp.print(-1.28, 1, true);`** //Displays '**``- 1.2``**'  
**`myLedDisp.print(-1.28, 1, true, true);`** //Displays '**``-01.2``**'    
**`myLedDisp.print(-1.28, 3, true, true);`** //Error

---
### **refresh**();
### Description:
Refreshes the display, **all available digits per call**, the method takes care of registering which digit was redrawn first and each call starts from the next until the last is reached and then restart from the first, to minimize ghosting and keep all the digits brightness even, and uses pre-built **`shiftOut()`** kind of methods. This working criteria has two consequences:
* The method works slower than the **`fastRefresh()`**, so it will take more time to execute.  
* When used by the developer to refresh the display from the code it will avoid ghosting or blinking effects being called less frequently to keep the display's cinematic effect.  
### Parameters:  
**None**  
### Return value:  
**None**   
### Use example:  
**`myLedDisp.refresh();`**  

---
### **resetBlinkMask**();
### Description:
Resets the blinking mask that configures which digits of the display will be affected by the **`.blink()`** method, so that all the digits will be affected when blinking is active.  
### Parameters:  
None
### Return value:  
None   
### Use example:  
**`myLedDisp.resetBlinkMask();`**

---
### **send**(uint8_t **segments**, uint8_t **port**);
### Description:
Sends one character to the display, using pre-built `shiftOut()` kind of methods, which takes unknown time to complete depending on the  implementation of the framework used to develop. The parameters indicate which character and to which digit will be sent. This is the method used by refresh() to send the digit when it has to be refreshed. **_Keep in mind_** that sending a character directly to the display has no connection to keep it displayed as it must be resent periodically to keep the cinematic effect. Also the refresh() and fastRefresh() methods will overwrite the character sent, explicitly called or by the ISR service if started by the **`begin()`** method.
### Parameters:  
**segments:** An unsigned short integer value representing which segments to turn on and which off to get the graphic representation of a character in the seven segment display, the corresponding value can be looked up in the **_charLeds[]** array definition in the header file of the library. Any other uint8_t (char or unsigned short int are equivalent terms here) value is admissible, but the displayed result might not be easily recognized as a known ASCII character.  In the case of a common cathode display the values there listed must be complemented to calculate the value to send.    
**port:** An unsigned short integer value representing the digit where the character will be sent, being the range of valid values 0 <= port <= (dspDigits-1), the 0 value is the rightmost digit, the 1 value the second from the right and so on.
### Return value:  
None   
### Use example:  
**`myLedDisp.send(0x91, 2);`** // Sends a Y to the third digit from right to left.

---
### **setBlinkMask**(bool **blnkPort[]**);
### Description:
Changes the blinking mask that indicates which digits will be involved after a **`blink()`** method is invoked. Indicating true for a digit makes it blink when the method is called, indicating false makes it display steady independently of the others. The parameter is positional referenced to the display, and for ease of use the index numbers of the array indicate their position relative to the rightmost digit (blnkPort0). The mask might be reset to its original value (all digits set to blink) by using this method with all parameters set to **true** or by using the **`.resetBlinkMask()`** method.  

### Parameters:  
**blnkPort[]**: array of booleans of length **dspDigits**, indexes are positional referenced to the display, indicating each one which digits must blink after a **`blink()`** method is invoked (true) or stay steady (false). The indexes valid range is 0 <= index <= (dspDigits-1), corresponding the [0] position withe the rightmost display port, the [1] position the second from the right and so on.  
### Return value:  
None.  
### Use example:  
**`bool tstMask[4]{true, true, true, true};`**  
**`testResult = myLedDisp.blink();`**  //Sets all the  digits to blink.  
**`tstMask[0] = true;`**  
**`tstMask[1] = false;`**  
**`tstMask[2] = false;`**  
**`tstMask[3] = false;`**  
**`myLedDisp.setBlinkMask(tstMask);`**  //Sets only the rightmost digit to blink.  
**`tstMask[0] = false;`**  
**`tstMask[1] = true;`**  
**`tstMask[2] = true;`**  
**`myLedDisp.setBlinkMask(tstMask);`**    //Sets the two central digits to blink.

---
### **setBlinkRate**(unsigned long **onRate**(,unsigned long **offRate**));
### Description:
Changes the time parameters to use for the display blinking the contents it shows. The parameters change will take immediate effect, either if the display is already blinking or not, in the latter case the parameters will be the ones used when a **`blink()`** method is called without parameters. The blinking will be **symmetrical** if only one parameter is passed, **asymmetrical** if two different parameters are passed, meaning that the time the display shows the contents and the time the display is blank will be equal (symmetrical) or not (asymmetrical), depending of those two parameters. The blink rate set will be kept after a **`.noBlink()`** or new **`.blink()`** without parameters call is done, until it is modified with a new **`.setBlinkRate()`** call, or it is restarted by a **`.blink()`** with parameters. Note that to restart the blinking with a **`.blink()`** the service must first be stopped, as the method makes no changes if the blinking service was already running.  
### Parameters:  
**onRate**: unsigned long integer containing the time (in milliseconds) the display must stay on, the value must be in the range _minBlinkRate <= onRate <= _maxBlinkRate. Those built-in values might be known by the use of the **`getMinBlinkRate()`** and the **`getMaxBlinkRate()`** methods.  
**offRate**: optional unsigned long integer containing the time (in milliseconds) the display must stay off, the value must be in the range _minBlinkRate <= offRate <= _maxBlinkRate. Those built-in values might be known by the use of the **`getMinBlinkRate()`** and the **`getMaxBlinkRate()`** methods. If no offRate value is provided the method will assume it's a symmetric blink call and use a value of offRate equal to the value passed by onRate.  
### Return value:  
true: If the parameter or parameters passed are whiting the valid range, and the change will take effect immediately.
false: One or more of the parameters passed were out of range. The rate change would not be made for none of the parameters.  
### Use example:  
**`myLedDisp.setBlinkRate(400);`** //Returns true and sets the blinking rate to 400 millisecs on, 400 millisecs off (symmetrical blink).  
**`myLedDisp.setBlinkRate(800, 200);`** //Returns true and sets the blinking rate to 800 millisecs on, 200 millisecs off (asymmetrical blink)  
**`myLedDisp.setBlinkRate(3000);`** //Returns false and the display blinking rate stays without change.  
**`myLedDisp.setBlinkRate(600, 3500);`** //Returns false and the display blinking rate stays without change.  

---
### **setDigitsOrder**(uint8_t* **newOrderPtr**);
### Description:
As different 7 segments dynamic displays based on two 74HC595 are differently wired, some implement the leftmost display port as the LSb of the shift register driving the port selection, some implement it as the MSb. When more than one display modules are used it adds a new level of hardware implementation that differs from one supplier to the other. The library implements a mechanism to provide the instantiated object to relate the positions of the display ports to the bits of the selection byte through an array. The array has the size of the display instantiated, and each array elment is meant to hold the number of the bit that selects the corresponding port, being the first element of the array (array[0]) the corresponding to the leftmost display digit, array[1], the next to it's right and so on. The array is default defined in the constructor as (0, 1, 2,...) that is the most usual implementation found. If the order needs to be changed the `.setDigitsOrder()` method is the way to set a new mapping.
### Parameters:  
**newOrderPtr**: pointer to an uint8_t array of **_dspDigits** lenght containing the position of the bit corresponding to each display port. Each value will be checked against the _dspDigits value to ensure that they are all in the range acceptable, 0 <= value <= _dspDigits - 1. If one of the values is out of the valid range no change will be done. Please note that no checking will be done to ensure all of the array values are different. A repeated value will be accepted.  
### Return value:  
true: All of the elements of the array were in the accepted range. The change was performed  
false: One or more of the parameters passed were out of range. The change wasn't performed.  
### Use example:
**`uint8_t diyMore8Bits[8] {3, 2, 1, 0, 7, 6, 5, 4};`** //Builds an array with the port order of the "DIY MORE 8-bit LED Display".  
**`myLedDisp.setDigitsOrder(diyMore8Bits);`** //Changes the display bit to port mapping according to the display characteristics.  

---
### **setWaitChar**(char **newWaitChar**);
### Description:
Changes the the character to use for the display to show the "progress bar advancement". The parameters change will take immediate effect, either if the display is already in wait mode or not. The new character will be changed for further calls of the method until a new setWaitChar is invoked with a valid argument.  
### Parameters:  
**newWaitChar**: a character the display must use for symbolizing the progress, the value must be in the displayable characters group as explained in the print() method.  
### Return value:  
true: If the character passed is whitin the displayable characters range, and the change will take effect immediately.
false: The parameter passed was invalid, i.e. it was a non displayable character. In this case the character change will not be made.  
### Use example:  
**`myLedDisp.setWaitRate('_');`** //Returns true and sets the wait character to '_'.  
**`myLedDisp.setWaitRate('#');`** //Error, returns false and the display wait character stays without change.  

---
### **setWaitRate**(unsigned long **newWaitRate**);
### Description:
Changes the time parameter to use for the display to show the "progress bar advancement". The parameters change will take immediate effect, either if the display is already in wait mode or not, in the latter case the parameter will be the one used when a **`wait()`** method is called without parameters. The wait rate set will be kept after a **`.noWait()`** or new **`.wait()`** without parameters call is done, until it is modified with a new **`.setWaitRate()`** call, or it is restarted by a **`.wait()`** with parameters. Note that to restart the waiting with a **`.wait()`** the service must first be stopped, as the method makes no changes if the waiting service was already running.  
### Parameters:  
**newWaitRate**: unsigned long integer containing the time (in milliseconds) the display must take to advance the next character symbolizing the progress, the value must be in the range _minBlinkRate <= newWaitRate <= _maxBlinkRate. Those values might be known by the use of the **`getMinBlinkRate()`** and the **`getMaxBlinkRate()`** methods.  
### Return value:  
true: If the parameter passed is whitin the valid range, and the change takes effect.
false: The parameter passed was out of range. In this case the rate change would not be made.  
### Use example:  
**`myLedDisp.setWaitRate(400);`** //Returns true and sets the advancement rate to 400 millisecs.  
**`myLedDisp.setWaitRate(3000);`** //Returns false and the display wait rate stays without change.  

---
### **stop**();
### Description:
Detaches the display from the timer interrupt service which takes care of refreshing the display regularly (if it was attached to it, if the display wasn't attached to the ISR no modification is made). The method then checks the array (list) of active serviced displays, if none is left in that array, the timer service is stopped, the interrupt used by it is released, and the array is deleted from the heap to free the allocated resources. This last actions are reversed when a new begin() method is executed in any display.  
### Parameters:  
**None**  
### Return value:  
true: The instance of the display was found and detached from the ISR.  
false: The instance of the display wasn't found attached to the ISR, no detach was carried as it wasn't needed.  
### Use example:  
**`myLedDisp.stop();`**  

---

### **wait**(unsigned long **newWaitRate**);
### Description:
Makes the display show an "simple animated progress bar" until a **`noWait()`** method is invoked. The speed rate for the progress animation starts at a passed rate when the method is invoked, or the last speed set will be used, having a preset value for the first time it's invoked if no parameter is passed. The animation rate can be changed by using the **`.setWaitRate()`** method. The speed rate set will be kept after a **`.noWait()`** or new **`.wait()`** without parameters call is done, until it is modified with a new **`.setWaitRate()`** call, or it is restarted by a **`.wait()`** with a parameter. Note that to restart the waiting with a **`.wait()`** the service must first be stopped, as the method makes no changes if the waiting service was already running.  
### Parameters:  
**newWaitRate**: Optional unsigned long integer containing the time (in milliseconds) the display must stay in the same advancement representation before moving on to the next, the value must be in the range _minBlinkRate <= newWaitRate <= _maxBlinkRate. Those values might be known by the use of the **`getMinBlinkRate()`** and the **`getMaxBlinkRate()`** methods.  
### Return value:  
true: If the display was not already set to wait (so now the waiting was started).  
false: The display was already set to wait, and/or the parameter passed was out of range.  
### Use example:  
**`myLedDisp.wait();`** //Returns true and shows advancement animation to the already set value.  
**`myLedDisp.wait(800);`** //Returns true and sets the advancement animation rate to 800 millisecs.  
**`myLedDisp.wait(getMaxBlinkRate() + 10);`** //Returns false and the display stays without change.  

---
### **write**(uint8_t **segments**, uint8_t **port**);
### Description:
Prints one character to the display, at a desired position, without affecting the rest of the characters displayed.
### Parameters:  
**segments:** An unsigned short integer value representing which segments to turn on and which off to get the graphic representation of a character in the seven segment display, the corresponding value can be looked up in the **_charLeds[]** array definition in the header file of the library. In the case of a common cathode display the values there listed must be complemented. Any other uint8_t (char or unsigned short int is the same here) value is admissible, but the displayed result might not be easily recognized as a known ASCII character.  
**port:** An unsigned short integer value representing the digit where the character will be sent, being the range of valid values 0 <= port <= (dspDigits - 1), the 0 value is the rightmost digit, the 1 value the second from the right and so on.
### Return value:  
true: If the parameters are within the acceptable range, in this case 0 <= port <= (dspDigits - 1).  
false: The port value was outside the acceptable range.  
### Use example:  
**`myLedDisp.write(0xA4, 1);`** // Modifies the displayed data, placing a '2' in the second digit from right to left in a common anode display.

---

### **write**(String **character**, uint8_t **port**);
### Description:
Prints one character to the display, at a desired position, without affecting the rest of the characters displayed.
### Parameters:  
**character:** A single character string that must be displayable, as defined in the **`.print()`** method.  
**port:** An unsigned short integer value representing the digit where the character will be sent, being the range of valid values 0 <= port <= (dspDigits - 1), the 0 value is the rightmost digit, the 1 value the second from the right and so on.
### Return value:  
true: If **character** is a displayable one char string, and **port** value is in the range 0 <= value <= (dspDigits - 1).  
false: The **character** was not "displayable" or the **port** value was out of range.  

### Use example:  
**`myLedDisp.write("J", 1);`** // Modifies the displayed data, placing a 'J' in the second digit from right to left.  

# **Included Methods for ClickCounter class**  

|Method | Parameters|
|---|---|
|**_ClickCounter_** |uint8_t **sclk**, uint8_t **rclk**, uint8_t **dio**(, bool **rgthAlgn**(, bool **zeroPad**(, bool **commAnode**(, uint8_t **dspDigits**))))|
|**blink()**|None|
||unsigned long **onRate** (,unsigned long **offRate**)|
|**countBegin()**|(int **startVal**)|
|**countDown()**|(int **qty**)|
|**countReset()**|None|
|**countRestart()**|(int **restartValue**)|
|**countStop()**|None|
|**countToZero()**|(int **qty**)|
|**countUp()**|(int **qty**)|
|**getCount()**|None|
|**getStartVal()**|None|
|**noBlink()**|None|
|**setBlinkRate()**|unsigned long **newOnRate**, (unsigned long **newOffRate**)|
|**updDisplay()**|None|

## **Methods definition and use description**

---
### **ClickCounter**(uint8_t **sclk**, uint8_t **rclk**, uint8_t **dio**, bool **rgthAlgn**, bool **zeroPad**)
### Description:  
Class constructor, creates an instance of the class for each display to use. There's no need to configure the pins before calling the method, as the constructor takes care of the task.  
### Parameters:  
**sclk:** uint8_t (unsigned char), passes the pin number that is connected to the sclk pin of the display (the **SH_CP** pin of the shift register if working in a custom display). The pin must be free to be used as a digital output.  
**rclk:** uint8_t (unsigned char), passes the pin number that is connected to the rclk pin of the display (the **ST_CP** pin of the shift register if working in a custom display). The pin must be free to be used as a digital output.  
**dio:** uint8_t (unsigned char), passes the pin number that is connected to the dio pin of the display (the **DS** pin of the shift register if working in a custom display). The pin must be free to be used as a digital output.  
**rgtAlgn:** Boolean, optional parameter (if not specified the default value, true, will be assumed), indicates if the represented value must be displayed right aligned, with the missing heading characters being completed with spaces or zeros, depending in the zeroPad optional parameter. When a negative value is displayed and it's less than (dspDigits - 1) digits long, a right aligned display will keep the '-' sign in the leftmost position, and the free space to the leftmost digit will be filled with spaces or zeros, depending in the zeroPad optional parameter.  
**zeroPad:** Boolean, optional parameter (if not specified the default value, false, will be assumed), indicates if the heading free spaces of the integer right aligned displayed must be filled with zeros (true) or spaces (false). In the case of a negative integer the spaces or zeros will fill the gap between the '-' sign kept in the leftmost position, and the first digit.  
**commAnode:** bool, indicates if the display uses common anode seven segment LED digits (**true** value, default to keep the implementation backwards compatible), or  common cathode kind (**false** value). The use of one kind or the other makes a difference in the fact that one is complementary of the other, meaning a translation must be done on the information sent to the display. Each display instantiated by the class might be independently set up as one kind or the other.  
**dspDigits:** uint8_t (unsigned char), passes the number of digits in the instantiated display, the default value is 4, to keep the implementation backwards compatible.  
### Return value:  
The object created.  
### Use example:  
**`ClickCounter myClickCounter(6, 7, 10, true, true);`**  
**`ClickCounter myClickCounter(6, 7, 10, true, true, true, 5);`**  // 5 digits common anode counter  

---
### **blink**();
### Description:
Refer to **TM74HC595LedTube::blink()** method.  
### Parameters:  
None
### Return value:  
true: If the display was not already set to blink (so now the blinking was started).  
false: The display was already set to blink.  
### Use example:  
**`myClickCounter.blink();`**

---
### **blink**(unsigned long **onRate**,unsigned long **offRate**);
### Description:
Refer to **TM74HC595LedTube::blink()** method.  
### Parameters:  
Refer to **TM74HC595LedTube::blink()** method.  
### Return value:  
true: If the display was not already set to blink (so now the blinking was started).  
false: The display was already set to blink, and/or one or more of the parameters passed were out of range.  
### Use example:  
**`myClickCounter.blink(400);`** //Returns true and sets the blinking rate to 400 millisecs on, 400 millisecs off (symmetrical blink).  
**`myClickCounter.blink(800, 200);`** //Returns true and sets the blinking rate to 800 millisecs on, 200 millisecs off (asymmetrical blink)  
**`myClickCounter.blink(3000);`** //Returns false and the display stays without change.  

---
### **countBegin**(int **startVal**);
### Description:
Attaches the display to a timer interrupt service, as described in the **SevenSeg74HC595::begin()** method. The display then is started with the **startVal** count value, or **0** if no parameter is provided, represented according to the selected options of alignement and padding.
### Parameters:  
startVal: Optional integer value at wich the counter starts which must be in the range (-1)*(pow(10, (dspDigits - 1)) - 1) <= startValue <= (pow(10, dspDigits) - 1).  
### Return value:  
true: If the display could be attached to the ISR, or if the display was already attached to it, and the startValue was within the valid representable values range according to dspDigits.  
false: If the display couldn't be attached to the ISR, due to lack of free slots, or the startValue was out of range.  
### Use example:  
**`myClickCounter.countBegin();`**  

---
## **countDown()**(int **qty**);  
### Description:
Decrements the value of the current count and refreshes the display to keep it updated. The counter is decremented independently of the sign of the current count, as long as the new value resulting is in the displayable range.
### Parameters:  
qty: Optional integer value, its **absolute** value will be decremented from the current count value. If no parameter is passed a value of one will be used.  
### Return value:  
true: If the count could be decremented by the corresponding value without setting count out of range.  The counter value is decremented.  
false: If the count couldn't be decremented by the parameter value without getting out of range.The counter will keep its current value. 
### Use example:  
**`myClickCounter.countDown();`**  //Decrements the current count by 1  
**`myClickCounter.countDown(2);`**  //Decrements the current count by 2  
**`myClickCounter.countDown(-2);`**  //Decrements the current count by 2  

---
### **countReset()**;  
### Description:
Restarts the count to the original value provided when the counter was started with the **countBegin**(int **startVal**) method (not necesarily 0!!). The display is updated to reflect this change in its new value.  
### Parameters:  
None
### Return value:  
true: After resetting the value and updating the display.  

### Use example:  
**`myClickCounter.countReset();`**  

---

## **countRestart()**(int **restartValue**)  
### Description:
Restarts the count from the value provided as parameter. The display is updated to reflect this change in its new value.  
### Parameters:  
restartValue: Optional integer value, a value of 0 is set if no parameter is provided. The parameter must be in the range (-1)*(pow(10, (dspDigits - 1)) - 1) <= restartValue <= (pow(10, dspDigits) - 1).  
### Return value:  
true: If the parameter value was within valid range. 
false: If the parameter value was outside valid range.  
### Use example:  
**`myClickCounter.countRestart();`**  //sets the counter to 0  
**`myClickCounter.countRestart(-100);`**  //Sets the counter to -100 if the display is more than 3 digits long, false otherwise  
**`myClickCounter.countRestart(10000);`**  //Returns false if the display is less than 5 digits long, the counter is not changed  

---
### **countStop**();
### Description:
Refer to **TM74HC595LedTube::stop()** method.    
### Parameters:  
**None**  
### Return value:  
Refer to **TM74HC595LedTube::stop()** method.   
### Use example:  
**`myClickCounter.countStop();`**  

---
## **countToZero()**(int **qty**);  
### Description:
Modifies the value of the current count and refreshes the display to keep it updated. The counter absolute value will be decremented, independently of the sign of the current count , as long as the new value resulting is in the displayable range. If the current count was negative, the value will be incremented, if it was positive, will be incremented, with the concrete porpouse of approaching the count value to 0.
### Parameters:  
qty: Optional integer value, its **absolute** value will be decremente from the current absolute count value, the sign of the resulting count will be preserved. If no parameter is passed a value of one will be used.  
### Return value:  
true: If the absolut count could be decremented by the corresponding value, i.e. the count was not zero already, and the value pased by parameter absolut value does not exceed the count absolute value.  The counter value will be updated.  
false: If the count was already in a 0 value, or the the value pased by parameter absolut value does not exceed the count absolute value. The counter will keep its current value.  
### Use example:  
**`myClickCounter.countToZero();`**  // If the count was positive decrements the current count by 1, if it was negative increments the count by 1.  
**`myClickCounter.countToZero(2);`**  //If the count was positive and greater than 2 decrements the current count by 2, if it was negative increments the count by 2.  
**`myClickCounter.countToZero(-2);`**  //If the count was positive and greater than 2 decrements the current count by 2, if it was negative increments the count by 2.  

---
## **countUp()**(int **qty**);  
### Description:
Increments the value of the current count and refreshes the display to keep it updated. The counter is incremented independently of the sign of the current count, as long as the new value resulting is in the displayable range.
### Parameters:  
qty: Optional integer value, its **absolute** value will be incremented in the current count value. If no parameter is passed a value of one will be used.  
### Return value:  
true: If the count could be incremented by the corresponding value without setting count out of range.  The counter value will be updated
false: If the count couldn't be incremented by the parameter value without getting out of range. The counter will keep its current value.  
### Use example:  
**`myClickCounter.countUp();`**  //Increments the current count by 1  
**`myClickCounter.countUp(2);`**  //Increments the current count by 2  
**`myClickCounter.countUp(-2);`**  //Increments the current count by 2  

---
## **getCount()**;  
### Description:
Gets the current value of the counter.  
### Parameters:  
None.  
### Return value:  
The current value held by the counter, due to the 4 digits limitations, it will be in the range (-1)*(pow(10, (dspDigits - 1)) - 1) <= counter <= (pow(10, dspDigits) - 1)  
### Use example:  
**`long finalCount = myClickCounter.getCount();`**  

---
## **getStartVal()**  
### Description:
Gets the value passed as parameter when the `**.countBegin()**` method was invoked, starting the counter. This is the value that will be used for the `**.countReset()**` method.  
### Parameters:  
None.  
### Return value:  
The value to wich the counter was originally started, it will be in the range (-1)*(pow(10, (dspDigits - 1)) - 1) <= counter <= (pow(10, dspDigits) - 1)  
### Use example:  
**`long countStarted = myClickCounter.getStartVal();`**  

---
### **noBlink**();
### Description:
Refer to **TM74HC595LedTube::noBlink()** method.  
### Parameters:  
None
### Return value:  
true: If the display was set to blink, and the blinking is stopped.   
false: If the display was not set to blink, no changes will be done.
### Use example:  
**`myClickCounter.noBlink();`**

---
### **setBlinkRate**();
### Description:
Refer to **TM74HC595LedTube::setBlinkRate()** method.  
### Parameters:  
None
### Return value:  
Refer to **TM74HC595LedTube::setBlinkRate()** method.  
### Use example:  
**`myClickCounter.setBlinkRate(400);`** //Returns true and sets the blinking rate to 400 millisecs on, 400 millisecs off (symmetrical blink).  
**`myClickCounter.setBlinkRate(800, 200);`** //Returns true and sets the blinking rate to 800 millisecs on, 200 millisecs off (asymmetrical blink)  
**`myClickCounter.setBlinkRate(600, 3500);`** //Returns false and the display blinking rate stays without change.  

---
## **updDisplay()**  
### Description:
Updates the display with the current value of the counter. This method is not usually needed as each method that affect the counter value takes care of refreshing the display, but is provided in case of need if some external manipulation of the display is needed to execute, so that the current count value can be displayed again.  
### Parameters:  
None
### Return value:  
true: The value could be restored.  
false: Te value couldn't be restored, the count value was out of range.  
### Use example:  
**`myClickCounter.updDisplay();`** //Returns true and displays the current counter value.  