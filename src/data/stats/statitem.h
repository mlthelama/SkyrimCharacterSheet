#pragma once

class stat_item {
    using stats_menu_value = menu_util::stats_menu_value;
    using show_menu = menu_util::show_menu;
    using stats_inventory_menu_value = menu_util::stats_inventory_menu_value;

public:
    stat_item(const std::string_view a_gui_key,
        std::string a_gui_value,
        const stats_menu_value a_stats_menu,
        const std::string_view a_icon_string)
        : gui_key_(a_gui_key)
        , gui_value_(std::move(a_gui_value))
        , stats_menu_(a_stats_menu)
        , icon_string_(a_icon_string) {}


    stat_item(const std::string_view a_gui_key,
        std::string a_gui_value,
        const stats_inventory_menu_value a_stats_inventory_menu)
        : gui_key_(a_gui_key)
        , gui_value_(std::move(a_gui_value))
        , stats_inventory_menu_(a_stats_inventory_menu) {}


    [[nodiscard]] std::string_view get_key() const { return gui_key_; }
    std::string get_value() { return gui_value_; }

    [[nodiscard]] stats_menu_value get_stats_menu() const { return stats_menu_; }

    [[nodiscard]] stats_inventory_menu_value get_stats_inventory_menu() const { return stats_inventory_menu_; }

    [[nodiscard]] std::string_view get_icon() const { return icon_string_; }

    void log_stat_item(stats_value a_stats_value, const show_menu a_menu) {
        if (a_menu == show_menu::m_stats) {
            logger::trace("name {}, key {}, value {}, StatsMenu {}"sv,
                a_stats_value,
                gui_key_,
                gui_value_,
                stats_menu_);
        } else {
            logger::trace("name {}, key {}, value {}, StatsInventoryMenu {}"sv,
                a_stats_value,
                gui_key_,
                gui_value_,
                stats_inventory_menu_);
        }
    }

    stat_item() = default;
    stat_item(const stat_item&) = delete;
    stat_item(stat_item&&) = delete;

    ~stat_item() = default;

    stat_item& operator=(const stat_item&) = delete;
    stat_item& operator=(stat_item&&) = delete;

private:
    std::string_view gui_key_;
    std::string gui_value_;
    stats_menu_value stats_menu_ = stats_menu_value::m_none;
    stats_inventory_menu_value stats_inventory_menu_ = stats_inventory_menu_value::m_none;
    std::string_view icon_string_;
};
