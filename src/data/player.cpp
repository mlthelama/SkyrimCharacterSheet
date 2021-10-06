#include "data/player.h"
#include "stats/statfiller.h"
#include "data/faction.h"

Player* Player::GetSingleton()
{
	static Player singleton;
	return addressof(singleton);
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
	auto faction = Faction::GetSingleton();

	if (*Settings::showFactions) {
		faction->getFactions(player);
	}

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
			case StatsValue::name:
				element.setValue(player->GetName());
				break;
			case StatsValue::race:
				element.setValue(player->GetRace()->GetFullName());
				break;
			case StatsValue::level:
				element.setValue(to_string(player->GetLevel()));
				break;
			case StatsValue::perkCount:
				element.setValue(to_string(player->perkCount));
				break;
			case StatsValue::height:
				element.setValue(getStringValueFromFloat(player->GetHeight()));
				break;
			case StatsValue::equipedWeight:
				element.setValue(getStringValueFromFloat(player->GetWeight()));
				break;
			case StatsValue::armor:
				element.setValue(getStringValueFromFloat(player->armorRating));
				break;
			case StatsValue::skillTrainingsThisLevel:
				element.setValue(to_string(player->skillTrainingsThisLevel));
				break;
			case StatsValue::damageArrow:
				element.setValue(getArrowDamage(player));
				break;
			case StatsValue::damage:
				element.setValue(getDamage(player, false));
				break;
			case StatsValue::damageLeft:
				element.setValue(getDamage(player, true));
				break;
			case StatsValue::beast:
				element.setValue(getBeast(
					player->GetActorValue(RE::ActorValue::kVampirePerks),
					player->GetActorValue(RE::ActorValue::kWerewolfPerks)
				));
				break;
			case StatsValue::healthRatePer:
				element.setValue(getStringValueFromFloat(calculateValue(
					player->GetActorValue(RE::ActorValue::kHealRateMult),
					player->GetActorValue(RE::ActorValue::kHealRate))
				));
				break;
			case StatsValue::magickaRatePer:
				element.setValue(getStringValueFromFloat(calculateValue(
					player->GetActorValue(RE::ActorValue::kMagickaRateMult),
					player->GetActorValue(RE::ActorValue::kMagickaRate))
				));
				break;
			case StatsValue::staminaRatePer:
				element.setValue(getStringValueFromFloat(calculateValue(
					player->GetActorValue(RE::ActorValue::kStaminaRateMult),
					player->GetActorValue(RE::ActorValue::KStaminaRate))
				));
				break;
			case StatsValue::xp:
				element.setValue(getXP(player));
				break;
			case StatsValue::weight:
				element.setValue(getStringValueFromFloat(player->GetWeight()));
				break;
			case StatsValue::weaponSpeedMult:
				element.setValue(handleWeaponSpeed(player, false));
				break;
			case StatsValue::leftWeaponSpeedMult:
				element.setValue(handleWeaponSpeed(player, true));
				break;
			case StatsValue::companions:
			case StatsValue::darkbrotherHood:
			case StatsValue::collegeOfWinterhold:
			case StatsValue::orcFriend:
			case StatsValue::thiefsGuild:
			case StatsValue::imperialLegion:
			case StatsValue::stormcloaks:
			case StatsValue::greybeard:
			case StatsValue::bard:
			case StatsValue::volkiharVampireClan:
			case StatsValue::dawnguard:
			case StatsValue::houseTelvanni:
				element.setValue(faction->getRank(element.getName()));
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
	return cutString(getStringValueFromFloat(p_player->skills->data->xp)) 
		+ "/" 
		+ cutString(getStringValueFromFloat(p_player->skills->data->levelThreshold));
}