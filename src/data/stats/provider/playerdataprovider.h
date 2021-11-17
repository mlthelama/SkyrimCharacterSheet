#pragma once

class PlayerDataProvider {
public:
    static std::string getBeast(float a_vamp, float a_were) {
        if (a_vamp > 0) {
            return *Settings::vampireString;
        } else if (a_were > 0) {
            return *Settings::werewolfString;
        }
        return "";
    }

    static std::string getArrowDamage(RE::PlayerCharacter*& a_player) {
        RE::InventoryEntryData* equip = a_player->GetEquippedEntryData(false);

        if (equip != nullptr) {
            if (equip->GetObject()->GetFormType() == RE::FormType::Ammo) {
                logger::trace("Item {} is arrow"sv, a_player->GetEquippedEntryData(false)->GetDisplayName());
                return StringUtil::getStringValueFromFloat(a_player->GetDamage(a_player->GetEquippedEntryData(false)));
            }
        }
        return "";
    }

    static std::string getDamage(RE::PlayerCharacter*& a_player, bool a_left) {
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

    static std::string handleWeaponSpeed(RE::PlayerCharacter*& a_player, bool a_left) {
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

    static std::string getXP(RE::PlayerCharacter*& a_player) {
        return fmt::format(FMT_STRING("{}/{}"),
            StringUtil::cutString(StringUtil::getStringValueFromFloat(a_player->skills->data->xp)),
            StringUtil::cutString(StringUtil::getStringValueFromFloat(a_player->skills->data->levelThreshold)));
    }

    /* might need additional checks for mods that add more items 
    * each light, heavy or shield gives 3% res + for some reason there is a 12 base res
    * formula would be ((totalArmorRating * 0.12) + (3 * piecesWorn));
    */
    static std::string getDamageResistance(RE::PlayerCharacter*& a_player, float a_cap, std::string a_ending) {
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

        auto damageResistance =
            ValueUtil::calculateArmorDamageRes(a_player->GetActorValue(RE::ActorValue::kDamageResist), armorCount);
        //auto dragonhide = getValueIfDragonhideIsAcitve(a_player);
        auto damageResistanceString = StringUtil::getStringValueFromFloat(damageResistance);
        logger::debug("Damage Resistance from Armor {}"sv, damageResistance);
        if (a_cap != -1) {
            damageResistanceString = ValueUtil::getValueWithCapIfNeeded(damageResistance, a_cap, a_ending);
        }

        return damageResistanceString;
    }

    static std::map<int32_t, std::string_view> getEquipment(RE::PlayerCharacter*& a_player) {
        //maybe chance to naming from int to a string
        std::map<int32_t, std::string_view> slotMap;

        const auto inv = a_player->GetInventory([](RE::TESBoundObject& a_object) { return (a_object.IsArmor()); });
        for (const auto& [item, invData] : inv) {
            const auto& [count, entry] = invData;
            if (count > 0 && entry->IsWorn()) {
                const auto armor = item->As<RE::TESObjectARMO>();
                /* if (armor->IsLightArmor() || armor->IsHeavyArmor() || armor->IsShield()) {
                    logger::trace("Armor name {}, Rating {}"sv, armor->GetName(), armor->GetArmorRating());
                }*/

                logger::trace("Armor name {}, Slot {}"sv, armor->GetName(), armor->GetSlotMask());

                for (auto slotType : slotTypes) {
                    //logger::trace("Checking for slotType {}"sv, slotType);
                    if (static_cast<int32_t>(armor->GetSlotMask()) & static_cast<int32_t>(slotType)) {
                        auto slot = getSlotidFromBitMask(slotType);
                        logger::trace("Item has slotType {}, {}"sv, slotType, slot);
                        slotMap[static_cast<int32_t>(slot)] = armor->GetName();
                    }
                }
            }
        }
        for (auto item : slotMap) { logger::trace("{}: {}"sv, item.first, item.second); }

        return slotMap;
    }

private:
    PlayerDataProvider() = default;
    PlayerDataProvider(const PlayerDataProvider&) = delete;
    PlayerDataProvider(PlayerDataProvider&&) = delete;

    ~PlayerDataProvider() = default;

    PlayerDataProvider& operator=(const PlayerDataProvider&) = delete;
    PlayerDataProvider& operator=(PlayerDataProvider&&) = delete;

    /* altered list from RE::BIPED_MODEL::BipedObjectSlot, to cover http://wiki.tesnexus.com/index.php/Skyrim_bodyparts_number */
    enum class ArmorSlot {
        kNone = 0,
        kHead = 1 << 0,
        kHair = 1 << 1,
        kBody = 1 << 2,
        kHands = 1 << 3,
        kForearms = 1 << 4,
        kAmulet = 1 << 5,
        kRing = 1 << 6,
        kFeet = 1 << 7,
        kCalves = 1 << 8,
        kShield = 1 << 9,
        kTail = 1 << 10,
        kLongHair = 1 << 11,
        kCirclet = 1 << 12,
        kEars = 1 << 13,
        kFaceMouth = 1 << 14,
        kNeck = 1 << 15,
        kChestPrimary = 1 << 16,
        kBack = 1 << 17,
        kMisc = 1 << 18,
        kPelvisPrimary = 1 << 19,
        kDecapitateHead = 1 << 20,
        kDecapitate = 1 << 21,
        kPelvisSecondary = 1 << 22,
        kLegPrimary = 1 << 23,
        kLegSecondary = 1 << 24,
        kFaceAlternate = 1 << 25,
        kChestSecondary = 1 << 26,
        kShoulder = 1 << 27,
        kArmSecondary = 1 << 28,
        kArmPrimary = 1 << 29,
        kMiscFX = 1 << 30,
        kFX01 = 1 << 31
    };

    inline static std::vector<ArmorSlot> slotTypes = { { ArmorSlot::kNone },
        { ArmorSlot::kHead },
        { ArmorSlot::kHair },
        { ArmorSlot::kBody },
        { ArmorSlot::kHands },
        { ArmorSlot::kForearms },
        { ArmorSlot::kAmulet },
        { ArmorSlot::kRing },
        { ArmorSlot::kFeet },
        { ArmorSlot::kCalves },
        { ArmorSlot::kShield },
        { ArmorSlot::kTail },
        { ArmorSlot::kLongHair },
        { ArmorSlot::kCirclet },
        { ArmorSlot::kEars },
        { ArmorSlot::kFaceMouth },
        { ArmorSlot::kNeck },
        { ArmorSlot::kChestPrimary },
        { ArmorSlot::kBack },
        { ArmorSlot::kMisc },
        { ArmorSlot::kPelvisPrimary },
        { ArmorSlot::kDecapitateHead },
        { ArmorSlot::kDecapitate },
        { ArmorSlot::kPelvisSecondary },
        { ArmorSlot::kLegPrimary },
        { ArmorSlot::kLegSecondary },
        { ArmorSlot::kFaceAlternate },
        { ArmorSlot::kChestSecondary },
        { ArmorSlot::kShoulder },
        { ArmorSlot::kArmSecondary },
        { ArmorSlot::kArmPrimary },
        { ArmorSlot::kMiscFX },
        { ArmorSlot::kFX01 } };

    static double getSlotidFromBitMask(ArmorSlot a_armor_slot) {
        return std::log(static_cast<int32_t>(a_armor_slot)) / 0.6931471805599453 + 30;
    }

    /* currently unused because unsure of calculation, it should be damageRes + ((100-damageRes)/(100/dragonhideValue))
    *  with the 80% cap it should be a total of 96% res
    */
    static float getValueIfDragonhideIsActive(RE::PlayerCharacter*& a_player) {
        auto effects = a_player->GetActiveEffectList();
        if (!effects) {
            return 0;
        }
        //a_player->currentProcess->middleHigh->activeEffects
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
