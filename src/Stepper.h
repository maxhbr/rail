#ifndef STEPPER_H
#define STEPPER_H

#include <Arduino.h>
#include <Ticker.h>

#define MAX_SPEED ((unsigned int) 5)
#define DIRECTION_FORWARD ((int) 1)
#define DIRECTION_BACKWARD ((int) -1)

class Stepper
{
private:
    int pin_direction;
    int pin_step;
    int pin_sleep;
    int pin_reset;
    int pin_mode2;
    int pin_mode1;
    int pin_mode0;
    int pin_enable;

    // sensors
    int pin_limit_top;
    int pin_limit_bottom;

    // state
    int is_on = 0;
    int position = 0;
    int direction = DIRECTION_FORWARD;
    int speed = 0;

    // ticker for poweroff
    Ticker power_off_ticker;

    // private functions
    void set_direction(int _direction);
    void set_speed(unsigned int _speed);
    void power_on();
    void power_cycle(float cyle_time = 2);

public:
    Stepper(
        int _pin_direction,
        int _pin_step,
        int _pin_sleep,
        int _pin_reset,
        int _pin_mode2,
        int _pin_mode1,
        int _pin_mode0,
        int _pin_limit_top,
        int _pin_limit_bottom);
    int get_direction();
    bool is_at_limit();
    int get_speed();
    int get_step_size();
    int step(int steps = 1, unsigned int _speed = 0, unsigned int wait_microseconds = 1000);
    void power_off(float delay = 0); // public for the usage in the callback

    void log_state();
};

#endif /* STEPPER_H */
