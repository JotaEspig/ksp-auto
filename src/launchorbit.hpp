#ifndef LAUNCH_ORBIT_HPP
#define LAUNCH_ORBIT_HPP

#include "types.hpp"


/**
 * @brief Launch the vessel into orbit
 * 
 * @param vessel 
 * @param target_altitude 
 */
void launch_into_orbit(SpaceCenter sc, Vessel vessel, int target_alt,
                        int turn_start_alt, int turn_end_alt);

#endif // LAUNCH_ORBIT_HPP
