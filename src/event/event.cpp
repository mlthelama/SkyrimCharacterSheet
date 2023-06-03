#include "event.h"
#include "event/equip_event.h"
#include "event/input_event.h"
#include "event/menu_open_close_event.h"

namespace event {
    void sink_event_handlers() {
        input_event::sink();
        logger::info("Added Input Event"sv);

        if (ini_setting::get_show_inventory_stats()) {
            menu_open_close_event::sink();
            logger::info("Added Menu Event"sv);

            equip_event::sink();
            logger::info("Added Equip Event"sv);
        }
    }
}
