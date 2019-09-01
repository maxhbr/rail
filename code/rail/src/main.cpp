#include <Arduino.h>
#include <Ticker.h>

#include "Motor.h"
// #include "IrSony.h"
#include "SerialCommandDispatcher.h"

const int button_clockwise = 16;
const int button_counter_clockwise = 4;
const int button_single_step = 17;
const int button_modehalfer = 5;

Ticker motorOffTimer;

Motor motor(32, 33, 25, 26, 27, 14, 12);
// IrSony ir_sony(2);

const SerialCommand commandtable[] = {
    {key_arrow_left, [](){
                         motor.set_direction(0);
                         motor.step(1);
                     }},
    {key_arrow_right, [](){
                         motor.set_direction(1);
                         motor.step(1);
                     }},
    {key_arrow_up, [](){
                       motor.add_speed(1);
                       Serial.println("speed = " + String(motor.get_speed()));
                      }},
    {key_arrow_down, [](){
                         motor.add_speed(-1);
                         Serial.println("speed = " + String(motor.get_speed()));
                     }},
};
SerialCommandDispatcher commander(Serial, commandtable, sizeof(commandtable) / sizeof(SerialCommand));

int mode = 1;

void setup() {
    Serial.begin(9600);
}

void loop() {
    commander.process();
}
