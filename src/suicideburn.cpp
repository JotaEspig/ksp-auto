#include <math.h>
#include <unistd.h>

#include <krpc/services/space_center.hpp>

#include "suicideburn.hpp"


void suicide_burn(Vessel vessel) {
    float twr, height_sb, thrust_to_final_speed;

    float thrust = vessel.available_thrust();
    float body_gravity = vessel.orbit().body().surface_gravity();
    auto body_refframe = vessel.orbit().body().reference_frame();

    auto mass_stream = vessel.mass_stream();
    auto throttle_stream = vessel.control().throttle_stream();
    auto speed_stream = vessel.flight(body_refframe).speed_stream();
    auto v_speed_stream = vessel.flight(body_refframe).vertical_speed_stream();
    auto h_speed_stream = vessel.flight(body_refframe).horizontal_speed_stream();
    auto height_stream = vessel.flight(body_refframe).bedrock_altitude_stream();

    if (thrust == 0) {
        std::cout << "No available thrust!\n";
        exit(-1);
    }

    vessel.control().set_sas(true);
    usleep(2*1000*1000);
    vessel.control().set_sas_mode(SASMode::retrograde);
    usleep(5*1000*1000);

    std::cout << "Removing horizontal speed\n";
    vessel.control().set_speed_mode(SpeedMode::surface);
    while (h_speed_stream() > 10) {
        twr = thrust / (body_gravity * mass_stream());
        height_sb = get_height(twr, v_speed_stream(), body_gravity);
        if (height_stream() > height_sb + 2000) continue;
        if (throttle_stream() < 1) vessel.control().set_throttle(1);
    }
    vessel.control().set_throttle(0);

    std::cout << "Starting first stage of suicide burn\n";
    vessel.control().set_speed_mode(SpeedMode::surface);
    vessel.control().set_gear(true);
    while (speed_stream() > FINAL_SPEED) {
        twr = thrust / (body_gravity * mass_stream());
        height_sb = get_height(twr, speed_stream(), body_gravity) + 20; // 20 is a safe margin
        if (height_sb < height_stream()) {
            if (throttle_stream() > 0) vessel.control().set_throttle(0);
            continue;
        }
        if (throttle_stream() < 1) vessel.control().set_throttle(1);
    }

    std::cout << "Final stage\n";
    while(height_stream() > 5) {
        twr = thrust / (body_gravity * mass_stream());
        thrust_to_final_speed = 1/twr;
        if (throttle_stream() == 1)
            vessel.control().set_throttle(thrust_to_final_speed);
    }
    vessel.control().set_throttle(0);
}

static double get_height(float twr, float current_speed, float gravity) {
    float a = twr * gravity; // acceleration
    float t = current_speed / a; // time
    float height = (current_speed/2)*t; // average speed plus time
    return height;
}
