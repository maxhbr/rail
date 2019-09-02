#ifndef RAIL_H
#define RAIL_H

#include <Arduino.h>

#include "Stepper.h"

class Rail
{
private:
    // state
    int position = 0;
    Stepper stepper;

    // ticker for poweroff
    Ticker power_off_ticker;

    // private functions
    void set_direction_to(int target);
    unsigned int get_distance_to(int target);

public:
    Rail(
        int _pin_direction,
        int _pin_step,
        int _pin_sleep,
        int _pin_reset,
        int _pin_mode2,
        int _pin_mode1,
        int _pin_mode0);
    int get_position();
    int get_direction();
    int get_speed();
    int get_step_size();
    void move(int distance, unsigned int speed = MAX_SPEED);
    void move_to(int target, unsigned int speed = MAX_SPEED);
};

#endif /* RAIL_H */
