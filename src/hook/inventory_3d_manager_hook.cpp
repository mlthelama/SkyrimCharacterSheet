#include "inventory_3d_manager_hook.h"

namespace hook {
    void inventory_3d_manager_hook::install() {
        auto& trampoline = SKSE::GetTrampoline();
        REL::Relocation<std::uintptr_t> update_item_3d_hook{ RELOCATION_ID(50884, 51757) };
        update_item_3d_ = trampoline.write_branch<5>(update_item_3d_hook.address(), &update_item_3d);
    }

    void inventory_3d_manager_hook::update_item_3d(RE::InventoryEntryData* a_objDesc) {
        update_item_3d_(a_objDesc);

        if (!a_objDesc) {
            return;
        }

        auto bound_object = a_objDesc->GetObject();
        if (!bound_object) {
            return;
        }

        /*if (RE::UI::GetSingleton()->IsMenuOpen(RE::InventoryMenu::MENU_NAME)) {
            if(bound_object->GetFormType() == RE::FormType::Book){
                logger::info("book?"sv);
            }
        }*/
        //logger::info("type {}"sv, magic_enum::enum_name(bound_object->GetFormType()));
        if (bound_object->GetFormType() == RE::FormType::Book) {
            logger::info("book?"sv);
        }
    }

}  // hook
