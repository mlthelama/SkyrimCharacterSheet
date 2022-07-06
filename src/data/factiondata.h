#pragma once
#include "data/faction/factionitem.h"
#include "data/faction/provider/champion.h"
#include "data/faction/provider/faction.h"
#include "data/faction/provider/thane.h"
#include "settings/stats/factionsettings.h"

class faction_data {
    using faction_item_map = std::map<FactionValue, std::unique_ptr<faction_item>>;
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

        if (menu_util::get_faction_menu(*settings::factionMenu) != faction_menu_value::m_none) {
            faction->get_factions(player);
        }
        if (menu_util::get_faction_menu(*settings::thaneMenu) != faction_menu_value::m_none) {
            thane->get_region_thanes();
        }
        if (menu_util::get_faction_menu(*settings::championMenu) != faction_menu_value::m_none) {
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
                case FactionValue::companions:
                case FactionValue::darkbrotherhood:
                case FactionValue::college_of_winterhold:
                case FactionValue::orc_friend:
                case FactionValue::thiefs_guild:
                case FactionValue::imperial_legion:
                case FactionValue::stormcloaks:
                case FactionValue::greybeard:
                case FactionValue::bard:
                case FactionValue::volkihar_vampire_clan:
                case FactionValue::dawnguard:
                case FactionValue::house_telvanni:
                    value_text = faction->get_rank(faction_value);
                    break;
                case FactionValue::thane_of_eastmarch:
                case FactionValue::thane_of_falkreath:
                case FactionValue::thane_of_haafingar:
                case FactionValue::thane_of_hjaalmarch:
                case FactionValue::thane_of_the_pale:
                case FactionValue::thane_of_the_reach:
                case FactionValue::thane_of_the_rift:
                case FactionValue::thane_of_whiterun:
                case FactionValue::thane_of_winterhold:
                    value_text = thane->get_thane(faction_value);
                    break;
                case FactionValue::azura:
                case FactionValue::boethiah:
                case FactionValue::clavicus_vile:
                case FactionValue::hermaeus_mora:
                case FactionValue::hircine:
                case FactionValue::malacath:
                case FactionValue::mehrunes_dagon:
                case FactionValue::mephala:
                case FactionValue::meridia:
                case FactionValue::molagBal:
                case FactionValue::namira:
                case FactionValue::nocturnal:
                case FactionValue::peryite:
                case FactionValue::sanguine:
                case FactionValue::sheogorath:
                case FactionValue::vaermina:
                    value_text = champion->get_champion(faction_value);
                    break;
                default:
                    logger::warn("unhandeled stat, name {}, displayName {}"sv,
                        faction_value,
                        faction_config->get_display_name());
                    break;
            }


            if (!value_text.empty()) {
                fimp[faction_value] =
                    std::make_unique<faction_item>(faction_config->get_display(value_text), faction_config->get_menu());
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
