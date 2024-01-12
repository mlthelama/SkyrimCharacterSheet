#include "mod.h"
#include "mod/mod_manager.h"
#include "setting/mod_detection.h"

namespace mod {
    void mod::init_mod_support() {
        auto* mod_manager = mod_manager::get_singleton();
        auto* data_handler = RE::TESDataHandler::GetSingleton();

        //check for mods here
        if (setting::mod_detection::get_armor_rating_rescaled_remake()) {
            mod_manager->set_armor_rating_rescaled_remake(
                LoadLibrary(L"Data/SKSE/Plugins/ArmorRatingRescaledRemake.dll"));
        }
        if (setting::mod_detection::get_hand_to_hand()) {
            mod_manager->set_hand_to_hand(LoadLibrary(L"Data/SKSE/Plugins/HandToHand.dll"));
        }
        if (setting::mod_detection::get_blade_and_blunt()) {
            mod_manager->set_blade_and_blunt(LoadLibrary(L"Data/SKSE/Plugins/BladeAndBlunt.dll"));
        }
        if (setting::mod_detection::get_skyrim_unbound()) {
            mod_manager->set_skyrim_unbound((data_handler && data_handler->LookupModByName("Skyrim Unbound.esp")));
        }
        if (setting::mod_detection::get_skyrim_souls()) {
            mod_manager->set_skyrim_souls(LoadLibrary(L"Data/SKSE/Plugins/SkyrimSoulsRE.dll"));
        }
        if (setting::mod_detection::get_wait_menu_redirected()) {
            mod_manager->set_wait_menu_redirected(LoadLibrary(L"Data/SKSE/Plugins/WaitMenuRedirected.dll"));
        }
    }
}  // mod
