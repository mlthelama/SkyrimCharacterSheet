#pragma once

class FactionConfig {
    using FactionMenuValue = MenuUtil::FactionMenuValue;
public:
    FactionConfig(std::string a_display_name, bool a_show, FactionMenuValue a_menu)
        : _displayName(a_display_name), _show(a_show), _menu(a_menu), _displayIsValue(false) {}

    FactionConfig(std::string a_display_name, bool a_show, FactionMenuValue a_menu, bool a_display_is_value)
        : _displayName(a_display_name), _show(a_show), _menu(a_menu), _displayIsValue(a_display_is_value) {}

    std::string getDisplayName() { return _displayName; }

    bool getShow() { return _show; }

    FactionMenuValue getMenu() { return _menu; }

    bool getDisplayIsValue() { return _displayIsValue; }

    std::string getDisplay(std::string a_value) {
        if (!a_value.empty()) {
            logger::trace("display {} got value {}, building text ..."sv, _displayName, a_value);
            return MenuUtil::buildDisplayString(a_value, _displayName, "", _show, _displayIsValue);
        }
        return "";
    }

    void logStatConfig(FactionValue a_stats_value) {
        logger::trace("name {}, displayname ({}), show {}, menu {}, displayIsValue {}"sv,
            a_stats_value,
            _displayName,
            _show,
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
    bool _show;
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
        FactionMap mp;
        /*change to brace init*/
        auto factionMenu = MenuUtil::getFactionMenu(*Settings::factionMenu);
        mp[FactionValue::darkbrotherHood] =
            std::make_unique<FactionConfig>(*Settings::darkbrotherHoodString, *Settings::showFactions, factionMenu);
        mp[FactionValue::thiefsGuild] =
            std::make_unique<FactionConfig>(*Settings::thiefsGuildString, *Settings::showFactions, factionMenu);
        mp[FactionValue::orcFriend] =
            std::make_unique<FactionConfig>(*Settings::orcFriendString, *Settings::showFactions, factionMenu);
        mp[FactionValue::collegeOfWinterhold] =
            std::make_unique<FactionConfig>(*Settings::collegeOfWinterholdString, *Settings::showFactions, factionMenu);
        mp[FactionValue::companions] =
            std::make_unique<FactionConfig>(*Settings::companionsString, *Settings::showFactions, factionMenu);
        mp[FactionValue::imperialLegion] =
            std::make_unique<FactionConfig>(*Settings::imperialLegionString, *Settings::showFactions, factionMenu);
        mp[FactionValue::stormcloaks] =
            std::make_unique<FactionConfig>(*Settings::stormcloaksString, *Settings::showFactions, factionMenu);
        mp[FactionValue::greybeard] =
            std::make_unique<FactionConfig>(*Settings::greybeardString, *Settings::showFactions, factionMenu);
        mp[FactionValue::bard] =
            std::make_unique<FactionConfig>(*Settings::bardString, *Settings::showFactions, factionMenu);
        mp[FactionValue::volkiharVampireClan] =
            std::make_unique<FactionConfig>(*Settings::volkiharVampireClanString, *Settings::showFactions, factionMenu);
        mp[FactionValue::dawnguard] =
            std::make_unique<FactionConfig>(*Settings::dawnguardString, *Settings::showFactions, factionMenu);
        mp[FactionValue::houseTelvanni] =
            std::make_unique<FactionConfig>(*Settings::houseTelvanniString, *Settings::showFactions, factionMenu);

        auto thaneMenu = MenuUtil::getFactionMenu(*Settings::thaneMenu);
        mp[FactionValue::thaneOfEastmarch] =
            std::make_unique<FactionConfig>(*Settings::thaneOfEastmarchName, *Settings::showThanes, thaneMenu, true);
        mp[FactionValue::thaneOfFalkreath] =
            std::make_unique<FactionConfig>(*Settings::thaneOfFalkreathName, *Settings::showThanes, thaneMenu, true);
        mp[FactionValue::thaneOfHaafingar] =
            std::make_unique<FactionConfig>(*Settings::thaneOfHaafingarName, *Settings::showThanes, thaneMenu, true);
        mp[FactionValue::thaneOfHjaalmarch] =
            std::make_unique<FactionConfig>(*Settings::thaneOfHjaalmarchName, *Settings::showThanes, thaneMenu, true);
        mp[FactionValue::thaneOfThePale] =
            std::make_unique<FactionConfig>(*Settings::thaneOfThePaleName, *Settings::showThanes, thaneMenu, true);
        mp[FactionValue::thaneOfTheReach] =
            std::make_unique<FactionConfig>(*Settings::thaneOfTheReachName, *Settings::showThanes, thaneMenu, true);
        mp[FactionValue::thaneOfTheRift] =
            std::make_unique<FactionConfig>(*Settings::thaneOfTheRiftName, *Settings::showThanes, thaneMenu, true);
        mp[FactionValue::thaneOfWhiterun] =
            std::make_unique<FactionConfig>(*Settings::thaneOfWhiterunName, *Settings::showThanes, thaneMenu, true);
        mp[FactionValue::thaneOfWinterhold] =
            std::make_unique<FactionConfig>(*Settings::thaneOfWinterholdName, *Settings::showThanes, thaneMenu, true);

        auto championMenu = MenuUtil::getFactionMenu(*Settings::championMenu);
        mp[FactionValue::azura] =
            std::make_unique<FactionConfig>(*Settings::azuraName, *Settings::showChampion, championMenu, true);
        mp[FactionValue::clavicusVile] =
            std::make_unique<FactionConfig>(*Settings::clavicusVileName, *Settings::showChampion, championMenu, true);
        mp[FactionValue::hermaeusMora] =
            std::make_unique<FactionConfig>(*Settings::hermaeusMoraName, *Settings::showChampion, championMenu, true);
        mp[FactionValue::hircine] =
            std::make_unique<FactionConfig>(*Settings::hircineName, *Settings::showChampion, championMenu, true);
        mp[FactionValue::malacath] =
            std::make_unique<FactionConfig>(*Settings::malacathName, *Settings::showChampion, championMenu, true);
        mp[FactionValue::mehrunesDagon] =
            std::make_unique<FactionConfig>(*Settings::mehrunesDagonName, *Settings::showChampion, championMenu, true);
        mp[FactionValue::mephala] =
            std::make_unique<FactionConfig>(*Settings::mephalaName, *Settings::showChampion, championMenu, true);
        mp[FactionValue::meridia] =
            std::make_unique<FactionConfig>(*Settings::meridiaName, *Settings::showChampion, championMenu, true);
        mp[FactionValue::molagBal] =
            std::make_unique<FactionConfig>(*Settings::molagBalName, *Settings::showChampion, championMenu, true);
        mp[FactionValue::namira] =
            std::make_unique<FactionConfig>(*Settings::namiraName, *Settings::showChampion, championMenu, true);
        mp[FactionValue::nocturnal] =
            std::make_unique<FactionConfig>(*Settings::nocturnalName, *Settings::showChampion, championMenu, true);
        mp[FactionValue::peryite] =
            std::make_unique<FactionConfig>(*Settings::peryiteName, *Settings::showChampion, championMenu, true);
        mp[FactionValue::sanguine] =
            std::make_unique<FactionConfig>(*Settings::sanguineName, *Settings::showChampion, championMenu, true);
        mp[FactionValue::sheogorath] =
            std::make_unique<FactionConfig>(*Settings::sheogorathName, *Settings::showChampion, championMenu, true);
        mp[FactionValue::vaermina] =
            std::make_unique<FactionConfig>(*Settings::vaerminaName, *Settings::showChampion, championMenu, true);

        return mp;
    }

    FactionSetting() = default;
    FactionSetting(const FactionSetting&) = default;
    FactionSetting(FactionSetting&&) = delete;

    ~FactionSetting() = default;

    FactionSetting& operator=(const FactionSetting&) = default;
    FactionSetting& operator=(FactionSetting&&) = delete;
};
