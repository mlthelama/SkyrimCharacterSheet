#pragma once

namespace constants
{
	enum class StatsValue
	{
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
		enchantingMod
	};

	typedef std::map<constants::StatsValue, std::string> StatsValueMap;
	typedef std::map<constants::StatsValue, RE::ActorValue> ActorMap;
	typedef std::map<constants::StatsValue, std::string> ValueMap;
	typedef std::map<constants::StatsValue, boolean> ShowMap;

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
};
