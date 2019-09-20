#include <Ticker.h>
#include <math.h>

#include "Rail.h"

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

void Rail::move_to(int target, unsigned int max_speed)
{
#ifdef DEBUG_BUILD
    Serial.println("Rail::move_to " + target);
#endif

    // TODO:
    // - soft start
    // - configurable slope

    for (int speed = max_speed; speed >= 0; speed--)
    {
        int steps = (target - get_position()) / pow(2, speed);
        step(steps, speed);
    }
}

void Rail::step(int steps, unsigned int speed, unsigned int wait_microseconds)
{
    if (steps == 0)
    {
        return;
    }

    Stepper::step(steps, speed, wait_microseconds);
    position += steps * Stepper::get_step_size();
}

void Rail::log_state()
{
    Serial.println("Rail::log_state: " + String(get_position()));
    Stepper::log_state();
}

