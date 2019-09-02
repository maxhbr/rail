#include <Ticker.h>
#include "Motor.h"
#include <math.h>

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
    set_speed(0);
    set_direction(0);
}

int Motor::get_position()
{
    return position;
}

int Motor::get_distance_to(int target)
{
  return target - get_position();
}

int Motor::get_speed()
{
    return speed;
}

void Motor::set_speed(unsigned int _speed)
{
    if (_speed != get_speed())
    {
        Serial.println("Motor::set_speed " + String(_speed));
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

int Motor::get_step_size()
{
    return pow(2, get_speed());
}

int Motor::get_direction()
{
  return direction;
}

void Motor::set_direction(int _direction)
{
    if (_direction != get_direction()) {
        Serial.println("Motor::set_direction " + String(_direction));
        if (_direction == DIRECTION_FORWARD)
        {
            digitalWrite(pin_direction, LOW);
        }
        else
        {
          digitalWrite(pin_direction, HIGH);
        }
        direction = _direction;
    }
}

void Motor::move(int distance, unsigned int max_speed)
{
    move_to(position + distance, max_speed);
}

void Motor::move_to(int target, unsigned int max_speed)
{
    Serial.println("Motor::move_to " + target);
    synchronized(m_mutex) {
        if (target > get_position())
        {
            set_direction(DIRECTION_FORWARD);
        }
        else
        {
            set_direction(DIRECTION_BACKWARD);
        }
        set_speed(0);

        int distance = get_distance_to(target);

        if (distance <= 3)
        {
            step(distance);
            return;
        }

        int actual_max_speed = 0;
        for (int s = 0; s < max_speed; s++)
        {
            if (distance <= 4 * (pow(2,s)))
            {
                actual_max_speed = s;
            }
        }

        for (int s = 0; s <= actual_max_speed; s++)
        {
            set_speed(s);
            step(2);
        }

        int distances_with_max = max(get_distance_to(target) - 4 * pow(2, actual_max_speed), 0);
        int steps_with_max = distances_with_max / pow(2, actual_max_speed);
        step(steps_with_max);

        for (int s = (actual_max_speed - 1); s >= 0; s--)
        {
            set_speed(s);
            step(get_distance_to(target) / pow(2,s));
        }
    }
}

void Motor::step(int steps)
{
    for (int i = 0; i < steps; i++)
    {
        delayMicroseconds(100);
        digitalWrite(pin_step, HIGH);
        delayMicroseconds(200);
        digitalWrite(pin_step, LOW);
        delayMicroseconds(100);
        position += get_direction() * get_step_size();
    }
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
