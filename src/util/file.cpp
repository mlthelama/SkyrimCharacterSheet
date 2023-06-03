#include "file.h"

namespace util {
    std::vector<std::string> file::search_for_config_files(const std::string& a_base_name,
        const std::string& a_extension) {
        std::vector<std::string> file_list;

        auto file_path = R"(Data\SKSE\Plugins\SkyrimCharacterSheet\)";
        logger::trace("using file path {}"sv, file_path);
        if (std::filesystem::is_directory(file_path)) {
            for (const auto& entry : std::filesystem::directory_iterator(file_path)) {
                if (std::filesystem::is_regular_file(entry) && entry.path().extension() == a_extension &&
                    entry.path().filename().string().starts_with(a_base_name)) {
                    const auto& config_file_path = entry.path();
                    logger::trace("found file {}"sv, config_file_path.string());
                    file_list.push_back(config_file_path.string());
                }
            }
        }

        /*auto file_name = util::ini_default_name;
        if (a_elden) {
            file_name = util::ini_elden_name;
        }

        
        logger::trace("Will start looking in Path {}"sv, util::ini_path);
        if (std::filesystem::is_directory(util::ini_path)) {
            for (const auto& entry : std::filesystem::directory_iterator(util::ini_path)) {
                if (is_regular_file(entry) && entry.path().extension() == util::ini_ending &&
                    entry.path().filename().string().starts_with(file_name)) {
                    logger::trace("found file {}, path {}"sv, entry.path().filename().string(), entry.path().string());
                    if (!a_elden && entry.path().filename().string().starts_with(util::ini_elden_name)) {
                        logger::warn("Skipping File {}, because it would also match for Elden"sv,
                            entry.path().filename().string());
                        continue;
                    }
                    file_list.push_back(entry.path().filename().string());
                }
            }
        }
        logger::trace("Got {} Files to return in Path"sv, file_list.size());*/
        return file_list;
    }
}  // util
