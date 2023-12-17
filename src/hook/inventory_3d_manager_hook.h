#pragma once

namespace hook {
    class inventory_3d_manager_hook {
    public:
        static void install();

    private:
        static void update_item_3d(RE::InventoryEntryData* a_objDesc);
        static inline REL::Relocation<decltype(update_item_3d)> update_item_3d_;
    };
}  // hook
