#pragma once

class StatItem {
public:
    StatItem(std::string a_gui_text, StatsMenuValue a_stats_menu) : _guiText(a_gui_text), _statsMenu(a_stats_menu) {}

    std::string getGuiText() { return _guiText; }

    StatsMenuValue getStatsMenu() { return _statsMenu; }

    void logStatItem(StatsValue a_stats_value) {
        logger::trace("name {}, guiText {}, StatsMenu {}"sv, a_stats_value, _guiText, _statsMenu);
    }

private:
    std::string _guiText;
    StatsMenuValue _statsMenu;
};
