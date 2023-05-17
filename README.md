# **A 4-bit Led Digital Tube Module easy to use library**
Developed for the cheap and popular 7-segment 4 digits led displays based on two TM74HC595 (or similar) shift registers, the main focus was set in: ease of use, flexibility and basic prevention of 'misrepresentation' errors

## Ease of use:
Instance the class, notify the object you're ready to go, and start `.print()`ing the data to the display. 

## Flexibility:
Integers, floating point or strings they'll display as long as the display is capable of it in a trustworthy way. If you need to represent a percentage or level of completeness a `.gauge()` method is included to represent them in a "Old Motorola brick cell phones style".

## Trustworthy representation basic checking
The representation of different types of data in this kind of displays is limited, and many implementations of the libraries to drive them take arbitrary or personally biased decisions on how to handle the problem.
The danger of misrepresenting values in the display are usually ignored so when a value can't be faithfully represented by the display, the data is truncated, sliced, characters are replaced by spaces or whatever criteria the developer defined. When trying to display the value __"90153"__ through the module, displaying __"9015"__ is no better than displaying __"0153"__, those are misrepresentations. This library returns a boolean value indicating if it was able to display a trustworthy representation of the value, as long as it is able to.  

