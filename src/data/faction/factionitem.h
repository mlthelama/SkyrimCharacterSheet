#pragma once

class FactionItem {
    using FactionMenuValue = MenuUtil::FactionMenuValue;

public:
    FactionItem(std::string a_gui_text, FactionMenuValue a_faction_menu)
        : _guiText(a_gui_text), _factionMenu(a_faction_menu) {}

    std::string getGuiText() { return _guiText; }

    FactionMenuValue getFactionMenu() { return _factionMenu; }

    void logStatItem(FactionValue a_stats_value) {
        logger::trace("name {}, guiText {}, StatsMenu {}"sv, a_stats_value, _guiText, _factionMenu);
    }


    FactionItem() = default;
    FactionItem(const FactionItem&) = delete;
    FactionItem(FactionItem&&) = delete;

    ~FactionItem() = default;

    FactionItem& operator=(const FactionItem&) = delete;
    FactionItem& operator=(FactionItem&&) = delete;

private:
    std::string _guiText;
    FactionMenuValue _factionMenu;
};
