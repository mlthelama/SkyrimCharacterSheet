#pragma once
#include "scaleform/statsmenu.h"
#include "data/playerdata.h"

namespace Scaleform {
    RE::IMenu* StatsMenu::Creator() { return new StatsMenu(); }

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
        [[maybe_unused]] const auto success =
            scaleformManager->LoadMovieEx(menu, FILE_NAME, RE::BSScaleformManager::ScaleModeType::kExactFit,
                [](RE::GFxMovieDef* a_def) -> void { logger::trace("FPS: {}"sv, a_def->GetFrameRate()); });
        assert(success);
        _view = menu->uiMovie;
        _view->SetMouseCursorCount(0);
        if (*Settings::pauseGame) {
            menu->menuFlags |= Flag::kPausesGame;
        } else {
            menu->menuFlags |= Flag::kAllowSaving;
        }
        menu->depthPriority = 0;
        menu->inputContext = Context::kNone;
        InitExtensions();

        _isActive = true;
        _view->SetVisible(true);
    }

    void StatsMenu::AdvanceMovie(float a_interval, uint32_t a_currentTime) {
        RE::IMenu::AdvanceMovie(a_interval, a_currentTime);
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

        if (isOpen) {
            logger::trace("Menu {} is open {}"sv, MENU_NAME, isOpen);
        }

        return isOpen;
    }

    void StatsMenu::PostCreate() { StatsMenu::OnOpen(); }

    void StatsMenu::OnOpen() {
        using element_t = std::pair<std::reference_wrapper<CLIK::Object>, std::string_view>;
        std::array objects{ element_t{ std::ref(_rootObj), "_root.rootObj"sv },
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
            element_t{ std::ref(_perksThiefItemList), "_root.rootObj.perksThiefItemList"sv },
            element_t{ std::ref(_next), "_root.rootObj.playerNextScreen"sv } };

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
        UpdateBottom();

        UpdateLists();

        UpdateNext();

        _view->SetVisible(true);
        _rootObj.Visible(true);

        logger::debug("Shown all Values for Menu {}"sv, MENU_NAME);
    }

    void StatsMenu::updateText(CLIK::TextField p_field, std::string_view p_string) {
        p_field.AutoSize(CLIK::Object{ "left" });
        p_field.HTMLText(p_string);
        p_field.Visible(true);
    }

    void StatsMenu::UpdateTitle() { updateText(_title, getMenuName(ShowMenu::mStats)); }

    void StatsMenu::UpdateHeaders() {
        updateText(_valuesHeader, static_cast<std::string_view>(*Settings::showStatsTitlePlayer));
        updateText(_attackHeader, static_cast<std::string_view>(*Settings::showStatsTitleAttack));
        updateText(_perksMagicHeader, static_cast<std::string_view>(*Settings::showStatsTitleMagic));
        updateText(_defenceHeader, static_cast<std::string_view>(*Settings::showStatsTitleDefence));
        updateText(_perksWarriorHeader, static_cast<std::string_view>(*Settings::showStatsTitleWarrior));
        updateText(_perksThiefHeader, static_cast<std::string_view>(*Settings::showStatsTitleThief));
    }

    RE::GFxValue StatsMenu::buildGFxValue(std::string p_val) {
        RE::GFxValue value;
        _view->CreateObject(std::addressof(value));
        value.SetMember("displayName", { static_cast<std::string_view>(p_val) });
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
        auto playerinfo = PlayerData::GetSingleton();

        ClearProviders();
        InvalidateItemLists();

        auto playerValues = playerinfo->getPlayerValues();
        for (auto& element : playerValues) {
            if (!element->getShow() || element->getGuiText().empty() || element->getGuiText() == "" ||
                element->getValue().empty() || element->getValue() == "") {
                continue;
            }

            logger::trace("processing name {}, displayName {}, menu {}"sv, element->getName(), element->getGuiText(),
                element->getMenu());
            switch (element->getName()) {
                case StatsValue::name:
                    updateText(_name, element->getGuiText());
                    break;
                case StatsValue::level:
                    updateText(_level, element->getGuiText());
                    break;
                case StatsValue::race:
                    updateText(_race, element->getGuiText());
                    break;
                case StatsValue::perkCount:
                    updateText(_perks, element->getGuiText());
                    break;
                case StatsValue::beast:
                    updateText(_beast, element->getGuiText());
                    break;
                case StatsValue::xp:
                    updateText(_xp, element->getGuiText());
                    break;
                case StatsValue::height:
                case StatsValue::carryWeight:
                case StatsValue::equipedWeight:
                case StatsValue::inventoryWeight:
                case StatsValue::weight:
                case StatsValue::skillTrainingsThisLevel:
                case StatsValue::dragonSouls:
                case StatsValue::shoutRecoveryMult:
                case StatsValue::movementNoiseMult:
                case StatsValue::speedMult:
                case StatsValue::mass:
                case StatsValue::bypassVendorKeywordCheck:
                case StatsValue::bypassVendorStolenCheck:
                case StatsValue::absorbChance:
                case StatsValue::armor:
                case StatsValue::combatHealthRegenMultiply:
                case StatsValue::resistDamage:
                case StatsValue::resistDisease:
                case StatsValue::resistFire:
                case StatsValue::resistFrost:
                case StatsValue::resistMagic:
                case StatsValue::resistPoison:
                case StatsValue::resistShock:
                case StatsValue::health:
                case StatsValue::healthRatePer:
                case StatsValue::magicka:
                case StatsValue::magickaRatePer:
                case StatsValue::stamina:
                case StatsValue::staminaRatePer:
                case StatsValue::reflectDamage:
                case StatsValue::armorPerks:
                case StatsValue::unarmedDamage:
                case StatsValue::weaponSpeedMult:
                case StatsValue::meleeDamage:
                case StatsValue::damage:
                case StatsValue::criticalChance:
                case StatsValue::bowSpeedBonus:
                case StatsValue::attackDamageMult:
                case StatsValue::damageArrow:
                case StatsValue::damageRight:
                case StatsValue::damageLeft:
                case StatsValue::leftWeaponSpeedMult:
                case StatsValue::rightItemCharge:
                case StatsValue::leftItemCharge:
                case StatsValue::bowStaggerBonus:
                case StatsValue::alteration:
                case StatsValue::conjuration:
                case StatsValue::enchanting:
                case StatsValue::illusion:
                case StatsValue::restoration:
                case StatsValue::destruction:
                case StatsValue::alterationPowerMod:
                case StatsValue::conjurationPowerMod:
                case StatsValue::enchantingPowerMod:
                case StatsValue::illusionPowerMod:
                case StatsValue::restorationPowerMod:
                case StatsValue::destructionPowerMod:
                case StatsValue::alterationMod:
                case StatsValue::conjurationMod:
                case StatsValue::enchantingMod:
                case StatsValue::illusionMod:
                case StatsValue::restorationMod:
                case StatsValue::destructionMod:
                case StatsValue::smithing:
                case StatsValue::twoHanded:
                case StatsValue::oneHanded:
                case StatsValue::lightArmor:
                case StatsValue::heavyArmor:
                case StatsValue::block:
                case StatsValue::smithingPowerMod:
                case StatsValue::twoHandedPowerMod:
                case StatsValue::oneHandedPowerMod:
                case StatsValue::lightArmorPowerMod:
                case StatsValue::heavyArmorPowerMod:
                case StatsValue::blockPowerMod:
                case StatsValue::smithingMod:
                case StatsValue::twoHandedMod:
                case StatsValue::oneHandedMod:
                case StatsValue::lightArmorMod:
                case StatsValue::heavyArmorMod:
                case StatsValue::blockMod:
                case StatsValue::sneak:
                case StatsValue::speech:
                case StatsValue::pickpocket:
                case StatsValue::lockpicking:
                case StatsValue::archery:
                case StatsValue::alchemy:
                case StatsValue::sneakPowerMod:
                case StatsValue::speechPowerMod:
                case StatsValue::pickpocketPowerMod:
                case StatsValue::lockpickingPowerMod:
                case StatsValue::archeryPowerMod:
                case StatsValue::alchemyPowerMod:
                case StatsValue::sneakingMod:
                case StatsValue::speechcraftMod:
                case StatsValue::pickpocketMod:
                case StatsValue::lockpickingMod:
                case StatsValue::marksmanMod:
                case StatsValue::alchemyMod:
                    if (element->getMenu() != StatsMenuValue::mNone) {
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

        playerValues.clear();
        for (auto& element : playerValues) { element.reset(); }
        logger::trace("Vector Size is {}"sv, playerValues.size());

        InvalidateDataItemLists();
    }

    void StatsMenu::UpdateBottom() {
        //in case something is not set, we do not want to see default swf text
        updateText(_name, "");
        updateText(_level, "");
        updateText(_race, "");
        updateText(_perks, "");
        updateText(_beast, "");
        updateText(_xp, "");
        updateText(_next, "");
    }

    void StatsMenu::UpdateNext() { updateText(_next, getNextMenuName(ShowMenu::mStats)); }
}
