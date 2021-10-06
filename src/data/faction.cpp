#pragma once
#include "data/faction.h"

auto Faction::GetSingleton() -> Faction* {
	static Faction singleton;
	return addressof(singleton);
}

void Faction::getFactions(RE::Actor* a_actor) {
	factionRankList.clear();
	auto sex = a_actor->GetActorBase()->GetSex();
	auto rankDefault = "Member";

	a_actor->VisitFactions([&](RE::TESFaction* a_faction, int8_t a_rank) {
		if (a_faction && a_rank > -1) {
			const auto name(a_faction->GetName());
			const auto formID(a_faction->GetFormID());
			auto rankData(a_faction->rankData);

			if (factionMap.find(formID) == factionMap.end()) {
				logger::trace("name {}, formId {}, rank {} not handeled"sv, name, intToHex(formID), a_rank);
			} else {
				logger::trace("name {}, formId {}, rank {}"sv, name, intToHex(formID), a_rank);
				string rank;

				for (auto it = rankData.begin(); it != rankData.end(); ++it) {
					auto index = distance(rankData.begin(), it);
					auto i = *it;
					if (index == a_rank) {
						if (sex == RE::SEXES::SEX::kFemale) {
							rank = i->femaleRankTitle;
						}
						if ((rank.empty() || rank.size() == 0) || sex == RE::SEXES::SEX::kMale) {
							rank = i->maleRankTitle;
						}
						logger::trace("Name {}, Rankname {}"sv, name, rank);
					}
				}

				/*if rank is empty here then we need to fill it by ourselfs*/
				switch (factionMap.find(formID)->second) {
				case StatsValue::darkbrotherHood:
					rank = getDarkBrotherhoodRank();
					break;
				case StatsValue::greybeard:
					rank = getGraybeardRank();
					break;
				case StatsValue::imperialLegion:
					rank = getImperialLegionRank();
					break;
				case StatsValue::stormcloaks:
					rank = getStormcloaksRank();
					break;
				case StatsValue::volkiharVampireClan:
					rank = getVolkiharVampireClanRank();
					break;
				case StatsValue::dawnguard:
					rank = getDawnguardRank();
					break;
				case StatsValue::houseTelvanni:
					rank = getHouseTelvanniRank();
					break;
				default:
					if (rank.empty()) {
						rank = rankDefault;
					}
					break;
				}

				factionRankList.insert(pair<StatsValue, string>(factionMap.find(formID)->second, rank));
			}
		}
		return false;
	});

	//MS05
	if (RE::TESForm::LookupByID(0x00053511)->As<RE::TESQuest>()->currentStage == 300) {
		//"Bard"
		factionRankList.insert(pair<StatsValue, string>(StatsValue::bard, *Settings::bardRank));
	}

	logger::trace("got {} items in faction list."sv, factionRankList.size());

	logMap();
}

string Faction::getRank(StatsValue p_stat) {
	if (factionRankList.find(p_stat) == factionRankList.end()) {
		return "";
	} else {
		return factionRankList.find(p_stat)->second;
	}
}

void Faction::logMap() {
	for (const auto& item : factionRankList) {
		logger::trace("faction {}, rank {}"sv, item.first, item.second);
	}
}

string Faction::getDarkBrotherhoodRank() {
	auto rank = *Settings::assassinRank;
	auto dbquest = RE::TESForm::LookupByID(0x0001EA59);	 //hail sithis
	if (dbquest != nullptr) {
		auto qst = dbquest->As<RE::TESQuest>();
		auto stage = qst->currentStage;
		if (stage == 200 || stage == 255) {
			rank = *Settings::listenerRank;
		}
	}
	return rank;
}

string Faction::getGraybeardRank() {
	return *Settings::ysmirRank;
}

string Faction::getImperialLegionRank() {
	auto rank = undefined;
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
			if ((praefectQuestReq == 200 || praefectQuestReq == 255) && (praefectQuest == 9000 || praefectQuest == 9999)) {
				rank = *Settings::praefectRank;

				//CWMission07
				//CWFortSiegeFort
				auto tribuneQuestReq = RE::TESForm::LookupByID(0x000504F0)->As<RE::TESQuest>()->currentStage;
				auto tribuneQuest = RE::TESForm::LookupByID(0x00083042)->As<RE::TESQuest>()->currentStage;
				if ((tribuneQuestReq == 200 || tribuneQuestReq == 255) && (tribuneQuest == 9000 || tribuneQuest == 9999)) {
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


string Faction::getStormcloaksRank() {
	auto rank = undefined;

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
				if ((snowHammerQuestReq == 200 || snowHammerQuestReq == 255) && (snowHammerQuest == 9000 || snowHammerQuest == 9999)) {
					rank = *Settings::snowHammerRank;

					//CWMission03
					//CWFortSiegeFort
					auto stormbladeQuestReq = RE::TESForm::LookupByID(0x0003BCC4)->As<RE::TESQuest>()->currentStage;
					auto stormbladeQuest = RE::TESForm::LookupByID(0x00083042)->As<RE::TESQuest>()->currentStage;
					if ((stormbladeQuestReq == 200 || stormbladeQuestReq == 255) && (stormbladeQuest == 9000 || stormbladeQuest == 9999)) {
						rank = *Settings::stormbladeRank;
					}
				}
			}
		}
	}

	return rank;
}

string Faction::getVolkiharVampireClanRank() {
	return *Settings::vampireLordRank;
}

string Faction::getDawnguardRank() {
	return *Settings::vampireHunterRank;
}

string Faction::getHouseTelvanniRank() {
	return *Settings::honoraryMemberRank;
}