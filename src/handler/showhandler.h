#pragma once
#include "scaleform/menus/factionmenu.h"
#include "scaleform/menus/statsinventorymenu.h"
#include "scaleform/menus/statsmenu.h"

class show_handler {
    using show_menu = menu_util::show_menu;

public:
    static show_handler* get_singleton() {
        static show_handler singleton;
        return std::addressof(singleton);
    }

    static void close_window(const show_menu a_menu) {
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

    static void swap_window(const show_menu a_menu_open, const show_menu a_menu_close) {
        close_window(a_menu_close);
        show_window(a_menu_open);
    }

    static void close_all_windows() {
        close_window(show_menu::m_stats);
        close_window(show_menu::m_faction);
        close_window(show_menu::m_stats_inventory);
    }

    static void handle_main_button_press() {
        if (scaleform::stats_menu::is_menu_open()) {
            close_window(show_menu::m_stats);
        } else if (scaleform::faction_menu::is_menu_open()) {
            close_window(show_menu::m_faction);
        } else {
            show_window(show_menu::m_stats);
        }
    }

    static void handle_next_menu_button_press() {
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

    static bool is_menu_open() {
        return (scaleform::stats_menu::is_menu_open() || scaleform::faction_menu::is_menu_open());
    }

    static bool is_menu_open(const show_menu a_menu_open) {
        return RE::UI::GetSingleton()->IsMenuOpen(get_menu_scaleform_name(a_menu_open));
    }

    static void handle_inventory_stats_open() {
        if (!scaleform::stats_inventory_menu::is_menu_open()) {
            show_window(show_menu::m_stats_inventory);
        }
    }

    static void handle_inventory_stats_update() {
        if (scaleform::stats_inventory_menu::is_menu_open()) {
            /*have to add it via task, so inventory is ready, might be useful for other menus as well*/
            const auto task = SKSE::GetTaskInterface();
            task->AddUITask([]() {
                if (const auto menu = RE::UI::GetSingleton()->GetMenu<scaleform::stats_inventory_menu>(
                    scaleform::stats_inventory_menu::menu_name)) {
                    menu->refresh_lists();
                }
            });
        }
    }

    static void handle_menu_swap(const show_menu a_menu) { show_window(a_menu); }

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

    static std::string_view get_menu_scaleform_name(show_menu a_menu) {
        if (!menu_scale_form_name_.contains(a_menu)) {
            logger::warn("can not find Scaleform Name for Menu {}"sv, a_menu);
            return "";
        }
        return menu_scale_form_name_.find(a_menu)->second;
    }

    static void show_window(const show_menu a_menu) {
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
};
