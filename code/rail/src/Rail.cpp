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
    synchronized(m_mutex) {
        set_direction_to(target);

        // TODO:
        // - soft start
        // - configurable slope

        for (int s = speed; s >= 0; s--) {
          stepper.set_speed(s);
          stepper.step(get_distance_to(target) / stepper.get_step_size());
        }
    }
}

