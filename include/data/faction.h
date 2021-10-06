#pragma once
#include "constants.h"

class Faction{
	typedef map<StatsValue, string> factionRankMap;

public:
	static Faction* GetSingleton();

	string getRank(StatsValue p_stat);

	void getFactions(RE::Actor* a_actor);


	Faction() = default;
	Faction(const Faction&) = delete;
	Faction(Faction&&) = delete;

	~Faction() = default;

	Faction& operator=(const Faction&) = delete;
	Faction& operator=(Faction&&) = delete;
private:
	factionRankMap factionRankList;

	void logMap();

	string getDarkBrotherhoodRank();

	string getGraybeardRank();

	string getImperialLegionRank();

	string getStormcloaksRank();

	string getVolkiharVampireClanRank();

	string getDawnguardRank();

	string getHouseTelvanniRank();
};