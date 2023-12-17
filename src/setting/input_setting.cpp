#include "input_setting.h"

namespace setting {
    class stat_menu_input {
    public:
        std::set<uint32_t> open_key_combination;
        std::set<uint32_t> close_key_combination;
        std::vector<uint32_t> page_next_keys;
        std::vector<uint32_t> page_previous_keys;
        bool pause_game{};
    };

    class inventory_menu_input {
    public:
        std::set<uint32_t> open_key_combination;
        std::set<uint32_t> close_key_combination;
        bool is_enabled{};
        bool auto_show_inventory{};
        bool auto_show_magic{};
    };

    static bool is_debug;
    static stat_menu_input menu_input;
    static inventory_menu_input inventory_input;

    void input_setting::load_setting() {
        logger::info("loading input setting file"sv);
        auto file = R"(Data\SKSE\Plugins\SkyrimCharacterSheet\SkyrimCharacterSheet_Input.json)";
        std::ifstream input_setting_file(file);
        if (!input_setting_file) {
            logger::warn("file {} not found"sv, file);
            return;
        }

        logger::info("loading key setting from file {}"sv, file);

        nlohmann::json json_setting;
        input_setting_file >> json_setting;

        if (auto& debug = json_setting.at("debug"); debug.is_boolean()) {
            is_debug = debug;
        }

        if (auto& stat_menu = json_setting.at("stat"); stat_menu.is_object()) {
            if (auto& open_keys = stat_menu.at("open_key_combination"); open_keys.is_array()) {
                std::set<uint32_t> keys;
                for (auto& key : open_keys) {
                    //cast needed in this case
                    keys.insert(static_cast<uint32_t>(key));
                }
                menu_input.open_key_combination = keys;
            }

            if (auto& close_keys = stat_menu.at("close_key_combination"); close_keys.is_array()) {
                std::set<uint32_t> keys;
                for (auto& key : close_keys) {
                    //cast needed in this case
                    keys.insert(static_cast<uint32_t>(key));
                }
                menu_input.close_key_combination = keys;
            }

            if (auto& next_keys = stat_menu.at("page_next_keys"); next_keys.is_array()) {
                std::vector<uint32_t> keys;
                for (auto& key : next_keys) {
                    keys.push_back(key);
                }
                menu_input.page_next_keys = keys;
            }

            if (auto& previous_keys = stat_menu.at("page_previous_keys"); previous_keys.is_array()) {
                std::vector<uint32_t> keys;
                for (auto& key : previous_keys) {
                    keys.push_back(key);
                }
                menu_input.page_previous_keys = keys;
            }

            if (auto& paused = stat_menu.at("pause_game"); paused.is_boolean()) {
                menu_input.pause_game = paused;
            }
        }
        if (auto& inventory_menu = json_setting.at("inventory"); inventory_menu.is_object()) {
            if (auto& open_keys = inventory_menu.at("open_key_combination"); open_keys.is_array()) {
                std::set<uint32_t> keys;
                for (auto& key : open_keys) {
                    //cast needed in this case
                    keys.insert(static_cast<uint32_t>(key));
                }
                inventory_input.open_key_combination = keys;
            }

            if (auto& close_keys = inventory_menu.at("close_key_combination"); close_keys.is_array()) {
                std::set<uint32_t> keys;
                for (auto& key : close_keys) {
                    //cast needed in this case
                    keys.insert(static_cast<uint32_t>(key));
                }
                inventory_input.close_key_combination = keys;
            }

            if (auto& enabled = inventory_menu.at("enabled"); enabled.is_boolean()) {
                inventory_input.is_enabled = enabled;
            }

            if (auto& show_inventory = inventory_menu.at("auto_show_inventory"); show_inventory.is_boolean()) {
                inventory_input.auto_show_inventory = show_inventory;
            }

            if (auto& show_magic = inventory_menu.at("auto_show_magic"); show_magic.is_boolean()) {
                inventory_input.auto_show_magic = show_magic;
            }
        }

        logger::info("done loading input setting file"sv);
    }

    bool input_setting::get_is_debug() { return is_debug; }

    std::set<uint32_t> input_setting::get_open_menu_key_combination() { return menu_input.open_key_combination; }

    std::set<uint32_t> input_setting::get_close_menu_key_combination() { return menu_input.close_key_combination; }

    std::vector<uint32_t> input_setting::get_next_page_menu_key_list() { return menu_input.page_next_keys; }

    std::vector<uint32_t> input_setting::get_previous_page_menu_key_list() { return menu_input.page_previous_keys; }

    bool input_setting::get_menu_pause_game() { return menu_input.pause_game; }

    std::set<uint32_t> input_setting::get_open_inventory_menu_key_combination() {
        return inventory_input.open_key_combination;
    }

    std::set<uint32_t> input_setting::get_close_inventory_menu_key_combination() {
        return inventory_input.close_key_combination;
    }

    bool input_setting::is_inventory_menu_enabled() { return inventory_input.is_enabled; }

    bool input_setting::auto_open_inventory_menu_inventory() { return inventory_input.auto_show_inventory; }

    bool input_setting::auto_open_inventory_menu_magic() { return inventory_input.auto_show_magic; }

    void input_setting::log() {
        logger::debug(
            "menu: open {}, close {}, next {}, previous {}, paused {}. inventory: open {}, close {}, enabled {}, auto_inventory {}, auto_magic {}"sv,
            menu_input.open_key_combination.size(),
            menu_input.close_key_combination.size(),
            menu_input.page_next_keys.size(),
            menu_input.close_key_combination.size(),
            menu_input.pause_game,
            inventory_input.open_key_combination.size(),
            inventory_input.close_key_combination.size(),
            inventory_input.is_enabled,
            inventory_input.auto_show_inventory,
            inventory_input.auto_show_magic);
    }
}  // setting
