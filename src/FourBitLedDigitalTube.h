#ifndef FourBitLedDigitalTube_h
#define FourBitLedDigitalTube_h
#include <Arduino.h>

class TM74HC595LedTube{
private:
    int _sclk;
    int _rclk;
    int _dio;
    int _data[4];
    String charSet {"0123456789AabCcdEFGHIJLlnOoPqrSUY-_=~ "}; //for using indexOf() method
    unsigned short int charLeds[38] = {
    0xC0, //0
    0xF9, //1
    0xA4, //2
    0xB0, //3
    0x99, //4
    0x92, //5
    0x82, //6
    0xF8, //7
    0x80, //8
    0x90, //9 
    0x88, //A
    0xA0, //a
    0x83, //b
    0xC6, //C
    0xA7, //c
    0xA1, //d
    0x86, //E
    0x8E, //F
    0xC2, //G
    0x89, //H
    0xF9, //I
    0xF1, //J
    0xC7, //L
    0xCF, //l
    0xA9, //n
    0xC0, //O
    0xA3, //o
    0x8C, //P
    0x98, //q
    0xAF, //r
    0x92, //S
    0xC1, //U
    0x91, //Y
    0xBF, //Minus -
    0xF7,  //Underscore _
    0xB7,  //Low =
    0xB6,  //~ for Equivalent symbol
    0xFF  //Space
    };
    void send(unsigned char content);
public:
    TM74HC595LedTube(int sclk, int rclk, int dio);
    void clear();    
    void send(unsigned char segments, unsigned char port);
    bool print(String text);
    bool print(int value, bool lftAlgh = false, bool zeroPad = false);
    void refresh();
    bool gauge (int level, char label = ' ');
    bool gauge (double level, char label = ' ');

};



#endif