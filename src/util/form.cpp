#include "form.h"
#include "type_util.h"

namespace util {
    RE::TESForm* form::get_tes_form_from_mod_and_form(const std::string& a_mod, const std::string& a_form) {
        if (a_mod.empty() || a_form.empty()) {
            return nullptr;
        }

        RE::TESForm* form;
        RE::FormID form_id;
        std::istringstream(a_form) >> std::hex >> form_id;

        logger::trace("checking mod {} for form {}"sv, a_mod, form_id);

        form = RE::TESDataHandler::GetSingleton()->LookupForm(form_id, a_mod);
        if (form) {
            logger::trace("got form id {}, name {}", util::type_util::int_to_hex(form->GetFormID()), form->GetName());
        }

        return form;
    }
}  // util
