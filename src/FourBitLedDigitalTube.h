#ifndef FourBitLedDigitalTube_h
#define FourBitLedDigitalTube_h
#include <Arduino.h>

#define MAX_PTR_ARRAY 4
class TM74HC595LedTube {
    static uint8_t displaysCount;
private:
    const unsigned long _minBlinkRate{100};
    const unsigned long _maxBlinkRate{2000};
    TM74HC595LedTube *_dispInstance;
    int _sclk;
    int _rclk;
    int _dio;
    uint8_t _dispInstNbr{0};
    int _digit[4];
    bool _blink{false};
    unsigned long _blinkTimer{0};
    bool _blinkShowOn{false};
    unsigned long _blinkRate{500};
    String _charSet{"0123456789AabCcdEeFGHhIiJLlnOoPqrStUuY-_=~* ."}; // for using indexOf() method
    unsigned short int _charLeds[45] = {
        0xC0, // 0
        0xF9, // 1
        0xA4, // 2
        0xB0, // 3
        0x99, // 4
        0x92, // 5
        0x82, // 6
        0xF8, // 7
        0x80, // 8
        0x90, // 9
        0x88, // A
        0xA0, // a
        0x83, // b
        0xC6, // C
        0xA7, // c
        0xA1, // d
        0x86, // E
        0x84, // e
        0x8E, // F
        0xC2, // G
        0x89, // H
        0x8B, // h
        0xF9, // I
        0xFB, // i
        0xF1, // J
        0xC7, // L
        0xCF, // l
        0xAB, // n
        0xC0, // O
        0xA3, // o
        0x8C, // P
        0x98, // q
        0xAF, // r
        0x92, // S
        0x87, // t
        0xC1, // U
        0xE3, // u
        0x91, // Y
        0xBF, // Minus -
        0xF7, // Underscore _
        0xB7, // Low =
        0xB6, //~ for Equivalent symbol
        0x9C, // °
        0xFF, // Space
        0x7F  //.
    };
    void send(const uint8_t &content);
    void fastSend(uint8_t content);

public:
    TM74HC595LedTube(uint8_t sclk, uint8_t rclk, uint8_t dio);

    bool begin();
    void stop();
    bool blink();
    bool noBlink();
    void clear();
    void send(const uint8_t &segments, const uint8_t &port);
    void fastSend(const uint8_t &segments, const uint8_t &port);
    bool print(String text);
    bool print(const int &value, bool rgtAlgn = false, bool zeroPad = false);
    bool print(const double &value, const unsigned int &decPlaces, bool rgtAlgn = false, bool zeroPad = false);
    void refresh();
    void fastRefresh();
    bool gauge(const int &level, char label = ' ');
    bool gauge(const double &level, char label = ' ');
    bool setBlinkRate(const unsigned long &newRate);
    bool isBlinking();

};

#endif