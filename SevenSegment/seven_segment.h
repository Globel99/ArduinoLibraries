#ifndef seven_segment_h
#define seven_segmetn_h

#include "Arduino.h"

class SevenSegment
{
    public:
        SevenSegment(int *digitPins, int *segmentPins, uint8_t dotPin);
        void decodeNumber(uint8_t number);
        void activateDigit(uint8_t digit, unsigned long interval);
        void displayNumber(unsigned int number, unsigned long interval, uint8_t dotPlace = 4);

    private:
        uint8_t _digitPins[4];
        uint8_t _segmentPins[4];
        uint8_t _dotPin;
        uint8_t _number[4];

        void setNumber(unsigned int number);
};

#endif