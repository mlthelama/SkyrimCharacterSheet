#pragma once

#include "scaleform/statsmenu.h"
#include "player.h"

namespace Scaleform
{
	RE::IMenu* StatsMenu::Creator() {
		return new StatsMenu();
	}

	void StatsMenu::Register() {
		auto ui = RE::UI::GetSingleton();
		ui->Register(MENU_NAME, Creator);

		logger::info("Registered {}"sv, MENU_NAME);
	}

	void StatsMenu::Open() {
		if (!StatsMenu::IsMenuOpen()) {
			logger::debug("Open Menu {}"sv, MENU_NAME);
			auto msgQueue = RE::UIMessageQueue::GetSingleton();
			msgQueue->AddMessage(MENU_NAME, RE::UI_MESSAGE_TYPE::kShow, nullptr);
		}
	}


	void StatsMenu::Close() {
		if (StatsMenu::IsMenuOpen()) {
			logger::debug("Close Menu {}"sv, MENU_NAME);
			auto msgQueue = RE::UIMessageQueue::GetSingleton();
			msgQueue->AddMessage(MENU_NAME, RE::UI_MESSAGE_TYPE::kHide, nullptr);
		}
	}

	StatsMenu::StatsMenu() {
		using Context = RE::UserEvents::INPUT_CONTEXT_ID;
		using Flag = RE::UI_MENU_FLAGS;

		auto menu = static_cast<RE::IMenu*>(this);
		auto scaleformManager = RE::BSScaleformManager::GetSingleton();
		[[maybe_unused]] const auto success = scaleformManager->LoadMovieEx(menu, FILE_NAME, RE::BSScaleformManager::ScaleModeType::kExactFit, [](RE::GFxMovieDef* a_def) -> void { logger::trace("FPS: {}"sv, a_def->GetFrameRate()); });
		assert(success);
		_view = menu->uiMovie;
		_view->SetMouseCursorCount(0);
		menu->menuFlags |= Flag::kAllowSaving;
		menu->depthPriority = 11;
		menu->inputContext = Context::kNone;
		//InitExtensions();

		_isActive = true;
		_view->SetVisible(true);

	}

	void StatsMenu::AdvanceMovie(float a_interval, uint32_t a_currentTime) {
		auto currentFrame = _view->GetCurrentFrame();

		logger::trace("interval {}, currenttime {}"sv, a_interval, a_currentTime);

		_view->SetVisible(true);

		auto nextFrame = currentFrame == 120 ? 1 : currentFrame + 1;
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
		auto isOpen = ui->IsMenuOpen(MENU_NAME);

		logger::trace("Menu {} is open {}"sv, MENU_NAME, isOpen);

		return isOpen;
	}

	void StatsMenu::PostCreate() {
		StatsMenu::OnOpen();
	}

	void StatsMenu::OnOpen() {

		using element_t = pair<reference_wrapper<CLIK::Object>, string_view>;
		array objects{
			element_t{ ref(_rootObj), "_root.rootObj"sv },
			element_t{ ref(_title), "_root.rootObj.title"sv },
			element_t{ ref(_name), "_root.rootObj.bottomBar.name"sv },
			element_t{ ref(_level), "_root.rootObj.bottomBar.level"sv },
			element_t{ ref(_race), "_root.rootObj.bottomBar.race"sv },
			element_t{ ref(_perks), "_root.rootObj.bottomBar.perks"sv },
			element_t{ ref(_beast), "_root.rootObj.bottomBar.beast"sv },
			element_t{ ref(_xp), "_root.rootObj.bottomBar.xp"sv },
			element_t{ ref(_valuesHeader), "_root.rootObj.playerValuesHeader"sv },
			element_t{ ref(_attackHeader), "_root.rootObj.playerAttackHeader"sv },
			element_t{ ref(_perksMagicHeader), "_root.rootObj.playerPerksMagicHeader"sv },
			element_t{ ref(_defenceHeader), "_root.rootObj.playerDefenceHeader"sv },
			element_t{ ref(_perksWarriorHeader), "_root.rootObj.playerPerksWarriorHeader"sv },
			element_t{ ref(_perksThiefHeader), "_root.rootObj.playerPerksThiefHeader"sv },
			element_t{ ref(_playerItemList), "_root.rootObj.playerItemList"sv },
			element_t{ ref(_defenceItemList), "_root.rootObj.defenceItemList"sv },
			element_t{ ref(_attackItemList), "_root.rootObj.attackItemList"sv },
			element_t{ ref(_perksMagicItemList), "_root.rootObj.perksMagicItemList"sv },
			element_t{ ref(_perksWarriorItemList), "_root.rootObj.perksWarriorItemList"sv },
			element_t{ ref(_perksThiefItemList), "_root.rootObj.perksThiefItemList"sv }
		};

		for (const auto& [object, path] : objects) {
			auto& instance = object.get().GetInstance();
			[[maybe_unused]] const auto success = _view->GetVariable(addressof(instance), path.data());
			assert(success && instance.IsObject());
		}

		_rootObj.Visible(false);

		_view->CreateArray(addressof(_playerItemListProvider));
		_playerItemList.DataProvider(CLIK::Array{ _playerItemListProvider });

		_view->CreateArray(addressof(_defenceItemListProvider));
		_defenceItemList.DataProvider(CLIK::Array{ _defenceItemListProvider });

		_view->CreateArray(addressof(_attackItemListProvider));
		_attackItemList.DataProvider(CLIK::Array{ _attackItemListProvider });

		_view->CreateArray(addressof(_perksMagicItemListProvider));
		_perksMagicItemList.DataProvider(CLIK::Array{ _perksMagicItemListProvider });

		_view->CreateArray(addressof(_perksWarriorItemListProvider));
		_perksWarriorItemList.DataProvider(CLIK::Array{ _perksWarriorItemListProvider });

		_view->CreateArray(addressof(_perksThiefItemListProvider));
		_perksThiefItemList.DataProvider(CLIK::Array{ _perksThiefItemListProvider });

		UpdateTitle();
		UpdateHeaders();
		updateBottom();

		UpdateLists();

		_view->SetVisible(true);
		_rootObj.Visible(true);

		logger::debug("Shown all Values for Menu {}"sv, MENU_NAME);
	}

	void StatsMenu::updateText(CLIK::TextField p_field, string_view p_string) {
		p_field.AutoSize(CLIK::Object{ "left" });
		p_field.HTMLText(p_string);
		p_field.Visible(true);
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
	
	RE::GFxValue StatsMenu::buildGFxValue(string p_val) {
		RE::GFxValue value;
		_view->CreateObject(addressof(value));
		value.SetMember("displayName", { static_cast<string_view>(p_val) });
		return value;
	}

	void StatsMenu::ClearProviders() {
		_playerItemListProvider.ClearElements();
		_defenceItemListProvider.ClearElements();
		_attackItemListProvider.ClearElements();
		_perksMagicItemListProvider.ClearElements();
		_perksWarriorItemListProvider.ClearElements();
		_perksThiefItemListProvider.ClearElements();
	}

	void StatsMenu::InvalidateItemLists() {
		_playerItemList.Invalidate();
		_defenceItemList.Invalidate();
		_attackItemList.Invalidate();
		_perksMagicItemList.Invalidate();
		_perksWarriorItemList.Invalidate();
		_perksThiefItemList.Invalidate();
	}

	void StatsMenu::InvalidateDataItemLists() {
		_playerItemList.InvalidateData();
		_defenceItemList.InvalidateData();
		_attackItemList.InvalidateData();
		_perksMagicItemList.InvalidateData();
		_perksWarriorItemList.InvalidateData();
		_perksThiefItemList.InvalidateData();
	}


	void StatsMenu::UpdateLists() {
		auto playerinfo = Player::GetSingleton();

		ClearProviders();
		InvalidateItemLists();

		auto playerValues = playerinfo->getPlayerValues();

		for (auto& element : playerValues) {

			if (!element.getShow() 
				|| element.getGuiText().empty() 
				|| element.getGuiText() == "" 
				|| element.getValue().empty()
				|| element.getValue() == ""
			) {
				continue;
			}

			logger::trace("processing name {}, displayName {}, menu {}"sv, element.getName(), element.getGuiText(), element.getMenu());
			switch (element.getName()) {
			case Stats::name:
				updateText(_name, element.getGuiText());
				break;
			case Stats::level:
				updateText(_level, element.getGuiText());
				break;
			case Stats::race:
				updateText(_race, element.getGuiText());
				break;
			case Stats::perkCount:
				updateText(_perks, element.getGuiText());
				break;
			case Stats::beast:
				updateText(_beast, element.getGuiText());
				break;
			case Stats::xp:
				updateText(_xp, element.getGuiText());
				break;
			case Stats::height:
			case Stats::carryWeight:
			case Stats::equipedWeight:
			case Stats::inventoryWeight:
			case Stats::weight:
			case Stats::skillTrainingsThisLevel:
			case Stats::dragonSouls:
			case Stats::shoutRecoveryMult:
			case Stats::movementNoiseMult:
			case Stats::speedMult:
			case Stats::darkbrotherHood:
			case Stats::thiefsGuild:
			case Stats::orcFriend:
			case Stats::collegeOfWinterhold:
			case Stats::companions:
			case Stats::imperialLegion:
			case Stats::stormcloaks:
			case Stats::greybeard:
			case Stats::mass:
			case Stats::bypassVendorKeywordCheck:
			case Stats::bypassVendorStolenCheck:
			case Stats::absorbChance:
			case Stats::armor:
			case Stats::combatHealthRegenMultiply:
			case Stats::resistDamage:
			case Stats::resistDisease:
			case Stats::resistFire:
			case Stats::resistFrost:
			case Stats::resistMagic:
			case Stats::resistPoison:
			case Stats::resistShock:
			case Stats::health:
			case Stats::healthRatePer:
			case Stats::magicka:
			case Stats::magickaRatePer:
			case Stats::stamina:
			case Stats::staminaRatePer:
			case Stats::reflectDamage:
			case Stats::armorPerks:
			case Stats::unarmedDamage:
			case Stats::weaponSpeedMult:
			case Stats::meleeDamage:
			case Stats::damage:
			case Stats::criticalChance:
			case Stats::bowSpeedBonus:
			case Stats::attackDamageMult:
			case Stats::damageArrow:
			case Stats::damageRight:
			case Stats::damageLeft:
			case Stats::leftWeaponSpeedMult:
			case Stats::rightItemCharge:
			case Stats::leftItemCharge:
			case Stats::bowStaggerBonus:
			case Stats::alteration:
			case Stats::conjuration:
			case Stats::enchanting:
			case Stats::illusion:
			case Stats::restoration:
			case Stats::destruction:
			case Stats::alterationPowerMod:
			case Stats::conjurationPowerMod:
			case Stats::enchantingPowerMod:
			case Stats::illusionPowerMod:
			case Stats::restorationPowerMod:
			case Stats::destructionPowerMod:
			case Stats::alterationMod:
			case Stats::conjurationMod:
			case Stats::enchantingMod:
			case Stats::illusionMod:
			case Stats::restorationMod:
			case Stats::destructionMod:
			case Stats::smithing:
			case Stats::twoHanded:
			case Stats::oneHanded:
			case Stats::lightArmor:
			case Stats::heavyArmor:
			case Stats::block:
			case Stats::smithingPowerMod:
			case Stats::twoHandedPowerMod:
			case Stats::oneHandedPowerMod:
			case Stats::lightArmorPowerMod:
			case Stats::heavyArmorPowerMod:
			case Stats::blockPowerMod:
			case Stats::smithingMod:
			case Stats::twoHandedMod:
			case Stats::oneHandedMod:
			case Stats::lightArmorMod:
			case Stats::heavyArmorMod:
			case Stats::blockMod:
			case Stats::sneak:
			case Stats::speech:
			case Stats::pickpocket:
			case Stats::lockpicking:
			case Stats::archery:
			case Stats::alchemy:
			case Stats::sneakPowerMod:
			case Stats::speechPowerMod:
			case Stats::pickpocketPowerMod:
			case Stats::lockpickingPowerMod:
			case Stats::archeryPowerMod:
			case Stats::alchemyPowerMod:
			case Stats::sneakingMod:
			case Stats::speechcraftMod:
			case Stats::pickpocketMod:
			case Stats::lockpickingMod:
			case Stats::marksmanMod:
			case Stats::alchemyMod:
				if (element.getMenu() != constants::MenuValue::mNone) {
					menuMap.find(element.getMenu())->second.PushBack(buildGFxValue(element.getGuiText()));
					logger::trace("added to Menu {}, Name {}, GuiText ({})"sv, element.getMenu(), element.getName(), element.getGuiText());
				}
				break;
			default:
				logger::warn("not handeled name {}, displayName {}"sv, element.getName(), element.getGuiText());
				break;
			}
		}

		playerValues.clear();
		InvalidateDataItemLists();
	}

	void StatsMenu::updateBottom() {
		//in case something is not set, we do not want to see default swf text
		updateText(_name, "");
		updateText(_level, "");
		updateText(_race, "");
		updateText(_perks, "");
		updateText(_beast, "");
		updateText(_xp, "");
	}
}