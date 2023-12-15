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

        class stat_menu_column {
        public:
            stats_column_type stat_column;
        };

        class faction_menu_column {
        public:
            faction_column_type faction_column;
        };

        class stat_inventory_column {
        public:
            stats_inventory_column_type stat_inventory_column;
        };

        class menu_column
            : public stat_menu_column
            , public faction_menu_column
            , public stat_inventory_column {
        public:
            std::string column_name;
        };


        menu_type menu;
        std::string menu_name;
        std::vector<menu_column*> columns;
    };
}  // setting_data
