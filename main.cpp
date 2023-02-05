#include <iostream>
#include <string>

#include <krpc.hpp>
#include <krpc/services/space_center.hpp>

#include "src/menu.hpp"


int main(int argc, const char **argv) {
    std::string choice;
    std::string address = "127.0.0.1";
    if (argc > 1) {
        address = argv[1];
    }

    auto conn = krpc::connect("KSP Auto", address);
    krpc::services::SpaceCenter sc(&conn);

    auto vessel = sc.active_vessel();

    std::cout << "Which tool do you want to use?\n"
                 "- \"suicideburn\"\n"
                 "- \"launch\" (launch into orbit)\n"
                 "- \"maneuver\" (do a maneuver)\n"
                 "|> ";
    std::cin >> choice;
    auto f = menu::commands.at(choice);
    f(vessel);
}
