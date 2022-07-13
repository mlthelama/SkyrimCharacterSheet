#pragma once

class faction_item {
    using faction_menu_value = menu_util::faction_menu_value;

public:
    faction_item(const std::string_view a_gui_key,
        std::string a_gui_value,
        const faction_menu_value a_faction_menu)
        : gui_key_(a_gui_key)
        , gui_value_(std::move(a_gui_value))
        , faction_menu_(a_faction_menu) {}


    [[nodiscard]] std::string_view get_key() const { return gui_key_; }
    [[nodiscard]] std::string get_value() const { return gui_value_; }

    [[nodiscard]] faction_menu_value get_faction_menu() const { return faction_menu_; }

    void log_stat_item(faction_value a_stats_value) {
        logger::trace("name {}, key {}, value {}, StatsMenu {}"sv, a_stats_value, gui_key_, gui_value_, faction_menu_);
    }


    faction_item() = default;
    faction_item(const faction_item&) = delete;
    faction_item(faction_item&&) = delete;

    ~faction_item() = default;

    faction_item& operator=(const faction_item&) = delete;
    faction_item& operator=(faction_item&&) = delete;

private:
    std::string_view gui_key_;
    std::string gui_value_;
    faction_menu_value faction_menu_;
};
