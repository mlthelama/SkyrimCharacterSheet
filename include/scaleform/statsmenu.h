#pragma once
#include "CLIK/Array.h"
#include "CLIK/GFx/Controls/ScrollingList.h"
#include "CLIK/TextField.h"

namespace Scaleform
{
	class StatsMenu : public RE::IMenu
	{
	public:
		static constexpr std::string_view MENU_NAME = "ShowStats";
		static constexpr std::string_view FILE_NAME = "ShowStats";
		static constexpr std::string_view TITLE_NAME = "Show Stats";

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

		RE::GPtr<RE::GFxMovieView> _view;
		bool _isActive = false;


		CLIK::MovieClip _rootObj;
		CLIK::TextField _title;

		CLIK::GFx::Controls::ScrollingList _itemList;
		RE::GFxValue _itemListProvider;
		//std::vector<std::unique_ptr<Items::Item>> _itemListImpl;
		//std::vector<std::unique_ptr<std::string>> _itemListImpl;
		std::vector<std::string> _itemListImpl;

		void OnOpen();

		void UpdateTitle();

		void UpdateStatsList();
	};
}