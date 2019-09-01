#include <Arduino.h>
#include <Ticker.h>

#include "Motor.h"
#include "IrSony.h"

const int button_clockwise = 16;
const int button_counter_clockwise = 4;
const int button_single_step = 17;
const int button_modehalfer = 5;

Ticker motorOffTimer;

Motor motor(32, 33, 25, 26, 27, 14, 12);
IrSony ir_sony(2);

int mode = 1;

void setup() {
    Serial.begin(9600);
    pinMode(button_clockwise, INPUT_PULLUP);
    pinMode(button_counter_clockwise, INPUT_PULLUP);
    pinMode(button_single_step, INPUT_PULLUP);
    pinMode(button_modehalfer, INPUT_PULLUP);

    // attachInterrupt(digitalPinToInterrupt(button_single_step),
    //                 []{
    //                     motor.power_cycle(2);
    //                     motor.step(20);
    //                     delay(10);
    //                 }, FALLING);
    attachInterrupt(digitalPinToInterrupt(button_modehalfer),
                    []{
                        mode *= 2;
                        if (mode > 32)
                            mode = 1;
                        motor.set_mode(mode);
                    }, FALLING);
}

void loop() {
    if (digitalRead(button_single_step) == LOW) {
        ir_sony.shoot();
        motor.power_cycle(2);
        delay(300);
        motor.step(10);
        delay(700);
    }
    else if (digitalRead(button_clockwise) == LOW || digitalRead(button_counter_clockwise) == LOW)
    {
        motor.power_cycle(2);
        motor.set_direction(digitalRead(button_clockwise));
        motor.step();
    }
}
