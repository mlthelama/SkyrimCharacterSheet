#pragma once
#include "settings/gamesettings.h"

class StatConfig {
    using StatsInventoryMenuValue = MenuUtil::StatsInventoryMenuValue;
    using StatsMenuValue = MenuUtil::StatsMenuValue;

public:
    StatConfig(RE::ActorValue a_actor,
        std::string a_display_name,
        StatsMenuValue a_stats_menu,
        StatsInventoryMenuValue a_stats_inventory_menu)
        : _actor(a_actor)
        , _displayName(a_display_name)
        , _statsMenu(a_stats_menu)
        , _statsInventoryMenu(a_stats_inventory_menu) {}

    StatConfig(RE::ActorValue a_actor,
        std::string a_display_name,
        std::string a_ending,
        StatsMenuValue a_stats_menu,
        StatsInventoryMenuValue a_stats_inventory_menu)
        : _actor(a_actor)
        , _displayName(a_display_name)
        , _ending(a_ending)
        , _statsMenu(a_stats_menu)
        , _statsInventoryMenu(a_stats_inventory_menu) {}

    StatConfig(RE::ActorValue a_actor,
        std::string a_display_name,
        std::string a_ending,
        StatsMenuValue a_stats_menu,
        StatsInventoryMenuValue a_stats_inventory_menu,
        int64_t a_value_multiplier)
        : _actor(a_actor)
        , _displayName(a_display_name)
        , _ending(a_ending)
        , _statsMenu(a_stats_menu)
        , _statsInventoryMenu(a_stats_inventory_menu)
        , _valueMultiplier(a_value_multiplier) {}

    StatConfig(RE::ActorValue a_actor,
        std::string a_display_name,
        std::string a_ending,
        StatsMenuValue a_stats_menu,
        StatsInventoryMenuValue a_stats_inventory_menu,
        int64_t a_value_multiplier,
        float a_cap)
        : _actor(a_actor)
        , _displayName(a_display_name)
        , _ending(a_ending)
        , _statsMenu(a_stats_menu)
        , _statsInventoryMenu(a_stats_inventory_menu)
        , _valueMultiplier(a_value_multiplier)
        , _cap(a_cap) {}

    RE::ActorValue getActor() { return _actor; }

    std::string getDisplayName() { return _displayName; }

    std::string getEnding() { return _ending; }

    StatsMenuValue getStatsMenu() { return _statsMenu; }

    StatsInventoryMenuValue getStatsInventoryMenu() { return _statsInventoryMenu; }

    int64_t getValueMultiplier() { return _valueMultiplier; }

    float getCap() { return _cap; }

    std::string getDisplay(std::string a_value) {
        if (!a_value.empty()) {
            logger::trace("display {} got value {}, building text ..."sv, _displayName, a_value);
            return MenuUtil::buildDisplayString(a_value, _displayName, _ending, false);
        }
        return "";
    }

    void logStatConfig(StatsValue a_stats_value) {
        logger::trace(
            "name {}, actor {}, displayName ({}), ending {}, statsMenu {}, statsInventoryMenu {}, valueMultiplier {}, cap {}"sv,
            a_stats_value,
            _actor,
            _displayName,
            _ending,
            _statsMenu,
            _statsInventoryMenu,
            _valueMultiplier,
            _cap);
    }

    StatConfig() = delete;
    StatConfig(const StatConfig&) = default;
    StatConfig(StatConfig&&) = delete;

    ~StatConfig() = default;

    StatConfig& operator=(const StatConfig&) = default;
    StatConfig& operator=(StatConfig&&) = delete;

private:
    RE::ActorValue _actor;
    std::string _displayName;
    std::string _ending = "";
    StatsMenuValue _statsMenu;
    StatsInventoryMenuValue _statsInventoryMenu;
    int64_t _valueMultiplier = _constStaticMultiplier;
    float _cap = -1;
};


class StatSetting {
    using StatsMap = std::map<StatsValue, std::unique_ptr<StatConfig>>;
    using ActorValue = RE::ActorValue;
    using StatsInventoryMenuValue = MenuUtil::StatsInventoryMenuValue;
    using StatsMenuValue = MenuUtil::StatsMenuValue;

public:
    static StatSetting* GetSingleton() {
        static StatSetting singleton;
        return std::addressof(singleton);
    }

    StatsMap load() {
        StatsMap mp;

        auto gameSettings = GameSettings::GetSingleton();
        if (*Settings::showResistanceCap) {
            gameSettings->getAndSetSettings();
        }

        mp[StatsValue::name] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::nameString,
            StatsMenuValue::mSpecial,
            StatsInventoryMenuValue::mNone);
        mp[StatsValue::race] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::raceString,
            StatsMenuValue::mSpecial,
            StatsInventoryMenuValue::mNone);
        mp[StatsValue::level] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::levelString,
            StatsMenuValue::mSpecial,
            StatsInventoryMenuValue::mNone);
        mp[StatsValue::perkCount] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::perkCountString,
            StatsMenuValue::mSpecial,
            StatsInventoryMenuValue::mNone);
        mp[StatsValue::height] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::heightString,
            *Settings::heightStringEnding,
            MenuUtil::getStatsMenu(*Settings::heightMenu),
            StatsInventoryMenuValue::mNone);
        mp[StatsValue::equipedWeight] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::equipedWeightString,
            *Settings::equipedWeightStringEnding,
            MenuUtil::getStatsMenu(*Settings::equipedWeightMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::equipedWeightMenuInventory));
        mp[StatsValue::weight] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::weightString,
            *Settings::weightStringEnding,
            MenuUtil::getStatsMenu(*Settings::weightMenu),
            StatsInventoryMenuValue::mNone);
        mp[StatsValue::armor] = std::make_unique<StatConfig>(ActorValue::kDamageResist,
            *Settings::armorString,
            MenuUtil::getStatsMenu(*Settings::armorMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::armorMenuInventory));
        mp[StatsValue::damage] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::damageString,
            MenuUtil::getStatsMenu(*Settings::damageMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::damageMenuInventory));
        mp[StatsValue::skillTrainingsThisLevel] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::skillTrainingsThisLevelString,
            MenuUtil::getStatsMenu(*Settings::skillTrainingsThisLevelMenu),
            StatsInventoryMenuValue::mNone);
        mp[StatsValue::health] = std::make_unique<StatConfig>(ActorValue::kHealth,
            *Settings::healthString,
            MenuUtil::getStatsMenu(*Settings::healthMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::healthMenuInventory));
        mp[StatsValue::healthRatePer] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::healthRateString,
            *Settings::healthRateStringEnding,
            MenuUtil::getStatsMenu(*Settings::healthRateMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::healthRateMenuInventory));
        mp[StatsValue::magicka] = std::make_unique<StatConfig>(ActorValue::kMagicka,
            *Settings::magickaString,
            MenuUtil::getStatsMenu(*Settings::magickaMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::magickaMenuInventory));
        mp[StatsValue::magickaRatePer] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::magickaRateString,
            *Settings::magickaRateStringEnding,
            MenuUtil::getStatsMenu(*Settings::magickaRateMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::magickaRateMenuInventory));
        mp[StatsValue::stamina] = std::make_unique<StatConfig>(ActorValue::kStamina,
            *Settings::staminaString,
            MenuUtil::getStatsMenu(*Settings::staminaMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::magickaRateMenuInventory));
        mp[StatsValue::staminaRatePer] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::staminaRateString,
            *Settings::staminaRateStringEnding,
            MenuUtil::getStatsMenu(*Settings::staminaRateMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::staminaMenuInventory));
        mp[StatsValue::resistDamage] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::resistDamageString,
            *Settings::resistDamageStringEnding,
            MenuUtil::getStatsMenu(*Settings::resistDamageMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::resistDamageMenuInventory),
            _constStaticMultiplier,
            gameSettings->maxArmorResistance);
        mp[StatsValue::resistDisease] = std::make_unique<StatConfig>(ActorValue::kResistDisease,
            *Settings::resistDiseaseString,
            *Settings::resistDiseaseStringEnding,
            MenuUtil::getStatsMenu(*Settings::resistDiseaseMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::resistDiseaseMenuInventory));
        mp[StatsValue::resistPoison] = std::make_unique<StatConfig>(ActorValue::kPoisonResist,
            *Settings::resistPoisonString,
            *Settings::resistPoisonStringEnding,
            MenuUtil::getStatsMenu(*Settings::resistPoisonMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::resistPoisonMenuInventory),
            _constStaticMultiplier,
            gameSettings->maxResistance);
        mp[StatsValue::resistFire] = std::make_unique<StatConfig>(ActorValue::kResistFire,
            *Settings::resistFireString,
            *Settings::resistFireStringEnding,
            MenuUtil::getStatsMenu(*Settings::resistFireMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::resistFireMenuInventory),
            _constStaticMultiplier,
            gameSettings->maxResistance);
        mp[StatsValue::resistShock] = std::make_unique<StatConfig>(ActorValue::kResistShock,
            *Settings::resistShockString,
            *Settings::resistShockStringEnding,
            MenuUtil::getStatsMenu(*Settings::resistShockMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::resistShockMenuInventory),
            _constStaticMultiplier,
            gameSettings->maxResistance);
        mp[StatsValue::resistFrost] = std::make_unique<StatConfig>(ActorValue::kResistFrost,
            *Settings::resistFrostString,
            *Settings::resistFrostStringEnding,
            MenuUtil::getStatsMenu(*Settings::resistFrostMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::resistFrostMenuInventory),
            _constStaticMultiplier,
            gameSettings->maxResistance);
        mp[StatsValue::resistMagic] = std::make_unique<StatConfig>(ActorValue::kResistMagic,
            *Settings::resistMagicString,
            *Settings::resistMagicStringEnding,
            MenuUtil::getStatsMenu(*Settings::resistMagicMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::resistMagicMenuInventory),
            _constStaticMultiplier,
            gameSettings->maxResistance);
        mp[StatsValue::oneHanded] = std::make_unique<StatConfig>(ActorValue::kOneHanded,
            *Settings::oneHandedString,
            MenuUtil::getStatsMenu(*Settings::oneHandedMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::oneHandedMenuInventory));
        mp[StatsValue::twoHanded] = std::make_unique<StatConfig>(ActorValue::kTwoHanded,
            *Settings::twoHandedString,
            MenuUtil::getStatsMenu(*Settings::twoHandedMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::twoHandedMenuInventory));
        mp[StatsValue::archery] = std::make_unique<StatConfig>(ActorValue::kArchery,
            *Settings::archeryString,
            MenuUtil::getStatsMenu(*Settings::archeryMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::archeryMenuInventory));
        mp[StatsValue::block] = std::make_unique<StatConfig>(ActorValue::kBlock,
            *Settings::blockString,
            MenuUtil::getStatsMenu(*Settings::blockMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::blockMenuInventory));
        mp[StatsValue::smithing] = std::make_unique<StatConfig>(ActorValue::kSmithing,
            *Settings::smithingString,
            MenuUtil::getStatsMenu(*Settings::smithingMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::smithingMenuInventory));
        mp[StatsValue::heavyArmor] = std::make_unique<StatConfig>(ActorValue::kHeavyArmor,
            *Settings::heavyArmorString,
            MenuUtil::getStatsMenu(*Settings::heavyArmorMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::heavyArmorMenuInventory));
        mp[StatsValue::lightArmor] = std::make_unique<StatConfig>(ActorValue::kLightArmor,
            *Settings::lightArmorString,
            MenuUtil::getStatsMenu(*Settings::lightArmorMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::lightArmorMenuInventory));
        mp[StatsValue::pickpocket] = std::make_unique<StatConfig>(ActorValue::kPickpocket,
            *Settings::pickpocketString,
            MenuUtil::getStatsMenu(*Settings::pickpocketMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::pickpocketMenuInventory));
        mp[StatsValue::lockpicking] = std::make_unique<StatConfig>(ActorValue::kLockpicking,
            *Settings::lockpickingString,
            MenuUtil::getStatsMenu(*Settings::lockpickingMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::lockpickingMenuInventory));
        mp[StatsValue::sneak] = std::make_unique<StatConfig>(ActorValue::kSneak,
            *Settings::sneakString,
            MenuUtil::getStatsMenu(*Settings::sneakMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::sneakMenuInventory));
        mp[StatsValue::alchemy] = std::make_unique<StatConfig>(ActorValue::kAlchemy,
            *Settings::alchemyString,
            MenuUtil::getStatsMenu(*Settings::alchemyMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::alchemyMenuInventory));
        mp[StatsValue::speech] = std::make_unique<StatConfig>(ActorValue::kSpeech,
            *Settings::speechString,
            MenuUtil::getStatsMenu(*Settings::speechMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::speechMenuInventory));
        mp[StatsValue::enchanting] = std::make_unique<StatConfig>(ActorValue::kEnchanting,
            *Settings::enchantingString,
            MenuUtil::getStatsMenu(*Settings::enchantingMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::enchantingMenuInventory));
        mp[StatsValue::alteration] = std::make_unique<StatConfig>(ActorValue::kAlteration,
            *Settings::alterationString,
            MenuUtil::getStatsMenu(*Settings::alterationMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::alterationMenuInventory));
        mp[StatsValue::conjuration] = std::make_unique<StatConfig>(ActorValue::kConjuration,
            *Settings::conjurationString,
            MenuUtil::getStatsMenu(*Settings::conjurationMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::conjurationMenuInventory));
        mp[StatsValue::destruction] = std::make_unique<StatConfig>(ActorValue::kDestruction,
            *Settings::destructionString,
            MenuUtil::getStatsMenu(*Settings::destructionMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::destructionMenuInventory));
        mp[StatsValue::illusion] = std::make_unique<StatConfig>(ActorValue::kIllusion,
            *Settings::illusionString,
            MenuUtil::getStatsMenu(*Settings::illusionMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::illusionMenuInventory));
        mp[StatsValue::restoration] = std::make_unique<StatConfig>(ActorValue::kRestoration,
            *Settings::restorationString,
            MenuUtil::getStatsMenu(*Settings::restorationMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::restorationMenuInventory));
        mp[StatsValue::oneHandedPowerMod] = std::make_unique<StatConfig>(ActorValue::kOneHandedPowerModifier,
            *Settings::oneHandedPowerModString,
            MenuUtil::getStatsMenu(*Settings::oneHandedPowerModMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::oneHandedPowerModMenuInventory));
        mp[StatsValue::twoHandedPowerMod] = std::make_unique<StatConfig>(ActorValue::kTwoHandedPowerModifier,
            *Settings::twoHandedPowerModString,
            MenuUtil::getStatsMenu(*Settings::twoHandedPowerModMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::twoHandedPowerModMenuInventory));
        mp[StatsValue::archeryPowerMod] = std::make_unique<StatConfig>(ActorValue::kMarksmanPowerModifier,
            *Settings::archeryPowerModString,
            MenuUtil::getStatsMenu(*Settings::archeryPowerModMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::archeryPowerModMenuInventory));
        mp[StatsValue::blockPowerMod] = std::make_unique<StatConfig>(ActorValue::kBlockPowerModifier,
            *Settings::blockPowerModString,
            MenuUtil::getStatsMenu(*Settings::blockPowerModMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::blockPowerModMenuInventory));
        mp[StatsValue::smithingPowerMod] = std::make_unique<StatConfig>(ActorValue::kSmithingPowerModifier,
            *Settings::smithingPowerModString,
            MenuUtil::getStatsMenu(*Settings::smithingPowerModMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::smithingPowerModMenuInventory));
        mp[StatsValue::heavyArmorPowerMod] = std::make_unique<StatConfig>(ActorValue::kHeavyArmorPowerModifier,
            *Settings::heavyArmorPowerModString,
            MenuUtil::getStatsMenu(*Settings::heavyArmorPowerModMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::heavyArmorPowerModMenuInventory));
        mp[StatsValue::lightArmorPowerMod] = std::make_unique<StatConfig>(ActorValue::kLightArmorPowerModifier,
            *Settings::lightArmorPowerModString,
            MenuUtil::getStatsMenu(*Settings::lightArmorPowerModMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::lightArmorPowerModMenuInventory));
        mp[StatsValue::pickpocketPowerMod] = std::make_unique<StatConfig>(ActorValue::kPickpocketPowerModifier,
            *Settings::pickpocketPowerModString,
            MenuUtil::getStatsMenu(*Settings::pickpocketPowerModMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::pickpocketPowerModMenuInventory));
        mp[StatsValue::lockpickingPowerMod] = std::make_unique<StatConfig>(ActorValue::kLockpickingPowerModifier,
            *Settings::lockpickingPowerModString,
            MenuUtil::getStatsMenu(*Settings::lockpickingPowerModMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::lockpickingPowerModMenuInventory));
        mp[StatsValue::sneakPowerMod] = std::make_unique<StatConfig>(ActorValue::kSneakingPowerModifier,
            *Settings::sneakPowerModString,
            MenuUtil::getStatsMenu(*Settings::sneakPowerModMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::sneakPowerModMenuInventory));
        mp[StatsValue::alchemyPowerMod] = std::make_unique<StatConfig>(ActorValue::kAlchemyPowerModifier,
            *Settings::alchemyPowerModString,
            MenuUtil::getStatsMenu(*Settings::alchemyPowerModMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::alchemyPowerModMenuInventory));
        mp[StatsValue::speechPowerMod] = std::make_unique<StatConfig>(ActorValue::kSpeechcraftPowerModifier,
            *Settings::speechPowerModString,
            MenuUtil::getStatsMenu(*Settings::speechPowerModMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::speechPowerModMenuInventory));
        mp[StatsValue::enchantingPowerMod] = std::make_unique<StatConfig>(ActorValue::kEnchantingPowerModifier,
            *Settings::enchantingPowerModString,
            MenuUtil::getStatsMenu(*Settings::enchantingPowerModMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::enchantingPowerModMenuInventory));
        mp[StatsValue::alterationPowerMod] = std::make_unique<StatConfig>(ActorValue::kAlterationPowerModifier,
            *Settings::alterationPowerModString,
            MenuUtil::getStatsMenu(*Settings::alterationPowerModMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::alterationPowerModMenuInventory));
        mp[StatsValue::conjurationPowerMod] = std::make_unique<StatConfig>(ActorValue::kConjurationPowerModifier,
            *Settings::conjurationPowerModString,
            MenuUtil::getStatsMenu(*Settings::conjurationPowerModMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::conjurationPowerModMenuInventory));
        mp[StatsValue::destructionPowerMod] = std::make_unique<StatConfig>(ActorValue::kDestructionPowerModifier,
            *Settings::destructionPowerModString,
            MenuUtil::getStatsMenu(*Settings::destructionPowerModMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::destructionPowerModMenuInventory));
        mp[StatsValue::illusionPowerMod] = std::make_unique<StatConfig>(ActorValue::kIllusionPowerModifier,
            *Settings::illusionPowerModString,
            MenuUtil::getStatsMenu(*Settings::illusionPowerModMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::illusionPowerModMenuInventory));
        mp[StatsValue::restorationPowerMod] = std::make_unique<StatConfig>(ActorValue::kRestorationPowerModifier,
            *Settings::restorationPowerModString,
            MenuUtil::getStatsMenu(*Settings::restorationPowerModMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::restorationPowerModMenuInventory));
        mp[StatsValue::speedMult] = std::make_unique<StatConfig>(ActorValue::kSpeedMult,
            *Settings::speedMultString,
            *Settings::speedMultStringEnding,
            MenuUtil::getStatsMenu(*Settings::speedMultMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::speedMultMenuInventory));
        mp[StatsValue::inventoryWeight] = std::make_unique<StatConfig>(ActorValue::kInventoryWeight,
            *Settings::inventoryWeightString,
            *Settings::inventoryWeightStringEnding,
            MenuUtil::getStatsMenu(*Settings::inventoryWeightMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::inventoryWeightMenuInventory));
        mp[StatsValue::carryWeight] = std::make_unique<StatConfig>(ActorValue::kCarryWeight,
            *Settings::carryWeightString,
            *Settings::carryWeightStringEnding,
            MenuUtil::getStatsMenu(*Settings::carryWeightMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::carryWeightMenuInventory));
        mp[StatsValue::criticalChance] = std::make_unique<StatConfig>(ActorValue::kCriticalChance,
            *Settings::criticalChanceString,
            *Settings::criticalChanceStringEnding,
            MenuUtil::getStatsMenu(*Settings::criticalChanceMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::criticalChanceMenuInventory));
        mp[StatsValue::meleeDamage] = std::make_unique<StatConfig>(ActorValue::kMeleeDamage,
            *Settings::meleeDamageString,
            MenuUtil::getStatsMenu(*Settings::meleeDamageMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::meleeDamageMenuInventory));
        mp[StatsValue::unarmedDamage] = std::make_unique<StatConfig>(ActorValue::kUnarmedDamage,
            *Settings::unarmedDamageString,
            MenuUtil::getStatsMenu(*Settings::unarmedDamageMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::unarmedDamageMenuInventory));
        mp[StatsValue::absorbChance] = std::make_unique<StatConfig>(ActorValue::kAbsorbChance,
            *Settings::absorbChanceString,
            *Settings::absorbChanceStringEnding,
            MenuUtil::getStatsMenu(*Settings::absorbChanceMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::absorbChanceMenuInventory));
        //we will not set the actor value kWeaponSpeedMult and kLeftWeaponSpeedMultiply here, because some genius thought it is nice that the value 0 and 1 means 100%
        // https://en.uesp.net/wiki/Skyrim_Mod:Actor_Value_Indices as documented here
        mp[StatsValue::weaponSpeedMult] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::weaponSpeedMultString,
            *Settings::weaponSpeedMultStringEnding,
            MenuUtil::getStatsMenu(*Settings::weaponSpeedMultMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::weaponSpeedMultMenuInventory),
            MenuUtil::getMultiplier(*Settings::weaponSpeedMultMult));
        mp[StatsValue::leftWeaponSpeedMult] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::leftWeaponSpeedMultString,
            *Settings::leftWeaponSpeedMultStringEnding,
            MenuUtil::getStatsMenu(*Settings::leftWeaponSpeedMultMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::leftWeaponSpeedMultMenuInventory),
            MenuUtil::getMultiplier(*Settings::leftWeaponSpeedMultMult));
        mp[StatsValue::rightItemCharge] = std::make_unique<StatConfig>(ActorValue::kRightItemCharge,
            *Settings::rightItemChargeString,
            MenuUtil::getStatsMenu(*Settings::rightItemChargeMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::rightItemChargeMenuInventory));
        mp[StatsValue::leftItemCharge] = std::make_unique<StatConfig>(ActorValue::kLeftItemCharge,
            *Settings::leftItemChargStringe,
            MenuUtil::getStatsMenu(*Settings::leftItemChargeMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::leftItemChargeMenuInventory));
        mp[StatsValue::armorPerks] = std::make_unique<StatConfig>(ActorValue::kArmorPerks,
            *Settings::armorPerksString,
            *Settings::armorPerksStringEnding,
            MenuUtil::getStatsMenu(*Settings::armorPerksMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::armorPerksMenuInventory),
            MenuUtil::getMultiplier(*Settings::armorPerksMult));
        mp[StatsValue::mass] = std::make_unique<StatConfig>(ActorValue::kMass,
            *Settings::massString,
            MenuUtil::getStatsMenu(*Settings::massMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::massMenuInventory));
        mp[StatsValue::bowStaggerBonus] = std::make_unique<StatConfig>(ActorValue::kBowStaggerBonus,
            *Settings::bowStaggerBonusString,
            MenuUtil::getStatsMenu(*Settings::bowStaggerBonusMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::bowStaggerBonusMenuInventory));
        mp[StatsValue::bypassVendorKeywordCheck] = std::make_unique<StatConfig>(ActorValue::kBypassVendorKeywordCheck,
            *Settings::bypassVendorKeywordCheckString,
            MenuUtil::getStatsMenu(*Settings::bypassVendorKeywordCheckMenu),
            StatsInventoryMenuValue::mNone);
        mp[StatsValue::bypassVendorStolenCheck] = std::make_unique<StatConfig>(ActorValue::kBypassVendorStolenCheck,
            *Settings::bypassVendorStolenCheckString,
            MenuUtil::getStatsMenu(*Settings::bypassVendorStolenCheckMenu),
            StatsInventoryMenuValue::mNone);
        mp[StatsValue::bowSpeedBonus] = std::make_unique<StatConfig>(ActorValue::kBowSpeedBonus,
            *Settings::bowSpeedBonusString,
            *Settings::bowSpeedBonusStringEnding,
            MenuUtil::getStatsMenu(*Settings::bowSpeedBonusMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::bowSpeedBonusMenuInventory));
        mp[StatsValue::shoutRecoveryMult] = std::make_unique<StatConfig>(ActorValue::kShoutRecoveryMult,
            *Settings::shoutRecoveryMultString,
            *Settings::shoutRecoveryMultStringEnding,
            MenuUtil::getStatsMenu(*Settings::shoutRecoveryMultMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::shoutRecoveryMultMenuInventory),
            MenuUtil::getMultiplier(*Settings::shoutRecoveryMultMult));
        mp[StatsValue::movementNoiseMult] = std::make_unique<StatConfig>(ActorValue::kMovementNoiseMult,
            *Settings::movementNoiseMultString,
            *Settings::movementNoiseMultStringEnding,
            MenuUtil::getStatsMenu(*Settings::movementNoiseMultMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::movementNoiseMultMenuInventory),
            MenuUtil::getMultiplier(*Settings::movementNoiseMultMult));
        mp[StatsValue::dragonSouls] = std::make_unique<StatConfig>(ActorValue::kDragonSouls,
            *Settings::dragonSoulsString,
            MenuUtil::getStatsMenu(*Settings::dragonSoulsMenu),
            StatsInventoryMenuValue::mNone);
        mp[StatsValue::combatHealthRegenMultiply] = std::make_unique<StatConfig>(ActorValue::kCombatHealthRegenMultiply,
            *Settings::combatHealthRegenMultiplyString,
            *Settings::combatHealthRegenMultiplyStringEnding,
            MenuUtil::getStatsMenu(*Settings::combatHealthRegenMultiplyMenu),
            StatsInventoryMenuValue::mNone,
            MenuUtil::getMultiplier(*Settings::combatHealthRegenMultiplyMult));
        mp[StatsValue::attackDamageMult] = std::make_unique<StatConfig>(ActorValue::kAttackDamageMult,
            *Settings::attackDamageMultString,
            *Settings::attackDamageMultStringEnding,
            MenuUtil::getStatsMenu(*Settings::attackDamageMultMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::attackDamageMultMenuInventory));
        mp[StatsValue::beast] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::beastString,
            StatsMenuValue::mSpecial,
            StatsInventoryMenuValue::mNone);
        mp[StatsValue::xp] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::xpString,
            StatsMenuValue::mSpecial,
            StatsInventoryMenuValue::mNone);
        mp[StatsValue::reflectDamage] = std::make_unique<StatConfig>(ActorValue::kReflectDamage,
            *Settings::reflectDamageString,
            *Settings::reflectDamageStringEnding,
            MenuUtil::getStatsMenu(*Settings::reflectDamageMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::reflectDamageMenuInventory));
        mp[StatsValue::oneHandedMod] = std::make_unique<StatConfig>(ActorValue::kOneHandedModifier,
            *Settings::oneHandedModString,
            *Settings::oneHandedModStringEnding,
            MenuUtil::getStatsMenu(*Settings::oneHandedModMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::oneHandedModMenuInventory));
        mp[StatsValue::twoHandedMod] = std::make_unique<StatConfig>(ActorValue::kTwoHandedModifier,
            *Settings::twoHandedModString,
            *Settings::twoHandedModStringEnding,
            MenuUtil::getStatsMenu(*Settings::twoHandedModMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::twoHandedModMenuInventory));
        mp[StatsValue::marksmanMod] = std::make_unique<StatConfig>(ActorValue::kMarksmanModifier,
            *Settings::archeryModString,
            *Settings::archeryModStringEnding,
            MenuUtil::getStatsMenu(*Settings::archeryModMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::archeryModMenuInventory));
        mp[StatsValue::blockMod] = std::make_unique<StatConfig>(ActorValue::kBlockModifier,
            *Settings::blockModString,
            *Settings::blockModStringEnding,
            MenuUtil::getStatsMenu(*Settings::blockModMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::blockModMenuInventory));
        mp[StatsValue::smithingMod] = std::make_unique<StatConfig>(ActorValue::kSmithingModifier,
            *Settings::smithingModString,
            *Settings::smithingModStringEnding,
            MenuUtil::getStatsMenu(*Settings::smithingModMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::smithingModMenuInventory));
        mp[StatsValue::heavyArmorMod] = std::make_unique<StatConfig>(ActorValue::kHeavyArmorModifier,
            *Settings::heavyArmorModString,
            *Settings::heavyArmorModStringEnding,
            MenuUtil::getStatsMenu(*Settings::heavyArmorModMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::heavyArmorModMenuInventory));
        mp[StatsValue::lightArmorMod] = std::make_unique<StatConfig>(ActorValue::kLightArmorModifier,
            *Settings::lightArmorModString,
            *Settings::lightArmorModStringEnding,
            MenuUtil::getStatsMenu(*Settings::lightArmorModMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::lightArmorModMenuInventory));
        mp[StatsValue::pickpocketMod] = std::make_unique<StatConfig>(ActorValue::kPickpocketModifier,
            *Settings::pickpocketModString,
            *Settings::pickpocketModStringEnding,
            MenuUtil::getStatsMenu(*Settings::pickpocketModMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::pickpocketModMenuInventory));
        mp[StatsValue::lockpickingMod] = std::make_unique<StatConfig>(ActorValue::kLockpickingModifier,
            *Settings::lockpickingModString,
            *Settings::lockpickingModStringEnding,
            MenuUtil::getStatsMenu(*Settings::lockpickingModMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::lockpickingModMenuInventory));
        mp[StatsValue::sneakingMod] = std::make_unique<StatConfig>(ActorValue::kSneakingModifier,
            *Settings::sneakModString,
            *Settings::sneakModStringEnding,
            MenuUtil::getStatsMenu(*Settings::sneakModMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::sneakModMenuInventory));
        mp[StatsValue::alchemyMod] = std::make_unique<StatConfig>(ActorValue::kAlchemyModifier,
            *Settings::alchemyModString,
            *Settings::alchemyModStringEnding,
            MenuUtil::getStatsMenu(*Settings::alchemyModMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::alchemyModMenuInventory));
        mp[StatsValue::speechcraftMod] = std::make_unique<StatConfig>(ActorValue::kSpeechcraftModifier,
            *Settings::speechModString,
            *Settings::speechModStringEnding,
            MenuUtil::getStatsMenu(*Settings::speechModMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::speechModMenuInventory));
        mp[StatsValue::enchantingMod] = std::make_unique<StatConfig>(ActorValue::kEnchantingModifier,
            *Settings::enchantingModString,
            *Settings::enchantingModStringEnding,
            MenuUtil::getStatsMenu(*Settings::enchantingModMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::enchantingModMenuInventory));
        mp[StatsValue::alterationMod] = std::make_unique<StatConfig>(ActorValue::kAlterationModifier,
            *Settings::alterationModString,
            *Settings::alterationModStringEnding,
            MenuUtil::getStatsMenu(*Settings::alterationModMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::alterationModMenuInventory));
        mp[StatsValue::conjurationMod] = std::make_unique<StatConfig>(ActorValue::kConjurationModifier,
            *Settings::conjurationModString,
            *Settings::conjurationModStringEnding,
            MenuUtil::getStatsMenu(*Settings::conjurationModMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::conjurationModMenuInventory));
        mp[StatsValue::destructionMod] = std::make_unique<StatConfig>(ActorValue::kDestructionModifier,
            *Settings::destructionModString,
            *Settings::destructionModStringEnding,
            MenuUtil::getStatsMenu(*Settings::destructionModMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::destructionModMenuInventory));
        mp[StatsValue::illusionMod] = std::make_unique<StatConfig>(ActorValue::kIllusionModifier,
            *Settings::illusionModString,
            *Settings::illusionModStringEnding,
            MenuUtil::getStatsMenu(*Settings::illusionModMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::illusionModMenuInventory));
        mp[StatsValue::restorationMod] = std::make_unique<StatConfig>(ActorValue::kRestorationModifier,
            *Settings::restorationModString,
            *Settings::restorationModStringEnding,
            MenuUtil::getStatsMenu(*Settings::restorationModMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::restorationModMenuInventory));
        mp[StatsValue::damageArrow] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::damageArrowString,
            MenuUtil::getStatsMenu(*Settings::damageArrowMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::damageArrowMenuInventory));
        mp[StatsValue::damageLeft] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::damageLeftString,
            MenuUtil::getStatsMenu(*Settings::damageLeftMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::damageLeftMenuInventory));
        mp[StatsValue::weaponReach] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::weaponReachString,
            MenuUtil::getStatsMenu(*Settings::weaponReachMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::weaponReachMenuInventory));
        mp[StatsValue::weaponReachLeft] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::weaponReachLeftString,
            MenuUtil::getStatsMenu(*Settings::weaponReachLeftMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::weaponReachLeftMenuInventory));
        mp[StatsValue::weaponBaseDamage] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::weaponBaseDamageString,
            MenuUtil::getStatsMenu(*Settings::weaponBaseDamageMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::weaponBaseDamageMenuInventory));
        mp[StatsValue::weaponBaseDamageLeft] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::weaponBaseDamageLeftString,
            MenuUtil::getStatsMenu(*Settings::weaponBaseDamageLeftMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::weaponBaseDamageLeftMenuInventory));
        mp[StatsValue::weaponStagger] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::weaponStaggerString,
            MenuUtil::getStatsMenu(*Settings::weaponStaggerMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::weaponStaggerMenuInventory));
        mp[StatsValue::weaponStaggerLeft] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::weaponStaggerLeftString,
            MenuUtil::getStatsMenu(*Settings::weaponStaggerLeftMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::weaponStaggerLeftMenuInventory));
        mp[StatsValue::weaponCritDamageRating] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::weaponCritDamageRatingString,
            MenuUtil::getStatsMenu(*Settings::weaponCritDamageRatingMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::weaponCritDamageRatingMenuInventory));
        mp[StatsValue::weaponCritDamageRatingLeft] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::weaponCritDamageRatingLeftString,
            MenuUtil::getStatsMenu(*Settings::weaponCritDamageRatingLeftMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::weaponCritDamageRatingLeftMenuInventory));
        mp[StatsValue::fallDamageMod] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::fallDamageModString,
            *Settings::fallDamageModStringEnding,
            MenuUtil::getStatsMenu(*Settings::fallDamageModMenu),
            MenuUtil::getStatsInventoryMenu(*Settings::fallDamageModMenuInventory),
            MenuUtil::getMultiplier(*Settings::fallDamageModMult));
        return mp;
    }

    StatSetting() = default;
    StatSetting(const StatSetting&) = default;
    StatSetting(StatSetting&&) = delete;

    ~StatSetting() = default;

    StatSetting& operator=(const StatSetting&) = default;
    StatSetting& operator=(StatSetting&&) = delete;
};
