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
		[[maybe_unused]] const auto success = scaleformManager->LoadMovieEx(menu, FILE_NAME, RE::BSScaleformManager::ScaleModeType::kExactFit, [](RE::GFxMovieDef* a_def) -> void { logger::trace("{}"sv, a_def->GetFrameRate()); });
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
			element_t{ std::ref(_beast), "_root.rootObj.bottomBar.beast"sv },
			element_t{ std::ref(_xp), "_root.rootObj.bottomBar.xp"sv },
			element_t{ std::ref(_valuesHeader), "_root.rootObj.playerValuesHeader"sv },
			element_t{ std::ref(_attackHeader), "_root.rootObj.playerAttackHeader"sv },
			element_t{ std::ref(_perksMagicHeader), "_root.rootObj.playerPerksMagicHeader"sv },
			element_t{ std::ref(_defenceHeader), "_root.rootObj.playerDefenceHeader"sv },
			element_t{ std::ref(_perksWarriorHeader), "_root.rootObj.playerPerksWarriorHeader"sv },
			element_t{ std::ref(_perksThiefHeader), "_root.rootObj.playerPerksThiefHeader"sv },
			element_t{ std::ref(_playerItemList), "_root.rootObj.playerItemList"sv },
			element_t{ std::ref(_defenceItemList), "_root.rootObj.defenceItemList"sv },
			element_t{ std::ref(_attackItemList), "_root.rootObj.attackItemList"sv },
			element_t{ std::ref(_perksMagicItemList), "_root.rootObj.perksMagicItemList"sv },
			element_t{ std::ref(_perksWarriorItemList), "_root.rootObj.perksWarriorItemList"sv },
			element_t{ std::ref(_perksThiefItemList), "_root.rootObj.perksThiefItemList"sv }
		};

		for (const auto& [object, path] : objects) {
			auto& instance = object.get().GetInstance();
			[[maybe_unused]] const auto success = _view->GetVariable(std::addressof(instance), path.data());
			assert(success && instance.IsObject());
		}

		_rootObj.Visible(false);

		_view->CreateArray(std::addressof(_playerItemListProvider));
		_playerItemList.DataProvider(CLIK::Array{ _playerItemListProvider });

		_view->CreateArray(std::addressof(_defenceItemListProvider));
		_defenceItemList.DataProvider(CLIK::Array{ _defenceItemListProvider });

		_view->CreateArray(std::addressof(_attackItemListProvider));
		_attackItemList.DataProvider(CLIK::Array{ _attackItemListProvider });

		_view->CreateArray(std::addressof(_perksMagicItemListProvider));
		_perksMagicItemList.DataProvider(CLIK::Array{ _perksMagicItemListProvider });

		_view->CreateArray(std::addressof(_perksWarriorItemListProvider));
		_perksWarriorItemList.DataProvider(CLIK::Array{ _perksWarriorItemListProvider });

		_view->CreateArray(std::addressof(_perksThiefItemListProvider));
		_perksThiefItemList.DataProvider(CLIK::Array{ _perksThiefItemListProvider });

		UpdateTitle();
		UpdateHeaders();
		UpdateStatsList();

		_view->SetVisible(true);
		_rootObj.Visible(true);
	}

	void StatsMenu::updateText(CLIK::TextField p_field, std::string_view p_string) {
		p_field.AutoSize(CLIK::Object{ "left" });
		p_field.HTMLText(p_string);
		p_field.Visible(true);
	}

	std::string StatsMenu::buildText(std::string p_key, std::string p_value) {
		std::string text;

		text = p_key;
		text += ": ";
		if (p_value.find(".") != std::string::npos) {
			auto s = p_value.substr(p_value.find(".") + 1, 2);
			if (std::count(s.begin(), s.end(), '0') == 2 ) {
				text += p_value.substr(0, p_value.find("."));
			} else {
				text += p_value.substr(0, p_value.find(".") + 3);
			}
		} else {
			text += p_value;
		}

		return text;
	}

	void StatsMenu::UpdateTitle() {
		updateText(_title, TITLE_NAME);
	}

	void StatsMenu::UpdateHeaders() {
		updateText(_valuesHeader, constants::headerValuesName);
		updateText(_attackHeader, constants::headerAttackName);
		updateText(_perksMagicHeader, constants::headerPerksMagicName);
		updateText(_defenceHeader, constants::headerDefenceName);
		updateText(_perksWarriorHeader, constants::headerPerksWarriorName);
		updateText(_perksThiefHeader, constants::headerPerksThiefName);
	}
	
	RE::GFxValue StatsMenu::buildGFxValue(std::string p_val) {
		RE::GFxValue value;
		_view->CreateObject(std::addressof(value));
		value.SetMember("displayName", { static_cast<std::string_view>(p_val) });
		return value;
	}

	void StatsMenu::UpdateStatsList() {
		Player* playerinfo = Player::GetSingleton();
		constants::ValueMap playerValues = playerinfo->getValues();

		_playerItemListProvider.ClearElements();
		_defenceItemListProvider.ClearElements();
		_attackItemListProvider.ClearElements();
		_perksMagicItemListProvider.ClearElements();
		_perksWarriorItemListProvider.ClearElements();
		_perksThiefItemListProvider.ClearElements();

		_playerItemList.Invalidate();
		_defenceItemList.Invalidate();
		_attackItemList.Invalidate();
		_perksMagicItemList.Invalidate();
		_perksWarriorItemList.Invalidate();
		_perksThiefItemList.Invalidate();

		/* todo add different handling for stats with mutliplier health, perks, ...*/
		for (const auto& [key, value] : playerValues) {
			logger::trace("processing {}"sv, buildText(playerinfo->getValueName(key), value));
			switch (key) {
			case constants::name:
				updateText(_name, buildText(playerinfo->getValueName(key), value));
				break;
			case constants::level:
				updateText(_level, buildText(playerinfo->getValueName(key), value));
				break;
			case constants::race:
				updateText(_race, buildText(playerinfo->getValueName(key), value));
				break;
			case constants::perkCount:
				updateText(_perks, buildText(playerinfo->getValueName(key), value));
				break;
			case constants::beast:
				updateText(_beast, buildText(playerinfo->getValueName(key), value));
				break;
			case constants::xp:
				updateText(_xp, buildText(playerinfo->getValueName(key), value));
				break;
			case constants::height:
			case constants::carryWeight:
			case constants::equipedWeight:
			case constants::inventoryWeight:
			case constants::weight:
			case constants::skillTrainingsThisLevel:
			case constants::dragonSouls:
			case constants::shoutRecoveryMult:
			case constants::movementNoiseMult:
			case constants::speedMult:
				_playerItemListProvider.PushBack(buildGFxValue(buildText(playerinfo->getValueName(key), value)));
				logger::trace("{} added to playerItemList"sv, playerinfo->getValueName(key));
				break;
			case constants::absorbChance:
			case constants::armor:
			case constants::combatHealthRegenMultiply:
			case constants::resistDamage:
			case constants::resistDisease:
			case constants::resistFire:
			case constants::resistFrost:
			case constants::resistMagic:
			case constants::resistPoison:
			case constants::resistShock:
			case constants::health:
			case constants::healthRate:
			case constants::healthRateMult:
			case constants::magicka:
			case constants::magickaRate:
			case constants::magickaRateMult:
			case constants::stamina:
			case constants::staminaRate:
			case constants::staminaRateMult:
				_defenceItemListProvider.PushBack(buildGFxValue(buildText(playerinfo->getValueName(key), value)));
				logger::trace("{} added to defenceItemList"sv, playerinfo->getValueName(key));
				break;
			case constants::unarmedDamage:
			case constants::weaponSpeedMult:
			case constants::meleeDamage:
			case constants::damage:
			case constants::criticalChance:
			case constants::bowSpeedBonus:
			case constants::attackDamageMult:
				_attackItemListProvider.PushBack(buildGFxValue(buildText(playerinfo->getValueName(key), value)));
				logger::trace("{} added to attackItemList"sv, playerinfo->getValueName(key));
				break;
			case constants::alteration:
			case constants::conjuration:
			case constants::enchanting:
			case constants::illusion:
			case constants::restoration:
			case constants::destruction:
			case constants::alterationPowerMod:
			case constants::conjurationPowerMod:
			case constants::enchantingPowerMod:
			case constants::illusionPowerMod:
			case constants::restorationPowerMod:
			case constants::destructionPowerMod:
				_perksMagicItemListProvider.PushBack(buildGFxValue(buildText(playerinfo->getValueName(key), value)));
				logger::trace("{} added to perksMagicItemList"sv, playerinfo->getValueName(key));
				break;
			case constants::smithing:
			case constants::twoHanded:
			case constants::oneHanded:
			case constants::lightArmor:
			case constants::heavyArmor:
			case constants::block:
			case constants::smithingPowerMod:
			case constants::twoHandedPowerMod:
			case constants::oneHandedPowerMod:
			case constants::lightArmorPowerMod:
			case constants::heavyArmorPowerMod:
			case constants::blockPowerMod:
				_perksWarriorItemListProvider.PushBack(buildGFxValue(buildText(playerinfo->getValueName(key), value)));
				logger::trace("{} added to perksWarriorItemList"sv, playerinfo->getValueName(key));
				break;
			case constants::sneak:
			case constants::speech:
			case constants::pickpocket:
			case constants::lockpicking:
			case constants::archery:
			case constants::alchemy:
			case constants::sneakPowerMod:
			case constants::speechPowerMod:
			case constants::pickpocketPowerMod:
			case constants::lockpickingPowerMod:
			case constants::archeryPowerMod:
			case constants::alchemyPowerMod:
				_perksThiefItemListProvider.PushBack(buildGFxValue(buildText(playerinfo->getValueName(key), value)));
				logger::trace("{} added to perksThiefItemList"sv, playerinfo->getValueName(key));
				break;
			default:
				logger::trace("not handeled {}"sv, buildText(playerinfo->getValueName(key), value));
				break;
			}
		}
		_playerItemList.InvalidateData();
		_defenceItemList.InvalidateData();
		_attackItemList.InvalidateData();
		_perksMagicItemList.InvalidateData();
		_perksWarriorItemList.InvalidateData();
		_perksThiefItemList.InvalidateData();

		playerValues.clear();
	}
}