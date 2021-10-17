#pragma once
#include "stats/factionholder.h"

class FactionFiller {
public:
    static FactionFiller* GetSingleton();

    std::vector<std::shared_ptr<FactionItem>> getData();

    void PrintFactionVector(std::vector<std::shared_ptr<FactionItem>>& p_vec);

    FactionFiller() = default;
    FactionFiller(const FactionFiller&) = delete;
    FactionFiller(FactionFiller&&) = delete;

    ~FactionFiller() = default;

    FactionFiller& operator=(const FactionFiller&) = delete;
    FactionFiller& operator=(FactionFiller&&) = delete;
};