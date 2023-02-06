#pragma once

#include <string>
#include <map>
#include <functional>

#include "types.hpp"


static void run_suicide_burn(SpaceCenter sc);
static void run_launch_into_orbit(SpaceCenter sc);
static void run_do_maneuver(SpaceCenter sc);

namespace menu {
    extern std::map<std::string, std::function<void(SpaceCenter)>> commands;
}
