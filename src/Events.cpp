#include "events.h"
#include "events/equipmanager.h"
#include "events/keymanager.h"
#include "events/menumanager.h"

namespace Events {
    void SinkEventHandlers() {
        KeyManager::Sink();
        logger::info("Added Input Event"sv);

        if (*Settings::showInventoryStats) {
            MenuManager::Sink();
            logger::info("Added Menu Event"sv);

            EquipManager::Sink();
            logger::info("Added Equip Event"sv);
        }
    }
}
