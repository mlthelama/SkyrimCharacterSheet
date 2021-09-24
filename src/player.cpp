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
	//maybe add factions too, someday

	//player->currentProcess->GetEquippedLeftHand()
	//player->currentProcess->GetEquippedRightHand()
	//player

	//player->currentProcess->GetEquippedLeftHand()->
	//logger::trace("")
	//player->skills->data->xp
	//logger::trace("XP {}"sv, std::to_string(player->skills->data->xp));

	//player->GetEquippedEntryData(false) //right hand
	//logger::trace("{}"sv, 
	//player->GetDamage(player->GetEquippedEntryData(false));
	logger::trace("Right Damage {}"sv, std::to_string(player->GetDamage(player->GetEquippedEntryData(false))));
	logger::trace("Left Damage {}"sv, std::to_string(player->GetDamage(player->GetEquippedEntryData(true))));

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
	addToValues(playerValues, Stats::damage, getStringValueFromFloat(0));
	addToValues(playerValues, Stats::skillTrainingsThisLevel, std::to_string(player->skillTrainingsThisLevel));
	/*to do add xp and beast (vampire, werewolf)*/


	addToValues(playerValues, Stats::beast, getBeast(
		player->GetActorValue(RE::ActorValue::kVampirePerks),
		player->GetActorValue(RE::ActorValue::kWerewolfPerks)
	));
	addToValues(playerValues, Stats::xp, "yes");

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
		{ Stats::restorationMod, *Settings::restorationMod }
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

Player::Player() :
	_lock()
{}