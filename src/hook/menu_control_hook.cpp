﻿#include "menu_control_hook.h"
#include "input/menu_key_input_holder.h"
#include "scaleform/menus/stats_inventory_menu.h"
#include "scaleform/menus/stats_menu.h"
#include "setting/data/menu_data.h"
#include "setting/input_setting.h"
#include "util/key_util.h"

namespace hook {

    using menu_type = setting_data::menu_data::menu_type;

    void menu_control_hook::install() {
        logger::info("Hooking ..."sv);

        REL::Relocation<std::uintptr_t> menu_controls_vtbl{ RE::VTABLE_MenuControls[0] };
        process_event_ = menu_controls_vtbl.write_vfunc(0x1, &menu_control_hook::process_event);

        logger::info("Hooked."sv);
    }

    RE::BSEventNotifyControl menu_control_hook::process_event(RE::MenuControls* a_menuControls,
        RE::InputEvent* const* a_event,
        RE::BSTEventSource<RE::InputEvent*>* a_eventSource) {
        auto* ui = RE::UI::GetSingleton();
        auto* key_input = input::menu_key_input_holder::get_singleton();

        if (setting::input_setting::get_tween_menu_only()) {
            auto IsTopMostInteractionMenu = [](const RE::UI* ui, const RE::GPtr<RE::IMenu>& iMenu) -> bool {
                for (auto iter = ui->menuStack.end() - 1; iter >= ui->menuStack.begin(); iter--) {
                    auto menu = iter->get();
                    if (menu && (menu->inputContext.get() < RE::IMenu::Context::kTotal || menu->PausesGame() ||
                                    menu->UsesCursor())) {
                        return menu == iMenu.get();
                    }
                }

                return false;
            };

            const auto menuStringsHolder = RE::InterfaceStrings::GetSingleton();
            const auto tweenMenu = ui->GetMenu<RE::TweenMenu>(menuStringsHolder->tweenMenu);

            if (a_event && *a_event && !a_menuControls->remapMode && !a_menuControls->isProcessing && tweenMenu &&
                tweenMenu->OnStack() && IsTopMostInteractionMenu(ui, tweenMenu) &&
                !ui->IsMenuOpen(menuStringsHolder->inventoryMenu)) {
                for (auto* event = *a_event; event; event = event->next) {
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

                        if (key_input->get_open_key_combo().contains(key) ||
                            key_input->get_close_key_combo().contains(key)) {
                            key_input->add_key_down(key);
                        }

                        if (key_input->is_down_list_equal(true)) {
                            TweenMenu_CloseTweenMenu();
                            scaleform::stats_menu::open();
                            key_input->clear_set();
                            return RE::BSEventNotifyControl::kStop;
                        }
                    }
                }
            }
        }

        if (a_event && *a_event && is_menu_open(ui)) {
            auto* inventory_manager = RE::Inventory3DManager::GetSingleton();
            auto* control_map = RE::ControlMap::GetSingleton();

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

                    if (control_map->GetRuntimeData().textEntryCount > 0) {
                        logger::trace("continue. due text input, count {}"sv,
                            control_map->GetRuntimeData().textEntryCount);
                        continue;
                    }

                    if (key_input->get_inventory_open_key_combo().contains(key) ||
                        key_input->get_inventory_close_key_combo().contains(key)) {
                        key_input->add_key_down(key);
                    }

                    if (key_input->is_down_list_equal(false, menu_type::stats_inventory) &&
                        scaleform::stats_inventory_menu::is_menu_open()) {
                        scaleform::stats_inventory_menu::close();
                        key_input->set_menu_manual_close(true);
                        key_input->clear_set();
                    }
                    if (key_input->is_down_list_equal(true, menu_type::stats_inventory) &&
                        !scaleform::stats_inventory_menu::is_menu_open()) {
                        scaleform::stats_inventory_menu::open();
                        key_input->set_menu_manual_close(false);
                        key_input->clear_set();
                    }
                }
            }
        }

        return process_event_(a_menuControls, a_event, a_eventSource);
    }

    bool menu_control_hook::is_menu_open(RE::UI*& a_ui) {
        return a_ui->IsMenuOpen(RE::InventoryMenu::MENU_NAME) || a_ui->IsMenuOpen(RE::MagicMenu::MENU_NAME);
    }

    void menu_control_hook::TweenMenu_CloseTweenMenu() {
        using func_t = decltype(&menu_control_hook::TweenMenu_CloseTweenMenu);
        REL::Relocation<func_t> func{ REL::VariantID(51839, 52711, 0x8FE180) };
        return func();
    }
}  // hook
