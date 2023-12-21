#include "scaleform/scaleform.h"
#include "scaleform/menus/faction_menu.h"
#include "scaleform/menus/stats_inventory_menu.h"
#include "scaleform/menus/stats_menu.h"
#include "setting/input_setting.h"

namespace scaleform {
    void Register() {
        stats_menu::Register();
        faction_menu::Register();
        if (setting::input_setting::is_inventory_menu_enabled()) {
            stats_inventory_menu::Register();
        }
        logger::info("Registered all forms");
    }
}
