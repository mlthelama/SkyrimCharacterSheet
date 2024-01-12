#include "blade_and_blunt.h"
#include "setting/game_setting.h"

namespace mod {
    float blade_and_blunt::calculate_armor_damage_resistance(float a_vanilla) {
        const auto game_settings = setting::game_setting::get_singleton();
        auto vanilla = a_vanilla / 100;
        auto factor = game_settings->get_armor_scaling_factor();
        auto armor_rating = (vanilla / factor) * 100;

        if (armor_rating <= 500) {
            return vanilla * 100;
        } else if (armor_rating < 1000) {
            auto remainderRating = armor_rating - 500;
            //bb sets base factor to 0
            return (0.75f + (remainderRating / 100 * 0.03f)) * 100;
        } else {
            return 0.90f * 100;
        }

    }  // mod
}
