#pragma once
#include "stats/statholder.h"

class StatFiller {
public:
    static StatFiller* GetSingleton();

    std::vector<std::shared_ptr<StatItem>> getData();

    void PrintStatsVector(std::vector<std::shared_ptr<StatItem>>& p_vec);

    StatFiller() = default;
    StatFiller(const StatFiller&) = delete;
    StatFiller(StatFiller&&) = delete;

    ~StatFiller() = default;

    StatFiller& operator=(const StatFiller&) = delete;
    StatFiller& operator=(StatFiller&&) = delete;
};