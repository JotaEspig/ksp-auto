#include "menu.hpp"

#include "suicideburn.hpp"


static void run_suicide_burn(Vessel vessel) {
    suicide_burn(vessel);
}

static void run_launch_into_orbit(Vessel vessel) {

}

static void run_do_maneuver(Vessel vessel) {

}

std::map<std::string, std::function<void(Vessel)>> menu::commands = {
    {"suicideburn", run_suicide_burn},
    {"launch", run_launch_into_orbit},
    {"maneuver", run_do_maneuver}
};
