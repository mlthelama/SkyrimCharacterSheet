#pragma once

namespace Scaleform
{
	class StatsMenu : public RE::IMenu
	{
	public:
		static constexpr std::string_view MENU_NAME = "ShowStats";
		static constexpr std::string_view FILE_NAME = "ShowStats";

		void AdvanceMovie(float a_interval, std::uint32_t a_currentTime) override;
		RE::UI_MESSAGE_RESULTS ProcessMessage(RE::UIMessage& a_message) override;

		void InitExtensions();

		static RE::IMenu* Creator();

		static void Register();

		static void Open();

		static void Close();

		static bool IsMenuOpen();
	private:
		StatsMenu();

		RE::GPtr<RE::GFxMovieView> _view;
		bool _isActive = false;
	};
}