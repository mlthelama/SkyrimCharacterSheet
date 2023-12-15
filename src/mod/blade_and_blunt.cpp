#include "blade_and_blunt.h"
#include "setting/game_setting.h"

namespace mod {
    float blade_and_blunt::calculate_armor_damage_resistance(float a_vanilla) {
        const auto game_settings = setting::game_setting::get_singleton();
        auto factor = game_settings->get_armor_scaling_factor();
        auto armor_rating = (a_vanilla / factor) * 100;
        
        if (armor_rating <= 500) {
            return a_vanilla;
        } else if (armor_rating < 1000) {
            auto remainderRating = armor_rating - 500;
            return 0.75f + (remainderRating / 100 * game_settings->get_armor_base_factor());
        } else {
            return 0.90f;
        }
        
    }  // mod
}
