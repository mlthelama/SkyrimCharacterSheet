#pragma once
#include "setting/config_setting.h"
#include "setting/data/menu_data.h"

namespace actor {
    class actor_faction_data {
    public:
        std::string faction_name;
        std::string faction_rank_name;
        setting_data::menu_data::faction_column_type column =
            setting_data::menu_data::faction_column_type::faction;  //overwrite if it should not be shown
        void log();
    };

    class faction {
    public:
        static std::vector<actor_faction_data*> get_actor_factions(RE::Actor* a_actor);

    private:
        static void get_faction_rank(setting::config_setting::faction_data*& a_faction_data,
            actor_faction_data*& a_actor_faction_data);
    };
}  // actor
