#include "hook.h"
#include "hook/menu_control_hook.h"
#include "setting/input_setting.h"

namespace hook {
    void hook::install() {
        if (setting::input_setting::is_inventory_menu_enabled()) {
            menu_control_hook::install();
        }
    }
}  // hook
