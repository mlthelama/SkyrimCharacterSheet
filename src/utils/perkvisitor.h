#pragma once
#include "utils/utils.h"

class PerkVisiter : public RE::PerkEntryVisitor {
public:
    PerkVisiter(RE::Actor* a_actor) {
        _actor = a_actor;
        _result = 0;
    }

    virtual RE::PerkEntryVisitor::ReturnType Visit(RE::BGSPerkEntry* perkEntry) override {
        RE::BGSEntryPointPerkEntry* entryPoint = (RE::BGSEntryPointPerkEntry*)perkEntry;
        RE::BGSPerk* perk = entryPoint->perk;

        logger::trace("formid {}, name {}"sv, StringUtil::intToHex(perk->GetFormID()), perk->GetName());

        if (entryPoint->functionData &&
            entryPoint->entryData.function == RE::BGSEntryPointPerkEntry::EntryData::Function::kMultiplyValue) {
            RE::BGSEntryPointFunctionDataOneValue* _value =
                (RE::BGSEntryPointFunctionDataOneValue*)entryPoint->functionData;
            _result = _value->data;
            logger::trace("Got value for Perk {}"sv, _result);
        }

        return RE::PerkEntryVisitor::ReturnType::kContinue;
    }

    float GetResult() const { return _result; }

protected:
    RE::Actor* _actor;
    float _result;
};
