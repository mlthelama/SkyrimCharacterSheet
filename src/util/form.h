#pragma once

namespace util {
    class form {
    public:
        static RE::TESForm* get_tes_form_from_mod_and_form(const std::string& a_mod, const std::string& a_form);
    };
}  // util
