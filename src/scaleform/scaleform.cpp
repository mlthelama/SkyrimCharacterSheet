#include "scaleform/scaleform.h"
#include "scaleform/factionmenu.h"
#include "scaleform/statsmenu.h"

namespace Scaleform {
    void Register() {
        StatsMenu::Register();
        FactionMenu::Register();
        logger::info("Registered all forms");
    }
}