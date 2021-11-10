#pragma once

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
                    logger::trace("name {}, formId {}, rank {} not handeled"sv, name, intToHex(formID), a_rank);
                } else {
                    logger::trace("name {}, formId {}, rank {}"sv, name, intToHex(formID), a_rank);
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
                            rank = getImperialLegionRank();
                            break;
                        case FactionValue::stormcloaks:
                            rank = getStormcloaksRank();
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
        if (RE::TESForm::LookupByID(0x00053511)->As<RE::TESQuest>()->currentStage == 300) {
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

    void logMap() {
        for (const auto& item : _factionRankList) { logger::trace("faction {}, rank {}"sv, item.first, item.second); }
    }

    std::string getDarkBrotherhoodRank() {
        auto rank = *Settings::assassinRank;
        auto dbquest = RE::TESForm::LookupByID(0x0001EA59);  //hail sithis
        if (dbquest != nullptr) {
            auto qst = dbquest->As<RE::TESQuest>();
            auto stage = qst->currentStage;
            if (stage == 200 || stage == 255) {
                rank = *Settings::listenerRank;
            }
        }
        return rank;
    }

    std::string getGraybeardRank() { return *Settings::ysmirRank; }

    std::string getImperialLegionRank() {
        auto rank = _constUndefined;
        if (RE::TESForm::LookupByID(0x000D517A)->As<RE::TESQuest>()->currentStage == 200) {
            // 	CW01A
            rank = *Settings::auxiliaryRank;

            //CWSiegeObj
            auto quaestorQuest = RE::TESForm::LookupByID(0x00096E71)->As<RE::TESQuest>()->currentStage;
            if (quaestorQuest == 9000 || quaestorQuest == 9999) {
                rank = *Settings::quaestorRank;

                //CWMission03
                //CWFortSiegeFort
                auto praefectQuestReq = RE::TESForm::LookupByID(0x0003BCC4)->As<RE::TESQuest>()->currentStage;
                auto praefectQuest = RE::TESForm::LookupByID(0x00083042)->As<RE::TESQuest>()->currentStage;
                if ((praefectQuestReq == 200 || praefectQuestReq == 255) &&
                    (praefectQuest == 9000 || praefectQuest == 9999)) {
                    rank = *Settings::praefectRank;

                    //CWMission07
                    //CWFortSiegeFort
                    auto tribuneQuestReq = RE::TESForm::LookupByID(0x000504F0)->As<RE::TESQuest>()->currentStage;
                    auto tribuneQuest = RE::TESForm::LookupByID(0x00083042)->As<RE::TESQuest>()->currentStage;
                    if ((tribuneQuestReq == 200 || tribuneQuestReq == 255) &&
                        (tribuneQuest == 9000 || tribuneQuest == 9999)) {
                        rank = *Settings::tribuneRank;

                        //CWMission04
                        auto legateQuest = RE::TESForm::LookupByID(0x00035A23)->As<RE::TESQuest>()->currentStage;
                        if (legateQuest == 200 || legateQuest == 255) {
                            rank = *Settings::legateRank;
                        }
                    }
                }
            }
        }
        return rank;
    }

    std::string getStormcloaksRank() {
        auto rank = _constUndefined;

        if (RE::TESForm::LookupByID(0x000E2D29)->As<RE::TESQuest>()->currentStage == 200) {
            // 	CW01B
            rank = *Settings::unbloodedRank;

            //CWSiegeObj
            auto iceVeinsQuest = RE::TESForm::LookupByID(0x00096E71)->As<RE::TESQuest>()->currentStage;
            if (iceVeinsQuest == 9000 || iceVeinsQuest == 9999) {
                rank = *Settings::iceVeinsRank;

                //CWMission04
                auto boneBreakerQuest = RE::TESForm::LookupByID(0x00035A23)->As<RE::TESQuest>()->currentStage;
                if (boneBreakerQuest == 200 || boneBreakerQuest == 255) {
                    rank = *Settings::boneBreakerRank;

                    //CWMission07
                    //CWFortSiegeFort
                    auto snowHammerQuestReq = RE::TESForm::LookupByID(0x000504F0)->As<RE::TESQuest>()->currentStage;
                    auto snowHammerQuest = RE::TESForm::LookupByID(0x00083042)->As<RE::TESQuest>()->currentStage;
                    if ((snowHammerQuestReq == 200 || snowHammerQuestReq == 255) &&
                        (snowHammerQuest == 9000 || snowHammerQuest == 9999)) {
                        rank = *Settings::snowHammerRank;

                        //CWMission03
                        //CWFortSiegeFort
                        auto stormbladeQuestReq = RE::TESForm::LookupByID(0x0003BCC4)->As<RE::TESQuest>()->currentStage;
                        auto stormbladeQuest = RE::TESForm::LookupByID(0x00083042)->As<RE::TESQuest>()->currentStage;
                        if ((stormbladeQuestReq == 200 || stormbladeQuestReq == 255) &&
                            (stormbladeQuest == 9000 || stormbladeQuest == 9999)) {
                            rank = *Settings::stormbladeRank;
                        }
                    }
                }
            }
        }

        return rank;
    }

    std::string getVolkiharVampireClanRank() { return *Settings::vampireLordRank; }

    std::string getDawnguardRank() { return *Settings::vampireHunterRank; }

    std::string getHouseTelvanniRank() { return *Settings::honoraryMemberRank; }
};
