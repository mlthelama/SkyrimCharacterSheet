#pragma once

class Faction {
public:
    static Faction* GetSingleton();

    std::string getRank(StatsValue p_stat);

    void getFactions(RE::Actor* a_actor);


    Faction() = default;
    Faction(const Faction&) = delete;
    Faction(Faction&&) = delete;

    ~Faction() = default;

    Faction& operator=(const Faction&) = delete;
    Faction& operator=(Faction&&) = delete;

private:
    valueStringMap factionRankList;

    void logMap();

    std::string getDarkBrotherhoodRank();

    std::string getGraybeardRank();

    std::string getImperialLegionRank();

    std::string getStormcloaksRank();

    std::string getVolkiharVampireClanRank();

    std::string getDawnguardRank();

    std::string getHouseTelvanniRank();
};