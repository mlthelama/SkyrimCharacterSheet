#pragma once
#include "scaleform/factionmenu.h"
#include "scaleform/statsmenu.h"

class ShowHandler {
public:
    static ShowHandler* GetSingleton() {
        static ShowHandler singleton;
        return std::addressof(singleton);
    }

    void CloseWindow(ShowMenu p_menu) {
        switch (p_menu) {
            case ShowMenu::mStats:
                Scaleform::StatsMenu::Close();
                break;
            case ShowMenu::mFaction:
                Scaleform::FactionMenu::Close();
                break;
        }
    }

    void SwapWindow(ShowMenu p_menu_open, ShowMenu p_menu_close) {
        CloseWindow(p_menu_close);
        ShowWindow(p_menu_open);
    }

    void CloseAllWindows() {
        CloseWindow(ShowMenu::mStats);
        CloseWindow(ShowMenu::mFaction);
    }

    void HandleMainButtonPress() {
        if (Scaleform::StatsMenu::IsMenuOpen()) {
            CloseWindow(ShowMenu::mStats);
        } else if (Scaleform::FactionMenu::IsMenuOpen()) {
            CloseWindow(ShowMenu::mFaction);
        } else {
            ShowWindow(ShowMenu::mStats);
        }
    }

    void HandleNextMenuButtonPress() {
        if (Scaleform::StatsMenu::IsMenuOpen()) {
            if (*Settings::showFactionMenu) {
                logger::debug("{} is open, open {}"sv, Scaleform::StatsMenu::MENU_NAME,
                    Scaleform::FactionMenu::MENU_NAME);
                SwapWindow(ShowMenu::mFaction, ShowMenu::mStats);
            } else {
                logger::debug("{} is open, {} is disabled via config"sv, Scaleform::StatsMenu::MENU_NAME,
                    Scaleform::FactionMenu::MENU_NAME);
            }
        } else if (Scaleform::FactionMenu::IsMenuOpen()) {
            logger::debug("{} is open, open {}"sv, Scaleform::FactionMenu::MENU_NAME, Scaleform::StatsMenu::MENU_NAME);
            SwapWindow(ShowMenu::mStats, ShowMenu::mFaction);
        }
    }

    bool IsMenuOpen() {
        if (Scaleform::StatsMenu::IsMenuOpen() || Scaleform::FactionMenu::IsMenuOpen()) {
            return true;
        }
        return false;
    }

private:
    void ShowWindow(ShowMenu p_menu) {
        logger::trace("Gather Value and Show Window"sv);

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

    ShowHandler() = default;
    ShowHandler(const ShowHandler&) = delete;
    ShowHandler(ShowHandler&&) = delete;
    ~ShowHandler() = default;

    ShowHandler& operator=(const ShowHandler&) = delete;
    ShowHandler& operator=(ShowHandler&&) = delete;
};
