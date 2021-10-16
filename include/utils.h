#pragma once

inline static std::string cutString(std::string p_value) {
    std::string text;
    if (p_value.find(".") != std::string::npos) {
        auto s = p_value.substr(p_value.find(".") + 1, 2);
        if (count(s.begin(), s.end(), '0') == 2) {
            text += p_value.substr(0, p_value.find("."));
        } else {
            text += p_value.substr(0, p_value.find(".") + 3);
        }
    } else {
        text += p_value;
    }
    return text;
}

inline static std::string getStringValueFromFloat(float p_x) { return std::to_string(round(p_x * 100.0) / 100.0); }

inline static float calculateValue(float p_rm, float p_r) { return (p_rm * p_r) / 100; }

inline static int64_t getMultiplier(int64_t p_mp) {
    if (p_mp < 0) {
        logger::warn("multiplier value {} not supported, using 1"sv, p_mp);
        return 1;
    } else {
        return p_mp;
    }
}

inline static StatsMenuValue getStatsMenu(int64_t p_menu_id) {
    //in case the config value does not match
    if (configStatsMenu.find(p_menu_id) == configStatsMenu.end()) {
        logger::warn("can not find Menu {}"sv, p_menu_id);
        return StatsMenuValue::mNone;
    } else {
        return configStatsMenu.find(p_menu_id)->second;
    }
}

template <typename T>
inline static std::string intToHex(T i) {
    std::stringstream stream;
    stream << "0x" << std::setfill('0') << std::setw(sizeof(T) * 2) << std::hex << i;

    return stream.str();
}

inline static FactionMenuValue getFactionMenu(int64_t p_menu_id) {
    //in case the config value does not match
    if (configFactionMenu.find(p_menu_id) == configFactionMenu.end()) {
        logger::warn("can not find Menu {}"sv, p_menu_id);
        return FactionMenuValue::mNone;
    } else {
        return configFactionMenu.find(p_menu_id)->second;
    }
}

inline static std::string buildDisplayString(std::string p_value, std::string p_display_name, std::string p_ending,
    boolean p_show, boolean p_staticText, boolean p_value_is_display) {
    if (!p_value.empty() && !p_display_name.empty() && !p_show) {
        return "";
    }

    std::string guiText = "";

    if (p_value_is_display) {
        if (p_value == staticDisplayValue) {
            guiText = p_display_name;
        }
    } else {
        guiText = p_display_name;
        if (p_value.size() > 0) {
            guiText += ": ";
        }

        guiText += (p_staticText) ? p_value : cutString(p_value);

        guiText += p_ending;
    }

    return guiText;
}

inline static std::map<ShowMenu, std::string_view> menuName = { { ShowMenu::mStats, *Settings::showStatsTitleTitle },
    { ShowMenu::mFaction, *Settings::showFactionsTitleTitle } };

inline static std::string_view getMenuName(ShowMenu p_menu) {
    if (menuName.find(p_menu) == menuName.end()) {
        logger::warn("can not find Menu {}"sv, p_menu);
        return "";
    } else {
        return menuName.find(p_menu)->second;
    }
}

inline static std::string_view getNextMenuName(ShowMenu p_menu) {
    //if cast to an int value outside the enum it should be undefined
    return getMenuName(static_cast<ShowMenu>(static_cast<int>(p_menu) + 1));
}

inline static std::string_view getPrevMenuName(ShowMenu p_menu) {
    //if cast to an int value outside the enum it should be undefined
    return getMenuName(static_cast<ShowMenu>(static_cast<int>(p_menu) - 1));
}