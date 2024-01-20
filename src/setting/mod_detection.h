#pragma once

namespace setting {
    class mod_detection {
    public:
        static void load_setting();

        static void log();

        static bool get_armor_rating_rescaled_remake();

        static bool get_hand_to_hand();

        static bool get_skyrim_unbound();

        static bool get_skyrim_souls();

        static bool get_blade_and_blunt();

        static bool get_wait_menu_redirected();
    };
}  // setting
