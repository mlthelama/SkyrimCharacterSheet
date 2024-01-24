#pragma once
#include "CLIK/Array.h"
#include "CLIK/GFx/Controls/Button.h"
#include "CLIK/GFx/Controls/ScrollingList.h"
#include "CLIK/TextField.h"
#include "setting/config_setting.h"
#include "setting/data/player_data.h"

namespace scaleform {

    class stats_menu final
        : public RE::IMenu
        , public RE::MenuEventHandler {
    public:
        using GRefCountBaseStatImpl::operator new;
        using GRefCountBaseStatImpl::operator delete;

        static constexpr std::string_view menu_name = "ShowStats";
        static constexpr std::string_view file_name = menu_name;
        static constexpr setting_data::menu_data::menu_type menu_type = setting_data::menu_data::menu_type::stats;

        static void Register();

        static void open();

        static void close();

        static bool is_menu_open();

        stats_menu(const stats_menu&) = delete;
        stats_menu(stats_menu&&) = delete;

        stats_menu& operator=(const stats_menu&) = delete;
        stats_menu& operator=(stats_menu&&) = delete;

    protected:
        stats_menu();

        ~stats_menu() override;

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

        RE::GFxValue
            build_gfx_value(std::string& a_key, const std::string& a_val, const std::string_view& a_icon) const;

        void clear_providers();

        void invalidate_item_lists();

        void invalidate_data_item_lists();

        void update_lists();

        void update_bottom() const;

        void update_menu_values() const;

        void on_close();

        void disable_item_lists();

        static void close_menu(const RE::FxDelegateArgs& a_params);

        static void next_menu(const RE::FxDelegateArgs& a_params);

        static void log(const RE::FxDelegateArgs& a_params);

        [[nodiscard]] CLIK::TextField& get_text_field_key(setting_data::player_data::stat a_stats_value) const;

        [[nodiscard]] CLIK::TextField& get_text_fields_value(setting_data::player_data::stat a_stats_value) const;

        static void process_next();

        [[nodiscard]] std::string get_column_name(setting_data::menu_data::stats_column_type a_column) const;

        RE::GPtr<RE::GFxMovieView> view_;
        bool is_active_ = false;

        CLIK::MovieClip root_obj_;
        CLIK::TextField title_;
        CLIK::GFx::Controls::Button next_;

        CLIK::TextField values_header_;
        CLIK::TextField attack_header_;
        CLIK::TextField perks_magic_header_;
        CLIK::TextField defence_header_;
        CLIK::TextField perks_warrior_header_;
        CLIK::TextField perks_thief_header_;

        CLIK::TextField name_key_;
        CLIK::TextField level_key_;
        CLIK::TextField race_key_;
        CLIK::TextField perks_key_;
        CLIK::TextField beast_key_;
        CLIK::TextField xp_key_;

        CLIK::TextField name_value_;
        CLIK::TextField level_value_;
        CLIK::TextField race_value_;
        CLIK::TextField perks_value_;
        CLIK::TextField beast_value_;
        CLIK::TextField xp_value_;

        CLIK::GFx::Controls::ScrollingList player_item_list_;
        RE::GFxValue player_item_list_provider_;

        CLIK::GFx::Controls::ScrollingList defence_item_list_;
        RE::GFxValue defence_item_list_provider_;

        CLIK::GFx::Controls::ScrollingList attack_item_list_;
        RE::GFxValue attack_item_list_provider_;

        CLIK::GFx::Controls::ScrollingList perks_magic_item_list_;
        RE::GFxValue perks_magic_item_list_provider_;

        CLIK::GFx::Controls::ScrollingList perks_warrior_item_list_;
        RE::GFxValue perks_warrior_item_list_provider_;

        CLIK::GFx::Controls::ScrollingList perks_thief_item_list_;
        RE::GFxValue perks_thief_item_list_provider_;

        CLIK::GFx::Controls::Button menu_close_;

        std::map<setting_data::menu_data::stats_column_type, RE::GFxValue&> menu_map_ = {
            { setting_data::menu_data::stats_column_type::player, player_item_list_provider_ },
            { setting_data::menu_data::stats_column_type::defence, defence_item_list_provider_ },
            { setting_data::menu_data::stats_column_type::attack, attack_item_list_provider_ },
            { setting_data::menu_data::stats_column_type::magic, perks_magic_item_list_provider_ },
            { setting_data::menu_data::stats_column_type::warrior, perks_warrior_item_list_provider_ },
            { setting_data::menu_data::stats_column_type::thief, perks_thief_item_list_provider_ },
        };

        std::map<setting_data::player_data::stat, CLIK::TextField&> bottom_map_key_ = {
            { setting_data::player_data::stat::name, name_key_ },
            { setting_data::player_data::stat::level, level_key_ },
            { setting_data::player_data::stat::race, race_key_ },
            { setting_data::player_data::stat::perk_count, perks_key_ },
            { setting_data::player_data::stat::beast, beast_key_ },
            { setting_data::player_data::stat::xp, xp_key_ },
        };

        std::map<setting_data::player_data::stat, CLIK::TextField&> bottom_map_value_ = {
            { setting_data::player_data::stat::name, name_value_ },
            { setting_data::player_data::stat::level, level_value_ },
            { setting_data::player_data::stat::race, race_value_ },
            { setting_data::player_data::stat::perk_count, perks_value_ },
            { setting_data::player_data::stat::beast, beast_value_ },
            { setting_data::player_data::stat::xp, xp_value_ },
        };

        std::map<setting_data::menu_data::stats_column_type, std::string> column_name_map_;

        std::string next_menu_name_;
        std::string menu_name_;
    };
}
