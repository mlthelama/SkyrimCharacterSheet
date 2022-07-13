#pragma once
#include "handler/showhandler.h"

class menu_manager final : public RE::BSTEventSink<RE::MenuOpenCloseEvent> {
public:
    using event_result = RE::BSEventNotifyControl;
    using show_menu = menu_util::show_menu;

    static menu_manager* get_singleton() {
        static menu_manager singleton;
        return std::addressof(singleton);
    }

    static void sink() { RE::UI::GetSingleton()->AddEventSink(get_singleton()); }

    menu_manager(const menu_manager&) = delete;
    menu_manager(menu_manager&&) = delete;

    menu_manager& operator=(const menu_manager&) = delete;
    menu_manager& operator=(menu_manager&&) = delete;

protected:
    event_result ProcessEvent(const RE::MenuOpenCloseEvent* a_event,
        [[maybe_unused]] RE::BSTEventSource<RE::MenuOpenCloseEvent>* a_event_source) override {
        if (!a_event) {
            return event_result::kContinue;
        }

        //sometimes it can happen, if you press menu button and inventory it opens both
        //that should not happen
        if (a_event->opening && a_event->menuName == RE::InventoryMenu::MENU_NAME) {
            if (show_handler::is_menu_open()) {
                show_handler::close_window(show_menu::m_stats);
            }

            if (*settings::show_inventory_stats_auto_open) {
                show_handler::handle_inventory_stats_open();
            }
        }

        if (!a_event->opening && a_event->menuName == RE::InventoryMenu::MENU_NAME) {
            show_handler::close_window(show_menu::m_stats_inventory);
        }

        return event_result::kContinue;
    }

private:
    menu_manager() = default;

    ~menu_manager() override = default;
};
