#include <Arduino.h>
#include <FourBitLedDigitalTube.h>
#include <TimerOne.h>

uint8_t TM74HC595LedTube::_displaysCount = 0;
uint8_t TM74HC595LedTube::_dspPtrArrLngth = 10;
TM74HC595LedTube** TM74HC595LedTube::_instancesLstPtr = nullptr;
bool TM74HC595LedTube::_intRfrshSrvcStrtd = false;

TM74HC595LedTube::TM74HC595LedTube()
{
}

TM74HC595LedTube::TM74HC595LedTube(uint8_t sclk, uint8_t rclk, uint8_t dio, bool commAnode, uint8_t dspDigits)
    :_sclk{sclk}, _rclk{rclk}, _dio{dio}, _commAnode{commAnode}, _dspDigits{dspDigits}, _digitPosPtr{new uint8_t[dspDigits]}, _digitPtr{new uint8_t[dspDigits]}, _blinkMaskPtr{new bool [dspDigits]}
{
    pinMode(_sclk, OUTPUT);
    pinMode(_rclk, OUTPUT);
    pinMode(_dio, OUTPUT);
    setAttrbts();
    clear();
}

TM74HC595LedTube::~TM74HC595LedTube(){
    stop(); //Frees the slot in the pointers array for the refresh timer, and stops the timer if there are no valid pointers left
    delete [] _digitPtr;        //Free the resources of the digits buffer
    delete [] _digitPosPtr;
    delete [] _blinkMaskPtr;    //Free the resources of the blink mask buffer
    --_displaysCount;
}

bool TM74HC595LedTube::begin(){
    bool result {false};
    int frstFreeSlot{-1};

    if (!_intRfrshSrvcStrtd){   //Verify if the timer interrupt service was started 
        //Initialize the Interrupt timer
        Timer1.attachInterrupt(intRefresh);
        Timer1.initialize(2000);
    }

    // Include the object's pointer to the array of pointers to be serviced by the ISR of a timer, 
    // If this is the first instance created, create the array of instances in Heap    
    if(_instancesLstPtr == nullptr){
        _instancesLstPtr = new TM74HC595LedTube* [_dspPtrArrLngth];
        for(int i{0}; i < _dspPtrArrLngth; i++)
            *(_instancesLstPtr + i) = nullptr;
    }

    // Check if pointer to this object was already in the list of pointers, add otherwise
    for(uint8_t i {0}; i < _dspPtrArrLngth; i++){
        if (*(_instancesLstPtr + i) == nullptr){
            if(frstFreeSlot == -1)
                frstFreeSlot = i;
        }
        else if (*(_instancesLstPtr + i) == _dispInstance){
            result = true;
            break;
        }        
    }
    if(!result)
        if(frstFreeSlot > -1){
            *(_instancesLstPtr + frstFreeSlot) = _dispInstance;
            result = true;
        }

    if (!_intRfrshSrvcStrtd){
        Timer1.start();
        _intRfrshSrvcStrtd = true;
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
    unsigned long newOffRate{offRate};

    if (!_blinking){
        if (newOffRate == 0)
            newOffRate = onRate;
        if (setBlinkRate(onRate, newOffRate))
            result = blink();
    }

    return result;
}

void TM74HC595LedTube::clear(){
  //Cleans the contents of the internal display buffer (All leds off for all digits)
    for (int i{0}; i < _dspDigits; i++){
        *(_digitPtr + i) = _space;
    }
    refresh();

    return;
}

bool TM74HC595LedTube::doubleGauge(const int &levelLeft, const int &levelRight, char labelLeft, char labelRight){
    bool displayable{true};
    String readOut{""};

    if ((levelLeft < 0) || (levelRight < 0) || (levelLeft > 3) || (levelRight > 3)) {
        clear();
        displayable = false;
    }
    else {
        readOut += labelLeft;
        if (readOut == "")
            readOut = " ";
        switch (levelLeft) {
            case 0:
                readOut += " ";
                break;
            case 1:
                readOut += "_";
                break;
            case 2:
                readOut += "=";
                break;
            case 3:
                readOut += "~";
                break;
        };
        if(_dspDigits > 4){
            for (int i{0}; i < (_dspDigits-4)/2; i++)
                readOut += " ";
        }
        readOut += labelRight;
        if (readOut.length() == 2)
            readOut += " ";
        switch (levelRight) {
            case 0:
                readOut += " ";
                break;
            case 1:
                readOut += "_";
                break;
            case 2:
                readOut += "=";
                break;
            case 3:
                readOut += "~";
                break;
        };
        displayable = print(readOut);
    }

    return displayable;
}

void TM74HC595LedTube::fastRefresh(){
   bool tmpLogic {true};

   updBlinkState();
   updWaitState();
   if ((_blinking == false) || (_blinkShowOn == true)) {
      fastSend(*(_digitPtr + _firstRefreshed), uint8_t(1) << *(_digitPosPtr + _firstRefreshed));
   }
   else if(_blinking && !_blinkShowOn){
        for(uint8_t i{0}; i<_dspDigits; i++)
            tmpLogic = tmpLogic && *(_blinkMaskPtr + i);
        if (!tmpLogic){   //At least one digit is set NOT TO BLINK
            if(!*(_blinkMaskPtr + _firstRefreshed))
                fastSend(*(_digitPtr + _firstRefreshed), uint8_t(1) << *(_digitPosPtr + _firstRefreshed));
        }
    }
   ++_firstRefreshed;
   if (_firstRefreshed == _dspDigits)
      _firstRefreshed = 0;

    return;
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

    return;
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

    return;
}

bool TM74HC595LedTube::gauge(const int &level, char label){
    bool displayable{true};
    String readOut{""};

    clear();    // Ensures a clean display in case it's not displayable, and also trailing spaces if _dspDigits > 4
    if (((level < 0) || (level > 3)) || (_dspDigits < 4)) {
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

    if (((level < 0.0) || (level > 1.0)) || (_dspDigits < 4)){
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

uint8_t TM74HC595LedTube::getDigitsQty(){

    return _dspDigits;
}

long TM74HC595LedTube::getDspValMax(){

    return _dspValMax;
}

long TM74HC595LedTube::getDspValMin(){

    return _dspValMin;
}

uint8_t TM74HC595LedTube::getInstanceNbr(){

    return _dispInstNbr;
}

unsigned long TM74HC595LedTube::getMaxBlinkRate(){
    
    return _maxBlinkRate;
}

unsigned long  TM74HC595LedTube::getMinBlinkRate(){

    return _minBlinkRate;
}

void TM74HC595LedTube::intRefresh(){
    //ISR called by Timer1 to keep the display lit by calling each display's fastRefresh() method
    for(uint8_t i {0}; i < _dspPtrArrLngth; i++){
        if (*(_instancesLstPtr + i) != nullptr)
            (*(_instancesLstPtr + i)) -> fastRefresh();
    }    

    return;
}

bool TM74HC595LedTube::isBlinking(){

    return _blinking;
}

bool TM74HC595LedTube::isWaiting(){

    return _waiting;
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

bool TM74HC595LedTube::print(String text){
    bool displayable{true};
    int position{-1};
    String tempText{""};
    uint8_t temp7SegData[_dspDigits];
    uint8_t tempDpData[_dspDigits];

    for (int i{0}; i < _dspDigits; i++){
        temp7SegData[i] = _space;
        tempDpData[i] = _space;
    }
    // Finds out if there are '.' in the string to display, creates a mask to add them to the display
    // and takes them out of the string to process the chars/digits
    for(unsigned int i{0}; i < text.length(); ++i){
        if (text.charAt(i) != '.')
            tempText += text.charAt(i);
        else{
            if (i == 0 || text.charAt(i - 1) == '.')    //If the text to display starts with a '.' or have 2 or more consecutive '.'chars, spaces must be added
                tempText += " ";
            if(tempText.length() <= _dspDigits)
                tempDpData[_dspDigits - tempText.length()] = _dot;      
        }
    }
    text = tempText;

    if (text.length() <= _dspDigits){
        for (unsigned int i {0}; i < text.length(); ++i){
            position = _charSet.indexOf(text.charAt(i));
            if (position > -1) {
                // Character found for translation
                temp7SegData[(_dspDigits - 1) - i] = _charLeds[position];
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
        for (uint8_t i{0}; i < _dspDigits; ++i)
            *(_digitPtr + i) = temp7SegData[i] & tempDpData[i];
    }

    return displayable;
}

bool TM74HC595LedTube::print(const long &value, bool rgtAlgn, bool zeroPad){
    bool displayable{true};
    String readOut{""};
        
    if ((value < _dspValMin) || (value > _dspValMax)) {
        clear();
        displayable = false;
    }
    else {
        readOut = String(abs(value));
        if (rgtAlgn) {
            if (zeroPad)
                readOut = _zeroPadding + readOut;
            else
                readOut = _spacePadding + readOut;

            if (value >= 0)
                readOut = readOut.substring(readOut.length() - _dspDigits);
            else
                readOut = readOut.substring(readOut.length() - (_dspDigits - 1));
        }
        if (value < 0)
            readOut = "-" + readOut;
        displayable = print(readOut);
    }

    return displayable;
}

bool TM74HC595LedTube::print(const double &value, const unsigned int &decPlaces, bool rgtAlgn, bool zeroPad){
    bool displayable{true};
    String readOut{""};
    String pad{""};
    int start{0};

    if (decPlaces == 0)
        displayable = print(long(value), rgtAlgn, zeroPad);
    else if ((value < _dspValMin) || (value > _dspValMax) || (decPlaces > _dspDigits)) {
        displayable = false;
        clear();
    }
    else if (long((decPlaces + String(long(value)).length())) > (((value < 0) && (value > (-1))) ? (_dspDigits - 1) : _dspDigits)) {
        displayable = false;
        clear();
    }
    else {
        if (value < 0 && value > -1)
            readOut = "-";
        readOut += String(long(value)) + ".";
        start = String(value).indexOf('.') + 1;
        readOut += (String(value) + _zeroPadding).substring(start, start + decPlaces);
        if (rgtAlgn) {
            if ((long)(readOut.length()) < _dspDigits + 1) {
                if (value < 0)
                    pad += "-";
                if (zeroPad)
                    pad += _zeroPadding;
                else
                    pad += _spacePadding;
                if (value < 0)
                    readOut = pad.substring(0, (_dspDigits+1) - (readOut.length()-1)) + readOut.substring(1);
                else
                    readOut = pad.substring(0, (_dspDigits+1) - (readOut.length())) + readOut;
                readOut = readOut.substring(0, _dspDigits+1);
            }
        }
        displayable = print(readOut);
    }

    return displayable;
}

void TM74HC595LedTube::refresh(){
   bool tmpLogic {true};
   uint8_t tmpDigToSend{0};
    updBlinkState();
    updWaitState();

    if((_blinking == false)||(_blinkShowOn == true)){
        for (int i {0}; i < _dspDigits; i++){
            tmpDigToSend = *(_digitPtr + ((i + _firstRefreshed) % _dspDigits));
            send(tmpDigToSend, 1 << *(_digitPosPtr + ((i + _firstRefreshed) % _dspDigits)));
        }
    }
    else if(_blinking && !_blinkShowOn){
      for(int i{0}; i < _dspDigits; i++)
         tmpLogic = tmpLogic && *(_blinkMaskPtr + ((i + _firstRefreshed) % _dspDigits));
        if (!tmpLogic){   //At least one digit is set NOT TO BLINK
            for (int i {0}; i < _dspDigits; i++){
                if(!*(_blinkMaskPtr + ((i + _firstRefreshed) % _dspDigits))){
                    tmpDigToSend = *(_digitPtr + ((i + _firstRefreshed) % _dspDigits));
                    send(tmpDigToSend, 1 << *(_digitPosPtr + ((i + _firstRefreshed) % _dspDigits)));
                }
            }
        }
    }
    ++_firstRefreshed;
    if (_firstRefreshed == _dspDigits)
        _firstRefreshed = 0;

    return;
}

void TM74HC595LedTube::resetBlinkMask(){
   for (uint8_t i{0}; i < _dspDigits; i++)
      *(_blinkMaskPtr + i) = true;

    return;
}

void TM74HC595LedTube::send(const uint8_t &content){
    //Sends the byte value (char <=> unsigned short int) to the 7-segment display bit by bit
    //by using the shiftOut() function. The time added (or not) to send it bit is unknown, so the total time
    //consumed to shift an entire byte is unknown, issue that must be considered when the method is invoked 
    //from an ISR and multiple times depending on the qty of displays being used
    shiftOut(_dio, _sclk, MSBFIRST, content);

    return;
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

    return;
}

void TM74HC595LedTube::setAttrbts(){
    if(_dspDigits > 1){ //Calculate the minimum integer value displayable with this display's available digits
        _dspValMin = 1;
        for (uint8_t i{0}; i < (_dspDigits - 1); i++)
            _dspValMin *= 10;
        _dspValMin = (-1)*(_dspValMin - 1);   //_dspValMin =(-1)*(_dspValMin - 1);
    }
    else
        _dspValMin = 0;

    _dspValMax = 1; //Calculate the maximum integer value displayable with this display's available digits, create a Zero and a Space padding string for right alignement
    for (uint8_t i{0}; i < _dspDigits; i++){
        _dspValMax *= 10;
        _zeroPadding += "0";
        _spacePadding += " ";
        *(_digitPosPtr + i) = i;    
        *(_blinkMaskPtr + i) = true;
    }
    --_dspValMax;

    _dispInstNbr = _displaysCount++;
    _dispInstance = this;

    if(!_commAnode){
        _waitChar = ~_waitChar;
        _space = ~_space;
        _dot = ~_dot;
        for(int i {0}; i < (int)_charSet.length(); i++)
            _charLeds[i] = ~_charLeds[i];
    }

    return;
}

void TM74HC595LedTube::setBlinkMask(const bool blnkPort[]){
   for (int i{0}; i < _dspDigits; i++)
      *(_blinkMaskPtr + i) = blnkPort[i];

    return;
}

bool TM74HC595LedTube::setBlinkRate(const unsigned long &newOnRate, const unsigned long &newOffRate){
    bool result {false};
    
    if ((newOnRate >= _minBlinkRate) && newOnRate <= _maxBlinkRate) {
        if ((newOffRate == 0) || ((newOffRate >= _minBlinkRate) && (newOffRate <= _maxBlinkRate))) {
            //if the new blinkRate is in the accepted range, set the blinkRate for symmetric rate
            if(_blinkOnRate != newOnRate)
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

bool TM74HC595LedTube::setDigitsOrder(uint8_t* newOrderPtr){
    bool result{true};

    for(int i {0}; i < _dspDigits; i++){
        if (*(newOrderPtr + i) >= _dspDigits){
            result = false;
            break;
        }   
    }
    if (result){
        for(uint8_t i {0}; i < _dspDigits; i++){
            *(_digitPosPtr + i) = *(newOrderPtr + i);
        }
    }

    return result;
}

bool TM74HC595LedTube::setWaitChar (const char &newWaitChar){
    bool result {false};
    int position {-1};

   if(_waitChar != newWaitChar){
      position = _charSet.indexOf(newWaitChar);
      if (position > -1) {
         _waitChar = _charLeds[position];
         result = true;
      }
   }
   else{
      result = true;
   }

    return result;
}

bool TM74HC595LedTube::setWaitRate(const unsigned long &newWaitRate){
    bool result {false};

    if ((newWaitRate >= _minBlinkRate) && newWaitRate <= _maxBlinkRate) {
        //if the new waitRate is within the accepted range, set it
        if(_waitRate != newWaitRate)
         _waitRate = newWaitRate;
        result =  true;        
    }
    //The value was outside valid range, keep the existing rate and report the error by returning false
    
    return result;
}

bool TM74HC595LedTube::stop() {
    //This object's pointer will be deleted from the arrays of pointers. If the array has no more valid pointers the timer will be stopped to avoid loosing processing time.
    bool pointersFound(false);
    bool result {false};

    for(uint8_t i {0}; i < _dspPtrArrLngth; i++)
        if (*(_instancesLstPtr + i) == _dispInstance){
            *(_instancesLstPtr + i) = nullptr;
            result = true;
        }
        else if (*(_instancesLstPtr + i) != nullptr){
            // There are still objects pointers in the vector, so the refresh display services must continue active
            pointersFound = true;
            if(result)
                break;
        }

    if (!pointersFound){
        //There are no more display instances active, there's no point in keeping the ISR active, the timer is stopped and the interrupt service detached
        delete [] _instancesLstPtr;
        _instancesLstPtr = nullptr;
        
        if(_intRfrshSrvcStrtd){   //if the timer still exists and is running, stop and delete
            Timer1.stop();
            Timer1.detachInterrupt();
            _intRfrshSrvcStrtd = false;
        }
    }   

    return result;
}

void TM74HC595LedTube::updBlinkState(){
    if (_blinking == true){
        if (_blinkShowOn == false) {
            if (_blinkTimer == 0){
                //turn off the digits by sending directly a blank to each port, without affecting the _digit[] buffer
                for (int i{0}; i < _dspDigits; i++)
                    send(_space, 0b01 << i);
                _blinkTimer = millis(); //Starts the count for the blinkRate control
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

void TM74HC595LedTube::updWaitState(){
   if (_waiting == true){
      if (_waitTimer == 0){
        for (int i{0}; i < _dspDigits; i++)
            *(_digitPtr + i) = _space;
        _waitTimer = millis();
      }
      else if((millis() - _waitTimer) > _waitRate){
         for (int i{_dspDigits - 1}; i >= 0; i--){

            if(( _dspDigits - i) <= _waitCount)
               *(_digitPtr + i) = _waitChar;
            else
               *(_digitPtr + i) = _space;
         }
         _waitCount++;
         if (_waitCount > _dspDigits)
            _waitCount = 0;
         _waitTimer = millis();
      }
   }

   return;
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

bool TM74HC595LedTube::write(const uint8_t &segments, const uint8_t &port){
    bool result {false};
    
    if (port < _dspDigits){
        *(_digitPtr + port) = segments;
        result = true;
    }
    
    return result;
}

bool TM74HC595LedTube::write(const String &character, const uint8_t &port){
    bool result {false};
    int position {-1};
    
    if (port < _dspDigits){
        position = _charSet.indexOf(character);
        if (position > -1) {
            // Character found for translation
            *(_digitPtr + port) = _charLeds[position];
            result = true;
        }
    }

    return result;
}

//============================================================> Class methods separator

ClickCounter::ClickCounter(uint8_t ccSclk, uint8_t ccRclk, uint8_t ccDio, bool rgthAlgn, bool zeroPad, bool commAnode, const uint8_t dspDigits)
:_display(ccSclk, ccRclk, ccDio, commAnode, dspDigits), _countRgthAlgn {rgthAlgn}, _countZeroPad {zeroPad}
{
    //Class constructor
}

ClickCounter::~ClickCounter(){
    //Class destructor
}

bool ClickCounter::blink(){

    return _display.blink();
}

bool ClickCounter::blink(const unsigned long &onRate, const unsigned long &offRate){

    return _display.blink(onRate, offRate);
}

void ClickCounter::clear(){
    _display.clear();

    return;
}

bool ClickCounter::countBegin(long startVal){
    bool result{false};

    if ((startVal >= _display.getDspValMin()) && (startVal <= _display.getDspValMax())){
        if (_display.begin() == true){
            result = countRestart(startVal);
            if (result)
                _beginStartVal = startVal;
        }
    }

   return result;
}

bool ClickCounter::countDown(long qty){
    bool result {false};
    qty = abs(qty);

    if((_count - qty) >= _display.getDspValMin()){
        _count -= qty;
        result = updDisplay();
    }

    return result;
}

bool ClickCounter::countReset(){

    return countRestart(_beginStartVal);
}
    
bool ClickCounter::countRestart(long restartValue){
   bool result{false};

   if ((restartValue >= _display.getDspValMin()) && (restartValue <= _display.getDspValMax())){
      _count = restartValue;
      result = updDisplay();
   }

   return result;
}

bool ClickCounter::countStop(){
    
    return _display.stop();
}

bool ClickCounter::countToZero(long qty){
    bool result {false};

    if (_count > 0)
        result = countDown(qty);
    else if (_count < 0)
        result = countUp(qty);
    
    return result;
}

bool ClickCounter::countUp(long qty){
    bool result {false};
    qty = abs(qty);

    if((_count + qty) <= _display.getDspValMax()){
        _count += qty;
        result = updDisplay();
    }

    return result;
}

long ClickCounter::getCount(){

    return _count;
}

long ClickCounter::getStartVal(){

    return _beginStartVal;
}

bool ClickCounter::noBlink(){

    return _display.noBlink();
}

bool ClickCounter::setBlinkRate(const unsigned long &newOnRate, const unsigned long &newOffRate){

    return _display.setBlinkRate(newOnRate, newOffRate);
}

bool ClickCounter::updDisplay(){

    return _display.print(_count, _countRgthAlgn, _countZeroPad);
}
