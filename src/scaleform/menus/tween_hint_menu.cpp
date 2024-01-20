#include "tween_hint_menu.h"
#include "input/menu_key_input_holder.h"
#include "mod/mod_manager.h"
#include "scaleform/menus/stats_menu.h"

namespace scaleform {

    void tween_hint_menu::Register() {
        RE::UI::GetSingleton()->Register(menu_name, creator);
        logger::info("Registered {}"sv, menu_name);
    }

    void tween_hint_menu::open() {
        if (!is_menu_open()) {
            logger::debug("Open Menu {}"sv, menu_name);
            RE::UIMessageQueue::GetSingleton()->AddMessage(menu_name, RE::UI_MESSAGE_TYPE::kShow, nullptr);
        }
    }

    void tween_hint_menu::close() {
        if (is_menu_open()) {
            logger::debug("Close Menu {}"sv, menu_name);
            RE::UIMessageQueue::GetSingleton()->AddMessage(menu_name, RE::UI_MESSAGE_TYPE::kHide, nullptr);
        }
    }

    bool tween_hint_menu::is_menu_open() { return RE::UI::GetSingleton()->IsMenuOpen(menu_name); }

    tween_hint_menu::tween_hint_menu() {
        auto* v_menu = static_cast<IMenu*>(this);

        auto* scaleform_manager = RE::BSScaleformManager::GetSingleton();
        const auto success = scaleform_manager->LoadMovieEx(v_menu,
            file_name,
            RE::BSScaleformManager::ScaleModeType::kExactFit,
            [&](RE::GFxMovieDef* a_def) -> void {
                fxDelegate.reset(new RE::FxDelegate);
                fxDelegate->RegisterHandler(this);
                a_def->SetState(RE::GFxState::StateType::kExternalInterface, fxDelegate.get());
                fxDelegate->Release();

                logger::trace("FPS: {}, Width: {}, Height: {}"sv,
                    a_def->GetFrameRate(),
                    a_def->GetWidth(),
                    a_def->GetHeight());
                a_def->SetState(RE::GFxState::StateType::kLog, RE::make_gptr<Logger>().get());
            });
        logger::debug("Loading Menu {} was successful {}"sv, file_name, success);
        view_ = v_menu->uiMovie;

        menuFlags.set(Flag::kRequiresUpdate, Flag::kUpdateUsesCursor, Flag::kCustomRendering, Flag::kUsesCursor);

        v_menu->depthPriority = 0;
        v_menu->inputContext = Context::kNone;

        init_extensions();

        is_active_ = true;
        view_->SetVisible(true);
    }

    RE::IMenu* tween_hint_menu::creator() { return new tween_hint_menu(); }

    void tween_hint_menu::PostCreate() { on_open(); }

    RE::UI_MESSAGE_RESULTS tween_hint_menu::ProcessMessage([[maybe_unused]] RE::UIMessage& a_message) {
        return RE::UI_MESSAGE_RESULTS::kPassOn;
    }

    void tween_hint_menu::AdvanceMovie(float a_interval, uint32_t a_current_time) {
        IMenu::AdvanceMovie(a_interval, a_current_time);
    }

    void tween_hint_menu::Accept(CallbackProcessor* a_processor) { a_processor->Process("Log", log); }

    void tween_hint_menu::Logger::LogMessageVarg(RE::GFxLogConstants::LogMessageType,
        const char* a_fmt,
        std::va_list a_arg_list) {
        std::string fmt(a_fmt ? a_fmt : "");
        while (!fmt.empty() && fmt.back() == '\n') {
            fmt.pop_back();
        }

        std::va_list args;
        va_copy(args, a_arg_list);
        std::vector<char> buf(static_cast<std::size_t>(std::vsnprintf(nullptr, 0, fmt.c_str(), a_arg_list) + 1));
        std::vsnprintf(buf.data(), buf.size(), fmt.c_str(), args);
        va_end(args);

        logger::info("{}: {}"sv, menu_name, buf.data());
    }

    void tween_hint_menu::init_extensions() const {
        /*const RE::GFxValue boolean(true);
        view_->SetVariable("_global.gfxExtensions", boolean);
        view_->SetVariable("_global.noInvisibleAdvance", boolean);*/
    }

    void tween_hint_menu::on_open() {
        using element_t = std::pair<std::reference_wrapper<CLIK::Object>, std::string_view>;

        for (std::array objects{ element_t{ std::ref(main_obj_), "main"sv },
                 element_t{ std::ref(left_hint_text_), "main.LB_Hint.HintText"sv },
                 element_t{ std::ref(left_hint_button_art_), "main.LB_Hint.ButtonArt_MC"sv },
                 element_t{ std::ref(right_hint_text_), "main.RB_Hint.HintText"sv },
                 element_t{ std::ref(right_hint_button_art_), "main.RB_Hint.ButtonArt_MC"sv } };
             const auto& [object, path] : objects) {
            auto& instance = object.get().GetInstance();
            view_->GetVariable(std::addressof(instance), path.data());
        }
        logger::debug("Loaded all SWF objects successfully for {}"sv, menu_name);

        main_obj_.Visible(false);

        auto right_key = get_and_update_right_hint();
        auto left_key = get_and_update_left_hint();

        main_obj_.data_provider(CLIK::Object{ build_key_gfx_value(right_key, left_key) });

        view_->SetVisible(true);
        main_obj_.Visible(true);

        logger::debug("Shown all Values for Menu {}"sv, menu_name);
    }

    void tween_hint_menu::on_close() {}

    void tween_hint_menu::log(const RE::FxDelegateArgs& a_params) {
        logger::debug("{}: {}"sv, menu_name, a_params[0].GetString());
    }

    void tween_hint_menu::update_text(CLIK::TextField a_field, const std::string_view a_string) {
        a_field.HTMLText(a_string);
        a_field.Visible(true);
    }

    RE::GFxValue tween_hint_menu::build_key_gfx_value(const uint32_t a_right_key, const uint32_t a_left_key) const {
        RE::GFxValue value;
        view_->CreateObject(std::addressof(value));
        value.SetMember("buttonRight", { a_right_key });
        value.SetMember("buttonLeft", { a_left_key });
        return value;
    }

    uint32_t tween_hint_menu::get_and_update_right_hint() {
        uint32_t key = 0;
        if (mod::mod_manager::get_singleton()->get_wait_menu_redirected()) {
            auto* interface_strings = RE::InterfaceStrings::GetSingleton();
            update_text(right_hint_text_, interface_strings->sleepWaitMenu);

            //input switch is noticed this way
            RE::UserEvents* user_events = RE::UserEvents::GetSingleton();
            auto* control_map = RE::ControlMap::GetSingleton();
            auto* device_manager = RE::BSInputDeviceManager::GetSingleton();
            auto device = RE::INPUT_DEVICE::kKeyboard;
            if (device_manager->IsGamepadEnabled()) {
                device = RE::INPUT_DEVICE::kGamepad;
            }

            key = control_map->GetMappedKey(user_events->wait, device);
            logger::debug("{} has key {} bound"sv, user_events->wait, key);
        } else {
            right_hint_text_.Visible(false);
            right_hint_button_art_.Visible(false);
        }
        return key;
    }

    uint32_t tween_hint_menu::get_and_update_left_hint() {
        auto* config_setting = setting::config_setting::get_singleton();
        auto stats_menu_name = config_setting->get_menu_data(setting_data::menu_data::menu_type::stats)->menu_name;
        update_text(left_hint_text_, stats_menu_name);

        uint32_t key = 0;
        auto key_list = input::menu_key_input_holder::get_singleton()->get_open_key_combo();
        if (!key_list.empty()) {
            key = *key_list.begin();
        }
        return key;
    }

}  // scaleform
