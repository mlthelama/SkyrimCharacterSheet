#include "event.h"
#include "event/equip_event.h"
#include "event/menu_open_close_event.h"
#include "setting/input_setting.h"

namespace event {
    void sink_event_handlers() {
        if (setting::input_setting::is_inventory_menu_enabled()) {
            menu_open_close_event::sink();
            logger::info("Added Menu Event"sv);

            equip_event::sink();
            logger::info("Added Equip Event"sv);
        }
    }
}
