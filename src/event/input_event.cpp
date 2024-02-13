#include "input_event.h"
#include "input/menu_key_input_holder.h"
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
        if (!a_event) {
            return event_result::kContinue;
        }

        auto* key_input = input::menu_key_input_holder::get_singleton();
        open_key_combo_ = key_input->get_open_key_combo();
        close_key_combo_ = key_input->get_close_key_combo();

        if (is_one_combo_empty()) {
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

            auto key = button->idCode;
            util::key_util::get_key_id(button->device.get(), key);

            if (button->IsUp()) {
                key_input->remove_key_down(key);
            }

            if (!button->IsDown()) {
                continue;
            }

            if (auto* control_map = RE::ControlMap::GetSingleton(); !control_map->IsMovementControlsEnabled()) {
                continue;
            }

            /*if the game is not paused with the menu, it triggers the menu always in the background*/
            if (ui->GameIsPaused() &&
                !(scaleform::stats_menu::is_menu_open() || scaleform::faction_menu::is_menu_open())) {
                continue;
            }
            
            if (ui->IsItemMenuOpen() ) {
                continue;
            }
            

            //for whatever reason I can open the menu while at a crafting station
            //so let that not happen
            if (ui->IsMenuOpen(RE::CraftingMenu::MENU_NAME) ||
                input::menu_key_input_holder::is_one_ignore_menu_open()) {
                continue;
            }

            if (open_key_combo_.contains(key) || close_key_combo_.contains(key)) {
                key_input->add_key_down(key);
            }

            if (key_input->is_down_list_equal(false)) {
                if (scaleform::stats_menu::is_menu_open()) {
                    scaleform::stats_menu::close();
                    key_input->clear_set();
                }
                if (scaleform::faction_menu::is_menu_open()) {
                    scaleform::faction_menu::close();
                    key_input->clear_set();
                }
            }
            if (key_input->is_down_list_equal(true)) {
                if (!scaleform::stats_menu::is_menu_open() && !scaleform::faction_menu::is_menu_open()) {
                    scaleform::stats_menu::open();
                    key_input->clear_set();
                }
            }
        }

        return event_result::kContinue;
    }

    bool input_event::is_one_combo_empty() { return open_key_combo_.empty() || close_key_combo_.empty(); }
}
