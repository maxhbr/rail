#ifndef RAIL_H
#define RAIL_H

#include <Arduino.h>

#include "Stepper.h"

class Rail
 : public Stepper
{
private:
    // state
    int position = 0;

    // ticker for poweroff
    Ticker power_off_ticker;

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
    void move(int distance, unsigned int max_speed = MAX_SPEED);
    void move_to(int target, unsigned int max_speed = MAX_SPEED);
    void step(int steps, unsigned int speed = 0, unsigned int wait_microseconds = 1000);

    void log_state();
};

#endif /* RAIL_H */
