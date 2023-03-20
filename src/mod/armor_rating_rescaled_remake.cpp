#include "armor_rating_rescaled_remake.h"
#include "toml++/toml.h"

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
}  // mod
