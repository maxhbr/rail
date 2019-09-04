// #include <SPI.h>
#include <Wire.h>
#include <SSD1306.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "SSD1306Wire.h"

#include "Display.h"

#define SSD1306_I2C_ADDRESS 0x3b

Display::Display(int _pin_sda,
                 int _pin_sck)
    : display(SSD1306_I2C_ADDRESS, _pin_sda, _pin_sck, GEOMETRY_128_32)
{
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 0, "Hello World!");
}
