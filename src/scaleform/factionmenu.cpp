#pragma once
#include "scaleform/factionmenu.h"
#include "data/factiondata.h"

namespace Scaleform {
    RE::IMenu* FactionMenu::Creator() { return new FactionMenu(); }

    void FactionMenu::Register() {
        auto ui = RE::UI::GetSingleton();
        ui->Register(MENU_NAME, Creator);

        logger::info("Registered {}"sv, MENU_NAME);
    }

    void FactionMenu::Open() {
        if (!FactionMenu::IsMenuOpen()) {
            logger::debug("Open Menu {}"sv, MENU_NAME);
            auto msgQueue = RE::UIMessageQueue::GetSingleton();
            msgQueue->AddMessage(MENU_NAME, RE::UI_MESSAGE_TYPE::kShow, nullptr);
        }
    }


    void FactionMenu::Close() {
        if (FactionMenu::IsMenuOpen()) {
            logger::debug("Close Menu {}"sv, MENU_NAME);
            auto msgQueue = RE::UIMessageQueue::GetSingleton();
            msgQueue->AddMessage(MENU_NAME, RE::UI_MESSAGE_TYPE::kHide, nullptr);
        }
    }

    FactionMenu::FactionMenu() {
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
        menu->menuFlags |= Flag::kAllowSaving;
        menu->depthPriority = 11;
        menu->inputContext = Context::kNone;
        InitExtensions();

        _isActive = true;
        _view->SetVisible(true);
    }

    void FactionMenu::AdvanceMovie(float a_interval, uint32_t a_currentTime) {
        auto currentFrame = _view->GetCurrentFrame();

        logger::trace("interval {}, currenttime {}"sv, a_interval, a_currentTime);

        _view->SetVisible(true);

        auto nextFrame = currentFrame == 120 ? 1 : currentFrame + 1;
        _view->GotoFrame(nextFrame);
    }

    RE::UI_MESSAGE_RESULTS FactionMenu::ProcessMessage(RE::UIMessage& a_message) {
        if (a_message.menu == FactionMenu::MENU_NAME) {
            return RE::UI_MESSAGE_RESULTS::kHandled;
        }
        return RE::UI_MESSAGE_RESULTS::kPassOn;
    }

    void FactionMenu::InitExtensions() {
        const RE::GFxValue boolean(true);
        bool success;

        success = _view->SetVariable("_global.gfxExtensions", boolean);
        assert(success);
        success = _view->SetVariable("_global.noInvisibleAdvance", boolean);
        assert(success);
    }

    bool FactionMenu::IsMenuOpen() {
        auto ui = RE::UI::GetSingleton();
        auto isOpen = ui->IsMenuOpen(MENU_NAME);

        logger::trace("Menu {} is open {}"sv, MENU_NAME, isOpen);

        return isOpen;
    }

    void FactionMenu::PostCreate() { FactionMenu::OnOpen(); }

    void FactionMenu::OnOpen() {
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
            element_t{ std::ref(_championItemList), "_root.rootObj.championItemList"sv } };

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
        updateBottom();

        UpdateLists();

        _view->SetVisible(true);
        _rootObj.Visible(true);

        logger::debug("Shown all Values for Menu {}"sv, MENU_NAME);
    }

    void FactionMenu::updateText(CLIK::TextField p_field, std::string_view p_string) {
        p_field.AutoSize(CLIK::Object{ "left" });
        p_field.HTMLText(p_string);
        p_field.Visible(true);
    }

    void FactionMenu::UpdateTitle() { updateText(_title, TITLE_NAME_FACTIONS); }

    void FactionMenu::UpdateHeaders() {
        updateText(_factionHeader, headerFactionName);
        updateText(_thaneHeader, headerThaneName);
        updateText(_championHeader, headerChampionName);
    }

    RE::GFxValue FactionMenu::buildGFxValue(std::string p_val) {
        RE::GFxValue value;
        _view->CreateObject(std::addressof(value));
        value.SetMember("displayName", { static_cast<std::string_view>(p_val) });
        return value;
    }

    void FactionMenu::ClearProviders() {
        _factionItemListProvider.ClearElements();
        _thaneItemListProvider.ClearElements();
        _championItemListProvider.ClearElements();
    }

    void FactionMenu::InvalidateItemLists() {
        _factionItemList.Invalidate();
        _thaneItemList.Invalidate();
        _championItemList.Invalidate();
    }

    void FactionMenu::InvalidateDataItemLists() {
        _factionItemList.InvalidateData();
        _thaneItemList.InvalidateData();
        _championItemList.InvalidateData();
    }

    void FactionMenu::UpdateLists() {
        auto factioninfo = FactionData::GetSingleton();

        ClearProviders();
        InvalidateItemLists();

        auto factionValue = factioninfo->getFactionValues();
        for (auto& element : factionValue) {
            if (!element->getShow() || element->getGuiText().empty() || element->getGuiText() == "" ||
                element->getValue().empty() || element->getValue() == "") {
                continue;
            }

            logger::trace("processing name {}, displayName {}, menu {}"sv, element->getName(), element->getGuiText(),
                element->getMenu());
            switch (element->getName()) {
                case FactionValue::darkbrotherHood:
                case FactionValue::thiefsGuild:
                case FactionValue::orcFriend:
                case FactionValue::collegeOfWinterhold:
                case FactionValue::companions:
                case FactionValue::imperialLegion:
                case FactionValue::stormcloaks:
                case FactionValue::greybeard:
                case FactionValue::bard:
                case FactionValue::volkiharVampireClan:
                case FactionValue::dawnguard:
                case FactionValue::houseTelvanni:
                case FactionValue::thaneOfEastmarch:
                case FactionValue::thaneOfFalkreath:
                case FactionValue::thaneOfHaafingar:
                case FactionValue::thaneOfHjaalmarch:
                case FactionValue::thaneOfThePale:
                case FactionValue::thaneOfTheReach:
                case FactionValue::thaneOfTheRift:
                case FactionValue::thaneOfWhiterun:
                case FactionValue::thaneOfWinterhold:
                    if (element->getMenu() != FactionMenuValue::mNone) {
                        menuMap.find(element->getMenu())->second.PushBack(buildGFxValue(element->getGuiText()));
                        logger::trace("added to Menu {}, Name {}, GuiText ({})"sv, element->getMenu(),
                            element->getName(), element->getGuiText());
                    }
                    break;
                default:
                    logger::warn("not handeled name {}, displayName {}"sv, element->getName(), element->getGuiText());
                    break;
            }

        }


        factionValue.clear();
        for (auto& element : factionValue) { element.reset(); }
        logger::trace("Vector Size is {}"sv, factionValue.size());

        InvalidateDataItemLists();
    }

    void FactionMenu::updateBottom() {
        //in case something is not set, we do not want to see default swf text
        updateText(_factionCount, "");
        updateText(_thaneCount, "");
        updateText(_championCount, "");
    }

}