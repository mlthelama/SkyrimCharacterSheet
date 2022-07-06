#pragma once

class game_settings {
public:
    static game_settings* get_singleton() {
        static game_settings singleton;
        return std::addressof(singleton);
    }

    void get_and_set_settings() {
        auto game_setting = RE::GameSettingCollection::GetSingleton();
        max_armor_resistance = get_float_setting("fMaxArmorRating", game_setting);
        max_resistance = get_float_setting("fPlayerMaxResistance", game_setting);
        armor_base_factor = get_float_setting("fArmorBaseFactor", game_setting);
        armor_scaling_factor = get_float_setting("fArmorScalingFactor", game_setting);

        logger::debug("fMaxArmorRating {}, fPlayerMaxResistance {}, fArmorBaseFactor {}, fArmorScalingFactor {}"sv,
            max_armor_resistance,
            max_resistance,
            armor_base_factor,
            armor_scaling_factor);
    }

    float max_armor_resistance = -1;
    float max_resistance = -1;
    float armor_base_factor = -1;
    float armor_scaling_factor = -1;

protected:
    game_settings() = default;
    game_settings(const game_settings&) = delete;
    game_settings(game_settings&&) = delete;

    ~game_settings() = default;

    game_settings& operator=(const game_settings&) = delete;
    game_settings& operator=(game_settings&&) = delete;

private:
    static float get_float_setting(const char* a_name, RE::GameSettingCollection*& a_game_setting) {
        return a_game_setting->GetSetting(a_name)->GetFloat();
    }
};
