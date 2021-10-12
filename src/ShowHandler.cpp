#include "showhandler.h"
#include "scaleform/factionmenu.h"
#include "scaleform/statsmenu.h"

auto ShowHandler::GetSingleton() -> ShowHandler* {
    static ShowHandler singleton;
    return std::addressof(singleton);
}

void ShowHandler::ShowWindow(ShowMenu p_menu) {
    logger::trace("Gather Value and Show Window"sv);
    Locker locker(_lock);

    if (*Settings::logLevel == logTrace) {
        RE::DebugNotification(fmt::format("Showing menu {} now."sv, getMenuName(p_menu)).c_str());
    }

    switch (p_menu) {
        case ShowMenu::mStats:
            Scaleform::StatsMenu::Open();
            break;
        case ShowMenu::mFaction:
            if (*Settings::showFactionMenu) {
                Scaleform::FactionMenu::Open();
            }
            break;
    }
}

void ShowHandler::CloseWindow(ShowMenu p_menu) {
    switch (p_menu) {
        case ShowMenu::mStats:
            Scaleform::StatsMenu::Close();
            break;
        case ShowMenu::mFaction:
            Scaleform::FactionMenu::Close();
            break;
    }
}

void ShowHandler::SwapWindow(ShowMenu p_menu_open, ShowMenu p_menu_close) {
    CloseWindow(p_menu_close);
    ShowWindow(p_menu_open);
}

void ShowHandler::CloseAllWindows() {
    CloseWindow(ShowMenu::mStats);
    CloseWindow(ShowMenu::mFaction);
}

void ShowHandler::HandleMainButtonPress() {
    if (Scaleform::StatsMenu::IsMenuOpen()) {
        CloseWindow(ShowMenu::mStats);
    } else if (Scaleform::FactionMenu::IsMenuOpen()) {
        CloseWindow(ShowMenu::mFaction);
    } else {
        ShowWindow(ShowMenu::mStats);
    }
}

void ShowHandler::HandleNextMenuButtonPress() {
    if (Scaleform::StatsMenu::IsMenuOpen()) {
        if (*Settings::showFactionMenu) {
            logger::info("{} is open, open {}"sv, Scaleform::StatsMenu::MENU_NAME, Scaleform::FactionMenu::MENU_NAME);
            SwapWindow(ShowMenu::mFaction, ShowMenu::mStats);
        } else {
            logger::info("{} is open, {} is disabled via config"sv, Scaleform::StatsMenu::MENU_NAME,
                Scaleform::FactionMenu::MENU_NAME);
        }
    } else if (Scaleform::FactionMenu::IsMenuOpen()) {
        logger::info("{} is open, open {}"sv, Scaleform::FactionMenu::MENU_NAME, Scaleform::StatsMenu::MENU_NAME);
        SwapWindow(ShowMenu::mStats, ShowMenu::mFaction);
    }
}

ShowHandler::ShowHandler() : _lock() {}