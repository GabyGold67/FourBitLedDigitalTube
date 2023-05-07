#include <Arduino.h>
#include <FourBitLedDigitalTube.h>

TM74HC595LedTube::TM74HC595LedTube(int sclk, int rclk, int dio)
    :_sclk {sclk}, _rclk {rclk}, _dio {dio} 
{
  pinMode(_sclk, OUTPUT);
  pinMode(_rclk, OUTPUT);
  pinMode(_dio, OUTPUT);

  clear();
}

void TM74HC595LedTube::refresh(){
    static int firstRefreshed {0};

    if (_blink == true){
        if (_blinkShowOn == false) {
            if (_blinkTimer == 0){
                //turn off all digits
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
  //Cleans the contents of the internal DATA array display buffer (All leds off for all digits)
  _digit[0]= _digit[1]= _digit[2]= _digit[3]= 0xFF;
  refresh();
}

void TM74HC595LedTube::send(unsigned char content)
{
  //Sends the byte value (char <=> unsigned short int) to the 4 7-segment display bit by bit
    shiftOut(_dio, _sclk, MSBFIRST, content);
}

void TM74HC595LedTube::send(unsigned char segments, unsigned char port)
// Sends the character 'X' to the digit 'port' of the display
// Content and Port must be sent in two sequencial parts, character first, port second
// so this overloaded two char send method uses the one char send method twice and then moves 
//up the RCLK pin to present the content in the shift register
{
  digitalWrite(_rclk, LOW);
  send(segments);
  send(port);
  digitalWrite(_rclk, HIGH);
}

bool TM74HC595LedTube::print(String text){
    //Takes text and tries to display it at the LED tube
    //returns true if found all the characters
    //returns false if at least one char had no representation
    //If no fidel representation is posible blanks the display to avoid false info risk
  
    bool displayable {true};
    int position {-1};
    String tempText {""};
    int temp7SegData[4] {0xFF, 0xFF, 0xFF, 0xFF};
    int tempDpData[4] {0xFF, 0xFF, 0xFF, 0xFF};
  
    //Finds out if there are '.' in the string to display, creates a mask to add them to the display
    //and takes them out of the string to process the chars/digits
    for (unsigned int i{0}; i< text.length(); ++i){
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
            position = charSet.indexOf(text.charAt(i));
            if (position > -1){
                //Character found for translation
                temp7SegData[3-i] = charLeds[position];
            }
            else{
                displayable = false;
                break;
            }
        }
    }
    else{
        displayable = false;
    }
    
    if (displayable){
        for (int i {0}; i < 4; ++i)
            _digit[i] = temp7SegData[i] & tempDpData[i];  
    }
    return displayable;
}

bool TM74HC595LedTube::print (const int &value, bool rgtAlgn, bool zeroPad){
    bool displayable {true};
    String readOut {""};    
    int start {0};

    if((value < -999)||(value>9999)){
        clear();
        displayable = false;
    }
    else{
        readOut = String(abs(value));
        if (rgtAlgn){
            if (zeroPad)
                readOut = "0000" + readOut;
            else
                readOut = "    " + readOut;
            start = readOut.length() - 4;
            if (value >= 0)
                readOut = readOut.substring(start);  
            else
                readOut = "-" + readOut.substring(start + 1);
        }    
    print(readOut);
    }
    
    return displayable;
}

bool TM74HC595LedTube::print (const double &value, const unsigned int &decPlaces, bool rgtAlgn, bool zeroPad){
    bool displayable {true};
    String readOut {""};
    String pad {""};
    int start {0};

    if (decPlaces == 0)
        displayable = print(int(value), rgtAlgn, zeroPad);
    else if ((value < -999)||(value>9999)||(decPlaces > 4)){
        displayable = false;
        clear();
    }
    else if ((decPlaces + String(int(value)).length()) > (((value < 0) && (value > (-1))) ? 3 : 4)){    
        displayable = false;
        clear();        
    }
    else{
            if (value < 0 && value > -1)
                readOut = "-";
            readOut += String(int(value))+ ".";            
            start = String(value).indexOf('.') + 1;
            readOut += (String(value)+"0000").substring(start, start + decPlaces);            

            if (rgtAlgn){
                if (readOut.length() < 5){
                    if (value < 0)
                        pad+= "-";
                    if (zeroPad)
                        pad += "0000";
                    else
                        pad += "    ";
                    if(value<0)
                        readOut = pad.substring(0,5-(readOut.length()-1)) + readOut.substring(1);
                    else
                        readOut = pad.substring(0,5-(readOut.length())) + readOut;
                    readOut = readOut.substring(0,5);
                }
            }

            displayable = print(readOut);
        }

    return displayable;
}

bool TM74HC595LedTube::gauge (const int &level, char label){
    bool displayable {true};
    String readOut {""};
    if((level < 0) || (level > 3)){
        clear();
        displayable = false;
    }
    else{
        readOut += label;
        if (readOut == "")
            readOut = " ";
        switch (level){
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

bool TM74HC595LedTube::gauge (const double &level, char label){
    bool displayable {true};
    int intLevel {0};

    if((level < 0.0) || (level > 1.0)){
        clear();
        displayable = false;
    }
    else{
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

void TM74HC595LedTube::begin(){
  //Timer Interrupt 1 setup, frequency and prescaler should be modified to get
  //the lowest acceptable (no disturbing flicker) display refresh rate
  unsigned int freq01 = 900;
  unsigned int prescaler01 = 256;
  cli();//stop interrupts

  //set timer1 interrupt at 25Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for the selected frequency (defined by the freq and prescaler selected)
  OCR1A = (((16*pow(10,6))/(prescaler01*freq01))-1);// = (16*10^6) / (P1024 * 25Hz) - 1 (must be <65536) = 624  P1024 the prescaler, the 25Hz the intended int frequency
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  
  switch (prescaler01)
  {
  case 1:
    // Set CS10 bit for 1 prescaler
    TCCR1B |= (1 << CS10);  
    break;
  case 8:
    // Set CS11 bit for 8 prescaler
    TCCR1B |= (1 << CS11);  
    break;
  case 64:
    // Set CS10 and CS11 bits for 64 prescaler
    TCCR1B |= (1 << CS11) | (1 << CS10);  
    break;
  case 256:
    // Set CS12 bit for 256 prescaler
    TCCR1B |= (1 << CS12);  
    break;
  default:
    // Set CS10 and CS12 bits for 1024 prescaler
    TCCR1B |= (1 << CS12) | (1 << CS10);  
    break;
  }

  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  sei();//allow interrupts

}

void TM74HC595LedTube::stop(){
    clear();

    cli();//stop interrupts

    //Clean timer1 interrupt setup
    TCCR1A = 0;// set entire TCCR1A register to 0
    TCCR1B = 0;// same for TCCR1B (disables all, including "CTC1 mode on", on the WGM12 bit)
    TCNT1  = 0;//initialize counter value to 0
    
    OCR1A = 0;// set compare match register to 0 for no operation  
    
    TIMSK1 &= ~(1 << OCIE1A);// disable timer compare interrupt

    sei();//allow interrupts
  
    return;
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

bool TM74HC595LedTube::setBlinkRate (const int &newRate){
    if((newRate >= _minBlinkRate) && newRate <= _maxBlinkRate){
        _blinkRate = newRate;
        return true;
    }
    return false;
}

// void TM74HC595LedTube::intRefresh(){
//     return;
// }