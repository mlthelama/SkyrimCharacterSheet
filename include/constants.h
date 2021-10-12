#pragma once

enum class StatsValue {
    name,
    race,
    level,
    perkCount,
    height,
    equipedWeight,
    weight,
    armor,
    damage,
    skillTrainingsThisLevel,
    health,
    healthRatePer,
    magicka,
    magickaRatePer,
    stamina,
    staminaRatePer,
    resistDamage,
    resistDisease,
    resistPoison,
    resistFire,
    resistShock,
    resistFrost,
    resistMagic,
    oneHanded,
    twoHanded,
    archery,
    block,
    smithing,
    heavyArmor,
    lightArmor,
    pickpocket,
    lockpicking,
    sneak,
    alchemy,
    speech,
    enchanting,
    alteration,
    conjuration,
    destruction,
    illusion,
    restoration,
    oneHandedPowerMod,
    twoHandedPowerMod,
    archeryPowerMod,
    blockPowerMod,
    smithingPowerMod,
    heavyArmorPowerMod,
    lightArmorPowerMod,
    pickpocketPowerMod,
    lockpickingPowerMod,
    sneakPowerMod,
    alchemyPowerMod,
    speechPowerMod,
    enchantingPowerMod,
    alterationPowerMod,
    conjurationPowerMod,
    destructionPowerMod,
    illusionPowerMod,
    restorationPowerMod,
    speedMult,
    inventoryWeight,
    carryWeight,
    criticalChance,
    meleeDamage,
    unarmedDamage,
    absorbChance,
    weaponSpeedMult,
    bowSpeedBonus,
    shoutRecoveryMult,
    movementNoiseMult,
    dragonSouls,
    combatHealthRegenMultiply,
    attackDamageMult,
    beast,
    xp,
    reflectDamage,
    oneHandedMod,
    twoHandedMod,
    marksmanMod,
    blockMod,
    smithingMod,
    heavyArmorMod,
    lightArmorMod,
    pickpocketMod,
    lockpickingMod,
    sneakingMod,
    alchemyMod,
    speechcraftMod,
    alterationMod,
    conjurationMod,
    destructionMod,
    illusionMod,
    restorationMod,
    enchantingMod,
    damageArrow,
    damageRight,
    damageLeft,
    leftWeaponSpeedMult,
    rightItemCharge,
    leftItemCharge,
    armorPerks,
    mass,
    bowStaggerBonus,
    bypassVendorKeywordCheck,
    bypassVendorStolenCheck,
};

enum class FactionValue {
    darkbrotherHood,
    thiefsGuild,
    orcFriend,
    collegeOfWinterhold,
    companions,
    imperialLegion,
    stormcloaks,
    greybeard,
    bard,
    volkiharVampireClan,
    dawnguard,
    houseTelvanni,
    thaneOfEastmarch,
    thaneOfFalkreath,
    thaneOfHaafingar,
    thaneOfHjaalmarch,
    thaneOfThePale,
    thaneOfTheReach,
    thaneOfTheRift,
    thaneOfWhiterun,
    thaneOfWinterhold
};

const std::string undefined = "<undef>";

const std::string headerValuesName = "$ShowStats_Player";
const std::string headerAttackName = "$ShowStats_Attack";
const std::string headerDefenceName = "$ShowStats_Defence";
const std::string headerPerksMagicName = "$ShowStats_PerksMagic";
const std::string headerPerksThiefName = "$ShowStats_PerksThief";
const std::string headerPerksWarriorName = "$ShowStats_PerksWarrior";

const int32_t logTrace = 0;
const int32_t logDebug = 1;
const int32_t logInfo = 2;

enum class StatsMenuValue { mNone = 0, mPlayer = 1, mDefence = 2, mAttack = 3, mMagic = 4, mWarrior = 5, mThief = 6 };

/* config can not work with enums, so lets map it*/
inline static std::map<int64_t, StatsMenuValue> configStatsMenu = {
    { static_cast<int64_t>(StatsMenuValue::mNone), StatsMenuValue::mNone },
    { static_cast<int64_t>(StatsMenuValue::mPlayer), StatsMenuValue::mPlayer },
    { static_cast<int64_t>(StatsMenuValue::mDefence), StatsMenuValue::mDefence },
    { static_cast<int64_t>(StatsMenuValue::mAttack), StatsMenuValue::mAttack },
    { static_cast<int64_t>(StatsMenuValue::mMagic), StatsMenuValue::mMagic },
    { static_cast<int64_t>(StatsMenuValue::mWarrior), StatsMenuValue::mWarrior },
    { static_cast<int64_t>(StatsMenuValue::mThief), StatsMenuValue::mThief },
};

typedef std::map<RE::FormID, FactionValue> formIdValueMap;
typedef std::map<FactionValue, std::string> valueStringMap;  //used in faction.h and thane.h

//0x00072834 //blades, player might not be in there
inline static formIdValueMap factionMap = { { 0x00048362, FactionValue::companions },
    { 0x0001BDB3, FactionValue::darkbrotherHood }, { 0x0001F259, FactionValue::collegeOfWinterhold },
    { 0x00024029, FactionValue::orcFriend }, { 0x00029DA9, FactionValue::thiefsGuild },
    { 0x0002BF9A, FactionValue::imperialLegion }, { 0x0002BF9B, FactionValue::stormcloaks },
    { 0x0002C6C8, FactionValue::greybeard },
    //{ 0x000C13C7, StatsValue::bard} //not sure if player can be in that, nah
    { 0x02003376, FactionValue::volkiharVampireClan }, { 0x02014217, FactionValue::dawnguard },
    { 0x04019B8A, FactionValue::houseTelvanni } };

//favor/quest thane map 200
inline static formIdValueMap thaneMap = { { 0x000A2CA6, FactionValue::thaneOfEastmarch },
    { 0x000A34DE, FactionValue::thaneOfFalkreath }, { 0x000A2C9B, FactionValue::thaneOfHaafingar },
    { 0x000A34CE, FactionValue::thaneOfHjaalmarch }, { 0x000A34D4, FactionValue::thaneOfThePale },
    { 0x000A2C86, FactionValue::thaneOfTheReach }, { 0x00065BDF, FactionValue::thaneOfTheRift },
    { 0x000A2C9E, FactionValue::thaneOfWhiterun },  //just if stormcloaks won the war, otherwise MQ104/0002610C/160
    { 0x000A34D7, FactionValue::thaneOfWinterhold } };

const std::string headerFactionName = "Faction";
const std::string headerThaneName = "Thane";
const std::string headerChampionName = "Champion";

enum class FactionMenuValue { mNone = 0, mFaction = 1, mThane = 2, mChampion = 3 };

/* config can not work with enums, so lets map it*/
inline static std::map<int64_t, FactionMenuValue> configFactionMenu = {
    { static_cast<int64_t>(FactionMenuValue::mNone), FactionMenuValue::mNone },
    { static_cast<int64_t>(FactionMenuValue::mFaction), FactionMenuValue::mFaction },
    { static_cast<int64_t>(FactionMenuValue::mThane), FactionMenuValue::mThane },
    { static_cast<int64_t>(FactionMenuValue::mChampion), FactionMenuValue::mChampion },
};

const std::string staticDisplayValue = "yes";

static constexpr std::string_view TITLE_NAME_FACTIONS = "Show Factions";
static constexpr std::string_view TITLE_NAME_STATS = "$ShowStats";
static constexpr std::string_view TITLE_NAME_STATS_NAME = "Show Stats";

enum class ShowMenu { mStats, mFaction };

inline static std::map<ShowMenu, std::string_view> menuName = { { ShowMenu::mStats, TITLE_NAME_STATS },
    { ShowMenu::mFaction, TITLE_NAME_STATS_NAME } };