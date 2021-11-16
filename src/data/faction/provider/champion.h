#pragma once

class Champion {
    using valueStringMap = std::map<FactionValue, std::string>;

public:
    static Champion* GetSingleton() {
        static Champion singleton;
        return std::addressof(singleton);
    }

    std::string getChampion(FactionValue a_stat) {
        if (_championList.find(a_stat) == _championList.end()) {
            return "";
        } else {
            return _championList.find(a_stat)->second;
        }
    }

    void getChampions() {
        _championList.clear();
        for (const auto& champion : _championQuestStageMap) {
            auto championValue = champion.first;
            for (const auto& formid : champion.second) {
                auto qst = RE::TESForm::LookupByID(formid.first)->As<RE::TESQuest>();
                logger::trace("Champion {} working with formid {}"sv,
                    championValue,
                    StringUtil::intToHex(qst->GetFormID()));
                auto questDone = QuestUtil::isOneQuestStageComplete(qst, formid.second);
                if (questDone) {
                    logger::trace("Champion of {}"sv, championValue);
                    _championList.insert(std::pair<FactionValue, std::string>(championValue, _constStaticDisplayValue));
                }
            }
        }


        logger::trace("got {} items in champion list."sv, _championList.size());
        logMap();
    }

private:
    Champion() = default;
    Champion(const Champion&) = delete;
    Champion(Champion&&) = delete;

    ~Champion() = default;

    Champion& operator=(const Champion&) = delete;
    Champion& operator=(Champion&&) = delete;

    valueStringMap _championList;

    /*
    azura, 00028AD6 100 -
    boethiah, 0004D8D6 50 100 -
    clavicusVile, 0001BFC4 200 205 -
    hermaeusMora, 0002D512 100 200 -
    hircine, 0002A49A 100 105 200 -
    malacath, 0003B681 200 -
    mehrunesDagon, 000240B8 100 -
    mephala, 0004A37B 60 80 -
    meridia, 0004E4E1 500 -
    molagBal, 00022F08 200 -
    namira, 0002C358 100 600 -
    nocturnal, 00021555 200 -
    peryite, 0008998D 100 -
    sanguine, 0001BB9B 200 -
    sheogorath, 0002AC68 200 -
    vaermina 000242AF 200 -
    */

    inline static std::map<FactionValue, std::map<RE::FormID, std::vector<uint16_t>>> _championQuestStageMap = {
        { FactionValue::azura, { { 0x00028AD6, std::vector{ QuestUtil::getAs(100) } } } },
        { FactionValue::boethiah, { { 0x0004D8D6, std::vector{ QuestUtil::getAs(50), QuestUtil::getAs(100) } } } },
        { FactionValue::clavicusVile, { { 0x0001BFC4, std::vector{ QuestUtil::getAs(200), QuestUtil::getAs(205) } } } },
        { FactionValue::hermaeusMora, { { 0x0002D512, std::vector{ QuestUtil::getAs(100), QuestUtil::getAs(200) } } } },
        { FactionValue::hircine, { { 0x0002A49A, std::vector{ QuestUtil::getAs(100), QuestUtil::getAs(105) } } } },
        { FactionValue::malacath, { { 0x0003B681, std::vector{ QuestUtil::getAs(200) } } } },
        { FactionValue::mehrunesDagon, { { 0x000240B8, std::vector{ QuestUtil::getAs(100) } } } },
        { FactionValue::mephala, { { 0x0004A37B, std::vector{ QuestUtil::getAs(60), QuestUtil::getAs(80) } } } },
        { FactionValue::meridia, { { 0x0004E4E1, std::vector{ QuestUtil::getAs(500) } } } },
        { FactionValue::molagBal, { { 0x00022F08, std::vector{ QuestUtil::getAs(200) } } } },
        { FactionValue::namira, { { 0x0002C358, std::vector{ QuestUtil::getAs(100), QuestUtil::getAs(600) } } } },
        { FactionValue::nocturnal, { { 0x00021555, std::vector{ QuestUtil::getAs(200) } } } },
        { FactionValue::peryite, { { 0x0008998D, std::vector{ QuestUtil::getAs(100) } } } },
        { FactionValue::sanguine, { { 0x0001BB9B, std::vector{ QuestUtil::getAs(200) } } } },
        { FactionValue::sheogorath, { { 0x0002AC68, std::vector{ QuestUtil::getAs(200) } } } },
        { FactionValue::vaermina, { { 0x000242AF, std::vector{ QuestUtil::getAs(200) } } } },
    };

    void logMap() {
        for (const auto& item : _championList) { logger::trace("champion {}, {}"sv, item.first, item.second); }
    }
};
