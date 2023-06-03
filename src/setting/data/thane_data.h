#pragma once
#include "setting/data/menu_data.h"
#include "util/type_util.h"

namespace setting_data {
    class thane_bypass_quest_data {
    public:
        RE::TESForm* quest_form;
        std::vector<uint16_t> quest_stages;
    };

    class thane_pre_quest_data {
    public:
        RE::TESForm* quest_form;
        std::vector<uint16_t> quest_stages;
    };

    class thane_data {
    public:
        enum class hold {
            windhelm,
            falkreath,
            solitude,
            morthal,
            dawnstar,
            markarth,
            riften,
            whiterun,
            winterhold,
            solstheim,
            custom
        };

        hold key;
        std::string name;
        std::string thane_name;
        RE::TESForm* quest_form;
        std::vector<uint16_t> quest_stages;
        setting_data::menu_data::faction_column_type faction_column;
        RE::TESForm* crime_faction;
        std::vector<thane_pre_quest_data*> pre_quests;
        thane_bypass_quest_data* bypass_quest;

        inline void log() {
            logger::trace(
                "key '{}', name '{}', thane name '{}', form_id '{}', stage(s) '{}', crime faction form '{}', pre_quest(s) '{}', bypass quest '{}', column '{}'"sv,
                magic_enum::enum_name(key),
                name,
                thane_name,
                quest_form ? util::type_util::int_to_hex(quest_form->formID) : "",
                quest_stages.size(),
                quest_form ? util::type_util::int_to_hex(crime_faction->formID) : "",
                pre_quests.size(),
                bypass_quest != nullptr,
                magic_enum::enum_name(faction_column));
        }
    };
}
