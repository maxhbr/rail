#include <Arduino.h>

#include "PhotoRail.h"

const int button_move_forward = 16;
const int button_move_backward = 4;
const int button_start = 5;
const int button_alt = 17;
const int button_top_1 = 34;
const int button_top_2 = 35;
const int status_led = 2;

PhotoRail rail(32, // pin_direction
               33, // pin_step
               25, // pin_sleep
               26, // pin_reset
               27, // pin_mode2
               14, // pin_mode1
               12, // pin_mode0
               15  // pin_ir
               );

void setup() {
    Serial.begin(9600);

    pinMode(button_move_forward, INPUT);
    pinMode(button_move_backward, INPUT);
    pinMode(button_start, INPUT);
    pinMode(button_alt, INPUT);
    pinMode(button_top_1, INPUT);
    pinMode(button_top_1, INPUT);

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
