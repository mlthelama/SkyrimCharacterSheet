#include "scaleform/scaleform.h"
#include "scaleform/menus/factionmenu.h"
#include "scaleform/menus/statsmenu.h"
#include "scaleform/menus/statsinventorymenu.h"

namespace Scaleform {
    void Register() {
        StatsMenu::Register();
        FactionMenu::Register();
        StatsInventoryMenu::Register();
        logger::info("Registered all forms");
    }
}
