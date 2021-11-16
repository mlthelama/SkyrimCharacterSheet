#pragma once
#include "data/stats/statitem.h"
#include "settings/stats/statssettings.h"


class PlayerData {
    using StatsItemMap = std::map<StatsValue, std::unique_ptr<StatItem>>;
    using ShowMenu = MenuUtil::ShowMenu;
    using StatsInventoryMenuValue = MenuUtil::StatsInventoryMenuValue;

public:
    static PlayerData* GetSingleton() {
        static PlayerData singleton;
        return std::addressof(singleton);
    }

    StatsItemMap getValuesToDisplay(ShowMenu a_menu) {
        logger::debug("Get Values to Display for Menu ({}) ..."sv, MenuUtil::getMenuName(a_menu));
        StatsItemMap simp;

        auto player = RE::PlayerCharacter::GetSingleton();

        auto statSettingMap = StatSetting::GetSingleton()->load();
        logger::debug("Config Map Size is {}"sv, statSettingMap.size());

        for (auto& element : statSettingMap) {
            auto statValue = element.first;
            auto statConfig = element.second.get();

            statConfig->logStatConfig(statValue);

            if ((a_menu == ShowMenu::mStats && !statConfig->getShow()) ||
                (a_menu == ShowMenu::mInventoryStats &&
                    (!statConfig->getShow() ||
                        statConfig->getStatsInventoryMenu() == StatsInventoryMenuValue::mNone))) {
                continue;
            }
            std::string valueText = "";

            switch (statValue) {
                case StatsValue::name:
                    valueText = player->GetName();
                    break;
                case StatsValue::race:
                    valueText = player->GetRace()->GetFullName();
                    break;
                case StatsValue::level:
                    valueText = std::to_string(player->GetLevel());
                    break;
                case StatsValue::perkCount:
                    valueText = std::to_string(player->perkCount);
                    break;
                case StatsValue::height:
                    valueText = StringUtil::getStringValueFromFloat(player->GetHeight());
                    break;
                case StatsValue::equipedWeight:
                    valueText = StringUtil::getStringValueFromFloat(player->GetWeight());
                    break;
                case StatsValue::armor:
                    valueText = StringUtil::getStringValueFromFloat(player->armorRating);
                    break;
                case StatsValue::skillTrainingsThisLevel:
                    valueText = std::to_string(player->skillTrainingsThisLevel);
                    break;
                case StatsValue::damageArrow:
                    valueText = getArrowDamage(player);
                    break;
                case StatsValue::damage:
                    valueText = getDamage(player, false);
                    break;
                case StatsValue::damageLeft:
                    valueText = getDamage(player, true);
                    break;
                case StatsValue::beast:
                    valueText = getBeast(player->GetActorValue(RE::ActorValue::kVampirePerks),
                        player->GetActorValue(RE::ActorValue::kWerewolfPerks));
                    break;
                case StatsValue::healthRatePer:
                    valueText = StringUtil::getStringValueFromFloat(
                        StringUtil::calculateValue(player->GetActorValue(RE::ActorValue::kHealRateMult),
                            player->GetActorValue(RE::ActorValue::kHealRate)));
                    break;
                case StatsValue::magickaRatePer:
                    valueText = StringUtil::getStringValueFromFloat(
                        StringUtil::calculateValue(player->GetActorValue(RE::ActorValue::kMagickaRateMult),
                            player->GetActorValue(RE::ActorValue::kMagickaRate)));
                    break;
                case StatsValue::staminaRatePer:
                    valueText = StringUtil::getStringValueFromFloat(
                        StringUtil::calculateValue(player->GetActorValue(RE::ActorValue::kStaminaRateMult),
                            player->GetActorValue(RE::ActorValue::KStaminaRate)));
                    break;
                case StatsValue::xp:
                    valueText = getXP(player);
                    break;
                case StatsValue::weight:
                    valueText = StringUtil::getStringValueFromFloat(player->GetWeight());
                    break;
                case StatsValue::weaponSpeedMult:
                    valueText = handleWeaponSpeed(player, false);
                    break;
                case StatsValue::leftWeaponSpeedMult:
                    valueText = handleWeaponSpeed(player, true);
                    break;
                case StatsValue::resistDamage:
                    valueText = getDamageResistance(player, statConfig->getCap(), statConfig->getEnding());
                    break;
                default:
                    if (statConfig->getActor() != RE::ActorValue::kNone) {
                        auto value = player->GetActorValue(statConfig->getActor()) * statConfig->getValueMultiplier();
                        if (statConfig->getCap() != -1) {
                            valueText = ValueUtil::getValueWithCapIfNeeded(value,
                                statConfig->getCap(),
                                statConfig->getEnding());
                        } else {
                            valueText = StringUtil::getStringValueFromFloat(value);
                        }
                    } else {
                        logger::warn("unhandeled stat, name {}, displayName {}"sv,
                            statValue,
                            statConfig->getDisplayName());
                    }
                    break;
            }

            if (valueText != "") {
                if (a_menu == ShowMenu::mStats) {
                    simp[statValue] =
                        std::make_unique<StatItem>(statConfig->getDisplay(valueText), statConfig->getStatsMenu());
                } else {
                    simp[statValue] = std::make_unique<StatItem>(statConfig->getDisplay(valueText),
                        statConfig->getStatsInventoryMenu());
                }
            }
        }

        for (auto& element : statSettingMap) { element.second.reset(); }
        statSettingMap.clear();

        logger::debug("Setting Map is {}, Display Map Size is {} for Menu ({})"sv,
            statSettingMap.size(),
            simp.size(),
            MenuUtil::getMenuName(a_menu));
        return simp;
    }

private:
    PlayerData() = default;
    PlayerData(const PlayerData&) = delete;
    PlayerData(PlayerData&&) = delete;

    ~PlayerData() = default;

    PlayerData& operator=(const PlayerData&) = delete;
    PlayerData& operator=(PlayerData&&) = delete;

    std::string getBeast(float a_vamp, float a_were) {
        if (a_vamp > 0) {
            return *Settings::vampireString;
        } else if (a_were > 0) {
            return *Settings::werewolfString;
        }
        return "";
    }

    std::string getArrowDamage(RE::PlayerCharacter*& a_player) {
        RE::InventoryEntryData* equip = a_player->GetEquippedEntryData(false);

        if (equip != nullptr) {
            if (equip->GetObject()->GetFormType() == RE::FormType::Ammo) {
                logger::trace("Item {} is arrow"sv, a_player->GetEquippedEntryData(false)->GetDisplayName());
                return StringUtil::getStringValueFromFloat(a_player->GetDamage(a_player->GetEquippedEntryData(false)));
            }
        }
        return "";
    }

    std::string getDamage(RE::PlayerCharacter*& a_player, bool a_left) {
        RE::InventoryEntryData* hand;
        float damage = -1;
        if (a_left) {
            hand = a_player->currentProcess->middleHigh->leftHand;
        } else {
            hand = a_player->currentProcess->middleHigh->rightHand;
        }

        if (hand != nullptr) {
            damage = a_player->GetDamage(hand);
            logger::trace("Name {}, Weapon Damage {}, Left {}"sv, hand->GetDisplayName(), damage, a_left);
        }
        return (damage == -1) ? "" : StringUtil::getStringValueFromFloat(damage);
    }

    std::string handleWeaponSpeed(RE::PlayerCharacter*& a_player, bool a_left) {
        RE::InventoryEntryData* hand;
        float speed = -1;
        if (a_left) {
            hand = a_player->currentProcess->middleHigh->leftHand;
        } else {
            hand = a_player->currentProcess->middleHigh->rightHand;
        }

        //could also get other weapon stats that way
        if (hand != nullptr) {
            speed = static_cast<RE::TESObjectWEAP*>(hand->GetObject())->GetSpeed();
            logger::trace("Name {}, Weapon Speed {}, Left {}"sv, hand->GetDisplayName(), speed, a_left);
        }
        return (speed == -1) ? "" : StringUtil::getStringValueFromFloat(speed);
    }

    std::string getXP(RE::PlayerCharacter*& a_player) {
        return fmt::format(FMT_STRING("{}/{}"),
            StringUtil::cutString(StringUtil::getStringValueFromFloat(a_player->skills->data->xp)),
            StringUtil::cutString(StringUtil::getStringValueFromFloat(a_player->skills->data->levelThreshold)));
    }

    /* might need additional checks for mods that add more items 
    * each light, heavy or shield gives 3% res + for some reason there is a 12 base res
    * formula would be ((totalArmorRating * 0.12) + (3 * piecesWorn));
    */
    std::string getDamageResistance(RE::PlayerCharacter*& a_player, float a_cap, std::string a_ending) {
        const auto inv = a_player->GetInventory([](RE::TESBoundObject& a_object) { return a_object.IsArmor(); });
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

        auto damageResistance = ValueUtil::calculateArmorDamageRes(a_player->armorRating, armorCount);
        //auto dragonhide = getValueIfDragonhideIsAcitve(a_player);
        auto damageResistanceString = StringUtil::getStringValueFromFloat(damageResistance);
        logger::debug("Damage Resistance from Armor {}"sv, damageResistance);
        if (a_cap != -1) {
            damageResistanceString = ValueUtil::getValueWithCapIfNeeded(damageResistance, a_cap, a_ending);
        }

        return damageResistanceString;
    }

    /* currently unused because unsure of calculation, it should be damageRes + ((100-damageRes)/(100/dragonhideValue))
    *  with the 80% cap it should be a total of 96% res
    */
    float getValueIfDragonhideIsActive(RE::PlayerCharacter*& a_player) {
        auto effects = a_player->GetActiveEffectList();
        if (!effects) {
            return 0;
        }

        for (const auto& effect : *effects) {
            if (effect) {
                auto formid = effect->GetBaseObject()->GetFormID();
                //Dragonhide
                if (formid == 0x000CDB75) {
                    logger::debug("Is Armor Spell {}, magnitude{}, formid {}"sv,
                        effect->GetBaseObject()->GetName(),
                        effect->magnitude,
                        StringUtil::intToHex(formid));
                    return effect->magnitude;
                }
            }
        }
        return 0;
    }
};
