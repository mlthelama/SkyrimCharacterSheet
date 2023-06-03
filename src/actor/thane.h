#pragma once
#include "setting/data/menu_data.h"

namespace actor {
    class actor_thane_data {
    public:
        std::string name;
        std::string thane_name;
        uint32_t hold_bounty;
        setting_data::menu_data::faction_column_type column =
            setting_data::menu_data::faction_column_type::thane;  //overwrite if it should not be shown
        void log(bool a_quest_done, bool a_bypass_done);
        void log();
    };

    class thane {
    public:
        static std::vector<actor_thane_data*> get_actor_thanes(RE::Actor* a_actor);
    };
}  // actor
