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
	houseTelvanni
};

const string undefined = "<undef>";

const string headerValuesName = "$ShowStats_Player";
const string headerAttackName = "$ShowStats_Attack";
const string headerDefenceName = "$ShowStats_Defence";
const string headerPerksMagicName = "$ShowStats_PerksMagic";
const string headerPerksThiefName = "$ShowStats_PerksThief";
const string headerPerksWarriorName = "$ShowStats_PerksWarrior";

const int32_t logTrace = 0;
const int32_t logDebug = 1;
const int32_t logInfo = 2;
	
enum class MenuValue {
	//mNone = static_cast<underlying_type_t<MenuValue>>(0),
	mNone = 0,
	mPlayer = 1,
	mDefence = 2,
	mAttack = 3,
	mMagic = 4,
	mWarrior = 5,
	mThief = 6
};

/* config can not work with enums, so lets map it*/
inline static map<int64_t, MenuValue> configMenu = {
	{ static_cast<int64_t>(MenuValue::mNone), MenuValue::mNone },
	{ static_cast<int64_t>(MenuValue::mPlayer), MenuValue::mPlayer },
	{ static_cast<int64_t>(MenuValue::mDefence), MenuValue::mDefence },
	{ static_cast<int64_t>(MenuValue::mAttack), MenuValue::mAttack },
	{ static_cast<int64_t>(MenuValue::mMagic), MenuValue::mMagic },
	{ static_cast<int64_t>(MenuValue::mWarrior), MenuValue::mWarrior },
	{ static_cast<int64_t>(MenuValue::mThief), MenuValue::mThief },
};

//0x02003376 should be DLC1VampireFaction Volkihar Vampire Clan
//0x02014217 should be DLC1DawnguardFaction
//0x04019b8a Staff Maker Faction, but should indicate House Telvanni
//0x00072834 //blades, player might not be in there
inline static map<RE::FormID, StatsValue> factionMap = {
	{ 0x00048362, StatsValue::companions },
	{ 0x0001BDB3, StatsValue::darkbrotherHood },
	{ 0x0001F259, StatsValue::collegeOfWinterhold },
	{ 0x00024029, StatsValue::orcFriend },
	{ 0x00029DA9, StatsValue::thiefsGuild },
	{ 0x0002BF9A, StatsValue::imperialLegion },
	{ 0x0002BF9B, StatsValue::stormcloaks },
	{ 0x0002C6C8, StatsValue::greybeard },
	//{ 0x000C13C7, StatsValue::bard} //not sure if player can be in that, nah
	{ 0x02003376, StatsValue::volkiharVampireClan },
	{ 0x02014217, StatsValue::dawnguard },
	{ 0x04019B8A, StatsValue::houseTelvanni }
};