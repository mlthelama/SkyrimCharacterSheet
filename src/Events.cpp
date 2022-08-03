#include "events.h"
#include "events/equipmanager.h"
#include "events/keymanager.h"
#include "events/menumanager.h"

namespace events {
    void sink_event_handlers() {
        key_manager::sink();
        logger::info("Added Input Event"sv);

        if (setting::get_show_inventory_stats()) {
            menu_manager::sink();
            logger::info("Added Menu Event"sv);

            equip_manager::sink();
            logger::info("Added Equip Event"sv);
        }
    }
}
