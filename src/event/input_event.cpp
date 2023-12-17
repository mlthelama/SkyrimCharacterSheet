#include "input_event.h"
#include "scaleform/menus/faction_menu.h"
#include "scaleform/menus/stats_inventory_menu.h"
#include "scaleform/menus/stats_menu.h"
#include "setting/ini_setting.h"
#include "setting/input_setting.h"

namespace event {

    input_event* input_event::get_singleton() {
        static input_event singleton;
        return std::addressof(singleton);
    }

    void input_event::sink() { RE::BSInputDeviceManager::GetSingleton()->AddEventSink(get_singleton()); }
    input_event::event_result input_event::ProcessEvent(RE::InputEvent* const* a_event,
        [[maybe_unused]] RE::BSTEventSource<RE::InputEvent*>* a_event_source) {
        key_ = static_cast<uint32_t>(ini_setting::get_open_menu_button());

        if (key_ == util::key_util::k_invalid) {
            return event_result::kContinue;
        }

        if (!a_event) {
            return event_result::kContinue;
        }

        auto* ui = RE::UI::GetSingleton();
        auto* intfc_str = RE::InterfaceStrings::GetSingleton();

        if (ui->IsMenuOpen(intfc_str->console)) {
            return event_result::kContinue;
        }

        for (auto* event = *a_event; event; event = event->next) {
            if (event->eventType != RE::INPUT_EVENT_TYPE::kButton) {
                continue;
            }

            //this stays static_cast
            auto* button = static_cast<RE::ButtonEvent*>(event);
            // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)
            if (!button->IsDown()) {
                continue;
            }

            auto key = button->idCode;
            util::key_util::get_key_id(button->device.get(), key);

            if (ui->IsMenuOpen(RE::InventoryMenu::MENU_NAME) || ui->IsMenuOpen(RE::MagicMenu::MENU_NAME)) {
                if (key == static_cast<uint32_t>(ini_setting::get_show_inventory_button())) {
                    logger::debug("configured Key ({}) for Inventory pressed"sv, key);
                    if (!scaleform::stats_inventory_menu::is_menu_open()) {
                        scaleform::stats_inventory_menu::open();
                    } else {
                        scaleform::stats_inventory_menu::close();
                    }
                }
            }

            if (auto* control_map = RE::ControlMap::GetSingleton(); !control_map->IsMovementControlsEnabled()) {
                continue;
            }

            /*if the game is not paused with the menu, it triggers the menu always in the background*/
            if (ui->GameIsPaused() &&
                !(scaleform::stats_menu::is_menu_open() || scaleform::faction_menu::is_menu_open())) {
                continue;
            }

            //for whatever reason I can open the menu while at a crafting station
            //so let that not happen
            if (ui->IsMenuOpen(RE::CraftingMenu::MENU_NAME)) {
                continue;
            }

            //logger::info("user event {}, id {}"sv, button->userEvent, button->idCode);

            if (key == key_) {
                logger::debug("configured Key ({}) pressed"sv, key);
                if (scaleform::stats_menu::is_menu_open()) {
                    scaleform::stats_menu::close();
                } else if (scaleform::faction_menu::is_menu_open()) {
                    scaleform::faction_menu::close();
                } else {
                    scaleform::stats_menu::open();
                }
                break;
            }
        }
        return event_result::kContinue;
    }

}
