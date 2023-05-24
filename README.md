# **A 4-bit Led Digital Tube Module display easy to use library**
Developed for the cheap and popular 7-segment 4 digits led displays based on two TM74HC595 (or similar) shift registers, the main focus was set on: ease of use, flexibility and basic prevention of 'misrepresentation' errors.

![alt text](https://github.com/GabyGold67/FourBitLedDigitalTube/blob/master/extras/4-BitsLedDigitalTubeModule01.jpg "4-Bits LED Digital Tube Module")

## Ease of use:
Instance the class, notify the object you're ready to go, and start ``.print()``ing the data to the display. 

## Flexibility:
Integers, floating point or strings they'll show as long as the display is capable of doing so in a trustworthy way. If you need to represent a percentage or level of completeness a ``.gauge()`` method is included to represent them in a "Old Motorola brick cell phones style".

## Trustworthy representation basic checking:
The representation of different types of data in this kind of displays is limited, and many implementations of the libraries to drive them take arbitrary or personally biased decisions on how to handle the problem.
The danger of misrepresenting values in the display are usually ignored so when a value can't be faithfully represented by the display, the data is truncated, sliced, characters are replaced by spaces or whatever criteria the developer defined. When trying to display the value __"90153"__ through the module, displaying __"9015"__ is no better (nor worse) than displaying __"0153"__, those are __misrepresentations__. This library returns a boolean value indicating if it was able to display a trustworthy representation of the value, as long as it is able to. If a trustworthy representation was nos possible it will blank the display.  
## Crossplatform:
This kind of displays need to be periodically refreshed, as it can actively turn on only one digit at a time, so to keep all de digits visible the user must activate periodically each digit one by one independently to generate a "cinematic effect". The library takes care of this, and offers two solutions to do so.  
* The first is to attach the refreshing methods to a timer interrupt service (ISR) of the microcontroller.  
* The second is through methods that the user can call from the main code.  

The first mechanism frees the user from the load of calling the refreshing methods periodically, specially considering that long looping times (when executing for, while, do included), or the use of delay() could make the display flicker or simply stop until next refresh. The second option is given in the case that the timer/interrupt library used (see de dependencies information provided as I might change it in a future) doesn't support the architecture being used by the developer, or too many displays are already attached to the ISR that makes the system unstable. In any case the library is capable of working in any platform, using one way when possible, or the other always.  

# **Included Methods**

|Method | Parameters|
|---|---|
|**_TM74HC595LedTube_**|uint8_t **sclk**, uint8_t **rclk**, uint8_t **dio**|
|**begin()**|None|
|**blink()**|None|
|**clear()**|None|
|**fastRefresh()**|None|
|**fastSend()**|uint8_t **segments**, uint8_t **port**|
|**gauge()**|int **level** (, char **label**)|
||double **level** (, char **label**)|
|**getInstanceNbr()**|None|
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
Class constructor, creates an instance of the class for each display in use.  
### Parameters:  
**sclk:** uint8_t (unsigned char), passes the pin number that is connected to the sclk pin of the display. The pin must be free to be used as a digital output.  
**rclk:** uint8_t (unsigned char), passes the pin number that is connected to the rclk pin of the display. The pin must be free to be used as a digital output.  
**dio:** uint8_t (unsigned char), passes the pin number that is connected to the dio pin of the display. The pin must be free to be used as a digital output.
### Return value:  
The object created.

### Use example:  
**TM74HC595LedTube** myLedDisp(6, 7, 10);

---
### **print**(String text);
### Description:
Displays the string text if it contains all "displayable" characters, which are the ones included in the following list: **0123456789AabCcdEeFGHhIiJLlnOoPqrStUuY-_.** and the **space**.  
There are other 3 characters that can be represented in the display, but the conversion from a character to use while programming is host language setting dependant, so I assigned them to available ASCII non displayable characters of easy access in any keyboard layout in most languages, they can be used as part of the text string to display, and they are:  
* **=** Builds a character formed by lighting the lower 2 horizontal segments of the digit display, can be described as a "lower equal" symbol.  
* **~** Builds a character formed by lighting the 3 horizontal segments of the digit display, can be described as an "equivalent" symbol.  
* **'*'** (asterisk) Builds a character by lighting the upper 4 segments, forming a little square, can be described as the "degrees" symbol or º.  
### Parameters:  
**text:** String, up to four displayable characters long PLUS usable dots, all characters included in the representable characters list. Each valid character might be followed by a "." if needed, without being counted as a character, even spaces and special chars. If two or more consecutive dots are passed an intermediate space is considered to be included between each pair of them, and that space counts as one of the four available characters to display.  
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
**rgtAlgn:** Boolean, optional parameter (if not specified the default value, false, will be assumed), indicates if the represented value must be displayed right aligned, with the missing heading characters being completed with spaces or zeros, depending in the zeroPad optional parameter. When a negative value is displayed and it's less than 3 digits long, a right aligned display will keep the '-' sign in the leftmost position, and the free space to the leftmost digit will be filled with spaces or zeros,depending in the zeroPad optional parameter.  
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
**value:** The floating point value which, due to the 4 digits limitations must be in the range -999 <= value <= 9999 for the integer part, and in the range -99 <= value <= 999 if the representation of **at least** one decimal digit is intended.  
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

---
### **begin**();
### Description:
Attaches the display to a timer interrupt service, which takes care of refreshing the display regularly. Up to four displays can be attached to the ISR, at least theoretically, as the refreshing work takes time, and the time taken is proportional to the quantity displays attached. And as ISRs literally interrupts other tasks done by the microcontroller, the time taken by the ISRs must be kept to minimal or the stability of the whole system will be compromised. As the time available to execute the ISRs without risking the stability of the system depends on various factors, the number of supported displays has to be tested in each development done. If the stability of the system is compromised then the displays exceeding the number of tolerated units will have to be refreshed by periodically using the **refresh()** method.
### Parameters:  
None
### Return value:  
true: If the display could be attached to the ISR, or if the display was already attached to it. This not ensures system stability.
false: If the display couldn't be attached to the ISR, due to lack of free slots.  
### Use example:  
myLedDisp.**begin**();  

---
### **stop**();
### Description:
Detaches the display from the timer interrupt service which takes care of refreshing the display regularly (if it was attached to it). If the display wasn't attached to the ISR no modification is made. The method then checks the array (list) of active serviced displays, if none is left in that array, the timer service is stopped, and the interrupt used is released, to leave the resource available for other uses. This last action is reversed when a new begin() method is executed in any display.  
### Parameters:  
None
### Return value:  
true: The instance of the display was found and detached from the ISR.
false: The instance of the display wasn't found attached to the ISR, no detach was carried as it wasn't needed.  
### Use example:  
myLedDisp.**stop**();

---
### **blink**();
### Description:
Makes the display blink the contents it shows until a noBlink() method is invoked. The blinking is symmetrical, meaning that the time the display shows the contents and the time the display is blank are equal. The blinking starts at a preset time time the first time the method is invoked. The blinking rate can be changed by using the .setBlinkRate() method. After changing the blinking rate, the new blinking rate will be kept after a .noBlink() or new .blink() calls until it's modified with a new .setBlinkRate() call.
### Return value:  
true: Always (for compatibility reasons)  
### Use example:  
myLedDisp.**blink**();

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
Returns a value indicating if the display is set to blink or not.
### Return value:  
true: If the display is set to blink.
false: If the display is set not to blink.   
### Use example:  
myLedDisp.**isBlinking**();
