#pragma once
#include "handler/showhandler.h"

class EquipManager : public RE::BSTEventSink<RE::TESEquipEvent> {
public:
    using EventResult = RE::BSEventNotifyControl;
    using ShowMenu = MenuUtil::ShowMenu;

    static EquipManager* GetSingleton() {
        static EquipManager singleton;
        return std::addressof(singleton);
    }

    auto ProcessEvent(const RE::TESEquipEvent* a_event,
        [[maybe_unused]] RE::BSTEventSource<RE::TESEquipEvent>* a_eventSource) -> EventResult {
        if (!a_event || !a_event->actor || !a_event->actor->IsPlayerRef()) {
            return EventResult::kContinue;
        }
        auto formid = RE::TESForm::LookupByID(a_event->baseObject);

        if (!formid) {
            return EventResult::kContinue;
        }

        if (formid->IsArmor() || formid->IsWeapon() || formid->IsAmmo()) {
            logger::trace("Player {} {}"sv, (a_event->equipped ? "equipped" : "unequipped"), formid->GetName());
            //if menu is open trigger reload of data
            auto showHandler = ShowHandler::GetSingleton();
            if (showHandler->IsMenuOpen(ShowMenu::mStatsInventory)) {
                showHandler->HandleInventoryStatsUpdate();
            }
        }

        return EventResult::kContinue;
    }

    static void Sink() { RE::ScriptEventSourceHolder::GetSingleton()->AddEventSink(EquipManager::GetSingleton()); }

private:
    EquipManager() = default;
    EquipManager(const EquipManager&) = delete;
    EquipManager(EquipManager&&) = delete;
    virtual ~EquipManager() = default;

    EquipManager& operator=(const EquipManager&) = delete;
    EquipManager& operator=(EquipManager&&) = delete;
};
