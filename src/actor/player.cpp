#include "player.h"
#include "setting/config_setting.h"
#include "setting/game_setting.h"
#include "util/player/player.h"
#include "util/type_util.h"

namespace actor {

    void actor_player_data::log(setting_data::menu_data::menu_type a_menu) {
        std::string column_name;
        if (a_menu == setting_data::menu_data::menu_type::stats) {
            column_name = magic_enum::enum_name(column);
        } else {
            column_name = magic_enum::enum_name(inventory_column);
        }
        logger::trace("key {}, value {}, icon {}, column {}"sv, key, value, icon, column_name);
    }

    std::vector<actor_player_data*> player::get_player_data(RE::PlayerCharacter*& a_player,
        setting_data::menu_data::menu_type a_menu) {
        if (!a_player) {
            return {};
        }
        if (a_menu != setting_data::menu_data::menu_type::stats &&
            a_menu != setting_data::menu_data::menu_type::stats_inventory) {
            return {};
        }

        logger::trace("getting data for actor, menu {}"sv, magic_enum::enum_name(a_menu));

        auto* config_setting = setting::config_setting::get_singleton();
        auto config_player = config_setting->get_player_data();

        logger::trace("Got {} item(s) from the config to check"sv, config_player.size());

        std::vector<actor_player_data*> actor_player_data_list;
        for (auto* player_data_element : config_player) {
            player_data_element->log();
            //skip element if menu type for the requested menu is disabled
            if ((a_menu == setting_data::menu_data::menu_type::stats &&
                    player_data_element->stats_column == setting_data::menu_data::stats_column_type::none) ||
                (a_menu == setting_data::menu_data::menu_type::stats_inventory &&
                    player_data_element->stats_inventory_column ==
                        setting_data::menu_data::stats_inventory_column_type::none)) {
                continue;
            }

            auto* player_data = new actor_player_data();
            player_data->key = player_data_element->display_name;
            player_data->icon = player_data_element->icon_string;
            if (player_data_element->overwrite_mod != setting_data::player_data::mod_values::none) {
                if (player_data_element->mod_data) {
                    if (!player_data_element->mod_data->display_name.empty()) {
                        player_data->key = player_data_element->mod_data->display_name;
                    }
                    if (!player_data_element->mod_data->icon_string.empty()) {
                        player_data->icon = player_data_element->mod_data->icon_string;
                    }
                }
            }
            //todo add info for column
            if (player_data_element->actor_value_handling == setting_data::player_data::value_handling::single) {
                //todo log
                switch (player_data_element->key) {
                    case setting_data::player_data::stat::name:
                        player_data->value = a_player->GetName();
                        break;
                    case setting_data::player_data::stat::race:
                        player_data->value = a_player->GetRace()->GetName();
                        break;
                    case setting_data::player_data::stat::level:
                        player_data->value = std::to_string(a_player->GetLevel());
                        break;
                    case setting_data::player_data::stat::perk_count:
                        player_data->value = std::to_string(a_player->GetGameStatsData().perkCount);
                        break;
                    case setting_data::player_data::stat::height:
                        player_data->value = util::type_util::get_float_as_string(a_player->GetHeight());
                        break;
                    case setting_data::player_data::stat::equipped_weight:
                    case setting_data::player_data::stat::weight:
                        player_data->value = string_util::get_string_value_from_float(a_player->GetWeight());
                        break;
                    case setting_data::player_data::stat::damage:
                        player_data->value = util::player::get_weapon_damage(a_player, false);
                        break;
                    case setting_data::player_data::stat::skill_trainings_this_level:
                        player_data->value = std::to_string(a_player->GetInfoRuntimeData().skillTrainingsThisLevel);
                        break;
                    case setting_data::player_data::stat::resist_damage:
                        process_damage_resist(a_player, player_data_element, player_data);
                        break;
                    default:
                        if (player_data_element->actor_value.actor_value != RE::ActorValue::kNone) {
                            auto value = a_player->AsActorValueOwner()->GetActorValue(
                                player_data_element->actor_value.actor_value);
                            process_result_handling(player_data_element, value);
                            player_data->value = util::type_util::get_float_as_string(value);
                            if (!player_data_element->ending.empty()) {
                                player_data->value += player_data_element->ending;
                            }
                            player_data->value += process_max_handling(player_data_element, value);
                        }
                }
            } else if (player_data_element->actor_value_handling ==
                       setting_data::player_data::value_handling::multiply) {
                /*switch (player_data_element->key) {
                    case setting_data::player_data::stat::health_rate_per:
                        break ;
                    default:
                        break;
                }*/
                float result = 0.f;
                auto assign_base = true;
                for (auto& av : player_data_element->actor_value.actor_value_list) {
                    if (assign_base) {
                        result = a_player->AsActorValueOwner()->GetActorValue(av);
                        assign_base = false;
                    } else {
                        result *= a_player->AsActorValueOwner()->GetActorValue(av);
                    }
                }

                process_result_handling(player_data_element, result);
                player_data->value = util::type_util::get_float_as_string(result);
                if (!player_data_element->ending.empty()) {
                    player_data->value += player_data_element->ending;
                }
                player_data->value += process_max_handling(player_data_element, result);
            }

            player_data->log(a_menu);
            actor_player_data_list.push_back(player_data);
        }

        for (auto* player_data : actor_player_data_list) {
            player_data->log(a_menu);
        }

        logger::trace("got {} item(s) for actor"sv, actor_player_data_list.size());
        return actor_player_data_list;
    }

    void player::process_result_handling(setting_data::player_data*& a_player_data_element, float& a_current_result) {
        if (a_player_data_element->result_value == 0) {
            return;
        }
        switch (a_player_data_element->result_handling) {
            case setting_data::player_data::result_value_handling::none:
                break;
            case setting_data::player_data::result_value_handling::multiply:
                a_current_result *= static_cast<float>(a_player_data_element->result_value);
                break;
            case setting_data::player_data::result_value_handling::divide:
                a_current_result /= static_cast<float>(a_player_data_element->result_value);
                break;
            case setting_data::player_data::result_value_handling::add:
                a_current_result += static_cast<float>(a_player_data_element->result_value);
                break;
        }
    }

    std::string player::process_max_handling(setting_data::player_data*& a_player_data_element,
        float& a_current_result) {
        if (a_player_data_element->max == setting_data::player_data::max_handling::none) {
            return {};
        }
        std::string value;
        auto* game_setting = setting::game_setting::get_singleton();
        if (a_player_data_element->max == setting_data::player_data::max_handling::armor) {
            auto max_armor = game_setting->get_max_armor_resistance();
            if (a_current_result > max_armor) {
                value = fmt::format(" ({}{})"sv, max_armor, a_player_data_element->ending);
            }
        } else if (a_player_data_element->max == setting_data::player_data::max_handling::resistance) {
            auto max_resistance = game_setting->get_max_resistance();
            if (a_current_result > max_resistance) {
                value = fmt::format(" ({}{})"sv, max_resistance, a_player_data_element->ending);
            }
        }

        return value;
    }

    void player::process_damage_resist(RE::PlayerCharacter*& a_player,
        setting_data::player_data*& a_player_data_element,
        actor_player_data*& a_player_data) {
        auto resist_damage = util::player::get_damage_resistance(a_player);
        a_player_data->value = util::type_util::get_float_as_string(resist_damage);
        if (!a_player_data_element->ending.empty()) {
            a_player_data->value += a_player_data_element->ending;
        }
        a_player_data->value += process_max_handling(a_player_data_element, resist_damage);
    }
}  // actor
