#include "scaleform/menus/stats_menu.h"
#include "actor/player.h"
#include "mod/mod_manager.h"
#include "scaleform/menus/faction_menu.h"
#include "setting/input_setting.h"
#include "util/key_util.h"

namespace scaleform {
    void stats_menu::Register() {
        RE::UI::GetSingleton()->Register(menu_name, creator);
        logger::info("Registered {}"sv, menu_name);
    }

    void stats_menu::open() {
        if (!is_menu_open()) {
            logger::debug("Open Menu {}"sv, menu_name);
            RE::UIMessageQueue::GetSingleton()->AddMessage(menu_name, RE::UI_MESSAGE_TYPE::kShow, nullptr);
        }
    }

    void stats_menu::close() {
        if (is_menu_open()) {
            logger::debug("Close Menu {}"sv, menu_name);
            RE::UIMessageQueue::GetSingleton()->AddMessage(menu_name, RE::UI_MESSAGE_TYPE::kHide, nullptr);
        }
    }

    bool stats_menu::is_menu_open() {
        auto is_open = RE::UI::GetSingleton()->IsMenuOpen(menu_name);
        if (is_open) {
            logger::trace("Menu {} is open {}"sv, menu_name, is_open);
        }
        return is_open;
    }

    stats_menu::stats_menu() {
        using context = RE::UserEvents::INPUT_CONTEXT_ID;
        using flag = RE::UI_MENU_FLAGS;

        auto* v_menu = static_cast<IMenu*>(this);
        auto* scaleform_manager = RE::BSScaleformManager::GetSingleton();
        //do not update ng yet, crashes at createinstance at gfxmoviedef
        //TODO test fix might be https://github.com/powerof3/CommonLibSSE/commit/bcff68216c9fadf567203aec0c7e67f60c6e136c
        const auto success = scaleform_manager->LoadMovieEx(v_menu,
            file_name,
            RE::BSScaleformManager::ScaleModeType::kExactFit,
            [&](RE::GFxMovieDef* a_def) -> void {
                fxDelegate.reset(new RE::FxDelegate);
                fxDelegate->RegisterHandler(this);
                a_def->SetState(RE::GFxState::StateType::kExternalInterface, fxDelegate.get());
                fxDelegate->Release();

                logger::trace("SWF FPS: {}, Width: {}, Height: {}"sv,
                    a_def->GetFrameRate(),
                    a_def->GetWidth(),
                    a_def->GetHeight());
                a_def->SetState(RE::GFxState::StateType::kLog, RE::make_gptr<Logger>().get());
            });
        logger::debug("Loading Menu {} was successful {}"sv, file_name, success);
        view_ = v_menu->uiMovie;

        if (mod::mod_manager::get_singleton()->get_skyrim_souls() || !setting::input_setting::get_menu_pause_game()) {
            v_menu->menuFlags.set(flag::kAllowSaving,
                flag::kUsesCursor,
                flag::kDisablePauseMenu,
                flag::kUpdateUsesCursor,
                flag::kTopmostRenderedMenu);
        } else {
            v_menu->menuFlags.set(flag::kPausesGame,
                flag::kUsesCursor,
                flag::kDisablePauseMenu,
                flag::kUpdateUsesCursor,
                flag::kTopmostRenderedMenu);
        }
        v_menu->depthPriority = 3;
        v_menu->inputContext = context::kNone;

        init_extensions();

        auto config_setting = setting::config_setting::get_singleton();
        auto menu_data = config_setting->get_menu_data(setting_data::menu_data::menu_type::stats);
        for (auto* column : menu_data->columns) {
            column_name_map_[column->stat_column] = column->column_name;
        }
        next_menu_name_ = config_setting->get_next_menu_name(menu_data->menu);
        menu_name_ = menu_data->menu_name;

        is_active_ = true;
        view_->SetVisible(true);

        auto menu_controls = RE::MenuControls::GetSingleton();
        menu_controls->RegisterHandler(this);
    }

    RE::IMenu* stats_menu::creator() { return new stats_menu(); }

    void stats_menu::PostCreate() { on_open(); }

    RE::UI_MESSAGE_RESULTS stats_menu::ProcessMessage(RE::UIMessage& a_message) {
        switch (*a_message.type) {
            case RE::UI_MESSAGE_TYPE::kHide:
            case RE::UI_MESSAGE_TYPE::kForceHide:
                on_close();
                return RE::UI_MESSAGE_RESULTS::kHandled;
            default:
                return IMenu::ProcessMessage(a_message);
        }
    }
    void stats_menu::AdvanceMovie(const float a_interval, const uint32_t a_current_time) {
        IMenu::AdvanceMovie(a_interval, a_current_time);
    }

    void stats_menu::Accept(CallbackProcessor* a_processor) {
        a_processor->Process("Log", log);
        a_processor->Process("CloseMenu", close_menu);
        a_processor->Process("NextMenu", next_menu);
    }

    void stats_menu::Logger::LogMessageVarg(RE::GFxLogConstants::LogMessageType,
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

    void stats_menu::init_extensions() const {
        const RE::GFxValue boolean(true);
        view_->SetVariable("_global.gfxExtensions", boolean);
        view_->SetVariable("_global.noInvisibleAdvance", boolean);
    }

    void stats_menu::on_open() {
        using element_t = std::pair<std::reference_wrapper<CLIK::Object>, std::string_view>;

        for (std::array objects{ element_t{ std::ref(root_obj_), "_root.rootObj"sv },
                 element_t{ std::ref(title_), "_root.rootObj.title"sv },
                 element_t{ std::ref(name_key_), "_root.rootObj.name"sv },
                 element_t{ std::ref(level_key_), "_root.rootObj.level"sv },
                 element_t{ std::ref(race_key_), "_root.rootObj.race"sv },
                 element_t{ std::ref(perks_key_), "_root.rootObj.perks"sv },
                 element_t{ std::ref(beast_key_), "_root.rootObj.beast"sv },
                 element_t{ std::ref(xp_key_), "_root.rootObj.xp"sv },
                 element_t{ std::ref(name_value_), "_root.rootObj.nameValue"sv },
                 element_t{ std::ref(level_value_), "_root.rootObj.levelValue"sv },
                 element_t{ std::ref(race_value_), "_root.rootObj.raceValue"sv },
                 element_t{ std::ref(perks_value_), "_root.rootObj.perksValue"sv },
                 element_t{ std::ref(beast_value_), "_root.rootObj.beastValue"sv },
                 element_t{ std::ref(xp_value_), "_root.rootObj.xpValue"sv },
                 element_t{ std::ref(values_header_), "_root.rootObj.playerValuesHeader"sv },
                 element_t{ std::ref(attack_header_), "_root.rootObj.playerAttackHeader"sv },
                 element_t{ std::ref(perks_magic_header_), "_root.rootObj.playerPerksMagicHeader"sv },
                 element_t{ std::ref(defence_header_), "_root.rootObj.playerDefenceHeader"sv },
                 element_t{ std::ref(perks_warrior_header_), "_root.rootObj.playerPerksWarriorHeader"sv },
                 element_t{ std::ref(perks_thief_header_), "_root.rootObj.playerPerksThiefHeader"sv },
                 element_t{ std::ref(player_item_list_), "_root.rootObj.playerItemList"sv },
                 element_t{ std::ref(defence_item_list_), "_root.rootObj.defenceItemList"sv },
                 element_t{ std::ref(attack_item_list_), "_root.rootObj.attackItemList"sv },
                 element_t{ std::ref(perks_magic_item_list_), "_root.rootObj.perksMagicItemList"sv },
                 element_t{ std::ref(perks_warrior_item_list_), "_root.rootObj.perksWarriorItemList"sv },
                 element_t{ std::ref(perks_thief_item_list_), "_root.rootObj.perksThiefItemList"sv },
                 element_t{ std::ref(next_), "_root.rootObj.playerNextScreen"sv },
                 element_t{ std::ref(menu_close_), "_root.rootObj.menuClose"sv } };
             const auto& [object, path] : objects) {
            auto& instance = object.get().GetInstance();
            view_->GetVariable(std::addressof(instance), path.data());
        }
        logger::debug("Loaded all SWF objects successfully for {}"sv, menu_name);

        root_obj_.Visible(false);

        view_->CreateArray(std::addressof(player_item_list_provider_));
        player_item_list_.DataProvider(CLIK::Array{ player_item_list_provider_ });

        view_->CreateArray(std::addressof(defence_item_list_provider_));
        defence_item_list_.DataProvider(CLIK::Array{ defence_item_list_provider_ });

        view_->CreateArray(std::addressof(attack_item_list_provider_));
        attack_item_list_.DataProvider(CLIK::Array{ attack_item_list_provider_ });

        view_->CreateArray(std::addressof(perks_magic_item_list_provider_));
        perks_magic_item_list_.DataProvider(CLIK::Array{ perks_magic_item_list_provider_ });

        view_->CreateArray(std::addressof(perks_warrior_item_list_provider_));
        perks_warrior_item_list_.DataProvider(CLIK::Array{ perks_warrior_item_list_provider_ });

        view_->CreateArray(std::addressof(perks_thief_item_list_provider_));
        perks_thief_item_list_.DataProvider(CLIK::Array{ perks_thief_item_list_provider_ });

        menu_close_.Label("Close");
        menu_close_.Disabled(false);

        update_title();
        update_headers();
        update_bottom();

        update_lists();

        next_.Label(next_menu_name_);
        next_.Disabled(false);

        disable_item_lists();

        view_->SetVisible(true);
        root_obj_.Visible(true);

        logger::debug("Shown all Values for Menu {}"sv, menu_name);
    }

    void stats_menu::update_text(CLIK::TextField a_field, const std::string_view a_string) {
        a_field.AutoSize(CLIK::Object{ "left" });
        a_field.HTMLText(a_string);
        a_field.Visible(true);
    }
    void stats_menu::update_text(CLIK::TextField a_field,
        const std::string_view a_string,
        const std::string& a_auto_size) {
        a_field.AutoSize(CLIK::Object{ a_auto_size });
        a_field.HTMLText(a_string);
        a_field.Visible(true);
    }
    void stats_menu::update_title() const { update_text(title_, menu_name_); }

    void stats_menu::update_headers() const {
        update_text(values_header_, get_column_name(setting_data::menu_data::stats_column_type::player));
        update_text(attack_header_, get_column_name(setting_data::menu_data::stats_column_type::attack));
        update_text(perks_magic_header_, get_column_name(setting_data::menu_data::stats_column_type::magic));
        update_text(defence_header_, get_column_name(setting_data::menu_data::stats_column_type::defence));
        update_text(perks_warrior_header_, get_column_name(setting_data::menu_data::stats_column_type::warrior));
        update_text(perks_thief_header_, get_column_name(setting_data::menu_data::stats_column_type::thief));
    }

    RE::GFxValue stats_menu::build_gfx_value(const std::string_view& a_key,
        const std::string& a_val,
        const std::string_view& a_icon) const {
        RE::GFxValue value;
        view_->CreateObject(std::addressof(value));
        value.SetMember("displayName", { a_key });
        value.SetMember("displayValue", { static_cast<std::string_view>(a_val) });
        value.SetMember("iconKey", { a_icon });
        value.SetMember("iconScale", { 22 });

        return value;
    }

    void stats_menu::clear_providers() {
        player_item_list_provider_.ClearElements();
        defence_item_list_provider_.ClearElements();
        attack_item_list_provider_.ClearElements();
        perks_magic_item_list_provider_.ClearElements();
        perks_warrior_item_list_provider_.ClearElements();
        perks_thief_item_list_provider_.ClearElements();
    }

    void stats_menu::invalidate_item_lists() {
        player_item_list_.Invalidate();
        defence_item_list_.Invalidate();
        attack_item_list_.Invalidate();
        perks_magic_item_list_.Invalidate();
        perks_warrior_item_list_.Invalidate();
        perks_thief_item_list_.Invalidate();
    }

    void stats_menu::invalidate_data_item_lists() {
        player_item_list_.InvalidateData();
        defence_item_list_.InvalidateData();
        attack_item_list_.InvalidateData();
        perks_magic_item_list_.InvalidateData();
        perks_warrior_item_list_.InvalidateData();
        perks_thief_item_list_.InvalidateData();
    }

    void stats_menu::update_lists() {
        clear_providers();
        invalidate_item_lists();

        update_menu_values();

        invalidate_data_item_lists();
    }

    void stats_menu::update_bottom() const {
        //in case something is not set, we do not want to see default swf text
        for (const auto& [stat_value, text_field] : bottom_map_key_) {
            update_text(text_field, "");
        }
        for (const auto& [stat_value, text_field_value] : bottom_map_value_) {
            update_text(text_field_value, "");
        }
    }

    void stats_menu::update_menu_values() const {
        auto* player = RE::PlayerCharacter::GetSingleton();
        auto player_data = actor::player::get_player_data(player, setting_data::menu_data::menu_type::stats);
        logger::debug("start filling menu with data, values to process {}"sv, player_data.size());

        for (auto* item : player_data) {
            if (item->column == setting_data::menu_data::stats_column_type::none) {
                continue;
            }
            switch (item->key) {
                case setting_data::player_data::stat::name:
                case setting_data::player_data::stat::level:
                case setting_data::player_data::stat::race:
                case setting_data::player_data::stat::perk_count:
                case setting_data::player_data::stat::beast:
                case setting_data::player_data::stat::xp:
                    update_text(get_text_field_key(item->key), item->name);
                    update_text(get_text_fields_value(item->key), item->value, "right");
                    break;
                default:
                    menu_map_.find(item->column)->second.PushBack(build_gfx_value(item->name, item->value, item->icon));
                    item->log(setting_data::menu_data::menu_type::stats);
                    break;
            }
        }
        logger::debug("Done showing values, processed {} items. return."sv, player_data.size());
    }

    void stats_menu::on_close() {}

    void stats_menu::disable_item_lists() {
        player_item_list_.Disabled(true);
        defence_item_list_.Disabled(true);
        attack_item_list_.Disabled(true);
        perks_magic_item_list_.Disabled(true);
        perks_warrior_item_list_.Disabled(true);
        perks_thief_item_list_.Disabled(true);
    }

    void stats_menu::close_menu(const RE::FxDelegateArgs& a_params) {
        logger::debug("GUI Close Button Pressed, parameter count {}"sv, a_params.GetArgCount());
        close();
    }

    void stats_menu::next_menu(const RE::FxDelegateArgs& a_params) {
        logger::debug("GUI Next Button Pressed, parameter count {}"sv, a_params.GetArgCount());
        process_next();
    }

    void stats_menu::log(const RE::FxDelegateArgs& a_params) {
        logger::debug("{}: {}"sv, menu_name, a_params[0].GetString());
    }

    CLIK::TextField& stats_menu::get_text_field_key(const setting_data::player_data::stat a_stats_value) const {
        return bottom_map_key_.find(a_stats_value)->second;
    }

    CLIK::TextField& stats_menu::get_text_fields_value(const setting_data::player_data::stat a_stats_value) const {
        return bottom_map_value_.find(a_stats_value)->second;
    }

    void stats_menu::process_next() {
        close();
        faction_menu::open();
    }

    std::string stats_menu::get_column_name(setting_data::menu_data::stats_column_type a_column) const {
        if (!column_name_map_.empty() && column_name_map_.contains(a_column)) {
            return column_name_map_.at(a_column);
        }
        return {};
    }

    bool stats_menu::CanProcess(RE::InputEvent* a_event) {
        if (!a_event) {
            return false;
        }

        return true;
    }

    bool stats_menu::ProcessButton(RE::ButtonEvent* a_event) {
        auto key = a_event->idCode;
        util::key_util::get_key_id(a_event->GetDevice(), key);

        if (a_event->IsDown()) {
            if (key == RE::BSWin32KeyboardDevice::Key::kEscape) {
                close();
            }
            auto next = setting::input_setting::get_next_page_menu_key_list();
            if (std::find(next.begin(), next.end(), key) != next.end()) {
                logger::debug("next menu Key ({}) pressed"sv, key);
                process_next();
            }
        }

        return true;
    }

    stats_menu::~stats_menu() {
        auto menu_controls = RE::MenuControls::GetSingleton();
        menu_controls->RemoveHandler(this);
    }
}
