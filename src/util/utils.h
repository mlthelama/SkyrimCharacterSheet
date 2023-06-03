#pragma once
#include "menukeys.h"
#include "mod/armor_rating_rescaled_remake.h"
#include "mod/mod_manager.h"
#include "setting/game_setting.h"

namespace string_util {
    static std::string cut_string(std::string a_value) {
        std::string text;
        if (a_value.find(".") != std::string::npos) {
            if (auto s = a_value.substr(a_value.find(".") + 1, 2); std::ranges::count(s, '0') == 2) {
                text = a_value.substr(0, a_value.find("."));
            } else {
                text = a_value.substr(0, a_value.find(".") + 3);
            }
        } else {
            text = a_value;
        }
        return text;
    }

    static std::string get_string_value_from_float(float a_x) {
        return cut_string(fmt::format(FMT_STRING("{:.2f}"), a_x));
    }

    static float calculate_value(const float a_rm, const float a_r) { return (a_rm * a_r) / 100; }

    template <typename T>
    static std::string int_to_hex(T a_i) {
        std::stringstream stream;
        stream << "0x" << std::setfill('0') << std::setw(sizeof(T) * 2) << std::hex << a_i;

        return stream.str();
    }

    template <typename T>
    static std::string delimit_two_values(const float a_v1, const float a_v2, T v_d) {
        return fmt::format(FMT_STRING("{}{}{}"),
            get_string_value_from_float(a_v1),
            v_d,
            get_string_value_from_float(a_v2));
    }


    template <typename T, std::enable_if_t<std::is_enum_v<T>, int> = 0>
    static int get_int_from_enum(const T& value) {
        return static_cast<int>(value);
    }

}

namespace menu_util {
    enum class show_menu { m_stats, m_faction, m_stats_inventory };

    static std::map<show_menu, std::string_view> menu_name = { { show_menu::m_stats, menu_keys::show_stats_title },
        { show_menu::m_faction, menu_keys::show_factions_title },
        { show_menu::m_stats_inventory, menu_keys::show_stats_inventory_title } };

    enum class stats_menu_value {
        m_none = 0,
        m_player = 1,
        m_defence = 2,
        m_attack = 3,
        m_magic = 4,
        m_warrior = 5,
        m_thief = 6,
        m_special = 7  //header or bottom
    };

    /* config can not work with enums, so lets map it*/
    inline static std::map<int64_t, stats_menu_value> const_config_stats_menu = {
        { static_cast<int64_t>(stats_menu_value::m_none), stats_menu_value::m_none },
        { static_cast<int64_t>(stats_menu_value::m_player), stats_menu_value::m_player },
        { static_cast<int64_t>(stats_menu_value::m_defence), stats_menu_value::m_defence },
        { static_cast<int64_t>(stats_menu_value::m_attack), stats_menu_value::m_attack },
        { static_cast<int64_t>(stats_menu_value::m_magic), stats_menu_value::m_magic },
        { static_cast<int64_t>(stats_menu_value::m_warrior), stats_menu_value::m_warrior },
        { static_cast<int64_t>(stats_menu_value::m_thief), stats_menu_value::m_thief },
        { static_cast<int64_t>(stats_menu_value::m_special), stats_menu_value::m_special }
    };

    enum class faction_menu_value { m_none = 0, m_faction = 1, m_thane = 2, m_champion = 3 };

    /* config can not work with enums, so lets map it*/
    inline static std::map<int64_t, faction_menu_value> const_config_faction_menu = {
        { static_cast<int64_t>(faction_menu_value::m_none), faction_menu_value::m_none },
        { static_cast<int64_t>(faction_menu_value::m_faction), faction_menu_value::m_faction },
        { static_cast<int64_t>(faction_menu_value::m_thane), faction_menu_value::m_thane },
        { static_cast<int64_t>(faction_menu_value::m_champion), faction_menu_value::m_champion },
    };

    enum class stats_inventory_menu_value { m_none = 0, m_equip = 1, m_armor = 2, m_weapon = 3, m_effect = 4 };

    /* config can not work with enums, so lets map it*/
    inline static std::map<int64_t, stats_inventory_menu_value> const_config_stats_inventory_menu = {
        { static_cast<int64_t>(stats_inventory_menu_value::m_none), stats_inventory_menu_value::m_none },
        { static_cast<int64_t>(stats_inventory_menu_value::m_equip), stats_inventory_menu_value::m_equip },
        { static_cast<int64_t>(stats_inventory_menu_value::m_armor), stats_inventory_menu_value::m_armor },
        { static_cast<int64_t>(stats_inventory_menu_value::m_weapon), stats_inventory_menu_value::m_weapon },
        { static_cast<int64_t>(stats_inventory_menu_value::m_effect), stats_inventory_menu_value::m_effect },
    };

    static std::string_view get_menu_name(const show_menu a_menu) {
        if (!menu_name.contains(a_menu)) {
            logger::warn("can not find Name for Menu {}"sv, string_util::get_int_from_enum(a_menu));
            return "";
        }
        return menu_name.find(a_menu)->second;
    }

    static stats_menu_value get_stats_menu(int64_t a_menu_id) {
        //in case the config value does not match
        if (!const_config_stats_menu.contains(a_menu_id)) {
            logger::warn("({}) can not find Menu {}"sv, get_menu_name(show_menu::m_stats), a_menu_id);
            return stats_menu_value::m_none;
        }
        return const_config_stats_menu.find(a_menu_id)->second;
    }

    static faction_menu_value get_faction_menu(int64_t a_menu_id) {
        //in case the config value does not match
        if (!const_config_faction_menu.contains(a_menu_id)) {
            logger::warn("({}) can not find Menu {}"sv, get_menu_name(show_menu::m_faction), a_menu_id);
            return faction_menu_value::m_none;
        }
        return const_config_faction_menu.find(a_menu_id)->second;
    }

    static stats_inventory_menu_value get_stats_inventory_menu(int64_t a_menu_id) {
        //in case the config value does not match
        if (!const_config_stats_inventory_menu.contains(a_menu_id)) {
            logger::warn("({}) can not find Menu {}"sv, get_menu_name(show_menu::m_stats_inventory), a_menu_id);
            return stats_inventory_menu_value::m_none;
        }
        return const_config_stats_inventory_menu.find(a_menu_id)->second;
    }

    static show_menu get_next_menu(show_menu a_menu) { return static_cast<show_menu>(static_cast<int>(a_menu) + 1); }

    static show_menu get_prev_menu(show_menu a_menu) { return static_cast<show_menu>(static_cast<int>(a_menu) - 1); }

    static std::string_view get_next_menu_name(const show_menu a_menu) {
        //if cast to an int value outside the enum it should be _constUndefined
        return get_menu_name(get_next_menu(a_menu));
    }

    static std::string_view get_prev_menu_name(const show_menu a_menu) {
        //if cast to an int value outside the enum it should be _constUndefined
        return get_menu_name(get_prev_menu(a_menu));
    }

    //TODO
    static void log_resolution() {
        const auto* const state = RE::BSGraphics::State::GetSingleton();
        logger::trace("Screen Resolution {}x{}"sv, state->screenWidth, state->screenHeight);
    }

    //TODO
    static int get_multiplier(int a_mp) {
        if (a_mp < 0) {
            logger::warn("multiplier value {} not supported, using 1"sv, a_mp);
            return const_static_multiplier;
        }
        return a_mp;
    }

    static std::string build_value_string(std::string a_value, std::string a_ending) {
        return fmt::format(FMT_STRING("{}{}"), a_value, a_ending);
    }
}

namespace value_util {

    static float calculate_armor_damage_res_ARRSR(const float a_armor_rating, const int32_t a_pieces_worn) {
        const auto game_settings = setting::game_setting::get_singleton();

        const auto overwrite = mod::armor_rating_rescaled_remake::get_overwrite_armor_cap();

        auto hidden_resist = game_settings->get_armor_base_factor() * a_pieces_worn;
        auto vanilla_resist = a_armor_rating / 100 * game_settings->get_armor_scaling_factor();
        if (!mod::armor_rating_rescaled_remake::get_disable_hidden()) {
            vanilla_resist = vanilla_resist + hidden_resist;
        }

        auto function_one = vanilla_resist * 5.0 * mod::armor_rating_rescaled_remake::get_scaling_factor();
        auto function_two = function_one / (1 + function_one);
        auto function_three = function_two + (1 - function_two) * hidden_resist;
        auto res = min(function_three, game_settings->get_max_armor_resistance());
        if (overwrite > 0 && res > overwrite) {
            res = overwrite;
        }

        //multiply by 100
        logger::trace("New Calculated Damage Resistance {}, hidden {}, vanilla {},  one {}, two {}, three {}, res {}",
            string_util::get_string_value_from_float(res),
            hidden_resist,
            vanilla_resist,
            function_one,
            function_two,
            function_three,
            res);

        return res * 100;
    }

    static float calculate_armor_damage_res(const float a_armor_rating, const int32_t a_pieces_worn) {
        const auto game_settings = setting::game_setting::get_singleton();

        if (mod::mod_manager::get_singleton()->get_armor_rating_rescaled_remake()) {
            return calculate_armor_damage_res_ARRSR(a_armor_rating, a_pieces_worn);
        }

        return a_armor_rating * game_settings->get_armor_scaling_factor() +
               game_settings->get_armor_base_factor() * 100 * a_pieces_worn;
    }

    //TODO
    static std::string get_value_with_cap_if_needed(const float a_res, const float a_cap, std::string a_ending) {
        auto value = string_util::get_string_value_from_float(a_res);

        if (a_res > a_cap) {
            value = fmt::format(FMT_STRING("{}{} ({})"),
                string_util::get_string_value_from_float(a_cap),
                a_ending,
                string_util::get_string_value_from_float(a_res));
        }
        return value;
    }

    //TODO
    static std::string get_value_av_add(const float a_av, const float a_add_av) {
        if (a_av != a_add_av) {
            return fmt::format(FMT_STRING("{} ({})"),
                string_util::get_string_value_from_float(a_av),
                string_util::get_string_value_from_float(a_add_av));
        }
        return string_util::get_string_value_from_float(a_av);
    }

    //TODO
    static std::string get_value_ext_av(const float a_av, const float a_base_av, const float a_perm_av) {
        if (a_av != a_base_av != a_perm_av) {
            return fmt::format(FMT_STRING("{} ({}) ({})"),
                string_util::get_string_value_from_float(a_av),
                string_util::get_string_value_from_float(a_base_av),
                string_util::get_string_value_from_float(a_perm_av));
        }
        return string_util::get_string_value_from_float(a_av);
    }


    enum class display_actor_value_type {
        m_value = 0,
        m_value_base = 1,
        m_value_permanent = 2,
        m_value_base_permanent = 3
    };

    inline static std::map<int64_t, display_actor_value_type> const_config_display_actor_value_type = {
        { static_cast<int64_t>(display_actor_value_type::m_value), display_actor_value_type::m_value },
        { static_cast<int64_t>(display_actor_value_type::m_value_base), display_actor_value_type::m_value_base },
        { static_cast<int64_t>(display_actor_value_type::m_value_permanent),
            display_actor_value_type::m_value_permanent },
        { static_cast<int64_t>(display_actor_value_type::m_value_base_permanent),
            display_actor_value_type::m_value_base_permanent },
    };

    static display_actor_value_type get_display_actor_value_type(int64_t a_type_id) {
        if (!const_config_display_actor_value_type.contains(a_type_id)) {
            logger::warn("Can not find display value type {}"sv, a_type_id);
            return display_actor_value_type::m_value;
        }
        return const_config_display_actor_value_type.find(a_type_id)->second;
    }
}

namespace vector_util {
    static std::vector<uint16_t> get_intersect(std::vector<uint16_t>& a_vec_first,
        std::vector<uint16_t>& a_vec_second) {
        std::vector<uint16_t> intersection_vector;

        std::ranges::sort(a_vec_first);
        std::ranges::sort(a_vec_second);

        std::ranges::set_intersection(a_vec_first, a_vec_second, back_inserter(intersection_vector));
        return intersection_vector;
    }

    template <typename T>
    static std::string get_delimited_string(std::vector<T>& a_vec) {
        auto deli_string =
            a_vec.empty() ?
                "" :
                std::accumulate(std::begin(a_vec), std::end(a_vec), std::string{}, [](std::string r, const int p) {
                    return std::move(r) + std::to_string(p) + ",";
                });

        if (!deli_string.empty()) {
            deli_string.pop_back();
        }
        return deli_string;
    }
}

namespace quest_util {
    static std::vector<uint16_t> get_stages_if_complete(RE::TESQuest* a_quest) {
        std::vector<uint16_t> fin_stages;

        //all favour quests finish at 25 except rift = 20
        auto hex = string_util::int_to_hex(a_quest->GetFormID());
        logger::debug("Questname ({}), formid {}, prio {}"sv, a_quest->GetName(), hex, a_quest->data.priority);

        //todo make util function if for checking stages
        logger::trace("executed Stages for quest {}"sv, hex);
        const auto exec = a_quest->executedStages;
        for (auto it = exec->begin(); it != exec->end(); ++it) {
            const auto& [data] = *it;
            auto [index, flags, pad3, pad4] = data;
            logger::trace("index {}, flag {}"sv, index, flags.underlying());
            if (flags.underlying() == 1) {
                fin_stages.push_back(index);
            }
        }

        logger::trace("waiting Stages for quest {}"sv, hex);
        const auto waiting = a_quest->waitingStages;
        for (auto it = waiting->begin(); it != waiting->end(); ++it) {
            const auto i = *it;
            auto [index, flags, pad3, pad4] = i->data;
            logger::trace("index {}, flag {}"sv, index, flags.underlying());
            if (flags.underlying() == 1) {
                fin_stages.push_back(index);
            }
        }
        return fin_stages;
    }

    static bool is_one_quest_stage_complete(RE::TESQuest* a_quest, std::vector<uint16_t> a_stages) {
        auto fin_stages = get_stages_if_complete(a_quest);
        auto intersect = vector_util::get_intersect(fin_stages, a_stages);
        auto hex = string_util::int_to_hex(a_quest->GetFormID());

        logger::debug("For Quest {}, got Stages (Values)/size completed ({})/{}, given ({})/{}, intersect ({})/{}"sv,
            hex,
            vector_util::get_delimited_string(fin_stages),
            fin_stages.size(),
            vector_util::get_delimited_string(a_stages),
            a_stages.size(),
            vector_util::get_delimited_string(intersect),
            intersect.size());

        return !intersect.empty();
    }

    static bool is_quest_stage_complete(RE::TESQuest* a_quest, const uint16_t a_stage) {
        return is_one_quest_stage_complete(a_quest, std::vector{ a_stage });
    }

    static bool is_quest_stage_complete(const RE::FormID a_form_id, const uint16_t a_stage) {
        const auto qst = RE::TESForm::LookupByID(a_form_id)->As<RE::TESQuest>();
        return is_quest_stage_complete(qst, a_stage);
    }

    static bool is_one_quest_stage_complete(const RE::FormID a_form_id, const std::vector<uint16_t> a_stages) {
        const auto qst = RE::TESForm::LookupByID(a_form_id)->As<RE::TESQuest>();
        return is_one_quest_stage_complete(qst, a_stages);
    }

    static uint16_t get_as(const int a_i) { return static_cast<uint16_t>(a_i); }
}
