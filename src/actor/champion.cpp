#include "champion.h"
#include "setting/config_setting.h"
#include "util/quest/quest.h"

namespace actor {
    void actor_champion_data::log(bool a_quest_done) {
        logger::trace("champion_name {}, status {}, column {}, quest_done {}"sv,
            champion_name,
            champion_finished_status,
            magic_enum::enum_name(column),
            a_quest_done);
    }

    std::vector<actor_champion_data*> champion::get_actor_champions(RE::Actor* a_actor) {
        if (!a_actor) {
            return {};
        }
        logger::trace("getting factions for actor"sv);

        auto* config_setting = setting::config_setting::get_singleton();
        auto config_champion = config_setting->get_champion_data();

        logger::trace("Got {} champion(s) from the config to check"sv, config_champion.size());

        std::vector<actor_champion_data*> actor_champion_list;
        for (auto* champion_data : config_champion) {
            champion_data->log();
            auto* actor_champion = new actor_champion_data();
            actor_champion->champion_name = champion_data->name;
            auto quest_done = false;

            if (!champion_data->stages.empty()) {
                quest_done =
                    util::quest::is_one_quest_stage_complete(champion_data->form->formID, champion_data->stages);
                if (quest_done) {
                    actor_champion->champion_finished_status = "pro daedra";  //TODO
                }
            }
            if (!quest_done && !champion_data->alternate_stages.empty()) {
                quest_done = util::quest::is_one_quest_stage_complete(champion_data->form->formID,
                    champion_data->alternate_stages);
                if (quest_done) {
                    actor_champion->champion_finished_status = "alternate";  //TODO
                }
            }

            if (quest_done && !actor_champion->champion_finished_status.empty()) {
                actor_champion->column = setting_data::menu_data::faction_column_type::champion;
                actor_champion_list.push_back(actor_champion);
            }
            actor_champion->log(quest_done);
        }

        for (auto* champion : actor_champion_list) {
            champion->log(true);
            logger::trace("champion {}, finished {}"sv, champion->champion_name, champion->champion_finished_status);
        }

        logger::trace("got {} champion(s) for actor"sv, actor_champion_list.size());
        return actor_champion_list;
    }
}  // actor
