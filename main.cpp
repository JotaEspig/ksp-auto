#include <iostream>
#include <string>
#include <unistd.h>

#include <krpc.hpp>
#include <krpc/services/space_center.hpp>

#include "src/suicideburn.hpp"

int main(int argc, const char **argv) {
    std::string address = "127.0.0.1";
    if (argc > 1) {
        address = argv[1];
    }

    auto conn = krpc::connect("KSP Auto", address);
    krpc::services::SpaceCenter sc(&conn);

    auto vessel = sc.active_vessel();

    suicide_burn(vessel);
}
