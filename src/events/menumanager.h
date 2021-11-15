#include "handler/showhandler.h"
#include "scaleform/factionmenu.h"
#include "scaleform/statsmenu.h"

class MenuManager : public RE::BSTEventSink<RE::MenuOpenCloseEvent> {
public:
    using EventResult = RE::BSEventNotifyControl;
    using ShowMenu = MenuUtil::ShowMenu;

    static MenuManager* GetSingleton() {
        static MenuManager singleton;
        return std::addressof(singleton);
    }

    static void Sink() {
        auto ui = RE::UI::GetSingleton();
        ui->AddEventSink(static_cast<RE::BSTEventSink<RE::MenuOpenCloseEvent>*>(MenuManager::GetSingleton()));
    }

    auto ProcessEvent(RE::MenuOpenCloseEvent const* a_event,
        [[maybe_unused]] RE::BSTEventSource<RE::MenuOpenCloseEvent>* a_eventSource) -> EventResult {
        if (!a_event) {
            return EventResult::kContinue;
        }

        if (a_event->opening) {
            auto showHandler = ShowHandler::GetSingleton();
            if (Scaleform::StatsMenu::IsMenuOpen() && a_event->menuName != Scaleform::StatsMenu::MENU_NAME) {
                showHandler->CloseWindow(ShowMenu::mStats);
            } else if (Scaleform::FactionMenu::IsMenuOpen() && a_event->menuName != Scaleform::FactionMenu::MENU_NAME) {
                showHandler->CloseWindow(ShowMenu::mFaction);
            }
        }

        return EventResult::kContinue;
    }

    MenuManager() = default;
    MenuManager(const MenuManager&) = delete;
    MenuManager(MenuManager&&) = delete;
    virtual ~MenuManager() = default;

    MenuManager& operator=(const MenuManager&) = delete;
    MenuManager& operator=(MenuManager&&) = delete;
};
