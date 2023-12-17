#include "input_event.h"
#include "scaleform/menus/faction_menu.h"
#include "scaleform/menus/stats_inventory_menu.h"
#include "scaleform/menus/stats_menu.h"
#include "setting/input_setting.h"

namespace event {

    input_event* input_event::get_singleton() {
        static input_event singleton;
        return std::addressof(singleton);
    }

    void input_event::sink() { RE::BSInputDeviceManager::GetSingleton()->AddEventSink(get_singleton()); }

    input_event::event_result input_event::ProcessEvent(RE::InputEvent* const* a_event,
        [[maybe_unused]] RE::BSTEventSource<RE::InputEvent*>* a_event_source) {
        open_key_combo_ = setting::input_setting::get_open_menu_key_combination();
        close_key_combo_ = setting::input_setting::get_close_menu_key_combination();
        open_inventory_key_combo_ = setting::input_setting::get_open_inventory_menu_key_combination();
        close_inventory_key_combo_ = setting::input_setting::get_open_inventory_menu_key_combination();

        if (is_one_combo_empty()) {
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

        //clear_key_down(key_down_list_);
        for (auto* event = *a_event; event; event = event->next) {
            if (event->eventType != RE::INPUT_EVENT_TYPE::kButton) {
                continue;
            }

            //this stays static_cast
            auto* button = static_cast<RE::ButtonEvent*>(event);
            // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)

            auto key = button->idCode;
            util::key_util::get_key_id(button->device.get(), key);

            if (button->IsUp()) {
                remove_key_down(key_down_list_, key);
            }

            if (!button->IsDown()) {
                continue;
            }

            if (open_key_combo_.contains(key) || close_key_combo_.contains(key) ||
                open_inventory_key_combo_.contains(key) || close_inventory_key_combo_.contains(key)) {
                add_key_down(key_down_list_, key);
            }

            if (ui->IsMenuOpen(RE::InventoryMenu::MENU_NAME) || ui->IsMenuOpen(RE::MagicMenu::MENU_NAME)) {
                if (close_inventory_key_combo_ == key_down_list_ && scaleform::stats_inventory_menu::is_menu_open()) {
                    log_combo_set(close_inventory_key_combo_, key_down_list_);
                    scaleform::stats_inventory_menu::close();
                }
                if (open_inventory_key_combo_ == key_down_list_ && !scaleform::stats_inventory_menu::is_menu_open()) {
                    log_combo_set(open_inventory_key_combo_, key_down_list_);
                    scaleform::stats_inventory_menu::open();
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

            if (close_key_combo_ == key_down_list_) {
                log_combo_set(close_key_combo_, key_down_list_);
                if (scaleform::stats_menu::is_menu_open()) {
                    scaleform::stats_menu::close();
                }
                if (scaleform::faction_menu::is_menu_open()) {
                    scaleform::faction_menu::close();
                }
            }
            if (open_key_combo_ == key_down_list_) {
                log_combo_set(open_key_combo_, key_down_list_);
                if (!scaleform::stats_menu::is_menu_open() && !scaleform::faction_menu::is_menu_open()) {
                    scaleform::stats_menu::open();
                }
            }
        }

        return event_result::kContinue;
    }

    void input_event::add_key_down(std::set<uint32_t>& a_set, uint32_t key) {
        a_set.insert(key);
        if (!a_set.empty()) {
            logger::trace("size {}, down list {}"sv, a_set.size(), util::type_util::get_delimited_string(a_set));
        }
    }

    void input_event::remove_key_down(std::set<uint32_t>& a_set, uint32_t key) {
        a_set.erase(key);
        if (!a_set.empty()) {
            logger::trace("size {}, down list {}"sv, a_set.size(), util::type_util::get_delimited_string(a_set));
        }
    }

    bool input_event::is_one_combo_empty() {
        return open_key_combo_.empty() || close_key_combo_.empty() || open_inventory_key_combo_.empty() ||
               close_inventory_key_combo_.empty();
    }

    void input_event::log_combo_set(std::set<uint32_t>& a_needed, std::set<uint32_t>& a_down) {
        logger::trace("key combo needed {}, down list {}"sv,
            util::type_util::get_delimited_string(a_needed),
            util::type_util::get_delimited_string(a_down));
    }
}
