#pragma once
#include "CLIK/Array.h"
#include "CLIK/GFx/Controls/ScrollingList.h"
#include "CLIK/TextField.h"
#include "data/playerdata.h"
#include "CLIK/GFx/Controls/Button.h"

namespace Scaleform {
    using ShowMenu = MenuUtil::ShowMenu;
    using StatsInventoryMenuValue = MenuUtil::StatsInventoryMenuValue;

    class StatsInventoryMenu : public RE::IMenu {
    public:
        static constexpr std::string_view MENU_NAME = "ShowStatsInventory";
        static constexpr std::string_view FILE_NAME = MENU_NAME;

        static void Register() {
            RE::UI::GetSingleton()->Register(MENU_NAME, Creator);
            logger::info("Registered {}"sv, MENU_NAME);
        }

        static void Open() {
            if (!StatsInventoryMenu::IsMenuOpen()) {
                logger::debug("Open Menu {}"sv, MENU_NAME);
                RE::UIMessageQueue::GetSingleton()->AddMessage(MENU_NAME, RE::UI_MESSAGE_TYPE::kShow, nullptr);
            }
        }

        static void Close() {
            if (StatsInventoryMenu::IsMenuOpen()) {
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

        void RefreshLists() {
            if (IsMenuOpen()) {
                UpdateLists();
            }
        }

    protected:
        StatsInventoryMenu() {
            using Context = RE::UserEvents::INPUT_CONTEXT_ID;
            using Flag = RE::UI_MENU_FLAGS;

            auto menu = static_cast<RE::IMenu*>(this);
            auto scaleformManager = RE::BSScaleformManager::GetSingleton();
            [[maybe_unused]] const auto success = scaleformManager->LoadMovieEx(menu,
                FILE_NAME,
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
            MenuUtil::logResolution();
            logger::debug("Loading Menu {} was successful {}"sv, FILE_NAME, success);
            assert(success);
            _view = menu->uiMovie;
            //_view->SetMouseCursorCount(0);
            menu->menuFlags |= Flag::kUsesCursor;

            //menu->depthPriority = 0;
            //menu->inputContext = Context::kNone;

            InitExtensions();

            _isActive = true;
            _view->SetVisible(true);
        }

        StatsInventoryMenu(const StatsInventoryMenu&) = delete;
        StatsInventoryMenu(StatsInventoryMenu&&) = delete;

        ~StatsInventoryMenu() = default;

        StatsInventoryMenu& operator=(const StatsInventoryMenu&) = delete;
        StatsInventoryMenu& operator=(StatsInventoryMenu&&) = delete;

        static stl::owner<RE::IMenu*> Creator() { return new StatsInventoryMenu(); }

        void PostCreate() override { StatsInventoryMenu::OnOpen(); }

        //might not work that well if InventoryMenu is open
        RE::UI_MESSAGE_RESULTS ProcessMessage(RE::UIMessage& a_message) override {
            /*switch (*a_message.type) {
                case RE::UI_MESSAGE_TYPE::kHide:
                    OnClose();
                    return RE::UI_MESSAGE_RESULTS::kHandled;
                default:
                    return RE::IMenu::ProcessMessage(a_message);
            }*/

            if (a_message.menu == StatsInventoryMenu::MENU_NAME) {
                return RE::UI_MESSAGE_RESULTS::kHandled;
            }
            return RE::UI_MESSAGE_RESULTS::kPassOn;
        }

        void AdvanceMovie(float a_interval, uint32_t a_currentTime) override {
            RE::IMenu::AdvanceMovie(a_interval, a_currentTime);
        }

        void Accept(CallbackProcessor* a_processor) override {
            a_processor->Process("Log", Log);
            a_processor->Process("CloseMenu", CloseMenu);
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

                logger::info("{}: {}"sv, StatsInventoryMenu::MENU_NAME, buf.data());
            }
        };

        void InitExtensions() {
            const RE::GFxValue boolean(true);
            bool success;

            success = _view->SetVariable("_global.gfxExtensions", boolean);
            assert(success);
            /*success = _view->SetVariable("_global.noInvisibleAdvance", boolean);
            assert(success);*/
        }

        void OnOpen() {
            using element_t = std::pair<std::reference_wrapper<CLIK::Object>, std::string_view>;
            std::array objects{ element_t{ std::ref(_rootObj), "_root.rootObj"sv },
                element_t{ std::ref(_equipHeader), "_root.rootObj.inventoryEquipHeader"sv },
                element_t{ std::ref(_armorHeader), "_root.rootObj.inventoryArmorHeader"sv },
                element_t{ std::ref(_weaponHeader), "_root.rootObj.inventoryWeaponHeader"sv },
                element_t{ std::ref(_effectHeader), "_root.rootObj.inventoryEffectHeader"sv },
                element_t{ std::ref(_equipItemList), "_root.rootObj.equipItemList"sv },
                element_t{ std::ref(_armorItemList), "_root.rootObj.armorItemList"sv },
                element_t{ std::ref(_weaponItemList), "_root.rootObj.weaponItemList"sv },
                element_t{ std::ref(_effectItemList), "_root.rootObj.effectItemList"sv },
                element_t{ std::ref(_menuClose), "_root.rootObj.menuClose"sv } 
            };

            for (const auto& [object, path] : objects) {
                auto& instance = object.get().GetInstance();
                [[maybe_unused]] const auto success = _view->GetVariable(std::addressof(instance), path.data());
                assert(success && instance.IsObject());
            }
            logger::debug("Loaded all SWF objects successfully for {}"sv, MENU_NAME);

            _rootObj.Visible(false);

            _view->CreateArray(std::addressof(_equipItemListProvider));
            _equipItemList.DataProvider(CLIK::Array{ _equipItemListProvider });

            _view->CreateArray(std::addressof(_armorItemListProvider));
            _armorItemList.DataProvider(CLIK::Array{ _armorItemListProvider });

            _view->CreateArray(std::addressof(_weaponItemListProvider));
            _weaponItemList.DataProvider(CLIK::Array{ _weaponItemListProvider });

            _view->CreateArray(std::addressof(_effectItemListProvider));
            _effectItemList.DataProvider(CLIK::Array{ _effectItemListProvider });

            _menuClose.Label("Close");
            _menuClose.Disabled(false);
            _menuClose.Visible(false); //for now 

            UpdateHeaders();

            UpdateLists();

            _view->SetVisible(true);
            _rootObj.Visible(true);
            
            DisableItemLists();

            logger::debug("Shown all Values for Menu {}"sv, MENU_NAME);
        }

        void UpdateText(CLIK::TextField a_field, std::string_view a_string) {
            a_field.AutoSize(CLIK::Object{ "left" });
            a_field.HTMLText(a_string);
            a_field.Visible(true);
        }

        void UpdateHeaders() {
            UpdateText(_equipHeader, static_cast<std::string_view>(*Settings::showStatsInventoryTitleEquip));
            UpdateText(_armorHeader, static_cast<std::string_view>(*Settings::showStatsInventoryTitleArmor));
            UpdateText(_weaponHeader, static_cast<std::string_view>(*Settings::showStatsInventoryTitleWeapon));
            UpdateText(_effectHeader, static_cast<std::string_view>(*Settings::showStatsInventoryTitleEffect));
        }

        RE::GFxValue buildGFxValue(std::string a_val) {
            RE::GFxValue value;
            _view->CreateObject(std::addressof(value));
            value.SetMember("displayName", { static_cast<std::string_view>(a_val) });
            return value;
        }

        void ClearProviders() {
            _equipItemListProvider.ClearElements();
            _armorItemListProvider.ClearElements();
            _weaponItemListProvider.ClearElements();
            _effectItemListProvider.ClearElements();
        }

        void InvalidateItemLists() {
            _equipItemList.Invalidate();
            _armorItemList.Invalidate();
            _weaponItemList.Invalidate();
            _effectItemList.Invalidate();
        }

        void InvalidateDataItemLists() {
            _equipItemList.InvalidateData();
            _armorItemList.InvalidateData();
            _weaponItemList.InvalidateData();
            _effectItemList.InvalidateData();
        }

        void UpdateLists() {
            ClearProviders();
            InvalidateItemLists();

            UpdateMenuValues();

            InvalidateDataItemLists();
        }

        void UpdateMenuValues() {
            auto values = PlayerData::GetSingleton()->getValuesToDisplay(_menu, MENU_NAME);
            logger::debug("Update menu Values, values to proces {}"sv, values.size());

            for (auto& element : values) {
                auto statValue = element.first;
                auto statItem = element.second.get();

                statItem->logStatItem(statValue, _menu);

                if (statItem->getGuiText().empty() || statItem->getGuiText() == "" ||
                    statItem->getStatsInventoryMenu() == StatsInventoryMenuValue::mNone ||
                    statItem->getStatsInventoryMenu() == StatsInventoryMenuValue::mEquip) {
                    continue;
                }

                _menuMap.find(statItem->getStatsInventoryMenu())
                    ->second.PushBack(buildGFxValue(statItem->getGuiText()));
                logger::trace("added to Menu {}, Name {}, GuiText ({})"sv,
                    statItem->getStatsInventoryMenu(),
                    statValue,
                    statItem->getGuiText());
            }
            for (auto& element : values) { element.second.reset(); }
            values.clear();

            //it seems the inventory needs a bit after an equipchange, so an item might be shown equiped
            //might need implement skse taskinterface
            auto armor = PlayerData::GetSingleton()->getArmorMap();
            for (auto item : armor) {
                _menuMap.find(StatsInventoryMenuValue::mEquip)
                    ->second.PushBack(buildGFxValue(fmt::format(FMT_STRING("{}: {}"), item.first, item.second)));
            }

            logger::debug("Done Updateing Values, Map Size is {}"sv, values.size());
        }

        void OnClose() { return; }

        void DisableItemLists() {
            _equipItemList.Disabled(true);
            _armorItemList.Disabled(true);
            _weaponItemList.Disabled(true);
            _effectItemList.Disabled(true);
        }

        static void CloseMenu([[maybe_unused]] const RE::FxDelegateArgs& a_params) {
            assert(a_params.GetArgCount() == 0);
            logger::debug("GUI Close Button Pressed"sv);
            Close();
        }

        static void Log(const RE::FxDelegateArgs& a_params) {
            assert(a_params.GetArgCount() == 1);
            assert(a_params[0].IsString());

            logger::debug("{}: {}"sv, StatsInventoryMenu::MENU_NAME, a_params[0].GetString());
        }

        RE::GPtr<RE::GFxMovieView> _view;
        bool _isActive = false;

        CLIK::MovieClip _rootObj;

        CLIK::TextField _equipHeader;
        CLIK::TextField _armorHeader;
        CLIK::TextField _weaponHeader;
        CLIK::TextField _effectHeader;

        CLIK::GFx::Controls::ScrollingList _equipItemList;
        RE::GFxValue _equipItemListProvider;

        CLIK::GFx::Controls::ScrollingList _armorItemList;
        RE::GFxValue _armorItemListProvider;

        CLIK::GFx::Controls::ScrollingList _weaponItemList;
        RE::GFxValue _weaponItemListProvider;

        CLIK::GFx::Controls::ScrollingList _effectItemList;
        RE::GFxValue _effectItemListProvider;

        CLIK::GFx::Controls::Button _menuClose;

        std::map<StatsInventoryMenuValue, RE::GFxValue&> _menuMap = {
            { StatsInventoryMenuValue::mEquip, _equipItemListProvider },
            { StatsInventoryMenuValue::mArmor, _armorItemListProvider },
            { StatsInventoryMenuValue::mWeapon, _weaponItemListProvider },
            { StatsInventoryMenuValue::mEffect, _effectItemListProvider },
        };

        ShowMenu _menu = ShowMenu::mStatsInventory;
    };
}
