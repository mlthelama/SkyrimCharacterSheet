#pragma once
#include "CLIK/Array.h"
#include "CLIK/GFx/Controls/Button.h"
#include "CLIK/GFx/Controls/ScrollingList.h"
#include "CLIK/TextField.h"
#include "setting/data/menu_data.h"

namespace scaleform {

    class stats_inventory_menu final : public RE::IMenu {
    public:
        static constexpr std::string_view menu_name = "ShowStatsInventory";
        static constexpr std::string_view file_name = menu_name;

        static void Register();

        static void open();

        static void close();

        static bool is_menu_open();

        void refresh_lists();

        stats_inventory_menu(const stats_inventory_menu&) = delete;
        stats_inventory_menu(stats_inventory_menu&&) = delete;

        stats_inventory_menu& operator=(const stats_inventory_menu&) = delete;
        stats_inventory_menu& operator=(stats_inventory_menu&&) = delete;

    protected:
        stats_inventory_menu();

        ~stats_inventory_menu() override = default;

        static stl::owner<IMenu*> creator();

        void PostCreate() override;

        //might not work that well if InventoryMenu is open
        RE::UI_MESSAGE_RESULTS ProcessMessage(RE::UIMessage& a_message) override;

        void AdvanceMovie(float a_interval, uint32_t a_current_time) override;

        void Accept(CallbackProcessor* a_processor) override;

    private:
        class Logger : public RE::GFxLog {
        public:
            void LogMessageVarg(LogMessageType, const char* a_fmt, std::va_list a_arg_list) override;
        };

        void init_extensions() const;

        void on_open();

        static void update_text(CLIK::TextField a_field, std::string_view a_string);

        void update_headers() const;

        [[nodiscard]] RE::GFxValue build_gfx_value(const std::string_view& a_key,
            const std::string& a_val,
            const std::string_view& a_icon) const;

        [[nodiscard]] RE::GFxValue build_gfx_value(const std::string_view& a_key, const std::string& a_val) const;

        void clear_providers();

        void invalidate_item_lists();

        void invalidate_data_item_lists();

        void update_lists() {
            clear_providers();
            invalidate_item_lists();
            update_menu_values();

            invalidate_data_item_lists();
        }

        void update_menu_values() const;

        static void on_close();

        void disable_item_lists();

        static void close_menu(const RE::FxDelegateArgs& a_params);

        static void log(const RE::FxDelegateArgs& a_params);

        RE::GPtr<RE::GFxMovieView> view_;
        bool is_active_ = false;

        CLIK::MovieClip root_obj_;

        CLIK::TextField equip_header_;
        CLIK::TextField armor_header_;
        CLIK::TextField weapon_header_;
        CLIK::TextField effect_header_;

        CLIK::GFx::Controls::ScrollingList equip_item_list_;
        RE::GFxValue equip_item_list_provider_;

        CLIK::GFx::Controls::ScrollingList armor_item_list_;
        RE::GFxValue armor_item_list_provider_;

        CLIK::GFx::Controls::ScrollingList weapon_item_list_;
        RE::GFxValue weapon_item_list_provider_;

        CLIK::GFx::Controls::ScrollingList effect_item_list_;
        RE::GFxValue effect_item_list_provider_;

        CLIK::GFx::Controls::Button menu_close_;

        std::map<setting_data::menu_data::stats_inventory_column_type, RE::GFxValue&> menu_map_ = {
            { setting_data::menu_data::stats_inventory_column_type::equip, equip_item_list_provider_ },
            { setting_data::menu_data::stats_inventory_column_type::armor, armor_item_list_provider_ },
            { setting_data::menu_data::stats_inventory_column_type::weapon, weapon_item_list_provider_ },
            { setting_data::menu_data::stats_inventory_column_type::effect, effect_item_list_provider_ },
        };
    };
}
