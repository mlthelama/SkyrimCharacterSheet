﻿#include "menu_open_close_event.h"
#include "input/menu_key_input_holder.h"
#include "scaleform/menus/faction_menu.h"
#include "scaleform/menus/stats_inventory_menu.h"
#include "scaleform/menus/stats_menu.h"
#include "scaleform/menus/tween_hint_menu.h"
#include "setting/input_setting.h"

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
        if (a_event->opening) {
            if (a_event->menuName == RE::InventoryMenu::MENU_NAME || a_event->menuName == RE::MagicMenu::MENU_NAME) {
                if (scaleform::stats_menu::is_menu_open() || scaleform::faction_menu::is_menu_open()) {
                    scaleform::stats_menu::close();
                    scaleform::faction_menu::close();
                }

                if ((setting::input_setting::auto_open_inventory_menu_inventory() &&
                        a_event->menuName == RE::InventoryMenu::MENU_NAME) ||
                    (setting::input_setting::auto_open_inventory_menu_magic() &&
                        a_event->menuName == RE::MagicMenu::MENU_NAME)) {
                    scaleform::stats_inventory_menu::open();
                }
            }

            if (a_event->menuName == RE::BookMenu::MENU_NAME) {
                if (scaleform::stats_inventory_menu::is_menu_open()) {
                    scaleform::stats_inventory_menu::close();
                }
            }
        }

        if (!a_event->opening) {
            if (a_event->menuName == RE::InventoryMenu::MENU_NAME || a_event->menuName == RE::MagicMenu::MENU_NAME) {
                scaleform::stats_inventory_menu::close();
            }
        }

        if (setting::input_setting::get_tween_menu_only() && a_event->menuName == RE::TweenMenu::MENU_NAME) {
            if (a_event->opening) {
                scaleform::tween_hint_menu::open();
            } else {
                scaleform::tween_hint_menu::close();
            }
        }

        if (a_event->menuName == scaleform::stats_menu::menu_name ||
            a_event->menuName == scaleform::faction_menu::menu_name ||
            a_event->menuName == scaleform::stats_inventory_menu::menu_name) {
            auto* key_input = input::menu_key_input_holder::get_singleton();
            key_input->clear_set();
        }

        return event_result::kContinue;
    }
}
