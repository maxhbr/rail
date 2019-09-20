#include <Ticker.h>
#include <math.h>

#include "PhotoRail.h"

PhotoRail::PhotoRail(
    int _pin_direction,
    int _pin_step,
    int _pin_sleep,
    int _pin_reset,
    int _pin_mode2,
    int _pin_mode1,
    int _pin_mode0,
    int _pin_ir)
    : Rail(_pin_direction,
           _pin_step,
           _pin_sleep,
           _pin_reset,
           _pin_mode2,
           _pin_mode1,
           _pin_mode0)
    , ir_sony(_pin_ir)
{}

void PhotoRail::update_state()
{
    int direction = Stepper::get_direction();
    if(direction  == DIRECTION_FORWARD)
    {
        left = Rail::get_position();
    }
    else if(direction  == DIRECTION_BACKWARD)
    {
        right = Rail::get_position();
    }
}

void PhotoRail::move(int distance, unsigned int speed)
{
    Rail::move(distance, speed);
    update_state();
}

void PhotoRail::move_to(int target, unsigned int max_speed)
{
    Rail::move_to(target, max_speed);
    update_state();
}

void PhotoRail::move_to_left(unsigned int max_speed)
{
    move_to(left);
}
void PhotoRail::move_to_right(unsigned int max_speed)
{
    move_to(right);
}

void PhotoRail::step(int steps, unsigned int speed, unsigned int wait_microseconds)
{
    Rail::step(steps, speed, wait_microseconds);
    update_state();
}

void PhotoRail::stack(unsigned int shots)
{
    int start_pos = Rail::get_position();
    int end_pos = start_pos == left ? right : left;
    int distance = end_pos - start_pos;
    int distance_between_shots = distance / shots;
    Serial.println("PhotoRail::stack " + String(shots) + " ( " + String(start_pos) + " " + String(end_pos) + " " + String(distance) + " " + String(distance_between_shots) + " )");

    log_state();

    for (int i = 0; i < shots; i++) {
        Rail::move(distance_between_shots, 0);
        delay(1000);
        Serial.println("shoot " + String(i) + " of " + String(shots));
        ir_sony.shoot();
        delay(300);
        log_state();
    }

    Rail::move_to(start_pos);
    log_state();
}

void PhotoRail::log_state()
{
    Serial.println("PhotoRail::log_state: " + String(left) + " " + String(right));
    Rail::log_state();
}

