#pragma once
#include "CLIK/Array.h"
#include "CLIK/GFx/Controls/Button.h"
#include "CLIK/GFx/Controls/ScrollingList.h"
#include "CLIK/TextField.h"
#include "data/playerdata.h"

namespace scaleform {
    using show_menu = menu_util::show_menu;
    using stats_inventory_menu_value = menu_util::stats_inventory_menu_value;

    class stats_inventory_menu final : public RE::IMenu {
    public:
        static constexpr std::string_view menu_name = "ShowStatsInventory";
        static constexpr std::string_view file_name = menu_name;
        static constexpr show_menu menu = show_menu::m_stats_inventory;

        static void Register() {
            RE::UI::GetSingleton()->Register(menu_name, creator);
            logger::info("Registered {}"sv, menu_name);
        }

        static void open() {
            if (!is_menu_open()) {
                logger::debug("Open Menu {}"sv, menu_name);
                RE::UIMessageQueue::GetSingleton()->AddMessage(menu_name, RE::UI_MESSAGE_TYPE::kShow, nullptr);
            }
        }

        static void close() {
            if (is_menu_open()) {
                logger::debug("Close Menu {}"sv, menu_name);
                RE::UIMessageQueue::GetSingleton()->AddMessage(menu_name, RE::UI_MESSAGE_TYPE::kHide, nullptr);
            }
        }

        static bool is_menu_open() {
            auto is_open = RE::UI::GetSingleton()->IsMenuOpen(menu_name);
            if (is_open) {
                logger::trace("Menu {} is open {}"sv, menu_name, is_open);
            }
            return is_open;
        }

        void refresh_lists() {
            if (is_menu_open()) {
                update_lists();
            }
        }

        stats_inventory_menu(const stats_inventory_menu&) = delete;
        stats_inventory_menu(stats_inventory_menu&&) = delete;

        stats_inventory_menu& operator=(const stats_inventory_menu&) = delete;
        stats_inventory_menu& operator=(stats_inventory_menu&&) = delete;

    protected:
        stats_inventory_menu() {
            using context = RE::UserEvents::INPUT_CONTEXT_ID;
            using flag = RE::UI_MENU_FLAGS;

            const auto a_menu = static_cast<IMenu*>(this);
            const auto scaleform_manager = RE::BSScaleformManager::GetSingleton();
            [[maybe_unused]] const auto success = scaleform_manager->LoadMovieEx(a_menu,
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
            menu_util::log_resolution();
            logger::debug("Loading Menu {} was successful {}"sv, file_name, success);
            assert(success);
            view_ = a_menu->uiMovie;
            //_view->SetMouseCursorCount(0);
            a_menu->menuFlags |= flag::kUsesCursor;

            //menu->depthPriority = 0;
            //menu->inputContext = Context::kNone;

            init_extensions();

            is_active_ = true;
            view_->SetVisible(true);
        }


        ~stats_inventory_menu() override = default;


        static stl::owner<IMenu*> creator() { return new stats_inventory_menu(); }

        void PostCreate() override { on_open(); }

        //might not work that well if InventoryMenu is open
        RE::UI_MESSAGE_RESULTS ProcessMessage(RE::UIMessage& a_message) override {
            /*switch (*a_message.type) {
                case RE::UI_MESSAGE_TYPE::kHide:
                    OnClose();
                    return RE::UI_MESSAGE_RESULTS::kHandled;
                default:
                    return RE::IMenu::ProcessMessage(a_message);
            }*/

            if (a_message.menu == menu_name) {
                return RE::UI_MESSAGE_RESULTS::kHandled;
            }
            return RE::UI_MESSAGE_RESULTS::kPassOn;
        }

        void AdvanceMovie(const float a_interval, const uint32_t a_current_time) override {
            IMenu::AdvanceMovie(a_interval, a_current_time);
        }

        void Accept(CallbackProcessor* a_processor) override {
            a_processor->Process("Log", log);
            a_processor->Process("CloseMenu", close_menu);
        }

    private:
        class Logger : public RE::GFxLog {
        public:
            void LogMessageVarg(LogMessageType, const char* a_fmt, const std::va_list a_arg_list) override {
                std::string fmt(a_fmt ? a_fmt : "");
                while (!fmt.empty() && fmt.back() == '\n') { fmt.pop_back(); }

                std::va_list args;
                va_copy(args, a_arg_list);
                std::vector<char> buf(
                    static_cast<std::size_t>(std::vsnprintf(nullptr, 0, fmt.c_str(), a_arg_list) + 1));
                std::vsnprintf(buf.data(), buf.size(), fmt.c_str(), args);
                va_end(args);

                logger::info("{}: {}"sv, menu_name, buf.data());
            }
        };

        void init_extensions() const {
            const RE::GFxValue boolean(true);

            [[maybe_unused]] const bool success = view_->SetVariable("_global.gfxExtensions", boolean);
            assert(success);
            /*success = _view->SetVariable("_global.noInvisibleAdvance", boolean);
            assert(success);*/
        }

        void on_open() {
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
                [[maybe_unused]] const auto success = view_->GetVariable(std::addressof(instance), path.data());
                assert(success && instance.IsObject());
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
            menu_close_.Visible(false); //for now

            update_headers();

            update_lists();

            view_->SetVisible(true);
            root_obj_.Visible(true);

            disable_item_lists();

            logger::debug("Shown all Values for Menu {}"sv, menu_name);
        }

        static void update_text(CLIK::TextField a_field, const std::string_view a_string) {
            a_field.AutoSize(CLIK::Object{ "left" });
            a_field.HTMLText(a_string);
            a_field.Visible(true);
        }

        void update_headers() const {
            update_text(equip_header_, menu_keys::equip_title);
            update_text(armor_header_, menu_keys::armor_title);
            update_text(weapon_header_, menu_keys::weapon_title);
            update_text(effect_header_, menu_keys::effect_title);
        }

        [[nodiscard]] RE::GFxValue build_gfx_value(const std::string_view& a_key,
            const std::string& a_val,
            const std::string_view& a_icon) const {
            RE::GFxValue value;
            view_->CreateObject(std::addressof(value));
            value.SetMember("displayName", { a_key });
            value.SetMember("displayValue", { static_cast<std::string_view>(a_val) });
            value.SetMember("iconKey", { a_icon });
            value.SetMember("iconScale", { 18 });
            return value;
        }

        [[nodiscard]] RE::GFxValue build_gfx_value(const std::string_view& a_key,
            const std::string& a_val) const {
            RE::GFxValue value;
            view_->CreateObject(std::addressof(value));
            value.SetMember("displayName", { a_key });
            value.SetMember("displayValue", { static_cast<std::string_view>(a_val) });
            value.SetMember("iconScale", { 18 });
            return value;
        }

        void clear_providers() {
            equip_item_list_provider_.ClearElements();
            armor_item_list_provider_.ClearElements();
            weapon_item_list_provider_.ClearElements();
            effect_item_list_provider_.ClearElements();
        }

        void invalidate_item_lists() {
            equip_item_list_.Invalidate();
            armor_item_list_.Invalidate();
            weapon_item_list_.Invalidate();
            effect_item_list_.Invalidate();
        }

        void invalidate_data_item_lists() {
            equip_item_list_.InvalidateData();
            armor_item_list_.InvalidateData();
            weapon_item_list_.InvalidateData();
            effect_item_list_.InvalidateData();
        }

        void update_lists() {
            clear_providers();
            invalidate_item_lists();
            update_menu_values();

            invalidate_data_item_lists();
        }

        void update_menu_values() const {
            auto values = player_data::get_singleton()->get_values_to_display(menu, menu_name);
            logger::debug("Update menu Values, values to proces {}"sv, values.size());

            for (auto& [fst, snd] : values) {
                auto stat_value = fst;
                const auto stat_item = snd.get();

                stat_item->log_stat_item(stat_value, menu);

                if (stat_item->get_value().empty() ||
                    stat_item->get_stats_inventory_menu() == stats_inventory_menu_value::m_none ||
                    stat_item->get_stats_inventory_menu() == stats_inventory_menu_value::m_equip) {
                    continue;
                }

                menu_map_.find(stat_item->get_stats_inventory_menu())->second.PushBack(
                    build_gfx_value(stat_item->get_key(), stat_item->get_value(), stat_item->get_icon()));
                logger::trace("added to Menu {}, Name {}, Key {}, Value {}"sv,
                    stat_item->get_stats_menu(),
                    stat_value,
                    stat_item->get_key(),
                    stat_item->get_value());
            }
            for (auto& [fst, snd] : values) { snd.reset(); }
            values.clear();

            //it seems the inventory needs a bit after an equipchange, so an item might be shown equiped
            for (const auto armor = player_data::get_armor_map(); auto [slot, name] : armor) {
                menu_map_.find(stats_inventory_menu_value::m_equip)
                         ->second.PushBack(build_gfx_value(slot, static_cast<std::string>(name)));
            }

            logger::debug("Done Updateing Values, Map Size is {}"sv, values.size());
        }

        static void on_close() { }

        void disable_item_lists() {
            equip_item_list_.Disabled(true);
            armor_item_list_.Disabled(true);
            weapon_item_list_.Disabled(true);
            effect_item_list_.Disabled(true);
        }

        static void close_menu([[maybe_unused]] const RE::FxDelegateArgs& a_params) {
            assert(a_params.GetArgCount() == 0);
            logger::debug("GUI Close Button Pressed"sv);
            close();
        }

        static void log(const RE::FxDelegateArgs& a_params) {
            assert(a_params.GetArgCount() == 1);
            assert(a_params[0].IsString());

            logger::debug("{}: {}"sv, menu_name, a_params[0].GetString());
        }

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

        std::map<stats_inventory_menu_value, RE::GFxValue&> menu_map_ = {
            { stats_inventory_menu_value::m_equip, equip_item_list_provider_ },
            { stats_inventory_menu_value::m_armor, armor_item_list_provider_ },
            { stats_inventory_menu_value::m_weapon, weapon_item_list_provider_ },
            { stats_inventory_menu_value::m_effect, effect_item_list_provider_ },
        };
    };
}
