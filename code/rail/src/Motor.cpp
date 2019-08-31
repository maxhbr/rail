#include <Ticker.h>
#include "Motor.h"


Motor::Motor(
    int _pin_direction,
    int _pin_step,
    int _pin_sleep,
    int _pin_reset,
    int _pin_mode2,
    int _pin_mode1,
    int _pin_mode0)
{
    pin_direction = _pin_direction;
    pin_step = _pin_step;
    pin_sleep = _pin_sleep;
    pin_reset = _pin_reset;
    pin_mode2 = _pin_mode2;
    pin_mode1 = _pin_mode1;
    pin_mode0 = _pin_mode0;

    pinMode(pin_direction, OUTPUT);
    pinMode(pin_step, OUTPUT);
    pinMode(pin_sleep, OUTPUT);
    pinMode(pin_reset, OUTPUT);
    pinMode(pin_mode2, OUTPUT);
    pinMode(pin_mode1, OUTPUT);
    pinMode(pin_mode0, OUTPUT);
    pinMode(pin_enable, OUTPUT);

    digitalWrite(pin_reset, HIGH);

    power_off();
    set_mode(1);
    set_direction(0);
}

void Motor::step(int steps)
{
    for (int i = 0; i < steps; i++)
    {
        digitalWrite(pin_step, HIGH);
        delayMicroseconds(200);
        digitalWrite(pin_step, LOW);
        delayMicroseconds(200);
    }
}

void Motor::set_mode(int mode)
{
    Serial.println("Motor::set_mode " + String(mode));
    switch (mode)
    {
    case 1:
        digitalWrite(pin_mode0, LOW);
        digitalWrite(pin_mode1, LOW);
        digitalWrite(pin_mode2, LOW);
        break;
    case 2:
        digitalWrite(pin_mode0, HIGH);
        digitalWrite(pin_mode1, LOW);
        digitalWrite(pin_mode2, LOW);
        break;
    case 4:
        digitalWrite(pin_mode0, LOW);
        digitalWrite(pin_mode1, HIGH);
        digitalWrite(pin_mode2, LOW);
        break;
    case 8:
        digitalWrite(pin_mode0, HIGH);
        digitalWrite(pin_mode1, HIGH);
        digitalWrite(pin_mode2, LOW);
        break;
    case 16:
        digitalWrite(pin_mode0, LOW);
        digitalWrite(pin_mode1, LOW);
        digitalWrite(pin_mode2, HIGH);
        break;
    case 32:
        digitalWrite(pin_mode0, HIGH);
        digitalWrite(pin_mode1, HIGH);
        digitalWrite(pin_mode2, HIGH);
        break;
    }
}

void Motor::set_direction(int direction)
{
    // Serial.println("Motor::set_direction " + String(direction));
    digitalWrite(pin_direction, direction);
}

void Motor::power_on()
{
    digitalWrite(pin_sleep, HIGH);
    delay(2);
}

void callback(Motor *motor)
{
    motor->power_off();
}

void Motor::power_off(float delay)
{
    if (delay == 0)
    {
        Serial.println("Motor::power_off");
        digitalWrite(pin_sleep, LOW);
    }
    else
    {
        power_off_ticker.once(delay, callback, this);
    }
}

void Motor::power_cycle(float cycle_time)
{
    power_on();
    power_off(cycle_time);
}
