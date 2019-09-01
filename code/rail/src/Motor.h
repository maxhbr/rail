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
    Ticker power_off_ticker;
    unsigned int speed;
    unsigned int fractionmode;

    void set_fractalrotation(float mode);

public:
    Motor(
        int _pin_direction,
        int _pin_step,
        int _pin_sleep,
        int _pin_reset,
        int _pin_mode2,
        int _pin_mode1,
        int _pin_mode0);
    void step(unsigned int steps = 1);
    void set_direction(int direction);
    void set_speed(unsigned int speed);
    void add_speed(int amount);
    unsigned int get_speed();
    void power_on();
    void power_off(float delay = 0);
    void power_cycle(float cyle_time = 2);
    int power_status();
};

#endif /* MOTOR_H */
