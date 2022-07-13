#pragma once
#include "CLIK/Array.h"
#include "CLIK/GFx/Controls/Button.h"
#include "CLIK/GFx/Controls/ScrollingList.h"
#include "CLIK/TextField.h"
#include "data/factiondata.h"
#include "utils/menukeys.h"


namespace scaleform {
    using faction_menu_value = menu_util::faction_menu_value;
    using show_menu = menu_util::show_menu;

    class faction_menu final : public RE::IMenu {
    public:
        static constexpr std::string_view menu_name = "ShowFactions";
        static constexpr std::string_view file_name = menu_name;
        static constexpr show_menu menu = show_menu::m_faction;

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

        faction_menu(const faction_menu&) = delete;
        faction_menu(faction_menu&&) = delete;

        faction_menu& operator=(const faction_menu&) = delete;
        faction_menu& operator=(faction_menu&&) = delete;

    protected:
        faction_menu() {
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
            if (*settings::pause_game) {
                a_menu->menuFlags.set(flag::kPausesGame,
                    flag::kUsesCursor,
                    flag::kDisablePauseMenu,
                    flag::kUpdateUsesCursor,
                    flag::kTopmostRenderedMenu);
            } else {
                a_menu->menuFlags.set(flag::kAllowSaving,
                    flag::kUsesCursor,
                    flag::kDisablePauseMenu,
                    flag::kUpdateUsesCursor,
                    flag::kTopmostRenderedMenu);
            }
            a_menu->depthPriority = 5;
            a_menu->inputContext = context::kNone;
            init_extensions();

            is_active_ = true;
            view_->SetVisible(true);
        }


        ~faction_menu() override = default;


        static stl::owner<IMenu*> creator() { return new faction_menu(); }

        void PostCreate() override { on_open(); }

        RE::UI_MESSAGE_RESULTS ProcessMessage(RE::UIMessage& a_message) override {
            switch (*a_message.type) {
                case RE::UI_MESSAGE_TYPE::kHide:
                    on_close();
                    return RE::UI_MESSAGE_RESULTS::kHandled;
                default:
                    return IMenu::ProcessMessage(a_message);
            }
        }

        void AdvanceMovie(const float a_interval, const uint32_t a_current_time) override {
            IMenu::AdvanceMovie(a_interval, a_current_time);
        }

        void Accept(CallbackProcessor* a_processor) override {
            a_processor->Process("Log", log);
            a_processor->Process("CloseMenu", close_menu);
            a_processor->Process("PrevMenu", prev_menu);
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
            //success = _view->SetVariable("_global.noInvisibleAdvance", boolean);
            //assert(success);
        }

        void on_open() {
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
                [[maybe_unused]] const auto success = view_->GetVariable(std::addressof(instance), path.data());
                assert(success && instance.IsObject());
            }
            logger::debug("Loaded all SWF objects successfully for {}"sv, menu_name);

            root_obj_.Visible(false);

            view_->CreateArray(std::addressof(faction_item_list_provider_));
            faction_item_list_.DataProvider(CLIK::Array{ faction_item_list_provider_ });

            view_->CreateArray(std::addressof(thane_item_list_provider_));
            thane_item_list_.DataProvider(CLIK::Array{ thane_item_list_provider_ });

            view_->CreateArray(std::addressof(champion_item_list_provider_));
            champion_item_list_.DataProvider(CLIK::Array{ champion_item_list_provider_ });

            menu_close_.Label("Close");
            menu_close_.Disabled(false);

            update_title();
            update_headers();
            update_bottom();

            update_lists();

            prev_.Label(get_prev_menu_name(menu));
            prev_.Disabled(false);

            disable_item_lists();

            view_->SetVisible(true);
            root_obj_.Visible(true);

            logger::debug("Shown all Values for Menu {}"sv, menu_name);
        }

        static void update_text(CLIK::TextField a_field, const std::string_view a_string) {
            a_field.AutoSize(CLIK::Object{ "left" });
            a_field.HTMLText(a_string);
            a_field.Visible(true);
        }

        static void update_text(CLIK::TextField a_field,
            const std::string_view a_string,
            const std::string& a_auto_size) {
            a_field.AutoSize(CLIK::Object{ a_auto_size });
            a_field.HTMLText(a_string);
            a_field.Visible(true);
        }

        void update_title() const { update_text(title_, get_menu_name(menu)); }

        void update_headers() const {
            update_text(faction_header_, menu_keys::faction_title);
            update_text(thane_header_, menu_keys::thane_title);
            update_text(champion_header_, menu_keys::champion_title);
        }

        [[nodiscard]] RE::GFxValue build_gfx_value(const std::string_view& a_key, const std::string& a_val) const {
            RE::GFxValue value;
            view_->CreateObject(std::addressof(value));
            value.SetMember("displayName", { a_key });
            value.SetMember("displayValue", { static_cast<std::string_view>(a_val) });
            return value;
        }

        void clear_providers() {
            faction_item_list_provider_.ClearElements();
            thane_item_list_provider_.ClearElements();
            champion_item_list_provider_.ClearElements();
        }

        void invalidate_item_lists() {
            faction_item_list_.Invalidate();
            thane_item_list_.Invalidate();
            champion_item_list_.Invalidate();
        }

        void invalidate_data_item_lists() {
            faction_item_list_.InvalidateData();
            thane_item_list_.InvalidateData();
            champion_item_list_.InvalidateData();
        }

        void update_lists() {
            clear_providers();
            invalidate_item_lists();

            update_menu_values();
            update_bottom_values();

            invalidate_data_item_lists();
        }

        void update_bottom() const {
            //in case something is not set, we do not want to see default swf text
            update_text(faction_count_key_, "");
            update_text(thane_count_key_, "");
            update_text(champion_count_key_, "");
            update_text(faction_count_value_, "");
            update_text(thane_count_value_, "");
            update_text(champion_count_value_, "");
        }

        void update_menu_values() const {
            auto values = faction_data::get_singleton()->get_values_to_display();

            logger::debug("Update menu Values, values to proces {}"sv, values.size());
            for (auto& [faction_value, faction_item_ptr] : values) {
                const auto faction_item = faction_item_ptr.get();
                auto faction_menu = faction_item->get_faction_menu();

                faction_item->log_stat_item(faction_value);

                if (faction_item->get_value().empty() || faction_menu == faction_menu_value::m_none) {
                    continue;
                }

                if (faction_item->get_faction_menu() != faction_menu_value::m_none) {
                    auto key_value = faction_item->get_value();
                    menu_map_.find(faction_menu)->second.PushBack(build_gfx_value(faction_item->get_key(),
                        key_value == const_static_display_value ? "" : key_value));
                    logger::trace("added to Menu {}, Name {}, Key {}, value {}"sv,
                        faction_menu,
                        faction_value,
                        faction_item->get_key(),
                        faction_item->get_value());
                }
            }

            for (auto& [fst, snd] : values) { snd.reset(); }
            values.clear();
            logger::debug("Done Updateing Values, Map Size is {}"sv, values.size());
        }

        void update_bottom_values() const {
            update_text(faction_count_key_, menu_keys::count);
            update_text(faction_count_value_,
                format(FMT_STRING("{}"), faction_item_list_provider_.GetArraySize()),
                "right");
            update_text(thane_count_key_, menu_keys::count);
            update_text(thane_count_value_,
                format(FMT_STRING("{}"), thane_item_list_provider_.GetArraySize()),
                "right");
            update_text(champion_count_key_, menu_keys::count);
            update_text(champion_count_value_,
                format(FMT_STRING("{}"), champion_item_list_provider_.GetArraySize()),
                "right");
        }

        static void on_close() { }

        void disable_item_lists() {
            faction_item_list_.Disabled(true);
            thane_item_list_.Disabled(true);
            champion_item_list_.Disabled(true);
        }

        static void close_menu([[maybe_unused]] const RE::FxDelegateArgs& a_params) {
            assert(a_params.GetArgCount() == 0);
            logger::debug("GUI Close Button Pressed"sv);
            close();
        }

        static void prev_menu([[maybe_unused]] const RE::FxDelegateArgs& a_params) {
            assert(a_params.GetArgCount() == 0);
            logger::debug("GUI Prev Button Pressed"sv);
            close();
            process_prev(menu);
        }

        static void log(const RE::FxDelegateArgs& a_params) {
            assert(a_params.GetArgCount() == 1);
            assert(a_params[0].IsString());

            logger::debug("{}: {}"sv, menu_name, a_params[0].GetString());
        }

        static void process_prev(show_menu a_menu);

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

        std::map<faction_menu_value, RE::GFxValue&> menu_map_ = {
            { faction_menu_value::m_faction, faction_item_list_provider_ },
            { faction_menu_value::m_thane, thane_item_list_provider_ },
            { faction_menu_value::m_champion, champion_item_list_provider_ },
        };
    };
}
