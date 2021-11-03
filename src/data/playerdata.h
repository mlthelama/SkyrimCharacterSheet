#pragma once
#include "stats/statfiller.h"
#include "stats/statholder.h"

class PlayerData {
public:
    static PlayerData* GetSingleton() {
        static PlayerData singleton;
        return std::addressof(singleton);
    }

    std::vector<std::shared_ptr<StatItem>> getPlayerValues() {
        logger::trace("Gather Values to Show ..."sv);
        auto player = RE::PlayerCharacter::GetSingleton();
        auto filler = StatFiller::GetSingleton();

        auto statList = filler->getData();
        for (auto& element : statList) {
            if (!element->getShow()) {
                continue;
            }

            if (element->getActor() != RE::ActorValue::kNone) {
                auto value = player->GetActorValue(element->getActor()) * element->getValueMultiplier();
                if (element->getSpecialHandling()) {
                    element->setValue(getValueWithCapIfNeeded(value, element->getCap(), element->getEnding()));
                } else {
                    element->setValue(getStringValueFromFloat(value));
                }
            } else {
                switch (element->getName()) {
                    case StatsValue::name:
                        element->setValue(player->GetName());
                        break;
                    case StatsValue::race:
                        element->setValue(player->GetRace()->GetFullName());
                        break;
                    case StatsValue::level:
                        element->setValue(std::to_string(player->GetLevel()));
                        break;
                    case StatsValue::perkCount:
                        element->setValue(std::to_string(player->perkCount));
                        break;
                    case StatsValue::height:
                        element->setValue(getStringValueFromFloat(player->GetHeight()));
                        break;
                    case StatsValue::equipedWeight:
                        element->setValue(getStringValueFromFloat(player->GetWeight()));
                        break;
                    case StatsValue::armor:
                        element->setValue(getStringValueFromFloat(player->armorRating));
                        break;
                    case StatsValue::skillTrainingsThisLevel:
                        element->setValue(std::to_string(player->skillTrainingsThisLevel));
                        break;
                    case StatsValue::damageArrow:
                        element->setValue(getArrowDamage(player));
                        break;
                    case StatsValue::damage:
                        element->setValue(getDamage(player, false));
                        break;
                    case StatsValue::damageLeft:
                        element->setValue(getDamage(player, true));
                        break;
                    case StatsValue::beast:
                        element->setValue(getBeast(player->GetActorValue(RE::ActorValue::kVampirePerks),
                            player->GetActorValue(RE::ActorValue::kWerewolfPerks)));
                        break;
                    case StatsValue::healthRatePer:
                        element->setValue(
                            getStringValueFromFloat(calculateValue(player->GetActorValue(RE::ActorValue::kHealRateMult),
                                player->GetActorValue(RE::ActorValue::kHealRate))));
                        break;
                    case StatsValue::magickaRatePer:
                        element->setValue(getStringValueFromFloat(
                            calculateValue(player->GetActorValue(RE::ActorValue::kMagickaRateMult),
                                player->GetActorValue(RE::ActorValue::kMagickaRate))));
                        break;
                    case StatsValue::staminaRatePer:
                        element->setValue(getStringValueFromFloat(
                            calculateValue(player->GetActorValue(RE::ActorValue::kStaminaRateMult),
                                player->GetActorValue(RE::ActorValue::KStaminaRate))));
                        break;
                    case StatsValue::xp:
                        element->setValue(getXP(player));
                        break;
                    case StatsValue::weight:
                        element->setValue(getStringValueFromFloat(player->GetWeight()));
                        break;
                    case StatsValue::weaponSpeedMult:
                        element->setValue(handleWeaponSpeed(player, false));
                        break;
                    case StatsValue::leftWeaponSpeedMult:
                        element->setValue(handleWeaponSpeed(player, true));
                        break;
                    case StatsValue::resistDamage:
                        element->setValue(getDamageResistance(player, element->getCap(), element->getSpecialHandling(),
                            element->getEnding()));
                        break;
                    default:
                        logger::warn("unhandeled stat, name {}, displayName {}"sv, element->getName(),
                            element->getDisplayName());
                        break;
                }
            }
        }

        filler->PrintStatsVector(statList);

        return statList;
    }

private:
    //std::map<StatsValue, std::string> factionRankMap;

    std::string getBeast(float p_vamp, float p_were) {
        if (p_vamp > 0) {
            return *Settings::vampireString;
        } else if (p_were > 0) {
            return *Settings::werewolfString;
        }
        return "";
    }

    std::string getArrowDamage(RE::PlayerCharacter*& p_player) {
        RE::InventoryEntryData* equip = p_player->GetEquippedEntryData(false);

        if (equip != nullptr) {
            if (equip->GetObject()->GetFormType() == RE::FormType::Ammo) {
                logger::trace("Item {} is arrow"sv, p_player->GetEquippedEntryData(false)->GetDisplayName());
                return getStringValueFromFloat(p_player->GetDamage(p_player->GetEquippedEntryData(false)));
            }
        }
        return "";
    }

    std::string getDamage(RE::PlayerCharacter*& p_player, bool p_left) {
        RE::InventoryEntryData* hand;
        float damage = -1;
        if (p_left) {
            hand = p_player->currentProcess->middleHigh->leftHand;
        } else {
            hand = p_player->currentProcess->middleHigh->rightHand;
        }

        if (hand != nullptr) {
            damage = p_player->GetDamage(hand);
            logger::trace("Name {}, Weapon Damage {}, Left {}"sv, hand->GetDisplayName(), damage, p_left);
        }
        return (damage == -1) ? "" : getStringValueFromFloat(damage);
    }

    std::string handleWeaponSpeed(RE::PlayerCharacter*& p_player, bool p_left) {
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

    std::string getXP(RE::PlayerCharacter*& p_player) {
        return fmt::format(FMT_STRING("{}/{}"), cutString(getStringValueFromFloat(p_player->skills->data->xp)),
            cutString(getStringValueFromFloat(p_player->skills->data->levelThreshold)));
    }

    /* might need additional checks for mods that add more items 
    * each light, heavy or shield gives 3% res + for some reason there is a 12 base res
    * formula would be ((totalArmorRating * 0.12) + (3 * piecesWorn));
    */
    std::string getDamageResistance(RE::PlayerCharacter*& p_player, float p_cap, bool p_special, std::string p_ending) {
        const auto inv = p_player->GetInventory([](RE::TESBoundObject& a_object) { return a_object.IsArmor(); });
        auto armorCount = 0;
        for (const auto& [item, invData] : inv) {
            const auto& [count, entry] = invData;
            if (count > 0 && entry->IsWorn()) {
                const auto armor = item->As<RE::TESObjectARMO>();
                /* clothing does not count torwards reduction
                *  as stated here http://en.uesp.net/wiki/Skyrim:Armor#Armor_Rating
                */
                if (armor->IsLightArmor() || armor->IsHeavyArmor() || armor->IsShield()) {
                    logger::trace("Armor name {}, Rating {}"sv, armor->GetName(), armor->GetArmorRating());
                    armorCount++;
                }
            }
        }

        auto damageResistance = calculateArmorDamageRes(p_player->armorRating, armorCount);
        //auto dragonhide = getValueIfDragonhideIsAcitve(p_player);
        auto damageResistanceString = getStringValueFromFloat(damageResistance);
        logger::debug("Damage Resistance from Armor {}"sv, damageResistance);
        if (p_special && p_cap > 0) {
            damageResistanceString = getValueWithCapIfNeeded(damageResistance, p_cap, p_ending);
        }

        return damageResistanceString;
    }

    /* currently unused because unsure of calculation, it should be damageRes + ((100-damageRes)/(100/dragonhideValue))
    *  with the 80% cap it should be a total of 96% res
    */
    float getValueIfDragonhideIsActive(RE::PlayerCharacter*& p_player) {
        auto effects = p_player->GetActiveEffectList();
        if (!effects) {
            return 0;
        }

        for (const auto& effect : *effects) {
            if (effect) {
                auto formid = effect->GetBaseObject()->GetFormID();
                //Dragonhide
                if (formid = 0x000CDB75) {
                    logger::debug("Is Armor Spell {}, magnitude{}, formid {}"sv, effect->GetBaseObject()->GetName(),
                        effect->magnitude, intToHex(formid));
                    return effect->magnitude;
                }
            }
        }
        return 0;
    }

    PlayerData() = default;
    PlayerData(const PlayerData&) = delete;
    PlayerData(PlayerData&&) = delete;

    ~PlayerData() = default;

    PlayerData& operator=(const PlayerData&) = delete;
    PlayerData& operator=(PlayerData&&) = delete;
};
