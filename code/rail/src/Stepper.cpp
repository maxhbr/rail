#include <Ticker.h>
#include "Stepper.h"

Stepper::Stepper(
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
    set_speed(0);
    set_direction(0);
}

int Stepper::get_speed()
{
    return speed;
}

void Stepper::set_speed(unsigned int _speed)
{
    if (_speed != get_speed())
    {
        Serial.println("Stepper::set_speed " + String(_speed));
        switch (_speed)
        {
        case 0:
            digitalWrite(pin_mode0, LOW);
            digitalWrite(pin_mode1, LOW);
            digitalWrite(pin_mode2, LOW);
            break;
        case 1:
            digitalWrite(pin_mode0, HIGH);
            digitalWrite(pin_mode1, LOW);
            digitalWrite(pin_mode2, LOW);
            break;
        case 2:
            digitalWrite(pin_mode0, LOW);
            digitalWrite(pin_mode1, HIGH);
            digitalWrite(pin_mode2, LOW);
            break;
        case 3:
            digitalWrite(pin_mode0, HIGH);
            digitalWrite(pin_mode1, HIGH);
            digitalWrite(pin_mode2, LOW);
            break;
        case 4:
            digitalWrite(pin_mode0, LOW);
            digitalWrite(pin_mode1, LOW);
            digitalWrite(pin_mode2, HIGH);
            break;
        case 5:
            digitalWrite(pin_mode0, HIGH);
            digitalWrite(pin_mode1, HIGH);
            digitalWrite(pin_mode2, HIGH);
            break;
        }
        speed = _speed;
    }
}

int Stepper::get_step_size()
{
    return pow(2, get_speed());
}

int Stepper::get_direction()
{
  return direction;
}

void Stepper::set_direction(int _direction)
{
    if (_direction != get_direction())
    {
        Serial.println("Stepper::set_direction " + String(_direction));
        if (_direction == DIRECTION_FORWARD)
        {
            digitalWrite(pin_direction, LOW);
        }
        else
        {
            digitalWrite(pin_direction, HIGH);
        }
        direction = _direction;
        delayMicroseconds(100);
    }
}

void Stepper::step(int steps)
{
    // Serial.println("Stepper::step " + String(steps));
    for (int i = 0; i < steps; i++)
    {
        // Serial.print(".");
        delayMicroseconds(100);
        digitalWrite(pin_step, HIGH);
        delayMicroseconds(200);
        digitalWrite(pin_step, LOW);
        delayMicroseconds(100);
    }
}

void Stepper::power_on()
{
    digitalWrite(pin_sleep, HIGH);
    delay(2);
}

void callback(Stepper *stepper)
{
    stepper->power_off();
}

void Stepper::power_off(float delay)
{
    if (delay == 0)
    {
        Serial.println("Stepper::power_off");
        digitalWrite(pin_sleep, LOW);
    }
    else
    {
        power_off_ticker.once(delay, callback, this);
    }
}

void Stepper::power_cycle(float cycle_time)
{
    power_on();
    power_off(cycle_time);
}
