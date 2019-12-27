#include "Arduino.h"
#include "seven_segment.h"

SevenSegment::SevenSegment(int *digitPins, int *segmentPins, uint8_t dotPin)
{
    for(int i=0;i<4;i++)
    {
        pinMode(digitPins[i], OUTPUT);
        digitalWrite(digitPins[i], 1);
        _digitPins[i] = digitPins[i];

        pinMode(segmentPins[i], OUTPUT);
        digitalWrite(segmentPins[i], 0);
        _segmentPins[i] = segmentPins[i];
    }

    pinMode(dotPin, OUTPUT);
    digitalWrite(dotPin, 0);
    _dotPin = dotPin;
}

void SevenSegment::decodeNumber(uint8_t number)
{
    digitalWrite(_segmentPins[0], number & 8);
    digitalWrite(_segmentPins[1], number & 4);
    digitalWrite(_segmentPins[2], number & 2);
    digitalWrite(_segmentPins[3], number & 1);
}

void SevenSegment::activateDigit(uint8_t digit, unsigned long interval)
{
    unsigned long now = millis();
    digitalWrite(_digitPins[digit], 0);

    while(millis() < now + interval) {}

    digitalWrite(_digitPins[digit], 1);
}

void SevenSegment::displayNumber(unsigned int number, unsigned long interval, uint8_t dotPlace = 4)
{
    if(number < 10000)
    {
        if(number != _number) setNumber(number);

        bool dot = false;
        uint8_t a = 0;
        uint64_t tmp = 0;

        unsigned long now = millis();
        if(dotPlace < 4) dot = true;

        while(millis() < now + interval)
        {
            for(int i=0;i<4;i++)
            {
                if(dot && i == dotPlace) digitalWrite(_dotPin, 1);
                decodeNumber(_number[i]);

                SevenSegment::activateDigit(i, 3);
                digitalWrite(_dotPin, 0);
            }

        }
    }
}

void SevenSegment::setNumber(unsigned int number)
{
    uint8_t temp = 0;

    _number[3] = number/1000;
    number -= _number[3]*1000;
    
    _number[2] = number / 100;
    number -= _number[2]*100;

    _number[1] = number / 10;
    number -= _number[1]*10;
    
    _number[0] = number;
}