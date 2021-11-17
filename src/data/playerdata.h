#pragma once
#include "data/stats/provider/playerdataprovider.h"
#include "data/stats/statitem.h"
#include "settings/stats/statssettings.h"


class PlayerData {
    using StatsItemMap = std::map<StatsValue, std::unique_ptr<StatItem>>;
    using ShowMenu = MenuUtil::ShowMenu;
    using StatsInventoryMenuValue = MenuUtil::StatsInventoryMenuValue;
    using StatsMenuValue = MenuUtil::StatsMenuValue;
    using SlotArmorMap = std::map<int32_t, std::string_view>;

public:
    static PlayerData* GetSingleton() {
        static PlayerData singleton;
        return std::addressof(singleton);
    }

    StatsItemMap getValuesToDisplay(ShowMenu a_menu, std::string_view a_name) {
        logger::debug("Get Values to Display for Menu ({}) ..."sv, a_name);
        StatsItemMap simp;

        auto player = RE::PlayerCharacter::GetSingleton();

        auto statSettingMap = StatSetting::GetSingleton()->load();
        logger::debug("Config Map Size is {}"sv, statSettingMap.size());

        for (auto& element : statSettingMap) {
            auto statValue = element.first;
            auto statConfig = element.second.get();

            statConfig->logStatConfig(statValue);

            if ((a_menu == ShowMenu::mStats && statConfig->getStatsMenu() == StatsMenuValue::mNone) ||
                (a_menu == ShowMenu::mStatsInventory &&
                    statConfig->getStatsInventoryMenu() == StatsInventoryMenuValue::mNone)) {
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
                case StatsValue::skillTrainingsThisLevel:
                    valueText = std::to_string(player->skillTrainingsThisLevel);
                    break;
                case StatsValue::damageArrow:
                    valueText = PlayerDataProvider::getArrowDamage(player);
                    break;
                case StatsValue::damage:
                    valueText = PlayerDataProvider::getDamage(player, false);
                    break;
                case StatsValue::damageLeft:
                    valueText = PlayerDataProvider::getDamage(player, true);
                    break;
                case StatsValue::beast:
                    valueText = PlayerDataProvider::getBeast(player->GetActorValue(RE::ActorValue::kVampirePerks),
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
                    valueText = PlayerDataProvider::getXP(player);
                    break;
                case StatsValue::weight:
                    valueText = StringUtil::getStringValueFromFloat(player->GetWeight());
                    break;
                case StatsValue::weaponSpeedMult:
                    valueText = PlayerDataProvider::handleWeaponSpeed(player, false);
                    break;
                case StatsValue::leftWeaponSpeedMult:
                    valueText = PlayerDataProvider::handleWeaponSpeed(player, true);
                    break;
                case StatsValue::resistDamage:
                    valueText =
                        PlayerDataProvider::getDamageResistance(player, statConfig->getCap(), statConfig->getEnding());
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

            if (valueText == "") {
                continue;
            }

            if ((!*Settings::showStatsInventorydisplayZero && valueText == "0" &&
                    a_menu == ShowMenu::mStatsInventory) ||
                (!*Settings::showStatsdisplayZero && valueText == "0" && a_menu == ShowMenu::mStats)) {
                continue;
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
            a_name);

        return simp;
    }

    SlotArmorMap getArmorMap() {
        auto player = RE::PlayerCharacter::GetSingleton();
        return PlayerDataProvider::getEquipment(player);
    }

private:
    PlayerData() = default;
    PlayerData(const PlayerData&) = delete;
    PlayerData(PlayerData&&) = delete;

    ~PlayerData() = default;

    PlayerData& operator=(const PlayerData&) = delete;
    PlayerData& operator=(PlayerData&&) = delete;
};
