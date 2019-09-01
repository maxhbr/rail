#include "IrSony.h"
#include <IRremoteESP8266.h>               //Don't worry about ESP8266 library, it works on ESP32
#include <IRsend.h>

// see: https://diydrones.com/forum/topics/sony-a7-infrared-codes
// Photo     740239    B4B8F   // Shutter | take photo
// VID       76687     12B8F   // Start | stop video recording
// DISP      166799    28B8F   // Display change cycles round
// Menu      117647    1CB8F   // Enter menu | leave menu
// MenuU     379791    5CB8F   // Menu up
// menuD     904079    DCB8F   // Menu down
// menuR     1035151   FCB8F   // Menu right
// menuL     510863    7CB8F   // Menu left
// OK        641937    9CB91   // Menu OK
// Z+        338831    52B8F   // Zoom in
// Z-        863119    D2B8F   // Zoom out

IrSony::IrSony(int _pin)
{
    pin = _pin;
    pinMode(pin, OUTPUT);
}

void IrSony::shoot(int microseconds)
{
    Serial.println("IrSony::shoot");
    IRsend irsend(pin, true); // TODO: should be in field
    for (int i=0; i<3; i++){
        irsend.sendSony(0xB4B8F, 20);
    }
    delayMicroseconds(microseconds);
}
