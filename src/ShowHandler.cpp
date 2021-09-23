#include "showhandler.h"
#include "player.h"
#include "scaleform/statsmenu.h"

ShowHandler* ShowHandler::GetSingleton() {
	static ShowHandler singleton;
	return std::addressof(singleton);
}

void ShowHandler::ShowWindow() {
	logger::trace("Gather Value and Show Window");
	Locker locker(_lock);

	RE::DebugNotification("Showing menu and information now.");

	Scaleform::StatsMenu::Open();
}

ShowHandler::ShowHandler() :
	_lock()
{}