#pragma once

#include "scaleform/statsmenu.h"
#include "player.h"

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

	void StatsMenu::Open() {
		if (!StatsMenu::IsMenuOpen()) {
			RE::UIMessageQueue* msgQueue = RE::UIMessageQueue::GetSingleton();
			msgQueue->AddMessage(MENU_NAME, RE::UI_MESSAGE_TYPE::kShow, nullptr);
		}
	}


	void StatsMenu::Close() {
		if (StatsMenu::IsMenuOpen()) {
			RE::UIMessageQueue* msgQueue = RE::UIMessageQueue::GetSingleton();
			msgQueue->AddMessage(MENU_NAME, RE::UI_MESSAGE_TYPE::kHide, nullptr);
		}
	}

	StatsMenu::StatsMenu() {
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

	void StatsMenu::AdvanceMovie(float a_interval, std::uint32_t a_currentTime) {
		std::uint32_t currentFrame = _view->GetCurrentFrame();

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
		std::uint32_t nextFrame = currentFrame == 120 ? 1 : currentFrame + 1;
		_view->GotoFrame(nextFrame);
	}

	RE::UI_MESSAGE_RESULTS StatsMenu::ProcessMessage(RE::UIMessage& a_message) {
		if (a_message.menu == StatsMenu::MENU_NAME) {
			return RE::UI_MESSAGE_RESULTS::kHandled;
		}
		return RE::UI_MESSAGE_RESULTS::kPassOn;
	}

	void StatsMenu::InitExtensions() {
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

		logger::trace("Menu {} is open {}"sv, MENU_NAME, isOpen);

		return isOpen;
	}

	void StatsMenu::PostCreate() {
		StatsMenu::OnOpen();
	}

	void StatsMenu::OnOpen() {

		using element_t = std::pair<std::reference_wrapper<CLIK::Object>, std::string_view>;
		std::array objects{
			element_t{ std::ref(_rootObj), "_root.rootObj"sv },
			element_t{ std::ref(_title), "_root.rootObj.title"sv },
			element_t{ std::ref(_name), "_root.rootObj.bottomBar.name"sv },
			element_t{ std::ref(_level), "_root.rootObj.bottomBar.level"sv },
			element_t{ std::ref(_race), "_root.rootObj.bottomBar.race"sv },
			element_t{ std::ref(_perks), "_root.rootObj.bottomBar.perks"sv },
			element_t{ std::ref(_valuesHeader), "_root.rootObj.playerValuesHeader"sv },
			element_t{ std::ref(_attackHeader), "_root.rootObj.playerAttackHeader"sv },
			element_t{ std::ref(_perksHeader), "_root.rootObj.playerPerksHeader"sv },
			element_t{ std::ref(_defenceHeader), "_root.rootObj.playerDefenceHeader"sv },
			//element_t{ std::ref(_playerItemList), "_root.rootObj.playerItemList"sv }
			element_t{ std::ref(_playerItemList), "_root.rootObj.playerArea.playerItemList"sv }
			//element_t{ std::ref(_itemList), "_root.rootObj.itemList"sv },
		};

		for (const auto& [object, path] : objects) {
			auto& instance = object.get().GetInstance();
			[[maybe_unused]] const auto success = _view->GetVariable(std::addressof(instance), path.data());
			assert(success && instance.IsObject());
		}

		_rootObj.Visible(false);

		UpdateTitle();
		UpdateHeaders();
		UpdateStatsList();

		//_view->CreateArray(std::addressof(_itemListProvider));
		//_itemList.DataProvider(CLIK::Array{ _itemListProvider });

		//_view->CreateArray(std::addressof(_playerItemListProvider));
		//_playerItemList.DataProvider(CLIK::Array{ _playerItemListProvider });
		//_playerItemList.SelectedIndex(0);
		//_playerItemList.LabelField(TITLE_NAME);
		//_playerItemList.Visible(true);
		

		_view->SetVisible(true);

		_rootObj.Visible(true);
	}

	void StatsMenu::updateText(CLIK::TextField p_field, std::string_view p_string)
	{
		p_field.AutoSize(CLIK::Object{ "left" });
		p_field.HTMLText(p_string);
		p_field.Visible(true);
	}

	std::string StatsMenu::buildText(std::string p_key, std::string p_value)
	{
		std::string text;

		text = p_key;
		text += ": ";
		text += p_value;

		return text;
	}

	void StatsMenu::UpdateTitle() {
		updateText(_title, TITLE_NAME);
	}

	void StatsMenu::UpdateHeaders() {
		updateText(_valuesHeader, constants::headerValuesName);
		updateText(_attackHeader, constants::headerAttackName);
		updateText(_perksHeader, constants::headerPerksName);
		updateText(_defenceHeader, constants::headerDefenceName);
	}

	void StatsMenu::updateList(CLIK::GFx::Controls::ScrollingList& p_scroll, CLIK::Array& p_arr) {
		p_scroll.DataProvider(p_arr);
		p_scroll.Visible(true);

		logger::trace("ListCount {}, ArrayCount {}"sv, p_scroll.RowCount(), p_arr.Length());
	}
	
	//void StatsMenu::AddToList(std::vector<RE::GFxValue>& p_vector, RE::GFxValue p_value) {
		//p_vector.push_back(p_value);
	void StatsMenu::AddToList(CLIK::Array& p_arr, CLIK::Object p_obj) {
		p_arr.Push(p_obj);
	}
	

	void StatsMenu::UpdateStatsList()
	{
		Player* playerinfo = Player::GetSingleton();
		constants::ValueMap playerValues = playerinfo->getValues();

		CLIK::Array valuesArray(_view);
		CLIK::Object str;
		for (const auto& [key, value] : playerValues) {

			switch (key) {
			case constants::name:
				updateText(_name, buildText(constants::getName(key), value));
				break;
			case constants::level:
				updateText(_level, buildText(constants::getName(key), value));
				break;
			case constants::race:
				updateText(_race, buildText(constants::getName(key), value));
				break;
			case constants::perkCount:
				updateText(_perks, buildText(constants::getName(key), value));
				break;
			case constants::height:
			case constants::carryWeight:
				//obj.SetString(buildText(constants::getName(key), value));
				//AddToList(_playerItemListImpl, obj);
				str = buildText(constants::getName(key), value);
				AddToList(valuesArray, str);
				break;
			default:
				break;
			}
		}

		

		updateList(_playerItemList, valuesArray);

		/*_playerItemList.DataProvider(valuesArray);
		_playerItemList.Visible(true);
		*/

		//updateText
		/*
		std::string_view item;
		RE::GFxValue obj;
		for (const auto& [key, value] : playerValues) {
			item = fmt::format("{} = {}", key, value);
			_itemListImpl.push_back(std::make_unique<RE::GFxValue>(item));
			logger::trace("{}"sv, item);
		}

		logger::trace("List size {}"sv, _itemListImpl.size());

		//_itemListProvider.ClearElements();
		for (const auto& elem : _itemListImpl) {
			_itemListProvider.PushBack(elem.get());
			logger::trace("{}"sv, elem->GetString());
		}
		_itemList.InvalidateData();


		*/
	}
}