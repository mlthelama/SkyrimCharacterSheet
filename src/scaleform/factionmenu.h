#pragma once
#include "CLIK/Array.h"
#include "CLIK/GFx/Controls/ScrollingList.h"
#include "CLIK/TextField.h"

#include "data/factiondata.h"

namespace Scaleform {
    class FactionMenu : public RE::IMenu {
    public:
        static constexpr std::string_view MENU_NAME = "ShowFactions";
        static constexpr std::string_view FILE_NAME = "ShowFactions";


        static void Register() {
            auto ui = RE::UI::GetSingleton();
            ui->Register(MENU_NAME, Creator);

            logger::info("Registered {}"sv, MENU_NAME);
        }

        static void Open() {
            if (!FactionMenu::IsMenuOpen()) {
                logger::debug("Open Menu {}"sv, MENU_NAME);
                auto msgQueue = RE::UIMessageQueue::GetSingleton();
                msgQueue->AddMessage(MENU_NAME, RE::UI_MESSAGE_TYPE::kShow, nullptr);
            }
        }

        static void Close() {
            if (FactionMenu::IsMenuOpen()) {
                logger::debug("Close Menu {}"sv, MENU_NAME);
                auto msgQueue = RE::UIMessageQueue::GetSingleton();
                msgQueue->AddMessage(MENU_NAME, RE::UI_MESSAGE_TYPE::kHide, nullptr);
            }
        }

        static bool IsMenuOpen() {
            auto ui = RE::UI::GetSingleton();
            auto isOpen = ui->IsMenuOpen(MENU_NAME);
            if (isOpen) {
                logger::trace("Menu {} is open {}"sv, MENU_NAME, isOpen);
            }

            return isOpen;
        }


    protected:
        FactionMenu() {
            using Context = RE::UserEvents::INPUT_CONTEXT_ID;
            using Flag = RE::UI_MENU_FLAGS;

            auto menu = static_cast<RE::IMenu*>(this);
            auto scaleformManager = RE::BSScaleformManager::GetSingleton();
            [[maybe_unused]] const auto success =
                scaleformManager->LoadMovieEx(menu, FILE_NAME, RE::BSScaleformManager::ScaleModeType::kExactFit,
                    [](RE::GFxMovieDef* a_def) -> void { logger::trace("FPS: {}"sv, a_def->GetFrameRate()); });
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
            InitExtensions();

            _isActive = true;
            _view->SetVisible(true);
        }

        FactionMenu(const FactionMenu&) = delete;
        FactionMenu(FactionMenu&&) = delete;

        ~FactionMenu() = default;

        FactionMenu& operator=(const FactionMenu&) = delete;
        FactionMenu& operator=(FactionMenu&&) = delete;

        static stl::owner<RE::IMenu*> Creator() { return new FactionMenu(); }

        void PostCreate() override { FactionMenu::OnOpen(); }

        RE::UI_MESSAGE_RESULTS ProcessMessage(RE::UIMessage& a_message) override {
            if (a_message.menu == FactionMenu::MENU_NAME) {
                return RE::UI_MESSAGE_RESULTS::kHandled;
            }
            return RE::UI_MESSAGE_RESULTS::kPassOn;
        }

        void AdvanceMovie(float a_interval, uint32_t a_currentTime) override {
            RE::IMenu::AdvanceMovie(a_interval, a_currentTime);
        }

    private:
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
                element_t{ std::ref(_factionCount), "_root.rootObj.bottomBar.factionCount"sv },
                element_t{ std::ref(_thaneCount), "_root.rootObj.bottomBar.thaneCount"sv },
                element_t{ std::ref(_championCount), "_root.rootObj.bottomBar.championCount"sv },
                element_t{ std::ref(_factionHeader), "_root.rootObj.factionValuesHeader"sv },
                element_t{ std::ref(_thaneHeader), "_root.rootObj.factionThanesHeader"sv },
                element_t{ std::ref(_championHeader), "_root.rootObj.factionChampionHeader"sv },
                element_t{ std::ref(_factionItemList), "_root.rootObj.factionItemList"sv },
                element_t{ std::ref(_thaneItemList), "_root.rootObj.thaneItemList"sv },
                element_t{ std::ref(_championItemList), "_root.rootObj.championItemList"sv },
                element_t{ std::ref(_prev), "_root.rootObj.factionPrevScreen"sv } };

            for (const auto& [object, path] : objects) {
                auto& instance = object.get().GetInstance();
                [[maybe_unused]] const auto success = _view->GetVariable(std::addressof(instance), path.data());
                assert(success && instance.IsObject());
            }

            _rootObj.Visible(false);

            _view->CreateArray(std::addressof(_factionItemListProvider));
            _factionItemList.DataProvider(CLIK::Array{ _factionItemListProvider });

            _view->CreateArray(std::addressof(_thaneItemListProvider));
            _thaneItemList.DataProvider(CLIK::Array{ _thaneItemListProvider });

            _view->CreateArray(std::addressof(_championItemListProvider));
            _championItemList.DataProvider(CLIK::Array{ _championItemListProvider });


            UpdateTitle();
            UpdateHeaders();
            UpdateBottom();

            UpdateLists();

            UpdatePrev();

            _view->SetVisible(true);
            _rootObj.Visible(true);

            logger::debug("Shown all Values for Menu {}"sv, MENU_NAME);
        }

        void updateText(CLIK::TextField p_field, std::string_view p_string) {
            p_field.AutoSize(CLIK::Object{ "left" });
            p_field.HTMLText(p_string);
            p_field.Visible(true);
        }

        void UpdateTitle() { updateText(_title, getMenuName(ShowMenu::mFaction)); }

        void UpdateHeaders() {
            updateText(_factionHeader, static_cast<std::string_view>(*Settings::showFactionsTitleFaction));
            updateText(_thaneHeader, static_cast<std::string_view>(*Settings::showFactionsTitleThane));
            updateText(_championHeader, static_cast<std::string_view>(*Settings::showFactionsTitleChampion));
        }

        RE::GFxValue buildGFxValue(std::string p_val) {
            RE::GFxValue value;
            _view->CreateObject(std::addressof(value));
            value.SetMember("displayName", { static_cast<std::string_view>(p_val) });
            return value;
        }


        void ClearProviders() {
            _factionItemListProvider.ClearElements();
            _thaneItemListProvider.ClearElements();
            _championItemListProvider.ClearElements();
        }

        void InvalidateItemLists() {
            _factionItemList.Invalidate();
            _thaneItemList.Invalidate();
            _championItemList.Invalidate();
        }

        void InvalidateDataItemLists() {
            _factionItemList.InvalidateData();
            _thaneItemList.InvalidateData();
            _championItemList.InvalidateData();
        }

        void UpdateLists() {
            auto factioninfo = FactionData::GetSingleton();

            ClearProviders();
            InvalidateItemLists();

            auto factionValue = factioninfo->getFactionValues();
            for (auto& element : factionValue) {
                if (!element->getShow() || element->getGuiText().empty() || element->getGuiText() == "" ||
                    element->getValue().empty() || element->getValue() == "") {
                    continue;
                }

                logger::trace("processing name {}, displayName {}, menu {}"sv, element->getName(),
                    element->getGuiText(), element->getMenu());

                if (element->getMenu() != FactionMenuValue::mNone) {
                    menuMap.find(element->getMenu())->second.PushBack(buildGFxValue(element->getGuiText()));
                    logger::trace("added to Menu {}, Name {}, GuiText ({})"sv, element->getMenu(), element->getName(),
                        element->getGuiText());
                }
            }


            factionValue.clear();
            for (auto& element : factionValue) { element.reset(); }
            logger::trace("Vector Size is {}"sv, factionValue.size());

            InvalidateDataItemLists();
        }

        void UpdateBottom() {
            //in case something is not set, we do not want to see default swf text
            updateText(_factionCount, "");
            updateText(_thaneCount, "");
            updateText(_championCount, "");
            updateText(_prev, "");
        }

        void UpdatePrev() { updateText(_prev, getPrevMenuName(ShowMenu::mFaction)); }


        RE::GPtr<RE::GFxMovieView> _view;
        bool _isActive = false;

        CLIK::MovieClip _rootObj;
        CLIK::TextField _title;
        CLIK::TextField _prev;

        CLIK::TextField _factionCount;
        CLIK::TextField _thaneCount;
        CLIK::TextField _championCount;

        CLIK::TextField _factionHeader;
        CLIK::TextField _thaneHeader;
        CLIK::TextField _championHeader;

        CLIK::GFx::Controls::ScrollingList _factionItemList;
        RE::GFxValue _factionItemListProvider;

        CLIK::GFx::Controls::ScrollingList _thaneItemList;
        RE::GFxValue _thaneItemListProvider;

        CLIK::GFx::Controls::ScrollingList _championItemList;
        RE::GFxValue _championItemListProvider;

        std::map<FactionMenuValue, RE::GFxValue&> menuMap = {
            { FactionMenuValue::mFaction, _factionItemListProvider },
            { FactionMenuValue::mThane, _thaneItemListProvider },
            { FactionMenuValue::mChampion, _championItemListProvider },
        };
    };
}
