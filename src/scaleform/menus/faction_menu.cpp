#include "scaleform/menus/faction_menu.h"
#include "actor/champion.h"
#include "actor/faction.h"
#include "actor/thane.h"
#include "input/menu_key_input_holder.h"
#include "mod/mod_manager.h"
#include "scaleform/menus/stats_menu.h"
#include "setting/config_setting.h"
#include "setting/input_setting.h"
#include "setting/key_setting.h"
#include "util/key_util.h"
#include "util/translation.h"

namespace scaleform {
    void faction_menu::Register() {
        RE::UI::GetSingleton()->Register(menu_name, creator);
        logger::info("Registered {}"sv, menu_name);
    }

    void faction_menu::open() {
        if (!is_menu_open()) {
            logger::debug("Open Menu {}"sv, menu_name);
            RE::UIMessageQueue::GetSingleton()->AddMessage(menu_name, RE::UI_MESSAGE_TYPE::kShow, nullptr);
        }
    }

    void faction_menu::close() {
        if (is_menu_open()) {
            logger::debug("Close Menu {}"sv, menu_name);
            RE::UIMessageQueue::GetSingleton()->AddMessage(menu_name, RE::UI_MESSAGE_TYPE::kHide, nullptr);
        }
    }

    bool faction_menu::is_menu_open() {
        auto is_open = RE::UI::GetSingleton()->IsMenuOpen(menu_name);
        if (is_open) {
            logger::trace("Menu {} is open {}"sv, menu_name, is_open);
        }
        return is_open;
    }

    faction_menu::faction_menu() {
        using context = RE::UserEvents::INPUT_CONTEXT_ID;

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
        if (mod::mod_manager::get_singleton()->get_skyrim_souls() || !setting::input_setting::get_menu_pause_game()) {
            v_menu->menuFlags.set(Flag::kAllowSaving,
                Flag::kUsesCursor,
                Flag::kUpdateUsesCursor,
                Flag::kTopmostRenderedMenu);
        } else {
            v_menu->menuFlags.set(Flag::kPausesGame,
                Flag::kUsesCursor,
                Flag::kUpdateUsesCursor,
                Flag::kTopmostRenderedMenu);
        }
        v_menu->depthPriority = 3;
        v_menu->inputContext = context::kNone;

        init_extensions();

        auto config_setting = setting::config_setting::get_singleton();
        auto menu_data = config_setting->get_menu_data(setting_data::menu_data::menu_type::faction);
        for (auto* column : menu_data->columns) {
            column_name_map_[column->faction_column] = column->column_name;
        }
        previous_menu_name_ = config_setting->get_previous_menu_name(menu_data->menu);
        menu_name_ = menu_data->menu_name;
        count_name_ = setting::key_setting::get_key(setting::key_setting::key_name::count);

        is_active_ = true;
        view_->SetVisible(true);

        auto menu_controls = RE::MenuControls::GetSingleton();
        menu_controls->RegisterHandler(this);
    }

    RE::IMenu* faction_menu::creator() { return new faction_menu(); }

    void faction_menu::PostCreate() { on_open(); }

    RE::UI_MESSAGE_RESULTS faction_menu::ProcessMessage(RE::UIMessage& a_message) {
        switch (*a_message.type) {
            case RE::UI_MESSAGE_TYPE::kHide:
            case RE::UI_MESSAGE_TYPE::kForceHide:
                on_close();
                return RE::UI_MESSAGE_RESULTS::kHandled;
            default:
                return IMenu::ProcessMessage(a_message);
        }
    }
    void faction_menu::AdvanceMovie(const float a_interval, const uint32_t a_current_time) {
        IMenu::AdvanceMovie(a_interval, a_current_time);
    }

    void faction_menu::Accept(CallbackProcessor* a_processor) {
        a_processor->Process("Log", log);
        a_processor->Process("CloseMenu", close_menu);
        a_processor->Process("PrevMenu", prev_menu);
    }

    void faction_menu::Logger::LogMessageVarg(RE::GFxLogConstants::LogMessageType,
        const char* a_fmt,
        const std::va_list a_arg_list) {
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

    void faction_menu::init_extensions() const {
        const RE::GFxValue boolean(true);
        view_->SetVariable("_global.gfxExtensions", boolean);
        view_->SetVariable("_global.noInvisibleAdvance", boolean);
    }

    void faction_menu::on_open() {
        using element_t = std::pair<std::reference_wrapper<CLIK::Object>, std::string_view>;

        for (std::array objects{ element_t{ std::ref(root_obj_), "_root.rootObj"sv },
                 element_t{ std::ref(title_), "_root.rootObj.title"sv },
                 element_t{ std::ref(faction_count_key_), "_root.rootObj.factionCount"sv },
                 element_t{ std::ref(thane_count_key_), "_root.rootObj.thaneCount"sv },
                 element_t{ std::ref(champion_count_key_), "_root.rootObj.championCount"sv },
                 element_t{ std::ref(faction_count_value_), "_root.rootObj.factionCountValue"sv },
                 element_t{ std::ref(thane_count_value_), "_root.rootObj.thaneCountValue"sv },
                 element_t{ std::ref(champion_count_value_), "_root.rootObj.championCountValue"sv },
                 element_t{ std::ref(faction_header_), "_root.rootObj.factionValuesHeader"sv },
                 element_t{ std::ref(thane_header_), "_root.rootObj.factionThanesHeader"sv },
                 element_t{ std::ref(champion_header_), "_root.rootObj.factionChampionHeader"sv },
                 element_t{ std::ref(faction_item_list_), "_root.rootObj.factionItemList"sv },
                 element_t{ std::ref(thane_item_list_), "_root.rootObj.thaneItemList"sv },
                 element_t{ std::ref(champion_item_list_), "_root.rootObj.championItemList"sv },
                 element_t{ std::ref(prev_), "_root.rootObj.factionPrevScreen"sv },
                 element_t{ std::ref(menu_close_), "_root.rootObj.menuClose"sv } };
             const auto& [object, path] : objects) {
            auto& instance = object.get().GetInstance();
            view_->GetVariable(std::addressof(instance), path.data());
        }
        logger::debug("Loaded all SWF objects successfully for {}"sv, menu_name);

        root_obj_.Visible(false);

        view_->CreateArray(std::addressof(faction_item_list_provider_));
        faction_item_list_.DataProvider(CLIK::Array{ faction_item_list_provider_ });

        view_->CreateArray(std::addressof(thane_item_list_provider_));
        thane_item_list_.DataProvider(CLIK::Array{ thane_item_list_provider_ });

        view_->CreateArray(std::addressof(champion_item_list_provider_));
        champion_item_list_.DataProvider(CLIK::Array{ champion_item_list_provider_ });

        update_title();
        update_headers();
        update_bottom();

        update_lists();

        update_buttons();

        disable_item_lists();

        view_->SetVisible(true);
        root_obj_.Visible(true);

        logger::debug("Shown all Values for Menu {}"sv, menu_name);
    }

    void faction_menu::update_text(CLIK::TextField a_field, std::string_view a_string) {
        if (util::translation::needs_translation(a_string)) {
            a_string = util::translation::get_singleton()->get_translation(a_string);
        }

        a_field.AutoSize(CLIK::Object{ "left" });
        a_field.HTMLText(a_string);
        a_field.Visible(true);
    }

    void faction_menu::update_text(CLIK::TextField a_field, std::string_view a_string, const std::string& a_auto_size) {
        if (util::translation::needs_translation(a_string)) {
            a_string = util::translation::get_singleton()->get_translation(a_string);
        }

        a_field.AutoSize(CLIK::Object{ a_auto_size });
        a_field.HTMLText(a_string);
        a_field.Visible(true);
    }

    void faction_menu::update_title() { update_text(title_, menu_name_); }

    void faction_menu::update_headers() {
        update_text(faction_header_, get_column_name(setting_data::menu_data::faction_column_type::faction));
        update_text(thane_header_, get_column_name(setting_data::menu_data::faction_column_type::thane));
        update_text(champion_header_, get_column_name(setting_data::menu_data::faction_column_type::champion));
    }

    RE::GFxValue faction_menu::build_gfx_value(std::string_view a_key, std::string& a_val) const {
        if (util::translation::needs_translation(a_key)) {
            a_key = util::translation::get_singleton()->get_translation(a_key);
        }
        if (util::translation::needs_translation(a_val)) {
            a_val = util::translation::get_singleton()->get_translation(a_val);
        }

        RE::GFxValue value;
        view_->CreateObject(std::addressof(value));
        value.SetMember("displayName", { a_key });
        value.SetMember("displayValue", { static_cast<std::string_view>(a_val) });
        return value;
    }

    void faction_menu::clear_providers() {
        faction_item_list_provider_.ClearElements();
        thane_item_list_provider_.ClearElements();
        champion_item_list_provider_.ClearElements();
    }

    void faction_menu::invalidate_item_lists() {
        faction_item_list_.Invalidate();
        thane_item_list_.Invalidate();
        champion_item_list_.Invalidate();
    }

    void faction_menu::invalidate_data_item_lists() {
        faction_item_list_.InvalidateData();
        thane_item_list_.InvalidateData();
        champion_item_list_.InvalidateData();
    }

    void faction_menu::update_lists() {
        clear_providers();
        invalidate_item_lists();

        update_menu_values();
        update_bottom_values();

        invalidate_data_item_lists();
    }

    void faction_menu::update_bottom() const {
        //in case something is not set, we do not want to see default swf text
        update_text(faction_count_key_, "");
        update_text(thane_count_key_, "");
        update_text(champion_count_key_, "");
        update_text(faction_count_value_, "");
        update_text(thane_count_value_, "");
        update_text(champion_count_value_, "");
    }

    void faction_menu::update_menu_values() const {
        auto* player = RE::PlayerCharacter::GetSingleton();
        auto faction_list = actor::faction::get_actor_factions(player);
        auto champion_list = actor::champion::get_actor_champions(player);
        auto thane_list = actor::thane::get_actor_thanes(player);

        logger::debug("start filling menu with data (faction), values to process {}"sv, faction_list.size());
        for (auto* faction : faction_list) {
            if (faction->column == setting_data::menu_data::faction_column_type::none) {
                continue;
            }
            menu_map_.find(faction->column)
                ->second.PushBack(build_gfx_value(faction->faction_name, faction->faction_rank_name));
        }

        logger::debug("start filling menu with data (champion), values to process {}"sv, champion_list.size());
        for (auto* champion : champion_list) {
            if (champion->column == setting_data::menu_data::faction_column_type::none) {
                continue;
            }
            menu_map_.find(champion->column)
                ->second.PushBack(build_gfx_value(champion->champion_name, champion->champion_finished_status));
        }

        logger::debug("start filling menu with data (thane), values to process {}"sv, thane_list.size());
        for (auto* thane : thane_list) {
            if (thane->column == setting_data::menu_data::faction_column_type::none) {
                continue;
            }
            //TODO add bounty
            menu_map_.find(thane->column)->second.PushBack(build_gfx_value(thane->name, thane->thane_name));
        }

        logger::debug("Done showing values. return."sv);
    }

    void faction_menu::update_bottom_values() const {
        update_text(faction_count_key_, count_name_);
        update_text(faction_count_value_,
            fmt::format(FMT_STRING("{}"), faction_item_list_provider_.GetArraySize()),
            "right");
        update_text(thane_count_key_, count_name_);
        update_text(thane_count_value_,
            fmt::format(FMT_STRING("{}"), thane_item_list_provider_.GetArraySize()),
            "right");
        update_text(champion_count_key_, count_name_);
        update_text(champion_count_value_,
            fmt::format(FMT_STRING("{}"), champion_item_list_provider_.GetArraySize()),
            "right");
    }

    void faction_menu::on_close() {
        auto menu_controls = RE::MenuControls::GetSingleton();
        menu_controls->RemoveHandler(this);
    }

    void faction_menu::disable_item_lists() {
        faction_item_list_.Disabled(true);
        thane_item_list_.Disabled(true);
        champion_item_list_.Disabled(true);
    }

    void faction_menu::close_menu(const RE::FxDelegateArgs& a_params) {
        logger::debug("GUI Close Button Pressed, parameter count {}"sv, a_params.GetArgCount());
        close();
    }

    void faction_menu::prev_menu(const RE::FxDelegateArgs& a_params) {
        logger::debug("GUI Prev Button Pressed, parameter count {}"sv, a_params.GetArgCount());
        process_prev();
    }

    void faction_menu::log(const RE::FxDelegateArgs& a_params) {
        logger::debug("{}: {}"sv, menu_name, a_params[0].GetString());
    }

    void faction_menu::process_prev() {
        close();
        stats_menu::open();
    }

    std::string faction_menu::get_column_name(setting_data::menu_data::faction_column_type a_column) const {
        if (!column_name_map_.empty() && column_name_map_.contains(a_column)) {
            return column_name_map_.at(a_column);
        }
        return {};
    }

    bool faction_menu::CanProcess(RE::InputEvent* a_event) {
        if (!a_event) {
            return false;
        }

        return true;
    }

    bool faction_menu::ProcessButton(RE::ButtonEvent* a_event) {
        auto key = a_event->idCode;
        util::key_util::get_key_id(a_event->GetDevice(), key);

        if (a_event->IsDown()) {
            if (key == RE::BSWin32KeyboardDevice::Key::kEscape) {
                close();
            }
            auto previous = setting::input_setting::get_previous_page_menu_key_list();
            if (std::find(previous.begin(), previous.end(), key) != previous.end()) {
                logger::debug("previous menu Key ({}) pressed"sv, key);
                process_prev();
            }
        }

        auto* key_input = input::menu_key_input_holder::get_singleton();
        if (a_event->eventType != RE::INPUT_EVENT_TYPE::kButton &&
            a_event->eventType != RE::INPUT_EVENT_TYPE::kThumbstick) {
            return true;
        }

        if (a_event->HasIDCode()) {
            if (a_event->IsUp()) {
                key_input->remove_key_down(key);
            }

            if (!a_event->IsDown()) {
                return true;
            }

            if (key_input->get_open_key_combo().contains(key) || key_input->get_close_key_combo().contains(key)) {
                key_input->add_key_down(key);
            }

            if (key_input->is_down_list_equal(false)) {
                close();
                key_input->clear_set();
            }
        }


        return true;
    }

    faction_menu::~faction_menu() {
        auto menu_controls = RE::MenuControls::GetSingleton();
        menu_controls->RemoveHandler(this);
    }

    void faction_menu::update_buttons() {
        auto close = setting::key_setting::get_key(setting::key_setting::key_name::close);
        if (util::translation::needs_translation(close)) {
            close = util::translation::get_singleton()->get_translation(close);
        }
        menu_close_.Label(close);
        menu_close_.Disabled(false);

        if (util::translation::needs_translation(previous_menu_name_)) {
            previous_menu_name_ = util::translation::get_singleton()->get_translation(previous_menu_name_);
        }
        prev_.Label(previous_menu_name_);
        prev_.Disabled(false);
    }
}
