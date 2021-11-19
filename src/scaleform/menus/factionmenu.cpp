#include "scaleform/menus/factionmenu.h"
#include "handler/showhandler.h"

void Scaleform::FactionMenu::ProcessPrev(ShowMenu a_menu) {
    ShowHandler::GetSingleton()->HandleMenuSwap(MenuUtil::getPrevMenu(a_menu));
}
