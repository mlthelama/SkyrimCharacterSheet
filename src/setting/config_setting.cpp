#include "config_setting.h"
#include "util/file.h"
#include "util/form.h"
#include "util/type_util.h"

namespace setting {
    config_setting* config_setting::get_singleton() {
        static config_setting singleton;
        return std::addressof(singleton);
    }

    void config_setting::load_menu_setting_file() {
        logger::trace("loading menu setting file"sv);
        auto file = R"(Data\SKSE\Plugins\SkyrimCharacterSheet\SkyrimCharacterSheet_Menu.json)";
        std::ifstream menu_setting_file(file);
        if (!menu_setting_file) {
            logger::warn("file {} not found"sv, file);
            return;
        }

        if (!this->data_) {
            this->data_ = new config_setting_data();
        }
        config_setting_data* data = this->data_;

        std::map<menu_data::menu_type, menu_data*> menu_data_map;

        logger::info("loading menu setting from file {}"sv, file);

        nlohmann::json json_setting;
        menu_setting_file >> json_setting;

        if (json_setting.at("menu").is_array()) {
            auto& json_menu = json_setting.at("menu");
            for (auto& menu_element : json_menu) {
                auto* menu_data = new setting_data::menu_data();

                auto& key = menu_element.at("key");
                if (key.is_string()) {
                    auto menu = magic_enum::enum_cast<menu_data::menu_type>(std::string{ key });
                    if (menu.has_value()) {
                        menu_data->menu = menu.value();
                    } else {
                        logger::warn("could not get enum for name {}"sv, to_string(key));
                    }
                }

                auto& name = menu_element.at("name");
                if (name.is_string()) {
                    menu_data->menu_name = name;
                }

                auto& columns_json = menu_element["columns"];
                if (columns_json.is_array()) {
                    std::vector<menu_data::menu_column*> column_data_list;
                    for (auto& column : columns_json) {
                        auto* column_data = new menu_data::menu_column();

                        auto& column_key = column.at("key");
                        if (menu_data->menu == menu_data::menu_type::stats) {
                            auto stat_column =
                                magic_enum::enum_cast<menu_data::stats_column_type>(std::string{ column_key });
                            if (stat_column.has_value()) {
                                column_data->stat_column = stat_column.value();
                            }
                        }
                        if (menu_data->menu == menu_data::menu_type::faction) {
                            auto faction_column =
                                magic_enum::enum_cast<menu_data::faction_column_type>(std::string{ column_key });
                            if (faction_column.has_value()) {
                                column_data->faction_column = faction_column.value();
                            }
                        }
                        if (menu_data->menu == menu_data::menu_type::stats_inventory) {
                            auto stat_inventory_column = magic_enum::enum_cast<menu_data::stats_inventory_column_type>(
                                std::string{ column_key });
                            if (stat_inventory_column.has_value()) {
                                column_data->stat_inventory_column = stat_inventory_column.value();
                            }
                        }

                        auto& column_name = column.at("name");
                        if (column_name.is_string()) {
                            column_data->column_name = column_name;
                        }

                        column_data_list.push_back(column_data);
                    }
                    menu_data->columns = column_data_list;
                }

                //better for access, if not set let it fail
                menu_data_map[menu_data->menu] = menu_data;

                logger::trace("menu name {}, name {}, columns {}"sv,
                    magic_enum::enum_name(menu_data->menu),
                    menu_data->menu_name,
                    menu_data->columns.size());
            }
        }
        data->menu_data_map = menu_data_map;

        logger::info("done loading menu setting file, loaded {}"sv, data->menu_data_map.size());
    }

    void config_setting::load_all_faction_setting_files() {
        logger::trace("loading all faction setting files"sv);
        auto base_name = "SkyrimCharacterSheet_Faction";

        auto files = util::file::search_for_config_files(base_name, ".json");
        logger::info("got {} faction files to load"sv, files.size());

        if (files.empty()) {
            logger::warn("no files found to load");
            return;
        }

        if (!this->data_) {
            this->data_ = new config_setting_data();
        }
        config_setting_data* data = this->data_;

        std::map<RE::FormID, faction_data*> faction_data_map;
        std::vector<faction_data*> special_faction_data_list;
        for (auto& file : files) {
            load_faction_setting_file(faction_data_map, special_faction_data_list, file);
        }

        data->faction_data_map = faction_data_map;
        data->special_faction_data_list = special_faction_data_list;
        logger::info("loaded normal {}, special {} faction setting"sv,
            data->faction_data_map.size(),
            data->special_faction_data_list.size());
    }

    void config_setting::load_all_champion_setting_files() {
        logger::trace("loading all champion setting files"sv);
        auto base_name = "SkyrimCharacterSheet_Champion";

        auto files = util::file::search_for_config_files(base_name, ".json");
        logger::info("got {} champion files to load"sv, files.size());

        if (files.empty()) {
            logger::warn("no files found to load");
            return;
        }

        if (!this->data_) {
            this->data_ = new config_setting_data();
        }
        config_setting_data* data = this->data_;

        std::vector<champion_data*> champion_data_list;
        for (auto& file : files) {
            load_champion_setting_file(champion_data_list, file);
        }

        data->champion_data_list = champion_data_list;
        logger::info("loaded {} champion setting"sv, data->champion_data_list.size());
    }

    void config_setting::load_all_thane_setting_files() {
        logger::trace("loading all thane setting files"sv);
        auto base_name = "SkyrimCharacterSheet_Thane";

        auto files = util::file::search_for_config_files(base_name, ".json");
        logger::info("got {} thane files to load"sv, files.size());

        if (files.empty()) {
            logger::warn("no files found to load");
            return;
        }

        if (!this->data_) {
            this->data_ = new config_setting_data();
        }
        config_setting_data* data = this->data_;

        std::vector<thane_data*> thane_data_list;
        for (auto& file : files) {
            load_thane_setting_file(thane_data_list, file);
        }

        data->thane_data_list = thane_data_list;
        logger::info("loaded {} thane setting"sv, data->thane_data_list.size());
    }

    void config_setting::load_all_player_setting_files() {
        logger::trace("loading all player setting files"sv);
        auto base_name = "SkyrimCharacterSheet_Player";

        auto files = util::file::search_for_config_files(base_name, ".json");
        logger::info("got {} player files to load"sv, files.size());

        if (files.empty()) {
            logger::warn("no files found to load");
            return;
        }

        if (!this->data_) {
            this->data_ = new config_setting_data();
        }
        config_setting_data* data = this->data_;

        std::vector<player_data*> player_data_list;
        for (auto& file : files) {
            load_player_setting_file(player_data_list, file);
        }

        data->player_data_list = player_data_list;
        logger::info("loaded {} player setting"sv, data->player_data_list.size());
    }

    setting_data::menu_data::menu_type config_setting::get_next_menu_type(setting_data::menu_data::menu_type a_menu) {
        auto* next_menu = get_next_menu(a_menu);
        if (next_menu) {
            return next_menu->menu;
        }
        return menu_data::menu_type::stats;
    }

    setting_data::menu_data::menu_type config_setting::get_previous_menu_type(
        setting_data::menu_data::menu_type a_menu) {
        auto* previous_menu = get_previous_menu(a_menu);
        if (previous_menu) {
            return previous_menu->menu;
        }
        return menu_data::menu_type::stats;
    }

    std::string config_setting::get_next_menu_name(setting_data::menu_data::menu_type a_menu) {
        auto* next_menu = get_next_menu(a_menu);
        if (next_menu) {
            return next_menu->menu_name;
        }
        return {};
    }

    std::string config_setting::get_previous_menu_name(setting_data::menu_data::menu_type a_menu) {
        auto* previous_menu = get_previous_menu(a_menu);
        if (previous_menu) {
            return previous_menu->menu_name;
        }
        return {};
    }

    std::map<RE::FormID, setting_data::faction_data*> config_setting::get_faction_data() {
        if (const config_setting_data* data = this->data_; data && !data->faction_data_map.empty()) {
            return data->faction_data_map;
        }
        return {};
    }

    std::vector<setting_data::faction_data*> config_setting::get_special_faction_data() {
        if (const config_setting_data* data = this->data_; data && !data->special_faction_data_list.empty()) {
            return data->special_faction_data_list;
        }
        return {};
    }

    std::vector<setting_data::champion_data*> config_setting::get_champion_data() {
        if (const config_setting_data* data = this->data_; data && !data->champion_data_list.empty()) {
            return data->champion_data_list;
        }
        return {};
    }

    std::vector<setting_data::thane_data*> config_setting::get_thane_data() {
        if (const config_setting_data* data = this->data_; data && !data->thane_data_list.empty()) {
            return data->thane_data_list;
        }
        return {};
    }

    std::vector<setting_data::player_data*> config_setting::get_player_data() {
        if (const config_setting_data* data = this->data_; data && !data->player_data_list.empty()) {
            return data->player_data_list;
        }
        return {};
    }

    config_setting::menu_data* config_setting::get_menu_data(setting_data::menu_data::menu_type a_menu) {
        if (const config_setting_data* data = this->data_;
            data && !data->menu_data_map.empty() && data->menu_data_map.contains(a_menu)) {
            return data->menu_data_map.at(a_menu);
        }
        return {};
    }

    void config_setting::load_faction_setting_file(std::map<RE::FormID, faction_data*>& a_data,
        std::vector<faction_data*>& a_data_list,
        const std::string& file) {
        std::ifstream faction_setting_file(file.c_str());
        if (!faction_setting_file) {
            logger::warn("file not found {}"sv, file.c_str());
            return;
        }

        logger::info("loading faction setting from file {}"sv, file.c_str());

        nlohmann::json json_setting;
        faction_setting_file >> json_setting;

        //TODO add to json the ini information of where the value can be found (section, value)
        if (json_setting.at("faction").is_array()) {
            auto& json_faction = json_setting.at("faction");
            for (auto& faction_element : json_faction) {
                auto* faction_data = new setting_data::faction_data();

                auto& key = faction_element.at("key");
                if (key.is_string()) {
                    faction_data->key = magic_enum::enum_cast<faction_data::faction>(std::string{ key })
                                            .value_or(faction_data::faction::custom);
                }

                auto& name = faction_element.at("name");
                if (name.is_string()) {
                    faction_data->name = name;
                }

                auto& mod = faction_element["mod"];
                auto& form_faction = faction_element["form_faction"];
                if (mod.is_string() && form_faction.is_string()) {
                    logger::trace("mod {}, form_faction {}"sv, mod, form_faction);
                    auto* form = util::form::get_tes_form_from_mod_and_form(mod, form_faction);
                    if (form) {
                        faction_data->form = form;
                    }
                } else {
                    logger::warn("mod valid {}, form valid {}"sv, mod.is_string(), form_faction.is_string());
                }

                auto& json_rank = faction_element["rank"];
                if (json_rank.is_array()) {
                    std::vector<setting_data::faction_rank_data*> faction_rank_data_list;
                    for (auto& rank_element : json_rank) {
                        auto* faction_rank_data = new setting_data::faction_rank_data();
                        auto& rank_key = rank_element.at("key");
                        if (rank_key.is_string()) {
                            faction_rank_data->key = rank_key;
                        }

                        auto& rank_name = rank_element.at("name");
                        if (rank_name.is_string()) {
                            faction_rank_data->name = rank_name;
                        }

                        auto& rank_quest = rank_element["quest"];
                        if (rank_quest.is_array()) {
                            std::vector<setting_data::faction_rank_quest_data*> faction_rank_quest_data_list;
                            for (auto& rank_quest_element : rank_quest) {
                                auto* faction_rank_quest_data = new setting_data::faction_rank_quest_data();
                                auto& rank_mod = rank_quest_element.at("mod");
                                auto& rank_quest_form = rank_quest_element.at("form_quest");
                                if (rank_mod.is_string() && rank_quest_form.is_string()) {
                                    logger::trace("rank mod {}, rank form_faction {}"sv, rank_mod, rank_quest_form);
                                    auto* form = util::form::get_tes_form_from_mod_and_form(rank_mod, rank_quest_form);
                                    if (form) {
                                        faction_rank_quest_data->form = form;
                                    }
                                } else {
                                    logger::warn("mod valid {}, form valid {}"sv,
                                        rank_mod.is_string(),
                                        rank_quest_form.is_string());
                                }

                                auto& rank_stages = rank_quest_element.at("stages");
                                if (rank_stages.is_array()) {
                                    std::vector<uint16_t> stages;
                                    for (auto& stage : rank_stages) {
                                        stages.push_back(static_cast<uint16_t>(stage));
                                    }
                                    faction_rank_quest_data->stages = stages;
                                }
                                faction_rank_quest_data_list.push_back(faction_rank_quest_data);
                                logger::trace("quest form {}, stages {}"sv,
                                    faction_rank_quest_data->form ?
                                        util::type_util::int_to_hex(faction_rank_quest_data->form->formID) :
                                        "",
                                    faction_rank_quest_data->stages.size());
                            }
                            faction_rank_data->quests = faction_rank_quest_data_list;
                            logger::trace("rank name {}, rank name {}, quests {} "sv,
                                faction_rank_data->key,
                                faction_rank_data->name,
                                faction_rank_data->quests.size());
                        }
                        faction_rank_data_list.push_back(faction_rank_data);
                    }
                    faction_data->ranks = faction_rank_data_list;
                }
                if (faction_data->form) {
                    a_data[faction_data->form->formID] = faction_data;
                } else {
                    a_data_list.push_back(faction_data);
                }

                faction_data->log();
            }
        }

        logger::info("done loading faction setting, loaded normal {}, special {} factions so far."sv,
            a_data.size(),
            a_data_list.size());
    }

    config_setting::menu_data* config_setting::get_next_menu(setting_data::menu_data::menu_type a_menu) {
        if (const config_setting_data* data = this->data_;
            data && !data->menu_data_map.empty() && data->menu_data_map.contains(a_menu)) {
            uint32_t next;
            auto current = static_cast<uint32_t>(a_menu);
            if (current < (static_cast<uint32_t>(menu_data::menu_type::total) - 1)) {
                next = current + 1;
            } else {
                next = static_cast<uint32_t>(menu_data::menu_type::stats);
            }

            auto next_menu = static_cast<menu_data::menu_type>(next);
            if (data->menu_data_map.contains(next_menu)) {
                return data->menu_data_map.at(next_menu);
            }
        }
        return nullptr;
    }

    config_setting::menu_data* config_setting::get_previous_menu(setting_data::menu_data::menu_type a_menu) {
        if (const config_setting_data* data = this->data_;
            data && !data->menu_data_map.empty() && data->menu_data_map.contains(a_menu)) {
            uint32_t previous;
            auto current = static_cast<uint32_t>(a_menu);
            if (current > (static_cast<uint32_t>(menu_data::menu_type::stats))) {
                previous = current - 1;
            } else {
                previous = static_cast<uint32_t>(menu_data::menu_type::total) - 1;
            }

            auto previous_menu = static_cast<menu_data::menu_type>(previous);
            if (data->menu_data_map.contains(previous_menu)) {
                return data->menu_data_map.at(previous_menu);
            }
        }
        return nullptr;
    }

    void config_setting::load_champion_setting_file(std::vector<champion_data*>& a_data_list, const std::string& file) {
        std::ifstream champion_setting_file(file.c_str());
        if (!champion_setting_file) {
            logger::warn("file not found {}"sv, file.c_str());
            return;
        }

        logger::info("loading champion setting from file {}"sv, file.c_str());

        nlohmann::json json_setting;
        champion_setting_file >> json_setting;

        if (json_setting.at("champion").is_array()) {
            auto& json_champion = json_setting.at("champion");
            for (auto& champion_element : json_champion) {
                auto* champion_data = new setting_data::champion_data();

                auto& key = champion_element.at("key");
                if (key.is_string()) {
                    champion_data->key = magic_enum::enum_cast<champion_data::champion>(std::string{ key })
                                             .value_or(champion_data::champion::custom);
                }

                auto& name = champion_element.at("name");
                if (name.is_string()) {
                    champion_data->name = name;
                }

                auto& mod = champion_element.at("mod");
                auto& quest = champion_element.at("quest_form");
                if (mod.is_string() && quest.is_string()) {
                    logger::trace("mod {}, form {}"sv, mod, quest);
                    auto* form = util::form::get_tes_form_from_mod_and_form(mod, quest);
                    if (form) {
                        champion_data->form = form;
                    }
                } else {
                    logger::warn("mod valid {}, form valid {}"sv, mod.is_string(), quest.is_string());
                }

                auto& quest_stage_favor = champion_element.at("quest_stage_favor");
                if (quest_stage_favor.is_array()) {
                    std::vector<uint16_t> stages;
                    for (auto& stage : quest_stage_favor) {
                        stages.push_back(static_cast<uint16_t>(stage));
                    }
                    champion_data->stages = stages;
                }

                auto& quest_stage_alternate = champion_element["quest_stage_alternate"];
                if (quest_stage_alternate.is_array()) {
                    std::vector<uint16_t> stages;
                    for (auto& stage : quest_stage_alternate) {
                        stages.push_back(static_cast<uint16_t>(stage));
                    }
                    champion_data->alternate_stages = stages;
                }

                champion_data->log();
                a_data_list.push_back(champion_data);
            }
        }
        logger::info("done loading champion setting, loaded {} champions so far."sv, a_data_list.size());
    }

    void config_setting::load_thane_setting_file(std::vector<thane_data*>& a_data_list, const std::string& file) {
        std::ifstream thane_setting_file(file.c_str());
        if (!thane_setting_file) {
            logger::warn("file not found {}"sv, file.c_str());
            return;
        }

        logger::info("loading thane setting from file {}"sv, file.c_str());

        nlohmann::json json_setting;
        thane_setting_file >> json_setting;

        if (json_setting.at("thane").is_array()) {
            auto& json_thane = json_setting.at("thane");
            for (auto& thane_element : json_thane) {
                auto* thane_data = new setting_data::thane_data();

                auto& key = thane_element.at("key");
                if (key.is_string()) {
                    thane_data->key =
                        magic_enum::enum_cast<thane_data::hold>(std::string{ key }).value_or(thane_data::hold::custom);
                }

                auto& name = thane_element.at("name");
                if (name.is_string()) {
                    thane_data->name = name;
                }

                auto& thane_name = thane_element.at("thane_name");
                if (name.is_string()) {
                    thane_data->thane_name = thane_name;
                }

                auto& mod = thane_element.at("quest_mod");
                auto& quest = thane_element.at("quest_form");
                if (mod.is_string() && quest.is_string()) {
                    logger::trace("mod {}, form {}"sv, mod, quest);
                    auto* form = util::form::get_tes_form_from_mod_and_form(mod, quest);
                    if (form) {
                        thane_data->quest_form = form;
                    }
                } else {
                    logger::warn("mod valid {}, form valid {}"sv, mod.is_string(), quest.is_string());
                }

                auto& quest_stage = thane_element.at("quest_stage");
                if (quest_stage.is_array()) {
                    std::vector<uint16_t> stages;
                    for (auto& stage : quest_stage) {
                        stages.push_back(static_cast<uint16_t>(stage));
                    }
                    thane_data->quest_stages = stages;
                }

                auto& mod_crime_faction = thane_element.at("crime_faction_mod");
                auto& form_crime_faction = thane_element.at("crime_faction_form");
                if (mod_crime_faction.is_string() && form_crime_faction.is_string()) {
                    logger::trace("mod {}, quest_form {}"sv, mod_crime_faction, form_crime_faction);
                    auto* form = util::form::get_tes_form_from_mod_and_form(mod_crime_faction, form_crime_faction);
                    if (form) {
                        thane_data->crime_faction = form;
                    }
                } else {
                    logger::warn("mod valid {}, form valid {}"sv,
                        mod_crime_faction.is_string(),
                        form_crime_faction.is_string());
                }

                auto& pre_quest = thane_element["pre_quest"];
                if (pre_quest.is_array()) {
                    std::vector<setting_data::thane_pre_quest_data*> thane_pre_quest_data_list;
                    for (auto& pre_quest_element : pre_quest) {
                        auto* thane_pre_quest_data = new setting_data::thane_pre_quest_data();

                        auto& pre_quest_mod = pre_quest_element.at("mod");
                        auto& pre_quest_form = pre_quest_element.at("form_quest");
                        if (pre_quest_mod.is_string() && pre_quest_form.is_string()) {
                            logger::trace("mod {}, quest_form {}"sv, pre_quest_mod, pre_quest_form);
                            auto* form = util::form::get_tes_form_from_mod_and_form(pre_quest_mod, pre_quest_form);
                            if (form) {
                                thane_pre_quest_data->quest_form = form;
                            }
                        } else {
                            logger::warn("mod valid {}, form valid {}"sv,
                                pre_quest_mod.is_string(),
                                pre_quest_form.is_string());
                        }

                        auto& pre_quest_stage = pre_quest_element.at("stages");
                        if (pre_quest_stage.is_array()) {
                            std::vector<uint16_t> stages;
                            for (auto& stage : pre_quest_stage) {
                                stages.push_back(static_cast<uint16_t>(stage));
                            }
                            thane_pre_quest_data->quest_stages = stages;
                        }

                        logger::trace("pre quest form {}, stage(s) {}"sv,
                            thane_pre_quest_data->quest_form ?
                                util::type_util::int_to_hex(thane_pre_quest_data->quest_form->formID) :
                                "",
                            thane_pre_quest_data->quest_stages.size());
                        thane_pre_quest_data_list.push_back(thane_pre_quest_data);
                    }
                    thane_data->pre_quests = thane_pre_quest_data_list;
                }

                auto& bypass_quest = thane_element["bypass_quest"];
                if (bypass_quest.is_object()) {
                    auto* bypass_quest_data = new setting_data::thane_bypass_quest_data();

                    auto& bypass_quest_mod = bypass_quest.at("bypass_quest_mod");
                    auto& bypass_quest_form = bypass_quest.at("bypass_quest_form");
                    if (bypass_quest_mod.is_string() && bypass_quest_form.is_string()) {
                        logger::trace("mod {}, quest_form {}"sv, bypass_quest_mod, bypass_quest_form);
                        auto* form = util::form::get_tes_form_from_mod_and_form(bypass_quest_mod, bypass_quest_form);
                        if (form) {
                            bypass_quest_data->quest_form = form;
                        }
                    } else {
                        logger::warn("mod valid {}, form valid {}"sv,
                            bypass_quest_mod.is_string(),
                            bypass_quest_form.is_string());
                    }

                    auto& bypass_quest_stage = bypass_quest.at("bypass_quest_stages");
                    if (bypass_quest_stage.is_array()) {
                        std::vector<uint16_t> stages;
                        for (auto& stage : bypass_quest_stage) {
                            stages.push_back(static_cast<uint16_t>(stage));
                        }
                        bypass_quest_data->quest_stages = stages;
                    }

                    logger::trace("pre quest form {}, stage(s) {}"sv,
                        bypass_quest_data->quest_form ?
                            util::type_util::int_to_hex(bypass_quest_data->quest_form->formID) :
                            "",
                        bypass_quest_data->quest_stages.size());
                    thane_data->bypass_quest = bypass_quest_data;
                }

                thane_data->log();
                a_data_list.push_back(thane_data);
            }
        }
        logger::info("done loading thane setting, loaded {} thanes so far."sv, a_data_list.size());
    }

    void config_setting::load_player_setting_file(std::vector<player_data*>& a_data_list, const std::string& file) {
        std::ifstream player_setting_file(file.c_str());
        if (!player_setting_file) {
            logger::warn("file not found {}"sv, file.c_str());
            return;
        }

        logger::info("loading player setting from file {}"sv, file.c_str());

        nlohmann::json json_setting;
        player_setting_file >> json_setting;

        if (json_setting.at("player").is_array()) {
            auto& json_player = json_setting.at("player");
            for (auto& player_element : json_player) {
                auto* player_data = new setting_data::player_data();

                auto& key = player_element.at("key");
                if (key.is_string()) {
                    player_data->key = magic_enum::enum_cast<player_data::stat>(std::string{ key })
                                           .value_or(player_data::stat::custom);
                }

                auto& display_name = player_element.at("display_name");
                if (display_name.is_string()) {
                    player_data->display_name = display_name;
                }

                auto& value_handling = player_element["actor_value_handling"];
                if (value_handling.is_string()) {
                    player_data->actor_value_handling =
                        magic_enum::enum_cast<player_data::value_handling>(std::string{ value_handling })
                            .value_or(player_data::value_handling::single);
                }

                auto& actor_value = player_element["actor_value"];
                if ((player_data->actor_value_handling == player_data::value_handling::single ||
                        player_data->actor_value_handling == player_data::value_handling::single_with_permanent ||
                        player_data->actor_value_handling == player_data::value_handling::single_with_base) &&
                    !actor_value.is_null()) {
                    if (actor_value.is_number()) {
                        auto* av_data = new setting_data::actor_value_data();
                        av_data->setting_data::single_actor_value::actor_value =
                            static_cast<RE::ActorValue>(actor_value);
                        player_data->actor_value = *av_data;
                    } else {
                        logger::warn("name {}, actor value handling {}, actor_value json type mismatch {}"sv,
                            magic_enum::enum_name(player_data->key),
                            magic_enum::enum_name(player_data->actor_value_handling),
                            actor_value.type_name());
                    }
                } else if (!actor_value.is_null()) {
                    if (actor_value.is_array()) {
                        auto* av_data = new setting_data::actor_value_data();
                        std::vector<RE::ActorValue> actor_value_list;
                        for (auto& actor_value_element : actor_value) {
                            if (actor_value_element.is_number()) {
                                actor_value_list.push_back(static_cast<RE::ActorValue>(actor_value_element));
                            }
                        }
                        av_data->actor_value_list = actor_value_list;
                        player_data->actor_value = *av_data;
                    } else {
                        logger::warn("name {}, actor value handling {}, actor_value json type mismatch {}"sv,
                            magic_enum::enum_name(player_data->key),
                            magic_enum::enum_name(player_data->actor_value_handling),
                            actor_value.type_name());
                    }
                }

                auto& actor_value_source = player_element["actor_value_source"];
                if (actor_value_source.is_string()) {
                    player_data->actor_value_source = magic_enum::enum_cast<player_data::actor_value_source_handling>(
                        std::string{ actor_value_source })
                                                          .value_or(player_data::actor_value_source_handling::standard);
                } else {
                    player_data->actor_value_source = player_data::actor_value_source_handling::standard;
                }

                auto& ending = player_element["ending"];
                if (ending.is_string()) {
                    player_data->ending = ending;
                }

                auto& result_handling = player_element["result_handling"];
                if (result_handling.is_string()) {
                    player_data->result_handling =
                        magic_enum::enum_cast<player_data::result_value_handling>(std::string{ result_handling })
                            .value_or(player_data::result_value_handling::none);
                }

                auto& result_handling_value = player_element["result_handling_value"];
                if (result_handling_value.is_number()) {
                    player_data->result_value = result_handling_value;
                }

                auto& max_handling = player_element["max_handling"];
                if (max_handling.is_string()) {
                    player_data->max = magic_enum::enum_cast<player_data::max_handling>(std::string{ max_handling })
                                           .value_or(player_data::max_handling::none);
                }

                auto& icon_string = player_element["icon_string"];
                if (icon_string.is_string()) {
                    player_data->icon_string = icon_string;
                }

                auto& overwrite_mod = player_element["overwrite_mod"];
                if (overwrite_mod.is_string()) {
                    player_data->overwrite_mod =
                        magic_enum::enum_cast<player_data::mod_values>(std::string{ overwrite_mod })
                            .value_or(player_data::mod_values::none);
                }

                auto& overwrite = player_element["overwrite"];
                if (player_data->overwrite_mod != player_data::mod_values::none && overwrite.is_object()) {
                    auto* overwrite_data = new setting_data::overwrite_mod_data();

                    auto& overwrite_display_name = overwrite["display_name"];
                    if (overwrite_display_name.is_string()) {
                        overwrite_data->display_name = overwrite_display_name;
                    }
                    auto& overwrite_icon_string = overwrite["icon_string"];
                    if (overwrite_icon_string.is_string()) {
                        overwrite_data->icon_string = overwrite_icon_string;
                    }
                    player_data->mod_data = overwrite_data;
                }

                auto& stats_column = player_element.at("stats_column");
                if (stats_column.is_string()) {
                    player_data->stats_column =
                        magic_enum::enum_cast<menu_data::stats_column_type>(std::string{ stats_column })
                            .value_or(menu_data::stats_column_type::none);
                }
                auto& stats_inventory_column = player_element.at("stats_inventory_column");
                if (stats_inventory_column.is_string()) {
                    player_data->stats_inventory_column = magic_enum::enum_cast<menu_data::stats_inventory_column_type>(
                        std::string{ stats_inventory_column })
                                                              .value_or(menu_data::stats_inventory_column_type::none);
                }

                auto& hide_value = player_element["hide_value_when_zero"];
                if (hide_value.is_boolean()) {
                    player_data->hide_value_when_zero = hide_value;
                }

                player_data->log();
                a_data_list.push_back(player_data);
            }
        }

        logger::info("done loading player setting, loaded {} player so far."sv, a_data_list.size());
    }
}
