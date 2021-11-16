#pragma once
#include "settings/gamesettings.h"

class StatConfig {
    using StatsInventoryMenuValue = MenuUtil::StatsInventoryMenuValue;
    using StatsMenuValue = MenuUtil::StatsMenuValue;

public:
    StatConfig(RE::ActorValue a_actor,
        std::string a_display_name,
        std::string a_ending,
        bool a_show,
        StatsMenuValue a_stats_menu,
        StatsInventoryMenuValue a_stats_inventory_menu)
        : _actor(a_actor)
        , _displayName(a_display_name)
        , _ending(a_ending)
        , _show(a_show)
        , _statsMenu(a_stats_menu)
        , _statsInventoryMenu(a_stats_inventory_menu) {}

    StatConfig(RE::ActorValue a_actor,
        std::string a_display_name,
        std::string a_ending,
        bool a_show,
        StatsMenuValue a_stats_menu,
        StatsInventoryMenuValue a_stats_inventory_menu,
        int64_t a_value_multiplier)
        : _actor(a_actor)
        , _displayName(a_display_name)
        , _ending(a_ending)
        , _show(a_show)
        , _statsMenu(a_stats_menu)
        , _statsInventoryMenu(a_stats_inventory_menu)
        , _valueMultiplier(a_value_multiplier) {}

    StatConfig(RE::ActorValue a_actor,
        std::string a_display_name,
        std::string a_ending,
        bool a_show,
        StatsMenuValue a_stats_menu,
        StatsInventoryMenuValue a_stats_inventory_menu,
        int64_t a_value_multiplier,
        float a_cap)
        : _actor(a_actor)
        , _displayName(a_display_name)
        , _ending(a_ending)
        , _show(a_show)
        , _statsMenu(a_stats_menu)
        , _statsInventoryMenu(a_stats_inventory_menu)
        , _valueMultiplier(a_value_multiplier)
        , _cap(a_cap) {}

    RE::ActorValue getActor() { return _actor; }

    std::string getDisplayName() { return _displayName; }

    std::string getEnding() { return _ending; }

    bool getShow() { return _show; }

    StatsMenuValue getStatsMenu() { return _statsMenu; }

    StatsInventoryMenuValue getStatsInventoryMenu() { return _statsInventoryMenu; }

    int64_t getValueMultiplier() { return _valueMultiplier; }

    float getCap() { return _cap; }

    std::string getDisplay(std::string a_value) {
        if (!a_value.empty()) {
            logger::trace("display {} got value {}, building text ..."sv, _displayName, a_value);
            return MenuUtil::buildDisplayString(a_value, _displayName, _ending, _show, false);
        }
        return "";
    }

    void logStatConfig(StatsValue a_stats_value) {
        logger::trace(
            "name {}, actor {}, displayName ({}), ending {}, show {}, statsMenu {}, statsInventoryMenu {}, valueMultiplier {}, cap {}"sv,
            a_stats_value,
            _actor,
            _displayName,
            _ending,
            _show,
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
    std::string _ending;
    bool _show;
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
            *Settings::nameStringEnding,
            *Settings::name,
            StatsMenuValue::mNone,
            StatsInventoryMenuValue::mNone);
        mp[StatsValue::race] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::raceString,
            *Settings::raceStringEnding,
            *Settings::race,
            StatsMenuValue::mNone,
            StatsInventoryMenuValue::mNone);
        mp[StatsValue::level] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::levelString,
            *Settings::levelStringEnding,
            *Settings::level,
            StatsMenuValue::mNone,
            StatsInventoryMenuValue::mNone);
        mp[StatsValue::perkCount] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::perkCountString,
            *Settings::perkCountStringEnding,
            *Settings::perkCount,
            StatsMenuValue::mNone,
            StatsInventoryMenuValue::mNone);
        mp[StatsValue::height] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::heightString,
            *Settings::heightStringEnding,
            *Settings::height,
            MenuUtil::getStatsMenu(*Settings::heightMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::equipedWeight] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::equipedWeightString,
            *Settings::equipedWeightStringEnding,
            *Settings::equipedWeight,
            MenuUtil::getStatsMenu(*Settings::equipedWeightMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::weight] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::weightString,
            *Settings::weightStringEnding,
            *Settings::weight,
            MenuUtil::getStatsMenu(*Settings::weightMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::armor] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::armorString,
            *Settings::armorStringEnding,
            *Settings::armor,
            MenuUtil::getStatsMenu(*Settings::armorMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::damage] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::damageString,
            *Settings::damageStringEnding,
            *Settings::damage,
            MenuUtil::getStatsMenu(*Settings::damageMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::skillTrainingsThisLevel] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::skillTrainingsThisLevelString,
            *Settings::skillTrainingsThisLevelStringEnding,
            *Settings::skillTrainingsThisLevel,
            MenuUtil::getStatsMenu(*Settings::skillTrainingsThisLevelMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::health] = std::make_unique<StatConfig>(ActorValue::kHealth,
            *Settings::healthString,
            *Settings::healthStringEnding,
            *Settings::health,
            MenuUtil::getStatsMenu(*Settings::healthMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::healthRatePer] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::healthRateString,
            *Settings::healthRateStringEnding,
            *Settings::healthRate,
            MenuUtil::getStatsMenu(*Settings::healthRateMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::magicka] = std::make_unique<StatConfig>(ActorValue::kMagicka,
            *Settings::magickaString,
            *Settings::magickaStringEnding,
            *Settings::magicka,
            MenuUtil::getStatsMenu(*Settings::magickaMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::magickaRatePer] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::magickaRateString,
            *Settings::magickaRateStringEnding,
            *Settings::magickaRate,
            MenuUtil::getStatsMenu(*Settings::magickaRateMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::stamina] = std::make_unique<StatConfig>(ActorValue::kStamina,
            *Settings::staminaString,
            *Settings::staminaStringEnding,
            *Settings::stamina,
            MenuUtil::getStatsMenu(*Settings::staminaMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::staminaRatePer] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::staminaRateString,
            *Settings::staminaRateStringEnding,
            *Settings::staminaRate,
            MenuUtil::getStatsMenu(*Settings::staminaRateMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::resistDamage] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::resistDamageString,
            *Settings::resistDamageStringEnding,
            *Settings::resistDamage,
            MenuUtil::getStatsMenu(*Settings::resistDamageMenu),
            MenuUtil::getStatsInventoryMenu(0),
            _constStaticMultiplier,
            gameSettings->maxArmorResistance);
        mp[StatsValue::resistDisease] = std::make_unique<StatConfig>(ActorValue::kResistDisease,
            *Settings::resistDiseaseString,
            *Settings::resistDiseaseStringEnding,
            *Settings::resistDisease,
            MenuUtil::getStatsMenu(*Settings::resistDiseaseMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::resistPoison] = std::make_unique<StatConfig>(ActorValue::kPoisonResist,
            *Settings::resistPoisonString,
            *Settings::resistPoisonStringEnding,
            *Settings::resistPoison,
            MenuUtil::getStatsMenu(*Settings::resistPoisonMenu),
            MenuUtil::getStatsInventoryMenu(0),
            _constStaticMultiplier,
            gameSettings->maxResistance);
        mp[StatsValue::resistFire] = std::make_unique<StatConfig>(ActorValue::kResistFire,
            *Settings::resistFireString,
            *Settings::resistFireStringEnding,
            *Settings::resistFire,
            MenuUtil::getStatsMenu(*Settings::resistFireMenu),
            MenuUtil::getStatsInventoryMenu(0),
            _constStaticMultiplier,
            gameSettings->maxResistance);
        mp[StatsValue::resistShock] = std::make_unique<StatConfig>(ActorValue::kResistShock,
            *Settings::resistShockString,
            *Settings::resistShockStringEnding,
            *Settings::resistShock,
            MenuUtil::getStatsMenu(*Settings::resistShockMenu),
            MenuUtil::getStatsInventoryMenu(0),
            _constStaticMultiplier,
            gameSettings->maxResistance);
        mp[StatsValue::resistFrost] = std::make_unique<StatConfig>(ActorValue::kResistFrost,
            *Settings::resistFrostString,
            *Settings::resistFrostStringEnding,
            *Settings::resistFrost,
            MenuUtil::getStatsMenu(*Settings::resistFrostMenu),
            MenuUtil::getStatsInventoryMenu(0),
            _constStaticMultiplier,
            gameSettings->maxResistance);
        mp[StatsValue::resistMagic] = std::make_unique<StatConfig>(ActorValue::kResistMagic,
            *Settings::resistMagicString,
            *Settings::resistMagicStringEnding,
            *Settings::resistMagic,
            MenuUtil::getStatsMenu(*Settings::resistMagicMenu),
            MenuUtil::getStatsInventoryMenu(0),
            _constStaticMultiplier,
            gameSettings->maxResistance);
        mp[StatsValue::oneHanded] = std::make_unique<StatConfig>(ActorValue::kOneHanded,
            *Settings::oneHandedString,
            *Settings::oneHandedStringEnding,
            *Settings::oneHanded,
            MenuUtil::getStatsMenu(*Settings::oneHandedMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::twoHanded] = std::make_unique<StatConfig>(ActorValue::kTwoHanded,
            *Settings::twoHandedString,
            *Settings::twoHandedStringEnding,
            *Settings::twoHanded,
            MenuUtil::getStatsMenu(*Settings::twoHandedMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::archery] = std::make_unique<StatConfig>(ActorValue::kArchery,
            *Settings::archeryString,
            *Settings::archeryStringEnding,
            *Settings::archery,
            MenuUtil::getStatsMenu(*Settings::archeryMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::block] = std::make_unique<StatConfig>(ActorValue::kBlock,
            *Settings::blockString,
            *Settings::blockStringEnding,
            *Settings::block,
            MenuUtil::getStatsMenu(*Settings::blockMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::smithing] = std::make_unique<StatConfig>(ActorValue::kSmithing,
            *Settings::smithingString,
            *Settings::smithingStringEnding,
            *Settings::smithing,
            MenuUtil::getStatsMenu(*Settings::smithingMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::heavyArmor] = std::make_unique<StatConfig>(ActorValue::kHeavyArmor,
            *Settings::heavyArmorString,
            *Settings::heavyArmorStringEnding,
            *Settings::heavyArmor,
            MenuUtil::getStatsMenu(*Settings::heavyArmorMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::lightArmor] = std::make_unique<StatConfig>(ActorValue::kLightArmor,
            *Settings::lightArmorString,
            *Settings::lightArmorStringEnding,
            *Settings::lightArmor,
            MenuUtil::getStatsMenu(*Settings::lightArmorMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::pickpocket] = std::make_unique<StatConfig>(ActorValue::kPickpocket,
            *Settings::pickpocketString,
            *Settings::pickpocketStringEnding,
            *Settings::pickpocket,
            MenuUtil::getStatsMenu(*Settings::pickpocketMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::lockpicking] = std::make_unique<StatConfig>(ActorValue::kLockpicking,
            *Settings::lockpickingString,
            *Settings::lockpickingStringEnding,
            *Settings::lockpicking,
            MenuUtil::getStatsMenu(*Settings::lockpickingMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::sneak] = std::make_unique<StatConfig>(ActorValue::kSneak,
            *Settings::sneakString,
            *Settings::sneakStringEnding,
            *Settings::sneak,
            MenuUtil::getStatsMenu(*Settings::sneakMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::alchemy] = std::make_unique<StatConfig>(ActorValue::kAlchemy,
            *Settings::alchemyString,
            *Settings::alchemyStringEnding,
            *Settings::alchemy,
            MenuUtil::getStatsMenu(*Settings::alchemyMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::speech] = std::make_unique<StatConfig>(ActorValue::kSpeech,
            *Settings::speechString,
            *Settings::speechStringEnding,
            *Settings::speech,
            MenuUtil::getStatsMenu(*Settings::speechMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::enchanting] = std::make_unique<StatConfig>(ActorValue::kEnchanting,
            *Settings::enchantingString,
            *Settings::enchantingStringEnding,
            *Settings::enchanting,
            MenuUtil::getStatsMenu(*Settings::enchantingMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::alteration] = std::make_unique<StatConfig>(ActorValue::kAlteration,
            *Settings::alterationString,
            *Settings::alterationStringEnding,
            *Settings::alteration,
            MenuUtil::getStatsMenu(*Settings::alterationMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::conjuration] = std::make_unique<StatConfig>(ActorValue::kConjuration,
            *Settings::conjurationString,
            *Settings::conjurationStringEnding,
            *Settings::conjuration,
            MenuUtil::getStatsMenu(*Settings::conjurationMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::destruction] = std::make_unique<StatConfig>(ActorValue::kDestruction,
            *Settings::destructionString,
            *Settings::destructionStringEnding,
            *Settings::destruction,
            MenuUtil::getStatsMenu(*Settings::destructionMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::illusion] = std::make_unique<StatConfig>(ActorValue::kIllusion,
            *Settings::illusionString,
            *Settings::illusionStringEnding,
            *Settings::illusion,
            MenuUtil::getStatsMenu(*Settings::illusionMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::restoration] = std::make_unique<StatConfig>(ActorValue::kRestoration,
            *Settings::restorationString,
            *Settings::restorationStringEnding,
            *Settings::restoration,
            MenuUtil::getStatsMenu(*Settings::restorationMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::oneHandedPowerMod] = std::make_unique<StatConfig>(ActorValue::kOneHandedPowerModifier,
            *Settings::oneHandedPowerModString,
            *Settings::oneHandedPowerModStringEnding,
            *Settings::oneHandedPowerMod,
            MenuUtil::getStatsMenu(*Settings::oneHandedPowerModMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::twoHandedPowerMod] = std::make_unique<StatConfig>(ActorValue::kTwoHandedPowerModifier,
            *Settings::twoHandedPowerModString,
            *Settings::twoHandedPowerModStringEnding,
            *Settings::twoHandedPowerMod,
            MenuUtil::getStatsMenu(*Settings::twoHandedPowerModMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::archeryPowerMod] = std::make_unique<StatConfig>(ActorValue::kMarksmanPowerModifier,
            *Settings::archeryPowerModString,
            *Settings::archeryPowerModStringEnding,
            *Settings::archeryPowerMod,
            MenuUtil::getStatsMenu(*Settings::archeryPowerModMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::blockPowerMod] = std::make_unique<StatConfig>(ActorValue::kBlockPowerModifier,
            *Settings::blockPowerModString,
            *Settings::blockPowerModStringEnding,
            *Settings::blockPowerMod,
            MenuUtil::getStatsMenu(*Settings::blockPowerModMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::smithingPowerMod] = std::make_unique<StatConfig>(ActorValue::kSmithingPowerModifier,
            *Settings::smithingPowerModString,
            *Settings::smithingPowerModStringEnding,
            *Settings::smithingPowerMod,
            MenuUtil::getStatsMenu(*Settings::smithingPowerModMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::heavyArmorPowerMod] = std::make_unique<StatConfig>(ActorValue::kHeavyArmorPowerModifier,
            *Settings::heavyArmorPowerModString,
            *Settings::heavyArmorPowerModStringEnding,
            *Settings::heavyArmorPowerMod,
            MenuUtil::getStatsMenu(*Settings::heavyArmorPowerModMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::lightArmorPowerMod] = std::make_unique<StatConfig>(ActorValue::kLightArmorPowerModifier,
            *Settings::lightArmorPowerModString,
            *Settings::lightArmorPowerModStringEnding,
            *Settings::lightArmorPowerMod,
            MenuUtil::getStatsMenu(*Settings::lightArmorPowerModMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::pickpocketPowerMod] = std::make_unique<StatConfig>(ActorValue::kPickpocketPowerModifier,
            *Settings::pickpocketPowerModString,
            *Settings::pickpocketPowerModStringEnding,
            *Settings::pickpocketPowerMod,
            MenuUtil::getStatsMenu(*Settings::pickpocketPowerModMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::lockpickingPowerMod] = std::make_unique<StatConfig>(ActorValue::kLockpickingPowerModifier,
            *Settings::lockpickingPowerModString,
            *Settings::lockpickingPowerModStringEnding,
            *Settings::lockpickingPowerMod,
            MenuUtil::getStatsMenu(*Settings::lockpickingPowerModMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::sneakPowerMod] = std::make_unique<StatConfig>(ActorValue::kSneakingPowerModifier,
            *Settings::sneakPowerModString,
            *Settings::sneakPowerModStringEnding,
            *Settings::sneakPowerMod,
            MenuUtil::getStatsMenu(*Settings::sneakPowerModMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::alchemyPowerMod] = std::make_unique<StatConfig>(ActorValue::kAlchemyPowerModifier,
            *Settings::alchemyPowerModString,
            *Settings::alchemyPowerModStringEnding,
            *Settings::alchemyPowerMod,
            MenuUtil::getStatsMenu(*Settings::alchemyPowerModMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::speechPowerMod] = std::make_unique<StatConfig>(ActorValue::kSpeechcraftPowerModifier,
            *Settings::speechPowerModString,
            *Settings::speechPowerModStringEnding,
            *Settings::speechPowerMod,
            MenuUtil::getStatsMenu(*Settings::speechPowerModMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::enchantingPowerMod] = std::make_unique<StatConfig>(ActorValue::kEnchantingPowerModifier,
            *Settings::enchantingPowerModString,
            *Settings::enchantingPowerModStringEnding,
            *Settings::enchantingPowerMod,
            MenuUtil::getStatsMenu(*Settings::enchantingPowerModMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::alterationPowerMod] = std::make_unique<StatConfig>(ActorValue::kAlterationPowerModifier,
            *Settings::alterationPowerModString,
            *Settings::alterationPowerModStringEnding,
            *Settings::alterationPowerMod,
            MenuUtil::getStatsMenu(*Settings::alterationPowerModMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::conjurationPowerMod] = std::make_unique<StatConfig>(ActorValue::kConjurationPowerModifier,
            *Settings::conjurationPowerModString,
            *Settings::conjurationPowerModStringEnding,
            *Settings::conjurationPowerMod,
            MenuUtil::getStatsMenu(*Settings::conjurationPowerModMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::destructionPowerMod] = std::make_unique<StatConfig>(ActorValue::kDestructionPowerModifier,
            *Settings::destructionPowerModString,
            *Settings::destructionPowerModStringEnding,
            *Settings::destructionPowerMod,
            MenuUtil::getStatsMenu(*Settings::destructionPowerModMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::illusionPowerMod] = std::make_unique<StatConfig>(ActorValue::kIllusionPowerModifier,
            *Settings::illusionPowerModString,
            *Settings::illusionPowerModStringEnding,
            *Settings::illusionPowerMod,
            MenuUtil::getStatsMenu(*Settings::illusionPowerModMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::restorationPowerMod] = std::make_unique<StatConfig>(ActorValue::kRestorationPowerModifier,
            *Settings::restorationPowerModString,
            *Settings::restorationPowerModStringEnding,
            *Settings::restorationPowerMod,
            MenuUtil::getStatsMenu(*Settings::restorationPowerModMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::speedMult] = std::make_unique<StatConfig>(ActorValue::kSpeedMult,
            *Settings::speedMultString,
            *Settings::speedMultStringEnding,
            *Settings::speedMult,
            MenuUtil::getStatsMenu(*Settings::speedMultMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::inventoryWeight] = std::make_unique<StatConfig>(ActorValue::kInventoryWeight,
            *Settings::inventoryWeightString,
            *Settings::inventoryWeightStringEnding,
            *Settings::inventoryWeight,
            MenuUtil::getStatsMenu(*Settings::inventoryWeightMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::carryWeight] = std::make_unique<StatConfig>(ActorValue::kCarryWeight,
            *Settings::carryWeightString,
            *Settings::carryWeightStringEnding,
            *Settings::carryWeight,
            MenuUtil::getStatsMenu(*Settings::carryWeightMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::criticalChance] = std::make_unique<StatConfig>(ActorValue::kCriticalChance,
            *Settings::criticalChanceString,
            *Settings::criticalChanceStringEnding,
            *Settings::criticalChance,
            MenuUtil::getStatsMenu(*Settings::criticalChanceMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::meleeDamage] = std::make_unique<StatConfig>(ActorValue::kMeleeDamage,
            *Settings::meleeDamageString,
            *Settings::meleeDamageStringEnding,
            *Settings::meleeDamage,
            MenuUtil::getStatsMenu(*Settings::meleeDamageMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::unarmedDamage] = std::make_unique<StatConfig>(ActorValue::kUnarmedDamage,
            *Settings::unarmedDamageString,
            *Settings::unarmedDamageStringEnding,
            *Settings::unarmedDamage,
            MenuUtil::getStatsMenu(*Settings::unarmedDamageMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::absorbChance] = std::make_unique<StatConfig>(ActorValue::kAbsorbChance,
            *Settings::absorbChanceString,
            *Settings::absorbChanceStringEnding,
            *Settings::absorbChance,
            MenuUtil::getStatsMenu(*Settings::absorbChanceMenu),
            MenuUtil::getStatsInventoryMenu(0));
        //we will not set the actor value kWeaponSpeedMult and kLeftWeaponSpeedMultiply here, because some genius thought it is nice that the value 0 and 1 means 100%
        // https://en.uesp.net/wiki/Skyrim_Mod:Actor_Value_Indices as documented here
        mp[StatsValue::weaponSpeedMult] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::weaponSpeedMultString,
            *Settings::weaponSpeedMultStringEnding,
            *Settings::weaponSpeedMult,
            MenuUtil::getStatsMenu(*Settings::weaponSpeedMultMenu),
            MenuUtil::getStatsInventoryMenu(0),
            MenuUtil::getMultiplier(*Settings::weaponSpeedMultMult));
        mp[StatsValue::leftWeaponSpeedMult] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::leftWeaponSpeedMultString,
            *Settings::leftWeaponSpeedMultStringEnding,
            *Settings::leftWeaponSpeedMult,
            MenuUtil::getStatsMenu(*Settings::leftWeaponSpeedMultMenu),
            MenuUtil::getStatsInventoryMenu(0),
            MenuUtil::getMultiplier(*Settings::leftWeaponSpeedMultMult));
        mp[StatsValue::rightItemCharge] = std::make_unique<StatConfig>(ActorValue::kRightItemCharge,
            *Settings::rightItemChargeString,
            *Settings::rightItemChargeStringEnding,
            *Settings::rightItemCharge,
            MenuUtil::getStatsMenu(*Settings::rightItemChargeMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::leftItemCharge] = std::make_unique<StatConfig>(ActorValue::kLeftItemCharge,
            *Settings::leftItemChargStringe,
            *Settings::leftItemChargStringeEnding,
            *Settings::leftItemCharge,
            MenuUtil::getStatsMenu(*Settings::leftItemChargeMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::armorPerks] = std::make_unique<StatConfig>(ActorValue::kArmorPerks,
            *Settings::armorPerksString,
            *Settings::armorPerksStringEnding,
            *Settings::armorPerks,
            MenuUtil::getStatsMenu(*Settings::armorPerksMenu),
            MenuUtil::getStatsInventoryMenu(0),
            MenuUtil::getMultiplier(*Settings::armorPerksMult));
        mp[StatsValue::mass] = std::make_unique<StatConfig>(ActorValue::kMass,
            *Settings::massString,
            *Settings::massStringEnding,
            *Settings::mass,
            MenuUtil::getStatsMenu(*Settings::massMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::bowStaggerBonus] = std::make_unique<StatConfig>(ActorValue::kBowStaggerBonus,
            *Settings::bowStaggerBonusString,
            *Settings::bowStaggerBonusStringEnding,
            *Settings::bowStaggerBonus,
            MenuUtil::getStatsMenu(*Settings::bowStaggerBonusMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::bypassVendorKeywordCheck] = std::make_unique<StatConfig>(ActorValue::kBypassVendorKeywordCheck,
            *Settings::bypassVendorKeywordCheckString,
            *Settings::bypassVendorKeywordCheckStringEnding,
            *Settings::bypassVendorKeywordCheck,
            MenuUtil::getStatsMenu(*Settings::bypassVendorKeywordCheckMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::bypassVendorStolenCheck] = std::make_unique<StatConfig>(ActorValue::kBypassVendorStolenCheck,
            *Settings::bypassVendorStolenCheckString,
            *Settings::bypassVendorStolenCheckStringEnding,
            *Settings::bypassVendorStolenCheck,
            MenuUtil::getStatsMenu(*Settings::bypassVendorStolenCheckMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::bowSpeedBonus] = std::make_unique<StatConfig>(ActorValue::kBowSpeedBonus,
            *Settings::bowSpeedBonusString,
            *Settings::bowSpeedBonusStringEnding,
            *Settings::bowSpeedBonus,
            MenuUtil::getStatsMenu(*Settings::bowSpeedBonusMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::shoutRecoveryMult] = std::make_unique<StatConfig>(ActorValue::kShoutRecoveryMult,
            *Settings::shoutRecoveryMultString,
            *Settings::shoutRecoveryMultStringEnding,
            *Settings::shoutRecoveryMult,
            MenuUtil::getStatsMenu(*Settings::shoutRecoveryMultMenu),
            MenuUtil::getStatsInventoryMenu(0),
            MenuUtil::getMultiplier(*Settings::shoutRecoveryMultMult));
        mp[StatsValue::movementNoiseMult] = std::make_unique<StatConfig>(ActorValue::kMovementNoiseMult,
            *Settings::movementNoiseMultString,
            *Settings::movementNoiseMultStringEnding,
            *Settings::movementNoiseMult,
            MenuUtil::getStatsMenu(*Settings::movementNoiseMultMenu),
            MenuUtil::getStatsInventoryMenu(0),
            MenuUtil::getMultiplier(*Settings::movementNoiseMultMult));
        mp[StatsValue::dragonSouls] = std::make_unique<StatConfig>(ActorValue::kDragonSouls,
            *Settings::dragonSoulsString,
            *Settings::dragonSoulsStringEnding,
            *Settings::dragonSouls,
            MenuUtil::getStatsMenu(*Settings::dragonSoulsMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::combatHealthRegenMultiply] = std::make_unique<StatConfig>(ActorValue::kCombatHealthRegenMultiply,
            *Settings::combatHealthRegenMultiplyString,
            *Settings::combatHealthRegenMultiplyStringEnding,
            *Settings::combatHealthRegenMultiply,
            MenuUtil::getStatsMenu(*Settings::combatHealthRegenMultiplyMenu),
            MenuUtil::getStatsInventoryMenu(0),
            MenuUtil::getMultiplier(*Settings::combatHealthRegenMultiplyMult));
        mp[StatsValue::attackDamageMult] = std::make_unique<StatConfig>(ActorValue::kAttackDamageMult,
            *Settings::attackDamageMultString,
            *Settings::attackDamageMultStringEnding,
            *Settings::attackDamageMult,
            MenuUtil::getStatsMenu(*Settings::attackDamageMultMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::beast] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::beastString,
            *Settings::beastStringEnding,
            *Settings::beast,
            StatsMenuValue::mNone,
            StatsInventoryMenuValue::mNone);
        mp[StatsValue::xp] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::xpString,
            *Settings::xpStringEnding,
            *Settings::xp,
            StatsMenuValue::mNone,
            StatsInventoryMenuValue::mNone);
        mp[StatsValue::reflectDamage] = std::make_unique<StatConfig>(ActorValue::kReflectDamage,
            *Settings::reflectDamageString,
            *Settings::reflectDamageStringEnding,
            *Settings::reflectDamage,
            MenuUtil::getStatsMenu(*Settings::reflectDamageMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::oneHandedMod] = std::make_unique<StatConfig>(ActorValue::kOneHandedModifier,
            *Settings::oneHandedModString,
            *Settings::oneHandedModStringEnding,
            *Settings::oneHandedMod,
            MenuUtil::getStatsMenu(*Settings::oneHandedModMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::twoHandedMod] = std::make_unique<StatConfig>(ActorValue::kTwoHandedModifier,
            *Settings::twoHandedModString,
            *Settings::twoHandedModStringEnding,
            *Settings::twoHandedMod,
            MenuUtil::getStatsMenu(*Settings::twoHandedModMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::marksmanMod] = std::make_unique<StatConfig>(ActorValue::kMarksmanModifier,
            *Settings::archeryModString,
            *Settings::archeryModStringEnding,
            *Settings::archeryMod,
            MenuUtil::getStatsMenu(*Settings::archeryModMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::blockMod] = std::make_unique<StatConfig>(ActorValue::kBlockModifier,
            *Settings::blockModString,
            *Settings::blockModStringEnding,
            *Settings::blockMod,
            MenuUtil::getStatsMenu(*Settings::blockModMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::smithingMod] = std::make_unique<StatConfig>(ActorValue::kSmithingModifier,
            *Settings::smithingModString,
            *Settings::smithingModStringEnding,
            *Settings::smithingMod,
            MenuUtil::getStatsMenu(*Settings::smithingModMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::heavyArmorMod] = std::make_unique<StatConfig>(ActorValue::kHeavyArmorModifier,
            *Settings::heavyArmorModString,
            *Settings::heavyArmorModStringEnding,
            *Settings::heavyArmorMod,
            MenuUtil::getStatsMenu(*Settings::heavyArmorModMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::lightArmorMod] = std::make_unique<StatConfig>(ActorValue::kLightArmorModifier,
            *Settings::lightArmorModString,
            *Settings::lightArmorModStringEnding,
            *Settings::lightArmorMod,
            MenuUtil::getStatsMenu(*Settings::lightArmorModMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::pickpocketMod] = std::make_unique<StatConfig>(ActorValue::kPickpocketModifier,
            *Settings::pickpocketModString,
            *Settings::pickpocketModStringEnding,
            *Settings::pickpocketMod,
            MenuUtil::getStatsMenu(*Settings::pickpocketModMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::lockpickingMod] = std::make_unique<StatConfig>(ActorValue::kLockpickingModifier,
            *Settings::lockpickingModString,
            *Settings::lockpickingModStringEnding,
            *Settings::lockpickingMod,
            MenuUtil::getStatsMenu(*Settings::lockpickingModMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::sneakingMod] = std::make_unique<StatConfig>(ActorValue::kSneakingModifier,
            *Settings::sneakModString,
            *Settings::sneakModStringEnding,
            *Settings::sneakMod,
            MenuUtil::getStatsMenu(*Settings::sneakModMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::alchemyMod] = std::make_unique<StatConfig>(ActorValue::kAlchemyModifier,
            *Settings::alchemyModString,
            *Settings::alchemyModStringEnding,
            *Settings::alchemyMod,
            MenuUtil::getStatsMenu(*Settings::alchemyModMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::speechcraftMod] = std::make_unique<StatConfig>(ActorValue::kSpeechcraftModifier,
            *Settings::speechModString,
            *Settings::speechModStringEnding,
            *Settings::speechMod,
            MenuUtil::getStatsMenu(*Settings::speechModMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::enchantingMod] = std::make_unique<StatConfig>(ActorValue::kEnchantingModifier,
            *Settings::enchantingModString,
            *Settings::enchantingModStringEnding,
            *Settings::enchantingMod,
            MenuUtil::getStatsMenu(*Settings::enchantingModMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::alterationMod] = std::make_unique<StatConfig>(ActorValue::kAlterationModifier,
            *Settings::alterationModString,
            *Settings::alterationModStringEnding,
            *Settings::alterationMod,
            MenuUtil::getStatsMenu(*Settings::alterationModMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::conjurationMod] = std::make_unique<StatConfig>(ActorValue::kConjurationModifier,
            *Settings::conjurationModString,
            *Settings::conjurationModStringEnding,
            *Settings::conjurationMod,
            MenuUtil::getStatsMenu(*Settings::conjurationModMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::destructionMod] = std::make_unique<StatConfig>(ActorValue::kDestructionModifier,
            *Settings::destructionModString,
            *Settings::destructionModStringEnding,
            *Settings::destructionMod,
            MenuUtil::getStatsMenu(*Settings::destructionModMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::illusionMod] = std::make_unique<StatConfig>(ActorValue::kIllusionModifier,
            *Settings::illusionModString,
            *Settings::illusionModStringEnding,
            *Settings::illusionMod,
            MenuUtil::getStatsMenu(*Settings::illusionModMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::restorationMod] = std::make_unique<StatConfig>(ActorValue::kRestorationModifier,
            *Settings::restorationModString,
            *Settings::restorationModStringEnding,
            *Settings::restorationMod,
            MenuUtil::getStatsMenu(*Settings::restorationModMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::damageArrow] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::damageArrowString,
            *Settings::damageArrowStringEnding,
            *Settings::damageArrow,
            MenuUtil::getStatsMenu(*Settings::damageArrowMenu),
            MenuUtil::getStatsInventoryMenu(0));
        mp[StatsValue::damageLeft] = std::make_unique<StatConfig>(ActorValue::kNone,
            *Settings::damageLeftString,
            *Settings::damageLeftStringEnding,
            *Settings::damageLeft,
            MenuUtil::getStatsMenu(*Settings::damageLeftMenu),
            MenuUtil::getStatsInventoryMenu(0));

        return mp;
    }

    StatSetting() = default;
    StatSetting(const StatSetting&) = default;
    StatSetting(StatSetting&&) = delete;

    ~StatSetting() = default;

    StatSetting& operator=(const StatSetting&) = default;
    StatSetting& operator=(StatSetting&&) = delete;
};
