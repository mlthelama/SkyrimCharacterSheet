#pragma once

namespace constants
{
	enum StatsValue
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
		healthRate,
		healthRateMult,
		magicka,
		magickaRate,
		magickaRateMult,
		stamina,
		staminaRate,
		staminaRateMult,
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
		attackDamageMult
	};

	/*add cfg to change that string*/
	const std::string nameString = "name";
	const std::string raceString = "race";
	const std::string levelString = "level";
	const std::string perkCountString = "perkCount";
	const std::string heightString = "height";
	const std::string equipedWeightString = "equipedWeight";
	const std::string weightString = "weight";
	const std::string armorString = "armor";
	const std::string damageString = "damage";
	const std::string skillTrainingsThisLevelString = "skillTrainingsThisLevel";
	//const std::string defaultClass = "defaultClass";

	const std::string healthString = "health";
	const std::string healthRateString = "healthRate";
	const std::string healthRateMultString = "healthRateMult";
	const std::string magickaString = "magicka";
	const std::string magickaRateString = "magickaRate";
	const std::string magickaRateMultString = "magickaRateMult";
	const std::string staminaString = "stamina";
	const std::string staminaRateString = "staminaRate";
	const std::string staminaRateMultString = "staminaRateMult";

	const std::string resistDamageString = "resistDamage";
	const std::string resistDiseaseString = "resistDisease";
	const std::string resistPoisonString = "resistPoison";
	const std::string resistFireString = "resistFire";
	const std::string resistShockString = "resistShock";
	const std::string resistFrostString = "resistFrost";
	const std::string resistMagicString = "resistMagic";

	const std::string oneHandedString = "oneHanded";
	const std::string twoHandedString = "twoHanded";
	const std::string archeryString = "archery";
	const std::string blockString = "block";
	const std::string smithingString = "smithing";
	const std::string heavyArmorString = "heavyArmor";
	const std::string lightArmorString = "lightArmor";
	const std::string pickpocketString = "pickpocket";
	const std::string lockpickingString = "lockpicking";
	const std::string sneakString = "sneak";
	const std::string alchemyString = "alchemy";
	const std::string speechString = "speech";
	const std::string enchantingString = "enchanting";
	const std::string alterationString = "alteration";
	const std::string conjurationString = "conjuration";
	const std::string destructionString = "destruction";
	const std::string illusionString = "illusion";
	const std::string restorationString = "restoration";

	const std::string oneHandedPowerModString = "oneHandedPowerMod";
	const std::string twoHandedPowerModString = "twoHandedPowerMod";
	const std::string archeryPowerModString = "archeryPowerMod";
	const std::string blockPowerModString = "blockPowerMod";
	const std::string smithingPowerModString = "smithingPowerMod";
	const std::string heavyArmorPowerModString = "heavyArmorPowerMod";
	const std::string lightArmorPowerModString = "lightArmorPowerMod";
	const std::string pickpocketPowerModString = "pickpocketPowerMod";
	const std::string lockpickingPowerModString = "lockpickingPowerMod";
	const std::string sneakPowerModString = "sneakPowerMod";
	const std::string alchemyPowerModString = "alchemyPowerMod";
	const std::string speechPowerModString = "speechPowerMod";
	const std::string enchantingPowerModString = "enchantingPowerMod";
	const std::string alterationPowerModString = "alterationPowerMod";
	const std::string conjurationPowerModString = "conjurationPowerMod";
	const std::string destructionPowerModString = "destructionPowerMod";
	const std::string illusionPowerModString = "illusionPowerMod";
	const std::string restorationPowerModString = "restorationPowerMod";

	const std::string speedMultString = "speedMult";
	const std::string inventoryWeightString = "inventoryWeight";
	const std::string carryWeightString = "carryWeight";
	const std::string criticalChanceString = "criticalChance";
	const std::string meleeDamageString = "meleeDamage";
	const std::string unarmedDamageString = "unarmedDamage";
	const std::string absorbChanceString = "absorbChance";
	const std::string weaponSpeedMultString = "weaponSpeedMult";
	const std::string bowSpeedBonusString = "bowSpeedBonus";
	const std::string shoutRecoveryMultString = "shoutRecoveryMult";
	const std::string movementNoiseMultString = "movementNoiseMult";
	const std::string dragonSoulsString = "dragonSouls";
	const std::string combatHealthRegenMultiplyString = "combatHealthRegenMultiply";
	const std::string attackDamageMultString = "attackDamageMult";

	typedef std::map<constants::StatsValue, std::string> StatsValueMap;
	typedef std::map<constants::StatsValue, RE::ActorValue> ActorMap;
	typedef std::map<constants::StatsValue, std::string> ValueMap;

	static const inline StatsValueMap nameMap = {
		{ StatsValue::name, constants::nameString },
		{ StatsValue::race, constants::raceString },
		{ StatsValue::level, constants::levelString },
		{ StatsValue::perkCount, constants::perkCountString },
		{ StatsValue::height, constants::heightString },
		{ StatsValue::equipedWeight, constants::equipedWeightString },
		{ StatsValue::weight, constants::weightString },
		{ StatsValue::armor, constants::armorString },
		{ StatsValue::damage, constants::damageString },
		{ StatsValue::skillTrainingsThisLevel, constants::skillTrainingsThisLevelString },
		{ StatsValue::health, constants::healthString },

		{ StatsValue::healthRate, constants::healthRateString },
		{ StatsValue::healthRateMult, constants::healthRateMultString },
		{ StatsValue::magicka, constants::magickaString },
		{ StatsValue::magickaRate, constants::magickaRateString },
		{ StatsValue::magickaRateMult, constants::magickaRateMultString },
		{ StatsValue::stamina, constants::staminaString },
		{ StatsValue::staminaRate, constants::staminaRateString },
		{ StatsValue::staminaRateMult, constants::staminaRateMultString },

		{ StatsValue::resistDamage, constants::resistDamageString },
		{ StatsValue::resistDisease, constants::resistDiseaseString },
		{ StatsValue::resistPoison, constants::resistPoisonString },
		{ StatsValue::resistFire, constants::resistFireString },
		{ StatsValue::resistShock, constants::resistShockString },
		{ StatsValue::resistFrost, constants::resistFrostString },
		{ StatsValue::resistMagic, constants::resistMagicString },

		{ StatsValue::oneHanded, constants::oneHandedString },
		{ StatsValue::twoHanded, constants::twoHandedString },
		{ StatsValue::archery, constants::archeryString },
		{ StatsValue::block, constants::blockString },
		{ StatsValue::smithing, constants::smithingString },
		{ StatsValue::heavyArmor, constants::heavyArmorString },
		{ StatsValue::lightArmor, constants::lightArmorString },
		{ StatsValue::pickpocket, constants::pickpocketString },
		{ StatsValue::lockpicking, constants::lockpickingString },
		{ StatsValue::sneak, constants::sneakString },
		{ StatsValue::alchemy, constants::alchemyString },
		{ StatsValue::speech, constants::speechString },
		{ StatsValue::enchanting, constants::enchantingString },
		{ StatsValue::alteration, constants::alterationString },
		{ StatsValue::conjuration, constants::conjurationString },
		{ StatsValue::destruction, constants::destructionString },
		{ StatsValue::illusion, constants::illusionString },
		{ StatsValue::restoration, constants::restorationString },

		{ StatsValue::oneHandedPowerMod, constants::oneHandedPowerModString },
		{ StatsValue::twoHandedPowerMod, constants::twoHandedPowerModString },
		{ StatsValue::archeryPowerMod, constants::archeryPowerModString },
		{ StatsValue::blockPowerMod, constants::blockPowerModString },
		{ StatsValue::smithingPowerMod, constants::smithingPowerModString },
		{ StatsValue::heavyArmorPowerMod, constants::heavyArmorPowerModString },
		{ StatsValue::lightArmorPowerMod, constants::lightArmorPowerModString },
		{ StatsValue::pickpocketPowerMod, constants::pickpocketPowerModString },
		{ StatsValue::lockpickingPowerMod, constants::lockpickingPowerModString },
		{ StatsValue::sneakPowerMod, constants::sneakPowerModString },
		{ StatsValue::alchemyPowerMod, constants::alchemyPowerModString },
		{ StatsValue::speechPowerMod, constants::speechPowerModString },
		{ StatsValue::enchantingPowerMod, constants::enchantingPowerModString },
		{ StatsValue::alterationPowerMod, constants::alterationPowerModString },
		{ StatsValue::conjurationPowerMod, constants::conjurationPowerModString },
		{ StatsValue::destructionPowerMod, constants::destructionPowerModString },
		{ StatsValue::illusionPowerMod, constants::illusionPowerModString },
		{ StatsValue::restorationPowerMod, constants::restorationPowerModString },

		{ StatsValue::speedMult, constants::speedMultString },
		{ StatsValue::inventoryWeight, constants::inventoryWeightString },
		{ StatsValue::carryWeight, constants::carryWeightString },
		{ StatsValue::criticalChance, constants::criticalChanceString },
		{ StatsValue::meleeDamage, constants::meleeDamageString },
		{ StatsValue::unarmedDamage, constants::unarmedDamageString },
		{ StatsValue::absorbChance, constants::absorbChanceString },
		{ StatsValue::weaponSpeedMult, constants::weaponSpeedMultString },
		{ StatsValue::bowSpeedBonus, constants::bowSpeedBonusString },
		{ StatsValue::shoutRecoveryMult, constants::shoutRecoveryMultString },
		{ StatsValue::movementNoiseMult, constants::movementNoiseMultString },
		{ StatsValue::dragonSouls, constants::dragonSoulsString },
		{ StatsValue::combatHealthRegenMultiply, constants::combatHealthRegenMultiplyString },
		{ StatsValue::attackDamageMult, constants::attackDamageMultString }
	};

	const std::string undefined = "<undef>";

	inline std::string getName(StatsValue p_val) {
		auto it = nameMap.find(p_val);

		if (it != nameMap.end()) {
			return it->second;
		} 
		return undefined;
	}

	const std::string headerValuesName = "Player";
	const std::string headerAttackName = "Attack";
	const std::string headerDefenceName = "Defence";
	const std::string headerPerksName = "Perks";
};
