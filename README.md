# **A 4-bit Led Digital Tube Module display easy to use library**
Developed for the cheap and popular 7-segment 4 digits led displays (**_and for the custom made displays as GIANTS COUNTERS and CLOCKS_**)  based on two TM74HC595 (or similar) shift registers, the main focus was set on: ease of use, flexibility and basic prevention of 'misrepresentation' errors.

![4-Bits LED Digital Tube Module](./extras/4-BitsLedDigitalTubeModule01.jpg "4-Bits LED Digital Tube Module")

## Ease of use:
Instance the class passing just 3 parameters (the 3 pins connected to the display module), notify the object you're ready to go, and start ``.print()``ing the data to the display. 

## Flexibility:
Integers, floating point or strings they'll show as long as the display is capable of doing so in a trustworthy way. If you need to represent a percentage or level of completeness a ``.gauge()`` method is included to represent them in a "Old Motorola brick cell phones style".

## Trustworthy representation basic checking:
The representation of different types of data in this kind of displays is limited, and many implementations of the libraries to drive them take arbitrary or personally biased decisions on how to handle the problem.
The danger of misrepresenting values in the display are usually ignored so when a value can't be faithfully represented by the display, the data is truncated, sliced, characters are replaced by others or whatever criteria the developer defined. When trying to display the value __"90153"__ through the module, displaying __"9015"__ is no better (nor worse) than displaying __"0153"__, those are __misrepresentations__. This library returns a boolean value indicating if it was able to display a trustworthy representation of the value, as long as it is able to. If a trustworthy representation was not possible it will blank the display.  
## Crossplatform:
This kind of displays need to be periodically refreshed, as it can actively turn on only one digit at a time, so to keep all de digits visible the user must activate periodically each digit one by one independently to generate a "cinematic effect". The library takes care of this, and offers two solutions to do so.  
* The first is to attach the refreshing methods to a timer interrupt service (ISR) of the microcontroller.  
* The second is through methods that the user can call from the main code.  

The first mechanism frees the user from the load of calling the refreshing methods periodically, specially considering that long looping times (when executing **for**, **while**, **do** loops included), or the use of **delay()** could make the display flicker or simply stop until next refresh. The second option is given in the case that the timer/interrupt library used (see de dependencies information provided as I might change it in a future) doesn't support the architecture being used by the developer, or too many displays are already attached to the ISR that makes the system unstable. In any case the library is capable of working in any platform, using one way when possible, or the other always.  

# **Included Methods**

|Method | Parameters|
|---|---|
|**_TM74HC595LedTube_** |uint8_t **sclk**, uint8_t **rclk**, uint8_t **dio**|
|**begin()**|None|
|**blink()**|None|
|**clear()**|None|
|**fastRefresh()**|None|
|**fastSend()**|uint8_t **segments**, uint8_t **port**|
|**gauge()**|int **level** (, char **label**)|
||double **level** (, char **label**)|
|**getInstanceNbr()**|None|
|**getMaxBlinkRate()**|None|
|**getMinBlinkRate()**|None|
|**isBlinking()**|None|
|**noBlink()**|None|
|**print()**|String **text**|
||int **value** (, bool **rgtAlgn** (, bool **zeroPad**))|
||double **value** (, unsigned int **decPlaces** (, bool **rgtAlgn** (, bool **zeroPad**)))|
|**refresh()**|None|
|**send()**|uint8_t **segments**, uint8_t **port**|
|**setBlinkRate()**|unsigned long **newRate**|
|**stop()**|None|


## **Methods definition and use description**

---
### **TM74HC595LedTube**(uint8_t sclk, uint8_t rclk, uint8_t dio)
### Description:  
Class constructor, create an instance of the class for each display to use. There's no need to configure the pin before calling the method, as the constructor takes care of the task.  
### Parameters:  
**sclk:** uint8_t (unsigned char), passes the pin number that is connected to the sclk pin of the display (the **SH_CP** pin of the shift register if working in a custom display). The pin must be free to be used as a digital output.  
**rclk:** uint8_t (unsigned char), passes the pin number that is connected to the rclk pin of the display (the **ST_CP** pin of the shift register if working in a custom display). The pin must be free to be used as a digital output.  
**dio:** uint8_t (unsigned char), passes the pin number that is connected to the dio pin of the display (the **DS** pin of the shift register if working in a custom display). The pin must be free to be used as a digital output.
### Return value:  
The object created.

### Use example:  
**TM74HC595LedTube** myLedDisp(6, 7, 10);

---
### **begin**();
### Description:
Attaches the display to a timer interrupt service, which takes care of refreshing the display regularly. Up to four displays can be attached to the ISR, at least theoretically, as the refreshing work takes time, and the time taken is proportional to the quantity of displays attached. And as ISRs literally interrupts other tasks done by the microcontroller, the time taken by the ISRs must be kept to minimal or the stability of the whole system will be compromised. As the time available to execute the ISRs without risking the stability of the system depends on various factors, the number of supported displays has to be tested in each development done. If the stability of the system is compromised then the displays exceeding the number of tolerated units will have to be refreshed by periodically using the **refresh()** method.
### Parameters:  
None
### Return value:  
true: If the display could be attached to the ISR, or if the display was already attached to it. This not ensures system stability.  
false: If the display couldn't be attached to the ISR, due to lack of free slots.  
### Use example:  
myLedDisp.**begin**();  

---
### **blink**();
### Description:
Makes the display blink the contents it shows until a **noBlink()** method is invoked. The blinking is symmetrical, meaning that the time the display shows the contents and the time the display is blank are equal. The blinking starts at a preset rate the first time the method is invoked. The blinking rate can be changed by using the .setBlinkRate() method. After changing the blinking rate, the new blinking rate will be kept after a .noBlink() or new .blink() call is done, until it is modified with a new .setBlinkRate() call.
### Parameters:  
None
### Return value:  
true: Always  
### Use example:  
myLedDisp.**blink**();

---
### **clear**();
### Description:
Clears the display, turning off all the segments and dots.
### Parameters:  
None
### Return value:  
None   
### Use example:  
myLedDisp.**clear**();

---
### **fastRefresh**();
### Description:
Refreshes the display, **only one digit per call**, the method takes care of registering which digit was redrawn last and move to the next until the last is reached and then restart from the first, and uses direct pin handling instead of using pre-built `shiftOut()` kind of methods. This working criteria has two consecuences:
* The method works faster than redrawing all the digits each time and using the call to shiftOut() methods, so it is less time consuming and so is the most appropiate to be used within an ISR.
* When used by the developer to refresh the display from the code it must be called more frequently (starting with the four times needed to refresh all the digits of the display, and then doing those four calls periodically) to keep the display's cinematic effect. Failing to do so will be seen as display flickering.  
### Parameters:  
None
### Return value:  
None   
### Use example:  
myLedDisp.**fastRefresh**();

---
### **fastSend**(uint8_t segments, uint8_t port);
### Description:
Sends one character to the display, using direct pin handling instead of using pre-built `shiftOut()` kind of methods. The parameters indicate which character and to which digit will be sent. This is the method used by fastRefresh() to send the digit when it has to be refreshed. **_Keep in mind_** that sending a character directly to the display has no connection to keep it displayed as it must be resent periodically to keep the cinematic effect. Also the refresh() and fastRefresh() methods will overwrite the character sent, explicitly called or by the ISR service.
### Parameters:  
**segments:** An unsigned short integer value representing which segments to turn on and which off to get the graphic representation of a character in the seven segment display, the corresponding value can be looked up in the **_charLeds[]** array definition in the header file of the library.  
**port:** An unsigned short integer value representing the digit where the character will be sent, being the range of valid values 0 <= port <= 3, the 0 value is the rightmost digit, the 1 value the second from the right and so on.
### Return value:  
None   
### Use example:  
myLedDisp.**fastSend**(0x88, 1); // Sends a capital A to the second digit from right to left.

---
### **gauge**(int level, char label);
### Description:
Displays a basic graphical representation of the level of fulfillment or completeness of a segmented value or task, gives a general fast notion on the matter, as a battery charge level, liquids deposit level, time remaining, tasks completeness and so on. The levels are represented by the horizontal segments (0, 1, 2 or 3 from bottom to top, and from left to right), and a character might be added before the graphical representation to give an indication of what the display is showing, passed through the **label** parameter. 
### Parameters:  
**level:** The integer value to display must be in the range 0 <= level <= 3.  
**label:** A character, optional parameter (if not specified the default value, a Space, will be assumed), that will be displayed in the leftmost digit of the display. The character must be one of the "displayable" characters, as listed in the **.print()** method description.
### Return value:  
true: If the value could be represented.  
false: Otherwise, being that the **level** parameter was out of range and/or the **label** parameter was not in the list of displayable characters, and the display will be blanked.

### Use example:  
myLedDisp.**gauge**(3);  
myLedDisp.**gauge**(2, 'b');  
myLedDisp.**gauge**(1, 'F');
myLedDisp.**gauge**(4, 'd'); //Error  
myLedDisp.**gauge**(3, 'X'); //Error  

---
### **gauge**(double level, char label);
### Description:
Displays a basic graphical representation of the level of fulfillment or completeness of a segmented value or task, gives a general fast notion on the matter, as a battery charge level, liquids deposit level, time remaining, tasks completeness and so on. The levels are represented by the horizontal segments (0, 1, 2 or 3 from bottom to top, and from left to right), and a character might be added before the graphical representation to give an indication of what the display is showing, passed through the **label** parameter. 
### Parameters:  
**level:** The double value to display must be in the range 0.0 <= level <= 1.0, being the range the representation of the percentage of the 'full' level, so that the ranges are 0.0 <= level < 0.25 for the first level, 0.25 <= level < 0.50 for the second level, 0.50 <= level < 0.75 for the third level, and 0.75 <= level <= 1.00 for the fourth and upper level.
**label:** A character, optional parameter (if not specified the default value, a Space, will be assumed), that will be displayed in the leftmost digit of the display. The character must be one of the "displayable" characters, as listed in the **.print()** method description.
### Return value:  
true: If the value could be represented.  
false: Otherwise, being that the **level** parameter was out of range and/or the **label** parameter was not in the list of displayable characters, and the display will be blanked.

### Use example:  
myLedDisp.**gauge**(0.0); 
myLedDisp.**gauge**(0.4); 
myLedDisp.**gauge**(0.55, 'b');
myLedDisp.**gauge**(1.0, 'F');
myLedDisp.**gauge**(1.5, 'd'); //Error
myLedDisp.**gauge**(3.0, 'X'); //Error

---
### **print**(String text);
### Description:
Displays the string text if it contains all "displayable" characters, which are the ones included in the following list: **0123456789AabCcdEeFGHhIiJLlnOoPqrStUuY-_.** and the **space**.  
There are other 3 characters that can be represented in the display, but the conversion from a character to use while programming is "host language setting dependant", so those where assigned to available ASCII non displayable characters of easy access in any keyboard layout in most languages, they can be used as part of the text string to display, and they are:  
* **=** Builds a character formed by lighting the lower 2 horizontal segments of the digit display, can be described as a "lower equal" symbol.  
* **~** Builds a character formed by lighting the 3 horizontal segments of the digit display, can be described as an "equivalent" symbol.  
* **'*'** (asterisk) Builds a character by lighting the upper 4 segments, forming a little square, can be described as the "degrees" symbol or º.  
### Parameters:  
**text:** String, up to four displayable characters long PLUS usable dots, all characters included in the representable characters list. Each valid character might be followed by a "." if needed, without being counted as a character, even spaces and special chars. If two or more consecutive dots are passed, an intermediate space is considered to be included between each pair of them, and that space counts as one of the four available characters to display.  
### Return value:  
true: If the text could be represented.  
false: Otherwise, and the display will be blanked.

### Use example:  
myLedDisp.**print**("Hi");  
myLedDisp.**print**("Strt");  
myLedDisp.**print**("L.O.L.");  
myLedDisp.**print**("36.7*");  
myLedDisp.**print**("....");  

---
### **print**(int value, bool rgtAlgn, bool zeroPad);
### Description:
Displays an integer value as long as the length representation fits the available space of the display.
### Parameters:  
**value:** The integer value to display which, due to the 4 digits limitations, must be in the range -999 <= value <= 9999.  
**rgtAlgn:** Boolean, optional parameter (if not specified the default value, false, will be assumed), indicates if the represented value must be displayed right aligned, with the missing heading characters being completed with spaces or zeros, depending in the zeroPad optional parameter. When a negative value is displayed and it's less than 3 digits long, a right aligned display will keep the '-' sign in the leftmost position, and the free space to the leftmost digit will be filled with spaces or zeros, depending in the zeroPad optional parameter.  
**zeroPad:** Boolean, optional parameter (if not specified the default value, false, will be assumed), indicates if the heading free spaces of the integer right aligned displayed must be filled with zeros (true) or spaces (false). In the case of a negative integer the spaces or zeros will fill the gap between the '-' sign kept in the leftmost position, and the first digit.  
### Return value:  
true: If the value could be represented.  
false: Otherwise, and the display will be blanked.

### Use example:  
myLedDisp.**print**(12); //Displays '**``12  ``**'  
myLedDisp.**print**(12, true); //Displays '**``  12``**'  
myLedDisp.**print**(12, true, true); //Displays '**``0012``**'    
myLedDisp.**print**(-12); //Displays '**``-12``**'  
myLedDisp.**print**(-12, true); //Displays '**``- 12``**'  
myLedDisp.**print**(-12, true, true); //Displays '**``-012``**'    

---
### **print**(double value, unsigned int decPlaces, bool rgtAlgn, bool zeroPad);
### Description:
Displays a floating point value as long as the length representation fits the available space of the display. If the integer part of value is not in the displayable range or if the sum of the spaces needed by the integer part plus the indicated decimal places to display is greater than the available digits space, the print() will fail, returning a false value and clearing the display.
### Parameters:  
**value:** The floating point value which, due to the 4 digits limitations must be in the range -999 <= value <= 9999 for the integer part, and in the range -99 <= value <= 999 if the representation of **at least** one decimal digit is intended.The range is limited to -9 <= value <= 99 for two decimal places. Negative numbers with three decimal places are not displayable due to the digit used by the **-** symbol, but positive numbers with one integer digit and 3 decimal places are.  
**decPlaces:** Decimal places to be displayed after the decimal point, ranging 0 <= decPlaces <= 3, selecting 0 value will display the number as an integer, with no '.' displayed. In any case the only modification that will be applied if value has a decimal part longer than the decPlaces number of digits is **truncation**, if any other rounding criteria is desired the developer must apply it to **value** before calling this method.
**rgtAlgn:** Boolean, optional parameter (if not specified the default value, false, will be assumed), indicates if the represented value must be displayed right aligned, with the missing heading characters being completed with spaces or zeros, depending in the zeroPad optional parameter. When a negative value is displayed and it's less than 3 digits long, a right aligned display will keep the '-' sign in the leftmost position, and the free space to the leftmost digit will be filled with spaces or zeros, depending in the zeroPad optional parameter.  
**zeroPad:** Boolean, optional parameter (if not specified the default value, false, will be assumed), indicates if the heading free spaces of the value right aligned displayed must be filled with zeros (true) or spaces (false). In the case of a negative value the spaces or zeros will fill the gap between the '-' sign kept in the leftmost position, and the first digit.  
### Return value:  
true: If the value could be represented.  
false: Otherwise, and the display will be blanked.
### Use example:  
myLedDisp.**print**(1.2, 2); //Displays '**``1.20 ``**'  
myLedDisp.**print**(1.2, 2, true); //Displays '**`` 1.20``**'  
myLedDisp.**print**(12, 2, true, true); //Displays '**``01.20``**'    
myLedDisp.**print**(-1.2, 2); //Displays '**``-1.20``**'  
myLedDisp.**print**(-1.28, 1, true); //Displays '**``- 1.2``**'  
myLedDisp.**print**(-1.28, 1, true, true); //Displays '**``-01.2``**'    
myLedDisp.**print**(-1.28, 3, true, true); //Error

---
### **refresh**();
### Description:
Refreshes the display, **all four digits per call**, the method takes care of registering which digit was redrawn first and each call starts from the next until the last is reached and then restart from the first, to minimize ghosting and keep all the digits brightness even, and uses pre-built `shiftOut()` kind of methods. This working criteria has two consecuences:
* The method works slower than the **fastRefresh()**, so it will take more time to execute.  
* When used by the developer to refresh the display from the code it will avoid ghosting or blinking effects being called less frequently to keep the display's cinematic effect.  
### Parameters:  
None
### Return value:  
None   
### Use example:  
myLedDisp.**refresh**();

---
### **send**(uint8_t segments, uint8_t port);
### Description:
Sends one character to the display, using pre-built `shiftOut()` kind of methods, which takes unknown time to complete depending on the  implementation of the framework used to develop. The parameters indicate which character and to which digit will be sent. This is the method used by refresh() to send the digit when it has to be refreshed. **_Keep in mind_** that sending a character directly to the display has no connection to keep it displayed as it must be resent periodically to keep the cinematic effect. Also the refresh() and fastRefresh() methods will overwrite the character sent, explicitly called or by the ISR service.
### Parameters:  
**segments:** An unsigned short integer value representing which segments to turn on and which off to get the graphic representation of a character in the seven segment display, the corresponding value can be looked up in the **_charLeds[]** array definition in the header file of the library.  
**port:** An unsigned short integer value representing the digit where the character will be sent, being the range of valid values 0 <= port <= 3, the 0 value is the rightmost digit, the 1 value the second from the right and so on.
### Return value:  
None   
### Use example:  
myLedDisp.**send**(0x91, 2); // Sends a Y to the third digit from right to left.

---
### **stop**();
### Description:
Detaches the display from the timer interrupt service which takes care of refreshing the display regularly (if it was attached to it). If the display wasn't attached to the ISR no modification is made. The method then checks the array (list) of active serviced displays, if none is left in that array, the timer service is stopped, and the interrupt used by it is released, to leave the resource available for other uses. This last action is reversed when a new begin() method is executed in any display.  
### Parameters:  
None
### Return value:  
true: The instance of the display was found and detached from the ISR.  
false: The instance of the display wasn't found attached to the ISR, no detach was carried as it wasn't needed.  
### Use example:  
myLedDisp.**stop**();

---
### **noBlink**();
### Description:
Stops the display blinking, leaving the display turned on.
### Return value:  
true: Always   
### Use example:  
myLedDisp.**noBlink**();

---
### **isBlinking**();
### Description:
Returns a boolean value indicating if the display is set to blink or not.
### Return value:  
true: If the display is set to blink.  
false: If the display is set not to blink.   
### Use example:  
myLedDisp.**isBlinking**();

---
### **getInstanceNbr**();
### Description:
Returns an unsigned short integer value indicating the instantition number it was given to the object. Each time the class is instantiated the created object receives a serial instantiation number that can be used in order to identify each object.
### Return value:  
The unsigned short number indicating the identificacion Instance Number.  
### Use example:  
myLedDisp.**getInstanceNbr**();

---
### **getMinBlinkRate**();
### Description:
Returns the minimum time the display can be configured to blink.
### Return value:  
unsigned long integer: The minimum time, in milliseconds, the display can be set to blink. This value is the minimum to set as the turned-on or the turned-off stage of the blinking process started by a **.blink()** method.  
### Use example:  
myLedDisp.**getMinBlinkRate**();

---
### **getMaxBlinkRate**();
### Description:
Returns the maximum time the display can be configured to blink.
### Return value:  
unsigned long integer: The maximum time, in milliseconds, the display can be set to blink. This value is the maximum to set as the turned-on or the turned-off stage of the blinking process started by a **.blink()** method.  
### Use example:  
myLedDisp.**getMaxBlinkRate**();

