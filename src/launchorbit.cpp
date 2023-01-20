#include <iostream>
#include <cmath>
#include <unistd.h>

#include "launchorbit.hpp"


#define visviva(gm, r, a) std::sqrt(gm * ((2.0 / r) - (1.0 / a)));

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
    double r = apoapsis();
    double a1 = vessel.orbit().semi_major_axis();
    double a2 = r;
    double v1 = visviva(gm, r, a1);
    double v2 = visviva(gm, r, a2);
    double delta_v = v2 - v1;

    auto node = vessel.control().add_node(
        ut() + vessel.orbit().time_to_apoapsis(), delta_v);
    
    double f = vessel.available_thrust();
    double isp = vessel.specific_impulse() * 9.82;
    double m0 = vessel.mass();
    double m1 = m0 / std::exp(delta_v / isp);
    double flow_rate = f / isp;
    double burn_time = (m0 - m1) / flow_rate;

    vessel.auto_pilot().set_reference_frame(node.reference_frame());
    vessel.auto_pilot().set_target_direction(std::make_tuple(0.0, 1.0, 0.0));
    vessel.auto_pilot().wait();

    while (time_to_apoapsis() - (burn_time / 2.0) > 0);
    vessel.control().set_throttle(1);
    usleep((burn_time - 0.1) * 1000 * 1000);
    vessel.control().set_throttle(0.05);
    auto remaining_burn = node.remaining_burn_vector_stream(node.reference_frame());
    while (std::get<0>(remaining_burn()) > 0);

    vessel.control().set_throttle(0);
    node.remove();

}
