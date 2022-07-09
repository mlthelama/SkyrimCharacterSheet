#include "scaleform/menus/statsmenu.h"
#include "handler/showhandler.h"

void scaleform::stats_menu::process_next(const show_menu a_menu) {
    show_handler::handle_menu_swap(get_next_menu(a_menu));
}
