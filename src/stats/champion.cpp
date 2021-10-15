#include "stats/champion.h"

auto Champion::GetSingleton() -> Champion* {
    static Champion singleton;
    return std::addressof(singleton);
}

std::string Champion::getChampion(FactionValue p_stat) {
    if (championList.find(p_stat) == championList.end()) {
        return "";
    } else {
        return championList.find(p_stat)->second;
    }
}

void Champion::logMap() {
    for (const auto& item : championList) { logger::trace("champion {}, {}"sv, item.first, item.second); }
}

void Champion::getChampions() {
    for (const auto& item : championMap) {
        logger::trace("working at formid {}"sv, intToHex(item.first));
        auto questStage = RE::TESForm::LookupByID(item.first)->As<RE::TESQuest>()->currentStage;
        auto questDone = false;

        switch (item.second) {
            case FactionValue::malacath:
            case FactionValue::molagBal:
            case FactionValue::nocturnal:
            case FactionValue::sanguine:
            case FactionValue::sheogorath:
            case FactionValue::vaermina:
                if (questStage == 200) {
                    questDone = true;
                }
                break;
            case FactionValue::azura:
            case FactionValue::mehrunesDagon:
            case FactionValue::peryite:
                if (questStage == 100) {
                    questDone = true;
                }
                break;
            case FactionValue::boethiah:
                if (questStage == 50 || questStage == 100) {
                    questDone = true;
                }
                break;
            case FactionValue::clavicusVile:
                if (questStage == 200 || questStage == 205) {
                    questDone = true;
                }
                break;
            case FactionValue::hermaeusMora:
                if (questStage == 100 || questStage == 200) {
                    questDone = true;
                }
                break;
            case FactionValue::hircine:
                if (questStage == 100 || questStage == 105 || questStage == 200) {
                    questDone = true;
                }
                break;
            case FactionValue::mephala:
                if (questStage == 60 || questStage == 80) {
                    questDone = true;
                }
                break;
            case FactionValue::meridia:
                if (questStage == 500) {
                    questDone = true;
                }
                break;
            case FactionValue::namira:
                if (questStage == 100 || questStage == 600) {
                    questDone = true;
                }
                break;
        }

        if (questDone) {
            championList.insert(std::pair<FactionValue, std::string>(item.second, staticDisplayValue));
        }
    }

    logger::trace("got {} items in champion list."sv, championList.size());

    logMap();
}