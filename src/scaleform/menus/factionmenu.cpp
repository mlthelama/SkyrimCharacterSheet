#include "scaleform/menus/factionmenu.h"
#include "handler/showhandler.h"

void scaleform::faction_menu::process_prev(const show_menu a_menu) {
    show_handler::get_singleton()->handle_menu_swap(get_prev_menu(a_menu));
}
