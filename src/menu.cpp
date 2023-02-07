#include "menu.hpp"

#include <iostream>

#include "suicideburn.hpp"
#include "launchorbit.hpp"
#include "maneuver.hpp"
#include "types.hpp"


static void run_suicide_burn(SpaceCenter sc) {
    Vessel vessel = sc.active_vessel();
    suicide_burn(vessel);
}

static void run_launch_into_orbit(SpaceCenter sc) {
    int target_alt, turn_start_alt, turn_end_alt;

    Vessel vessel = sc.active_vessel();
    
    std::cout << "Target altitude: ";
    std::cin >> target_alt;
    std::cout << "Altitude at the start of the gravitational turn: ";
    std::cin >> turn_start_alt;
    std::cout << "Altitude at the end of the gravitational turn: ";
    std::cin >> turn_end_alt;

    launch_into_orbit(sc, vessel, target_alt, turn_start_alt, turn_end_alt);
}

static void run_do_maneuver(SpaceCenter sc) {
    Vessel vessel = sc.active_vessel();
    
    Node node = vessel.control().nodes().at(0);
    do_maneuver(vessel, node);
}

std::map<std::string, std::function<void(SpaceCenter)>> menu::commands = {
    {"suicideburn", run_suicide_burn},
    {"launch", run_launch_into_orbit},
    {"maneuver", run_do_maneuver}
};
