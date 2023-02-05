#include <iostream>
#include <cmath>
#include <unistd.h>

#include "launchorbit.hpp"
#include "maneuver.hpp"


void launch_into_orbit(SpaceCenter sc, Vessel vessel, int target_alt, 
                        int turn_start_alt, int turn_end_alt) {
    auto ut = sc.ut_stream();
    auto altitude = vessel.flight().mean_altitude_stream();
    auto apoapsis = vessel.orbit().apoapsis_altitude_stream();
    auto time_to_apoapsis = vessel.orbit().time_to_apoapsis_stream();

    vessel.control().set_sas(false);
    vessel.control().set_rcs(false);
    vessel.control().set_throttle(1);

    std::cout << "Lift off!\n";
    vessel.control().activate_next_stage();
    vessel.auto_pilot().engage();
    vessel.auto_pilot().target_pitch_and_heading(90, 90);

    std::cout << "Started gravity turn\n";
    while (true) {
        if (altitude() >= turn_start_alt && altitude() <= turn_end_alt) {
            double frac = (altitude() - turn_start_alt)
                    / (turn_end_alt - turn_start_alt);
            double turn_angle = frac * 90;
            vessel.auto_pilot().target_pitch_and_heading(90 - turn_angle, 90);
        }
        if (apoapsis() > target_alt) {
            vessel.control().set_throttle(0);
            break;
        }
    }

    std::cout << "Waiting to be out of the atmosphere\n";
    while (altitude() < 70500);

    double gm = vessel.orbit().body().gravitational_parameter();
    double r = vessel.orbit().apoapsis();
    double a1 = vessel.orbit().semi_major_axis();
    double a2 = r;
    double v1 = std::sqrt(gm * ((2.0 / r) - (1.0 / a1)));
    double v2 = std::sqrt(gm * ((2.0 / r) - (1.0 / a2)));
    double delta_v = v2 - v1;
    auto node = vessel.control().add_node(
        ut() + vessel.orbit().time_to_apoapsis(), delta_v);
    
    do_maneuver(vessel, node);
}
