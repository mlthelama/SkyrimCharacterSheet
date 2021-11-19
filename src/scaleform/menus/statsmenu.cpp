#include "scaleform/menus/statsmenu.h"
#include "handler/showhandler.h"

void Scaleform::StatsMenu::ProcessNext(ShowMenu a_menu) {
    ShowHandler::GetSingleton()->HandleMenuSwap(MenuUtil::getNextMenu(a_menu));
}
