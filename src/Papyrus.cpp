#include "papyrus.h"
#include "events.h"

namespace Papyrus {
    uint32_t ShowStats::GetKey(RE::StaticFunctionTag*) {
        auto input = Events::KeyManager::GetSingleton();
        logger::info("getKey {}", input->GetKey());
        return input->GetKey();
    }

    void ShowStats::SetKey(RE::StaticFunctionTag*, uint32_t p_key) {
        auto input = Events::KeyManager::GetSingleton();
        logger::info("setKey {}", p_key);
        input->SetKey(p_key);
    }

    bool ShowStats::Register(RE::BSScript::IVirtualMachine* p_vm) {
        p_vm->RegisterFunction("GetKey", "ShowStats", GetKey);
        p_vm->RegisterFunction("SetKey", "ShowStats", SetKey);
        logger::info("Registered ShowStats class");
        return true;
    }

    void Register() {
        auto papyrus = SKSE::GetPapyrusInterface();
        papyrus->Register(ShowStats::Register);

        logger::info("Registered papyrus functions");
    }

}