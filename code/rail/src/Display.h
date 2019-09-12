#ifndef DISPLAY_H
#define DISPLAY_H

// #include <SSD1306.h>
// #include <Adafruit_SSD1306.h>
#include "SSD1306Wire.h"

class Display
{
private:
    SSD1306Wire display;

public:
    Display(int _pin_sda,
            int _pin_sck);
};

#endif /* DISPLAY_H */
