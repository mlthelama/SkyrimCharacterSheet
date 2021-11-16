#pragma once
#include "scaleform/menus/factionmenu.h"
#include "scaleform/menus/statsinventorymenu.h"
#include "scaleform/menus/statsmenu.h"

class ShowHandler {
    using ShowMenu = MenuUtil::ShowMenu;

public:
    static ShowHandler* GetSingleton() {
        static ShowHandler singleton;
        return std::addressof(singleton);
    }

    void CloseWindow(ShowMenu a_menu) {
        switch (a_menu) {
            case ShowMenu::mStats:
                Scaleform::StatsMenu::Close();
                break;
            case ShowMenu::mFaction:
                Scaleform::FactionMenu::Close();
                break;
            case ShowMenu::mStatsInventory:
                Scaleform::StatsInventoryMenu::Close();
        }
    }

    void SwapWindow(ShowMenu a_menu_open, ShowMenu a_menu_close) {
        CloseWindow(a_menu_close);
        ShowWindow(a_menu_open);
    }

    void CloseAllWindows() {
        CloseWindow(ShowMenu::mStats);
        CloseWindow(ShowMenu::mFaction);
        CloseWindow(ShowMenu::mStatsInventory);
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
                logger::debug("{} is open, open {}"sv,
                    Scaleform::StatsMenu::MENU_NAME,
                    Scaleform::FactionMenu::MENU_NAME);
                SwapWindow(ShowMenu::mFaction, ShowMenu::mStats);
            } else {
                logger::debug("{} is open, {} is disabled via config"sv,
                    Scaleform::StatsMenu::MENU_NAME,
                    Scaleform::FactionMenu::MENU_NAME);
            }
        } else if (Scaleform::FactionMenu::IsMenuOpen()) {
            logger::debug("{} is open, open {}"sv, Scaleform::FactionMenu::MENU_NAME, Scaleform::StatsMenu::MENU_NAME);
            SwapWindow(ShowMenu::mStats, ShowMenu::mFaction);
        }
    }

    bool IsMenuOpen() { return (Scaleform::StatsMenu::IsMenuOpen() || Scaleform::FactionMenu::IsMenuOpen()); }

    bool IsMenuOpen(ShowMenu a_menu_open) {
        return RE::UI::GetSingleton()->IsMenuOpen(getMenuScaleformName(a_menu_open));
    }

    void HandleInventoryStatsOpen() {
        if (!Scaleform::StatsInventoryMenu::IsMenuOpen()) {
            ShowWindow(ShowMenu::mStatsInventory);
        }
    }

    void HandleInventoryStatsUpdate() {
        if (Scaleform::StatsInventoryMenu::IsMenuOpen()) {
            RE::UI::GetSingleton()
                ->GetMenu<Scaleform::StatsInventoryMenu>(Scaleform::StatsInventoryMenu::MENU_NAME)
                ->RefreshLists();
        }
    }

    ShowHandler() = default;
    ShowHandler(const ShowHandler&) = delete;
    ShowHandler(ShowHandler&&) = delete;
    ~ShowHandler() = default;

    ShowHandler& operator=(const ShowHandler&) = delete;
    ShowHandler& operator=(ShowHandler&&) = delete;

private:
    inline static std::map<ShowMenu, std::string_view> _menuScaleFormName = { { ShowMenu::mStats,
                                                                                  Scaleform::StatsMenu::MENU_NAME },
        { ShowMenu::mFaction, Scaleform::FactionMenu::MENU_NAME },
        { ShowMenu::mStatsInventory, Scaleform::StatsInventoryMenu::MENU_NAME } };

    static std::string_view getMenuScaleformName(ShowMenu a_menu) {
        if (_menuScaleFormName.find(a_menu) == _menuScaleFormName.end()) {
            logger::warn("can not find Scaleform Name for Menu {}"sv, a_menu);
            return "";
        } else {
            return _menuScaleFormName.find(a_menu)->second;
        }
    }

    void ShowWindow(ShowMenu a_menu) {
        logger::trace("Gather Value and Show Window"sv);

        switch (a_menu) {
            case ShowMenu::mStats:
                Scaleform::StatsMenu::Open();
                break;
            case ShowMenu::mFaction:
                if (*Settings::showFactionMenu) {
                    Scaleform::FactionMenu::Open();
                }
                break;
            case ShowMenu::mStatsInventory:
                Scaleform::StatsInventoryMenu::Open();
                break;
        }
    }
};
