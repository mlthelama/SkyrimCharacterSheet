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
            return str;
        }

        template <class T>
        static bool needs_translation(T& a_key) {
            if (a_key.starts_with('$')) {
                return true;
            }
            return false;
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
