#pragma once
#include "data/faction/factionitem.h"
#include "data/faction/provider/champion.h"
#include "data/faction/provider/faction.h"
#include "data/faction/provider/thane.h"
#include "settings/stats/factionsettings.h"

class faction_data {
    using faction_item_map = std::map<faction_value, std::unique_ptr<faction_item>>;
    using faction_menu_value = menu_util::faction_menu_value;

public:
    static faction_data* get_singleton() {
        static faction_data singleton;
        return std::addressof(singleton);
    }

    [[nodiscard]] faction_item_map get_values_to_display() const {
        faction_item_map fimp;

        const auto player = RE::PlayerCharacter::GetSingleton();
        const auto faction = faction::get_singleton();
        const auto thane = thane::get_singleton();
        const auto champion = champion::get_singleton();

        if (menu_util::get_faction_menu(setting::get_faction_menu()) != faction_menu_value::m_none) {
            faction->get_factions(player);
        }
        if (menu_util::get_faction_menu(setting::get_thane_menu()) != faction_menu_value::m_none) {
            thane->get_region_thanes();
        }
        if (menu_util::get_faction_menu(setting::get_champion_menu()) != faction_menu_value::m_none) {
            champion->get_champions();
        }

        auto faction_setting_map = faction_setting::get_singleton()->load();
        logger::debug("Config Map Size is {}"sv, faction_setting_map.size());

        for (auto& [fst, snd] : faction_setting_map) {
            auto faction_value = fst;
            const auto faction_config = snd.get();

            faction_config->log_stat_config(faction_value);

            if (faction_config->get_menu() == faction_menu_value::m_none) {
                continue;
            }
            std::string value_text;

            switch (faction_value) {
                case faction_value::companions:
                case faction_value::darkbrotherhood:
                case faction_value::college_of_winterhold:
                case faction_value::orc_friend:
                case faction_value::thiefs_guild:
                case faction_value::imperial_legion:
                case faction_value::stormcloaks:
                case faction_value::greybeard:
                case faction_value::bard:
                case faction_value::volkihar_vampire_clan:
                case faction_value::dawnguard:
                case faction_value::house_telvanni:
                    value_text = faction->get_rank(faction_value);
                    break;
                case faction_value::windhelm:
                case faction_value::falkreath:
                case faction_value::solitude:
                case faction_value::morthal:
                case faction_value::dawnstar:
                case faction_value::markarth:
                case faction_value::riften:
                case faction_value::whiterun:
                case faction_value::winterhold:
                    value_text = thane->get_thane(faction_value);
                    break;
                case faction_value::azura:
                case faction_value::boethiah:
                case faction_value::clavicus_vile:
                case faction_value::hermaeus_mora:
                case faction_value::hircine:
                case faction_value::malacath:
                case faction_value::mehrunes_dagon:
                case faction_value::mephala:
                case faction_value::meridia:
                case faction_value::molag_bal:
                case faction_value::namira:
                case faction_value::nocturnal:
                case faction_value::peryite:
                case faction_value::sanguine:
                case faction_value::sheogorath:
                case faction_value::vaermina:
                    value_text = champion->get_champion(faction_value);
                    break;
                default:
                    logger::warn("unhandeled stat, name {}, displayName {}"sv,
                        string_util::get_int_from_enum(faction_value),
                        faction_config->get_display_name());
                    break;
            }


            if (!value_text.empty()) {
                fimp[faction_value] =
                    std::make_unique<faction_item>(faction_config->get_display_name(),
                        value_text,
                        faction_config->get_menu());
            }
        }


        logger::debug("Display Map Size is {}"sv, fimp.size());
        clear_lists(thane, faction, champion);
        for (auto& [fst, snd] : faction_setting_map) { snd.reset(); }
        faction_setting_map.clear();
        return fimp;
    }

    faction_data(const faction_data&) = delete;
    faction_data(faction_data&&) = delete;

    faction_data& operator=(const faction_data&) = delete;
    faction_data& operator=(faction_data&&) = delete;

private:
    faction_data() = default;

    ~faction_data() = default;

    static void clear_lists(thane* a_thane, faction* a_faction, champion* a_champion) {
        a_thane->clear_list();
        a_faction->clear_list();
        a_champion->clear_list();
    }
};
