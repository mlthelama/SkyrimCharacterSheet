#include "ShowHandler.h"
#include "player.h"

ShowHandler* ShowHandler::GetSingleton() {
	static ShowHandler singleton;
	return std::addressof(singleton);
}

void ShowHandler::LogValues() {
	logger::trace("WriteStuff");
	Locker locker(_lock);

	Player* playerinfo = Player::GetSingleton();
	ValueMap playerValues = playerinfo->getValues();
}

ShowHandler::ShowHandler() :
	_lock()
{}