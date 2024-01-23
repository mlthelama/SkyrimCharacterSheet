#pragma once

namespace util {
    class translation {
    public:
        static translation* get_singleton();

        static std::string get_game_language();

        void build_translation_map();

        bool load_translation(const std::filesystem::path& a_path);

        template <class T>
        const std::string& get_translation(const T& a_key) {
            if (const auto it = translation_map.find(a_key); it != translation_map.end()) {
                return it->second;
            }

            static std::string str = "TRANSLATION FAILED";
            //static auto str = static_cast<std::string>(a_key);
            return str;
            //return static_cast<std::string>(a_key);
        }

        translation(const translation&) = delete;
        translation(translation&&) = delete;

        translation& operator=(const translation&) = delete;
        translation& operator=(translation&&) = delete;

    protected:
        translation() = default;
        ~translation() = default;

    private:
        string_map<std::string> translation_map{};
    };
    
}  // util

#define TRANSLATE(STR) util::translation::get_singleton()->get_translation(STR).c_str()
