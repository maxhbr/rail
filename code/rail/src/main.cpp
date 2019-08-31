#include <Arduino.h>
#include <Ticker.h>

#include "Motor.h"

const int button_clockwise = 18;
const int button_counter_clockwise = 19;
const int button_modefull = 2;
const int button_modehalfer = 4;

Ticker motorOffTimer;

Motor motor(32, 33, 25, 26, 27, 14, 12);

int mode = 1;

void setup() {
    Serial.begin(9600);
    pinMode(button_clockwise, INPUT_PULLUP);
    pinMode(button_counter_clockwise, INPUT_PULLUP);
    pinMode(button_modefull, INPUT_PULLUP);
    pinMode(button_modehalfer, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(button_modefull),
                    []{
                        motor.power_cycle(2);
                        motor.step(20);
                        delay(10);
                    }, FALLING);
    attachInterrupt(digitalPinToInterrupt(button_modehalfer),
                    []{
                        mode *= 2;
                        if (mode > 32)
                            mode = 1;
                        motor.set_mode(mode);
                        delay(1000);
                    }, FALLING);
}

void loop() {
    if (digitalRead(button_clockwise) == LOW || digitalRead(button_counter_clockwise) == LOW)
    {
        motor.power_cycle(2);
        motor.set_direction(digitalRead(button_clockwise));
        motor.step();
    }
}
