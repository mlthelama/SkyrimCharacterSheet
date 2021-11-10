#pragma once

class Thane {
public:
    static Thane* GetSingleton() {
        static Thane singleton;
        return std::addressof(singleton);
    }

    std::string getThane(FactionValue a_stat) {
        if (_thaneList.find(a_stat) == _thaneList.end()) {
            return "";
        } else {
            return _thaneList.find(a_stat)->second;
        }
    }

    void getRegionThanes() {
        for (const auto& item : _constThaneMap) {
            logger::trace("working at formid {}"sv, intToHex(item.first));
            auto questStage = RE::TESForm::LookupByID(item.first)->As<RE::TESQuest>()->currentStage;
            auto isThane = false;

            //handle whiterun and eastmarch differently because of cw and main quest specials
            if (item.second == FactionValue::thaneOfEastmarch) {
                auto eastmarchCWstage = RE::TESForm::LookupByID(0x00035A23)->As<RE::TESQuest>()->currentStage;
                auto CWObjectStage = RE::TESForm::LookupByID(0x00096E71)->As<RE::TESQuest>()->currentStage;
                auto preQuests = (eastmarchCWstage == 200 || eastmarchCWstage == 255) ||
                                 (CWObjectStage == 9000 || CWObjectStage == 9999);
                if (preQuests && questStage == 200) {
                    isThane = true;
                }
            } else if (item.second == FactionValue::thaneOfWhiterun && !*Settings::skyrimUnbound) {
                auto dragonsRisingStage = RE::TESForm::LookupByID(0x0002610C)->As<RE::TESQuest>()->currentStage;
                auto CWObjectStage = RE::TESForm::LookupByID(0x00096E71)->As<RE::TESQuest>()->currentStage;
                auto preQuests = (CWObjectStage == 9000 || CWObjectStage == 9999);
                if ((dragonsRisingStage >= 160) || (preQuests && questStage == 200)) {
                    isThane = true;
                }
            } else if (questStage == 200) {
                isThane = true;
            }

            if (isThane) {
                _thaneList.insert(std::pair<FactionValue, std::string>(item.second, _constStaticDisplayValue));
            }
        }

        logger::trace("got {} items in thane list."sv, _thaneList.size());
        logMap();
    }

    Thane() = default;
    Thane(const Thane&) = delete;
    Thane(Thane&&) = delete;

    ~Thane() = default;

    Thane& operator=(const Thane&) = delete;
    Thane& operator=(Thane&&) = delete;

private:
    valueStringMap _thaneList;

    void logMap() {
        for (const auto& item : _thaneList) { logger::trace("thane {}, {}"sv, item.first, item.second); }
    }
};
