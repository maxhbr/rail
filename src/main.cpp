#include <Arduino.h>

#include "PhotoRail.h"

const int button_move_forward = 16;
const int button_move_backward = 4;
const int button_start = 17;
const int button_alt = 5;
const int status_led = 15;

PhotoRail rail(32, 33, 25, 26, 27, 14, 12, 2);

void setup() {
    Serial.begin(9600);

    pinMode(button_move_forward, INPUT);
    pinMode(button_move_backward, INPUT);
    pinMode(button_start, INPUT);
    pinMode(status_led, OUTPUT);

    digitalWrite(status_led, LOW);
    delay(250);
    digitalWrite(status_led, HIGH);
    delay(250);
    digitalWrite(status_led, LOW);
}

void loop() {
    if (digitalRead(button_start) == HIGH)
    {
        rail.stack(100);
    }
    else if (digitalRead(button_move_forward) == HIGH)
    {
        rail.move(32, 3);
    }
    else if (digitalRead(button_move_backward) == HIGH)
    {
        rail.move(-32, 3);
    }
    else if (digitalRead(button_alt) == HIGH)
    {
        rail.log_state();
        digitalWrite(status_led, HIGH);
        delay(1000);
        digitalWrite(status_led, LOW);
    }
}
