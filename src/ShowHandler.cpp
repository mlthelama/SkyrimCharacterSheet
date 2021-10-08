#include "showhandler.h"
#include "scaleform/statsmenu.h"

auto ShowHandler::GetSingleton() -> ShowHandler* {
    static ShowHandler singleton;
    return std::addressof(singleton);
}

void ShowHandler::ShowWindow() {
    logger::trace("Gather Value and Show Window");
    Locker locker(_lock);

    if (*Settings::logLevel == logTrace) {
        RE::DebugNotification("Showing menu and information now.");
    }
    Scaleform::StatsMenu::Open();
}

ShowHandler::ShowHandler() : _lock() {}