#pragma once
#include "handler/showhandler.h"

class equip_manager final : public RE::BSTEventSink<RE::TESEquipEvent> {
public:
    using event_result = RE::BSEventNotifyControl;
    using show_menu = menu_util::show_menu;

    static equip_manager* get_singleton() {
        static equip_manager singleton;
        return std::addressof(singleton);
    }

    static void sink() { RE::ScriptEventSourceHolder::GetSingleton()->AddEventSink(get_singleton()); }

    equip_manager(const equip_manager&) = delete;
    equip_manager(equip_manager&&) = delete;

    equip_manager& operator=(const equip_manager&) = delete;
    equip_manager& operator=(equip_manager&&) = delete;

protected:
    auto ProcessEvent(const RE::TESEquipEvent* a_event, [[maybe_unused]] RE::BSTEventSource<RE::TESEquipEvent>* a_event_source) -> event_result override {
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
            if ([[maybe_unused]] const auto show_handler = show_handler::get_singleton();
                show_handler::is_menu_open(show_menu::m_stats_inventory)) {
                show_handler::handle_inventory_stats_update();
            }
        }

        return event_result::kContinue;
    }

private:
    equip_manager() = default;
    ~equip_manager() override = default;
};
