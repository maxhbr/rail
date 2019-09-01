#include <Ticker.h>
#include "Motor.h"

#define MOTOR_SPEED_MAX ((unsigned int )50)


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
    set_speed(1);
    set_direction(0);
}

void Motor::step(unsigned int _steps)
{
    int steps = _steps * speed * speed * fractionmode / 32 ;
    // Serial.println("_steps: " + String(_steps) + " steps: " + String(steps) + " speed: " + String(speed) + " fraction: " + String(fractionmode));
    power_cycle();
    for (int i = 0; i < steps; i++)
    {
        digitalWrite(pin_step, HIGH);
        delayMicroseconds(200);
        digitalWrite(pin_step, LOW);
        delayMicroseconds(200);
    }
}

void Motor::set_fractalrotation(float fraction)
{
    if (fraction < 0 || fraction > 1)
        return;

    if (fraction <= 1.0 / 32)
    {
        fractionmode = 32;
        digitalWrite(pin_mode0, HIGH);
        digitalWrite(pin_mode1, HIGH);
        digitalWrite(pin_mode2, HIGH);
    }
    else if (fraction <= 1.0 / 16)
    {
        fractionmode = 16;
        digitalWrite(pin_mode0, LOW);
        digitalWrite(pin_mode1, LOW);
        digitalWrite(pin_mode2, HIGH);
    }
    else if (fraction <= 1.0 / 8)
    {
        fractionmode = 8;
        digitalWrite(pin_mode0, HIGH);
        digitalWrite(pin_mode1, HIGH);
        digitalWrite(pin_mode2, LOW);
    }
    else if (fraction <= 1.0 / 4)
    {
        fractionmode = 4;
        digitalWrite(pin_mode0, LOW);
        digitalWrite(pin_mode1, HIGH);
        digitalWrite(pin_mode2, LOW);
    }
    else if (fraction <= 1.0 / 2)
    {
        fractionmode = 2;
        digitalWrite(pin_mode0, HIGH);
        digitalWrite(pin_mode1, LOW);
        digitalWrite(pin_mode2, LOW);
    }
    else
    {
        fractionmode = 1;
        digitalWrite(pin_mode0, LOW);
        digitalWrite(pin_mode1, LOW);
        digitalWrite(pin_mode2, LOW);
    }
}

void Motor::set_direction(int direction)
{
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
        digitalWrite(pin_sleep, LOW);
    else
        power_off_ticker.once(delay, callback, this);
}

void Motor::power_cycle(float cycle_time)
{
    if (!power_status())
        power_on();
    power_off(cycle_time);
}

int Motor::power_status()
{
    return digitalRead(pin_sleep);
}

void Motor::add_speed(int amount)
{
    int current_speed = get_speed();
    if (amount < 0 && current_speed + amount < 0)
        set_speed(0);
    else if (amount > 0 && current_speed + amount > MOTOR_SPEED_MAX)
        set_speed(MOTOR_SPEED_MAX);
    else
        set_speed(current_speed + amount);
}

void Motor::set_speed(unsigned int _speed)
{
    speed = std::min(_speed, MOTOR_SPEED_MAX);

    if (_speed > MOTOR_SPEED_MAX / 2)
        set_fractalrotation(1.0 / 8);
    else
        set_fractalrotation(1.0 / 32);

}

unsigned int Motor::get_speed()
{
    return speed;
}
