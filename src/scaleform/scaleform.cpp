#include "scaleform/scaleform.h"
#include "scaleform/menus/factionmenu.h"
#include "scaleform/menus/statsinventorymenu.h"
#include "scaleform/menus/statsmenu.h"

namespace scaleform {
    void Register() {
        stats_menu::Register();
        FactionMenu::Register();
        stats_inventory_menu::Register();
        logger::info("Registered all forms");
    }
}
