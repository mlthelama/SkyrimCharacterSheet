#include "equip_event.h"
#include "handler/show_handler.h"

namespace event {
    using show_menu = menu_util::show_menu;

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
            if (handler::show_handler::is_menu_open(show_menu::m_stats_inventory)) {
                handler::show_handler::handle_inventory_stats_update();
            }
        }

        return event_result::kContinue;
    }
}
