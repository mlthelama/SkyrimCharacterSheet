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
    thaneOfWinterhold,
    azura,
    boethiah,
    clavicusVile,
    hermaeusMora,
    hircine,
    malacath,
    mehrunesDagon,
    mephala,
    meridia,
    molagBal,
    namira,
    nocturnal,
    peryite,
    sanguine,
    sheogorath,
    vaermina
};

const std::string _constUndefined = "<undef>";

enum class ShowMenu { mStats, mFaction };

constexpr int32_t _constLogTrace = 0;
constexpr int32_t _constLogDebug = 1;
constexpr int32_t _constLogInfo = 2;

enum class StatsMenuValue { mNone = 0, mPlayer = 1, mDefence = 2, mAttack = 3, mMagic = 4, mWarrior = 5, mThief = 6 };

/* config can not work with enums, so lets map it*/
inline static std::map<int64_t, StatsMenuValue> _constConfigStatsMenu = {
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
inline static formIdValueMap _constFactionMap = { { 0x00048362, FactionValue::companions },
    { 0x0001BDB3, FactionValue::darkbrotherHood },
    { 0x0001F259, FactionValue::collegeOfWinterhold },
    { 0x00024029, FactionValue::orcFriend },
    { 0x00029DA9, FactionValue::thiefsGuild },
    { 0x0002BF9A, FactionValue::imperialLegion },
    { 0x0002BF9B, FactionValue::stormcloaks },
    { 0x0002C6C8, FactionValue::greybeard },
    { 0x02003376, FactionValue::volkiharVampireClan },
    { 0x02014217, FactionValue::dawnguard },
    { 0x04019B8A, FactionValue::houseTelvanni } };

//favor/quest thane map 200
inline static formIdValueMap _constThaneMap = { { 0x000A2CA6, FactionValue::thaneOfEastmarch },
    { 0x000A34DE, FactionValue::thaneOfFalkreath },
    { 0x000A2C9B, FactionValue::thaneOfHaafingar },
    { 0x000A34CE, FactionValue::thaneOfHjaalmarch },
    { 0x000A34D4, FactionValue::thaneOfThePale },
    { 0x000A2C86, FactionValue::thaneOfTheReach },
    { 0x00065BDF, FactionValue::thaneOfTheRift },
    { 0x000A2C9E, FactionValue::thaneOfWhiterun },  //just if stormcloaks won the war, otherwise MQ104/0002610C/160
    { 0x000A34D7, FactionValue::thaneOfWinterhold } };

enum class FactionMenuValue { mNone = 0, mFaction = 1, mThane = 2, mChampion = 3 };

/* config can not work with enums, so lets map it*/
inline static std::map<int64_t, FactionMenuValue> _constConfigFactionMenu = {
    { static_cast<int64_t>(FactionMenuValue::mNone), FactionMenuValue::mNone },
    { static_cast<int64_t>(FactionMenuValue::mFaction), FactionMenuValue::mFaction },
    { static_cast<int64_t>(FactionMenuValue::mThane), FactionMenuValue::mThane },
    { static_cast<int64_t>(FactionMenuValue::mChampion), FactionMenuValue::mChampion },
};

constexpr auto _constStaticDisplayValue = "yes"sv;
constexpr auto _constStaticMultiplier = 1;

/*
    azura, 00028AD6 100 -
    boethiah, 0004D8D6 50 100 -
    clavicusVile, 0001BFC4 200 205 -
    hermaeusMora, 0002D512 100 200 -
    hircine, 0002A49A 100 105 200 -
    malacath, 0003B681 200 -
    mehrunesDagon, 000240B8 100 -
    mephala, 0004A37B 60 80 -
    meridia, 0004E4E1 500 -
    molagBal, 00022F08 200 -
    namira, 0002C358 100 600 -
    nocturnal, 00021555 200 -
    peryite, 0008998D 100 -
    sanguine, 0001BB9B 200 -
    sheogorath, 0002AC68 200 -
    vaermina 000242AF 200 -
*/
inline static formIdValueMap _constChampionMap = {
    { 0x00028AD6, FactionValue::azura },
    { 0x0004D8D6, FactionValue::boethiah },
    { 0x0001BFC4, FactionValue::clavicusVile },
    { 0x0002D512, FactionValue::hermaeusMora },
    { 0x0002A49A, FactionValue::hircine },
    { 0x0003B681, FactionValue::malacath },
    { 0x000240B8, FactionValue::mehrunesDagon },
    { 0x0004A37B, FactionValue::mephala },
    { 0x0004E4E1, FactionValue::meridia },
    { 0x00022F08, FactionValue::molagBal },
    { 0x0002C358, FactionValue::namira },
    { 0x00021555, FactionValue::nocturnal },
    { 0x0008998D, FactionValue::peryite },
    { 0x0001BB9B, FactionValue::sanguine },
    { 0x0002AC68, FactionValue::sheogorath },
    { 0x000242AF, FactionValue::vaermina },
};
