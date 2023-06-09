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

void TM74HC595LedTube::refresh(){
    static int firstRefreshed {0};

    updBlinkState();
    updWaitState();

    if((_blinking == false)||(_blinkShowOn == true)){
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
  _digit[0] = _digit[1] = _digit[2] = _digit[3] = _space;
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

    if ((value < MIN_DISP_VALUE) || (value > MAX_DISP_VALUE)) {
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
    else if ((value < MIN_DISP_VALUE) || (value > MAX_DISP_VALUE) || (decPlaces > 4)) {
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
    bool result {false};
    if (!_blinking){
    _blinkTimer = 0;
    _blinkShowOn = false;
    _blinking = true;
    result = true;
    }

    return result;
}

bool TM74HC595LedTube::blink(const unsigned long &onRate, const unsigned long &offRate){
    bool result {false};
    if (!_blinking){
        if (offRate == 0)
            result = setBlinkRate(onRate, onRate);
        else
            result = setBlinkRate(onRate, offRate);
        
        if (result)
            result = blink();
    }

    return result;
}

bool TM74HC595LedTube::noBlink(){
    bool result {false};
    if(_blinking){
        _blinking = false;
        _blinkTimer = 0;
        _blinkShowOn = true;
        result = true;
    }

    return result;
}

bool TM74HC595LedTube::isBlinking(){
    return _blinking;
}

bool TM74HC595LedTube::setBlinkRate(const unsigned long &newOnRate, const unsigned long &newOffRate){
    bool result {false};
    
    if ((newOnRate >= _minBlinkRate) && newOnRate <= _maxBlinkRate) {
        if ((newOffRate == 0) || ((newOffRate >= _minBlinkRate) && (newOffRate <= _maxBlinkRate))) {
            //if the new blinkRate is in the accepted range, set the blinkRate for symmetric rate
            _blinkOnRate = newOnRate;
            if (newOffRate == 0)
                _blinkOffRate = newOnRate;
            else
                _blinkOffRate = newOffRate;
            result =  true;
        }
    }
    //The value was outside valid range, keep the existing rate and report the error by returning false
    
    return result;
  
}

void TM74HC595LedTube::fastRefresh(){

    updBlinkState();
    updWaitState();

    if ((_blinking == false) || (_blinkShowOn == true)) {
        fastSend(_digit[firstRefreshed], 1 << firstRefreshed);
        firstRefreshed++;
        if (firstRefreshed == 4)
            firstRefreshed = 0;
    }
    return;
}

uint8_t TM74HC595LedTube::getInstanceNbr(){
    return _dispInstNbr;
}

unsigned long  TM74HC595LedTube::getMinBlinkRate(){
    return _minBlinkRate;
}

unsigned long TM74HC595LedTube::getMaxBlinkRate(){
        return _maxBlinkRate;
    }

void TM74HC595LedTube::updBlinkState(){
    if (_blinking == true){
        if (_blinkShowOn == false) {
            if (_blinkTimer == 0){
                //turn off all digits by sending directly a blank to each port, without affecting the _digit[] buffer
                send(_space, 0b0001);
                send(_space, 0b0010);
                send(_space, 0b0100);
                send(_space, 0b1000);

                _blinkTimer = millis();
            }
            else if((millis() - _blinkTimer)> _blinkOffRate){
                _blinkTimer = 0;
                _blinkShowOn = true;
            }
        }
        else{
            if (_blinkTimer == 0){
                _blinkTimer = millis();
            }
            else if((millis() - _blinkTimer) > _blinkOnRate){
                _blinkTimer = 0;
                _blinkShowOn = false;
            }
        }
    }

    return;
}

bool TM74HC595LedTube::write(const uint8_t &segments, const uint8_t &port){
    bool result {false};
    
    if (port <= 3){
        _digit[port] = segments;
        result = true;
    }
    
    return result;
}

bool TM74HC595LedTube::write(const String &character, const uint8_t &port){
    bool result {false};
    int position {-1};
    
    if (port <= 3){
            position = _charSet.indexOf(character);
            if (position > -1) {
                // Character found for translation
                _digit[port] = _charLeds[position];
                result = true;
            }
    }

    return result;
}

bool TM74HC595LedTube::isWaiting(){
    return _waiting;
}

bool TM74HC595LedTube::noWait(){
    bool result {false};
    if (_waiting){
        _waiting = false;
        _waitTimer = 0;
        clear();
        result = true;
    }
    return result;
}

bool TM74HC595LedTube::setWaitRate(const unsigned long &newWaitRate)
{
    bool result {false};
    if ((newWaitRate >= _minBlinkRate) && newWaitRate <= _maxBlinkRate) {
        //if the new waitRate is within the accepted range, set it
        _waitRate = newWaitRate;
        result =  true;        
    }
    //The value was outside valid range, keep the existing rate and report the error by returning false
    
    return result;
}

bool TM74HC595LedTube::wait(const unsigned long &newWaitRate){
   bool result {true};
   
   if (_waiting == false){
      if (newWaitRate != 0){
         if ((newWaitRate >= _minBlinkRate) && (newWaitRate <= _maxBlinkRate)){
            _waitRate = newWaitRate;         
         }
         else{
            result = false;
         }
      }
      if (result == true){
         _waitTimer = 0;
         _waitCount = 0;
         _waiting = true;
      }
   }
   else{
      result = false;
   }

   return result;
}

void TM74HC595LedTube::updWaitState(){
   if (_waiting == true){
      if (_waitTimer == 0){
         _digit[0] = _digit[1] = _digit[2] = _digit[3] = _space;
         _waitTimer = millis();
      }
      else if((millis() - _waitTimer) > _waitRate){
         _digit[0] = _digit[1] = _digit[2] = _digit[3] = _space;
         switch(_waitCount){
            case 4:
               _digit[0] = _waitChar;
            case 3:
               _digit[1] = _waitChar;
            case 2:
               _digit[2] = _waitChar;
            case 1:
               _digit[3] = _waitChar;
            default:
               break;
         }
         _waitCount++;
         if (_waitCount == 5)
            _waitCount = 0;

         _waitTimer = millis();
      }
   }

   return;
}

ClickCounter::ClickCounter(uint8_t ccSclk, uint8_t ccRclk, uint8_t ccDio, bool rgthAlgn, bool zeroPad)
:TM74HC595LedTube(ccSclk, ccRclk, ccDio), _countRgthAlgn {rgthAlgn}, _countZeroPad {zeroPad}
{
    //Class constructor
}

bool ClickCounter::countBegin(int startVal){
   bool result{false};

    if (TM74HC595LedTube::begin() == true){
        result = countRestart(startVal);
        if (result)
            _beginStartVal = startVal;
    }

   return result;
}

bool ClickCounter::countReset(){
    return countRestart(_beginStartVal);
}
    
bool ClickCounter::countRestart(int restartValue){
   bool result{false};

   if ((restartValue >= MIN_DISP_VALUE) && (restartValue <= MAX_DISP_VALUE)){
      _count = restartValue;
      result = updDisplay();
   }

   return result;
}

bool ClickCounter::countStop(){
    
    return TM74HC595LedTube::stop();
}

bool ClickCounter::countUp(int qty){
    bool result {false};
    qty = abs(qty);

    if((_count + qty) <= MAX_DISP_VALUE){
        _count += qty;
        result = updDisplay();
    }

    return result;
}

bool ClickCounter::countDown(int qty){
    bool result {false};
    qty = abs(qty);

    if((_count - qty) >= MIN_DISP_VALUE){
        _count -= qty;
        result = updDisplay();
    }

    return result;
}

bool ClickCounter::countToZero(int qty){
    bool result {false};

    if (_count > 0)
        result = countDown(qty);
    else if (_count < 0)
        result = countUp(qty);
    
    return result;
}

bool ClickCounter::updDisplay(){

    return print(_count, _countRgthAlgn, _countZeroPad);
   }

int ClickCounter::getCount(){

    return _count;
}

int ClickCounter::getStartVal(){

    return _beginStartVal;
}

bool ClickCounter::setBlinkRate(const unsigned long &newOnRate, const unsigned long &newOffRate){

    return TM74HC595LedTube::setBlinkRate(newOnRate, newOffRate);
}

bool ClickCounter::blink(){

    return TM74HC595LedTube::blink();
}

bool ClickCounter::blink(const unsigned long &onRate, const unsigned long &offRate){

    return TM74HC595LedTube::blink(onRate, offRate);
}

bool ClickCounter::noBlink(){

    return TM74HC595LedTube::noBlink();
}
