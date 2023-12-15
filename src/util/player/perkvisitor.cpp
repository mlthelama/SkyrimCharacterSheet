#include "perkvisitor.h"
#include <util/type_util.h>

namespace util {
    RE::PerkEntryVisitor::ReturnType perk_visitor::Visit(RE::BGSPerkEntry* perk_entry) {
        const auto* entry_point = static_cast<RE::BGSEntryPointPerkEntry*>(perk_entry);
        const auto* perk = entry_point->perk;

        logger::trace("formid {}, name {}"sv, util::type_util::int_to_hex(perk->GetFormID()), perk->GetName());

        if (entry_point->functionData &&
            entry_point->entryData.function == RE::BGSEntryPointPerkEntry::EntryData::Function::kMultiplyValue) {
            const RE::BGSEntryPointFunctionDataOneValue* value =
                static_cast<RE::BGSEntryPointFunctionDataOneValue*>(entry_point->functionData);
            result_ = value->data;
            logger::trace("Got value for Perk {}"sv, result_);
        }

        return ReturnType::kContinue;
    }

    float perk_visitor::get_result() const { return result_; }
}  // util
