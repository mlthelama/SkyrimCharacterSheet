#include "menu_control_hook.h"
#include "scaleform/menus/stats_inventory_menu.h"
#include "setting/input_setting.h"

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

        //TODO handle stuff from input manager here too, that is needed for the inventory/magic menus
        if (a_event && *a_event && is_menu_open(ui)) {
            for (auto* event = *a_event; event; event = event->next) {
                if (event->HasIDCode()) {
                    auto* inventory_manager = RE::Inventory3DManager::GetSingleton();
                    if (inventory_manager && inventory_manager->GetRuntimeData().zoomProgress != 0.f) {
                        scaleform::stats_inventory_menu::close();
                    } else if (inventory_manager && inventory_manager->GetRuntimeData().zoomProgress == 0.f &&
                               !scaleform::stats_inventory_menu::is_menu_open()) {
                        //TODO fix if it has been manually closed, it should not reopen
                        if (setting::input_setting::auto_open_inventory_menu_inventory() &&
                                ui->IsMenuOpen(RE::InventoryMenu::MENU_NAME) ||
                            setting::input_setting::auto_open_inventory_menu_magic() &&
                                ui->IsMenuOpen(RE::MagicMenu::MENU_NAME)) {
                            scaleform::stats_inventory_menu::open();
                        }
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
