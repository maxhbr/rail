#ifndef IR_SONY_H
#define IR_SONY_H

#include <Arduino.h>
#include <IRremoteESP8266.h>               //Don't worry about ESP8266 library, it works on ESP32
#include <IRsend.h>

class IrSony
{
private:
    int pin;

public:
    IrSony(int _pin);
    void shoot(int microseconds = 0);
};

#endif /* IR_SONY_H */
