#pragma once

namespace constants
{
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
		darkbrotherHood,
		thiefsGuild,
		orcFriend,
		collegeOfWinterhold,
		companions,
		imperialLegion,
		stormcloaks,
		greybeard
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

	
	/*we might need a map here*/
	inline static vector<RE::FormID> factionList = { 0x00048362 //companions
		, 0x0001BDB3 //dark brotherhood
		, 0x0001F259 //college of winterhold
		, 0x00024029 //orc friend/kin
		, 0x00029DA9 //Thiefs Guild
		, 0x0002BF9A //Imperial Legion
		, 0x0002BF9B //Sons of Skyrim, Stormcloaks
		, 0x0002C6C8 //Greybeard
		, 0x0004135B //dark brotherhood, again?
		//, 0x00103372 //archmage ?
		, 0x00072834 //blades, player might not be in there
		//, 0x001070DD //harbringer
		, 0x02003375 //dawnguard
		, 0x02003376 //vampire
	};
};
