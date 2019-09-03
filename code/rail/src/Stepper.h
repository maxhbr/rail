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

    // state
    int is_on = 0;
    int position = 0;
    int direction = DIRECTION_FORWARD;
    int speed = 0;

    // ticker for poweroff
    Ticker power_off_ticker;

public:
    Stepper(
        int _pin_direction,
        int _pin_step,
        int _pin_sleep,
        int _pin_reset,
        int _pin_mode2,
        int _pin_mode1,
        int _pin_mode0);
    int get_direction();
    void set_direction(int _direction);
    int get_speed();
    void set_speed(unsigned int _speed);
    int get_step_size();
    void step(unsigned int steps = 1, unsigned int wait_microseconds = 1000);
    void step_forward(int steps = 1);
    void step_backward(int steps = 1);
    void power_on();
    void power_cycle(float cyle_time = 2);
    void power_off(float delay = 0); // public for the usage in the callback
};

#endif /* STEPPER_H */
