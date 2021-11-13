#pragma once

class StatItem {
    using StatsMenuValue = MenuUtil::StatsMenuValue;
    using ShowMenu = MenuUtil::ShowMenu;
    using StatsInventoryMenuValue = MenuUtil::StatsInventoryMenuValue;
public:
    StatItem(std::string a_gui_text, StatsMenuValue a_stats_menu) : _guiText(a_gui_text), _statsMenu(a_stats_menu) {}

    StatItem(std::string a_gui_text, StatsInventoryMenuValue a_stats_inventory_menu)
        : _guiText(a_gui_text), _statsInventoryMenu(a_stats_inventory_menu) {}

    std::string getGuiText() { return _guiText; }

    StatsMenuValue getStatsMenu() { return _statsMenu; }

    StatsInventoryMenuValue getStatsInventoryMenu() { return _statsInventoryMenu; }

    void logStatItem(StatsValue a_stats_value, ShowMenu a_menu) {
        if (a_menu == ShowMenu::mStats) {
            logger::trace("name {}, guiText {}, StatsMenu {}"sv, a_stats_value, _guiText, _statsMenu);
        } else {
            logger::trace("name {}, guiText {}, StatsInventoryMenu {}"sv, a_stats_value, _guiText, _statsInventoryMenu);
        }
    }

private:
    std::string _guiText;
    StatsMenuValue _statsMenu;
    StatsInventoryMenuValue _statsInventoryMenu;
};
