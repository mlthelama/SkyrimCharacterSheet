#include "perkvisitor.h"
#include "util/type_util.h"

namespace util {
    RE::BSContainer::ForEachResult perk_visitor::Visit(RE::BGSPerkEntry* perk_entry) {

        const auto* entry_point = static_cast<RE::BGSEntryPointPerkEntry*>(perk_entry);
        const auto* perk = entry_point->perk;

        logger::trace("formid {}, name {}, type {}, function {}"sv,
            util::type_util::int_to_hex(perk->GetFormID()),
            perk->GetName(),
            static_cast<uint32_t>(entry_point->functionData->GetType()),
            entry_point->entryData.function.underlying());

 

        RE::BGSEntryPointFunctionDataOneValue* value = nullptr;
        switch (entry_point->functionData->GetType()) {
            case RE::BGSEntryPointFunctionData::ENTRY_POINT_FUNCTION_DATA::kOneValue:
                value = static_cast<RE::BGSEntryPointFunctionDataOneValue*>(entry_point->functionData);
                break;
            case RE::BGSEntryPointFunctionData::ENTRY_POINT_FUNCTION_DATA::kInvalid:
            case RE::BGSEntryPointFunctionData::ENTRY_POINT_FUNCTION_DATA::kTwoValue:
            case RE::BGSEntryPointFunctionData::ENTRY_POINT_FUNCTION_DATA::kLeveledList:
            case RE::BGSEntryPointFunctionData::ENTRY_POINT_FUNCTION_DATA::kActivateChoice:
            case RE::BGSEntryPointFunctionData::ENTRY_POINT_FUNCTION_DATA::kSpellItem:
            case RE::BGSEntryPointFunctionData::ENTRY_POINT_FUNCTION_DATA::kBooleanGraphVariable:
            case RE::BGSEntryPointFunctionData::ENTRY_POINT_FUNCTION_DATA::kText:
                break;
        }
        if (value) {
            result_ = value->data;
        }

        logger::trace("Got value {} for Perk {}"sv, result_, perk->GetName());

        return RE::BSContainer::ForEachResult::kStop;
    }

    float perk_visitor::get_result() const { return result_; }

}  // util
