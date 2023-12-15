#include "armor_rating_rescaled_remake.h"
#include "toml++/toml.h"
#include "util/type_util.h"

namespace mod {
    static double scaling_factor{};
    static bool disable_hidden{};
    static int overwrite_armor_cap{};

    void armor_rating_rescaled_remake::load_config() {
        auto config = toml::parse_file(R"(.\Data\SKSE\Plugins\ArmorRatingRescaledRemake.toml)");

        scaling_factor = config["General"]["ArmorScalingFactor"].value_or(1.0);
        disable_hidden = config["General"]["DisableHiddenArmorRating"].value_or(false);
        overwrite_armor_cap = config["General"]["OverrideArmorCap"].value_or(0);

        logger::trace(
            "Armor rating rescaled remake loaded. scaling factor {}, disable hidden {}, overwrite armor cap {}"sv,
            scaling_factor,
            disable_hidden,
            overwrite_armor_cap);
    }

    double armor_rating_rescaled_remake::get_scaling_factor() { return scaling_factor; }
    bool armor_rating_rescaled_remake::get_disable_hidden() { return disable_hidden; }
    int armor_rating_rescaled_remake::get_overwrite_armor_cap() { return overwrite_armor_cap; }

    float armor_rating_rescaled_remake::calculate_armor_damage_resistance(float a_armor_rating, int32_t a_pieces_worn) {
        const auto game_settings = setting::game_setting::get_singleton();

        auto hidden_resist = game_settings->get_armor_base_factor() * a_pieces_worn;
        auto vanilla_resist = a_armor_rating / 100 * game_settings->get_armor_scaling_factor();
        if (!disable_hidden) {
            vanilla_resist = vanilla_resist + hidden_resist;
        }

        auto function_one = vanilla_resist * 5.0 * static_cast<float>(scaling_factor);
        auto function_two = function_one / (1 + function_one);
        auto function_three = function_two + (1 - function_two) * hidden_resist;
        auto res = min(function_three, game_settings->get_max_armor_resistance());
        if (overwrite_armor_cap > 0 && res > overwrite_armor_cap) {
            res = overwrite_armor_cap;
        }

        //multiply by 100
        logger::trace("New Calculated Damage Resistance {}, hidden {}, vanilla {},  one {}, two {}, three {}, res {}",
            util::type_util::get_float_as_string(static_cast<float>(res)),
            hidden_resist,
            vanilla_resist,
            function_one,
            function_two,
            function_three,
            res);

        return static_cast<float>(res * 100);
    }
}  // mod
