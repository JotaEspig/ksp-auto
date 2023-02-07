#pragma once

#include "types.hpp"


/**
 * @brief Launch the vessel into orbit
 * 
 * @param vessel Vessel that will be launched into orbit
 * @param target_altitude Final altitude of the orbit
 */
void launch_into_orbit(SpaceCenter sc, Vessel vessel, int target_alt,
                        int turn_start_alt, int turn_end_alt);
