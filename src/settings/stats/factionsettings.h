#pragma once
#include "utils/menukeys.h"
#include "utils/utils.h"

class faction_config {
    using faction_menu_value = menu_util::faction_menu_value;

public:
    faction_config(const std::string_view a_display_name, const faction_menu_value a_menu)
        : display_name_(a_display_name), menu_(a_menu) {}

    [[nodiscard]] std::string_view get_display_name() const { return display_name_; }

    [[nodiscard]] faction_menu_value get_menu() const { return menu_; }


    void log_stat_config(const faction_value a_stats_value) {
        logger::trace("name {}, displayname {}, menu {}"sv,
            string_util::get_int_from_enum(a_stats_value),
            display_name_,
            string_util::get_int_from_enum(menu_));
    }

    faction_config() = delete;
    faction_config(const faction_config&) = default;
    faction_config(faction_config&&) = delete;

    ~faction_config() = default;

    faction_config& operator=(const faction_config&) = default;
    faction_config& operator=(faction_config&&) = delete;

private:
    std::string_view display_name_;
    faction_menu_value menu_;
};

class faction_setting {
    using faction_map = std::map<faction_value, std::unique_ptr<faction_config>>;

public:
    static faction_setting* get_singleton() {
        static faction_setting singleton;
        return std::addressof(singleton);
    }

    [[nodiscard]] faction_map load() const {
        auto faction_menu = menu_util::get_faction_menu(setting::get_faction_menu());
        auto thane_menu = menu_util::get_faction_menu(setting::get_thane_menu());
        auto champion_menu = menu_util::get_faction_menu(setting::get_champion_menu());

        faction_map mp;
        mp[faction_value::darkbrotherhood] = std::make_unique<faction_config>(menu_keys::darkbrotherhood, faction_menu);
        mp[faction_value::thiefs_guild] = std::make_unique<faction_config>(menu_keys::thiefs_guild, faction_menu);
        mp[faction_value::orc_friend] = std::make_unique<faction_config>(menu_keys::orc_friend, faction_menu);
        mp[faction_value::college_of_winterhold] =
            std::make_unique<faction_config>(menu_keys::college_of_winterhold, faction_menu);
        mp[faction_value::companions] = std::make_unique<faction_config>(menu_keys::companions, faction_menu);
        mp[faction_value::imperial_legion] = std::make_unique<faction_config>(menu_keys::imperial_legion, faction_menu);
        mp[faction_value::stormcloaks] = std::make_unique<faction_config>(menu_keys::stormcloaks, faction_menu);
        mp[faction_value::greybeard] = std::make_unique<faction_config>(menu_keys::greybeard, faction_menu);
        mp[faction_value::bard] = std::make_unique<faction_config>(menu_keys::bard_college, faction_menu);
        mp[faction_value::volkihar_vampire_clan] =
            std::make_unique<faction_config>(menu_keys::volkihar_vampire_clan, faction_menu);
        mp[faction_value::dawnguard] = std::make_unique<faction_config>(menu_keys::dawnguard, faction_menu);
        mp[faction_value::house_telvanni] = std::make_unique<faction_config>(menu_keys::house_telvanni, faction_menu);

        mp[faction_value::windhelm] = std::make_unique<faction_config>(menu_keys::windhelm, thane_menu);
        mp[faction_value::falkreath] = std::make_unique<faction_config>(menu_keys::falkreath, thane_menu);
        mp[faction_value::solitude] = std::make_unique<faction_config>(menu_keys::solitude, thane_menu);
        mp[faction_value::morthal] = std::make_unique<faction_config>(menu_keys::morthal, thane_menu);
        mp[faction_value::dawnstar] = std::make_unique<faction_config>(menu_keys::dawnstar, thane_menu);
        mp[faction_value::markarth] = std::make_unique<faction_config>(menu_keys::markarth, thane_menu);
        mp[faction_value::riften] = std::make_unique<faction_config>(menu_keys::riften, thane_menu);
        mp[faction_value::whiterun] = std::make_unique<faction_config>(menu_keys::whiterun, thane_menu);
        mp[faction_value::winterhold] = std::make_unique<faction_config>(menu_keys::winterhold, thane_menu);

        mp[faction_value::azura] = std::make_unique<faction_config>(menu_keys::azura, champion_menu);
        mp[faction_value::clavicus_vile] = std::make_unique<faction_config>(menu_keys::clavicus_vile, champion_menu);
        mp[faction_value::hermaeus_mora] = std::make_unique<faction_config>(menu_keys::hermaeus_mora, champion_menu);
        mp[faction_value::hircine] = std::make_unique<faction_config>(menu_keys::hircine, champion_menu);
        mp[faction_value::malacath] = std::make_unique<faction_config>(menu_keys::malacath, champion_menu);
        mp[faction_value::mehrunes_dagon] = std::make_unique<faction_config>(menu_keys::mehrunes_dagon, champion_menu);
        mp[faction_value::mephala] = std::make_unique<faction_config>(menu_keys::mephala, champion_menu);
        mp[faction_value::meridia] = std::make_unique<faction_config>(menu_keys::meridia, champion_menu);
        mp[faction_value::molag_bal] = std::make_unique<faction_config>(menu_keys::molag_bal, champion_menu);
        mp[faction_value::namira] = std::make_unique<faction_config>(menu_keys::namira, champion_menu);
        mp[faction_value::nocturnal] = std::make_unique<faction_config>(menu_keys::nocturnal, champion_menu);
        mp[faction_value::peryite] = std::make_unique<faction_config>(menu_keys::peryite, champion_menu);
        mp[faction_value::sanguine] = std::make_unique<faction_config>(menu_keys::sanguine, champion_menu);
        mp[faction_value::sheogorath] = std::make_unique<faction_config>(menu_keys::sheogorath, champion_menu);
        mp[faction_value::vaermina] = std::make_unique<faction_config>(menu_keys::vearmina, champion_menu);

        return mp;
    }

    faction_setting() = default;
    faction_setting(const faction_setting&) = default;
    faction_setting(faction_setting&&) = delete;

    ~faction_setting() = default;

    faction_setting& operator=(const faction_setting&) = default;
    faction_setting& operator=(faction_setting&&) = delete;
};
