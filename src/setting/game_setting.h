#pragma once

namespace setting {
    class game_setting {
    public:
        [[nodiscard]] static game_setting* get_singleton();

        void set_settings();

        [[nodiscard]] float get_max_armor_resistance() const;
        [[nodiscard]] float get_max_resistance() const;
        [[nodiscard]] float get_armor_base_factor() const;
        [[nodiscard]] float get_armor_scaling_factor() const;

        game_setting(const game_setting&) = delete;
        game_setting(game_setting&&) = delete;
        game_setting& operator=(const game_setting&) = delete;
        game_setting& operator=(game_setting&&) = delete;

    private:
        game_setting() = default;
        ~game_setting() = default;

        static float get_float_setting(const char* a_name, RE::GameSettingCollection*& a_game_setting);

        float max_armor_resistance = -1;
        float max_resistance = -1;
        float armor_base_factor = -1;
        float armor_scaling_factor = -1;
    };
}
