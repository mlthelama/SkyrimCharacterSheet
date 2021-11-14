#pragma once
#include "data/faction/quest/civilwar.h"

class Faction {
public:
    static Faction* GetSingleton() {
        static Faction singleton;
        return std::addressof(singleton);
    }

    std::string getRank(FactionValue a_stat) {
        if (_factionRankList.find(a_stat) == _factionRankList.end()) {
            return "";
        } else {
            return _factionRankList.find(a_stat)->second;
        }
    }

    void getFactions(RE::Actor* a_actor) {
        _factionRankList.clear();
        auto actorSex = a_actor->GetActorBase()->GetSex();
        auto rankDefault = "Member";

        auto male = RE::SEXES::SEX::kMale;
        auto female = RE::SEXES::SEX::kFemale;

        a_actor->VisitFactions([&](RE::TESFaction* a_faction, int8_t a_rank) {
            if (a_faction && a_rank > -1) {
                const auto name(a_faction->GetName());
                const auto formID(a_faction->GetFormID());
                auto rankData(a_faction->rankData);

                if (_constFactionMap.find(formID) == _constFactionMap.end()) {
                    logger::trace("name {}, formId {}, rank {} not handeled"sv,
                        name,
                        StringUtil::intToHex(formID),
                        a_rank);
                } else {
                    logger::trace("name {}, formId {}, rank {}"sv, name, StringUtil::intToHex(formID), a_rank);
                    std::string rank;

                    for (auto it = rankData.begin(); it != rankData.end(); ++it) {
                        auto index = std::distance(rankData.begin(), it);
                        auto i = *it;
                        if (index == a_rank) {
                            if (actorSex == female) {
                                rank = i->femaleRankTitle;
                            }
                            if ((rank.empty() || rank.size() == 0) || actorSex == male) {
                                rank = i->maleRankTitle;
                            }
                            logger::trace("Name {}, Rankname {}"sv, name, rank);
                        }
                    }

                    /*if rank is empty here then we need to fill it by ourselfs*/
                    switch (_constFactionMap.find(formID)->second) {
                        case FactionValue::darkbrotherHood:
                            rank = getDarkBrotherhoodRank();
                            break;
                        case FactionValue::greybeard:
                            rank = getGraybeardRank();
                            break;
                        case FactionValue::imperialLegion:
                            rank = CivilWar::GetSingleton()->getImperialLegionRank();
                            break;
                        case FactionValue::stormcloaks:
                            rank = CivilWar::GetSingleton()->getStormcloakRank();
                            break;
                        case FactionValue::volkiharVampireClan:
                            rank = getVolkiharVampireClanRank();
                            break;
                        case FactionValue::dawnguard:
                            rank = getDawnguardRank();
                            break;
                        case FactionValue::houseTelvanni:
                            rank = getHouseTelvanniRank();
                            break;
                        default:
                            if (rank.empty()) {
                                rank = rankDefault;
                            }
                            break;
                    }

                    _factionRankList.insert(
                        std::pair<FactionValue, std::string>(_constFactionMap.find(formID)->second, rank));
                }
            }
            return false;
        });

        //MS05
        if (QuestUtil::isQuestStageComplete(0x00053511, QuestUtil::getAs(300))) {
            //"Bard"
            _factionRankList.insert(std::pair<FactionValue, std::string>(FactionValue::bard, *Settings::bardRank));
        }

        logger::trace("got {} items in faction list."sv, _factionRankList.size());
        logMap();
    }


    Faction() = default;
    Faction(const Faction&) = delete;
    Faction(Faction&&) = delete;

    ~Faction() = default;

    Faction& operator=(const Faction&) = delete;
    Faction& operator=(Faction&&) = delete;

private:
    valueStringMap _factionRankList;

    //0x00072834 //blades, player might not be in there
    inline static std::map<RE::FormID, FactionValue> _constFactionMap = { { 0x00048362, FactionValue::companions },
        { 0x0001BDB3, FactionValue::darkbrotherHood },
        { 0x0001F259, FactionValue::collegeOfWinterhold },
        { 0x00024029, FactionValue::orcFriend },
        { 0x00029DA9, FactionValue::thiefsGuild },
        { 0x0002BF9A, FactionValue::imperialLegion },
        { 0x0002BF9B, FactionValue::stormcloaks },
        { 0x0002C6C8, FactionValue::greybeard },
        { 0x02003376, FactionValue::volkiharVampireClan },
        { 0x02014217, FactionValue::dawnguard },
        { 0x04019B8A, FactionValue::houseTelvanni } };


    void logMap() {
        for (const auto& item : _factionRankList) { logger::trace("faction {}, rank {}"sv, item.first, item.second); }
    }

    std::string getDarkBrotherhoodRank() {
        auto rank = *Settings::assassinRank;
        //hail sithis
        if (QuestUtil::isOneQuestStageComplete(0x0001EA59,
                std::vector{ QuestUtil::getAs(200), QuestUtil::getAs(255) })) {
            rank = *Settings::listenerRank;
        }
        return rank;
    }

    std::string getGraybeardRank() { return *Settings::ysmirRank; }

    std::string getVolkiharVampireClanRank() { return *Settings::vampireLordRank; }

    std::string getDawnguardRank() { return *Settings::vampireHunterRank; }

    std::string getHouseTelvanniRank() { return *Settings::honoraryMemberRank; }
};
