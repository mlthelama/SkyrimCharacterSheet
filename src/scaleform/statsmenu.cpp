#pragma once

#include "scaleform/statsmenu.h"

namespace Scaleform
{
	RE::IMenu* StatsMenu::Creator()
	{
		return new StatsMenu();
	}

	void StatsMenu::Register()
	{
		auto ui = RE::UI::GetSingleton();
		ui->Register(MENU_NAME, Creator);

		logger::info("Registered {}"sv, MENU_NAME);
	}

	void StatsMenu::Open()
	{
		if (!StatsMenu::IsMenuOpen()) {
			RE::UIMessageQueue* msgQueue = RE::UIMessageQueue::GetSingleton();
			msgQueue->AddMessage(MENU_NAME, RE::UI_MESSAGE_TYPE::kShow, nullptr);

			//msgQueue->
		}
	}


	void StatsMenu::Close()
	{
		if (StatsMenu::IsMenuOpen()) {
			RE::UIMessageQueue* msgQueue = RE::UIMessageQueue::GetSingleton();
			msgQueue->AddMessage(MENU_NAME, RE::UI_MESSAGE_TYPE::kHide, nullptr);
		}
	}

	StatsMenu::StatsMenu()
	{
		using Context = RE::UserEvents::INPUT_CONTEXT_ID;
		using Flag = RE::UI_MENU_FLAGS;

		auto menu = static_cast<RE::IMenu*>(this);
		auto scaleformManager = RE::BSScaleformManager::GetSingleton();
		[[maybe_unused]] const auto success = scaleformManager->LoadMovieEx(menu, FILE_NAME, RE::BSScaleformManager::ScaleModeType::kExactFit, [](RE::GFxMovieDef* a_def) -> void { logger::trace("{}"sv, a_def->GetFileAttributes()); });
		assert(success);
		_view = menu->uiMovie;
		_view->SetMouseCursorCount(0);
		menu->menuFlags |= Flag::kAllowSaving;
		menu->depthPriority = 11;
		menu->inputContext = Context::kNone;
		//InitExtensions();

		/*
		RE::PlayerCharacter* player = RE::PlayerCharacter::GetSingleton();
		if (player) {
			if (player->IsInCombat()) {
				_isActive = true;
				_view->SetVisible(true);
			} else if (!player->IsInCombat()) {
				_isActive = false;
				_view->SetVisible(false);
			}
		}

		_view->SetPause(true);
		*/
		_isActive = true;
		_view->SetVisible(true);

	}

	void StatsMenu::AdvanceMovie(float a_interval, std::uint32_t a_currentTime)
	{
		//std::uint32_t currentFrame = _view->GetCurrentFrame();

		logger::trace("interval {}, currenttime {}"sv, a_interval, a_currentTime);

		/*if (!GetCombatAlertOverlayCount()) {
			RE::UIMessageQueue* msgQueue = RE::UIMessageQueue::GetSingleton();
			msgQueue->AddMessage(StatsMenu::MENU_NAME, RE::UI_MESSAGE_TYPE::kHide, nullptr);
		}*/

		/*
		RE::UIMessageQueue* msgQueue = RE::UIMessageQueue::GetSingleton();
		msgQueue->AddMessage(StatsMenu::MENU_NAME, RE::UI_MESSAGE_TYPE::kHide, nullptr);
		*/

		/*RE::PlayerCharacter* player = RE::PlayerCharacter::GetSingleton();
		if (player && currentFrame == 120) {
			if (player->IsInCombat() && !_isActive) {
				_isActive = true;
				_view->SetVisible(true);
			} else if (!player->IsInCombat() && _isActive) {
				_isActive = false;
				_view->SetVisible(false);
			}
		}*/

		_view->SetVisible(true);

		//std::uint32_t nextFrame = currentFrame == 120 ? 1 : currentFrame + 1;
		//_view->GotoFrame(nextFrame);
	}

	RE::UI_MESSAGE_RESULTS StatsMenu::ProcessMessage(RE::UIMessage& a_message)
	{
		if (a_message.menu == StatsMenu::MENU_NAME) {
			return RE::UI_MESSAGE_RESULTS::kHandled;
		}
		return RE::UI_MESSAGE_RESULTS::kPassOn;
	}

	void StatsMenu::InitExtensions()
	{
		const RE::GFxValue boolean(true);
		bool success;

		success = _view->SetVariable("_global.gfxExtensions", boolean);
		assert(success);
		success = _view->SetVariable("_global.noInvisibleAdvance", boolean);
		assert(success);
	}

	bool StatsMenu::IsMenuOpen() {
		auto ui = RE::UI::GetSingleton();
		bool isOpen = ui->IsMenuOpen(MENU_NAME);

		logger::info("Menu {} is open {}"sv, MENU_NAME, isOpen);

		return isOpen;
	}
}