#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "Display.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels



#define SSD1306_I2C_ADDRESS 0x3c

Display::Display()
    : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1)
{

    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3D)) { // Address 0x3D for 128x64
        Serial.println(F("SSD1306 allocation failed"));
        for(;;);
    }
    Serial.println(F("SSD1306 allocation succeeded"));

    delay(20000);
    display.clearDisplay();
    Serial.println("Display is initialized");
}

void Display::printHello() {
    Serial.println("Display::printHello()");
    display.clearDisplay();

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 10);
    // Display static text
    display.println("Hello World");
    display.display();

    delay(20000);
}
