#include "player.h"
#include "stats/statfiller.h"

Player* Player::GetSingleton()
{
	static Player singleton;
	return addressof(singleton);
}

string Player::getStringValueFromFloat(float x) {
	return to_string(round(x * 100.0) / 100.0);
}

float Player::calculateValue(float p_rm, float p_r) {
	return (p_rm * p_r) / 100;
}

string Player::getBeast(float p_vamp, float p_were) {
	if (p_vamp > 0) {
		return *Settings::vampireString;
	}
	else if (p_were > 0) {
		return *Settings::werewolfString;
	}
	return "";
}

int32_t Player::getFaction(RE::Actor* a_actor) {
	int32_t x = -1;

	/*build into list*/
	auto sex = a_actor->GetActorBase()->GetSex();

	//a_actor->VisitFactions([&x](RE::TESFaction* a_faction, int8_t a_rank) {
	a_actor->VisitFactions([&](RE::TESFaction* a_faction, int8_t a_rank) {
		if (a_faction && a_rank > -1) {
			const auto name(a_faction->GetName());
			const auto formID(a_faction->GetFormID());
			auto rankData(a_faction->rankData);

			if (find(constants::factionList.begin(), constants::factionList.end(), formID) != constants::factionList.end()) {
				logger::info("name {}, formId {}, rank {}"sv, name, formID, a_rank);
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
						logger::info("Name {}, Rankname {}"sv, name, rank);
					}
				}
				/*if rank is empty here then we need to fill it by ourselfs*/
				if (rank.empty()) {
					rank = "Member";
				}
			}
		}
		return false;
		});

	return x;
}

string Player::getArrowDamage(RE::PlayerCharacter* &p_player) {
	RE::InventoryEntryData* equip = p_player->GetEquippedEntryData(false);

	if (equip != nullptr) {
		if (equip->GetObject()->GetFormType() == RE::FormType::Ammo) {
			logger::trace("Item {} is arrow"sv, p_player->GetEquippedEntryData(false)->GetDisplayName());
			return getStringValueFromFloat(p_player->GetDamage(p_player->GetEquippedEntryData(false)));
		}
	}
	return "";
}

string Player::getDamage(RE::PlayerCharacter* &p_player, boolean p_left) {
	RE::InventoryEntryData* hand;
	float damage = -1;
	if (p_left) {
		hand = p_player->currentProcess->middleHigh->leftHand;
	}
	else {
		hand = p_player->currentProcess->middleHigh->rightHand;
	}

	if (hand != nullptr) {
		damage = p_player->GetDamage(hand);
		logger::trace("Name {}, Weapon Damage {}, Left {}"sv, hand->GetDisplayName(), damage, p_left);
	}
	return (damage == -1) ? "" : getStringValueFromFloat(damage);
}

const vector<StatItem> Player::getPlayerValues() {
	logger::trace("Gather Values to Show ..."sv);
	auto player = RE::PlayerCharacter::GetSingleton();
	auto filler = Filler::GetSingleton();

	/*auto fac = getFaction(player);
	logger::trace(to_string(fac));*/

	auto statList = filler->getData();
	for (auto& element : statList) {
		logger::trace("start working name {}, fill values, if needed ..."sv, element.getName());
		if (!element.getShow()) {
			continue;
		}

		if (element.getActor() != RE::ActorValue::kNone) {
			element.setValue(getStringValueFromFloat(player->GetActorValue(element.getActor()) * element.getValueMultiplier() ));
		} else {
			switch (element.getName()) {
			case Stats::name:
				element.setValue(player->GetName());
				break;
			case Stats::race:
				element.setValue(player->GetRace()->GetFullName());
				break;
			case Stats::level:
				element.setValue(to_string(player->GetLevel()));
				break;
			case Stats::perkCount:
				element.setValue(to_string(player->perkCount));
				break;
			case Stats::height:
				element.setValue(getStringValueFromFloat(player->GetHeight()));
				break;
			case Stats::equipedWeight:
				element.setValue(getStringValueFromFloat(player->GetWeight()));
				break;
			case Stats::armor:
				element.setValue(getStringValueFromFloat(player->armorRating));
				break;
			case Stats::skillTrainingsThisLevel:
				element.setValue(to_string(player->skillTrainingsThisLevel));
				break;
			case Stats::damageArrow:
				element.setValue(getArrowDamage(player));
				break;
			case Stats::damage:
				element.setValue(getDamage(player, false));
				break;
			case Stats::damageLeft:
				element.setValue(getDamage(player, true));
				break;
			case Stats::beast:
				element.setValue(getBeast(
					player->GetActorValue(RE::ActorValue::kVampirePerks),
					player->GetActorValue(RE::ActorValue::kWerewolfPerks)
				));
				break;
			case Stats::healthRatePer:
				element.setValue(getStringValueFromFloat(calculateValue(
					player->GetActorValue(RE::ActorValue::kHealRateMult),
					player->GetActorValue(RE::ActorValue::kHealRate))
				));
				break;
			case Stats::magickaRatePer:
				element.setValue(getStringValueFromFloat(calculateValue(
					player->GetActorValue(RE::ActorValue::kMagickaRateMult),
					player->GetActorValue(RE::ActorValue::kMagickaRate))
				));
				break;
			case Stats::staminaRatePer:
				element.setValue(getStringValueFromFloat(calculateValue(
					player->GetActorValue(RE::ActorValue::kStaminaRateMult),
					player->GetActorValue(RE::ActorValue::KStaminaRate))
				));
				break;
			case Stats::xp:
				element.setValue(getXP(player));
				break;
			case Stats::weight:
				element.setValue(getStringValueFromFloat(player->GetWeight()));
				break;
			case Stats::weaponSpeedMult:
				element.setValue(handleWeaponSpeed(player, false));
				break;
			case Stats::leftWeaponSpeedMult:
				element.setValue(handleWeaponSpeed(player, true));
				break;
			default:
				logger::warn("unhandeled stat, name {}, displayName {}"sv, element.getName(), element.getDisplayName());
				break;
			}
		}
	}

	filler->PrintStatsVector(statList);
	return statList;
}

string Player::handleWeaponSpeed(RE::PlayerCharacter* &p_player, boolean p_left) {
	RE::InventoryEntryData* hand;
	float speed = -1;
	if (p_left) {
		hand = p_player->currentProcess->middleHigh->leftHand;
	} else {
		hand = p_player->currentProcess->middleHigh->rightHand;
	}

	//could also get other weapon stats that way
	if (hand != nullptr) {
		auto weapon = static_cast<RE::TESObjectWEAP*>(hand->GetObject());
		speed = weapon->GetSpeed();
		logger::trace("Name {}, Weapon Speed {}, Left {}"sv, hand->GetDisplayName(), speed, p_left);
	}
	return (speed == -1) ? "" : getStringValueFromFloat(speed);
}

string Player::getXP(RE::PlayerCharacter* &p_player) {
	return constants::cutString(getStringValueFromFloat(p_player->skills->data->xp)) 
		+ "/" 
		+ constants::cutString(getStringValueFromFloat(p_player->skills->data->levelThreshold));
}