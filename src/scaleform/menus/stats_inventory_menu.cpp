#include "stats_inventory_menu.h"
#include "actor/player.h"
#include "setting/config_setting.h"
#include "setting/data/menu_data.h"
#include "util/player/player.h"
#include "util/translation.h"

namespace scaleform {

    void stats_inventory_menu::Register() {
        RE::UI::GetSingleton()->Register(menu_name, creator);
        logger::info("Registered {}"sv, menu_name);
    }

    void stats_inventory_menu::open() {
        if (!is_menu_open()) {
            logger::debug("Open Menu {}"sv, menu_name);
            RE::UIMessageQueue::GetSingleton()->AddMessage(menu_name, RE::UI_MESSAGE_TYPE::kShow, nullptr);
        }
    }

    void stats_inventory_menu::close() {
        if (is_menu_open()) {
            logger::debug("Close Menu {}"sv, menu_name);
            RE::UIMessageQueue::GetSingleton()->AddMessage(menu_name, RE::UI_MESSAGE_TYPE::kHide, nullptr);
        }
    }

    bool stats_inventory_menu::is_menu_open() { return RE::UI::GetSingleton()->IsMenuOpen(menu_name); }

    void stats_inventory_menu::refresh_lists() {
        if (is_menu_open()) {
            update_lists();
        }
    }

    stats_inventory_menu::stats_inventory_menu() {
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

        auto menu_data = setting::config_setting::get_singleton()->get_menu_data(
            setting_data::menu_data::menu_type::stats_inventory);
        for (auto* column : menu_data->columns) {
            column_name_map_[column->stat_inventory_column] = column->column_name;
        }

        is_active_ = true;
        view_->SetVisible(true);
    }

    RE::IMenu* stats_inventory_menu::creator() { return new stats_inventory_menu(); }

    void stats_inventory_menu::PostCreate() { on_open(); }

    RE::UI_MESSAGE_RESULTS stats_inventory_menu::ProcessMessage([[maybe_unused]] RE::UIMessage& a_message) {
        /*switch (*a_message.type) {
                case RE::UI_MESSAGE_TYPE::kHide:
                    OnClose();
                    return RE::UI_MESSAGE_RESULTS::kHandled;
                default:
                    return RE::IMenu::ProcessMessage(a_message);
            }*/

        /*if (a_message.menu == menu_name) {
            return RE::UI_MESSAGE_RESULTS::kHandled;
        }*/
        return RE::UI_MESSAGE_RESULTS::kPassOn;
    }

    void stats_inventory_menu::AdvanceMovie(const float a_interval, const uint32_t a_current_time) {
        IMenu::AdvanceMovie(a_interval, a_current_time);
    }

    void stats_inventory_menu::Accept(CallbackProcessor* a_processor) {
        a_processor->Process("Log", log);
        a_processor->Process("CloseMenu", close_menu);
    }

    void stats_inventory_menu::Logger::LogMessageVarg(RE::GFxLogConstants::LogMessageType,
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

    void stats_inventory_menu::init_extensions() const {
        const RE::GFxValue boolean(true);
        view_->SetVariable("_global.gfxExtensions", boolean);
        view_->SetVariable("_global.noInvisibleAdvance", boolean);
    }

    void stats_inventory_menu::on_open() {
        using element_t = std::pair<std::reference_wrapper<CLIK::Object>, std::string_view>;

        for (std::array objects{ element_t{ std::ref(root_obj_), "_root.rootObj"sv },
                 element_t{ std::ref(equip_header_), "_root.rootObj.inventoryEquipHeader"sv },
                 element_t{ std::ref(armor_header_), "_root.rootObj.inventoryArmorHeader"sv },
                 element_t{ std::ref(weapon_header_), "_root.rootObj.inventoryWeaponHeader"sv },
                 element_t{ std::ref(effect_header_), "_root.rootObj.inventoryEffectHeader"sv },
                 element_t{ std::ref(equip_item_list_), "_root.rootObj.equipItemList"sv },
                 element_t{ std::ref(armor_item_list_), "_root.rootObj.armorItemList"sv },
                 element_t{ std::ref(weapon_item_list_), "_root.rootObj.weaponItemList"sv },
                 element_t{ std::ref(effect_item_list_), "_root.rootObj.effectItemList"sv },
                 element_t{ std::ref(menu_close_), "_root.rootObj.menuClose"sv } };
             const auto& [object, path] : objects) {
            auto& instance = object.get().GetInstance();
            view_->GetVariable(std::addressof(instance), path.data());
        }
        logger::debug("Loaded all SWF objects successfully for {}"sv, menu_name);

        root_obj_.Visible(false);

        view_->CreateArray(std::addressof(equip_item_list_provider_));
        equip_item_list_.DataProvider(CLIK::Array{ equip_item_list_provider_ });

        view_->CreateArray(std::addressof(armor_item_list_provider_));
        armor_item_list_.DataProvider(CLIK::Array{ armor_item_list_provider_ });

        view_->CreateArray(std::addressof(weapon_item_list_provider_));
        weapon_item_list_.DataProvider(CLIK::Array{ weapon_item_list_provider_ });

        view_->CreateArray(std::addressof(effect_item_list_provider_));
        effect_item_list_.DataProvider(CLIK::Array{ effect_item_list_provider_ });

        menu_close_.Label("Close");
        menu_close_.Disabled(false);
        menu_close_.Visible(false);  //for now

        update_headers();

        update_lists();

        view_->SetVisible(true);
        root_obj_.Visible(true);

        disable_item_lists();

        logger::debug("Shown all Values for Menu {}"sv, menu_name);
    }

    void stats_inventory_menu::update_text(CLIK::TextField a_field, std::string_view a_string) {
        if (util::translation::needs_translation(a_string)) {
            a_string = util::translation::get_singleton()->get_translation(a_string);
        }

        a_field.AutoSize(CLIK::Object{ "left" });
        a_field.HTMLText(a_string);
        a_field.Visible(true);
    }

    void stats_inventory_menu::update_headers() const {
        update_text(equip_header_, get_column_name(setting_data::menu_data::stats_inventory_column_type::equip));
        update_text(armor_header_, get_column_name(setting_data::menu_data::stats_inventory_column_type::armor));
        update_text(weapon_header_, get_column_name(setting_data::menu_data::stats_inventory_column_type::weapon));
        update_text(effect_header_, get_column_name(setting_data::menu_data::stats_inventory_column_type::effect));
    }

    RE::GFxValue stats_inventory_menu::build_gfx_value(std::string& a_key,
        const std::string& a_val,
        const std::string_view& a_icon) const {
        if (util::translation::needs_translation(a_key)) {
            a_key = util::translation::get_singleton()->get_translation(a_key);
        }

        RE::GFxValue value;
        view_->CreateObject(std::addressof(value));
        value.SetMember("displayName", { static_cast<std::string_view>(a_key) });
        value.SetMember("displayValue", { static_cast<std::string_view>(a_val) });
        value.SetMember("iconKey", { a_icon });
        value.SetMember("iconScale", { 18 });
        return value;
    }

    RE::GFxValue stats_inventory_menu::build_gfx_value(const std::string& a_key, const std::string& a_val) const {
        RE::GFxValue value;
        view_->CreateObject(std::addressof(value));
        value.SetMember("displayName", { static_cast<std::string_view>(a_key) });
        value.SetMember("displayValue", { static_cast<std::string_view>(a_val) });
        value.SetMember("iconScale", { 18 });
        return value;
    }

    void stats_inventory_menu::clear_providers() {
        equip_item_list_provider_.ClearElements();
        armor_item_list_provider_.ClearElements();
        weapon_item_list_provider_.ClearElements();
        effect_item_list_provider_.ClearElements();
    }

    void stats_inventory_menu::invalidate_item_lists() {
        equip_item_list_.Invalidate();
        armor_item_list_.Invalidate();
        weapon_item_list_.Invalidate();
        effect_item_list_.Invalidate();
    }

    void stats_inventory_menu::invalidate_data_item_lists() {
        equip_item_list_.InvalidateData();
        armor_item_list_.InvalidateData();
        weapon_item_list_.InvalidateData();
        effect_item_list_.InvalidateData();
    }

    void stats_inventory_menu::update_menu_values() const {
        auto* player = RE::PlayerCharacter::GetSingleton();
        auto player_data = actor::player::get_player_data(player, setting_data::menu_data::menu_type::stats_inventory);
        logger::debug("start filling menu with data, values to process {}"sv, player_data.size());
        for (auto* item : player_data) {
            if (item->inventory_column == setting_data::menu_data::stats_inventory_column_type::none) {
                continue;
            }
            menu_map_.find(item->inventory_column)
                ->second.PushBack(build_gfx_value(item->name, item->value, item->icon));
        }

        //it seems the inventory needs a bit after an equip change, so an item might be shown equipped
        for (const auto armor = util::player::get_equipment(player); auto [slot, name] : armor) {
            menu_map_.find(setting_data::menu_data::stats_inventory_column_type::equip)
                ->second.PushBack(build_gfx_value(slot, static_cast<std::string>(name)));
        }

        logger::debug("Done showing values, processed {} items. return."sv, player_data.size());
    }

    void stats_inventory_menu::on_close() {}

    void stats_inventory_menu::disable_item_lists() {
        equip_item_list_.Disabled(true);
        armor_item_list_.Disabled(true);
        weapon_item_list_.Disabled(true);
        effect_item_list_.Disabled(true);
    }

    void stats_inventory_menu::close_menu(const RE::FxDelegateArgs& a_params) {
        logger::debug("GUI Close Button Pressed, parameter count {}"sv, a_params.GetArgCount());
        close();
    }

    void stats_inventory_menu::log(const RE::FxDelegateArgs& a_params) {
        logger::debug("{}: {}"sv, menu_name, a_params[0].GetString());
    }

    std::string stats_inventory_menu::get_column_name(
        setting_data::menu_data::stats_inventory_column_type a_column) const {
        if (!column_name_map_.empty() && column_name_map_.contains(a_column)) {
            return column_name_map_.at(a_column);
        }
        return {};
    }
}
