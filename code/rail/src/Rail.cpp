#include <Ticker.h>
#include "Rail.h"
#include <math.h>

Rail::Rail(
    int _pin_direction,
    int _pin_step,
    int _pin_sleep,
    int _pin_reset,
    int _pin_mode2,
    int _pin_mode1,
    int _pin_mode0)
    : stepper(_pin_direction,
              _pin_step,
              _pin_sleep,
              _pin_reset,
              _pin_mode2,
              _pin_mode1,
              _pin_mode0)
{}

int Rail::get_position()
{
    return position;
}

unsigned int Rail::get_distance_to(int target)
{
  return abs(target - get_position());
}

void Rail::set_direction_to(int target)
{
    if (target > position)
    {
        stepper.set_direction(DIRECTION_FORWARD);
    }
    else
    {
        stepper.set_direction(DIRECTION_BACKWARD);
    }
}

void Rail::move(int distance, unsigned int speed)
{
    move_to(position + distance, speed);
}

void Rail::move_to(int target, unsigned int speed)
{
    Serial.println("Rail::move_to " + target);
    set_direction_to(target);

    stepper.power_cycle(2);

    // TODO:
    // - soft start
    // - configurable slope

    for (int s = speed; s >= 0; s--)
    {
        int steps = get_distance_to(target) / pow(2, s);
        step(s, steps);
    }
}

void Rail::step(unsigned int speed, unsigned int steps, unsigned int wait_microseconds){
    if (steps == 0)
    {
        return;
    }

    if (stepper.get_speed() != speed)
    {
        stepper.set_speed(speed);
    }

    stepper.step(steps, wait_microseconds);
    position += steps * stepper.get_direction() * stepper.get_step_size();
}

Stepper* Rail::get_stepper()
{
    return &stepper;
}

