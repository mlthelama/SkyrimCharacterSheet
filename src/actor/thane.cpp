#include "thane.h"
#include "mod/mod_manager.h"
#include "setting/config_setting.h"
#include "util/quest/quest.h"
#include "util/type_util.h"

namespace actor {
    void actor_thane_data::log(bool a_quest_done, bool a_bypass_done) {
        logger::trace("name {}, thane_name {}, column {}, quest_done {}, bypass_done {}"sv,
            name,
            thane_name,
            magic_enum::enum_name(column),
            a_quest_done,
            a_bypass_done);
    }

    void actor_thane_data::log() {
        logger::trace("name {}, thane_name {}, column {}"sv, name, thane_name, magic_enum::enum_name(column));
    }

    std::vector<actor_thane_data*> thane::get_actor_thanes(RE::Actor* a_actor) {
        if (!a_actor) {
            return {};
        }
        logger::trace("getting thanes for actor"sv);

        auto* config_setting = setting::config_setting::get_singleton();
        auto config_thane = config_setting->get_thane_data();

        auto* mod_manager = mod::mod_manager::get_singleton();
        logger::trace("Got {} thane(s) from the config to check"sv, config_thane.size());

        std::vector<actor_thane_data*> actor_thane_list;
        for (auto* thane_data : config_thane) {
            //thane_data->log();
            auto* actor_thane = new actor_thane_data();
            actor_thane->name = thane_data->name;

            auto bypass_done = false;
            auto allow_bypass = true;
            //todo add json config like player_data (overwrite)
            if (mod_manager->get_skyrim_unbound() && thane_data->key == setting_data::thane_data::hold::whiterun) {
                allow_bypass = false;
            }

            if (thane_data->bypass_quest && allow_bypass) {
                bypass_done = util::quest::is_one_quest_stage_complete(thane_data->bypass_quest->quest_form->formID,
                    thane_data->bypass_quest->quest_stages);
            }

            auto quest_done = false;
            if (!thane_data->quest_stages.empty()) {
                quest_done =
                    util::quest::is_one_quest_stage_complete(thane_data->quest_form->formID, thane_data->quest_stages);
                auto pre_quest_needed = !thane_data->pre_quests.empty();
                logger::trace("quest {} is done {}, pre quest needed {}"sv,
                    util::type_util::int_to_hex(thane_data->quest_form->formID),
                    quest_done,
                    pre_quest_needed);
                if (quest_done && pre_quest_needed) {
                    for (auto* pre_quest_element : thane_data->pre_quests) {
                        quest_done = util::quest::is_one_quest_stage_complete(pre_quest_element->quest_form->formID,
                            pre_quest_element->quest_stages);
                        logger::trace("quest {} is done {}"sv,
                            util::type_util::int_to_hex(pre_quest_element->quest_form->formID),
                            quest_done);
                        if (!quest_done) {
                            break;
                        }
                    }
                }
            }

            logger::trace("thane {}, quest {}, bypass {}"sv, actor_thane->name, quest_done, bypass_done);

            if (quest_done || bypass_done) {
                actor_thane->thane_name = thane_data->thane_name;
                actor_thane_list.push_back(actor_thane);
            }

            /*if (thane_data->crime_faction && thane_data->crime_faction->Is(RE::FormType::Faction)) {
                auto* faction = thane_data->crime_faction->As<RE::TESFaction>();
                actor_thane->hold_bounty = a_actor->GetCrimeGoldValue(faction);
                if (actor_thane->hold_bounty > 0) {
                    actor_thane_list.push_back(actor_thane);
                }
            }*/

            actor_thane->log(quest_done, bypass_done);
        }

        for (auto* thane : actor_thane_list) {
            thane->log();
        }

        logger::trace("got {} thane(s) for actor"sv, actor_thane_list.size());
        return actor_thane_list;
    }
}  // actor
