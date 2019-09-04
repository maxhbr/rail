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
    : Stepper(_pin_direction,
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

void Rail::move(int distance, unsigned int speed)
{
    move_to(position + distance, speed);
}

void Rail::move_to(int target, unsigned int speed)
{
    Serial.println("Rail::move_to " + target);

    // TODO:
    // - soft start
    // - configurable slope

    for (int s = speed; s >= 0; s--)
    {
        int steps = (target - get_position()) / pow(2, s);
        step(s, steps);
    }
}

void Rail::step(int steps, unsigned int speed, unsigned int wait_microseconds){
    if (steps == 0)
    {
        return;
    }

    Stepper::step(steps, speed, wait_microseconds);
    position += steps * Stepper::get_step_size();
}

