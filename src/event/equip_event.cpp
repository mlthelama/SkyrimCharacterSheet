#include "equip_event.h"
#include "scaleform/menus/stats_inventory_menu.h"

namespace event {

    equip_event* equip_event::get_singleton() {
        static equip_event singleton;
        return std::addressof(singleton);
    }

    void equip_event::sink() { RE::ScriptEventSourceHolder::GetSingleton()->AddEventSink(get_singleton()); }

    equip_event::event_result equip_event::ProcessEvent(const RE::TESEquipEvent* a_event,
        [[maybe_unused]] RE::BSTEventSource<RE::TESEquipEvent>* a_event_source) {
        if (!a_event || !a_event->actor || !a_event->actor->IsPlayerRef()) {
            return event_result::kContinue;
        }
        const auto formid = RE::TESForm::LookupByID(a_event->baseObject);

        if (!formid) {
            return event_result::kContinue;
        }

        if (formid->IsArmor() || formid->IsWeapon() || formid->IsAmmo()) {
            logger::trace("Player {} {}"sv, (a_event->equipped ? "equipped" : "unequipped"), formid->GetName());
            //if menu is open trigger reload of data
            if (scaleform::stats_inventory_menu::is_menu_open()) {
                /*have to add it via task, so inventory is ready, might be useful for other menus as well*/
                const auto* task = SKSE::GetTaskInterface();
                task->AddUITask([]() {
                    if (const auto menu = RE::UI::GetSingleton()->GetMenu<scaleform::stats_inventory_menu>(
                            scaleform::stats_inventory_menu::menu_name)) {
                        menu->refresh_lists();
                    }
                });
            }
        }

        return event_result::kContinue;
    }
}
