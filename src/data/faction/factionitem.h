#pragma once

class faction_item {
    using faction_menu_value = menu_util::faction_menu_value;

public:
    faction_item(std::string a_gui_text, const faction_menu_value a_faction_menu)
        : gui_text_(std::move(a_gui_text)), faction_menu_(a_faction_menu) {}

    std::string get_gui_text() { return gui_text_; }

    [[nodiscard]] faction_menu_value get_faction_menu() const { return faction_menu_; }

    void log_stat_item(FactionValue a_stats_value) {
        logger::trace("name {}, guiText {}, StatsMenu {}"sv, a_stats_value, gui_text_, faction_menu_);
    }


    //faction_item() = default;
    faction_item(const faction_item&) = delete;
    faction_item(faction_item&&) = delete;

    ~faction_item() = default;

    faction_item& operator=(const faction_item&) = delete;
    faction_item& operator=(faction_item&&) = delete;

private:
    std::string gui_text_;
    faction_menu_value faction_menu_;
};
