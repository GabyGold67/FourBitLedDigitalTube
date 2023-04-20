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

void  TM74HC595LedTube::refresh(){
  send(_data[0], 0b0001);
  send(_data[1], 0b0010);
  send(_data[2], 0b0100);
  send(_data[3], 0b1000);
  return;
}

void TM74HC595LedTube::clear(){
  //Cleans the contents of the internal DATA array display buffer (All leds off for all digits)
  _data[0]= _data[1]= _data[2]= _data[3]= 0xFF;
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
            _data[i] = temp7SegData[i] & tempDpData[i];  
    }
    return displayable;
}

bool TM74HC595LedTube::gauge (int level, char label){
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

bool TM74HC595LedTube::gauge (double level, char label){
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
