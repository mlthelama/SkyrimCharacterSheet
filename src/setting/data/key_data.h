#pragma once

namespace setting_data {
    class key_data {
    public:
        enum class key_name { none, vampire, werewolf, count, in_favor, alternative };

        key_name key;
        std::string name;

        inline void log() { logger::trace("key '{}', name '{}'"sv, magic_enum::enum_name(key), name); }
    };
}
