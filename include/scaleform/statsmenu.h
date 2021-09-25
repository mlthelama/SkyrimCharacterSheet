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
		static constexpr std::string_view MENU_NAME = "ShowStats";
		static constexpr std::string_view FILE_NAME = "ShowStats";
		static constexpr std::string_view TITLE_NAME = "$ShowStats";

		void AdvanceMovie(float a_interval, std::uint32_t a_currentTime) override;
		RE::UI_MESSAGE_RESULTS ProcessMessage(RE::UIMessage& a_message) override;

		void InitExtensions();

		static RE::IMenu* Creator();

		static void Register();

		static void Open();

		static void Close();

		static bool IsMenuOpen();

		void PostCreate() override;
	private:
		StatsMenu();

		using Stats = constants::StatsValue;

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

		void OnOpen();

		void updateText(CLIK::TextField p_field, std::string_view p_string);

		std::string buildText(std::string p_key, std::string p_value, std::string p_ending);

		void UpdateTitle();

		void UpdateHeaders();

		RE::GFxValue buildGFxValue(std::string p_val);

		void UpdateStatsList();

		void ClearProviders();

		void InvalidateItemLists();

		void InvalidateDataItemLists();
	};
}