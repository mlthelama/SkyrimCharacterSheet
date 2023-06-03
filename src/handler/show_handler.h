#pragma once
#include "scaleform/menus/faction_menu.h"
#include "scaleform/menus/stats_inventory_menu.h"
#include "scaleform/menus/stats_menu.h"

namespace handler {
    class show_handler {
        using show_menu = menu_util::show_menu;

    public:
        static show_handler* get_singleton();

        static void close_window(show_menu a_menu);

        static void swap_window(show_menu a_menu_open, show_menu a_menu_close);

        static void close_all_windows();

        static void handle_main_button_press();

        static void handle_next_menu_button_press();

        static bool is_menu_open();

        static bool is_menu_open(show_menu a_menu_open);

        static void handle_inventory_stats_open();

        static void handle_inventory_stats_update();

        static void handle_menu_swap(show_menu a_menu);

        show_handler() = default;
        show_handler(const show_handler&) = delete;
        show_handler(show_handler&&) = delete;
        ~show_handler() = default;

        show_handler& operator=(const show_handler&) = delete;
        show_handler& operator=(show_handler&&) = delete;

    private:
        inline static std::map<show_menu, std::string_view> menu_scale_form_name_ = {
            { show_menu::m_stats, scaleform::stats_menu::menu_name },
            { show_menu::m_faction, scaleform::faction_menu::menu_name },
            { show_menu::m_stats_inventory, scaleform::stats_inventory_menu::menu_name }
        };

        static std::string_view get_menu_scaleform_name(show_menu a_menu);

        static void show_window(show_menu a_menu);
    };
}
