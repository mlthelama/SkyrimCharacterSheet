#pragma once
#include "data/stats/provider/playerdataprovider.h"
#include "data/stats/statitem.h"
#include "settings/stats/statssettings.h"

class player_data {
    using stats_item_map = std::map<stats_value, std::unique_ptr<stat_item>>;
    using show_menu = menu_util::show_menu;
    using stats_inventory_menu_value = menu_util::stats_inventory_menu_value;
    using stats_menu_value = menu_util::stats_menu_value;
    using slot_armor_map = std::map<std::string, std::string_view>;

public:
    static player_data* get_singleton() {
        static player_data singleton;
        return std::addressof(singleton);
    }

    [[nodiscard]] stats_item_map get_values_to_display(show_menu a_menu, std::string_view a_name) const {
        logger::debug("Get Values to Display for Menu ({}) ..."sv, a_name);
        stats_item_map simp;

        auto player = RE::PlayerCharacter::GetSingleton();

        auto stat_setting_map = stat_setting::get_singleton()->load();
        logger::debug("Config Map Size is {}"sv, stat_setting_map.size());

        for (auto& [fst, snd] : stat_setting_map) {
            auto stat_value = fst;
            auto stat_config = snd.get();

            stat_config->log_stat_config(stat_value);

            if ((a_menu == show_menu::m_stats && stat_config->get_stats_menu() == stats_menu_value::m_none) ||
                (a_menu == show_menu::m_stats_inventory &&
                    stat_config->get_stats_inventory_menu() == stats_inventory_menu_value::m_none)) {
                continue;
            }


            std::string value_text;

            switch (stat_value) {
                case stats_value::name:
                    value_text = player->GetName();
                    break;
                case stats_value::race:
                    value_text = player->GetRace()->GetFullName();
                    break;
                case stats_value::level:
                    value_text = std::to_string(player->GetLevel());
                    break;
                case stats_value::perk_count:
                    value_text = std::to_string(player->GetGameStatsData().perkCount);
                    break;
                case stats_value::height:
                    value_text = string_util::get_string_value_from_float(player->GetHeight());
                    break;
                case stats_value::equipped_weight:
                    value_text = string_util::get_string_value_from_float(player->GetWeight());
                    break;
                case stats_value::skill_trainings_this_level:
                    value_text = std::to_string(player->GetInfoRuntimeData().skillTrainingsThisLevel);
                    break;
                case stats_value::damage_arrow:
                    value_text = player_data_provider::get_arrow_damage(player);
                    break;
                case stats_value::damage:
                    value_text = player_data_provider::get_damage(player, false);
                    break;
                case stats_value::damage_left:
                    value_text = player_data_provider::get_damage(player, true);
                    break;
                case stats_value::beast:
                    value_text = player_data_provider::get_beast(
                        player->AsActorValueOwner()->GetActorValue(RE::ActorValue::kVampirePerks),
                        player->AsActorValueOwner()->GetActorValue(RE::ActorValue::kWerewolfPerks));
                    break;
                case stats_value::health_rate_per:
                    value_text = string_util::get_string_value_from_float(string_util::calculate_value(
                        player->AsActorValueOwner()->GetActorValue(RE::ActorValue::kHealRateMult),
                        player->AsActorValueOwner()->GetActorValue(RE::ActorValue::kHealRate)));
                    break;
                case stats_value::magicka_rate_per:
                    value_text = string_util::get_string_value_from_float(string_util::calculate_value(
                        player->AsActorValueOwner()->GetActorValue(RE::ActorValue::kMagickaRateMult),
                        player->AsActorValueOwner()->GetActorValue(RE::ActorValue::kMagickaRate)));
                    break;
                case stats_value::stamina_rate_per:
                    value_text = string_util::get_string_value_from_float(string_util::calculate_value(
                        player->AsActorValueOwner()->GetActorValue(RE::ActorValue::kStaminaRateMult),
                        player->AsActorValueOwner()->GetActorValue(RE::ActorValue::kStaminaRate)));
                    break;
                case stats_value::xp:
                    value_text = player_data_provider::get_xp(player);
                    break;
                case stats_value::weight:
                    value_text = string_util::get_string_value_from_float(player->GetWeight());
                    break;
                case stats_value::weapon_speed_mult:
                    value_text = player_data_provider::handle_weapon_speed(player, false);
                    break;
                case stats_value::left_weapon_speed_mult:
                    value_text = player_data_provider::handle_weapon_speed(player, true);
                    break;
                case stats_value::resist_damage:
                    value_text = player_data_provider::get_damage_resistance(player,
                        stat_config->get_cap(),
                        stat_config->get_ending());
                    break;
                case stats_value::weapon_reach:
                    value_text = player_data_provider::handle_weapon_reach(player, false);
                    break;
                case stats_value::weapon_reach_left:
                    value_text = player_data_provider::handle_weapon_reach(player, true);
                    break;
                case stats_value::weapon_base_damage:
                    value_text = player_data_provider::handle_weapon_base_damage(player, false);
                    break;
                case stats_value::weapon_base_damage_left:
                    value_text = player_data_provider::handle_weapon_base_damage(player, true);
                    break;
                case stats_value::weapon_stagger:
                    value_text = player_data_provider::handle_weapon_stagger(player, false);
                    break;
                case stats_value::weapon_stagger_left:
                    value_text = player_data_provider::handle_weapon_stagger(player, true);
                    break;
                case stats_value::weapon_crit_damage_rating:
                    value_text = player_data_provider::handle_weapon_crit(player, false);
                    break;
                case stats_value::weapon_crit_damage_rating_left:
                    value_text = player_data_provider::handle_weapon_crit(player, true);
                    break;
                case stats_value::fall_damage_mod:
                    value_text = string_util::get_string_value_from_float(
                        player_data_provider::get_fall_damage_mod(player) * stat_config->get_value_multiplier());
                    break;
                case stats_value::warmth:
                    value_text =
                        string_util::get_string_value_from_float(player_data_provider::get_warmth_rating(player, 0.0));
                    break;
                default:
                    if (stat_config->get_actor() != RE::ActorValue::kNone) {
                        //for whatever reason magicka, stamina and health enchantments count as permanent
                        auto value = player->AsActorValueOwner()->GetActorValue(stat_config->get_actor()) *
                                     stat_config->get_value_multiplier();
                        if (stat_config->get_cap() != -1) {
                            value_text = value_util::get_value_with_cap_if_needed(value,
                                stat_config->get_cap(),
                                stat_config->get_ending());
                        }

                        if (value_text.empty()) {
                            auto base_av = player->AsActorValueOwner()->GetBaseActorValue(stat_config->get_actor()) *
                                           stat_config->get_value_multiplier();
                            auto perm_av =
                                player->AsActorValueOwner()->GetPermanentActorValue(stat_config->get_actor()) *
                                stat_config->get_value_multiplier();
                            switch (stat_config->get_show_base_permanent_value()) {
                                case value_util::display_actor_value_type::m_value:
                                    value_text = string_util::get_string_value_from_float(value);
                                    break;
                                case value_util::display_actor_value_type::m_value_base:
                                    value_text = value_util::get_value_av_add(value, base_av);
                                    break;
                                case value_util::display_actor_value_type::m_value_permanent:
                                    value_text = value_util::get_value_av_add(value, perm_av);
                                    break;
                                case value_util::display_actor_value_type::m_value_base_permanent:
                                    value_text = value_util::get_value_ext_av(value, base_av, perm_av);
                                    break;
                            }
                        }
                    } else {
                        logger::warn("unhandeled stat, name {}, displayName {}"sv,
                            string_util::get_int_from_enum(stat_value),
                            stat_config->get_display_name());
                    }
                    break;
            }

            if (value_text.empty()) {
                continue;
            }

            //todo fix for some values should be shown if 0, atm hardcode noise here
            if (!setting::get_show_stats_inventorydisplay_zero() && value_text == "0" &&
                    a_menu == show_menu::m_stats_inventory ||
                !setting::get_show_stats_display_zero() && value_text == "0" && a_menu == show_menu::m_stats) {
                if (stat_config->get_actor() != RE::ActorValue::kMovementNoiseMult) {
                    continue;
                }
            }

            if (!value_text.empty()) {
                auto icon =
                    !stat_config->get_icon_string().empty() ? stat_config->get_icon_string() : icon_keys::default_icon;
                if (a_menu == show_menu::m_stats) {
                    simp[stat_value] = std::make_unique<stat_item>(stat_config->get_key_display(),
                        stat_config->get_value_display(value_text),
                        stat_config->get_stats_menu(),
                        icon);
                } else {
                    simp[stat_value] = std::make_unique<stat_item>(stat_config->get_key_display(),
                        stat_config->get_value_display(value_text),
                        stat_config->get_stats_inventory_menu(),
                        icon);
                }
            }
        }

        for (auto& [fst, snd] : stat_setting_map) {
            snd.reset();
        }
        stat_setting_map.clear();

        logger::debug("Setting Map is {}, Display Map Size is {} for Menu {}"sv,
            stat_setting_map.size(),
            simp.size(),
            a_name);

        return simp;
    }

    static slot_armor_map get_armor_map() {
        auto player = RE::PlayerCharacter::GetSingleton();
        return player_data_provider::get_equipment(player);
    }

    player_data(const player_data&) = delete;
    player_data(player_data&&) = delete;

    player_data& operator=(const player_data&) = delete;
    player_data& operator=(player_data&&) = delete;

private:
    player_data() = default;

    ~player_data() = default;
};
