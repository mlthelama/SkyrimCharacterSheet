#pragma once
#include "util/utils.h"

namespace util {
    class perk_visitor : public RE::PerkEntryVisitor {
    public:
        //explicit perk_visitor(RE::Actor* a_actor) {
        explicit perk_visitor() {
            //actor_ = a_actor;
            result_ = 0;
        }

        RE::PerkEntryVisitor::ReturnType Visit(RE::BGSPerkEntry* perk_entry) override;

        [[nodiscard]] float get_result() const;

    protected:
        //RE::Actor* actor_;
        float result_;
    };
}  // util
