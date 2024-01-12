#include "setting.h"
#include "setting/config_setting.h"
#include "setting/game_setting.h"
#include "setting/key_setting.h"
#include "setting/mod_detection.h"

namespace setting {
    void setting::load_all_setting() {
        auto* config_setting = config_setting::get_singleton();

        config_setting->load_menu_setting_file();
        config_setting->load_all_faction_setting_files();
        config_setting->load_all_champion_setting_files();
        config_setting->load_all_thane_setting_files();
        config_setting->load_all_player_setting_files();

        //input settings are loaded in main when the log level is set
        key_setting::load_setting();
        mod_detection::load_setting();

        game_setting::get_singleton()->set_settings();
    }
}  // setting
