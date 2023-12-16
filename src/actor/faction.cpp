#include "faction.h"
#include "util/quest/quest.h"

namespace actor {
    void actor_faction_data::log() {
        logger::trace("faction {}, rank {}, column {}"sv,
            faction_name,
            faction_rank_name,
            magic_enum::enum_name(column));
    }

    std::vector<actor_faction_data*> faction::get_actor_factions(RE::Actor* a_actor) {
        if (!a_actor) {
            return {};
        }
        logger::trace("getting factions for actor"sv);

        auto* config_setting = setting::config_setting::get_singleton();
        auto config_faction = config_setting->get_faction_data();

        logger::trace("Got {} faction(s) from the config to check"sv, config_faction.size());

        const auto actor_sex = a_actor->GetActorBase()->GetSex();

        constexpr auto male = RE::SEXES::SEX::kMale;
        constexpr auto female = RE::SEXES::SEX::kFemale;

        std::vector<actor_faction_data*> actor_faction_list;

        a_actor->VisitFactions([&](const RE::TESFaction* a_faction, int8_t a_rank) {
            if (a_faction && a_rank > -1) {
                const auto name(a_faction->GetName());
                const auto form_id(a_faction->formID);
                auto rank_data(a_faction->rankData);

                if (!config_faction.contains(form_id)) {
                    logger::trace("name {}, formId {}, rank {} not handled"sv,
                        name,
                        util::type_util::int_to_hex(form_id),
                        a_rank);
                } else {
                    logger::trace("name {}, formId {}, rank {}"sv, name, util::type_util::int_to_hex(form_id), a_rank);
                    std::string rank;

                    for (auto it = rank_data.begin(); it != rank_data.end(); ++it) {
                        const auto index = std::distance(rank_data.begin(), it);
                        const auto i = *it;
                        if (index == a_rank) {
                            if (actor_sex == female) {
                                rank = i->femaleRankTitle;
                            }
                            if (rank.empty() || actor_sex == male) {
                                rank = i->maleRankTitle;
                            }
                            logger::trace("Name {}, Rankname {}"sv, name, rank);
                        }
                    }

                    //if the rank was set from the game files we can skip the next part
                    auto* faction_data = config_faction.at(form_id);
                    logger::trace("got rank {} from game, faction name {}, name {}"sv,
                        rank,
                        magic_enum::enum_name(faction_data->key),
                        faction_data->name);
                    auto* actor_faction = new actor_faction_data();
                    actor_faction->faction_name = faction_data->name;
                    if (!rank.empty()) {
                        actor_faction->faction_rank_name = rank;
                    }

                    if (!faction_data->ranks.empty()) {
                        get_faction_rank(faction_data, actor_faction);
                    }
                    actor_faction_list.push_back(actor_faction);
                    actor_faction->log();
                }
            }
            return false;
        });

        auto special_config_faction = config_setting->get_special_faction_data();
        logger::trace("Checking for special faction, got {} to check"sv, special_config_faction.size());
        for (auto* faction_data : special_config_faction) {
            //faction_data->log();
            auto* actor_faction = new actor_faction_data();
            actor_faction->faction_name = faction_data->name;
            if (!faction_data->ranks.empty()) {
                get_faction_rank(faction_data, actor_faction);
                if (!actor_faction->faction_rank_name.empty()) {
                    actor_faction_list.push_back(actor_faction);
                }
            }
        }

        for (auto* faction : actor_faction_list) {
            faction->log();
        }

        logger::trace("got {} faction(s) for actor"sv, actor_faction_list.size());
        return actor_faction_list;
    }

    void faction::get_faction_rank(setting::config_setting::faction_data*& a_faction_data,
        actor_faction_data*& a_actor_faction_data) {
        logger::trace("getting rank in faction name {}, name {}"sv,
            magic_enum::enum_name(a_faction_data->key),
            a_actor_faction_data->faction_name);

        for (auto* rank : a_faction_data->ranks) {
            logger::trace("checking rank {}"sv, rank->name);
            auto rank_done = false;
            if (rank->quests.empty()) {
                logger::trace("no quest data set. continue."sv);
                a_actor_faction_data->faction_rank_name = rank->name;
                continue;
            }
            for (auto* quest : rank->quests) {
                auto quest_done = util::quest::is_one_quest_stage_complete(quest->form->formID, quest->stages);

                if (!quest_done) {
                    rank_done = false;
                    break;
                }
                rank_done = quest_done;
            }
            if (rank_done) {
                logger::trace("Faction Rank {} done"sv, rank->name);
                a_actor_faction_data->faction_rank_name = rank->name;
            } else {
                break;
            }
        }

        a_actor_faction_data->log();
    }
}  // actor
