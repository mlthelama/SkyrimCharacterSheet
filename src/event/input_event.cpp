#include "input_event.h"
#include "handler/show_handler.h"
#include "setting/ini_setting.h"

namespace event {

    input_event* input_event::get_singleton() {
        static input_event singleton;
        return std::addressof(singleton);
    }

    void input_event::sink() { RE::BSInputDeviceManager::GetSingleton()->AddEventSink(get_singleton()); }
    input_event::event_result input_event::ProcessEvent(RE::InputEvent* const* a_event,
        [[maybe_unused]] RE::BSTEventSource<RE::InputEvent*>* a_event_source) {
        key_ = static_cast<uint32_t>(ini_setting::get_open_menu_button());

        if (key_ == k_invalid) {
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
            const auto* button = static_cast<RE::ButtonEvent*>(event);
            // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)
            if (!button->IsDown()) {
                continue;
            }

            auto key = button->idCode;
            auto device = button->device.get();
            switch (device) {
                case RE::INPUT_DEVICE::kMouse:
                    key += k_mouse_offset;
                    break;
                case RE::INPUT_DEVICE::kKeyboard:
                    key += k_keyboard_offset;
                    break;
                case RE::INPUT_DEVICE::kGamepad:
                    key = get_gamepad_index(static_cast<RE::BSWin32GamepadDevice::Key>(key));
                    break;
                default:
                    continue;
            }


            if (ui->IsMenuOpen(RE::InventoryMenu::MENU_NAME) || ui->IsMenuOpen(RE::MagicMenu::MENU_NAME)) {
                if (key == static_cast<uint32_t>(ini_setting::get_show_inventory_button())) {
                    logger::debug("configured Key ({}) for Inventory pressed"sv, key);
                    if (!handler::show_handler::is_menu_open(setting_data::menu_data::menu_type::stats_inventory)) {
                        handler::show_handler::handle_inventory_stats_open();
                    } else {
                        handler::show_handler::close_window(setting_data::menu_data::menu_type::stats_inventory);
                    }
                }
            }

            if (auto* control_map = RE::ControlMap::GetSingleton(); !control_map->IsMovementControlsEnabled()) {
                continue;
            }

            /*if the game is not paused with the menu, it triggers the menu always in the background*/
            if (ui->GameIsPaused() && !handler::show_handler::is_menu_open()) {
                continue;
            }

            //for whatever reason I can open the menu while at a crafting station
            //so let that not happen
            if (ui->IsMenuOpen(RE::CraftingMenu::MENU_NAME)) {
                continue;
            }

            if (key == key_) {
                logger::debug("configured Key ({}) pressed"sv, key);
                handler::show_handler::handle_main_button_press();
                break;
            }
            if (handler::show_handler::is_menu_open() && key == RE::BSWin32KeyboardDevice::Key::kEscape) {
                handler::show_handler::close_all_windows();
                break;
            }
            if (key == static_cast<uint32_t>(ini_setting::get_open_faction_menu_button())) {
                logger::debug("next menu Key ({}) pressed"sv, key);
                handler::show_handler::handle_next_menu_button_press();
                break;
            }
        }
        return event_result::kContinue;
    }

    uint32_t input_event::get_gamepad_index(RE::BSWin32GamepadDevice::Key a_key) {
        using key = RE::BSWin32GamepadDevice::Key;

        uint32_t index;
        switch (a_key) {
            case key::kUp:
                index = 0;
                break;
            case key::kDown:
                index = 1;
                break;
            case key::kLeft:
                index = 2;
                break;
            case key::kRight:
                index = 3;
                break;
            case key::kStart:
                index = 4;
                break;
            case key::kBack:
                index = 5;
                break;
            case key::kLeftThumb:
                index = 6;
                break;
            case key::kRightThumb:
                index = 7;
                break;
            case key::kLeftShoulder:
                index = 8;
                break;
            case key::kRightShoulder:
                index = 9;
                break;
            case key::kA:
                index = 10;
                break;
            case key::kB:
                index = 11;
                break;
            case key::kX:
                index = 12;
                break;
            case key::kY:
                index = 13;
                break;
            case key::kLeftTrigger:
                index = 14;
                break;
            case key::kRightTrigger:
                index = 15;
                break;
            default:
                index = k_invalid;
                break;
        }

        return index != k_invalid ? index + k_gamepad_offset : k_invalid;
    }


}
