#include "menu_open_close_event.h"
#include "handler/show_handler.h"

namespace event {

    menu_open_close_event* menu_open_close_event::get_singleton() {
        static menu_open_close_event singleton;
        return std::addressof(singleton);
    }

    void menu_open_close_event::sink() { RE::UI::GetSingleton()->AddEventSink(get_singleton()); }
    menu_open_close_event::event_result menu_open_close_event::ProcessEvent(const RE::MenuOpenCloseEvent* a_event,
        [[maybe_unused]] RE::BSTEventSource<RE::MenuOpenCloseEvent>* a_event_source) {
        if (!a_event) {
            return event_result::kContinue;
        }

        //sometimes it can happen, if you press menu button and inventory it opens both
        //that should not happen
        if (a_event->opening &&
            (a_event->menuName == RE::InventoryMenu::MENU_NAME || a_event->menuName == RE::MagicMenu::MENU_NAME)) {
            if (handler::show_handler::is_menu_open()) {
                handler::show_handler::close_window(setting_data::menu_data::menu_type::stats);
                handler::show_handler::close_window(setting_data::menu_data::menu_type::faction);
            }

            if ((ini_setting::get_show_inventory_stats_auto_open() &&
                    a_event->menuName == RE::InventoryMenu::MENU_NAME) ||
                (ini_setting::get_show_inventory_stats_auto_open_magic_menu() &&
                    a_event->menuName == RE::MagicMenu::MENU_NAME)) {
                handler::show_handler::handle_inventory_stats_open();
            }
        }

        if (!a_event->opening &&
            (a_event->menuName == RE::InventoryMenu::MENU_NAME || a_event->menuName == RE::MagicMenu::MENU_NAME)) {
            handler::show_handler::close_window(setting_data::menu_data::menu_type::stats_inventory);
        }

        return event_result::kContinue;
    }
}
