#pragma once

namespace setting {
    class key_setting {
    public:
        enum class key_name { none, vampire, werewolf, count, in_favor, alternative, close };

        static void load_setting();

        static std::string get_key(key_name a_name);
    };
}  // setting
