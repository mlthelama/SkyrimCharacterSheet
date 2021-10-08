#pragma once
#include "stats/statholder.h"

class Filler {
public:
    static Filler* GetSingleton();

    void PrintStatsVector(std::vector<std::shared_ptr<StatItem>>& p_vec);

    std::vector<std::shared_ptr<StatItem>> getData();

    Filler() = default;
    Filler(const Filler&) = delete;
    Filler(Filler&&) = delete;

    ~Filler() = default;

    Filler& operator=(const Filler&) = delete;
    Filler& operator=(Filler&&) = delete;
};