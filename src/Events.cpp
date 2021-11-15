#include "events.h"
#include "events/keymanager.h"
#include "events/menumanager.h"

namespace Events {
    void SinkEventHandlers() {
        KeyManager::Sink();
        logger::info("Added Input Event"sv);

        if (*Settings::closeOnOtherMenuOpen) {
            MenuManager::Sink();
            logger::info("Added Menu Event"sv);
        }
    }
}
