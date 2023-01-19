#ifndef SUICIDEBURN_HPP
#define SUICIDEBURN_HPP

#include <krpc/services/space_center.hpp>


typedef krpc::services::SpaceCenter::SASMode SASMode;
typedef krpc::services::SpaceCenter::SpeedMode SpeedMode;
typedef krpc::services::SpaceCenter::Vessel Vessel;

#define FINAL_SPEED 6

/**
 * @brief Start the suicide burn
 *
 * @param vessel
 */
void suicide_burn(Vessel vessel);

/**
 * @brief Get the height to start the suicide burn
 *
 * @param twr TWR
 * @param current_speed Current speed of the vessel
 * @param gravity Gravity of the body
 * @return double
 */
static double get_height(float twr, float current_speed, float gravity);

#endif // SUICIDEBURN_HPP