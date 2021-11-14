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
        for (const auto& thane : _thaneQuestStageMap) {
            auto thaneValue = thane.first;
            for (const auto& formid : thane.second) {
                auto qst = RE::TESForm::LookupByID(formid.first)->As<RE::TESQuest>();
                logger::trace("Thane {] working with formid {}"sv, thaneValue, StringUtil::intToHex(qst));
                auto isThane = false;

                auto qstDone = QuestUtil::isQuestStageComplete(qst, formid.second);

                if (thaneValue == FactionValue::thaneOfEastmarch) {
                    auto eastmarchCWQuest = RE::TESForm::LookupByID(0x00035A23)->As<RE::TESQuest>();
                    auto CWObjectQuest = RE::TESForm::LookupByID(0x00096E71)->As<RE::TESQuest>();
                    auto preQuests = (QuestUtil::isOneQuestStageComplete(eastmarchCWQuest,
                                         std::vector{ QuestUtil::getAs(200), QuestUtil::getAs(255) })) ||
                                     (QuestUtil::isOneQuestStageComplete(CWObjectQuest,
                                         std::vector{ QuestUtil::getAs(9000), QuestUtil::getAs(9999) }));


                    if (preQuests && qstDone) {
                        isThane = true;
                    }
                } else if (thaneValue == FactionValue::thaneOfWhiterun && !*Settings::skyrimUnbound) {
                    auto dragonsRisingQst = RE::TESForm::LookupByID(0x0002610C)->As<RE::TESQuest>();
                    auto CWObjectQst = RE::TESForm::LookupByID(0x00096E71)->As<RE::TESQuest>();
                    auto preQuests = QuestUtil::isOneQuestStageComplete(CWObjectQst,
                        std::vector{ QuestUtil::getAs(9000), QuestUtil::getAs(9999) });
                    auto dragonRising =
                        QuestUtil::isOneQuestStageComplete(dragonsRisingQst, std::vector{ QuestUtil::getAs(160) });

                    if ((dragonRising) || (preQuests && qstDone)) {
                        isThane = true;
                    }
                } else if (qstDone) {
                    isThane = qstDone;
                }

                if (isThane) {
                    logger::trace("Thane of {}"sv, thaneValue);
                    _thaneList.insert(std::pair<FactionValue, std::string>(thaneValue, _constStaticDisplayValue));
                }
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

    static const uint16_t _stage25 = 25;

    inline static std::map<FactionValue, std::map<RE::FormID, uint16_t>> _thaneQuestStageMap = {
        { FactionValue::thaneOfEastmarch, { { 0x000A2CA6, _stage25 } } },
        { FactionValue::thaneOfFalkreath, { { 0x000A34DE, _stage25 } } },
        { FactionValue::thaneOfHaafingar, { { 0x000A2C9B, _stage25 } } },
        { FactionValue::thaneOfHjaalmarch, { { 0x000A34CE, _stage25 } } },
        { FactionValue::thaneOfThePale, { { 0x000A34D4, _stage25 } } },
        { FactionValue::thaneOfTheReach, { { 0x000A2C86, _stage25 } } },
        { FactionValue::thaneOfTheRift, { { 0x00065BDF, QuestUtil::getAs(20) } } },  //rift quest is special
        { FactionValue::thaneOfWhiterun,
            { { 0x000A2C9E, _stage25 } } },  //just if stormcloaks won the war, otherwise MQ104/0002610C/160
        { FactionValue::thaneOfWinterhold, { { 0x000A34D7, _stage25 } } }
    };

    void logMap() {
        for (const auto& item : _thaneList) { logger::trace("thane {}, {}"sv, item.first, item.second); }
    }
};
