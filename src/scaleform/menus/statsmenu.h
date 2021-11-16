#pragma once
#include "CLIK/Array.h"
#include "CLIK/GFx/Controls/ScrollingList.h"
#include "CLIK/TextField.h"
#include "data/playerdata.h"

namespace Scaleform {
    using StatsMenuValue = MenuUtil::StatsMenuValue;
    using ShowMenu = MenuUtil::ShowMenu;

    class StatsMenu : public RE::IMenu {
    public:
        static constexpr std::string_view MENU_NAME = "ShowStats";
        static constexpr std::string_view FILE_NAME = MENU_NAME;

        static void Register() {
            RE::UI::GetSingleton()->Register(MENU_NAME, Creator);
            logger::info("Registered {}"sv, MENU_NAME);
        }

        static void Open() {
            if (!StatsMenu::IsMenuOpen()) {
                logger::debug("Open Menu {}"sv, MENU_NAME);
                RE::UIMessageQueue::GetSingleton()->AddMessage(MENU_NAME, RE::UI_MESSAGE_TYPE::kShow, nullptr);
            }
        }

        static void Close() {
            if (StatsMenu::IsMenuOpen()) {
                logger::debug("Close Menu {}"sv, MENU_NAME);
                RE::UIMessageQueue::GetSingleton()->AddMessage(MENU_NAME, RE::UI_MESSAGE_TYPE::kHide, nullptr);
            }
        }

        static bool IsMenuOpen() {
            auto isOpen = RE::UI::GetSingleton()->IsMenuOpen(MENU_NAME);
            if (isOpen) {
                logger::trace("Menu {} is open {}"sv, MENU_NAME, isOpen);
            }
            return isOpen;
        }

    protected:
        StatsMenu() {
            using Context = RE::UserEvents::INPUT_CONTEXT_ID;
            using Flag = RE::UI_MENU_FLAGS;

            auto menu = static_cast<RE::IMenu*>(this);
            auto scaleformManager = RE::BSScaleformManager::GetSingleton();
            [[maybe_unused]] const auto success = scaleformManager->LoadMovieEx(menu,
                FILE_NAME,
                RE::BSScaleformManager::ScaleModeType::kExactFit,
                [](RE::GFxMovieDef* a_def) -> void {
                    logger::trace("SWF FPS: {}, Width: {}, Height: {}"sv,
                        a_def->GetFrameRate(),
                        a_def->GetWidth(),
                        a_def->GetHeight());
                    a_def->SetState(RE::GFxState::StateType::kLog, RE::make_gptr<Logger>().get());
                });
            MenuUtil::logResolution();
            logger::debug("Loading Menu {} was successful {}"sv, FILE_NAME, success);
            assert(success);
            _view = menu->uiMovie;
            _view->SetMouseCursorCount(0);
            if (*Settings::pauseGame) {
                menu->menuFlags |= Flag::kPausesGame;
            } else {
                menu->menuFlags |= Flag::kAllowSaving;
            }
            menu->depthPriority = 0;
            menu->inputContext = Context::kNone;
            //InitExtensions();

            _isActive = true;
            _view->SetVisible(true);
        }

        StatsMenu(const StatsMenu&) = delete;
        StatsMenu(StatsMenu&&) = delete;

        ~StatsMenu() = default;

        StatsMenu& operator=(const StatsMenu&) = delete;
        StatsMenu& operator=(StatsMenu&&) = delete;

        static stl::owner<RE::IMenu*> Creator() { return new StatsMenu(); }

        void PostCreate() override { StatsMenu::OnOpen(); }

        RE::UI_MESSAGE_RESULTS ProcessMessage(RE::UIMessage& a_message) override {
            if (a_message.menu == StatsMenu::MENU_NAME) {
                return RE::UI_MESSAGE_RESULTS::kHandled;
            }
            return RE::UI_MESSAGE_RESULTS::kPassOn;
        }

        void AdvanceMovie(float a_interval, uint32_t a_currentTime) override {
            RE::IMenu::AdvanceMovie(a_interval, a_currentTime);
        }

    private:
        class Logger : public RE::GFxLog {
        public:
            void LogMessageVarg(LogMessageType, const char* a_fmt, std::va_list a_argList) override {
                std::string fmt(a_fmt ? a_fmt : "");
                while (!fmt.empty() && fmt.back() == '\n') { fmt.pop_back(); }

                std::va_list args;
                va_copy(args, a_argList);
                std::vector<char> buf(static_cast<std::size_t>(std::vsnprintf(0, 0, fmt.c_str(), a_argList) + 1));
                std::vsnprintf(buf.data(), buf.size(), fmt.c_str(), args);
                va_end(args);

                logger::info("{}: {}"sv, StatsMenu::MENU_NAME, buf.data());
            }
        };

        void InitExtensions() {
            const RE::GFxValue boolean(true);
            bool success;

            success = _view->SetVariable("_global.gfxExtensions", boolean);
            assert(success);
            success = _view->SetVariable("_global.noInvisibleAdvance", boolean);
            assert(success);
        }

        void OnOpen() {
            using element_t = std::pair<std::reference_wrapper<CLIK::Object>, std::string_view>;
            std::array objects{ element_t{ std::ref(_rootObj), "_root.rootObj"sv },
                element_t{ std::ref(_title), "_root.rootObj.title"sv },
                element_t{ std::ref(_name), "_root.rootObj.bottomBar.name"sv },
                element_t{ std::ref(_level), "_root.rootObj.bottomBar.level"sv },
                element_t{ std::ref(_race), "_root.rootObj.bottomBar.race"sv },
                element_t{ std::ref(_perks), "_root.rootObj.bottomBar.perks"sv },
                element_t{ std::ref(_beast), "_root.rootObj.bottomBar.beast"sv },
                element_t{ std::ref(_xp), "_root.rootObj.bottomBar.xp"sv },
                element_t{ std::ref(_valuesHeader), "_root.rootObj.playerValuesHeader"sv },
                element_t{ std::ref(_attackHeader), "_root.rootObj.playerAttackHeader"sv },
                element_t{ std::ref(_perksMagicHeader), "_root.rootObj.playerPerksMagicHeader"sv },
                element_t{ std::ref(_defenceHeader), "_root.rootObj.playerDefenceHeader"sv },
                element_t{ std::ref(_perksWarriorHeader), "_root.rootObj.playerPerksWarriorHeader"sv },
                element_t{ std::ref(_perksThiefHeader), "_root.rootObj.playerPerksThiefHeader"sv },
                element_t{ std::ref(_playerItemList), "_root.rootObj.playerItemList"sv },
                element_t{ std::ref(_defenceItemList), "_root.rootObj.defenceItemList"sv },
                element_t{ std::ref(_attackItemList), "_root.rootObj.attackItemList"sv },
                element_t{ std::ref(_perksMagicItemList), "_root.rootObj.perksMagicItemList"sv },
                element_t{ std::ref(_perksWarriorItemList), "_root.rootObj.perksWarriorItemList"sv },
                element_t{ std::ref(_perksThiefItemList), "_root.rootObj.perksThiefItemList"sv },
                element_t{ std::ref(_next), "_root.rootObj.playerNextScreen"sv } };

            for (const auto& [object, path] : objects) {
                auto& instance = object.get().GetInstance();
                [[maybe_unused]] const auto success = _view->GetVariable(std::addressof(instance), path.data());
                assert(success && instance.IsObject());
            }
            logger::debug("Loaded all SWF objects successfully"sv);

            _rootObj.Visible(false);

            _view->CreateArray(std::addressof(_playerItemListProvider));
            _playerItemList.DataProvider(CLIK::Array{ _playerItemListProvider });

            _view->CreateArray(std::addressof(_defenceItemListProvider));
            _defenceItemList.DataProvider(CLIK::Array{ _defenceItemListProvider });

            _view->CreateArray(std::addressof(_attackItemListProvider));
            _attackItemList.DataProvider(CLIK::Array{ _attackItemListProvider });

            _view->CreateArray(std::addressof(_perksMagicItemListProvider));
            _perksMagicItemList.DataProvider(CLIK::Array{ _perksMagicItemListProvider });

            _view->CreateArray(std::addressof(_perksWarriorItemListProvider));
            _perksWarriorItemList.DataProvider(CLIK::Array{ _perksWarriorItemListProvider });

            _view->CreateArray(std::addressof(_perksThiefItemListProvider));
            _perksThiefItemList.DataProvider(CLIK::Array{ _perksThiefItemListProvider });

            UpdateTitle();
            UpdateHeaders();
            UpdateBottom();

            UpdateLists();

            UpdateNext();

            _view->SetVisible(true);
            _rootObj.Visible(true);

            logger::debug("Shown all Values for Menu {}"sv, MENU_NAME);
        }

        void UpdateText(CLIK::TextField a_field, std::string_view a_string) {
            a_field.AutoSize(CLIK::Object{ "left" });
            a_field.HTMLText(a_string);
            a_field.Visible(true);
        }

        void UpdateTitle() { UpdateText(_title, MenuUtil::getMenuName(_menu)); }

        void UpdateHeaders() {
            UpdateText(_valuesHeader, static_cast<std::string_view>(*Settings::showStatsTitlePlayer));
            UpdateText(_attackHeader, static_cast<std::string_view>(*Settings::showStatsTitleAttack));
            UpdateText(_perksMagicHeader, static_cast<std::string_view>(*Settings::showStatsTitleMagic));
            UpdateText(_defenceHeader, static_cast<std::string_view>(*Settings::showStatsTitleDefence));
            UpdateText(_perksWarriorHeader, static_cast<std::string_view>(*Settings::showStatsTitleWarrior));
            UpdateText(_perksThiefHeader, static_cast<std::string_view>(*Settings::showStatsTitleThief));
        }

        RE::GFxValue buildGFxValue(std::string a_val) {
            RE::GFxValue value;
            _view->CreateObject(std::addressof(value));
            value.SetMember("displayName", { static_cast<std::string_view>(a_val) });
            return value;
        }

        void ClearProviders() {
            _playerItemListProvider.ClearElements();
            _defenceItemListProvider.ClearElements();
            _attackItemListProvider.ClearElements();
            _perksMagicItemListProvider.ClearElements();
            _perksWarriorItemListProvider.ClearElements();
            _perksThiefItemListProvider.ClearElements();
        }

        void InvalidateItemLists() {
            _playerItemList.Invalidate();
            _defenceItemList.Invalidate();
            _attackItemList.Invalidate();
            _perksMagicItemList.Invalidate();
            _perksWarriorItemList.Invalidate();
            _perksThiefItemList.Invalidate();
        }

        void InvalidateDataItemLists() {
            _playerItemList.InvalidateData();
            _defenceItemList.InvalidateData();
            _attackItemList.InvalidateData();
            _perksMagicItemList.InvalidateData();
            _perksWarriorItemList.InvalidateData();
            _perksThiefItemList.InvalidateData();
        }

        void UpdateLists() {
            ClearProviders();
            InvalidateItemLists();

            UpdateMenuValues();

            InvalidateDataItemLists();
        }

        void UpdateBottom() {
            //in case something is not set, we do not want to see default swf text
            UpdateText(_name, "");
            UpdateText(_level, "");
            UpdateText(_race, "");
            UpdateText(_perks, "");
            UpdateText(_beast, "");
            UpdateText(_xp, "");
            UpdateText(_next, "");
        }

        void UpdateNext() { UpdateText(_next, MenuUtil::getNextMenuName(_menu)); }

        void UpdateMenuValues() {
            auto values = PlayerData::GetSingleton()->getValuesToDisplay(_menu);
            logger::debug("Update menu Values, values to proces {}"sv, values.size());

            for (auto& element : values) {
                auto statValue = element.first;
                auto statItem = element.second.get();

                statItem->logStatItem(statValue, _menu);

                if (statItem->getGuiText().empty() || statItem->getGuiText() == "" ||
                    statItem->getStatsMenu() == StatsMenuValue::mNone) {
                    continue;
                }

                switch (statValue) {
                    case StatsValue::name:
                        UpdateText(_name, statItem->getGuiText());
                        break;
                    case StatsValue::level:
                        UpdateText(_level, statItem->getGuiText());
                        break;
                    case StatsValue::race:
                        UpdateText(_race, statItem->getGuiText());
                        break;
                    case StatsValue::perkCount:
                        UpdateText(_perks, statItem->getGuiText());
                        break;
                    case StatsValue::beast:
                        UpdateText(_beast, statItem->getGuiText());
                        break;
                    case StatsValue::xp:
                        UpdateText(_xp, statItem->getGuiText());
                        break;
                    default:
                        if (statItem->getStatsMenu() != StatsMenuValue::mSpecial) {
                            _menuMap.find(statItem->getStatsMenu())
                                ->second.PushBack(buildGFxValue(statItem->getGuiText()));
                            logger::trace("added to Menu {}, Name {}, GuiText ({})"sv,
                                statItem->getStatsMenu(),
                                statValue,
                                statItem->getGuiText());
                        }
                        break;
                }
            }
            for (auto& element : values) { element.second.reset(); }
            values.clear();
            logger::debug("Done Updateing Values, Map Size is {}"sv, values.size());
        }

        RE::GPtr<RE::GFxMovieView> _view;
        bool _isActive = false;

        CLIK::MovieClip _rootObj;
        CLIK::TextField _title;
        CLIK::TextField _next;

        CLIK::TextField _name;
        CLIK::TextField _level;
        CLIK::TextField _race;
        CLIK::TextField _perks;
        CLIK::TextField _beast;
        CLIK::TextField _xp;

        CLIK::TextField _valuesHeader;
        CLIK::TextField _attackHeader;
        CLIK::TextField _perksMagicHeader;
        CLIK::TextField _defenceHeader;
        CLIK::TextField _perksWarriorHeader;
        CLIK::TextField _perksThiefHeader;

        CLIK::GFx::Controls::ScrollingList _playerItemList;
        RE::GFxValue _playerItemListProvider;

        CLIK::GFx::Controls::ScrollingList _defenceItemList;
        RE::GFxValue _defenceItemListProvider;

        CLIK::GFx::Controls::ScrollingList _attackItemList;
        RE::GFxValue _attackItemListProvider;

        CLIK::GFx::Controls::ScrollingList _perksMagicItemList;
        RE::GFxValue _perksMagicItemListProvider;

        CLIK::GFx::Controls::ScrollingList _perksWarriorItemList;
        RE::GFxValue _perksWarriorItemListProvider;

        CLIK::GFx::Controls::ScrollingList _perksThiefItemList;
        RE::GFxValue _perksThiefItemListProvider;

        std::map<StatsMenuValue, RE::GFxValue&> _menuMap = {
            { StatsMenuValue::mPlayer, _playerItemListProvider },
            { StatsMenuValue::mDefence, _defenceItemListProvider },
            { StatsMenuValue::mAttack, _attackItemListProvider },
            { StatsMenuValue::mMagic, _perksMagicItemListProvider },
            { StatsMenuValue::mWarrior, _perksWarriorItemListProvider },
            { StatsMenuValue::mThief, _perksThiefItemListProvider },
        };

        ShowMenu _menu = ShowMenu::mStats;
    };
}
