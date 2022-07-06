#pragma once
#include "data/stats/provider/playerdataprovider.h"
#include "data/stats/statitem.h"
#include "settings/stats/statssettings.h"

class PlayerData {
    using StatsItemMap = std::map<stats_value, std::unique_ptr<stat_item>>;
    using ShowMenu = menu_util::show_menu;
    using StatsInventoryMenuValue = menu_util::stats_inventory_menu_value;
    using StatsMenuValue = menu_util::stats_menu_value;
    using SlotArmorMap = std::map<std::string, std::string_view>;

public:
    static PlayerData* GetSingleton() {
        static PlayerData singleton;
        return std::addressof(singleton);
    }

    StatsItemMap getValuesToDisplay(ShowMenu a_menu, std::string_view a_name) {
        logger::debug("Get Values to Display for Menu ({}) ..."sv, a_name);
        StatsItemMap simp;

        auto player = RE::PlayerCharacter::GetSingleton();

        auto statSettingMap = stat_setting::get_singleton()->load();
        logger::debug("Config Map Size is {}"sv, statSettingMap.size());

        for (auto& element : statSettingMap) {
            auto statValue = element.first;
            auto statConfig = element.second.get();

            statConfig->log_stat_config(statValue);

            if ((a_menu == ShowMenu::m_stats && statConfig->get_stats_menu() == StatsMenuValue::m_none) ||
                (a_menu == ShowMenu::m_stats_inventory &&
                    statConfig->get_stats_inventory_menu() == StatsInventoryMenuValue::m_none)) {
                continue;
            }


            std::string valueText = "";

            switch (statValue) {
                case stats_value::name:
                    valueText = player->GetName();
                    break;
                case stats_value::race:
                    valueText = player->GetRace()->GetFullName();
                    break;
                case stats_value::level:
                    valueText = std::to_string(player->GetLevel());
                    break;
                case stats_value::perk_count:
                    valueText = std::to_string(player->perkCount);
                    break;
                case stats_value::height:
                    valueText = string_util::get_string_value_from_float(player->GetHeight());
                    break;
                case stats_value::equipped_weight:
                    valueText = string_util::get_string_value_from_float(player->GetWeight());
                    break;
                case stats_value::skill_trainings_this_level:
                    valueText = std::to_string(player->skillTrainingsThisLevel);
                    break;
                case stats_value::damage_arrow:
                    valueText = player_data_provider::get_arrow_damage(player);
                    break;
                case stats_value::damage:
                    valueText = player_data_provider::get_damage(player, false);
                    break;
                case stats_value::damage_left:
                    valueText = player_data_provider::get_damage(player, true);
                    break;
                case stats_value::beast:
                    valueText = player_data_provider::get_beast(player->GetActorValue(RE::ActorValue::kVampirePerks),
                        player->GetActorValue(RE::ActorValue::kWerewolfPerks));
                    break;
                case stats_value::health_rate_per:
                    valueText = string_util::get_string_value_from_float(
                        string_util::calculate_value(player->GetActorValue(RE::ActorValue::kHealRateMult),
                            player->GetActorValue(RE::ActorValue::kHealRate)));
                    break;
                case stats_value::magicka_rate_per:
                    valueText = string_util::get_string_value_from_float(
                        string_util::calculate_value(player->GetActorValue(RE::ActorValue::kMagickaRateMult),
                            player->GetActorValue(RE::ActorValue::kMagickaRate)));
                    break;
                case stats_value::stamina_rate_per:
                    valueText = string_util::get_string_value_from_float(
                        string_util::calculate_value(player->GetActorValue(RE::ActorValue::kStaminaRateMult),
                            player->GetActorValue(RE::ActorValue::KStaminaRate)));
                    break;
                case stats_value::xp:
                    valueText = player_data_provider::get_xp(player);
                    break;
                case stats_value::weight:
                    valueText = string_util::get_string_value_from_float(player->GetWeight());
                    break;
                case stats_value::weapon_speed_mult:
                    valueText = player_data_provider::handle_weapon_speed(player, false);
                    break;
                case stats_value::left_weapon_speed_mult:
                    valueText = player_data_provider::handle_weapon_speed(player, true);
                    break;
                case stats_value::resist_damage:
                    valueText = player_data_provider::get_damage_resistance(player,
                        statConfig->get_cap(),
                        statConfig->get_ending());
                    break;
                case stats_value::weapon_reach:
                    valueText = player_data_provider::handle_weapon_reach(player, false);
                    break;
                case stats_value::weapon_reach_left:
                    valueText = player_data_provider::handle_weapon_reach(player, true);
                    break;
                case stats_value::weapon_base_damage:
                    valueText = player_data_provider::handle_weapon_base_damage(player, false);
                    break;
                case stats_value::weapon_base_damage_left:
                    valueText = player_data_provider::handle_weapon_base_damage(player, true);
                    break;
                case stats_value::weapon_stagger:
                    valueText = player_data_provider::handle_weapon_stagger(player, false);
                    break;
                case stats_value::weapon_stagger_left:
                    valueText = player_data_provider::handle_weapon_stagger(player, true);
                    break;
                case stats_value::weapon_crit_damage_rating:
                    valueText = player_data_provider::handle_weapon_crit(player, false);
                    break;
                case stats_value::weapon_crit_damage_rating_left:
                    valueText = player_data_provider::handle_weapon_crit(player, true);
                    break;
                case stats_value::fall_damage_mod:
                    valueText = string_util::get_string_value_from_float(
                        player_data_provider::get_fall_damage_mod(player) * statConfig->get_value_multiplier());
                    break;
                default:
                    if (statConfig->get_actor() != RE::ActorValue::kNone) {
                        //for whatever reason magicka, stamina and health enchantments count as permanent
                        auto value =
                            player->GetActorValue(statConfig->get_actor()) * statConfig->get_value_multiplier();

                        if (statConfig->get_cap() != -1) {
                            valueText = value_util::get_value_with_cap_if_needed(value,
                                statConfig->get_cap(),
                                statConfig->get_ending());
                        } else if (statConfig->get_show_perm_av()) {
                            auto permAV = player->GetPermanentActorValue(statConfig->get_actor()) *
                                          statConfig->get_value_multiplier();
                            valueText = value_util::get_value_with_perm_av(value, permAV);
                        } else {
                            valueText = string_util::get_string_value_from_float(value);
                        }
                    } else {
                        logger::warn("unhandeled stat, name {}, displayName {}"sv,
                            statValue,
                            statConfig->get_display_name());
                    }
                    break;
            }

            if (valueText == "") {
                continue;
            }

            //todo fix for some values should be shown if 0, atm hardcode noise here
            if ((!*settings::show_stats_inventorydisplay_zero && valueText == "0" &&
                    a_menu == ShowMenu::m_stats_inventory) ||
                (!*settings::show_stat_sdisplay_zero && valueText == "0" && a_menu == ShowMenu::m_stats)) {
                if (statConfig->get_actor() != RE::ActorValue::kMovementNoiseMult) {
                    continue;
                }
            }

            if (valueText != "") {
                if (a_menu == ShowMenu::m_stats) {
                    simp[statValue] =
                        std::make_unique<stat_item>(statConfig->get_display(valueText), statConfig->get_stats_menu());
                } else {
                    simp[statValue] = std::make_unique<stat_item>(statConfig->get_display(valueText),
                        statConfig->get_stats_inventory_menu());
                }
            }
        }

        for (auto& element : statSettingMap) { element.second.reset(); }
        statSettingMap.clear();

        logger::debug("Setting Map is {}, Display Map Size is {} for Menu ({})"sv,
            statSettingMap.size(),
            simp.size(),
            a_name);

        return simp;
    }

    SlotArmorMap getArmorMap() {
        auto player = RE::PlayerCharacter::GetSingleton();
        return player_data_provider::get_equipment(player);
    }

private:
    PlayerData() = default;
    PlayerData(const PlayerData&) = delete;
    PlayerData(PlayerData&&) = delete;

    ~PlayerData() = default;

    PlayerData& operator=(const PlayerData&) = delete;
    PlayerData& operator=(PlayerData&&) = delete;
};
