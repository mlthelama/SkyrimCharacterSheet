#pragma once
#include "setting/data/menu_data.h"

namespace setting_data {
    class overwrite_mod_data {
    public:
        std::string display_name;
        std::string icon_string;
    };

    class single_actor_value {
    public:
        RE::ActorValue actor_value = RE::ActorValue::kNone;
    };

    class multiple_actor_value {
    public:
        std::vector<RE::ActorValue> actor_value_list;
    };

    class actor_value_data
        : public single_actor_value
        , public multiple_actor_value {};

    class player_data {
    public:
        enum class stat {
            name,
            race,
            level,
            perk_count,
            height,
            equipped_weight,
            weight,
            armor,
            damage,
            skill_trainings_this_level,
            health,
            health_rate_per,
            magicka,
            magicka_rate_per,
            stamina,
            stamina_rate_per,
            resist_damage,
            resist_disease,
            resist_poison,
            resist_fire,
            resist_shock,
            resist_frost,
            resist_magic,
            one_handed,
            two_handed,
            archery,
            block,
            smithing,
            heavy_armor,
            light_armor,
            pickpocket,
            lockpicking,
            sneak,
            alchemy,
            speech,
            enchanting,
            alteration,
            conjuration,
            destruction,
            illusion,
            restoration,
            one_handed_power_mod,
            two_handed_power_mod,
            archery_power_mod,
            block_power_mod,
            smithing_power_mod,
            heavy_armor_power_mod,
            light_armor_power_mod,
            pickpocket_power_mod,
            lockpicking_power_mod,
            sneak_power_mod,
            alchemy_power_mod,
            speech_power_mod,
            enchanting_power_mod,
            alteration_power_mod,
            conjuration_power_mod,
            destruction_power_mod,
            illusion_power_mod,
            restoration_power_mod,
            speed_mult,
            inventory_weight,
            carry_weight,
            critical_chance,
            melee_damage,
            unarmed_damage,
            absorb_chance,
            weapon_speed_mult,
            bow_speed_bonus,
            shout_recovery_mult,
            movement_noise_mult,
            dragon_souls,
            combat_health_regen_multiply,
            attack_damage_mult,
            beast,
            xp,
            reflect_damage,
            one_handed_mod,
            two_handed_mod,
            marksman_mod,
            block_mod,
            smithing_mod,
            heavy_armor_mod,
            light_armor_mod,
            pickpocket_mod,
            lockpicking_mod,
            sneaking_mod,
            alchemy_mod,
            speechcraft_mod,
            alteration_mod,
            conjuration_mod,
            destruction_mod,
            illusion_mod,
            restoration_mod,
            enchanting_mod,
            damage_arrow,
            damage_left,
            left_weapon_speed_mult,
            right_item_charge,
            left_item_charge,
            armor_perks,
            mass,
            bow_stagger_bonus,
            bypass_vendor_keyword_check,
            bypass_vendor_stolen_check,
            weapon_reach,
            weapon_reach_left,
            weapon_base_damage,
            weapon_base_damage_left,
            weapon_stagger,
            weapon_stagger_left,
            weapon_crit_damage_rating,
            weapon_crit_damage_rating_left,
            fall_damage_mod,
            warmth,
            custom
        };

        enum class value_handling { single, multiply, value_or };

        enum class result_value_handling { none, multiply, divide, add };

        enum class max_handling { none, armor, resistance };

        enum class mod_values { none, armor_rating_rescaled_remake, hand_to_hand, skyrim_unbound, skyrim_souls };

        stat key;
        std::string display_name;
        actor_value_data actor_value;
        value_handling actor_value_handling;
        std::string ending;
        result_value_handling result_handling;
        int32_t result_value;
        max_handling max;
        std::string icon_string;
        mod_values overwrite_mod;
        overwrite_mod_data* mod_data;
        setting_data::menu_data::stats_column_type stats_column;
        setting_data::menu_data::stats_inventory_column_type stats_inventory_column;

        inline void log() {
            std::string log_string =
                fmt::format("key '{}', display_name '{}'"sv, magic_enum::enum_name(key), display_name);
            if (actor_value_handling == value_handling::single) {
                if (actor_value.actor_value != RE::ActorValue::kNone) {
                    log_string += fmt::format(", actor_value '{}'"sv, magic_enum::enum_name(actor_value.actor_value));
                }
            } else {
                log_string += fmt::format(", actor_value_list count '{}'"sv, actor_value.actor_value_list.size());
            }
            log_string += fmt::format(", value_handling '{}'"sv, magic_enum::enum_name(actor_value_handling));
            if (!ending.empty()) {
                log_string += fmt::format(", ending '{}'"sv, ending);
            }
            if (result_handling != result_value_handling::none) {
                log_string += fmt::format(", result_handling '{}'"sv, magic_enum::enum_name(result_handling));
            }
            if (result_value != 0) {
                log_string += fmt::format(", result_value '{}'"sv, result_value);
            }
            if (max != max_handling::none) {
                log_string += fmt::format(", display_max '{}'"sv, magic_enum::enum_name(max));
            }
            if (!icon_string.empty()) {
                log_string += fmt::format(", icon_string '{}'"sv, icon_string);
            }
            if (overwrite_mod != mod_values::none) {
                log_string += fmt::format(", overwrite_mod '{}'"sv, magic_enum::enum_name(overwrite_mod));
            }
            if (overwrite_mod != mod_values::none && mod_data) {
                if (!mod_data->display_name.empty()) {
                    log_string += fmt::format(", overwrite display_name '{}'"sv, mod_data->display_name);
                }
                if (!mod_data->icon_string.empty()) {
                    log_string += fmt::format(", overwrite icon_string '{}'"sv, mod_data->icon_string);
                }
            }
            log_string += fmt::format(", stats column '{}'"sv, magic_enum::enum_name(stats_column));
            log_string += fmt::format(", stats inv column '{}'"sv, magic_enum::enum_name(stats_inventory_column));

            logger::trace("{}"sv, log_string);
        }
    };
}
