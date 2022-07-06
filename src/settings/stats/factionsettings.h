#pragma once

class faction_config {
    using faction_menu_value = menu_util::faction_menu_value;

public:
    faction_config(std::string a_display_name, const faction_menu_value a_menu)
        : display_name_(std::move(a_display_name)), menu_(a_menu), display_is_value_(false) {}

    faction_config(std::string a_display_name, const faction_menu_value a_menu, const bool a_display_is_value)
        : display_name_(std::move(a_display_name)), menu_(a_menu), display_is_value_(a_display_is_value) {}

    std::string get_display_name() { return display_name_; }

    [[nodiscard]] faction_menu_value get_menu() const { return menu_; }

    [[nodiscard]] bool get_display_is_value() const { return display_is_value_; }

    std::string get_display(const std::string& a_value) {
        if (!a_value.empty()) {
            logger::trace("display {} got value {}, building text ..."sv, display_name_, a_value);
            return menu_util::build_display_string(a_value, display_name_, "", display_is_value_);
        }
        return "";
    }

    void log_stat_config(FactionValue a_stats_value) {
        logger::trace("name {}, displayname ({}), menu {}, displayIsValue {}"sv,
            a_stats_value,
            display_name_,
            menu_,
            display_is_value_);
    }

    faction_config() = delete;
    faction_config(const faction_config&) = default;
    faction_config(faction_config&&) = delete;

    ~faction_config() = default;

    faction_config& operator=(const faction_config&) = default;
    faction_config& operator=(faction_config&&) = delete;

private:
    std::string display_name_;
    faction_menu_value menu_;
    bool display_is_value_ = false;
};

class faction_setting {
    using faction_map = std::map<FactionValue, std::unique_ptr<faction_config>>;

public:
    static faction_setting* get_singleton() {
        static faction_setting singleton;
        return std::addressof(singleton);
    }

    faction_map load() const {
        auto faction_menu = menu_util::get_faction_menu(*settings::factionMenu);
        auto thane_menu = menu_util::get_faction_menu(*settings::thaneMenu);
        auto champion_menu = menu_util::get_faction_menu(*settings::championMenu);

        faction_map mp;
        mp[FactionValue::darkbrotherhood] =
            std::make_unique<faction_config>(*settings::darkbrotherHoodString, faction_menu);
        mp[FactionValue::thiefs_guild] = std::make_unique<faction_config>(*settings::thiefsGuildString, faction_menu);
        mp[FactionValue::orc_friend] = std::make_unique<faction_config>(*settings::orcFriendString, faction_menu);
        mp[FactionValue::college_of_winterhold] =
            std::make_unique<faction_config>(*settings::collegeOfWinterholdString, faction_menu);
        mp[FactionValue::companions] = std::make_unique<faction_config>(*settings::companionsString, faction_menu);
        mp[FactionValue::imperial_legion] =
            std::make_unique<faction_config>(*settings::imperialLegionString, faction_menu);
        mp[FactionValue::stormcloaks] = std::make_unique<faction_config>(*settings::stormcloaksString, faction_menu);
        mp[FactionValue::greybeard] = std::make_unique<faction_config>(*settings::greybeardString, faction_menu);
        mp[FactionValue::bard] = std::make_unique<faction_config>(*settings::bardString, faction_menu);
        mp[FactionValue::volkihar_vampire_clan] =
            std::make_unique<faction_config>(*settings::volkiharVampireClanString, faction_menu);
        mp[FactionValue::dawnguard] = std::make_unique<faction_config>(*settings::dawnguardString, faction_menu);
        mp[FactionValue::house_telvanni] =
            std::make_unique<faction_config>(*settings::houseTelvanniString, faction_menu);

        mp[FactionValue::thane_of_eastmarch] =
            std::make_unique<faction_config>(*settings::thaneOfEastmarchName, thane_menu, true);
        mp[FactionValue::thane_of_falkreath] =
            std::make_unique<faction_config>(*settings::thaneOfFalkreathName, thane_menu, true);
        mp[FactionValue::thane_of_haafingar] =
            std::make_unique<faction_config>(*settings::thaneOfHaafingarName, thane_menu, true);
        mp[FactionValue::thane_of_hjaalmarch] =
            std::make_unique<faction_config>(*settings::thaneOfHjaalmarchName, thane_menu, true);
        mp[FactionValue::thane_of_the_pale] =
            std::make_unique<faction_config>(*settings::thaneOfThePaleName, thane_menu, true);
        mp[FactionValue::thane_of_the_reach] =
            std::make_unique<faction_config>(*settings::thaneOfTheReachName, thane_menu, true);
        mp[FactionValue::thane_of_the_rift] =
            std::make_unique<faction_config>(*settings::thaneOfTheRiftName, thane_menu, true);
        mp[FactionValue::thane_of_whiterun] =
            std::make_unique<faction_config>(*settings::thaneOfWhiterunName, thane_menu, true);
        mp[FactionValue::thane_of_winterhold] =
            std::make_unique<faction_config>(*settings::thaneOfWinterholdName, thane_menu, true);

        mp[FactionValue::azura] = std::make_unique<faction_config>(*settings::azuraName, champion_menu, true);
        mp[FactionValue::clavicus_vile] =
            std::make_unique<faction_config>(*settings::clavicusVileName, champion_menu, true);
        mp[FactionValue::hermaeus_mora] =
            std::make_unique<faction_config>(*settings::hermaeusMoraName, champion_menu, true);
        mp[FactionValue::hircine] = std::make_unique<faction_config>(*settings::hircineName, champion_menu, true);
        mp[FactionValue::malacath] = std::make_unique<faction_config>(*settings::malacathName, champion_menu, true);
        mp[FactionValue::mehrunes_dagon] =
            std::make_unique<faction_config>(*settings::mehrunesDagonName, champion_menu, true);
        mp[FactionValue::mephala] = std::make_unique<faction_config>(*settings::mephalaName, champion_menu, true);
        mp[FactionValue::meridia] = std::make_unique<faction_config>(*settings::meridiaName, champion_menu, true);
        mp[FactionValue::molagBal] = std::make_unique<faction_config>(*settings::molagBalName, champion_menu, true);
        mp[FactionValue::namira] = std::make_unique<faction_config>(*settings::namiraName, champion_menu, true);
        mp[FactionValue::nocturnal] = std::make_unique<faction_config>(*settings::nocturnalName, champion_menu, true);
        mp[FactionValue::peryite] = std::make_unique<faction_config>(*settings::peryiteName, champion_menu, true);
        mp[FactionValue::sanguine] = std::make_unique<faction_config>(*settings::sanguineName, champion_menu, true);
        mp[FactionValue::sheogorath] = std::make_unique<faction_config>(*settings::sheogorathName, champion_menu, true);
        mp[FactionValue::vaermina] = std::make_unique<faction_config>(*settings::vaerminaName, champion_menu, true);

        return mp;
    }

    faction_setting() = default;
    faction_setting(const faction_setting&) = default;
    faction_setting(faction_setting&&) = delete;

    ~faction_setting() = default;

    faction_setting& operator=(const faction_setting&) = default;
    faction_setting& operator=(faction_setting&&) = delete;
};
