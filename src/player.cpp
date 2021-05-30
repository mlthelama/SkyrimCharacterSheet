#include "player.h"

Player* Player::GetSingleton()
{
	static Player singleton;
	return std::addressof(singleton);
}

ValueMap Player::getValues()
{
	return GatherValues();
}

ValueMap Player::GatherValues()
{
	ValueMap playerValues;
	RE::PlayerCharacter* player = RE::PlayerCharacter::GetSingleton();
	//make const
	playerValues["name"] = player->GetName();
	playerValues["health"] = std::to_string(player->GetActorValue(RE::ActorValue::kHealth));
	playerValues["resistFrost"] = std::to_string(player->GetActorValue(RE::ActorValue::kResistFrost));
	PrintValues(playerValues);

	return playerValues;
}

void Player::PrintValues(ValueMap& p_map)
{
	for (const auto& [key, value] : p_map) {
		logger::trace("{} = {}", key, value);
	}
}

Player::Player() :
	_lock()
{}