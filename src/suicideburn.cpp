#include <math.h>

#include "suicideburn.hpp"

double SBurn::get_height(float twr, float current_speed, float gravity) {
    float a = twr * gravity; // acceleration
    float t = current_speed / a; // time
    float height = (current_speed/2)*t;
    return height;
}
