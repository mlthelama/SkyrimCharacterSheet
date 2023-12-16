#pragma once

namespace setting {
    class input_setting {
    public:
        static void load_setting();

        static bool get_is_debug();

        static std::vector<uint32_t> get_open_menu_key_combination();

        static std::vector<uint32_t> get_close_menu_key_combination();

        static std::vector<uint32_t> get_next_page_menu_key_list();

        static std::vector<uint32_t> get_previous_page_menu_key_list();

        static bool get_menu_pause_game();

        static std::vector<uint32_t> get_open_inventory_menu_key_combination();

        static std::vector<uint32_t> get_close_inventory_menu_key_combination();

        static bool is_inventory_menu_enabled();

        static bool auto_open_inventory_menu_inventory();

        static bool auto_open_inventory_menu_magic();

        static void log();
    };
}  // setting
