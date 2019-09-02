#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

#include <mutex>
#define synchronized(m) \
    for(std::unique_lock<std::recursive_mutex> lk(m); lk; lk.unlock())

#define MAX_SPEED ((unsigned int) 5)
#define DIRECTION_FORWARD ((int) 1)
#define DIRECTION_BACKWARD ((int) -1)

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

    // state:
    int position = 0;
    int direction = 1;
    int speed = 0;

    // ticker for poweroff
    Ticker power_off_ticker;

    // private functions
    void step(int steps = 1);
    void set_direction(int _direction);
    void set_speed(unsigned int _speed);
    void power_on();
    void power_cycle(float cyle_time = 2);

    std::recursive_mutex m_mutex;

public:
    Motor(
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
    void power_off(float delay = 0); // public for the usage in the callback
};

#endif /* MOTOR_H */
