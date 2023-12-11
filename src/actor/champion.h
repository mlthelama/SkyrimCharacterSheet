#pragma once
#include "setting/data/menu_data.h"

namespace actor {
    class actor_champion_data {
    public:
        std::string champion_name;
        std::string champion_finished_status;  //some can be finished not in favor of the daedra
        setting_data::menu_data::faction_column_type column =
            setting_data::menu_data::faction_column_type::champion;  //overwrite if it should not be shown
        void log(bool a_quest_done);
    };

    class champion {
    public:
        static std::vector<actor_champion_data*> get_actor_champions(RE::Actor* a_actor);
    };
}  // actor
