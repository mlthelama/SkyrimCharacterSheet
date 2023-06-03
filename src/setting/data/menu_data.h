#pragma once

namespace setting_data {
    class menu_data {
    public:
        enum class menu_type { stats, faction, stats_inventory, total };

        enum class stats_column_type : std::uint32_t {
            none,
            player,
            defence,
            attack,
            magic,
            warrior,
            thief,
            special  //header or bottom
        };

        enum class faction_column_type : std::uint32_t { none, faction, thane, champion };

        enum class stats_inventory_column_type : std::uint32_t { none, equip, armor, weapon, effect };

        menu_type menu;
        std::string_view menu_name;
    };
}  // setting_data
