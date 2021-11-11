#pragma once
#include "settings/gamesettings.h"

class StatConfig {
public:
    StatConfig(RE::ActorValue a_actor,
        std::string a_display_name,
        std::string a_ending,
        bool a_show,
        StatsMenuValue a_stats_menu)
        : _actor(a_actor), _displayName(a_display_name), _ending(a_ending), _show(a_show), _statsMenu(a_stats_menu) {}

    StatConfig(RE::ActorValue a_actor,
        std::string a_display_name,
        std::string a_ending,
        bool a_show,
        StatsMenuValue a_stats_menu,
        int64_t a_value_multiplier)
        : _actor(a_actor)
        , _displayName(a_display_name)
        , _ending(a_ending)
        , _show(a_show)
        , _statsMenu(a_stats_menu)
        , _valueMultiplier(a_value_multiplier) {}

    StatConfig(RE::ActorValue a_actor,
        std::string a_display_name,
        std::string a_ending,
        bool a_show,
        StatsMenuValue a_stats_menu,
        int64_t a_value_multiplier,
        float a_cap)
        : _actor(a_actor)
        , _displayName(a_display_name)
        , _ending(a_ending)
        , _show(a_show)
        , _statsMenu(a_stats_menu)
        , _valueMultiplier(a_value_multiplier)
        , _cap(a_cap) {}

    RE::ActorValue getActor() { return _actor; }

    std::string getDisplayName() { return _displayName; }

    std::string getEnding() { return _ending; }

    bool getShow() { return _show; }

    StatsMenuValue getMenu() { return _statsMenu; }

    int64_t getValueMultiplier() { return _valueMultiplier; }

    float getCap() { return _cap; }

    std::string getDisplay(std::string a_value) {
        if (!a_value.empty()) {
            logger::trace("display {} got value {}, building text ..."sv, _displayName, a_value);
            return buildDisplayString(a_value, _displayName, _ending, _show, false);
        }
        return "";
    }

    void logStatConfig(StatsValue a_stats_value) {
        logger::trace("name {}, actor {}, displayName ({}), ending {}, show {}, menu {}, valueMultiplier {}, cap {}"sv,
            a_stats_value,
            _actor,
            _displayName,
            _ending,
            _show,
            _statsMenu,
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
    std::string _ending;
    bool _show;
    StatsMenuValue _statsMenu;
    int64_t _valueMultiplier = _constStaticMultiplier;
    float _cap = -1;
};


class StatSetting {
    using StatsMap = std::map<StatsValue, std::unique_ptr<StatConfig>>;
    using ActorValue = RE::ActorValue;

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

        /*change to brace init*/
        mp[StatsValue::name] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::nameString,
            *Settings::nameStringEnding,
            *Settings::name,
            StatsMenuValue::mNone);
        mp[StatsValue::race] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::raceString,
            *Settings::raceStringEnding,
            *Settings::race,
            StatsMenuValue::mNone);
        mp[StatsValue::level] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::levelString,
            *Settings::levelStringEnding,
            *Settings::level,
            StatsMenuValue::mNone);
        mp[StatsValue::perkCount] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::perkCountString,
            *Settings::perkCountStringEnding,
            *Settings::perkCount,
            StatsMenuValue::mNone);
        mp[StatsValue::height] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::heightString,
            *Settings::heightStringEnding,
            *Settings::height,
            getStatsMenu(*Settings::heightMenu));
        mp[StatsValue::equipedWeight] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::equipedWeightString,
            *Settings::equipedWeightStringEnding,
            *Settings::equipedWeight,
            getStatsMenu(*Settings::equipedWeightMenu));
        mp[StatsValue::weight] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::weightString,
            *Settings::weightStringEnding,
            *Settings::weight,
            getStatsMenu(*Settings::weightMenu));
        mp[StatsValue::armor] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::armorString,
            *Settings::armorStringEnding,
            *Settings::armor,
            getStatsMenu(*Settings::armorMenu));
        mp[StatsValue::damage] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::damageString,
            *Settings::damageStringEnding,
            *Settings::damage,
            getStatsMenu(*Settings::damageMenu));
        mp[StatsValue::skillTrainingsThisLevel] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::skillTrainingsThisLevelString,
            *Settings::skillTrainingsThisLevelStringEnding,
            *Settings::skillTrainingsThisLevel,
            getStatsMenu(*Settings::skillTrainingsThisLevelMenu));
        mp[StatsValue::health] = std::make_unique<StatConfig>(ActorValue::kHealth,
            *Settings::healthString,
            *Settings::healthStringEnding,
            *Settings::health,
            getStatsMenu(*Settings::healthMenu));
        mp[StatsValue::healthRatePer] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::healthRateString,
            *Settings::healthRateStringEnding,
            *Settings::healthRate,
            getStatsMenu(*Settings::healthRateMenu));
        mp[StatsValue::magicka] = std::make_unique<StatConfig>(ActorValue::kMagicka,
            *Settings::magickaString,
            *Settings::magickaStringEnding,
            *Settings::magicka,
            getStatsMenu(*Settings::magickaMenu));
        mp[StatsValue::magickaRatePer] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::magickaRateString,
            *Settings::magickaRateStringEnding,
            *Settings::magickaRate,
            getStatsMenu(*Settings::magickaRateMenu));
        mp[StatsValue::stamina] = std::make_unique<StatConfig>(ActorValue::kStamina,
            *Settings::staminaString,
            *Settings::staminaStringEnding,
            *Settings::stamina,
            getStatsMenu(*Settings::staminaMenu));
        mp[StatsValue::staminaRatePer] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::staminaRateString,
            *Settings::staminaRateStringEnding,
            *Settings::staminaRate,
            getStatsMenu(*Settings::staminaRateMenu));
        mp[StatsValue::resistDamage] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::resistDamageString,
            *Settings::resistDamageStringEnding,
            *Settings::resistDamage,
            getStatsMenu(*Settings::resistDamageMenu),
            _constStaticMultiplier,
            gameSettings->maxArmorResistance);
        mp[StatsValue::resistDisease] = std::make_unique<StatConfig>(ActorValue::kResistDisease,
            *Settings::resistDiseaseString,
            *Settings::resistDiseaseStringEnding,
            *Settings::resistDisease,
            getStatsMenu(*Settings::resistDiseaseMenu));
        mp[StatsValue::resistPoison] = std::make_unique<StatConfig>(ActorValue::kPoisonResist,
            *Settings::resistPoisonString,
            *Settings::resistPoisonStringEnding,
            *Settings::resistPoison,
            getStatsMenu(*Settings::resistPoisonMenu),
            _constStaticMultiplier,
            gameSettings->maxResistance);
        mp[StatsValue::resistFire] = std::make_unique<StatConfig>(ActorValue::kResistFire,
            *Settings::resistFireString,
            *Settings::resistFireStringEnding,
            *Settings::resistFire,
            getStatsMenu(*Settings::resistFireMenu),
            _constStaticMultiplier,
            gameSettings->maxResistance);
        mp[StatsValue::resistShock] = std::make_unique<StatConfig>(ActorValue::kResistShock,
            *Settings::resistShockString,
            *Settings::resistShockStringEnding,
            *Settings::resistShock,
            getStatsMenu(*Settings::resistShockMenu),
            _constStaticMultiplier,
            gameSettings->maxResistance);
        mp[StatsValue::resistFrost] = std::make_unique<StatConfig>(ActorValue::kResistFrost,
            *Settings::resistFrostString,
            *Settings::resistFrostStringEnding,
            *Settings::resistFrost,
            getStatsMenu(*Settings::resistFrostMenu),
            _constStaticMultiplier,
            gameSettings->maxResistance);
        mp[StatsValue::resistMagic] = std::make_unique<StatConfig>(ActorValue::kResistMagic,
            *Settings::resistMagicString,
            *Settings::resistMagicStringEnding,
            *Settings::resistMagic,
            getStatsMenu(*Settings::resistMagicMenu),
            _constStaticMultiplier,
            gameSettings->maxResistance);
        mp[StatsValue::oneHanded] = std::make_unique<StatConfig>(ActorValue::kOneHanded,
            *Settings::oneHandedString,
            *Settings::oneHandedStringEnding,
            *Settings::oneHanded,
            getStatsMenu(*Settings::oneHandedMenu));
        mp[StatsValue::twoHanded] = std::make_unique<StatConfig>(ActorValue::kTwoHanded,
            *Settings::twoHandedString,
            *Settings::twoHandedStringEnding,
            *Settings::twoHanded,
            getStatsMenu(*Settings::twoHandedMenu));
        mp[StatsValue::archery] = std::make_unique<StatConfig>(ActorValue::kArchery,
            *Settings::archeryString,
            *Settings::archeryStringEnding,
            *Settings::archery,
            getStatsMenu(*Settings::archeryMenu));
        mp[StatsValue::block] = std::make_unique<StatConfig>(ActorValue::kBlock,
            *Settings::blockString,
            *Settings::blockStringEnding,
            *Settings::block,
            getStatsMenu(*Settings::blockMenu));
        mp[StatsValue::smithing] = std::make_unique<StatConfig>(ActorValue::kSmithing,
            *Settings::smithingString,
            *Settings::smithingStringEnding,
            *Settings::smithing,
            getStatsMenu(*Settings::smithingMenu));
        mp[StatsValue::heavyArmor] = std::make_unique<StatConfig>(ActorValue::kHeavyArmor,
            *Settings::heavyArmorString,
            *Settings::heavyArmorStringEnding,
            *Settings::heavyArmor,
            getStatsMenu(*Settings::heavyArmorMenu));
        mp[StatsValue::lightArmor] = std::make_unique<StatConfig>(ActorValue::kLightArmor,
            *Settings::lightArmorString,
            *Settings::lightArmorStringEnding,
            *Settings::lightArmor,
            getStatsMenu(*Settings::lightArmorMenu));
        mp[StatsValue::pickpocket] = std::make_unique<StatConfig>(ActorValue::kPickpocket,
            *Settings::pickpocketString,
            *Settings::pickpocketStringEnding,
            *Settings::pickpocket,
            getStatsMenu(*Settings::pickpocketMenu));
        mp[StatsValue::lockpicking] = std::make_unique<StatConfig>(ActorValue::kLockpicking,
            *Settings::lockpickingString,
            *Settings::lockpickingStringEnding,
            *Settings::lockpicking,
            getStatsMenu(*Settings::lockpickingMenu));
        mp[StatsValue::sneak] = std::make_unique<StatConfig>(ActorValue::kSneak,
            *Settings::sneakString,
            *Settings::sneakStringEnding,
            *Settings::sneak,
            getStatsMenu(*Settings::sneakMenu));
        mp[StatsValue::alchemy] = std::make_unique<StatConfig>(ActorValue::kAlchemy,
            *Settings::alchemyString,
            *Settings::alchemyStringEnding,
            *Settings::alchemy,
            getStatsMenu(*Settings::alchemyMenu));
        mp[StatsValue::speech] = std::make_unique<StatConfig>(ActorValue::kSpeech,
            *Settings::speechString,
            *Settings::speechStringEnding,
            *Settings::speech,
            getStatsMenu(*Settings::speechMenu));
        mp[StatsValue::enchanting] = std::make_unique<StatConfig>(ActorValue::kEnchanting,
            *Settings::enchantingString,
            *Settings::enchantingStringEnding,
            *Settings::enchanting,
            getStatsMenu(*Settings::enchantingMenu));
        mp[StatsValue::alteration] = std::make_unique<StatConfig>(ActorValue::kAlteration,
            *Settings::alterationString,
            *Settings::alterationStringEnding,
            *Settings::alteration,
            getStatsMenu(*Settings::alterationMenu));
        mp[StatsValue::conjuration] = std::make_unique<StatConfig>(ActorValue::kConjuration,
            *Settings::conjurationString,
            *Settings::conjurationStringEnding,
            *Settings::conjuration,
            getStatsMenu(*Settings::conjurationMenu));
        mp[StatsValue::destruction] = std::make_unique<StatConfig>(ActorValue::kDestruction,
            *Settings::destructionString,
            *Settings::destructionStringEnding,
            *Settings::destruction,
            getStatsMenu(*Settings::destructionMenu));
        mp[StatsValue::illusion] = std::make_unique<StatConfig>(ActorValue::kIllusion,
            *Settings::illusionString,
            *Settings::illusionStringEnding,
            *Settings::illusion,
            getStatsMenu(*Settings::illusionMenu));
        mp[StatsValue::restoration] = std::make_unique<StatConfig>(ActorValue::kRestoration,
            *Settings::restorationString,
            *Settings::restorationStringEnding,
            *Settings::restoration,
            getStatsMenu(*Settings::restorationMenu));
        mp[StatsValue::oneHandedPowerMod] = std::make_unique<StatConfig>(ActorValue::kOneHandedPowerModifier,
            *Settings::oneHandedPowerModString,
            *Settings::oneHandedPowerModStringEnding,
            *Settings::oneHandedPowerMod,
            getStatsMenu(*Settings::oneHandedPowerModMenu));
        mp[StatsValue::twoHandedPowerMod] = std::make_unique<StatConfig>(ActorValue::kTwoHandedPowerModifier,
            *Settings::twoHandedPowerModString,
            *Settings::twoHandedPowerModStringEnding,
            *Settings::twoHandedPowerMod,
            getStatsMenu(*Settings::twoHandedPowerModMenu));
        mp[StatsValue::archeryPowerMod] = std::make_unique<StatConfig>(ActorValue::kMarksmanPowerModifier,
            *Settings::archeryPowerModString,
            *Settings::archeryPowerModStringEnding,
            *Settings::archeryPowerMod,
            getStatsMenu(*Settings::archeryPowerModMenu));
        mp[StatsValue::blockPowerMod] = std::make_unique<StatConfig>(ActorValue::kBlockPowerModifier,
            *Settings::blockPowerModString,
            *Settings::blockPowerModStringEnding,
            *Settings::blockPowerMod,
            getStatsMenu(*Settings::blockPowerModMenu));
        mp[StatsValue::smithingPowerMod] = std::make_unique<StatConfig>(ActorValue::kSmithingPowerModifier,
            *Settings::smithingPowerModString,
            *Settings::smithingPowerModStringEnding,
            *Settings::smithingPowerMod,
            getStatsMenu(*Settings::smithingPowerModMenu));
        mp[StatsValue::heavyArmorPowerMod] = std::make_unique<StatConfig>(ActorValue::kHeavyArmorPowerModifier,
            *Settings::heavyArmorPowerModString,
            *Settings::heavyArmorPowerModStringEnding,
            *Settings::heavyArmorPowerMod,
            getStatsMenu(*Settings::heavyArmorPowerModMenu));
        mp[StatsValue::lightArmorPowerMod] = std::make_unique<StatConfig>(ActorValue::kLightArmorPowerModifier,
            *Settings::lightArmorPowerModString,
            *Settings::lightArmorPowerModStringEnding,
            *Settings::lightArmorPowerMod,
            getStatsMenu(*Settings::lightArmorPowerModMenu));
        mp[StatsValue::pickpocketPowerMod] = std::make_unique<StatConfig>(ActorValue::kPickpocketPowerModifier,
            *Settings::pickpocketPowerModString,
            *Settings::pickpocketPowerModStringEnding,
            *Settings::pickpocketPowerMod,
            getStatsMenu(*Settings::pickpocketPowerModMenu));
        mp[StatsValue::lockpickingPowerMod] = std::make_unique<StatConfig>(ActorValue::kLockpickingPowerModifier,
            *Settings::lockpickingPowerModString,
            *Settings::lockpickingPowerModStringEnding,
            *Settings::lockpickingPowerMod,
            getStatsMenu(*Settings::lockpickingPowerModMenu));
        mp[StatsValue::sneakPowerMod] = std::make_unique<StatConfig>(ActorValue::kSneakingPowerModifier,
            *Settings::sneakPowerModString,
            *Settings::sneakPowerModStringEnding,
            *Settings::sneakPowerMod,
            getStatsMenu(*Settings::sneakPowerModMenu));
        mp[StatsValue::alchemyPowerMod] = std::make_unique<StatConfig>(ActorValue::kAlchemyPowerModifier,
            *Settings::alchemyPowerModString,
            *Settings::alchemyPowerModStringEnding,
            *Settings::alchemyPowerMod,
            getStatsMenu(*Settings::alchemyPowerModMenu));
        mp[StatsValue::speechPowerMod] = std::make_unique<StatConfig>(ActorValue::kSpeechcraftPowerModifier,
            *Settings::speechPowerModString,
            *Settings::speechPowerModStringEnding,
            *Settings::speechPowerMod,
            getStatsMenu(*Settings::speechPowerModMenu));
        mp[StatsValue::enchantingPowerMod] = std::make_unique<StatConfig>(ActorValue::kEnchantingPowerModifier,
            *Settings::enchantingPowerModString,
            *Settings::enchantingPowerModStringEnding,
            *Settings::enchantingPowerMod,
            getStatsMenu(*Settings::enchantingPowerModMenu));
        mp[StatsValue::alterationPowerMod] = std::make_unique<StatConfig>(ActorValue::kAlterationPowerModifier,
            *Settings::alterationPowerModString,
            *Settings::alterationPowerModStringEnding,
            *Settings::alterationPowerMod,
            getStatsMenu(*Settings::alterationPowerModMenu));
        mp[StatsValue::conjurationPowerMod] = std::make_unique<StatConfig>(ActorValue::kConjurationPowerModifier,
            *Settings::conjurationPowerModString,
            *Settings::conjurationPowerModStringEnding,
            *Settings::conjurationPowerMod,
            getStatsMenu(*Settings::conjurationPowerModMenu));
        mp[StatsValue::destructionPowerMod] = std::make_unique<StatConfig>(ActorValue::kDestructionPowerModifier,
            *Settings::destructionPowerModString,
            *Settings::destructionPowerModStringEnding,
            *Settings::destructionPowerMod,
            getStatsMenu(*Settings::destructionPowerModMenu));
        mp[StatsValue::illusionPowerMod] = std::make_unique<StatConfig>(ActorValue::kIllusionPowerModifier,
            *Settings::illusionPowerModString,
            *Settings::illusionPowerModStringEnding,
            *Settings::illusionPowerMod,
            getStatsMenu(*Settings::illusionPowerModMenu));
        mp[StatsValue::restorationPowerMod] = std::make_unique<StatConfig>(ActorValue::kRestorationPowerModifier,
            *Settings::restorationPowerModString,
            *Settings::restorationPowerModStringEnding,
            *Settings::restorationPowerMod,
            getStatsMenu(*Settings::restorationPowerModMenu));
        mp[StatsValue::speedMult] = std::make_unique<StatConfig>(ActorValue::kSpeedMult,
            *Settings::speedMultString,
            *Settings::speedMultStringEnding,
            *Settings::speedMult,
            getStatsMenu(*Settings::speedMultMenu));
        mp[StatsValue::inventoryWeight] = std::make_unique<StatConfig>(ActorValue::kInventoryWeight,
            *Settings::inventoryWeightString,
            *Settings::inventoryWeightStringEnding,
            *Settings::inventoryWeight,
            getStatsMenu(*Settings::inventoryWeightMenu));
        mp[StatsValue::carryWeight] = std::make_unique<StatConfig>(ActorValue::kCarryWeight,
            *Settings::carryWeightString,
            *Settings::carryWeightStringEnding,
            *Settings::carryWeight,
            getStatsMenu(*Settings::carryWeightMenu));
        mp[StatsValue::criticalChance] = std::make_unique<StatConfig>(ActorValue::kCriticalChance,
            *Settings::criticalChanceString,
            *Settings::criticalChanceStringEnding,
            *Settings::criticalChance,
            getStatsMenu(*Settings::criticalChanceMenu));
        mp[StatsValue::meleeDamage] = std::make_unique<StatConfig>(ActorValue::kMeleeDamage,
            *Settings::meleeDamageString,
            *Settings::meleeDamageStringEnding,
            *Settings::meleeDamage,
            getStatsMenu(*Settings::meleeDamageMenu));
        mp[StatsValue::unarmedDamage] = std::make_unique<StatConfig>(ActorValue::kUnarmedDamage,
            *Settings::unarmedDamageString,
            *Settings::unarmedDamageStringEnding,
            *Settings::unarmedDamage,
            getStatsMenu(*Settings::unarmedDamageMenu));
        mp[StatsValue::absorbChance] = std::make_unique<StatConfig>(ActorValue::kAbsorbChance,
            *Settings::absorbChanceString,
            *Settings::absorbChanceStringEnding,
            *Settings::absorbChance,
            getStatsMenu(*Settings::absorbChanceMenu));
        //we will not set the actor value kWeaponSpeedMult and kLeftWeaponSpeedMultiply here, because some genius thought it is nice that the value 0 and 1 means 100%
        // https://en.uesp.net/wiki/Skyrim_Mod:Actor_Value_Indices as documented here
        mp[StatsValue::weaponSpeedMult] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::weaponSpeedMultString,
            *Settings::weaponSpeedMultStringEnding,
            *Settings::weaponSpeedMult,
            getStatsMenu(*Settings::weaponSpeedMultMenu),
            getMultiplier(*Settings::weaponSpeedMultMult));
        mp[StatsValue::leftWeaponSpeedMult] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::leftWeaponSpeedMultString,
            *Settings::leftWeaponSpeedMultStringEnding,
            *Settings::leftWeaponSpeedMult,
            getStatsMenu(*Settings::leftWeaponSpeedMultMenu),
            getMultiplier(*Settings::leftWeaponSpeedMultMult));
        mp[StatsValue::rightItemCharge] = std::make_unique<StatConfig>(ActorValue::kRightItemCharge,
            *Settings::rightItemChargeString,
            *Settings::rightItemChargeStringEnding,
            *Settings::rightItemCharge,
            getStatsMenu(*Settings::rightItemChargeMenu));
        mp[StatsValue::leftItemCharge] = std::make_unique<StatConfig>(ActorValue::kLeftItemCharge,
            *Settings::leftItemChargStringe,
            *Settings::leftItemChargStringeEnding,
            *Settings::leftItemCharge,
            getStatsMenu(*Settings::leftItemChargeMenu));
        mp[StatsValue::armorPerks] = std::make_unique<StatConfig>(ActorValue::kArmorPerks,
            *Settings::armorPerksString,
            *Settings::armorPerksStringEnding,
            *Settings::armorPerks,
            getStatsMenu(*Settings::armorPerksMenu),
            getMultiplier(*Settings::armorPerksMult));
        mp[StatsValue::mass] = std::make_unique<StatConfig>(ActorValue::kMass,
            *Settings::massString,
            *Settings::massStringEnding,
            *Settings::mass,
            getStatsMenu(*Settings::massMenu));
        mp[StatsValue::bowStaggerBonus] = std::make_unique<StatConfig>(ActorValue::kBowStaggerBonus,
            *Settings::bowStaggerBonusString,
            *Settings::bowStaggerBonusStringEnding,
            *Settings::bowStaggerBonus,
            getStatsMenu(*Settings::bowStaggerBonusMenu));
        mp[StatsValue::bypassVendorKeywordCheck] = std::make_unique<StatConfig>(ActorValue::kBypassVendorKeywordCheck,
            *Settings::bypassVendorKeywordCheckString,
            *Settings::bypassVendorKeywordCheckStringEnding,
            *Settings::bypassVendorKeywordCheck,
            getStatsMenu(*Settings::bypassVendorKeywordCheckMenu));
        mp[StatsValue::bypassVendorStolenCheck] = std::make_unique<StatConfig>(ActorValue::kBypassVendorStolenCheck,
            *Settings::bypassVendorStolenCheckString,
            *Settings::bypassVendorStolenCheckStringEnding,
            *Settings::bypassVendorStolenCheck,
            getStatsMenu(*Settings::bypassVendorStolenCheckMenu));
        mp[StatsValue::bowSpeedBonus] = std::make_unique<StatConfig>(ActorValue::kBowSpeedBonus,
            *Settings::bowSpeedBonusString,
            *Settings::bowSpeedBonusStringEnding,
            *Settings::bowSpeedBonus,
            getStatsMenu(*Settings::bowSpeedBonusMenu));
        mp[StatsValue::shoutRecoveryMult] = std::make_unique<StatConfig>(ActorValue::kShoutRecoveryMult,
            *Settings::shoutRecoveryMultString,
            *Settings::shoutRecoveryMultStringEnding,
            *Settings::shoutRecoveryMult,
            getStatsMenu(*Settings::shoutRecoveryMultMenu),
            getMultiplier(*Settings::shoutRecoveryMultMult));
        mp[StatsValue::movementNoiseMult] = std::make_unique<StatConfig>(ActorValue::kMovementNoiseMult,
            *Settings::movementNoiseMultString,
            *Settings::movementNoiseMultStringEnding,
            *Settings::movementNoiseMult,
            getStatsMenu(*Settings::movementNoiseMultMenu),
            getMultiplier(*Settings::movementNoiseMultMult));
        mp[StatsValue::dragonSouls] = std::make_unique<StatConfig>(ActorValue::kDragonSouls,
            *Settings::dragonSoulsString,
            *Settings::dragonSoulsStringEnding,
            *Settings::dragonSouls,
            getStatsMenu(*Settings::dragonSoulsMenu));
        mp[StatsValue::combatHealthRegenMultiply] = std::make_unique<StatConfig>(ActorValue::kCombatHealthRegenMultiply,
            *Settings::combatHealthRegenMultiplyString,
            *Settings::combatHealthRegenMultiplyStringEnding,
            *Settings::combatHealthRegenMultiply,
            getStatsMenu(*Settings::combatHealthRegenMultiplyMenu),
            getMultiplier(*Settings::combatHealthRegenMultiplyMult));
        mp[StatsValue::attackDamageMult] = std::make_unique<StatConfig>(ActorValue::kAttackDamageMult,
            *Settings::attackDamageMultString,
            *Settings::attackDamageMultStringEnding,
            *Settings::attackDamageMult,
            getStatsMenu(*Settings::attackDamageMultMenu));
        mp[StatsValue::beast] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::beastString,
            *Settings::beastStringEnding,
            *Settings::beast,
            StatsMenuValue::mNone);
        mp[StatsValue::xp] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::xpString,
            *Settings::xpStringEnding,
            *Settings::xp,
            StatsMenuValue::mNone);
        mp[StatsValue::reflectDamage] = std::make_unique<StatConfig>(ActorValue::kReflectDamage,
            *Settings::reflectDamageString,
            *Settings::reflectDamageStringEnding,
            *Settings::reflectDamage,
            getStatsMenu(*Settings::reflectDamageMenu));
        mp[StatsValue::oneHandedMod] = std::make_unique<StatConfig>(ActorValue::kOneHandedModifier,
            *Settings::oneHandedModString,
            *Settings::oneHandedModStringEnding,
            *Settings::oneHandedMod,
            getStatsMenu(*Settings::oneHandedModMenu));
        mp[StatsValue::twoHandedMod] = std::make_unique<StatConfig>(ActorValue::kTwoHandedModifier,
            *Settings::twoHandedModString,
            *Settings::twoHandedModStringEnding,
            *Settings::twoHandedMod,
            getStatsMenu(*Settings::twoHandedModMenu));
        mp[StatsValue::marksmanMod] = std::make_unique<StatConfig>(ActorValue::kMarksmanModifier,
            *Settings::archeryModString,
            *Settings::archeryModStringEnding,
            *Settings::archeryMod,
            getStatsMenu(*Settings::archeryModMenu));
        mp[StatsValue::blockMod] = std::make_unique<StatConfig>(ActorValue::kBlockModifier,
            *Settings::blockModString,
            *Settings::blockModStringEnding,
            *Settings::blockMod,
            getStatsMenu(*Settings::blockModMenu));
        mp[StatsValue::smithingMod] = std::make_unique<StatConfig>(ActorValue::kSmithingModifier,
            *Settings::smithingModString,
            *Settings::smithingModStringEnding,
            *Settings::smithingMod,
            getStatsMenu(*Settings::smithingModMenu));
        mp[StatsValue::heavyArmorMod] = std::make_unique<StatConfig>(ActorValue::kHeavyArmorModifier,
            *Settings::heavyArmorModString,
            *Settings::heavyArmorModStringEnding,
            *Settings::heavyArmorMod,
            getStatsMenu(*Settings::heavyArmorModMenu));
        mp[StatsValue::lightArmorMod] = std::make_unique<StatConfig>(ActorValue::kLightArmorModifier,
            *Settings::lightArmorModString,
            *Settings::lightArmorModStringEnding,
            *Settings::lightArmorMod,
            getStatsMenu(*Settings::lightArmorModMenu));
        mp[StatsValue::pickpocketMod] = std::make_unique<StatConfig>(ActorValue::kPickpocketModifier,
            *Settings::pickpocketModString,
            *Settings::pickpocketModStringEnding,
            *Settings::pickpocketMod,
            getStatsMenu(*Settings::pickpocketModMenu));
        mp[StatsValue::lockpickingMod] = std::make_unique<StatConfig>(ActorValue::kLockpickingModifier,
            *Settings::lockpickingModString,
            *Settings::lockpickingModStringEnding,
            *Settings::lockpickingMod,
            getStatsMenu(*Settings::lockpickingModMenu));
        mp[StatsValue::sneakingMod] = std::make_unique<StatConfig>(ActorValue::kSneakingModifier,
            *Settings::sneakModString,
            *Settings::sneakModStringEnding,
            *Settings::sneakMod,
            getStatsMenu(*Settings::sneakModMenu));
        mp[StatsValue::alchemyMod] = std::make_unique<StatConfig>(ActorValue::kAlchemyModifier,
            *Settings::alchemyModString,
            *Settings::alchemyModStringEnding,
            *Settings::alchemyMod,
            getStatsMenu(*Settings::alchemyModMenu));
        mp[StatsValue::speechcraftMod] = std::make_unique<StatConfig>(ActorValue::kSpeechcraftModifier,
            *Settings::speechModString,
            *Settings::speechModStringEnding,
            *Settings::speechMod,
            getStatsMenu(*Settings::speechModMenu));
        mp[StatsValue::enchantingMod] = std::make_unique<StatConfig>(ActorValue::kEnchantingModifier,
            *Settings::enchantingModString,
            *Settings::enchantingModStringEnding,
            *Settings::enchantingMod,
            getStatsMenu(*Settings::enchantingModMenu));
        mp[StatsValue::alterationMod] = std::make_unique<StatConfig>(ActorValue::kAlterationModifier,
            *Settings::alterationModString,
            *Settings::alterationModStringEnding,
            *Settings::alterationMod,
            getStatsMenu(*Settings::alterationModMenu));
        mp[StatsValue::conjurationMod] = std::make_unique<StatConfig>(ActorValue::kConjurationModifier,
            *Settings::conjurationModString,
            *Settings::conjurationModStringEnding,
            *Settings::conjurationMod,
            getStatsMenu(*Settings::conjurationModMenu));
        mp[StatsValue::destructionMod] = std::make_unique<StatConfig>(ActorValue::kDestructionModifier,
            *Settings::destructionModString,
            *Settings::destructionModStringEnding,
            *Settings::destructionMod,
            getStatsMenu(*Settings::destructionModMenu));
        mp[StatsValue::illusionMod] = std::make_unique<StatConfig>(ActorValue::kIllusionModifier,
            *Settings::illusionModString,
            *Settings::illusionModStringEnding,
            *Settings::illusionMod,
            getStatsMenu(*Settings::illusionModMenu));
        mp[StatsValue::restorationMod] = std::make_unique<StatConfig>(ActorValue::kRestorationModifier,
            *Settings::restorationModString,
            *Settings::restorationModStringEnding,
            *Settings::restorationMod,
            getStatsMenu(*Settings::restorationModMenu));
        mp[StatsValue::damageArrow] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::damageArrowString,
            *Settings::damageArrowStringEnding,
            *Settings::damageArrow,
            getStatsMenu(*Settings::damageArrowMenu));
        mp[StatsValue::damageLeft] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::damageLeftString,
            *Settings::damageLeftStringEnding,
            *Settings::damageLeft,
            getStatsMenu(*Settings::damageLeftMenu));

        return mp;
    }

    StatSetting() = default;
    StatSetting(const StatSetting&) = default;
    StatSetting(StatSetting&&) = delete;

    ~StatSetting() = default;

    StatSetting& operator=(const StatSetting&) = default;
    StatSetting& operator=(StatSetting&&) = delete;
};
