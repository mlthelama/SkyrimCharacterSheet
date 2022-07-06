#pragma once

class stat_item {
    using stats_menu_value = menu_util::stats_menu_value;
    using show_menu = menu_util::show_menu;
    using stats_inventory_menu_value = menu_util::stats_inventory_menu_value;

public:
    stat_item(std::string a_gui_text, const stats_menu_value a_stats_menu)
        : gui_text_(std::move(a_gui_text)), stats_menu_(a_stats_menu) {}

    stat_item(std::string a_gui_text, const stats_inventory_menu_value a_stats_inventory_menu)
        : gui_text_(std::move(a_gui_text)), stats_inventory_menu_(a_stats_inventory_menu) {}

    std::string get_gui_text() { return gui_text_; }

    [[nodiscard]] stats_menu_value get_stats_menu() const { return stats_menu_; }

    [[nodiscard]] stats_inventory_menu_value get_stats_inventory_menu() const { return stats_inventory_menu_; }

    void log_stat_item(stats_value a_stats_value, const show_menu a_menu) {
        if (a_menu == show_menu::m_stats) {
            logger::trace("name {}, guiText {}, StatsMenu {}"sv, a_stats_value, gui_text_, stats_menu_);
        } else {
            logger::trace("name {}, guiText {}, StatsInventoryMenu {}"sv,
                a_stats_value,
                gui_text_,
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
    std::string gui_text_;
    stats_menu_value stats_menu_ = stats_menu_value::m_none;
    stats_inventory_menu_value stats_inventory_menu_ = stats_inventory_menu_value::m_none;
};
