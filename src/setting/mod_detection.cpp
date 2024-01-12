#include "mod_detection.h"

namespace setting {
    static bool armor_rating_rescaled_remake;
    static bool hand_to_hand;
    static bool skyrim_unbound;
    static bool skyrim_souls;
    static bool blade_and_blunt;
    static bool wait_menu_redirected;

    void mod_detection::load_setting() {
        logger::info("loading mod detection setting file"sv);
        auto file = R"(Data\SKSE\Plugins\SkyrimCharacterSheet\SkyrimCharacterSheet_ModDetection.json)";
        std::ifstream mod_detection_setting_file(file);
        if (!mod_detection_setting_file) {
            logger::warn("file {} not found"sv, file);
            return;
        }

        logger::info("loading mod detection setting from file {}"sv, file);

        nlohmann::json json_setting;
        mod_detection_setting_file >> json_setting;

        if (auto& armor_rating_rescaled_remake_json = json_setting.at("armor_rating_rescaled_remake");
            armor_rating_rescaled_remake_json.is_boolean()) {
            armor_rating_rescaled_remake = armor_rating_rescaled_remake_json;
        }

        if (auto& hand_to_hand_json = json_setting.at("hand_to_hand"); hand_to_hand_json.is_boolean()) {
            hand_to_hand = hand_to_hand_json;
        }

        if (auto& skyrim_unbound_json = json_setting.at("skyrim_unbound"); skyrim_unbound_json.is_boolean()) {
            skyrim_unbound = skyrim_unbound_json;
        }

        if (auto& skyrim_souls_json = json_setting.at("skyrim_souls"); skyrim_souls_json.is_boolean()) {
            skyrim_souls = skyrim_souls_json;
        }

        if (auto& blade_and_blunt_json = json_setting.at("blade_and_blunt"); blade_and_blunt_json.is_boolean()) {
            blade_and_blunt = blade_and_blunt_json;
        }

        if (auto& wait_menu_redirected_json = json_setting.at("wait_menu_redirected");
            wait_menu_redirected_json.is_boolean()) {
            wait_menu_redirected = wait_menu_redirected_json;
        }

        logger::info("done loading input setting file"sv);
        log();
    }

    void mod_detection::log() {
        logger::debug(
            "mod detection: armor_rating_rescaled_remake {}, hand_to_hand {}, skyrim_unbound {}, skyrim_souls {}, blade_and_blunt {}. wait_menu_redirected {}"sv,
            armor_rating_rescaled_remake,
            hand_to_hand,
            skyrim_unbound,
            skyrim_souls,
            blade_and_blunt,
            wait_menu_redirected);
    }

    bool mod_detection::get_armor_rating_rescaled_remake() { return armor_rating_rescaled_remake; }

    bool mod_detection::get_hand_to_hand() { return hand_to_hand; }

    bool mod_detection::get_skyrim_unbound() { return skyrim_unbound; }

    bool mod_detection::get_skyrim_souls() { return skyrim_souls; }

    bool mod_detection::get_blade_and_blunt() { return blade_and_blunt; }

    bool mod_detection::get_wait_menu_redirected() { return wait_menu_redirected; }

}  // setting
