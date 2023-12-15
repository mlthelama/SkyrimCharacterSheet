#pragma once
#include "setting/data/menu_data.h"
#include "setting/data/player_data.h"

namespace actor {
    class actor_player_data {
    public:
        setting_data::player_data::stat key;
        std::string icon;
        std::string name;
        std::string value;
        setting_data::menu_data::stats_column_type column;
        setting_data::menu_data::stats_inventory_column_type inventory_column;

        void log(setting_data::menu_data::menu_type a_menu);
    };

    class player {
    public:
        static std::vector<actor_player_data*> get_player_data(RE::PlayerCharacter*& a_player,
            setting_data::menu_data::menu_type a_menu);

    private:
        static void handle_result_handling(setting_data::player_data*& a_player_data_element, float& a_current_result);
        static std::string handle_max_handling(setting_data::player_data*& a_player_data_element,
            float& a_current_result);
        static void handle_damage_resist(RE::PlayerCharacter*& a_player,
            setting_data::player_data*& a_player_data_element,
            actor_player_data*& a_player_data);
        static void handle_ending(setting_data::player_data*& a_player_data_element,
            float& a_current_result,
            actor_player_data*& a_player_data);
        static float get_actor_value(RE::PlayerCharacter*& a_player,
            RE::ActorValue a_actor_value,
            setting_data::player_data::actor_value_source_handling source_handling);
        static void process_single(RE::PlayerCharacter*& a_player,
            setting_data::player_data*& a_player_data_element,
            actor_player_data*& a_player_data);
        static void process_multiply(RE::PlayerCharacter*& a_player,
            setting_data::player_data*& a_player_data_element,
            actor_player_data*& a_player_data);
        static void process_single_with_additional(RE::PlayerCharacter*& a_player,
            setting_data::player_data*& a_player_data_element,
            actor_player_data*& a_player_data,
            setting_data::player_data::actor_value_source_handling a_additional);
    };
}  // actor
