# v2.4.0 Code simplification and display improvement
- Several methods simplified for faster execution.  
- Several methods simplified for easy code understanding.  
- Order and times for driving display pins modified for better display latching and artifacts and ghosting avoidance.  
- `void send(const uint8_t &)` and `void send(const uint8_t &, const uint8_t &)` methods code replaced with the corresponding `void fastSend(uint8_t)` and `void fastSend(uint8_t, uint8_t)` methods code. Considerations:
   - Not the `.send()`, nor the `.fastSend()` methods were removed for back compatibility reasons. In other versions of analog libraries I developed for other platforms the `.send()` name for the method was the one kept.
   - The use of the `.send()` code was deprecated as it was based on the use of the `.shiftOut()` Arduino command, not compatible nor with direct replacement in other environments, and avoids the detailed management of the control lines timming of the 74HC595 chips.
   


# v2.3.1 On-line simulation added for example files, documentation corrections and updates
- WOKWI simulation added for the following examples:
   - blinkExample (https://wokwi.com/projects/414743484710761473)
   - oneDisplayExample (https://wokwi.com/projects/414740776518446081)
   - doubleGaugeExample (https://wokwi.com/projects/414798270033977345)
   - fastRefreshUseExample (https://wokwi.com/projects/414798729014618113)
   - gaugeExample (https://wokwi.com/projects/414799255569708033)
   - partialBlinkExample (https://wokwi.com/projects/414799772454823937)
   - refreshUseExample (https://wokwi.com/projects/414800983125084161)
   - setWaitCharExample (https://wokwi.com/projects/414801219291718657)
   - twoDisplaysExample (https://wokwi.com/projects/414802678289036289)
   - waitExample (https://wokwi.com/projects/414801567923357697)

# v2.3.0 Library update
Bugs corrections:
- ClickCounter::countDown(int) and ClickCounter::countUp(int): These methods now check the parameter to be not equal to 0. If the parameter passed is 0 the value returned will be false.
- ClickCounter::countToZero(int): This method now check the parameter to be not equal to 0. If the parameter passed is 0 the value returned will be false.
Changes:
- ClickCounter::countToZero(int): If the counter value reached 0, this method will make no changes to the counter, and return false


# v2.2.3 Method added to conform to the SevenSegDisplays interface Latest
- isBlank() method added to conform to the SevenSegDisplays library interface as possible.
- Documentation updated

# v2.2.2 Library update
- Minor debugging and cleanup of setters methods
- Documentation updated
- Ends any delvelopment stages

# v2.2.1 Library update
_ Redundant code cleanup.
_ Minor debug in counter class limit checking corrected.
_ README.md corrections

# v2.2.0 Library update
_ Changed the relation between ClickCounter and TM74HC595LedTube classes, from Inheritance to Dependency, as the needed methods to achieve the change were progresively added.
_ getDspValMax() and getDspValMin() methods added, as the v2.0.0 update gave the possibility to instantiate different lenght displays, the minimum and maximum values representable by the display are now instantiation dependant. These methods give the resulting values for the integer range displayable.

# v2.1.0 Library update
Bugs correction:
_ In 8 bits Atmel based boards (Arduino Uno and other ATmega based boards) an int stores a 16-bit (2-byte) value. This yields a range of -32,768 to 32,767, and so the library couldn't correctly represent more than 4 digits, as 99.999 is beyond the range. The restriction was eliminated by calculating displayable values as long integers, and modifying all methods accordingly and transparently.
New methods and capabilities:
_ Some displays tested show there's not a unique (simple and logical) wiring criteria used to build the displays, some use the LSb of the register to manage the first digit from right to left (very intuitive), some use the LSb to manage the first digit from left to right (not as intuitive but reasonable) and some use alternative options, some of them awkward which makes the representation reordering an extra load (the popular DM "DIY MORE" (R) 8 digits display is a good example). This new version adds the possibility to map the order of the display ports on any display, settable through the .setDigitsOrder() method.
Examples:
_ Examples were added to show the support for different display lenghts up to 8 digits/ports
_ Examples were added to show the new capabilities to change the order of the display wired ports

# v2.0.0 Library update
- Major changes have been done to the library internal mechanisms to expand its capabilities and services, reduce resources footprint and make it more flexible without compromising it's backward compatibility.
- While using the provided interface there's only one backward compatibility issue that can't be avoided: the **`setBlinkMask()`** method parameters had to be changed and any code using that method will have to be updated, direct result of the library new capability to implement various display lengths from 1 to 8 display ports, while the abovementioned method limits the mask to 4 digit displays.

The new version of this library includes benefits and services like:
_ NEW ability to implement and drive different lengthed displays, with the corresponding length related validations, including string lengths, in-range values, paddings, etc.
_ NEW dynamic resource acquisition to avoid allocating resources until they are actually needed, and released them when the will not be needed anymore.
_ NEW methods added to get the values associated with the possibility to build different size displays.
