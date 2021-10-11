#pragma once
#include "CLIK/Array.h"
#include "CLIK/GFx/Controls/ScrollingList.h"
#include "CLIK/TextField.h"

namespace Scaleform {
    class FactionMenu : public RE::IMenu {
    public:
        static constexpr std::string_view MENU_NAME = "ShowFactions";
        static constexpr std::string_view FILE_NAME = "ShowFactions";
        static constexpr std::string_view TITLE_NAME = "$ShowFactions";

        void AdvanceMovie(float a_interval, uint32_t a_currentTime) override;
        RE::UI_MESSAGE_RESULTS ProcessMessage(RE::UIMessage& a_message) override;

        void InitExtensions();

        static RE::IMenu* Creator();

        static void Register();

        static void Open();

        static void Close();

        static bool IsMenuOpen();

        void PostCreate() override;


        FactionMenu(const FactionMenu&) = delete;
        FactionMenu(FactionMenu&&) = delete;

        ~FactionMenu() = default;

        FactionMenu& operator=(const FactionMenu&) = delete;
        FactionMenu& operator=(FactionMenu&&) = delete;

    private:
        FactionMenu();

        RE::GPtr<RE::GFxMovieView> _view;
        bool _isActive = false;

        CLIK::MovieClip _rootObj;
        CLIK::TextField _title;

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

        void OnOpen();

        void updateText(CLIK::TextField p_field, std::string_view p_string);

        void UpdateTitle();

        void UpdateHeaders();

        RE::GFxValue buildGFxValue(std::string p_val);

        void ClearProviders();

        void InvalidateItemLists();

        void InvalidateDataItemLists();

        void UpdateLists();

        void updateBottom();
    };
}
