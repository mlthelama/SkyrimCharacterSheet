#include "event.h"
#include "event/equip_event.h"
#include "event/input_event.h"
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
        if (!setting::input_setting::get_tween_menu_only()) {
            input_event::sink();
            logger::info("Added Input Event"sv);
        }
    }
}
