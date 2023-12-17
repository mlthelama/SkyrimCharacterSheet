#pragma once
#include "setting/data/menu_data.h"
#include "util/type_util.h"

namespace setting_data {
    class champion_data {
    public:
        enum class champion {
            azura,
            boethiah,
            clavicus_vile,
            hermaeus_mora,
            hircine,
            malacath,
            mehrunes_dagon,
            mephala,
            meridia,
            molag_bal,
            namira,
            nocturnal,
            peryite,
            sanguine,
            sheogorath,
            vaermina,
            custom
        };

        champion key;
        std::string name;
        RE::TESForm* form;
        std::vector<uint16_t> stages;
        std::vector<uint16_t> alternate_stages;
        setting_data::menu_data::faction_column_type faction_column;

        inline void log() {
            logger::trace("key '{}', name '{}', form '{}', stages '{}', alternate_stages '{}', column '{}'"sv,
                magic_enum::enum_name(key),
                name,
                form ? util::type_util::int_to_hex(form->formID) : "",
                util::type_util::get_delimited_string(stages),
                util::type_util::get_delimited_string(alternate_stages),
                magic_enum::enum_name(faction_column));
        }
    };
}
