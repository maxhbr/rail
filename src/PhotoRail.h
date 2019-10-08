#ifndef PHOTO_RAIL_H
#define PHOTO_RAIL_H

#include <Arduino.h>

#include "IrSony.h"
#include "Rail.h"

class PhotoRail
 : public Rail
{
private:
    int left = 0;
    int right = 0;

    IrSony ir_sony;

    void update_state();

public:
    PhotoRail(
        int _pin_direction,
        int _pin_step,
        int _pin_sleep,
        int _pin_reset,
        int _pin_mode2,
        int _pin_mode1,
        int _pin_mode0,
        int _pin_limit_top,
        int _pin_limit_bottom,
        int _pin_ir);

    void move(int distance, unsigned int max_speed = MAX_SPEED);
    void move_to(int target, unsigned int max_speed = MAX_SPEED);
    void step(int steps, unsigned int speed = 0, unsigned int wait_microseconds = 1000);

    void move_to_left(unsigned int max_speed = MAX_SPEED);
    void move_to_right(unsigned int max_speed = MAX_SPEED);

    void stack(unsigned int shots);
    void shoot(int microseconds = 0);

    void log_state();
};

#endif /* PHOTO_RAIL_H */
