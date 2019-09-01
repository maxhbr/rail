#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

class Motor
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

    // current position:
    int position = 0;

    // ticker for poweroff
    Ticker power_off_ticker;

    // private functions
    void step(int steps = 1);
    void set_direction(int direction);
    void set_mode(int mode);
    void power_on();
    void power_off(float delay = 0);
    void power_cycle(float cyle_time = 2);

public:
    Motor(
        int _pin_direction,
        int _pin_step,
        int _pin_sleep,
        int _pin_reset,
        int _pin_mode2,
        int _pin_mode1,
        int _pin_mode0);
    int position();
    void move(int distance, int speed = 100);
    void moveTo(int target, int speed = 100);
};

#endif /* MOTOR_H */
