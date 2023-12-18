#include "menu_control_hook.h"
#include "input/menu_key_input_holder.h"
#include "scaleform/menus/stats_inventory_menu.h"
#include "setting/input_setting.h"
#include "util/key_util.h"

namespace hook {

    void menu_control_hook::install() {
        logger::info("Hooking ..."sv);

        REL::Relocation<std::uintptr_t> menu_controls_vtbl{ RE::VTABLE_MenuControls[0] };
        process_event_ = menu_controls_vtbl.write_vfunc(0x1, &menu_control_hook::process_event);

        logger::info("Hooked."sv);
    }

    RE::BSEventNotifyControl menu_control_hook::process_event(RE::InputEvent** a_event,
        RE::BSTEventSource<RE::InputEvent*>* a_source) {
        auto* ui = RE::UI::GetSingleton();

        if (a_event && *a_event && is_menu_open(ui)) {
            auto* inventory_manager = RE::Inventory3DManager::GetSingleton();
            auto* key_input = input::menu_key_input_holder::get_singleton();

            for (auto* event = *a_event; event; event = event->next) {
                if (inventory_manager && inventory_manager->GetRuntimeData().zoomProgress != 0.f) {
                    scaleform::stats_inventory_menu::close();
                } else if (inventory_manager && inventory_manager->GetRuntimeData().zoomProgress == 0.f &&
                           !scaleform::stats_inventory_menu::is_menu_open() &&
                           !ui->IsMenuOpen(RE::BookMenu::MENU_NAME)) {
                    if (!key_input->get_menu_manual_close() &&
                            setting::input_setting::auto_open_inventory_menu_inventory() &&
                            ui->IsMenuOpen(RE::InventoryMenu::MENU_NAME) ||
                        setting::input_setting::auto_open_inventory_menu_magic() &&
                            ui->IsMenuOpen(RE::MagicMenu::MENU_NAME)) {
                        scaleform::stats_inventory_menu::open();
                        logger::info("in open auto");
                    }
                }

                if (event->eventType != RE::INPUT_EVENT_TYPE::kButton &&
                    event->eventType != RE::INPUT_EVENT_TYPE::kThumbstick) {
                    continue;
                }

                if (event->HasIDCode()) {
                    auto* button = static_cast<RE::ButtonEvent*>(event);
                    auto key = button->idCode;
                    util::key_util::get_key_id(button->device.get(), key);

                    if (button->IsUp()) {
                        key_input->remove_key_down(key);
                    }

                    if (!button->IsDown()) {
                        continue;
                    }

                    if (key_input->get_open_inventory_key_combo().contains(key) ||
                        key_input->get_close_inventory_key_combo().contains(key)) {
                        key_input->add_key_down(key);
                    }

                    if (key_input->is_down_list_equal(false) && scaleform::stats_inventory_menu::is_menu_open()) {
                        scaleform::stats_inventory_menu::close();
                        key_input->set_menu_manual_close(true);
                        logger::info("in close");
                    }
                    if (key_input->is_down_list_equal(true) && !scaleform::stats_inventory_menu::is_menu_open()) {
                        scaleform::stats_inventory_menu::open();
                        key_input->set_menu_manual_close(false);
                        logger::info("in open");
                    }
                }
            }
        }

        return process_event_(this, a_event, a_source);
    }

    bool menu_control_hook::is_menu_open(RE::UI*& a_ui) {
        return a_ui->IsMenuOpen(RE::InventoryMenu::MENU_NAME) || a_ui->IsMenuOpen(RE::MagicMenu::MENU_NAME);
    }
}  // hook
