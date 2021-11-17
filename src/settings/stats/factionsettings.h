#pragma once

class FactionConfig {
    using FactionMenuValue = MenuUtil::FactionMenuValue;

public:
    FactionConfig(std::string a_display_name, FactionMenuValue a_menu)
        : _displayName(a_display_name), _menu(a_menu), _displayIsValue(false) {}

    FactionConfig(std::string a_display_name, FactionMenuValue a_menu, bool a_display_is_value)
        : _displayName(a_display_name), _menu(a_menu), _displayIsValue(a_display_is_value) {}

    std::string getDisplayName() { return _displayName; }

    FactionMenuValue getMenu() { return _menu; }

    bool getDisplayIsValue() { return _displayIsValue; }

    std::string getDisplay(std::string a_value) {
        if (!a_value.empty()) {
            logger::trace("display {} got value {}, building text ..."sv, _displayName, a_value);
            return MenuUtil::buildDisplayString(a_value, _displayName, "", _displayIsValue);
        }
        return "";
    }

    void logStatConfig(FactionValue a_stats_value) {
        logger::trace("name {}, displayname ({}), menu {}, displayIsValue {}"sv,
            a_stats_value,
            _displayName,
            _menu,
            _displayIsValue);
    }

    FactionConfig() = delete;
    FactionConfig(const FactionConfig&) = default;
    FactionConfig(FactionConfig&&) = delete;

    ~FactionConfig() = default;

    FactionConfig& operator=(const FactionConfig&) = default;
    FactionConfig& operator=(FactionConfig&&) = delete;

private:
    std::string _displayName;
    FactionMenuValue _menu;
    bool _displayIsValue = false;
};

class FactionSetting {
    using FactionMap = std::map<FactionValue, std::unique_ptr<FactionConfig>>;

public:
    static FactionSetting* GetSingleton() {
        static FactionSetting singleton;
        return std::addressof(singleton);
    }

    FactionMap load() {
        auto factionMenu = MenuUtil::getFactionMenu(*Settings::factionMenu);
        auto thaneMenu = MenuUtil::getFactionMenu(*Settings::thaneMenu);
        auto championMenu = MenuUtil::getFactionMenu(*Settings::championMenu);

        FactionMap mp;
        mp[FactionValue::darkbrotherHood] =
            std::make_unique<FactionConfig>(*Settings::darkbrotherHoodString, factionMenu);
        mp[FactionValue::thiefsGuild] = std::make_unique<FactionConfig>(*Settings::thiefsGuildString, factionMenu);
        mp[FactionValue::orcFriend] = std::make_unique<FactionConfig>(*Settings::orcFriendString, factionMenu);
        mp[FactionValue::collegeOfWinterhold] =
            std::make_unique<FactionConfig>(*Settings::collegeOfWinterholdString, factionMenu);
        mp[FactionValue::companions] = std::make_unique<FactionConfig>(*Settings::companionsString, factionMenu);
        mp[FactionValue::imperialLegion] =
            std::make_unique<FactionConfig>(*Settings::imperialLegionString, factionMenu);
        mp[FactionValue::stormcloaks] = std::make_unique<FactionConfig>(*Settings::stormcloaksString, factionMenu);
        mp[FactionValue::greybeard] = std::make_unique<FactionConfig>(*Settings::greybeardString, factionMenu);
        mp[FactionValue::bard] = std::make_unique<FactionConfig>(*Settings::bardString, factionMenu);
        mp[FactionValue::volkiharVampireClan] =
            std::make_unique<FactionConfig>(*Settings::volkiharVampireClanString, factionMenu);
        mp[FactionValue::dawnguard] = std::make_unique<FactionConfig>(*Settings::dawnguardString, factionMenu);
        mp[FactionValue::houseTelvanni] = std::make_unique<FactionConfig>(*Settings::houseTelvanniString, factionMenu);

        mp[FactionValue::thaneOfEastmarch] =
            std::make_unique<FactionConfig>(*Settings::thaneOfEastmarchName, thaneMenu, true);
        mp[FactionValue::thaneOfFalkreath] =
            std::make_unique<FactionConfig>(*Settings::thaneOfFalkreathName, thaneMenu, true);
        mp[FactionValue::thaneOfHaafingar] =
            std::make_unique<FactionConfig>(*Settings::thaneOfHaafingarName, thaneMenu, true);
        mp[FactionValue::thaneOfHjaalmarch] =
            std::make_unique<FactionConfig>(*Settings::thaneOfHjaalmarchName, thaneMenu, true);
        mp[FactionValue::thaneOfThePale] =
            std::make_unique<FactionConfig>(*Settings::thaneOfThePaleName, thaneMenu, true);
        mp[FactionValue::thaneOfTheReach] =
            std::make_unique<FactionConfig>(*Settings::thaneOfTheReachName, thaneMenu, true);
        mp[FactionValue::thaneOfTheRift] =
            std::make_unique<FactionConfig>(*Settings::thaneOfTheRiftName, thaneMenu, true);
        mp[FactionValue::thaneOfWhiterun] =
            std::make_unique<FactionConfig>(*Settings::thaneOfWhiterunName, thaneMenu, true);
        mp[FactionValue::thaneOfWinterhold] =
            std::make_unique<FactionConfig>(*Settings::thaneOfWinterholdName, thaneMenu, true);

        mp[FactionValue::azura] = std::make_unique<FactionConfig>(*Settings::azuraName, championMenu, true);
        mp[FactionValue::clavicusVile] =
            std::make_unique<FactionConfig>(*Settings::clavicusVileName, championMenu, true);
        mp[FactionValue::hermaeusMora] =
            std::make_unique<FactionConfig>(*Settings::hermaeusMoraName, championMenu, true);
        mp[FactionValue::hircine] = std::make_unique<FactionConfig>(*Settings::hircineName, championMenu, true);
        mp[FactionValue::malacath] = std::make_unique<FactionConfig>(*Settings::malacathName, championMenu, true);
        mp[FactionValue::mehrunesDagon] =
            std::make_unique<FactionConfig>(*Settings::mehrunesDagonName, championMenu, true);
        mp[FactionValue::mephala] = std::make_unique<FactionConfig>(*Settings::mephalaName, championMenu, true);
        mp[FactionValue::meridia] = std::make_unique<FactionConfig>(*Settings::meridiaName, championMenu, true);
        mp[FactionValue::molagBal] = std::make_unique<FactionConfig>(*Settings::molagBalName, championMenu, true);
        mp[FactionValue::namira] = std::make_unique<FactionConfig>(*Settings::namiraName, championMenu, true);
        mp[FactionValue::nocturnal] = std::make_unique<FactionConfig>(*Settings::nocturnalName, championMenu, true);
        mp[FactionValue::peryite] = std::make_unique<FactionConfig>(*Settings::peryiteName, championMenu, true);
        mp[FactionValue::sanguine] = std::make_unique<FactionConfig>(*Settings::sanguineName, championMenu, true);
        mp[FactionValue::sheogorath] = std::make_unique<FactionConfig>(*Settings::sheogorathName, championMenu, true);
        mp[FactionValue::vaermina] = std::make_unique<FactionConfig>(*Settings::vaerminaName, championMenu, true);

        return mp;
    }

    FactionSetting() = default;
    FactionSetting(const FactionSetting&) = default;
    FactionSetting(FactionSetting&&) = delete;

    ~FactionSetting() = default;

    FactionSetting& operator=(const FactionSetting&) = default;
    FactionSetting& operator=(FactionSetting&&) = delete;
};
