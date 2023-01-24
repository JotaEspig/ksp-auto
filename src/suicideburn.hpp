#ifndef SUICIDEBURN_HPP
#define SUICIDEBURN_HPP

#include <krpc/services/space_center.hpp>

#include "types.hpp"


#define FINAL_SPEED 6

/**
 * @brief Start the suicide burn
 *
 * @param vessel
 */
void suicide_burn(Vessel vessel);

static double get_height(float twr, float current_speed, float gravity);

static void set_retrograde_direction(Vessel vessel, std::tuple<double, double, double>);

#endif // SUICIDEBURN_HPP
