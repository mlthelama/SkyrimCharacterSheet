#pragma once

class Thane {
public:
    static Thane* GetSingleton() {
        static Thane singleton;
        return std::addressof(singleton);
    }

    std::string getThane(FactionValue p_stat) {
        if (thaneList.find(p_stat) == thaneList.end()) {
            return "";
        } else {
            return thaneList.find(p_stat)->second;
        }
    }

    void getRegionThanes() {
        for (const auto& item : thaneMap) {
            logger::trace("working at formid {}"sv, intToHex(item.first));
            auto questStage = RE::TESForm::LookupByID(item.first)->As<RE::TESQuest>()->currentStage;

            if (questStage == 200) {
                thaneList.insert(std::pair<FactionValue, std::string>(item.second, staticDisplayValue));
            } else if (item.second == FactionValue::thaneOfWhiterun) {
                auto whiterunQuestStage = RE::TESForm::LookupByID(0x0002610C)->As<RE::TESQuest>()->currentStage;
                if (whiterunQuestStage == 200) {
                    thaneList.insert(std::pair<FactionValue, std::string>(item.second, staticDisplayValue));
                }
            }
        }

        logger::trace("got {} items in thane list."sv, thaneList.size());
        logMap();
    }

    Thane() = default;
    Thane(const Thane&) = delete;
    Thane(Thane&&) = delete;

    ~Thane() = default;

    Thane& operator=(const Thane&) = delete;
    Thane& operator=(Thane&&) = delete;

private:
    valueStringMap thaneList;

    void logMap() {
        for (const auto& item : thaneList) { logger::trace("thane {}, {}"sv, item.first, item.second); }
    }
};
