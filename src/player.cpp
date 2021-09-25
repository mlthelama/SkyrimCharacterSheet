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

constants::ValueMap Player::GatherValues() {
	logger::trace("Gather Values to Show ..."sv);

	constants::ValueMap playerValues;
	RE::PlayerCharacter* player = RE::PlayerCharacter::GetSingleton();
	loadSettings();

	if (player->GetEquippedEntryData(false)->GetObject()->GetFormType() == RE::FormType::Ammo) {
		logger::trace("Item {} is arrow"sv, player->GetEquippedEntryData(false)->GetDisplayName());
		addToValues(playerValues, Stats::damageArrow, getStringValueFromFloat(
			player->GetDamage(player->GetEquippedEntryData(false)))
		);
	}

	//auto test = player->currentProcess->processLevel;
	rightHand = player->currentProcess->middleHigh->rightHand;
	leftHand = player->currentProcess->middleHigh->leftHand;

	leftDamage = 0;
	rightDamage = 0;
	if (rightHand != nullptr) {
		rightDamage = player->GetDamage(rightHand);
		logger::trace("Right Name {}, Right Weapon Damage {}"sv, rightHand->GetDisplayName(), rightDamage);
		rightFormID = rightHand->GetObject()->GetFormID();
	}
	if (leftHand != nullptr) {
		leftDamage = player->GetDamage(leftHand);
		logger::trace("Left Name {}, Left Weapon Damage {}"sv, leftHand->GetDisplayName(), leftDamage);
		leftFormID = leftHand->GetObject()->GetFormID();
	}

	/*currently not working if both hands have the same weapon, should be fixed*/
	if (rightFormID != 0 && leftFormID == 0) {
		addToValues(playerValues, Stats::damage, getStringValueFromFloat(rightDamage));
	} else if ((rightFormID != leftFormID) || (rightFormID == leftFormID)) {
		addToValues(playerValues, Stats::damageRight, getStringValueFromFloat(rightDamage));
		if (leftDamage != 0) {
			addToValues(playerValues, Stats::damageLeft, getStringValueFromFloat(leftDamage));
		}
	}

	//maybe add factions too, someday
	//const auto thiefGuild = RE::TESForm::LookupByID<RE::TESFaction>(formid)
	/*
	for (const auto& [faction, v2] : player->factionOwnerFriendsMap) {
		//logger::trace("faction name full {}, playable {}, objectName {}"sv, faction->GetFullName(), faction->GetPlayable(), faction->GetObjectTypeName());
		if (player->IsInFaction(faction)) {
			logger::trace("faction name full {}, playable {}, objectName {}"sv, faction->GetFullName(), faction->GetPlayable(), faction->GetObjectTypeName());
			auto rankData = faction->rankData;
			for (auto it = rankData.begin(); it != rankData.end(); ++it) {
				//auto i = std::distance(rankData.begin(), it);
				auto i = *it;
				logger::trace("rank {}"sv, i->femaleRankTitle);
			}
		}
	}*/

	addToValues(playerValues, Stats::name, player->GetName());
	addToValues(playerValues, Stats::race, player->GetRace()->GetFullName());
	addToValues(playerValues, Stats::level, std::to_string(player->GetLevel()));
	addToValues(playerValues, Stats::perkCount, std::to_string(player->perkCount));
	addToValues(playerValues, Stats::height, getStringValueFromFloat(player->GetHeight()));
	addToValues(playerValues, Stats::equipedWeight, getStringValueFromFloat(player->GetWeight()));
	addToValues(playerValues, Stats::armor, getStringValueFromFloat(player->armorRating));
	addToValues(playerValues, Stats::skillTrainingsThisLevel, std::to_string(player->skillTrainingsThisLevel));

	addToValues(playerValues, Stats::beast, getBeast(
		player->GetActorValue(RE::ActorValue::kVampirePerks),
		player->GetActorValue(RE::ActorValue::kWerewolfPerks)
	));
	/*todo fix*/
	addToValues(playerValues, Stats::xp, "");

	addToValues(playerValues, Stats::healthRatePer, getStringValueFromFloat(
		calculateValue(player->GetActorValue(RE::ActorValue::kHealRateMult), 
			player->GetActorValue(RE::ActorValue::kHealRate)
		))
	);
	addToValues(playerValues, Stats::magickaRatePer, getStringValueFromFloat(
		calculateValue(player->GetActorValue(RE::ActorValue::kMagickaRateMult), 
			player->GetActorValue(RE::ActorValue::kMagickaRate)
		))
	);
	addToValues(playerValues, Stats::staminaRatePer, getStringValueFromFloat(
		calculateValue(player->GetActorValue(RE::ActorValue::kStaminaRateMult), 
			player->GetActorValue(RE::ActorValue::KStaminaRate)
		))
	);
	addToValues(playerValues, Stats::movementNoiseMult, getStringValueFromFloat(
		player->GetActorValue(RE::ActorValue::kMovementNoiseMult) * 100
	));

	//add here health, magicka, stamina, skill values, ...
	/* maybe add advance for skills as well = xp*/
	for (const auto& [key, value] : staticValues) {
		if (showValue(key)) {
			playerValues[key] = getStringValueFromFloat(player->GetActorValue(value));
		}
	}
	PrintValues(playerValues);

	return playerValues;
}

void Player::PrintValues(constants::ValueMap& p_map) {
	for (const auto& [key, value] : p_map) {
		logger::trace("{} = {}"sv, getValueName(key), value);
	}
}

std::string Player::getStringValueFromFloat( float x ) {
	return std::to_string(round(x * 100.0) / 100.0);
}

void Player::loadSettings() {
	showMap = {
		{ Stats::name, *Settings::name },
		{ Stats::race, *Settings::race },
		{ Stats::level, *Settings::level },
		{ Stats::perkCount, *Settings::perkCount },
		{ Stats::height, *Settings::height },
		{ Stats::equipedWeight, *Settings::equipedWeight },
		{ Stats::weight, *Settings::weight },
		{ Stats::armor, *Settings::armor },
		{ Stats::damage, *Settings::damage },
		{ Stats::skillTrainingsThisLevel, *Settings::skillTrainingsThisLevel },
		{ Stats::health, *Settings::health },

		{ Stats::healthRatePer, *Settings::healthRate },
		{ Stats::magicka, *Settings::magicka },
		{ Stats::magickaRatePer, *Settings::magickaRate },
		{ Stats::stamina, *Settings::stamina },
		{ Stats::staminaRatePer, *Settings::staminaRate },

		{ Stats::resistDamage, *Settings::resistDamage },
		{ Stats::resistDisease, *Settings::resistDisease },
		{ Stats::resistPoison, *Settings::resistPoison },
		{ Stats::resistFire, *Settings::resistFire },
		{ Stats::resistShock, *Settings::resistShock },
		{ Stats::resistFrost, *Settings::resistFrost },
		{ Stats::resistMagic, *Settings::resistMagic },

		{ Stats::oneHanded, *Settings::oneHanded },
		{ Stats::twoHanded, *Settings::twoHanded },
		{ Stats::archery, *Settings::archery },
		{ Stats::block, *Settings::block },
		{ Stats::smithing, *Settings::smithing },
		{ Stats::heavyArmor, *Settings::heavyArmor },
		{ Stats::lightArmor, *Settings::lightArmor },
		{ Stats::pickpocket, *Settings::pickpocket },
		{ Stats::lockpicking, *Settings::lockpicking },
		{ Stats::sneak, *Settings::sneak },
		{ Stats::alchemy, *Settings::alchemy },
		{ Stats::speech, *Settings::speech },
		{ Stats::enchanting, *Settings::enchanting },
		{ Stats::alteration, *Settings::alteration },
		{ Stats::conjuration, *Settings::conjuration },
		{ Stats::destruction, *Settings::destruction },
		{ Stats::illusion, *Settings::illusion },
		{ Stats::restoration, *Settings::restoration },

		{ Stats::oneHandedPowerMod, *Settings::oneHandedPowerMod },
		{ Stats::twoHandedPowerMod, *Settings::twoHandedPowerMod },
		{ Stats::archeryPowerMod, *Settings::archeryPowerMod },
		{ Stats::blockPowerMod, *Settings::blockPowerMod },
		{ Stats::smithingPowerMod, *Settings::smithingPowerMod },
		{ Stats::heavyArmorPowerMod, *Settings::heavyArmorPowerMod },
		{ Stats::lightArmorPowerMod, *Settings::lightArmorPowerMod },
		{ Stats::pickpocketPowerMod, *Settings::pickpocketPowerMod },
		{ Stats::lockpickingPowerMod, *Settings::lockpickingPowerMod },
		{ Stats::sneakPowerMod, *Settings::sneakPowerMod },
		{ Stats::alchemyPowerMod, *Settings::alchemyPowerMod },
		{ Stats::speechPowerMod, *Settings::speechPowerMod },
		{ Stats::enchantingPowerMod, *Settings::enchantingPowerMod },
		{ Stats::alterationPowerMod, *Settings::alterationPowerMod },
		{ Stats::conjurationPowerMod, *Settings::conjurationPowerMod },
		{ Stats::destructionPowerMod, *Settings::destructionPowerMod },
		{ Stats::illusionPowerMod, *Settings::illusionPowerMod },
		{ Stats::restorationPowerMod, *Settings::restorationPowerMod },

		{ Stats::speedMult, *Settings::speedMult },
		{ Stats::inventoryWeight, *Settings::inventoryWeight },
		{ Stats::carryWeight, *Settings::carryWeight },
		{ Stats::criticalChance, *Settings::criticalChance },
		{ Stats::meleeDamage, *Settings::meleeDamage },
		{ Stats::unarmedDamage, *Settings::unarmedDamage },
		{ Stats::absorbChance, *Settings::absorbChance },
		{ Stats::weaponSpeedMult, *Settings::weaponSpeedMult },
		{ Stats::bowSpeedBonus, *Settings::bowSpeedBonus },
		{ Stats::shoutRecoveryMult, *Settings::shoutRecoveryMult },
		{ Stats::movementNoiseMult, *Settings::movementNoiseMult },
		{ Stats::dragonSouls, *Settings::dragonSouls },
		{ Stats::combatHealthRegenMultiply, *Settings::combatHealthRegenMultiply },
		{ Stats::attackDamageMult, *Settings::attackDamageMult },
		{ Stats::beast, *Settings::beast },
		{ Stats::xp, *Settings::xp },

		{ Stats::reflectDamage, *Settings::reflectDamage },
		{ Stats::oneHandedMod, *Settings::oneHandedMod },
		{ Stats::twoHandedMod, *Settings::twoHandedMod },
		{ Stats::marksmanMod, *Settings::archeryMod },
		{ Stats::blockMod, *Settings::blockMod },
		{ Stats::smithingMod, *Settings::smithingMod },
		{ Stats::heavyArmorMod, *Settings::heavyArmorMod },
		{ Stats::lightArmorMod, *Settings::lightArmorMod },
		{ Stats::pickpocketMod, *Settings::pickpocketMod },
		{ Stats::lockpickingMod, *Settings::lockpickingMod },
		{ Stats::sneakingMod, *Settings::sneakMod },
		{ Stats::alchemyMod, *Settings::alchemyMod },
		{ Stats::speechcraftMod, *Settings::speechMod },
		{ Stats::enchantingMod, *Settings::enchantingMod },
		{ Stats::alterationMod, *Settings::alterationMod },
		{ Stats::conjurationMod, *Settings::conjurationMod },
		{ Stats::destructionMod, *Settings::destructionMod },
		{ Stats::illusionMod, *Settings::illusionMod },
		{ Stats::restorationMod, *Settings::restorationMod },

		{ Stats::damageArrow, *Settings::damageArrow },
		{ Stats::damageRight, *Settings::damageRight },
		{ Stats::damageLeft, *Settings::damageLeft }
	};

	nameMap = {
		{ Stats::name, *Settings::nameString },
		{ Stats::race, *Settings::raceString },
		{ Stats::level, *Settings::levelString },
		{ Stats::perkCount, *Settings::perkCountString },
		{ Stats::height, *Settings::heightString },
		{ Stats::equipedWeight, *Settings::equipedWeightString },
		{ Stats::weight, *Settings::weightString },
		{ Stats::armor, *Settings::armorString },
		{ Stats::damage, *Settings::damageString },
		{ Stats::skillTrainingsThisLevel, *Settings::skillTrainingsThisLevelString },
		{ Stats::health, *Settings::healthString },

		{ Stats::healthRatePer, *Settings::healthRateString },
		{ Stats::magicka, *Settings::magickaString },
		{ Stats::magickaRatePer, *Settings::magickaRateString },
		{ Stats::stamina, *Settings::staminaString },
		{ Stats::staminaRatePer, *Settings::staminaRateString },

		{ Stats::resistDamage, *Settings::resistDamageString },
		{ Stats::resistDisease, *Settings::resistDiseaseString },
		{ Stats::resistPoison, *Settings::resistPoisonString },
		{ Stats::resistFire, *Settings::resistFireString },
		{ Stats::resistShock, *Settings::resistShockString },
		{ Stats::resistFrost, *Settings::resistFrostString },
		{ Stats::resistMagic, *Settings::resistMagicString },

		{ Stats::oneHanded, *Settings::oneHandedString },
		{ Stats::twoHanded, *Settings::twoHandedString },
		{ Stats::archery, *Settings::archeryString },
		{ Stats::block, *Settings::blockString },
		{ Stats::smithing, *Settings::smithingString },
		{ Stats::heavyArmor, *Settings::heavyArmorString },
		{ Stats::lightArmor, *Settings::lightArmorString },
		{ Stats::pickpocket, *Settings::pickpocketString },
		{ Stats::lockpicking, *Settings::lockpickingString },
		{ Stats::sneak, *Settings::sneakString },
		{ Stats::alchemy, *Settings::alchemyString },
		{ Stats::speech, *Settings::speechString },
		{ Stats::enchanting, *Settings::enchantingString },
		{ Stats::alteration, *Settings::alterationString },
		{ Stats::conjuration, *Settings::conjurationString },
		{ Stats::destruction, *Settings::destructionString },
		{ Stats::illusion, *Settings::illusionString },
		{ Stats::restoration, *Settings::restorationString },

		{ Stats::oneHandedPowerMod, *Settings::oneHandedPowerModString },
		{ Stats::twoHandedPowerMod, *Settings::twoHandedPowerModString },
		{ Stats::archeryPowerMod, *Settings::archeryPowerModString },
		{ Stats::blockPowerMod, *Settings::blockPowerModString },
		{ Stats::smithingPowerMod, *Settings::smithingPowerModString },
		{ Stats::heavyArmorPowerMod, *Settings::heavyArmorPowerModString },
		{ Stats::lightArmorPowerMod, *Settings::lightArmorPowerModString },
		{ Stats::pickpocketPowerMod, *Settings::pickpocketPowerModString },
		{ Stats::lockpickingPowerMod, *Settings::lockpickingPowerModString },
		{ Stats::sneakPowerMod, *Settings::sneakPowerModString },
		{ Stats::alchemyPowerMod, *Settings::alchemyPowerModString },
		{ Stats::speechPowerMod, *Settings::speechPowerModString },
		{ Stats::enchantingPowerMod, *Settings::enchantingPowerModString },
		{ Stats::alterationPowerMod, *Settings::alterationPowerModString },
		{ Stats::conjurationPowerMod, *Settings::conjurationPowerModString },
		{ Stats::destructionPowerMod, *Settings::destructionPowerModString },
		{ Stats::illusionPowerMod, *Settings::illusionPowerModString },
		{ Stats::restorationPowerMod, *Settings::restorationPowerModString },

		{ Stats::speedMult, *Settings::speedMultString },
		{ Stats::inventoryWeight, *Settings::inventoryWeightString },
		{ Stats::carryWeight, *Settings::carryWeightString },
		{ Stats::criticalChance, *Settings::criticalChanceString },
		{ Stats::meleeDamage, *Settings::meleeDamageString },
		{ Stats::unarmedDamage, *Settings::unarmedDamageString },
		{ Stats::absorbChance, *Settings::absorbChanceString },
		{ Stats::weaponSpeedMult, *Settings::weaponSpeedMultString },
		{ Stats::bowSpeedBonus, *Settings::bowSpeedBonusString },
		{ Stats::shoutRecoveryMult, *Settings::shoutRecoveryMultString },
		{ Stats::movementNoiseMult, *Settings::movementNoiseMultString },
		{ Stats::dragonSouls, *Settings::dragonSoulsString },
		{ Stats::combatHealthRegenMultiply, *Settings::combatHealthRegenMultiplyString },
		{ Stats::attackDamageMult, *Settings::attackDamageMultString },
		{ Stats::beast, *Settings::beastString },
		{ Stats::xp, *Settings::xpString },

		{ Stats::reflectDamage, *Settings::reflectDamageString },
		{ Stats::oneHandedMod, *Settings::oneHandedModString },
		{ Stats::twoHandedMod, *Settings::twoHandedModString },
		{ Stats::marksmanMod, *Settings::archeryModString },
		{ Stats::blockMod, *Settings::blockModString },
		{ Stats::smithingMod, *Settings::smithingModString },
		{ Stats::heavyArmorMod, *Settings::heavyArmorModString },
		{ Stats::lightArmorMod, *Settings::lightArmorModString },
		{ Stats::pickpocketMod, *Settings::pickpocketModString },
		{ Stats::lockpickingMod, *Settings::lockpickingModString },
		{ Stats::sneakingMod, *Settings::sneakModString },
		{ Stats::alchemyMod, *Settings::alchemyModString },
		{ Stats::speechcraftMod, *Settings::speechModString },
		{ Stats::enchantingMod, *Settings::enchantingModString },
		{ Stats::alterationMod, *Settings::alterationModString },
		{ Stats::conjurationMod, *Settings::conjurationModString },
		{ Stats::destructionMod, *Settings::destructionModString },
		{ Stats::illusionMod, *Settings::illusionModString },
		{ Stats::restorationMod, *Settings::restorationModString },

		{ Stats::damageArrow, *Settings::damageArrowString },
		{ Stats::damageRight, *Settings::damageRightString },
		{ Stats::damageLeft, *Settings::damageLeftString }
	};

	nameEndingMap = {
		{ Stats::name, *Settings::nameStringEnding },
		{ Stats::race, *Settings::raceStringEnding },
		{ Stats::level, *Settings::levelStringEnding },
		{ Stats::perkCount, *Settings::perkCountStringEnding },
		{ Stats::height, *Settings::heightStringEnding },
		{ Stats::equipedWeight, *Settings::equipedWeightStringEnding },
		{ Stats::weight, *Settings::weightStringEnding },
		{ Stats::armor, *Settings::armorStringEnding },
		{ Stats::damage, *Settings::damageStringEnding },
		{ Stats::skillTrainingsThisLevel, *Settings::skillTrainingsThisLevelStringEnding },
		{ Stats::health, *Settings::healthStringEnding },

		{ Stats::healthRatePer, *Settings::healthRateStringEnding },
		{ Stats::magicka, *Settings::magickaStringEnding },
		{ Stats::magickaRatePer, *Settings::magickaRateStringEnding },
		{ Stats::stamina, *Settings::staminaStringEnding },
		{ Stats::staminaRatePer, *Settings::staminaRateStringEnding },

		{ Stats::resistDamage, *Settings::resistDamageStringEnding },
		{ Stats::resistDisease, *Settings::resistDiseaseStringEnding },
		{ Stats::resistPoison, *Settings::resistPoisonStringEnding },
		{ Stats::resistFire, *Settings::resistFireStringEnding },
		{ Stats::resistShock, *Settings::resistShockStringEnding },
		{ Stats::resistFrost, *Settings::resistFrostStringEnding },
		{ Stats::resistMagic, *Settings::resistMagicStringEnding },

		{ Stats::oneHanded, *Settings::oneHandedStringEnding },
		{ Stats::twoHanded, *Settings::twoHandedStringEnding },
		{ Stats::archery, *Settings::archeryStringEnding },
		{ Stats::block, *Settings::blockStringEnding },
		{ Stats::smithing, *Settings::smithingStringEnding },
		{ Stats::heavyArmor, *Settings::heavyArmorStringEnding },
		{ Stats::lightArmor, *Settings::lightArmorStringEnding },
		{ Stats::pickpocket, *Settings::pickpocketStringEnding },
		{ Stats::lockpicking, *Settings::lockpickingStringEnding },
		{ Stats::sneak, *Settings::sneakStringEnding },
		{ Stats::alchemy, *Settings::alchemyStringEnding },
		{ Stats::speech, *Settings::speechStringEnding },
		{ Stats::enchanting, *Settings::enchantingStringEnding },
		{ Stats::alteration, *Settings::alterationStringEnding },
		{ Stats::conjuration, *Settings::conjurationStringEnding },
		{ Stats::destruction, *Settings::destructionStringEnding },
		{ Stats::illusion, *Settings::illusionStringEnding },
		{ Stats::restoration, *Settings::restorationStringEnding },

		{ Stats::oneHandedPowerMod, *Settings::oneHandedPowerModStringEnding },
		{ Stats::twoHandedPowerMod, *Settings::twoHandedPowerModStringEnding },
		{ Stats::archeryPowerMod, *Settings::archeryPowerModStringEnding },
		{ Stats::blockPowerMod, *Settings::blockPowerModStringEnding },
		{ Stats::smithingPowerMod, *Settings::smithingPowerModStringEnding },
		{ Stats::heavyArmorPowerMod, *Settings::heavyArmorPowerModStringEnding },
		{ Stats::lightArmorPowerMod, *Settings::lightArmorPowerModStringEnding },
		{ Stats::pickpocketPowerMod, *Settings::pickpocketPowerModStringEnding },
		{ Stats::lockpickingPowerMod, *Settings::lockpickingPowerModStringEnding },
		{ Stats::sneakPowerMod, *Settings::sneakPowerModStringEnding },
		{ Stats::alchemyPowerMod, *Settings::alchemyPowerModStringEnding },
		{ Stats::speechPowerMod, *Settings::speechPowerModStringEnding },
		{ Stats::enchantingPowerMod, *Settings::enchantingPowerModStringEnding },
		{ Stats::alterationPowerMod, *Settings::alterationPowerModStringEnding },
		{ Stats::conjurationPowerMod, *Settings::conjurationPowerModStringEnding },
		{ Stats::destructionPowerMod, *Settings::destructionPowerModStringEnding },
		{ Stats::illusionPowerMod, *Settings::illusionPowerModStringEnding },
		{ Stats::restorationPowerMod, *Settings::restorationPowerModStringEnding },

		{ Stats::speedMult, *Settings::speedMultStringEnding },
		{ Stats::inventoryWeight, *Settings::inventoryWeightStringEnding },
		{ Stats::carryWeight, *Settings::carryWeightStringEnding },
		{ Stats::criticalChance, *Settings::criticalChanceStringEnding },
		{ Stats::meleeDamage, *Settings::meleeDamageStringEnding },
		{ Stats::unarmedDamage, *Settings::unarmedDamageStringEnding },
		{ Stats::absorbChance, *Settings::absorbChanceStringEnding },
		{ Stats::weaponSpeedMult, *Settings::weaponSpeedMultStringEnding },
		{ Stats::bowSpeedBonus, *Settings::bowSpeedBonusStringEnding },
		{ Stats::shoutRecoveryMult, *Settings::shoutRecoveryMultStringEnding },
		{ Stats::movementNoiseMult, *Settings::movementNoiseMultStringEnding },
		{ Stats::dragonSouls, *Settings::dragonSoulsStringEnding },
		{ Stats::combatHealthRegenMultiply, *Settings::combatHealthRegenMultiplyStringEnding },
		{ Stats::attackDamageMult, *Settings::attackDamageMultStringEnding },
		{ Stats::beast, *Settings::beastStringEnding },
		{ Stats::xp, *Settings::xpStringEnding },

		{ Stats::reflectDamage, *Settings::reflectDamageStringEnding },
		{ Stats::oneHandedMod, *Settings::oneHandedModStringEnding },
		{ Stats::twoHandedMod, *Settings::twoHandedModStringEnding },
		{ Stats::marksmanMod, *Settings::archeryModStringEnding },
		{ Stats::blockMod, *Settings::blockModStringEnding },
		{ Stats::smithingMod, *Settings::smithingModStringEnding },
		{ Stats::heavyArmorMod, *Settings::heavyArmorModStringEnding },
		{ Stats::lightArmorMod, *Settings::lightArmorModStringEnding },
		{ Stats::pickpocketMod, *Settings::pickpocketModStringEnding },
		{ Stats::lockpickingMod, *Settings::lockpickingModStringEnding },
		{ Stats::sneakingMod, *Settings::sneakModStringEnding },
		{ Stats::alchemyMod, *Settings::alchemyModStringEnding },
		{ Stats::speechcraftMod, *Settings::speechModStringEnding },
		{ Stats::enchantingMod, *Settings::enchantingModStringEnding },
		{ Stats::alterationMod, *Settings::alterationModStringEnding },
		{ Stats::conjurationMod, *Settings::conjurationModStringEnding },
		{ Stats::destructionMod, *Settings::destructionModStringEnding },
		{ Stats::illusionMod, *Settings::illusionModStringEnding },
		{ Stats::restorationMod, *Settings::restorationModStringEnding },

		{ Stats::damageArrow, *Settings::damageArrowStringEnding },
		{ Stats::damageRight, *Settings::damageRightStringEnding },
		{ Stats::damageLeft, *Settings::damageLeftStringEnding }
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

float Player::calculateValue(float p_rm, float p_r) {
	return (p_rm * p_r) /100;
}

std::string Player::getBeast(float p_vamp, float p_were) {
	if (p_vamp > 0) {
		return *Settings::vampireString;
	} else if (p_were > 0) {
		return *Settings::werewolfString;
	}
	return "";
}

std::string Player::getValueEnding(constants::StatsValue p_val) {
	auto it = nameEndingMap.find(p_val);

	if (it != nameEndingMap.end()) {
		return it->second;
	}
	return constants::undefined;
}

Player::Player() :
	_lock()
{}