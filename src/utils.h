#pragma once

static std::string cutString(std::string a_value) {
    std::string text;
    if (a_value.find(".") != std::string::npos) {
        auto s = a_value.substr(a_value.find(".") + 1, 2);
        if (count(s.begin(), s.end(), '0') == 2) {
            text = a_value.substr(0, a_value.find("."));
        } else {
            text = a_value.substr(0, a_value.find(".") + 3);
        }
    } else {
        text = a_value;
    }
    return text;
}

static std::string getStringValueFromFloat(float a_x) { return cutString(fmt::format(FMT_STRING("{:.2f}"), a_x)); }

static float calculateValue(float a_rm, float a_r) { return (a_rm * a_r) / 100; }

static int64_t getMultiplier(int64_t a_mp) {
    if (a_mp < 0) {
        logger::warn("multiplier value {} not supported, using 1"sv, a_mp);
        return 1;
    } else {
        return a_mp;
    }
}

static StatsMenuValue getStatsMenu(int64_t a_menu_id) {
    //in case the config value does not match
    if (_constConfigStatsMenu.find(a_menu_id) == _constConfigStatsMenu.end()) {
        logger::warn("can not find Menu {}"sv, a_menu_id);
        return StatsMenuValue::mNone;
    } else {
        return _constConfigStatsMenu.find(a_menu_id)->second;
    }
}

template <typename T>
static std::string intToHex(T i) {
    std::stringstream stream;
    stream << "0x" << std::setfill('0') << std::setw(sizeof(T) * 2) << std::hex << i;

    return stream.str();
}

static FactionMenuValue getFactionMenu(int64_t a_menu_id) {
    //in case the config value does not match
    if (_constConfigFactionMenu.find(a_menu_id) == _constConfigFactionMenu.end()) {
        logger::warn("can not find Menu {}"sv, a_menu_id);
        return FactionMenuValue::mNone;
    } else {
        return _constConfigFactionMenu.find(a_menu_id)->second;
    }
}

static std::string buildDisplayString(std::string a_value,
    std::string a_display_name,
    std::string a_ending,
    bool a_show,
    bool a_value_is_display) {
    if (!a_value.empty() && !a_display_name.empty() && !a_show) {
        return "";
    }

    std::string guiText;

    if (a_value_is_display) {
        if (a_value == _constStaticDisplayValue) {
            guiText = a_display_name;
        }
    } else {
        auto seperator = (a_value.size() > 0) ? ": " : "";
        guiText = fmt::format(FMT_STRING("{}{}{}{}"), a_display_name, seperator, a_value, a_ending);
    }

    return guiText;
}

static std::map<ShowMenu, std::string_view> menuName = {
    { ShowMenu::mStats, static_cast<std::string_view>(*Settings::showStatsTitleTitle) },
    { ShowMenu::mFaction, static_cast<std::string_view>(*Settings::showFactionsTitleTitle) }
};

static std::string_view getMenuName(ShowMenu a_menu) {
    if (menuName.find(a_menu) == menuName.end()) {
        logger::warn("can not find Menu {}"sv, a_menu);
        return "";
    } else {
        return menuName.find(a_menu)->second;
    }
}

static std::string_view getNextMenuName(ShowMenu a_menu) {
    //if cast to an int value outside the enum it should be _constUndefined
    return getMenuName(static_cast<ShowMenu>(static_cast<int>(a_menu) + 1));
}

static std::string_view getPrevMenuName(ShowMenu a_menu) {
    //if cast to an int value outside the enum it should be _constUndefined
    return getMenuName(static_cast<ShowMenu>(static_cast<int>(a_menu) - 1));
}

static void logResolution() {
    const auto* const state = RE::BSGraphics::State::GetSingleton();
    logger::trace("Screen Resolution {}x{}"sv, state->screenWidth, state->screenHeight);
}

static float calculateArmorDamageRes(float a_armor_rating, int32_t a_pieces_worn) {
    return (float(a_armor_rating * 0.12) + float(3 * a_pieces_worn));
}

static std::string getValueWithCapIfNeeded(float a_res, float a_cap, std::string a_ending) {
    auto value = getStringValueFromFloat(a_res);

    if (a_res > a_cap) {
        value = fmt::format(FMT_STRING("{}{} ({})"),
            getStringValueFromFloat(a_cap),
            a_ending,
            getStringValueFromFloat(a_res));
    }
    return value;
}
