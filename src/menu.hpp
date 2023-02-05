#pragma once

#include <string>
#include <map>
#include <functional>

#include "types.hpp"


static void run_suicide_burn(Vessel vessel);
static void run_launch_into_orbit(Vessel vessel);
static void run_do_maneuver(Vessel vessel);

namespace menu {
    extern std::map<std::string, std::function<void(Vessel)>> commands;
}
