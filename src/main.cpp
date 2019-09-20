#include <Arduino.h>

#include "PhotoRail.h"

const int button_move_forward = 16;
const int button_move_backward = 4;
const int button_single_step = 17;

PhotoRail rail(32, 33, 25, 26, 27, 14, 12, 2);

void setup() {
    Serial.begin(9600);

    pinMode(button_move_forward, INPUT);
    pinMode(button_move_backward, INPUT);
    pinMode(button_single_step, INPUT);
}

void loop() {
    if (digitalRead(button_single_step) == HIGH)
    {
        rail.stack(10);
    }
    else if (digitalRead(button_move_forward) == HIGH)
    {
#ifdef DEBUG_BUILD
        Serial.write("+");
#endif
        rail.move(32, 3);
#ifdef DEBUG_BUILD
        rail.log_state();
#endif
    }
    else if (digitalRead(button_move_backward) == HIGH)
    {
#ifdef DEBUG_BUILD
        Serial.write("-");
#endif
        rail.move(-32, 3);
#ifdef DEBUG_BUILD
        rail.log_state();
#endif
    }
}
