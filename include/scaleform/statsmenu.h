#pragma once
#include "CLIK/Array.h"
#include "CLIK/GFx/Controls/ScrollingList.h"
#include "CLIK/TextField.h"
#include "constants.h"

namespace Scaleform
{
	class StatsMenu : public RE::IMenu
	{
	public:
		static constexpr string_view MENU_NAME = "ShowStats";
		static constexpr string_view FILE_NAME = "ShowStats";
		static constexpr string_view TITLE_NAME = "$ShowStats";

		void AdvanceMovie(float a_interval, uint32_t a_currentTime) override;
		RE::UI_MESSAGE_RESULTS ProcessMessage(RE::UIMessage& a_message) override;

		void InitExtensions();

		static RE::IMenu* Creator();

		static void Register();

		static void Open();

		static void Close();

		static bool IsMenuOpen();

		void PostCreate() override;


		StatsMenu(const StatsMenu&) = delete;
		StatsMenu(StatsMenu&&) = delete;

		~StatsMenu() = default;

		StatsMenu& operator=(const StatsMenu&) = delete;
		StatsMenu& operator=(StatsMenu&&) = delete;
	private:
		StatsMenu();

		RE::GPtr<RE::GFxMovieView> _view;
		bool _isActive = false;

		CLIK::MovieClip _rootObj;
		CLIK::TextField _title;

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

		map<MenuValue, RE::GFxValue&> menuMap = {
			{ MenuValue::mPlayer, _playerItemListProvider },
			{ MenuValue::mDefence, _defenceItemListProvider },
			{ MenuValue::mAttack, _attackItemListProvider },
			{ MenuValue::mMagic, _perksMagicItemListProvider },
			{ MenuValue::mWarrior, _perksWarriorItemListProvider },
			{ MenuValue::mThief, _perksThiefItemListProvider },
		};

		void OnOpen();

		void updateText(CLIK::TextField p_field, string_view p_string);

		void UpdateTitle();

		void UpdateHeaders();

		RE::GFxValue buildGFxValue(string p_val);

		void ClearProviders();

		void InvalidateItemLists();

		void InvalidateDataItemLists();

		void UpdateLists();

		void updateBottom();
	};
}