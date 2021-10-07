#include "data/thane.h"

auto Thane::GetSingleton() -> Thane* {
	static Thane singleton;
	return addressof(singleton);
}

string Thane::getThane(StatsValue p_stat) {
	if (thaneList.find(p_stat) == thaneList.end()) {
		return "";
	} else {
		return thaneList.find(p_stat)->second;
	}
}

void Thane::logMap() {
	for (const auto& item : thaneList) {
		logger::trace("thane {}, {}"sv, item.first, item.second);
	}
}

void Thane::getRegionThanes() {
	//fix spacebar so we do not add a : in statfiller
	for (const auto& item : thaneMap) {
		auto questStage = RE::TESForm::LookupByID(item.first)->As<RE::TESQuest>()->currentStage;

		if (questStage == 200) {
			thaneList.insert(pair<StatsValue, string>(item.second, " "));
		} else if (item.second == StatsValue::thaneOfWhiterun) {
			auto whiterunQuestStage = RE::TESForm::LookupByID(0x0002610C)->As<RE::TESQuest>()->currentStage;
			if (whiterunQuestStage == 200) {
				thaneList.insert(pair<StatsValue, string>(item.second, " "));
			}
		}
	}

	logger::trace("got {} items in thane list."sv, thaneList.size());

	logMap();
}