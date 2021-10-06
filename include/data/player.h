#pragma once
#include "constants.h"
#include "stats/statholder.h"

class Player
{
public:
	static Player* GetSingleton();

	const vector<StatItem> getPlayerValues();

private:
	//using Stats = constants::StatsValue;

	map<StatsValue, string> factionRankMap;

	string getBeast(float p_vamp, float p_were);

	string getArrowDamage(RE::PlayerCharacter* &p_player);

	string getDamage(RE::PlayerCharacter* &p_player, boolean p_left);

	string handleWeaponSpeed(RE::PlayerCharacter* &p_player, boolean p_left);

	string getXP(RE::PlayerCharacter*& p_player);

	Player() = default;
	Player(const Player&) = delete;
	Player(Player&&) = delete;

	~Player() = default;

	Player& operator=(const Player&) = delete;
	Player& operator=(Player&&) = delete;
};