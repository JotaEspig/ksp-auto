#include "maneuver.hpp"

#include <unistd.h>
#include <cmath>


void do_maneuver(Vessel vessel, Node node) {
    double delta_v = node.delta_v();
    double f = vessel.available_thrust();
    double isp = vessel.specific_impulse() * 9.82;
    double m0 = vessel.mass();
    double m1 = m0 / std::exp(delta_v / isp);
    double flow_rate = f / isp;
    double burn_time = (m0 - m1) / flow_rate;

    vessel.auto_pilot().engage();
    vessel.auto_pilot().set_reference_frame(node.reference_frame());
    vessel.auto_pilot().set_target_direction(std::make_tuple(0.0, 1.0, 0.0));
    vessel.auto_pilot().wait();

    auto time_to_maneuver = node.time_to_stream();

    while (time_to_maneuver() - (burn_time / 2.0) > 0); // Wait until burn

    vessel.control().set_throttle(1);
    usleep((burn_time - 0.5) * 1000 * 1000);

    vessel.control().set_throttle(0.25);

    auto remaining_burn = node.remaining_burn_vector_stream(node.reference_frame());
    while (std::get<0>(remaining_burn()) > 5 || std::get<1>(remaining_burn()) > 5);

    vessel.control().set_throttle(0.05);
    while (std::get<0>(remaining_burn()) > 0.5 || std::get<1>(remaining_burn()) > 0.5);

    vessel.control().set_throttle(0.01);
    while (std::get<0>(remaining_burn()) > 0.03 || std::get<1>(remaining_burn()) > 0.03);

    vessel.control().set_throttle(0);
    node.remove();
}
