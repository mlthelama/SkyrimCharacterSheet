#pragma once

namespace Papyrus {
    class ShowStats {
    public:
        static uint32_t GetKey(RE::StaticFunctionTag*);
        static void SetKey(RE::StaticFunctionTag*, uint32_t p_key);

        static bool Register(RE::BSScript::IVirtualMachine* p_vm);
    };

    void Register();
}