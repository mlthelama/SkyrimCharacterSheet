#pragma once

namespace util {
    class player {
    public:
        static float get_ammo_damage(RE::PlayerCharacter*& a_player);

        static float get_weapon_damage(RE::PlayerCharacter*& a_player, bool a_left);

        static float get_weapon_speed(RE::PlayerCharacter*& a_player, bool a_left);

        static float get_weapon_reach(RE::PlayerCharacter*& a_player, bool a_left);

        static float get_weapon_base_damage(RE::PlayerCharacter*& a_player, bool a_left);

        static float get_weapon_stagger(RE::PlayerCharacter*& a_player, bool a_left);

        static float get_weapon_critical_damage(RE::PlayerCharacter*& a_player, bool a_left);

        static std::string get_xp(RE::PlayerCharacter*& a_player);

        static std::map<std::string, std::string_view> get_equipment(RE::PlayerCharacter*& a_player);

        static float get_fall_damage_mod(RE::PlayerCharacter*& a_player);

        static float get_damage_resistance(RE::PlayerCharacter*& a_player);

        static std::string get_is_beast(RE::PlayerCharacter*& a_player);

    private:
        static RE::InventoryEntryData* get_equipped_weapon(RE::PlayerCharacter*& a_player, bool a_left);

        static double get_slot_id_from_bit_mask(RE::BIPED_MODEL::BipedObjectSlot a_armor_slot);

        static float calculate_armor_damage_resistance(float a_armor_rating, int32_t a_pieces_worn);

        inline static std::vector<RE::BIPED_MODEL::BipedObjectSlot> slot_type_list = {
            RE::BIPED_MODEL::BipedObjectSlot::kNone,
            RE::BIPED_MODEL::BipedObjectSlot::kHead,
            RE::BIPED_MODEL::BipedObjectSlot::kHair,
            RE::BIPED_MODEL::BipedObjectSlot::kBody,
            RE::BIPED_MODEL::BipedObjectSlot::kHands,
            RE::BIPED_MODEL::BipedObjectSlot::kForearms,
            RE::BIPED_MODEL::BipedObjectSlot::kAmulet,
            RE::BIPED_MODEL::BipedObjectSlot::kRing,
            RE::BIPED_MODEL::BipedObjectSlot::kFeet,
            RE::BIPED_MODEL::BipedObjectSlot::kCalves,
            RE::BIPED_MODEL::BipedObjectSlot::kShield,
            RE::BIPED_MODEL::BipedObjectSlot::kTail,
            RE::BIPED_MODEL::BipedObjectSlot::kLongHair,
            RE::BIPED_MODEL::BipedObjectSlot::kCirclet,
            RE::BIPED_MODEL::BipedObjectSlot::kEars,
            RE::BIPED_MODEL::BipedObjectSlot::kModMouth,
            RE::BIPED_MODEL::BipedObjectSlot::kModNeck,
            RE::BIPED_MODEL::BipedObjectSlot::kModChestPrimary,
            RE::BIPED_MODEL::BipedObjectSlot::kModBack,
            RE::BIPED_MODEL::BipedObjectSlot::kModMisc1,
            RE::BIPED_MODEL::BipedObjectSlot::kModPelvisPrimary,
            RE::BIPED_MODEL::BipedObjectSlot::kDecapitateHead,
            RE::BIPED_MODEL::BipedObjectSlot::kDecapitate,
            RE::BIPED_MODEL::BipedObjectSlot::kModPelvisSecondary,
            RE::BIPED_MODEL::BipedObjectSlot::kModLegRight,
            RE::BIPED_MODEL::BipedObjectSlot::kModLegLeft,
            RE::BIPED_MODEL::BipedObjectSlot::kModFaceJewelry,
            RE::BIPED_MODEL::BipedObjectSlot::kModChestSecondary,
            RE::BIPED_MODEL::BipedObjectSlot::kModShoulder,
            RE::BIPED_MODEL::BipedObjectSlot::kModArmLeft,
            RE::BIPED_MODEL::BipedObjectSlot::kModArmRight,
            RE::BIPED_MODEL::BipedObjectSlot::kModMisc2,
            RE::BIPED_MODEL::BipedObjectSlot::kFX01
        };
    };
}  // util
