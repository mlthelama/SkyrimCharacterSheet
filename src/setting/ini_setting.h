#pragma once

#include <SimpleIni.h>

class ini_setting {
    inline static const char* ini_path_ = R"(.\Data\SKSE\Plugins\SkyrimCharacterSheet.ini)";

    inline static bool is_debug_;
    inline static int open_menu_button_;
    inline static int open_faction_menu_button_;
    inline static bool show_inventory_stats_;
    inline static bool show_inventory_stats_auto_open_;
    inline static int show_inventory_button_;
    inline static int show_inventory_stats_auto_open_magic_menu_;

public:
    static void load_settings() {
        CSimpleIniA ini;
        ini.SetUnicode();
        ini.LoadFile(ini_path_);

        is_debug_ = ini.GetBoolValue("General", "bIsDebug", false);
        open_menu_button_ = ini.GetLongValue("General", "iOpenMenuButton", 22);
        open_faction_menu_button_ = ini.GetLongValue("General", "iOpenNextMenuButton", 49);
        show_inventory_stats_ = ini.GetBoolValue("General", "bShowInventoryStats", false);
        show_inventory_stats_auto_open_ = ini.GetBoolValue("General", "bShowInventoryStatsAutoOpen", false);
        show_inventory_button_ = ini.GetLongValue("General", "iShowInventoryButton", 11);
        show_inventory_stats_auto_open_magic_menu_ =
            ini.GetBoolValue("General", "bShowInventoryStatsAutoOpenMagicMenu", false);

        (void)ini.SaveFile(ini_path_);
    }

    static bool get_is_debug() { return is_debug_; }
    static int get_open_menu_button() { return open_menu_button_; }
    static int get_open_faction_menu_button() { return open_faction_menu_button_; }
    static bool get_show_inventory_stats() { return show_inventory_stats_; }
    static bool get_show_inventory_stats_auto_open() { return show_inventory_stats_auto_open_; }
    static int get_show_inventory_button() { return show_inventory_button_; }
    static bool get_show_inventory_stats_auto_open_magic_menu() { return show_inventory_stats_auto_open_magic_menu_; }
};
