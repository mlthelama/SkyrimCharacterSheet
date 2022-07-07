#pragma once
#include "utils/perkvisitor.h"

class player_data_provider {
public:
    static std::string get_beast(const float a_vamp, const float a_were) {
        if (a_vamp > 0) {
            return *settings::vampireString;
        }
        if (a_were > 0) {
            return *settings::werewolfString;
        }
        return "";
    }

    static std::string get_arrow_damage(RE::PlayerCharacter*& a_player) {
        if (const RE::TESAmmo* ammo = a_player->GetCurrentAmmo()) {
            logger::trace("Item {} is arrow"sv, ammo->GetName());
            return string_util::get_string_value_from_float(ammo->data.damage);
        }
        return "";
    }

    static std::string get_damage(RE::PlayerCharacter*& a_player, bool a_left) {
        float damage = -1;
        if (const auto hand = get_equipped_weapon(a_player, a_left)) {
            damage = a_player->GetDamage(hand);
            logger::trace("Name {}, WeaponDamage {}, Left {}"sv, hand->GetDisplayName(), damage, a_left);
        }
        return (damage == -1) ? "" : string_util::get_string_value_from_float(damage);
    }

    static std::string handle_weapon_speed(RE::PlayerCharacter*& a_player, bool a_left) {
        float speed = -1;

        //could also get other weapon stats that way
        if (const auto hand = get_equipped_weapon(a_player, a_left)) {
            speed = static_cast<RE::TESObjectWEAP*>(hand->object)->GetSpeed();
            logger::trace("Name {}, WeaponSpeed {}, Left {}"sv, hand->GetDisplayName(), speed, a_left);
        }
        return (speed == -1) ? "" : string_util::get_string_value_from_float(speed);
    }

    static std::string handle_weapon_reach(RE::PlayerCharacter*& a_player, bool a_left) {
        float reach = -1;
        if (const auto hand = get_equipped_weapon(a_player, a_left)) {
            reach = static_cast<RE::TESObjectWEAP*>(hand->object)->GetReach();
            logger::trace("Name {}, WeaponReach {}, Left {}"sv, hand->GetDisplayName(), reach, a_left);
        }
        return (reach == -1) ? "" : string_util::get_string_value_from_float(reach);
    }

    static std::string handle_weapon_base_damage(RE::PlayerCharacter*& a_player, bool a_left) {
        float base_damage = -1;
        if (const auto hand = get_equipped_weapon(a_player, a_left)) {
            base_damage = static_cast<RE::TESObjectWEAP*>(hand->object)->attackDamage;
            logger::trace("Name {}, WeaponBaseDamage {}, Left {}"sv, hand->GetDisplayName(), base_damage, a_left);
        }
        return (base_damage == -1) ? "" : string_util::get_string_value_from_float(base_damage);
    }

    static std::string handle_weapon_stagger(RE::PlayerCharacter*& a_player, bool a_left) {
        float stagger = -1;
        if (const auto hand = get_equipped_weapon(a_player, a_left)) {
            stagger = static_cast<RE::TESObjectWEAP*>(hand->object)->GetStagger();
            logger::trace("Name {}, WeaponStagger {}, Left {}"sv, hand->GetDisplayName(), stagger, a_left);
        }
        return (stagger == -1) ? "" : string_util::get_string_value_from_float(stagger);
    }

    static std::string handle_weapon_crit(RE::PlayerCharacter*& a_player, bool a_left) {
        float crit = -1;
        if (const auto hand = get_equipped_weapon(a_player, a_left)) {
            const auto [prcntMult, pad04, effect, damage, flags, pad13, pad14] =
                static_cast<RE::TESObjectWEAP*>(hand->object)->criticalData;
            crit = prcntMult * damage;
            logger::trace("Name {}, WeaponCritDamageRating {}, Left {}"sv, hand->GetDisplayName(), crit, a_left);
        }
        return (crit == -1) ? "" : string_util::get_string_value_from_float(crit);
    }

    static std::string get_xp(RE::PlayerCharacter*& a_player) {
        return string_util::delimit_two_values(a_player->skills->data->xp,
            a_player->skills->data->levelThreshold,
            const_delimiter);
    }

    /* might need additional checks for mods that add more items 
    * each light, heavy or shield gives 3% res + for some reason there is a 12 base res
    * formula would be ((totalArmorRating * 0.12) + (3 * piecesWorn));
    * the 3% is provided by fArmorBaseFactor
    */
    static std::string
        get_damage_resistance(RE::PlayerCharacter*& a_player, const float a_cap, const std::string& a_ending) {
        const auto inv = a_player->GetInventory([](const RE::TESBoundObject& a_object) { return a_object.IsArmor(); });
        auto armor_count = 0;
        for (const auto& [item, invData] : inv) {
            if (const auto& [count, entry] = invData; count > 0 && entry->IsWorn()) {
                /* clothing does not count torwards reduction
                *  as stated here http://en.uesp.net/wiki/Skyrim:Armor#Armor_Rating
                */
                if (const auto armor = item->As<RE::TESObjectARMO>();
                    armor->IsLightArmor() || armor->IsHeavyArmor() || armor->IsShield()) {
                    logger::trace("Armor name {}, Rating {}"sv, armor->GetName(), armor->GetArmorRating());
                    armor_count++;
                }
            }
        }

        auto damage_resistance =
            value_util::calculate_armor_damage_res(a_player->GetActorValue(RE::ActorValue::kDamageResist), armor_count);
        //auto dragonhide = getValueIfDragonhideIsAcitve(a_player);
        auto damage_resistance_string = string_util::get_string_value_from_float(damage_resistance);
        logger::debug("Damage Resistance from Armor {}"sv, damage_resistance);
        if (a_cap != -1) {
            damage_resistance_string = value_util::get_value_with_cap_if_needed(damage_resistance, a_cap, a_ending);
        }
        return damage_resistance_string;
    }

    static std::map<std::string, std::string_view> get_equipment(RE::PlayerCharacter*& a_player) {
        //maybe chance to naming from int to a string
        std::map<std::string, std::string_view> slot_map_string;

        for (const auto inv =
                 a_player->GetInventory([](const RE::TESBoundObject& a_object) { return (a_object.IsArmor()); });
             const auto& [item, invData] : inv) {
            if (const auto& [count, entry] = invData; count > 0 && entry->IsWorn()) {
                const auto armor = item->As<RE::TESObjectARMO>();

                logger::trace("Armor name {}, Slot {}"sv, armor->GetName(), armor->GetSlotMask());
                std::vector<int32_t> slot_list;
                for (auto slot_type : slot_types_) {
                    if (static_cast<int32_t>(armor->GetSlotMask()) & static_cast<int32_t>(slot_type)) {
                        auto slot = get_slotid_from_bit_mask(slot_type);
                        logger::trace("Item has slotType {}, {}"sv, slot_type, slot);
                        slot_list.push_back(static_cast<int32_t>(slot));
                    }
                }
                auto slot_string = vector_util::getDelimitedString(slot_list);
                slot_list.clear();
                if (!slot_string.empty()) {
                    slot_map_string[slot_string] = armor->GetName();
                }
            }
        }
        for (auto [fst, snd] : slot_map_string) { logger::trace("{}: {}"sv, fst, snd); }

        return slot_map_string;
    }

    //kModSneakAttackMult should work with that as well
    //kModPlayerIntimidation
    //kModEnchantmentPower
    // maybe some more
    static float get_fall_damage_mod(RE::PlayerCharacter*& a_player) {
        float fall_damage_mod = 0;
        if (a_player->HasPerkEntries(RE::BGSEntryPoint::ENTRY_POINTS::kModFallingDamage)) {
            auto perk_visit = perk_visiter(a_player);
            a_player->ForEachPerkEntry(RE::BGSEntryPoint::ENTRY_POINTS::kModFallingDamage, perk_visit);
            fall_damage_mod = perk_visit.get_result();
            logger::trace("perk visit got {} for FallingDamage"sv, fall_damage_mod);
        }

        return fall_damage_mod;
    }

    player_data_provider(const player_data_provider&) = delete;
    player_data_provider(player_data_provider&&) = delete;

    player_data_provider& operator=(const player_data_provider&) = delete;
    player_data_provider& operator=(player_data_provider&&) = delete;

private:
    player_data_provider() = default;

    ~player_data_provider() = default;

    /* altered list from RE::BIPED_MODEL::BipedObjectSlot, to cover http://wiki.tesnexus.com/index.php/Skyrim_bodyparts_number */
    enum class armor_slot {
        k_none = 0,
        k_head = 1 << 0,
        k_hair = 1 << 1,
        k_body = 1 << 2,
        k_hands = 1 << 3,
        k_forearms = 1 << 4,
        k_amulet = 1 << 5,
        k_ring = 1 << 6,
        k_feet = 1 << 7,
        k_calves = 1 << 8,
        k_shield = 1 << 9,
        k_tail = 1 << 10,
        k_long_hair = 1 << 11,
        k_circlet = 1 << 12,
        k_ears = 1 << 13,
        k_face_mouth = 1 << 14,
        k_neck = 1 << 15,
        k_chest_primary = 1 << 16,
        k_back = 1 << 17,
        k_misc = 1 << 18,
        k_pelvis_primary = 1 << 19,
        k_decapitate_head = 1 << 20,
        k_decapitate = 1 << 21,
        k_pelvis_secondary = 1 << 22,
        k_leg_primary = 1 << 23,
        k_leg_secondary = 1 << 24,
        k_face_alternate = 1 << 25,
        k_chest_secondary = 1 << 26,
        k_shoulder = 1 << 27,
        k_arm_secondary = 1 << 28,
        k_arm_primary = 1 << 29,
        k_misc_fx = 1 << 30,
        k_fx01 = 1 << 31
    };

    inline static std::vector<armor_slot> slot_types_ = { armor_slot::k_none,
                                                          armor_slot::k_head,
                                                          armor_slot::k_hair,
                                                          armor_slot::k_body,
                                                          armor_slot::k_hands,
                                                          armor_slot::k_forearms,
                                                          armor_slot::k_amulet,
                                                          armor_slot::k_ring,
                                                          armor_slot::k_feet,
                                                          armor_slot::k_calves,
                                                          armor_slot::k_shield,
                                                          armor_slot::k_tail,
                                                          armor_slot::k_long_hair,
                                                          armor_slot::k_circlet,
                                                          armor_slot::k_ears,
                                                          armor_slot::k_face_mouth,
                                                          armor_slot::k_neck,
                                                          armor_slot::k_chest_primary,
                                                          armor_slot::k_back,
                                                          armor_slot::k_misc,
                                                          armor_slot::k_pelvis_primary,
                                                          armor_slot::k_decapitate_head,
                                                          armor_slot::k_decapitate,
                                                          armor_slot::k_pelvis_secondary,
                                                          armor_slot::k_leg_primary,
                                                          armor_slot::k_leg_secondary,
                                                          armor_slot::k_face_alternate,
                                                          armor_slot::k_chest_secondary,
                                                          armor_slot::k_shoulder,
                                                          armor_slot::k_arm_secondary,
                                                          armor_slot::k_arm_primary,
                                                          armor_slot::k_misc_fx,
                                                          armor_slot::k_fx01 };

    static double get_slotid_from_bit_mask(armor_slot a_armor_slot) {
        return std::log(static_cast<int32_t>(a_armor_slot)) / std::log1p(1) + 30;
    }

    /* currently unused because unsure of calculation, it should be damageRes + ((100-damageRes)/(100/dragonhideValue))
    *  with the 80% cap it should be a total of 96% res
    */
    static float get_value_if_dragonhide_is_active(RE::PlayerCharacter*& a_player) {
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
                    logger::debug("Is Armor Spell {}, magnitude {}, formid {}"sv,
                        effect->GetBaseObject()->GetName(),
                        effect->magnitude,
                        string_util::int_to_hex(formid));
                    return effect->magnitude;
                }
            }
        }
        return 0;
    }

    static RE::InventoryEntryData* get_equipped_weapon(RE::PlayerCharacter*& a_player, bool a_left) {
        RE::InventoryEntryData* weapon;
        if (a_left) {
            weapon = a_player->currentProcess->middleHigh->leftHand;
        } else {
            weapon = a_player->currentProcess->middleHigh->rightHand;
        }

        if (weapon) {
            logger::trace("Equipped Item is {}, left {}"sv, weapon->GetDisplayName(), a_left);
        }
        return weapon;
    }
};
