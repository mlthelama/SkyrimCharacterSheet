#include "events.h"
#include "events/equipmanager.h"
#include "events/keymanager.h"
#include "events/menumanager.h"

namespace Events {
    void SinkEventHandlers() {
        KeyManager::Sink();
        logger::info("Added Input Event"sv);

        if (*Settings::closeOnOtherMenuOpen || *Settings::showInventoryStats) {
            MenuManager::Sink();
            logger::info("Added Menu Event"sv);
        }

        if (*Settings::showInventoryStats) {
            EquipManager::Sink();
            logger::info("Added Equip Event"sv);
        }
    }
}
