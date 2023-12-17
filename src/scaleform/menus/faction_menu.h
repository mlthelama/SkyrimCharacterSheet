#pragma once
#include "CLIK/Array.h"
#include "CLIK/GFx/Controls/Button.h"
#include "CLIK/GFx/Controls/ScrollingList.h"
#include "CLIK/TextField.h"
#include "setting/data/menu_data.h"

namespace scaleform {

    class faction_menu final
        : public RE::IMenu
        , public RE::MenuEventHandler {
    public:
        using GRefCountBaseStatImpl::operator new;
        using GRefCountBaseStatImpl::operator delete;

        static constexpr std::string_view menu_name = "ShowFactions";
        static constexpr std::string_view file_name = menu_name;
        static constexpr setting_data::menu_data::menu_type menu_type = setting_data::menu_data::menu_type::faction;

        static void Register();

        static void open();

        static void close();

        static bool is_menu_open();

        faction_menu(const faction_menu&) = delete;
        faction_menu(faction_menu&&) = delete;

        faction_menu& operator=(const faction_menu&) = delete;
        faction_menu& operator=(faction_menu&&) = delete;

    protected:
        faction_menu();

        ~faction_menu() override;

        static stl::owner<IMenu*> creator();

        void PostCreate() override;

        RE::UI_MESSAGE_RESULTS ProcessMessage(RE::UIMessage& a_message) override;

        void AdvanceMovie(float a_interval, uint32_t a_current_time) override;

        void Accept(CallbackProcessor* a_processor) override;

        bool CanProcess(RE::InputEvent* a_event) override;

        bool ProcessButton(RE::ButtonEvent* a_event) override;

    private:
        class Logger : public RE::GFxLog {
        public:
            void LogMessageVarg(LogMessageType, const char* a_fmt, std::va_list a_arg_list) override;
        };

        void init_extensions() const;

        void on_open();

        static void update_text(CLIK::TextField a_field, std::string_view a_string);

        static void update_text(CLIK::TextField a_field, std::string_view a_string, const std::string& a_auto_size);

        void update_title() const;

        void update_headers() const;

        [[nodiscard]] RE::GFxValue build_gfx_value(const std::string_view& a_key, const std::string& a_val) const;

        void clear_providers();

        void invalidate_item_lists();

        void invalidate_data_item_lists();

        void update_lists();

        void update_bottom() const;

        void update_menu_values() const;

        void update_bottom_values() const;

        static void on_close();

        void disable_item_lists();

        static void close_menu(const RE::FxDelegateArgs& a_params);

        static void prev_menu(const RE::FxDelegateArgs& a_params);

        static void log(const RE::FxDelegateArgs& a_params);

        static void process_prev();

        [[nodiscard]] std::string get_column_name(setting_data::menu_data::faction_column_type a_column) const;

        RE::GPtr<RE::GFxMovieView> view_;
        bool is_active_ = false;

        CLIK::MovieClip root_obj_;
        CLIK::TextField title_;
        CLIK::GFx::Controls::Button prev_;

        CLIK::TextField faction_header_;
        CLIK::TextField thane_header_;
        CLIK::TextField champion_header_;

        CLIK::GFx::Controls::ScrollingList faction_item_list_;
        RE::GFxValue faction_item_list_provider_;

        CLIK::GFx::Controls::ScrollingList thane_item_list_;
        RE::GFxValue thane_item_list_provider_;

        CLIK::GFx::Controls::ScrollingList champion_item_list_;
        RE::GFxValue champion_item_list_provider_;

        CLIK::GFx::Controls::Button menu_close_;

        CLIK::TextField faction_count_key_;
        CLIK::TextField thane_count_key_;
        CLIK::TextField champion_count_key_;

        CLIK::TextField faction_count_value_;
        CLIK::TextField thane_count_value_;
        CLIK::TextField champion_count_value_;

        std::map<setting_data::menu_data::faction_column_type, RE::GFxValue&> menu_map_ = {
            { setting_data::menu_data::faction_column_type::faction, faction_item_list_provider_ },
            { setting_data::menu_data::faction_column_type::thane, thane_item_list_provider_ },
            { setting_data::menu_data::faction_column_type::champion, champion_item_list_provider_ },
        };

        std::map<setting_data::menu_data::faction_column_type, std::string> column_name_map_;

        std::string previous_menu_name_;
        std::string menu_name_;
        std::string count_name_;
    };
}
