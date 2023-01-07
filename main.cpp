#include <iostream>
#include <iomanip>
#include <string>
#include <tuple>
#include <unistd.h>

#include <krpc.hpp>
#include <krpc/services/krpc.hpp>
#include <krpc/services/space_center.hpp>

int main(int argc, const char **argv) {
    std::string address = "127.0.0.1";
    if (argc > 1) {
        address = argv[1];
    }
    auto conn = krpc::connect("KSP Auto", address);
    krpc::services::SpaceCenter sc(&conn);
    auto vessel = sc.active_vessel();
    auto ref_frame = vessel.orbit().body().reference_frame();
    auto pos_stream = vessel.position_stream(ref_frame);
    while (true) {
        auto pos = pos_stream();
        std::cout << std::fixed << std::setprecision(1);
        std::cout << std::get<0>(pos) << ", "
                  << std::get<1>(pos) << ", "
                  << std::get<2>(pos) << std::endl;
        usleep(1000 * 100);
    }
}
