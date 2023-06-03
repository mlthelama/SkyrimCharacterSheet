#pragma once

namespace mod {
    class armor_rating_rescaled_remake {
    public:
        static void load_config();

        [[maybe_unused]] static double get_scaling_factor();
        [[maybe_unused]] static bool get_disable_hidden();
        [[maybe_unused]] static int get_overwrite_armor_cap();

        static float calculate_armor_damage_resistance(float a_armor_rating, int32_t a_pieces_worn);
    };
}  // mod
