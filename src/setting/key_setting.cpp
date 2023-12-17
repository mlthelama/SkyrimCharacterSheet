#include "key_setting.h"

namespace setting {

    std::map<key_setting::key_name, std::string> key_map;

    void key_setting::load_setting() {
        logger::trace("loading key setting file"sv);
        auto file = R"(Data\SKSE\Plugins\SkyrimCharacterSheet\SkyrimCharacterSheet_Keys.json)";
        std::ifstream key_setting_file(file);
        if (!key_setting_file) {
            logger::warn("file {} not found"sv, file);
            return;
        }

        logger::info("loading key setting from file {}"sv, file);

        nlohmann::json json_setting;
        key_setting_file >> json_setting;

        if (json_setting.at("keys").is_array()) {
            auto& json_keys = json_setting.at("keys");
            for (auto& key_element : json_keys) {
                key_name key = key_setting::key_name::none;
                std::string key_name;

                auto& key_json = key_element.at("key");
                if (key_json.is_string()) {
                    auto key_enum = magic_enum::enum_cast<key_setting::key_name>(std::string{ key_json });
                    if (key_enum.has_value()) {
                        key = key_enum.value();
                    } else {
                        logger::warn("could not get enum for name {}"sv, to_string(key_json));
                    }
                }

                auto& name = key_element.at("name");
                if (name.is_string()) {
                    key_name = name;
                    logger::trace("key '{}', name '{}'"sv, magic_enum::enum_name(key), name);
                }

                if (key != key_setting::key_name::none && !key_name.empty()) {
                    key_map[key] = key_name;
                }
            }
        }

        logger::info("done loading key setting file, loaded {}"sv, key_map.size());
    }

    std::string key_setting::get_key(key_setting::key_name a_name) {
        if (a_name == key_setting::key_name::none) {
            return {};
        }
        if (!key_map.empty() && key_map.contains(a_name)) {
            return key_map.at(a_name);
        }
        return {};
    }

}  // setting
