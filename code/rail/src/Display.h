#ifndef DISPLAY_H
#define DISPLAY_H

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class Display
{
private:
    Adafruit_SSD1306 display;

public:
    Display();
    void printHello();
};

#endif /* DISPLAY_H */
