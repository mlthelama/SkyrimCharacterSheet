#include "player.h"

Player* Player::GetSingleton()
{
	static Player singleton;
	return std::addressof(singleton);
}

constants::ValueMap Player::getValues()
{
	return GatherValues();
}

constants::ValueMap Player::GatherValues()
{
	constants::ValueMap playerValues;
	RE::PlayerCharacter* player = RE::PlayerCharacter::GetSingleton();
	loadSettings();
	//maybe add factions too, someday

	addToValues(playerValues, constants::StatsValue::name, player->GetName());
	addToValues(playerValues, constants::StatsValue::race, player->GetRace()->GetFullName());
	addToValues(playerValues, constants::StatsValue::level, std::to_string(player->GetLevel()));
	addToValues(playerValues, constants::StatsValue::perkCount, std::to_string(player->perkCount));
	addToValues(playerValues, constants::StatsValue::height, getStringValueFromFloat(player->GetHeight()));
	addToValues(playerValues, constants::StatsValue::equipedWeight, getStringValueFromFloat(player->GetWeight()));
	addToValues(playerValues, constants::StatsValue::armor, getStringValueFromFloat(player->armorRating));
	addToValues(playerValues, constants::StatsValue::damage, getStringValueFromFloat(0));
	addToValues(playerValues, constants::StatsValue::skillTrainingsThisLevel, std::to_string(player->skillTrainingsThisLevel));
	/*to do add xp and beast (vampire, werewolf)*/
	addToValues(playerValues, constants::StatsValue::beast, "yes");
	addToValues(playerValues, constants::StatsValue::xp, "yes");

	/*
	RE::BGSDefaultObjectManager* defaultObject = RE::BGSDefaultObjectManager::GetSingleton();
	playerValues["test"] = defaultObject->GetObject(RE::DEFAULT_OBJECT::kPlayerIsVampireVariable)->GetName();
	*/
	//add here health, magicka, stamina, skill values, ...
	for (const auto& [key, value] : staticValues) {
		if (showValue(key)) {
			playerValues[key] = getStringValueFromFloat(player->GetActorValue(value));
		}
	}
	PrintValues(playerValues);

	return playerValues;
}

void Player::PrintValues(constants::ValueMap& p_map)
{
	for (const auto& [key, value] : p_map) {
		logger::trace("{} = {}"sv, getValueName(key), value);
	}
}

std::string Player::getStringValueFromFloat( float x )
{
	return std::to_string(round(x * 100.0) / 100.0);
}

void Player::loadSettings() {
	showMap = {
		{ constants::StatsValue::name, *Settings::name },
		{ constants::StatsValue::race, *Settings::race },
		{ constants::StatsValue::level, *Settings::level },
		{ constants::StatsValue::perkCount, *Settings::perkCount },
		{ constants::StatsValue::height, *Settings::height },
		{ constants::StatsValue::equipedWeight, *Settings::equipedWeight },
		{ constants::StatsValue::weight, *Settings::weight },
		{ constants::StatsValue::armor, *Settings::armor },
		{ constants::StatsValue::damage, *Settings::damage },
		{ constants::StatsValue::skillTrainingsThisLevel, *Settings::skillTrainingsThisLevel },
		{ constants::StatsValue::health, *Settings::health },

		{ constants::StatsValue::healthRate, *Settings::healthRate },
		{ constants::StatsValue::healthRateMult, *Settings::healthRateMult },
		{ constants::StatsValue::magicka, *Settings::magicka },
		{ constants::StatsValue::magickaRate, *Settings::magickaRate },
		{ constants::StatsValue::magickaRateMult, *Settings::magickaRateMult },
		{ constants::StatsValue::stamina, *Settings::stamina },
		{ constants::StatsValue::staminaRate, *Settings::staminaRate },
		{ constants::StatsValue::staminaRateMult, *Settings::staminaRateMult },

		{ constants::StatsValue::resistDamage, *Settings::resistDamage },
		{ constants::StatsValue::resistDisease, *Settings::resistDisease },
		{ constants::StatsValue::resistPoison, *Settings::resistPoison },
		{ constants::StatsValue::resistFire, *Settings::resistFire },
		{ constants::StatsValue::resistShock, *Settings::resistShock },
		{ constants::StatsValue::resistFrost, *Settings::resistFrost },
		{ constants::StatsValue::resistMagic, *Settings::resistMagic },

		{ constants::StatsValue::oneHanded, *Settings::oneHanded },
		{ constants::StatsValue::twoHanded, *Settings::twoHanded },
		{ constants::StatsValue::archery, *Settings::archery },
		{ constants::StatsValue::block, *Settings::block },
		{ constants::StatsValue::smithing, *Settings::smithing },
		{ constants::StatsValue::heavyArmor, *Settings::heavyArmor },
		{ constants::StatsValue::lightArmor, *Settings::lightArmor },
		{ constants::StatsValue::pickpocket, *Settings::pickpocket },
		{ constants::StatsValue::lockpicking, *Settings::lockpicking },
		{ constants::StatsValue::sneak, *Settings::sneak },
		{ constants::StatsValue::alchemy, *Settings::alchemy },
		{ constants::StatsValue::speech, *Settings::speech },
		{ constants::StatsValue::enchanting, *Settings::enchanting },
		{ constants::StatsValue::alteration, *Settings::alteration },
		{ constants::StatsValue::conjuration, *Settings::conjuration },
		{ constants::StatsValue::destruction, *Settings::destruction },
		{ constants::StatsValue::illusion, *Settings::illusion },
		{ constants::StatsValue::restoration, *Settings::restoration },

		{ constants::StatsValue::oneHandedPowerMod, *Settings::oneHandedPowerMod },
		{ constants::StatsValue::twoHandedPowerMod, *Settings::twoHandedPowerMod },
		{ constants::StatsValue::archeryPowerMod, *Settings::archeryPowerMod },
		{ constants::StatsValue::blockPowerMod, *Settings::blockPowerMod },
		{ constants::StatsValue::smithingPowerMod, *Settings::smithingPowerMod },
		{ constants::StatsValue::heavyArmorPowerMod, *Settings::heavyArmorPowerMod },
		{ constants::StatsValue::lightArmorPowerMod, *Settings::lightArmorPowerMod },
		{ constants::StatsValue::pickpocketPowerMod, *Settings::pickpocketPowerMod },
		{ constants::StatsValue::lockpickingPowerMod, *Settings::lockpickingPowerMod },
		{ constants::StatsValue::sneakPowerMod, *Settings::sneakPowerMod },
		{ constants::StatsValue::alchemyPowerMod, *Settings::alchemyPowerMod },
		{ constants::StatsValue::speechPowerMod, *Settings::speechPowerMod },
		{ constants::StatsValue::enchantingPowerMod, *Settings::enchantingPowerMod },
		{ constants::StatsValue::alterationPowerMod, *Settings::alterationPowerMod },
		{ constants::StatsValue::conjurationPowerMod, *Settings::conjurationPowerMod },
		{ constants::StatsValue::destructionPowerMod, *Settings::destructionPowerMod },
		{ constants::StatsValue::illusionPowerMod, *Settings::illusionPowerMod },
		{ constants::StatsValue::restorationPowerMod, *Settings::restorationPowerMod },

		{ constants::StatsValue::speedMult, *Settings::speedMult },
		{ constants::StatsValue::inventoryWeight, *Settings::inventoryWeight },
		{ constants::StatsValue::carryWeight, *Settings::carryWeight },
		{ constants::StatsValue::criticalChance, *Settings::criticalChance },
		{ constants::StatsValue::meleeDamage, *Settings::meleeDamage },
		{ constants::StatsValue::unarmedDamage, *Settings::unarmedDamage },
		{ constants::StatsValue::absorbChance, *Settings::absorbChance },
		{ constants::StatsValue::weaponSpeedMult, *Settings::weaponSpeedMult },
		{ constants::StatsValue::bowSpeedBonus, *Settings::bowSpeedBonus },
		{ constants::StatsValue::shoutRecoveryMult, *Settings::shoutRecoveryMult },
		{ constants::StatsValue::movementNoiseMult, *Settings::movementNoiseMult },
		{ constants::StatsValue::dragonSouls, *Settings::dragonSouls },
		{ constants::StatsValue::combatHealthRegenMultiply, *Settings::combatHealthRegenMultiply },
		{ constants::StatsValue::attackDamageMult, *Settings::attackDamageMult },
		{ constants::StatsValue::beast, *Settings::beast },
		{ constants::StatsValue::xp, *Settings::xp }

	};

	nameMap = {
		{ constants::StatsValue::name, *Settings::nameString },
		{ constants::StatsValue::race, *Settings::raceString },
		{ constants::StatsValue::level, *Settings::levelString },
		{ constants::StatsValue::perkCount, *Settings::perkCountString },
		{ constants::StatsValue::height, *Settings::heightString },
		{ constants::StatsValue::equipedWeight, *Settings::equipedWeightString },
		{ constants::StatsValue::weight, *Settings::weightString },
		{ constants::StatsValue::armor, *Settings::armorString },
		{ constants::StatsValue::damage, *Settings::damageString },
		{ constants::StatsValue::skillTrainingsThisLevel, *Settings::skillTrainingsThisLevelString },
		{ constants::StatsValue::health, *Settings::healthString },

		{ constants::StatsValue::healthRate, *Settings::healthRateString },
		{ constants::StatsValue::healthRateMult, *Settings::healthRateMultString },
		{ constants::StatsValue::magicka, *Settings::magickaString },
		{ constants::StatsValue::magickaRate, *Settings::magickaRateString },
		{ constants::StatsValue::magickaRateMult, *Settings::magickaRateMultString },
		{ constants::StatsValue::stamina, *Settings::staminaString },
		{ constants::StatsValue::staminaRate, *Settings::staminaRateString },
		{ constants::StatsValue::staminaRateMult, *Settings::staminaRateMultString },

		{ constants::StatsValue::resistDamage, *Settings::resistDamageString },
		{ constants::StatsValue::resistDisease, *Settings::resistDiseaseString },
		{ constants::StatsValue::resistPoison, *Settings::resistPoisonString },
		{ constants::StatsValue::resistFire, *Settings::resistFireString },
		{ constants::StatsValue::resistShock, *Settings::resistShockString },
		{ constants::StatsValue::resistFrost, *Settings::resistFrostString },
		{ constants::StatsValue::resistMagic, *Settings::resistMagicString },

		{ constants::StatsValue::oneHanded, *Settings::oneHandedString },
		{ constants::StatsValue::twoHanded, *Settings::twoHandedString },
		{ constants::StatsValue::archery, *Settings::archeryString },
		{ constants::StatsValue::block, *Settings::blockString },
		{ constants::StatsValue::smithing, *Settings::smithingString },
		{ constants::StatsValue::heavyArmor, *Settings::heavyArmorString },
		{ constants::StatsValue::lightArmor, *Settings::lightArmorString },
		{ constants::StatsValue::pickpocket, *Settings::pickpocketString },
		{ constants::StatsValue::lockpicking, *Settings::lockpickingString },
		{ constants::StatsValue::sneak, *Settings::sneakString },
		{ constants::StatsValue::alchemy, *Settings::alchemyString },
		{ constants::StatsValue::speech, *Settings::speechString },
		{ constants::StatsValue::enchanting, *Settings::enchantingString },
		{ constants::StatsValue::alteration, *Settings::alterationString },
		{ constants::StatsValue::conjuration, *Settings::conjurationString },
		{ constants::StatsValue::destruction, *Settings::destructionString },
		{ constants::StatsValue::illusion, *Settings::illusionString },
		{ constants::StatsValue::restoration, *Settings::restorationString },

		{ constants::StatsValue::oneHandedPowerMod, *Settings::oneHandedPowerModString },
		{ constants::StatsValue::twoHandedPowerMod, *Settings::twoHandedPowerModString },
		{ constants::StatsValue::archeryPowerMod, *Settings::archeryPowerModString },
		{ constants::StatsValue::blockPowerMod, *Settings::blockPowerModString },
		{ constants::StatsValue::smithingPowerMod, *Settings::smithingPowerModString },
		{ constants::StatsValue::heavyArmorPowerMod, *Settings::heavyArmorPowerModString },
		{ constants::StatsValue::lightArmorPowerMod, *Settings::lightArmorPowerModString },
		{ constants::StatsValue::pickpocketPowerMod, *Settings::pickpocketPowerModString },
		{ constants::StatsValue::lockpickingPowerMod, *Settings::lockpickingPowerModString },
		{ constants::StatsValue::sneakPowerMod, *Settings::sneakPowerModString },
		{ constants::StatsValue::alchemyPowerMod, *Settings::alchemyPowerModString },
		{ constants::StatsValue::speechPowerMod, *Settings::speechPowerModString },
		{ constants::StatsValue::enchantingPowerMod, *Settings::enchantingPowerModString },
		{ constants::StatsValue::alterationPowerMod, *Settings::alterationPowerModString },
		{ constants::StatsValue::conjurationPowerMod, *Settings::conjurationPowerModString },
		{ constants::StatsValue::destructionPowerMod, *Settings::destructionPowerModString },
		{ constants::StatsValue::illusionPowerMod, *Settings::illusionPowerModString },
		{ constants::StatsValue::restorationPowerMod, *Settings::restorationPowerModString },

		{ constants::StatsValue::speedMult, *Settings::speedMultString },
		{ constants::StatsValue::inventoryWeight, *Settings::inventoryWeightString },
		{ constants::StatsValue::carryWeight, *Settings::carryWeightString },
		{ constants::StatsValue::criticalChance, *Settings::criticalChanceString },
		{ constants::StatsValue::meleeDamage, *Settings::meleeDamageString },
		{ constants::StatsValue::unarmedDamage, *Settings::unarmedDamageString },
		{ constants::StatsValue::absorbChance, *Settings::absorbChanceString },
		{ constants::StatsValue::weaponSpeedMult, *Settings::weaponSpeedMultString },
		{ constants::StatsValue::bowSpeedBonus, *Settings::bowSpeedBonusString },
		{ constants::StatsValue::shoutRecoveryMult, *Settings::shoutRecoveryMultString },
		{ constants::StatsValue::movementNoiseMult, *Settings::movementNoiseMultString },
		{ constants::StatsValue::dragonSouls, *Settings::dragonSoulsString },
		{ constants::StatsValue::combatHealthRegenMultiply, *Settings::combatHealthRegenMultiplyString },
		{ constants::StatsValue::attackDamageMult, *Settings::attackDamageMultString },
		{ constants::StatsValue::beast, *Settings::beastString },
		{ constants::StatsValue::xp, *Settings::xpString }
	};

}

boolean Player::showValue(constants::StatsValue p_val) {
	auto it = showMap.find(p_val);
	if (it != showMap.end()) {
		logger::trace("Show {} {}"sv, getValueName(p_val), it->second);
		return it->second;
	}
	return false;
}

void Player::addToValues(constants::ValueMap& p_map, constants::StatsValue p_key, std::string p_value) {
	if (showValue(p_key)) {
		p_map[p_key] = p_value;
	}
}

std::string Player::getValueName(constants::StatsValue p_val) {
	auto it = nameMap.find(p_val);

	if (it != nameMap.end()) {
		return it->second;
	}
	return constants::undefined;
}

Player::Player() :
	_lock()
{}