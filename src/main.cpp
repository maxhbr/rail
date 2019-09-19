#include <Arduino.h>

#include "Rail.h"
#include "IrSony.h"

const int button_move_forward = 16;
const int button_move_backward = 4;
const int button_single_step = 17;

Rail rail(32, 33, 25, 26, 27, 14, 12);
// IrSony ir_sony(0);

void setup() {
    Serial.begin(9600);

    pinMode(button_move_forward, INPUT);
    pinMode(button_move_backward, INPUT);
    pinMode(button_single_step, INPUT);
}

void loop() {
    if (digitalRead(button_single_step) == HIGH)
    {
        // ir_sony.shoot();
        rail.move(15, 0);
        delay(700);
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
