#include "player.h"
#include "mod/armor_rating_rescaled_remake.h"
#include "mod/blade_and_blunt.h"
#include "util/player/perkvisitor.h"
#include "util/type_util.h"

namespace util {
    float player::get_ammo_damage(RE::PlayerCharacter*& a_player) {
        if (const RE::TESAmmo* ammo = a_player->GetCurrentAmmo()) {
            logger::trace("ammo name {}"sv, ammo->GetName());
            return ammo->data.damage;
        }
        return {};
    }

    float player::get_weapon_damage(RE::PlayerCharacter*& a_player, bool a_left) {
        if (const auto hand = get_equipped_weapon(a_player, a_left)) {
            auto damage = a_player->GetDamage(hand);
            logger::trace("name {}, weapon damage {}, left {}"sv, hand->GetDisplayName(), damage, a_left);
            return damage;
        }
        return {};
    }

    float player::get_weapon_speed(RE::PlayerCharacter*& a_player, bool a_left) {
        if (const auto hand = get_equipped_weapon(a_player, a_left)) {
            auto speed = static_cast<RE::TESObjectWEAP*>(hand->object)->GetSpeed();
            logger::trace("name {}, weapon speed {}, left {}"sv, hand->GetDisplayName(), speed, a_left);
            return speed;
        }
        return {};
    }

    float player::get_weapon_reach(RE::PlayerCharacter*& a_player, bool a_left) {
        if (const auto hand = get_equipped_weapon(a_player, a_left)) {
            auto reach = static_cast<RE::TESObjectWEAP*>(hand->object)->GetReach();
            logger::trace("name {}, weapon reach {}, left {}"sv, hand->GetDisplayName(), reach, a_left);
            return reach;
        }
        return {};
    }

    float player::get_weapon_base_damage(RE::PlayerCharacter*& a_player, bool a_left) {
        if (const auto hand = get_equipped_weapon(a_player, a_left)) {
            auto base_damage = static_cast<RE::TESObjectWEAP*>(hand->object)->attackDamage;
            logger::trace("name {}, weapon base damage {}, left {}"sv, hand->GetDisplayName(), base_damage, a_left);
            return base_damage;
        }
        return {};
    }

    float player::get_weapon_stagger(RE::PlayerCharacter*& a_player, bool a_left) {
        if (const auto hand = get_equipped_weapon(a_player, a_left)) {
            auto stagger = static_cast<RE::TESObjectWEAP*>(hand->object)->GetStagger();
            logger::trace("name {}, weapon stagger {}, left {}"sv, hand->GetDisplayName(), stagger, a_left);
            return stagger;
        }
        return {};
    }

    float player::get_weapon_critical_damage(RE::PlayerCharacter*& a_player, bool a_left) {
        if (const auto hand = get_equipped_weapon(a_player, a_left)) {
            const auto [prcntMult, pad04, effect, damage, flags, pad13, pad14] =
                static_cast<RE::TESObjectWEAP*>(hand->object)->criticalData;
            auto critical_damage = prcntMult * damage;
            logger::trace("name {}, weapon critical damage {}, Left {}"sv,
                hand->GetDisplayName(),
                critical_damage,
                a_left);
            return critical_damage;
        }
        return {};
    }

    std::string player::get_xp(RE::PlayerCharacter*& a_player) {
        const auto data = a_player->GetInfoRuntimeData().skills->data;
        return util::type_util::format_with_delimiter(data->xp, data->levelThreshold, "/");
    }
    std::map<std::string, std::string_view> player::get_equipment(RE::PlayerCharacter*& a_player) {
        std::map<std::string, std::string_view> slot_map_string;

        for (const auto inventory =
                 a_player->GetInventory([](const RE::TESBoundObject& a_object) { return a_object.IsArmor(); });
             const auto& [item, inventory_data] : inventory) {
            if (const auto& [count, entry] = inventory_data; count > 0 && entry->IsWorn()) {
                const auto armor = item->As<RE::TESObjectARMO>();

                //magic enum
                logger::trace("Armor name {}, Slot {}"sv,
                    armor->GetName(),
                    magic_enum::enum_name(armor->GetSlotMask()));
                std::vector<int32_t> slot_list;
                for (auto slot_type : slot_type_list) {
                    if (static_cast<int32_t>(armor->GetSlotMask()) & static_cast<int32_t>(slot_type)) {
                        auto slot = get_slot_id_from_bit_mask(slot_type);
                        logger::trace("item has slot type {}, {}"sv, magic_enum::enum_name(slot_type), slot);
                        slot_list.push_back(static_cast<int32_t>(slot));
                    }
                }
                auto slot_string = util::type_util::get_delimited_string_from_vector(slot_list);
                slot_list.clear();
                if (!slot_string.empty()) {
                    slot_map_string[slot_string] = armor->GetName();
                }
            }
        }
        for (auto [slot, name] : slot_map_string) {
            logger::trace("{}: {}"sv, slot, name);
        }

        return slot_map_string;
    }

    float player::get_fall_damage_mod(RE::PlayerCharacter*& a_player) {
        if (a_player->HasPerkEntries(RE::BGSEntryPoint::ENTRY_POINTS::kModFallingDamage)) {
            auto perk_visit = util::perk_visitor();
            a_player->ForEachPerkEntry(RE::BGSEntryPoint::ENTRY_POINTS::kModFallingDamage, perk_visit);
            auto fall_damage_mod = perk_visit.get_result();
            logger::trace("perk visit got {} for falling damage"sv, fall_damage_mod);
            return fall_damage_mod;
        }
        return {};
    }

    float player::get_damage_resistance(RE::PlayerCharacter*& a_player) {
        auto inventory = a_player->GetInventory([](const RE::TESBoundObject& a_object) { return a_object.IsArmor(); });
        auto armor_count = 0;

        for (auto& [item, inventory_data] : inventory) {
            if (auto& [count, inventory_entry] = inventory_data; count > 0 && inventory_entry->IsWorn()) {
                if (auto* armor = item->As<RE::TESObjectARMO>();
                    armor->IsLightArmor() || armor->IsHeavyArmor() || armor->IsShield()) {
                    logger::trace("Armor name {}, Rating {}"sv, armor->GetName(), armor->GetArmorRating());
                    armor_count++;
                }
            }
        }

        auto armor_rating = a_player->AsActorValueOwner()->GetActorValue(RE::ActorValue::kDamageResist);
        //todo dragonhide handling
        return calculate_armor_damage_resistance(armor_rating, armor_count);
    }

    std::string player::get_is_beast(RE::PlayerCharacter*& a_player) {
        if (a_player->AsActorValueOwner()->GetActorValue(RE::ActorValue::kVampirePerks) > 0) {
            return static_cast<std::string>(menu_keys::vampire);
        }
        if (a_player->AsActorValueOwner()->GetActorValue(RE::ActorValue::kWerewolfPerks) > 0) {
            return static_cast<std::string>(menu_keys::werewolf);
        }

        return {};
    }


    RE::InventoryEntryData* player::get_equipped_weapon(RE::PlayerCharacter*& a_player, bool a_left) {
        auto* weapon = a_player->GetEquippedEntryData(a_left);
        if (weapon) {
            logger::trace("equipped item is {}, left {}"sv, weapon->GetDisplayName(), a_left);
        }
        return weapon;
    }

    double player::get_slot_id_from_bit_mask(RE::BIPED_MODEL::BipedObjectSlot a_armor_slot) {
        return std::log(static_cast<int32_t>(a_armor_slot)) / std::log1p(1) + 30;
    }

    float player::calculate_armor_damage_resistance(float a_armor_rating, int32_t a_pieces_worn) {
        const auto game_settings = setting::game_setting::get_singleton();

        if (mod::mod_manager::get_singleton()->get_armor_rating_rescaled_remake()) {
            return mod::armor_rating_rescaled_remake::calculate_armor_damage_resistance(a_armor_rating, a_pieces_worn);
        }

        if (mod::mod_manager::get_singleton()->get_blade_and_blunt()) {
            return mod::blade_and_blunt::calculate_armor_damage_resistance(a_armor_rating);
        }
        
        return a_armor_rating * game_settings->get_armor_scaling_factor() +
               game_settings->get_armor_base_factor() * 100 * a_pieces_worn;
    }

}  // util
