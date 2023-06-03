#include "scaleform/scaleform.h"
#include "scaleform/menus/faction_menu.h"
#include "scaleform/menus/stats_inventory_menu.h"
#include "scaleform/menus/stats_menu.h"

namespace scaleform {
    void Register() {
        stats_menu::Register();
        faction_menu::Register();
        stats_inventory_menu::Register();
        logger::info("Registered all forms");
    }
}
