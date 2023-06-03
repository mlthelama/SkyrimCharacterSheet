#include "game_setting.h"

namespace setting {

    game_setting* game_setting::get_singleton() {
        static game_setting singleton;
        return std::addressof(singleton);
    }

    void game_setting::set_settings() {
        auto* game_setting = RE::GameSettingCollection::GetSingleton();
        max_armor_resistance = get_float_setting("fMaxArmorRating", game_setting);
        max_resistance = get_float_setting("fPlayerMaxResistance", game_setting);
        armor_base_factor = get_float_setting("fArmorBaseFactor", game_setting);
        armor_scaling_factor = get_float_setting("fArmorScalingFactor", game_setting);

        logger::debug(
            "set game setting. fMaxArmorRating {}, fPlayerMaxResistance {}, fArmorBaseFactor {}, fArmorScalingFactor {}"sv,
            max_armor_resistance,
            max_resistance,
            armor_base_factor,
            armor_scaling_factor);
    }

    float game_setting::get_max_armor_resistance() const { return max_armor_resistance; }

    float game_setting::get_max_resistance() const { return max_resistance; }

    float game_setting::get_armor_base_factor() const { return armor_base_factor; }

    float game_setting::get_armor_scaling_factor() const { return armor_scaling_factor; }

    float game_setting::get_float_setting(const char* a_name, RE::GameSettingCollection*& a_game_setting) {
        return a_game_setting->GetSetting(a_name)->GetFloat();
    }
}
