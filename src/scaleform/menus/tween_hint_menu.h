#pragma once

#include "CLIK/MovieClip.h"
#include "CLIK/TextField.h"
#include <CLIK/TweenMainWidget.h>

namespace scaleform {
    class tween_hint_menu final : public RE::IMenu {
    public:
        static constexpr std::string_view menu_name = "ShowTweenHintMenu";
        static constexpr std::string_view file_name = menu_name;

        static void Register();

        static void open();

        static void close();

        static bool is_menu_open();

        tween_hint_menu(const tween_hint_menu&) = delete;
        tween_hint_menu(tween_hint_menu&&) = delete;

        tween_hint_menu& operator=(const tween_hint_menu&) = delete;
        tween_hint_menu& operator=(tween_hint_menu&&) = delete;

    protected:
        tween_hint_menu();

        ~tween_hint_menu() override = default;

        static stl::owner<IMenu*> creator();

        void PostCreate() override;

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

        static void on_close();

        static void log(const RE::FxDelegateArgs& a_params);

        static void update_text(CLIK::TextField a_field, std::string& a_string);

        [[nodiscard]] RE::GFxValue build_key_gfx_value(uint32_t a_right_key, uint32_t a_left_key) const;

        uint32_t get_and_update_right_hint();

        uint32_t get_and_update_left_hint();

        RE::GPtr<RE::GFxMovieView> view_;
        bool is_active_ = false;

        CLIK::TweenMainWidget main_obj_;

        CLIK::TextField left_hint_text_;
        CLIK::MovieClip left_hint_button_art_;

        CLIK::TextField right_hint_text_;
        CLIK::MovieClip right_hint_button_art_;
    };
}  // scaleform
