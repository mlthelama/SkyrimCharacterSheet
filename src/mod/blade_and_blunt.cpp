#include "blade_and_blunt.h"
#include "setting/game_setting.h"

namespace mod {
    float blade_and_blunt::calculate_armor_damage_resistance(float a_armor_rating) {
        const auto game_settings = setting::game_setting::get_singleton();
        auto vanilla_resist = a_armor_rating / 100 * game_settings->get_armor_scaling_factor();

        //TODO?
        //auto return_resist = vanilla_resist;
        if (a_armor_rating <= 500) {
            return vanilla_resist * 100;
        } else if (a_armor_rating < 1000) {
            auto remainder_rating = a_armor_rating - 500;
            return (0.75f + (remainder_rating / 100 * 0.03f)) * 100;
        } else {
            return 0.90f * 100;
        }
        //return return_resist;
    }  // mod
}
