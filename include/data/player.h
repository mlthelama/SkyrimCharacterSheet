#pragma once
#include "stats/statholder.h"

class Player {
public:
    static Player* GetSingleton();

    std::vector<std::shared_ptr<StatItem>> getPlayerValues();

private:
    std::map<StatsValue, std::string> factionRankMap;

    std::string getBeast(float p_vamp, float p_were);

    std::string getArrowDamage(RE::PlayerCharacter*& p_player);

    std::string getDamage(RE::PlayerCharacter*& p_player, boolean p_left);

    std::string handleWeaponSpeed(RE::PlayerCharacter*& p_player, boolean p_left);

    std::string getXP(RE::PlayerCharacter*& p_player);

    Player() = default;
    Player(const Player&) = delete;
    Player(Player&&) = delete;

    ~Player() = default;

    Player& operator=(const Player&) = delete;
    Player& operator=(Player&&) = delete;
};