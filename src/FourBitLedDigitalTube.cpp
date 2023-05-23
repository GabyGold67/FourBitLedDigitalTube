#include <Arduino.h>
#include <FourBitLedDigitalTube.h>
#include <TimerOne.h>

uint8_t TM74HC595LedTube::displaysCount = 0;
TM74HC595LedTube *instancesList[MAX_PTR_ARRAY] {};

void intRefresh(){
    //ISR called by Timer1 to keep the display lit by calling each display's fastRefresh() method
    for(uint8_t i {0}; i < MAX_PTR_ARRAY; i++)
        if (instancesList[i] != nullptr){
            instancesList[i]->fastRefresh();
        }

    return;
}

TM74HC595LedTube::TM74HC595LedTube(uint8_t sclk, uint8_t rclk, uint8_t dio)
    :_sclk{sclk}, _rclk{rclk}, _dio{dio}
{
    pinMode(_sclk, OUTPUT);
    pinMode(_rclk, OUTPUT);
    pinMode(_dio, OUTPUT);

    _dispInstNbr = displaysCount++;
    _dispInstance = this;

    clear();
}

void TM74HC595LedTube::refresh(){
    static int firstRefreshed {0};

    if (_blink == true){
        if (_blinkShowOn == false) {
            if (_blinkTimer == 0){
                //turn off all digits without affecting the _digit[] buffer
                send(0xFF, 0b0001);
                send(0xFF, 0b0010);
                send(0xFF, 0b0100);
                send(0xFF, 0b1000);

                _blinkTimer = millis();
            }
            else if((millis() - _blinkTimer)> _blinkRate){
                _blinkTimer = 0;
                _blinkShowOn = true;
            }
        }
        else{
            if (_blinkTimer == 0){
                _blinkTimer = millis();
            }
            else if((millis() - _blinkTimer)> _blinkRate){
                _blinkTimer = 0;
                _blinkShowOn = false;
            }
        }
    }

    if((_blink == false)||(_blinkShowOn == true)){
        send(_digit[(0 + firstRefreshed)%4], 1<<(0 + firstRefreshed)%4);
        send(_digit[(1 + firstRefreshed)%4], 1<<(1 + firstRefreshed)%4);
        send(_digit[(2 + firstRefreshed)%4], 1<<(2 + firstRefreshed)%4);
        send(_digit[(3 + firstRefreshed)%4], 1<<(3 + firstRefreshed)%4);
        firstRefreshed++;
        if (firstRefreshed == 4)
            firstRefreshed = 0;
    }

    return;
}

void TM74HC595LedTube::clear(){
  //Cleans the contents of the internal display buffer (All leds off for all digits)
  _digit[0] = _digit[1] = _digit[2] = _digit[3] = 0xFF;
    refresh();
}

void TM74HC595LedTube::send(const uint8_t &content){
    //Sends the byte value (char <=> unsigned short int) to the 4 7-segment display bit by bit
    //by using the shiftOut() function. The time added (or not) to send it bit is unknown, so the total time
    //consumed to shift an entire byte is unknown, issue that must be considered when the method is invoked 
    //from an ISR and multiple times depending on the qty of displays being used
    shiftOut(_dio, _sclk, MSBFIRST, content);
}

void TM74HC595LedTube::send(const uint8_t &segments, const uint8_t &port){
// Sends the character 'segments' to the digit 'port' of the display
// Content and Port must be sent in two sequencial parts, character first, port second
// so this overloaded two char send method uses the one char send method twice and then moves
// up the RCLK pin to present the content in the shift register. This method depends on the shiftOut() function
// so consumed time must be considered
    digitalWrite(_rclk, LOW);
    send(segments);
    send(port);
    digitalWrite(_rclk, HIGH);
}

void TM74HC595LedTube::fastSend(uint8_t content){
    //Sends the byte value (char <=> unsigned short int) to the 4 7-segment display bit by bit
    //by direct manipulation of the microcontroller pins. There is no time added, so the total time
    //consumed to shift an entire byte is supposed to be the lowest achievable in this level of abstraction.
    //So this is the method suggested to be called from an ISR to keep the ISR time consumed to the lowest

    for (int i {7}; i >= 0; i--){
        if (content & 0x80)
            digitalWrite(_dio, HIGH);
        else
            digitalWrite(_dio, LOW);
        content <<= 1;
        digitalWrite(_sclk, LOW);
        digitalWrite(_sclk, HIGH);
    }
}

void TM74HC595LedTube::fastSend(const uint8_t &segments, const uint8_t &port){
    // Sends the character 'segments' to the digit 'port' of the display
    // Content and Port must be sent in two sequencial parts, character first, port second
    // so this overloaded two char fastSend() method uses the one char fastSend() method twice and then moves
    // up the RCLK pin to present the content in the shift register. This method doesn't add time delays, 
    //So this is the method suggested to be called from an ISR to keep the ISR time consumed to the lowest

    digitalWrite(_rclk, LOW);
    fastSend(segments);
    fastSend(port);
    digitalWrite(_rclk, HIGH);
}

bool TM74HC595LedTube::print(String text){
    bool displayable{true};
    int position{-1};
    String tempText{""};
    int temp7SegData[4]{0xFF, 0xFF, 0xFF, 0xFF};
    int tempDpData[4]{0xFF, 0xFF, 0xFF, 0xFF};

    // Finds out if there are '.' in the string to display, creates a mask to add them to the display
    // and takes them out of the string to process the chars/digits
    for(unsigned int i{0}; i < text.length(); ++i){
        if (text.charAt(i) != '.')
            tempText += text.charAt(i);
        else{
            if (i == 0 || text.charAt(i-1) == '.')
                tempText += " ";
            if(tempText.length()<=4)
                tempDpData[3-(tempText.length()-1)] = 0x7F;      
        }
    }
    text = tempText;

    if (text.length() <= 4){
        for (unsigned int i {0}; i < text.length(); ++i){
            position = _charSet.indexOf(text.charAt(i));
            if (position > -1) {
                // Character found for translation
                temp7SegData[3 - i] = _charLeds[position];
            }
            else {
                displayable = false;
                break;
            }
        }
    }
    else {
        displayable = false;
    }

    if (displayable) {
        for (int i{0}; i < 4; ++i)
            _digit[i] = temp7SegData[i] & tempDpData[i];
    }
    return displayable;
}

bool TM74HC595LedTube::print(const int &value, bool rgtAlgn, bool zeroPad){
    bool displayable{true};
    String readOut{""};

    if ((value < -999) || (value > 9999)) {
        clear();
        displayable = false;
    }
    else {
        readOut = String(abs(value));
        if (rgtAlgn) {
            if (zeroPad)
                readOut = "0000" + readOut;
            else
                readOut = "    " + readOut;

            if (value >= 0)
                readOut = readOut.substring(readOut.length() - 4);
            else
                readOut = readOut.substring(readOut.length() - 3);
        }
        if (value < 0)
            readOut = "-" + readOut;
        print(readOut);
    }

    return displayable;
}

bool TM74HC595LedTube::print(const double &value, const unsigned int &decPlaces, bool rgtAlgn, bool zeroPad){
    bool displayable{true};
    String readOut{""};
    String pad{""};
    int start{0};

    if (decPlaces == 0)
        displayable = print(int(value), rgtAlgn, zeroPad);
    else if ((value < -999) || (value > 9999) || (decPlaces > 4)) {
        displayable = false;
        clear();
    }
    else if ((decPlaces + String(int(value)).length()) > (((value < 0) && (value > (-1))) ? 3 : 4)) {
        displayable = false;
        clear();
    }
    else {
        if (value < 0 && value > -1)
            readOut = "-";
        readOut += String(int(value)) + ".";
        start = String(value).indexOf('.') + 1;
        readOut += (String(value) + "0000").substring(start, start + decPlaces);

        if (rgtAlgn) {
            if (readOut.length() < 5) {
                if (value < 0)
                    pad += "-";
                if (zeroPad)
                    pad += "0000";
                else
                    pad += "    ";
                if (value < 0)
                    readOut = pad.substring(0, 5 - (readOut.length() - 1)) + readOut.substring(1);
                else
                    readOut = pad.substring(0, 5 - (readOut.length())) + readOut;
                readOut = readOut.substring(0, 5);
            }
        }

        displayable = print(readOut);
    }

    return displayable;
}

bool TM74HC595LedTube::gauge(const int &level, char label){
    bool displayable{true};
    String readOut{""};
    if ((level < 0) || (level > 3)) {
        clear();
        displayable = false;
    }
    else {
        readOut += label;
        if (readOut == "")
            readOut = " ";
        switch (level) {
            case 0:
                readOut += "   ";
                break;
            case 1:
                readOut += "_  ";
                break;
            case 2:
                readOut += "_= ";
                break;
            case 3:
                readOut += "_=~";
                break;
        };
        displayable = print(readOut);
    }

    return displayable;
}

bool TM74HC595LedTube::gauge(const double &level, char label) {
    bool displayable{true};
    int intLevel{0};

    if ((level < 0.0) || (level > 1.0)) {
        clear();
        displayable = false;
    }
    else {
        if (level < 0.25)
            intLevel = 0;
        else if (level < 0.50)
            intLevel = 1;
        else if (level < 0.75)
            intLevel = 2;
        else
            intLevel = 3;
        displayable = gauge(intLevel, label);
    }

    return displayable;
}

bool TM74HC595LedTube::begin()
{
    //Verify if the timer interrupt service was started by checking if there are displays added to the pointers vector
    bool serviceStarted {false};
    for(uint8_t i {0}; i < MAX_PTR_ARRAY; i++)
        if (instancesList[i] != nullptr){
            serviceStarted = true;
            break;
        }
    if (!serviceStarted){
        //Initialize the Interrupt timer
        Timer1.attachInterrupt(intRefresh);
        Timer1.initialize(2000);
    }
    
    // Include the object's pointer to the array of pointers to be serviced by the ISR of a timer, 
    // if there's available space to hook the object will return true
    bool result {false};
    for(uint8_t i {0}; i < MAX_PTR_ARRAY; i++)
        if (instancesList[i] == nullptr){
            instancesList[i] = _dispInstance;
            result = true;
            break;
        }
        else if (instancesList[i] == _dispInstance){
            // The object pointer was already in the vector, the method will return true because the purpose of including it in te array 
            // was achieved, although some mistake must have been done in the logic to try to include twice the same display
            result = true;
            break;
        }

    if (!serviceStarted){
        Timer1.start();
    }   

    return result;
}

bool TM74HC595LedTube::stop() {
    //This object's pointer will be deleted from the arrays of pointers. If the array has no more valid pointers the timer will be stopped to avoid loosing processing time.
    
    bool pointersFound(false);
    bool result {false};

    for(uint8_t i {0}; i < MAX_PTR_ARRAY; i++)
        if (instancesList[i] == _dispInstance){
            instancesList[i] = nullptr;
            result = true;
        }
        else if (instancesList[i] != nullptr){
            // There are still objects pointers in the vector, so the refresh display services must continue active
            pointersFound = true;
        }

    if (!pointersFound){
        //There are no more display instances active, there's no point in keeping the ISR active, the timer is stopped and the interrupt service detached
        Timer1.stop();
        Timer1.detachInterrupt();
    }   

    return result;
}

bool TM74HC595LedTube::blink(){
    _blink = true;
    _blinkTimer = 0;
    _blinkShowOn = false;

    return true;
}

bool TM74HC595LedTube::noBlink(){
    _blink = false;
    _blinkTimer = 0;
    _blinkShowOn = true;

    return true;
}

bool TM74HC595LedTube::isBlinking(){
    return _blink;
}

bool TM74HC595LedTube::setBlinkRate(const unsigned long &newRate) {
    if ((newRate >= _minBlinkRate) && newRate <= _maxBlinkRate) {
        //if the new blinkRate is in the accepted range, change the blinkRate
        _blinkRate = newRate;
        return true;
    }
    //The value was outside valid range, keep the existing rate and report the error by returning false
    return false;
}

void TM74HC595LedTube::fastRefresh(){
    static int firstRefreshed{0};

    if (_blink == true) {
        if (_blinkShowOn == false) {
            if (_blinkTimer == 0) {
                // turn off all digits
                fastSend(0xFF, 0b0001);
                fastSend(0xFF, 0b0010);
                fastSend(0xFF, 0b0100);
                fastSend(0xFF, 0b1000);

                _blinkTimer = millis();
            }
            else if ((millis() - _blinkTimer) > _blinkRate) {
                _blinkTimer = 0;
                _blinkShowOn = true;
            }
        }
        else {
            if (_blinkTimer == 0) {
                _blinkTimer = millis();
            }
            else if ((millis() - _blinkTimer) > _blinkRate) {
                _blinkTimer = 0;
                _blinkShowOn = false;
            }
        }
    }

    if ((_blink == false) || (_blinkShowOn == true)) {
        fastSend(_digit[firstRefreshed], 1 << firstRefreshed);
        firstRefreshed++;
        if (firstRefreshed == 4)
            firstRefreshed = 0;
    }
    return;
}
