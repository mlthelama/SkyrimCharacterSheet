#pragma once
#include "setting/data/champion_data.h"
#include "setting/data/faction_data.h"
#include "setting/data/menu_data.h"
#include "setting/data/player_data.h"
#include "setting/data/thane_data.h"

namespace setting {
    class config_setting {
    public:
        using faction_data = setting_data::faction_data;
        using menu_data = setting_data::menu_data;
        using champion_data = setting_data::champion_data;
        using thane_data = setting_data::thane_data;
        using player_data = setting_data::player_data;

        static config_setting* get_singleton();

        void load_menu_setting_file();
        void load_all_faction_setting_files();
        void load_all_champion_setting_files();
        void load_all_thane_setting_files();
        void load_all_player_setting_files();

        menu_data::menu_type get_next_menu_type(menu_data::menu_type a_menu);
        menu_data::menu_type get_previous_menu_type(menu_data::menu_type a_menu);
        std::string get_next_menu_name(menu_data::menu_type a_menu);
        std::string get_previous_menu_name(menu_data::menu_type a_menu);
        std::map<RE::FormID, faction_data*> get_faction_data();
        std::vector<faction_data*> get_special_faction_data();
        std::vector<champion_data*> get_champion_data();
        std::vector<thane_data*> get_thane_data();
        std::vector<player_data*> get_player_data();
        menu_data* get_menu_data(menu_data::menu_type a_menu);

        config_setting(const config_setting&) = delete;
        config_setting(config_setting&&) = delete;

        config_setting& operator=(const config_setting&) const = delete;
        config_setting& operator=(config_setting&&) const = delete;

    private:
        config_setting() : data_(nullptr) {}
        ~config_setting() = default;

        struct config_setting_data {
            std::map<RE::FormID, faction_data*> faction_data_map;
            std::vector<faction_data*> special_faction_data_list;
            std::map<menu_data::menu_type, menu_data*> menu_data_map;
            std::vector<champion_data*> champion_data_list;
            std::vector<thane_data*> thane_data_list;
            std::vector<player_data*> player_data_list;
        };

        config_setting_data* data_;

        static void load_faction_setting_file(std::map<RE::FormID, faction_data*>& a_data,
            std::vector<faction_data*>& a_data_list,
            const std::string& file);

        menu_data* get_next_menu(menu_data::menu_type a_menu);
        menu_data* get_previous_menu(menu_data::menu_type a_menu);

        static void load_champion_setting_file(std::vector<champion_data*>& a_data_list, const std::string& file);
        static void load_thane_setting_file(std::vector<thane_data*>& a_data_list, const std::string& file);
        static void load_player_setting_file(std::vector<player_data*>& a_data_list, const std::string& file);
    };
}
