#include "translation.h"

namespace util {
    translation* translation::get_singleton() {
        static translation singleton;
        return std::addressof(singleton);
    }
    
    std::string translation::get_game_language() {
        const auto ini_setting = RE::INISettingCollection::GetSingleton();
        const auto setting = ini_setting ? ini_setting->GetSetting("sLanguage:General") : nullptr;
        
        return (setting && setting->GetType() == RE::Setting::Type::kString) ? clib_util::string::toupper(setting->data.s) : "ENGLISH"s;
    }
    
    void translation::build_translation_map() {
        std::filesystem::path path{ fmt::format(R"(Data\Interface\Translations\SkyrimCharacterSheet_{}.txt)", get_game_language()) };
        
        if (!load_translation(path)) {
            load_translation(R"(Data\Interface\Translations\SkyrimCharacterSheet_ENGLISH.txt)"sv);
        }
    }
    
    bool translation::load_translation(const std::filesystem::path& a_path) {
        if (!std::filesystem::exists(a_path)) {
            return false;
        }
        
        std::wfstream filestream(a_path, std::wfstream::in | std::wfstream::binary);
        if (!filestream.good()) {
            return false;
        } else {
            logger::info("Reading translations from {}...", a_path.string());
        }

        filestream.imbue(std::locale(filestream.getloc(), new std::codecvt_utf16<wchar_t, 0x10FFFF, std::little_endian>));

        // check if the BOM is UTF-16
        constexpr wchar_t BOM_UTF16LE = 0xFEFF;
        if (filestream.get() != BOM_UTF16LE) {
            logger::info("BOM Error, file must be encoded in UCS-2 LE.");
            return false;
        }

        std::wstring line, key, value;

        while (std::getline(filestream, line)) {
            std::wstringstream ss(line);
            ss >> key;
            // remove leading whitespace
            std::getline(ss >> std::ws, value);
            // remove space/new line at end
            if (std::isspace(value.back())) {
                value.pop_back();
            }
            translation_map.emplace(*stl::utf16_to_utf8(key), *stl::utf16_to_utf8(value));
        }

        logger::info("Read translations from {}...", a_path.string());
        return true;
    }

}  // util
