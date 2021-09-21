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
	//maybe add factions too, someday
	/*playerValues[constants::name] = player->GetName();
	playerValues[constants::race] = player->GetRace()->GetFullName();
	playerValues[constants::level] = std::to_string(player->GetLevel());
	playerValues[constants::perkCount] = std::to_string(player->perkCount);
	playerValues[constants::height] = getStringValueFromFloat(player->GetHeight());
	playerValues[constants::equipedWeight] = getStringValueFromFloat(player->equippedWeight);
	playerValues[constants::weight] = getStringValueFromFloat(player->GetWeight());
	playerValues[constants::armor] = getStringValueFromFloat(player->armorRating);
	playerValues[constants::damage] = getStringValueFromFloat(0); //fix me maybe
	playerValues[constants::skillTrainingsThisLevel] = std::to_string(player->skillTrainingsThisLevel);*/
	//playerValues[constants::defaultClass] = player->defaultClass->GetFullName();

	playerValues[constants::StatsValue::name] = player->GetName();
	playerValues[constants::StatsValue::race] = player->GetRace()->GetFullName();
	playerValues[constants::StatsValue::level] = std::to_string(player->GetLevel());
	playerValues[constants::StatsValue::perkCount] = std::to_string(player->perkCount);
	playerValues[constants::StatsValue::height] = getStringValueFromFloat(player->GetHeight());
	playerValues[constants::StatsValue::equipedWeight] = getStringValueFromFloat(player->equippedWeight);
	playerValues[constants::StatsValue::weight] = getStringValueFromFloat(player->GetWeight());
	playerValues[constants::StatsValue::armor] = getStringValueFromFloat(player->armorRating);
	playerValues[constants::StatsValue::damage] = getStringValueFromFloat(0);  //fix me maybe
	playerValues[constants::StatsValue::skillTrainingsThisLevel] = std::to_string(player->skillTrainingsThisLevel);

	/*
	RE::BGSDefaultObjectManager* defaultObject = RE::BGSDefaultObjectManager::GetSingleton();
	playerValues["test"] = defaultObject->GetObject(RE::DEFAULT_OBJECT::kPlayerIsVampireVariable)->GetName();
	*/
	//add here health, magicka, stamina, skill values, ...
	for (const auto& [key, value] : staticValues) { //std::underlying_type_t<RE::ActorValue>>
		playerValues[key] = getStringValueFromFloat(player->GetActorValue(value));
	}
	PrintValues(playerValues);

	return playerValues;
}

void Player::PrintValues(constants::ValueMap& p_map)
{
	for (const auto& [key, value] : p_map) {
		logger::trace("{} = {}"sv, constants::getName(key), value);
	}
}

std::string Player::getStringValueFromFloat( float x )
{
	return std::to_string(round(x * 100.0) / 100.0);
}

Player::Player() :
	_lock()
{}