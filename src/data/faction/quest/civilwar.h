#pragma once

class CivilWar {
public:
    static CivilWar* GetSingleton() {
        static CivilWar singleton;
        return std::addressof(singleton);
    }

    //handle jagged crown switch
    std::string getImperialLegionRank() {
        auto rankName = _constStringEmpty;
        for (const auto& rank : _imperialQuestStageMap) {
            auto rankValue = rank.first;
            logger::trace("Checking Imperal Rank {}"sv, getImperialRankName(rankValue));
            auto rankDone = false;
            for (const auto& qst : rank.second) {
                auto qstDone = QuestUtil::isOneQuestStageComplete(qst.first, qst.second);
                logger::trace("checked quest {}, done {}"sv, StringUtil::intToHex(qst.first), qstDone);
                if (!qstDone) {
                    rankDone = false;
                    break;
                }
                rankDone = qstDone;
            }
            if (rankDone) {
                logger::trace("Imperial Rank {} done."sv, getImperialRankName(rankValue));
                rankName = getImperialRankName(rankValue);
            } else {
                break;
            }
        }
        logger::trace("Check Done Rank {}"sv, rankName);
        return rankName;
    }

    //handle jagged crown switch
    std::string getStormcloakRank() {
        auto rankName = _constStringEmpty;
        for (const auto& rank : _stormcloakQuestStageMap) {
            auto rankValue = rank.first;
            logger::trace("Checking Stormcloak Rank {}"sv, getStormcloakRankName(rankValue));
            auto rankDone = false;
            for (const auto& qst : rank.second) {
                auto qstDone = QuestUtil::isOneQuestStageComplete(qst.first, qst.second);
                logger::trace("checked quest {}, done {}"sv, StringUtil::intToHex(qst.first), qstDone);
                if (!qstDone) {
                    rankDone = false;
                    break;
                }
                rankDone = qstDone;
            }
            if (rankDone) {
                logger::trace("Stormcloak Rank {} done."sv, getStormcloakRankName(rankValue));
                rankName = getStormcloakRankName(rankValue);
            } else {
                break;
            }
        }
        logger::trace("Check Done Rank {}"sv, rankName);
        return rankName;
    }

private:
    CivilWar() = default;
    CivilWar(const CivilWar&) = delete;
    CivilWar(CivilWar&&) = delete;

    ~CivilWar() = default;

    CivilWar& operator=(const CivilWar&) = delete;
    CivilWar& operator=(CivilWar&&) = delete;

    const std::string _constStringEmpty = "";

    enum class ImperialRank {
        auxiliary,
        quaestor,
        praefect,
        tribune,
        legate,
    };

    inline static std::map<ImperialRank, std::string_view> _imperalRankNameMap = { { ImperialRank::auxiliary,
                                                                                       *Settings::auxiliaryRank },
        { ImperialRank::quaestor, *Settings::quaestorRank },
        { ImperialRank::praefect, *Settings::praefectRank },
        { ImperialRank::tribune, *Settings::tribuneRank },
        { ImperialRank::legate, *Settings::legateRank } };

    static std::string_view getImperialRankName(ImperialRank a_rank) {
        if (_imperalRankNameMap.find(a_rank) == _imperalRankNameMap.end()) {
            logger::warn("can not find Name for Rank {}"sv, a_rank);
            return "";
        } else {
            return _imperalRankNameMap.find(a_rank)->second;
        }
    }

    inline static std::map<ImperialRank, std::map<RE::FormID, std::vector<uint16_t>>> _imperialQuestStageMap = {
        { ImperialRank::auxiliary, { { 0x000D517A, std::vector{ QuestUtil::getAs(200) } } } },
        { ImperialRank::quaestor, { { 0x00096E71, std::vector{ QuestUtil::getAs(9000), QuestUtil::getAs(9999) } } } },
        { ImperialRank::praefect,
            { { 0x0003BCC4, std::vector{ QuestUtil::getAs(200), QuestUtil::getAs(255) } },
                { 0x00083042, std::vector{ QuestUtil::getAs(9000), QuestUtil::getAs(9999) } } } },
        { ImperialRank::tribune,
            { { 0x000504F0, std::vector{ QuestUtil::getAs(200), QuestUtil::getAs(255) } },
                { 0x00083042, std::vector{ QuestUtil::getAs(9000), QuestUtil::getAs(9999) } } } },
        { ImperialRank::legate, { { 0x00035A23, std::vector{ QuestUtil::getAs(200), QuestUtil::getAs(255) } } } },
    };


    enum class StormcloakRank {
        unblooded,
        iceVeins,
        boneBreaker,
        snowHammer,
        stormblade,
    };

    inline static std::map<StormcloakRank, std::string_view> _stormcloakRankNameMap = { { StormcloakRank::unblooded,
                                                                                            *Settings::unbloodedRank },
        { StormcloakRank::iceVeins, *Settings::iceVeinsRank },
        { StormcloakRank::boneBreaker, *Settings::boneBreakerRank },
        { StormcloakRank::snowHammer, *Settings::snowHammerRank },
        { StormcloakRank::stormblade, *Settings::stormbladeRank } };

    static std::string_view getStormcloakRankName(StormcloakRank a_rank) {
        if (_stormcloakRankNameMap.find(a_rank) == _stormcloakRankNameMap.end()) {
            logger::warn("can not find Name for Rank {}"sv, a_rank);
            return "";
        } else {
            return _stormcloakRankNameMap.find(a_rank)->second;
        }
    }

    inline static std::map<StormcloakRank, std::map<RE::FormID, std::vector<uint16_t>>> _stormcloakQuestStageMap = {
        { StormcloakRank::unblooded, { { 0x000E2D29, std::vector{ QuestUtil::getAs(200) } } } },
        { StormcloakRank::iceVeins, { { 0x00096E71, std::vector{ QuestUtil::getAs(9000), QuestUtil::getAs(9999) } } } },
        { StormcloakRank::boneBreaker,
            { { 0x00035A23, std::vector{ QuestUtil::getAs(200), QuestUtil::getAs(255) } } } },
        { StormcloakRank::snowHammer,
            { { 0x000504F0, std::vector{ QuestUtil::getAs(200), QuestUtil::getAs(255) } },
                { 0x00083042, std::vector{ QuestUtil::getAs(9000), QuestUtil::getAs(9999) } } } },
        { StormcloakRank::stormblade,
            { { 0x0003BCC4, std::vector{ QuestUtil::getAs(200), QuestUtil::getAs(255) } },
                { 0x00083042, std::vector{ QuestUtil::getAs(9000), QuestUtil::getAs(9999) } } } },
    };
};
