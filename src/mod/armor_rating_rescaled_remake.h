#pragma once

namespace mod {
    class armor_rating_rescaled_remake {
    public:
        static void load_config();

        static double get_scaling_factor();
        static bool get_disable_hidden();
        static int get_overwrite_armor_cap();
    };
}  // mod
