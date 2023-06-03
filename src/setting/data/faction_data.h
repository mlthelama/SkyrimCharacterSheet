#pragma once
#include "setting/data/menu_data.h"
#include "util/type_util.h"

namespace setting_data {
    class faction_rank_quest_data {
    public:
        RE::TESForm* form;
        std::vector<uint16_t> stages;
    };

    class faction_rank_data {
    public:
        std::string key;
        std::string name;
        std::vector<faction_rank_quest_data*> quests;
    };

    class faction_data {
    public:
        enum class faction {
            dark_brotherhood,
            thiefs_guild,
            orc_friend,
            college_of_winterhold,
            companions,
            imperial_legion,
            stormcloaks,
            greybeard,
            bard_college,
            volkihar_vampire_clan,
            dawnguard,
            house_telvanni,
            custom
        };
        faction key;
        std::string name;
        RE::TESForm* form;
        std::vector<faction_rank_data*> ranks;
        setting_data::menu_data::faction_column_type faction_column;

        inline void log() {
            logger::trace("key '{}', name '{}', form_id '{}', rank count '{}', column '{}'"sv,
                magic_enum::enum_name(key),
                name,
                form ? util::type_util::int_to_hex(form->formID) : "",
                ranks.size(),
                magic_enum::enum_name(faction_column));
        }
    };
}
