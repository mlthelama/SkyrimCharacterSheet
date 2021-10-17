#pragma once

class Champion {
public:
    static Champion* GetSingleton();

    std::string getChampion(FactionValue p_stat);

    void getChampions();

    Champion() = default;
    Champion(const Champion&) = delete;
    Champion(Champion&&) = delete;

    ~Champion() = default;

    Champion& operator=(const Champion&) = delete;
    Champion& operator=(Champion&&) = delete;

private:
    valueStringMap championList;

    void logMap();
};