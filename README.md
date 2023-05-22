# **A 4-bit Led Digital Tube Module easy to use library**
Developed for the cheap and popular 7-segment 4 digits led displays based on two TM74HC595 (or similar) shift registers, the main focus was set in: ease of use, flexibility and basic prevention of 'misrepresentation' errors.

![alt text](https://github.com/GabyGold67/FourBitLedDigitalTube/blob/master/extras/4-BitsLedDigitalTubeModule01.jpg "4-Bits LED Digital Tube Module")

## Ease of use:
Instance the class, notify the object you're ready to go, and start `.print()`ing the data to the display. 

## Flexibility:
Integers, floating point or strings they'll show as long as the display is capable of doing so in a trustworthy way. If you need to represent a percentage or level of completeness a `.gauge()` method is included to represent them in a "Old Motorola brick cell phones style".

## Trustworthy representation basic checking:
The representation of different types of data in this kind of displays is limited, and many implementations of the libraries to drive them take arbitrary or personally biased decisions on how to handle the problem.
The danger of misrepresenting values in the display are usually ignored so when a value can't be faithfully represented by the display, the data is truncated, sliced, characters are replaced by spaces or whatever criteria the developer defined. When trying to display the value __"90153"__ through the module, displaying __"9015"__ is no better (nor worse) than displaying __"0153"__, those are __misrepresentations__. This library returns a boolean value indicating if it was able to display a trustworthy representation of the value, as long as it is able to. If a trustworthy representation was nos possible it will blank the display.  
## Crossplatform:
This kind of displays need to be periodically refreshed, as it can actively turn on only one digit at a time, so to keep all de digits visible the user must activate each digit independently to generate a "cinematic effect". The library takes care of this, and offers two solutions to do so. The first is to attach the refreshing methods to a timer interrupt service (ISR) of the microcontroller, the second is through methods that the user can call from the main code. The first mechanism frees the user from the load of calling the refreshing methods periodically, specially considering that long looping times (for, while, do included), or the use of delay() could make the display flicker or simply stop until next refresh. The second option is given in the case that the timer/interrupt library used (see de dependencies information provided as I might change it in a future) doesn't support the architecture being used by the developer. In any case the library is capable of work in any platform, using one way or the other.

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
There are other 3 characters that can be represented in the display, but the conversion from a character to use while programming is language setting dependant, so I assigned them to available non displayable characters of easy access in any keyboard layout in most languages, they can be used as part of the text string to display, and they are:  
= Builds a character formed by lighting the lower 2 horizontal segments of the digit display, can be described as a "lower equal" symbol.  
~ Builds a character formed by lighting the 3 horizontal segments of the digit display, can be described as an "equivalent" symbol.  
'*' (asterisk) Builds a character by lighting the upper 4 segments, forming a little square, can be described as the "degrees" symbol or º.  
### Parameters:  
**text:** String, up to four displayable characters long PLUS usable dots, all characters included in the representable characters list. Each valid character might be followed by a "." if needed, without being counted as a character, even spaces and special chars. If two or more consecutive dots are passed an intermediate space is considered to be included between each pair of them.  
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
