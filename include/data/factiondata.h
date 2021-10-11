#pragma once
#include "stats/factionholder.h"

class FactionData {
public:
    static FactionData* GetSingleton();
    
    std::vector<std::shared_ptr<FactionItem>> getFactionValues();

private:
    FactionData() = default;
    FactionData(const FactionData&) = delete;
    FactionData(FactionData&&) = delete;

    ~FactionData() = default;

    FactionData& operator=(const FactionData&) = delete;
    FactionData& operator=(FactionData&&) = delete;
};