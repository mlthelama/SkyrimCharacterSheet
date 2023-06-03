#include "show_handler.h"

namespace handler {
    show_handler* show_handler::get_singleton() {
        static show_handler singleton;
        return std::addressof(singleton);
    }

    void show_handler::close_window(const show_handler::show_menu a_menu) {
        switch (a_menu) {
            case show_menu::m_stats:
                scaleform::stats_menu::close();
                break;
            case show_menu::m_faction:
                scaleform::faction_menu::close();
                break;
            case show_menu::m_stats_inventory:
                scaleform::stats_inventory_menu::close();
        }
    }

    void show_handler::swap_window(const show_handler::show_menu a_menu_open,
        const show_handler::show_menu a_menu_close) {
        close_window(a_menu_close);
        show_window(a_menu_open);
    }

    void show_handler::close_all_windows() {
        close_window(show_menu::m_stats);
        close_window(show_menu::m_faction);
        close_window(show_menu::m_stats_inventory);
    }

    void show_handler::handle_main_button_press() {
        if (scaleform::stats_menu::is_menu_open()) {
            close_window(show_menu::m_stats);
        } else if (scaleform::faction_menu::is_menu_open()) {
            close_window(show_menu::m_faction);
        } else {
            show_window(show_menu::m_stats);
        }
    }

    void show_handler::handle_next_menu_button_press() {
        if (scaleform::stats_menu::is_menu_open()) {
            logger::debug("{} is open, open {}"sv,
                scaleform::stats_menu::menu_name,
                scaleform::faction_menu::menu_name);
            swap_window(show_menu::m_faction, show_menu::m_stats);
        } else if (scaleform::faction_menu::is_menu_open()) {
            logger::debug("{} is open, open {}"sv,
                scaleform::faction_menu::menu_name,
                scaleform::stats_menu::menu_name);
            swap_window(show_menu::m_stats, show_menu::m_faction);
        }
    }

    bool show_handler::is_menu_open() {
        return (scaleform::stats_menu::is_menu_open() || scaleform::faction_menu::is_menu_open());
    }

    bool show_handler::is_menu_open(const show_handler::show_menu a_menu_open) {
        return RE::UI::GetSingleton()->IsMenuOpen(get_menu_scaleform_name(a_menu_open));
    }

    void show_handler::handle_inventory_stats_open() {
        if (!scaleform::stats_inventory_menu::is_menu_open()) {
            show_window(show_menu::m_stats_inventory);
        }
    }

    void show_handler::handle_inventory_stats_update() {
        if (scaleform::stats_inventory_menu::is_menu_open()) {
            /*have to add it via task, so inventory is ready, might be useful for other menus as well*/
            const auto* task = SKSE::GetTaskInterface();
            task->AddUITask([]() {
                if (const auto menu = RE::UI::GetSingleton()->GetMenu<scaleform::stats_inventory_menu>(
                        scaleform::stats_inventory_menu::menu_name)) {
                    menu->refresh_lists();
                }
            });
        }
    }

    void show_handler::handle_menu_swap(const show_handler::show_menu a_menu) { show_window(a_menu); }

    std::string_view show_handler::get_menu_scaleform_name(const show_handler::show_menu a_menu) {
        if (!menu_scale_form_name_.contains(a_menu)) {
            logger::warn("can not find Scaleform Name for Menu {}"sv, string_util::get_int_from_enum(a_menu));
            return "";
        }
        return menu_scale_form_name_.find(a_menu)->second;
    }

    void show_handler::show_window(const show_handler::show_menu a_menu) {
        logger::trace("Show Window {}"sv, get_menu_scaleform_name(a_menu));
        switch (a_menu) {
            case show_menu::m_stats:
                scaleform::stats_menu::open();
                break;
            case show_menu::m_faction:
                scaleform::faction_menu::open();
                break;
            case show_menu::m_stats_inventory:
                scaleform::stats_inventory_menu::open();
                break;
        }
    }
}
