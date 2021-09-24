#pragma once

struct Settings
{
	using ISetting = AutoTOML::ISetting;
	using bSetting = AutoTOML::bSetting;
	using sSetting = AutoTOML::sSetting;
	using iSetting = AutoTOML::iSetting;

	static void load() {
		try {
			const auto table = toml::parse_file("Data/SKSE/Plugins/ShowStats.toml"s);
			for (const auto& setting : ISetting::get_settings()) {
				setting->load(table);
			}
		} catch (const toml::parse_error& ex) {
			std::ostringstream ss;
			ss << "Error parsing file \'" << *ex.source().path << "\':\n"
			   << '\t' << ex.description() << '\n'
			   << "\t\t(" << ex.source().begin << ')';
			logger::error(ss.str());
			throw std::runtime_error("failed to load settings"s);
		}
	}

	static inline bSetting name{ "showStats"s, "name"s, true };
	static inline bSetting race{ "showStats"s, "race"s, true };
	static inline bSetting level{ "showStats"s, "level"s, true };
	static inline bSetting perkCount{ "showStats"s, "perkCount"s, true };
	static inline bSetting height{ "showStats"s, "height"s, true };
	static inline bSetting equipedWeight{ "showStats"s, "equipedWeight"s, true };
	static inline bSetting weight{ "showStats"s, "weight"s, true };
	static inline bSetting armor{ "showStats"s, "armor"s, true };
	static inline bSetting damage{ "showStats"s, "damage"s, true };
	static inline bSetting skillTrainingsThisLevel{ "showStats"s, "skillTrainingsThisLevel"s, true };
	static inline bSetting health{ "showStats"s, "health"s, true };
	static inline bSetting healthRate{ "showStats"s, "healthRatePer"s, true };
	static inline bSetting magicka{ "showStats"s, "magicka"s, true };
	static inline bSetting magickaRate{ "showStats"s, "magickaRatePer"s, true };
	static inline bSetting stamina{ "showStats"s, "stamina"s, true };
	static inline bSetting staminaRate{ "showStats"s, "staminaRatePer"s, true };
	static inline bSetting resistDamage{ "showStats"s, "resistDamage"s, true };
	static inline bSetting resistDisease{ "showStats"s, "resistDisease"s, true };
	static inline bSetting resistPoison{ "showStats"s, "resistPoison"s, true };
	static inline bSetting resistFire{ "showStats"s, "resistFire"s, true };
	static inline bSetting resistShock{ "showStats"s, "resistShock"s, true };
	static inline bSetting resistFrost{ "showStats"s, "resistFrost"s, true };
	static inline bSetting resistMagic{ "showStats"s, "resistMagic"s, true };
	static inline bSetting oneHanded{ "showStats"s, "oneHanded"s, true };
	static inline bSetting twoHanded{ "showStats"s, "twoHanded"s, true };
	static inline bSetting archery{ "showStats"s, "archery"s, true };
	static inline bSetting block{ "showStats"s, "block"s, true };
	static inline bSetting smithing{ "showStats"s, "smithing"s, true };
	static inline bSetting heavyArmor{ "showStats"s, "heavyArmor"s, true };
	static inline bSetting lightArmor{ "showStats"s, "lightArmor"s, true };
	static inline bSetting pickpocket{ "showStats"s, "pickpocket"s, true };
	static inline bSetting lockpicking{ "showStats"s, "lockpicking"s, true };
	static inline bSetting sneak{ "showStats"s, "sneak"s, true };
	static inline bSetting alchemy{ "showStats"s, "alchemy"s, true };
	static inline bSetting speech{ "showStats"s, "speech"s, true };
	static inline bSetting enchanting{ "showStats"s, "enchanting"s, true };
	static inline bSetting alteration{ "showStats"s, "alteration"s, true };
	static inline bSetting conjuration{ "showStats"s, "conjuration"s, true };
	static inline bSetting destruction{ "showStats"s, "destruction"s, true };
	static inline bSetting illusion{ "showStats"s, "illusion"s, true };
	static inline bSetting restoration{ "showStats"s, "restoration"s, true };
	static inline bSetting oneHandedPowerMod{ "showStats"s, "oneHandedPowerMod"s, true };
	static inline bSetting twoHandedPowerMod{ "showStats"s, "twoHandedPowerMod"s, true };
	static inline bSetting archeryPowerMod{ "showStats"s, "archeryPowerMod"s, true };
	static inline bSetting blockPowerMod{ "showStats"s, "blockPowerMod"s, true };
	static inline bSetting smithingPowerMod{ "showStats"s, "smithingPowerMod"s, true };
	static inline bSetting heavyArmorPowerMod{ "showStats"s, "heavyArmorPowerMod"s, true };
	static inline bSetting lightArmorPowerMod{ "showStats"s, "lightArmorPowerMod"s, true };
	static inline bSetting pickpocketPowerMod{ "showStats"s, "pickpocketPowerMod"s, true };
	static inline bSetting lockpickingPowerMod{ "showStats"s, "lockpickingPowerMod"s, true };
	static inline bSetting sneakPowerMod{ "showStats"s, "sneakPowerMod"s, true };
	static inline bSetting alchemyPowerMod{ "showStats"s, "alchemyPowerMod"s, true };
	static inline bSetting speechPowerMod{ "showStats"s, "speechPowerMod"s, true };
	static inline bSetting enchantingPowerMod{ "showStats"s, "enchantingPowerMod"s, true };
	static inline bSetting alterationPowerMod{ "showStats"s, "alterationPowerMod"s, true };
	static inline bSetting conjurationPowerMod{ "showStats"s, "conjurationPowerMod"s, true };
	static inline bSetting destructionPowerMod{ "showStats"s, "destructionPowerMod"s, true };
	static inline bSetting illusionPowerMod{ "showStats"s, "illusionPowerMod"s, true };
	static inline bSetting restorationPowerMod{ "showStats"s, "restorationPowerMod"s, true };
	static inline bSetting speedMult{ "showStats"s, "speedMult"s, true };
	static inline bSetting inventoryWeight{ "showStats"s, "inventoryWeight"s, true };
	static inline bSetting carryWeight{ "showStats"s, "carryWeight"s, true };
	static inline bSetting criticalChance{ "showStats"s, "criticalChance"s, true };
	static inline bSetting meleeDamage{ "showStats"s, "meleeDamage"s, true };
	static inline bSetting unarmedDamage{ "showStats"s, "unarmedDamage"s, true };
	static inline bSetting absorbChance{ "showStats"s, "absorbChance"s, true };
	static inline bSetting weaponSpeedMult{ "showStats"s, "weaponSpeedMult"s, true };
	static inline bSetting bowSpeedBonus{ "showStats"s, "bowSpeedBonus"s, true };
	static inline bSetting shoutRecoveryMult{ "showStats"s, "shoutRecoveryMult"s, true };
	static inline bSetting movementNoiseMult{ "showStats"s, "movementNoiseMult"s, true };
	static inline bSetting dragonSouls{ "showStats"s, "dragonSouls"s, true };
	static inline bSetting combatHealthRegenMultiply{ "showStats"s, "combatHealthRegenMultiply"s, true };
	static inline bSetting attackDamageMult{ "showStats"s, "attackDamageMult"s, true };
	static inline bSetting beast{ "showStats"s, "beast"s, true };
	static inline bSetting xp{ "showStats"s, "xp"s, true };
	static inline bSetting reflectDamage{ "showStats"s, "reflectDamage"s, true };

	static inline sSetting nameString { "showStatsName"s, "name"s, "<undef>" };
	static inline sSetting raceString { "showStatsName"s, "race"s, "<undef>" };
	static inline sSetting levelString { "showStatsName"s, "level"s, "<undef>" };
	static inline sSetting perkCountString{ "showStatsName"s, "perkCount"s, "<undef>" };
	static inline sSetting heightString{ "showStatsName"s, "height"s, "<undef>" };
	static inline sSetting equipedWeightString{ "showStatsName"s, "equipedWeight"s, "<undef>" };
	static inline sSetting weightString{ "showStatsName"s, "weight"s, "<undef>" };
	static inline sSetting armorString{ "showStatsName"s, "armor"s, "<undef>" };
	static inline sSetting damageString{ "showStatsName"s, "damage"s, "<undef>" };
	static inline sSetting skillTrainingsThisLevelString{ "showStatsName"s, "skillTrainingsThisLevel"s, "<undef>" };
	static inline sSetting healthString{ "showStatsName"s, "health"s, "<undef>" };
	static inline sSetting healthRateString{ "showStatsName"s, "healthRatePer"s, "<undef>" };
	static inline sSetting magickaString{ "showStatsName"s, "magicka"s, "<undef>" };
	static inline sSetting magickaRateString{ "showStatsName"s, "magickaRatePer"s, "<undef>" };
	static inline sSetting staminaString{ "showStatsName"s, "stamina"s, "<undef>" };
	static inline sSetting staminaRateString{ "showStatsName"s, "staminaRatePer"s, "<undef>" };
	static inline sSetting resistDamageString{ "showStatsName"s, "resistDamage"s, "<undef>" };
	static inline sSetting resistDiseaseString{ "showStatsName"s, "resistDisease"s, "<undef>" };
	static inline sSetting resistPoisonString{ "showStatsName"s, "resistPoison"s, "<undef>" };
	static inline sSetting resistFireString{ "showStatsName"s, "resistFire"s, "<undef>" };
	static inline sSetting resistShockString{ "showStatsName"s, "resistShock"s, "<undef>" };
	static inline sSetting resistFrostString{ "showStatsName"s, "resistFrost"s, "<undef>" };
	static inline sSetting resistMagicString{ "showStatsName"s, "resistMagic"s, "<undef>" };
	static inline sSetting oneHandedString{ "showStatsName"s, "oneHanded"s, "<undef>" };
	static inline sSetting twoHandedString{ "showStatsName"s, "twoHanded"s, "<undef>" };
	static inline sSetting archeryString{ "showStatsName"s, "archery"s, "<undef>" };
	static inline sSetting blockString{ "showStatsName"s, "block"s, "<undef>" };
	static inline sSetting smithingString{ "showStatsName"s, "smithing"s, "<undef>" };
	static inline sSetting heavyArmorString{ "showStatsName"s, "heavyArmor"s, "<undef>" };
	static inline sSetting lightArmorString{ "showStatsName"s, "lightArmor"s, "<undef>" };
	static inline sSetting pickpocketString{ "showStatsName"s, "pickpocket"s, "<undef>" };
	static inline sSetting lockpickingString{ "showStatsName"s, "lockpicking"s, "<undef>" };
	static inline sSetting sneakString{ "showStatsName"s, "sneak"s, "<undef>" };
	static inline sSetting alchemyString{ "showStatsName"s, "alchemy"s, "<undef>" };
	static inline sSetting speechString{ "showStatsName"s, "speech"s, "<undef>" };
	static inline sSetting enchantingString{ "showStatsName"s, "enchanting"s, "<undef>" };
	static inline sSetting alterationString{ "showStatsName"s, "alteration"s, "<undef>" };
	static inline sSetting conjurationString{ "showStatsName"s, "conjuration"s, "<undef>" };
	static inline sSetting destructionString{ "showStatsName"s, "destruction"s, "<undef>" };
	static inline sSetting illusionString{ "showStatsName"s, "illusion"s, "<undef>" };
	static inline sSetting restorationString{ "showStatsName"s, "restoration"s, "<undef>" };
	static inline sSetting oneHandedPowerModString{ "showStatsName"s, "oneHandedPowerMod"s, "<undef>" };
	static inline sSetting twoHandedPowerModString{ "showStatsName"s, "twoHandedPowerMod"s, "<undef>" };
	static inline sSetting archeryPowerModString{ "showStatsName"s, "archeryPowerMod"s, "<undef>" };
	static inline sSetting blockPowerModString{ "showStatsName"s, "blockPowerMod"s, "<undef>" };
	static inline sSetting smithingPowerModString{ "showStatsName"s, "smithingPowerMod"s, "<undef>" };
	static inline sSetting heavyArmorPowerModString{ "showStatsName"s, "heavyArmorPowerMod"s, "<undef>" };
	static inline sSetting lightArmorPowerModString{ "showStatsName"s, "lightArmorPowerMod"s, "<undef>" };
	static inline sSetting pickpocketPowerModString{ "showStatsName"s, "pickpocketPowerMod"s, "<undef>" };
	static inline sSetting lockpickingPowerModString{ "showStatsName"s, "lockpickingPowerMod"s, "<undef>" };
	static inline sSetting sneakPowerModString{ "showStatsName"s, "sneakPowerMod"s, "<undef>" };
	static inline sSetting alchemyPowerModString{ "showStatsName"s, "alchemyPowerMod"s, "<undef>" };
	static inline sSetting speechPowerModString{ "showStatsName"s, "speechPowerMod"s, "<undef>" };
	static inline sSetting enchantingPowerModString{ "showStatsName"s, "enchantingPowerMod"s, "<undef>" };
	static inline sSetting alterationPowerModString{ "showStatsName"s, "alterationPowerMod"s, "<undef>" };
	static inline sSetting conjurationPowerModString{ "showStatsName"s, "conjurationPowerMod"s, "<undef>" };
	static inline sSetting destructionPowerModString{ "showStatsName"s, "destructionPowerMod"s, "<undef>" };
	static inline sSetting illusionPowerModString{ "showStatsName"s, "illusionPowerMod"s, "<undef>" };
	static inline sSetting restorationPowerModString{ "showStatsName"s, "restorationPowerMod"s, "<undef>" };
	static inline sSetting speedMultString{ "showStatsName"s, "speedMult"s, "<undef>" };
	static inline sSetting inventoryWeightString{ "showStatsName"s, "inventoryWeight"s, "<undef>" };
	static inline sSetting carryWeightString{ "showStatsName"s, "carryWeight"s, "<undef>" };
	static inline sSetting criticalChanceString{ "showStatsName"s, "criticalChance"s, "<undef>" };
	static inline sSetting meleeDamageString{ "showStatsName"s, "meleeDamage"s, "<undef>" };
	static inline sSetting unarmedDamageString{ "showStatsName"s, "unarmedDamage"s, "<undef>" };
	static inline sSetting absorbChanceString{ "showStatsName"s, "absorbChance"s, "<undef>" };
	static inline sSetting weaponSpeedMultString{ "showStatsName"s, "weaponSpeedMult"s, "<undef>" };
	static inline sSetting bowSpeedBonusString{ "showStatsName"s, "bowSpeedBonus"s, "<undef>" };
	static inline sSetting shoutRecoveryMultString{ "showStatsName"s, "shoutRecoveryMult"s, "<undef>" };
	static inline sSetting movementNoiseMultString{ "showStatsName"s, "movementNoiseMult"s, "<undef>" };
	static inline sSetting dragonSoulsString{ "showStatsName"s, "dragonSouls"s, "<undef>" };
	static inline sSetting combatHealthRegenMultiplyString{ "showStatsName"s, "combatHealthRegenMultiply"s, "<undef>" };
	static inline sSetting attackDamageMultString{ "showStatsName"s, "attackDamageMult"s, "<undef>" };
	static inline sSetting beastString{ "showStatsName"s, "beast"s, "<undef>" };
	static inline sSetting xpString{ "showStatsName"s, "xp"s, "<undef>" };
	static inline sSetting reflectDamageString{ "showStatsName"s, "reflectDamage"s, "<undef>" };

	static inline iSetting logLevel{"General"s, "logLevel"s, 0};

	static inline sSetting vampireString{ "showBeastName"s, "vampire"s, "<undef>" };
	static inline sSetting werewolfString{ "showBeastName"s, "werewolf"s, "<undef>" };
};