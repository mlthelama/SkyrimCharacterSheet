#pragma once

namespace util {
    class file {
    public:
        static std::vector<std::string> search_for_config_files(const std::string& a_base_name,
            const std::string& a_extension);
    };
}  // util
