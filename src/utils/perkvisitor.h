#pragma once
#include "utils/utils.h"

class perk_visiter : public RE::PerkEntryVisitor {
public:
    explicit perk_visiter(RE::Actor* a_actor) {
        actor_ = a_actor;
        result_ = 0;
    }

    ReturnType Visit(RE::BGSPerkEntry* perk_entry) override {
        const auto* entry_point = static_cast<RE::BGSEntryPointPerkEntry*>(perk_entry);
        const auto* perk = entry_point->perk;

        logger::trace("formid {}, name {}"sv, string_util::int_to_hex(perk->GetFormID()), perk->GetName());

        if (entry_point->functionData &&
            entry_point->entryData.function == RE::BGSEntryPointPerkEntry::EntryData::Function::kMultiplyValue) {
            const RE::BGSEntryPointFunctionDataOneValue* value =
                static_cast<RE::BGSEntryPointFunctionDataOneValue*>(entry_point->functionData);
            result_ = value->data;
            logger::trace("Got value for Perk {}"sv, result_);
        }

        return ReturnType::kContinue;
    }

    [[nodiscard]] float get_result() const { return result_; }

protected:
    RE::Actor* actor_;
    float result_;
};
