#pragma once
#include "settings/gamesettings.h"
#include "utils/utils.h"

class stat_config {
    using stats_inventory_menu_value = menu_util::stats_inventory_menu_value;
    using stats_menu_value = menu_util::stats_menu_value;

public:
    stat_config(const RE::ActorValue a_actor,
        std::string a_display_name,
        const stats_menu_value a_stats_menu,
        const stats_inventory_menu_value a_stats_inventory_menu)
        : actor_(a_actor)
        , display_name_(std::move(a_display_name))
        , stats_menu_(a_stats_menu)
        , stats_inventory_menu_(a_stats_inventory_menu) {}

    stat_config(const RE::ActorValue a_actor,
        std::string a_display_name,
        std::string a_ending,
        const stats_menu_value a_stats_menu,
        const stats_inventory_menu_value a_stats_inventory_menu)
        : actor_(a_actor)
        , display_name_(std::move(a_display_name))
        , ending_(std::move(a_ending))
        , stats_menu_(a_stats_menu)
        , stats_inventory_menu_(a_stats_inventory_menu) {}

    stat_config(const RE::ActorValue a_actor,
        std::string a_display_name,
        std::string a_ending,
        const stats_menu_value a_stats_menu,
        const stats_inventory_menu_value a_stats_inventory_menu,
        const int64_t a_value_multiplier)
        : actor_(a_actor)
        , display_name_(std::move(a_display_name))
        , ending_(std::move(a_ending))
        , stats_menu_(a_stats_menu)
        , stats_inventory_menu_(a_stats_inventory_menu)
        , value_multiplier_(a_value_multiplier) {}

    stat_config(const RE::ActorValue a_actor,
        std::string a_display_name,
        std::string a_ending,
        const stats_menu_value a_stats_menu,
        const stats_inventory_menu_value a_stats_inventory_menu,
        const int64_t a_value_multiplier,
        const float a_cap)
        : actor_(a_actor)
        , display_name_(std::move(a_display_name))
        , ending_(std::move(a_ending))
        , stats_menu_(a_stats_menu)
        , stats_inventory_menu_(a_stats_inventory_menu)
        , value_multiplier_(a_value_multiplier)
        , cap_(a_cap) {}

    stat_config(const RE::ActorValue a_actor,
        std::string a_display_name,
        const stats_menu_value a_stats_menu,
        const stats_inventory_menu_value a_stats_inventory_menu,
        const bool a_perm_av)
        : actor_(a_actor)
        , display_name_(std::move(a_display_name))
        , stats_menu_(a_stats_menu)
        , stats_inventory_menu_(a_stats_inventory_menu)
        , show_perm_av_(a_perm_av) {}

    [[nodiscard]] RE::ActorValue get_actor() const { return actor_; }

    std::string get_display_name() { return display_name_; }

    std::string get_ending() { return ending_; }

    [[nodiscard]] stats_menu_value get_stats_menu() const { return stats_menu_; }

    [[nodiscard]] stats_inventory_menu_value get_stats_inventory_menu() const { return stats_inventory_menu_; }

    [[nodiscard]] int64_t get_value_multiplier() const { return value_multiplier_; }

    [[nodiscard]] float get_cap() const { return cap_; }

    [[nodiscard]] bool get_show_perm_av() const { return show_perm_av_; }

    std::string get_display(const std::string& a_value) {
        if (!a_value.empty()) {
            logger::trace("display {} got value {}, building text ..."sv, display_name_, a_value);
            return menu_util::build_display_string(a_value, display_name_, ending_, false);
        }
        return "";
    }

    void log_stat_config(stats_value a_stats_value) {
        logger::trace(
            "name {}, actor {}, displayName ({}), ending {}, statsMenu {}, statsInventoryMenu {}, valueMultiplier {}, cap {}, showPermAV {}"sv,
            a_stats_value,
            actor_,
            display_name_,
            ending_,
            stats_menu_,
            stats_inventory_menu_,
            value_multiplier_,
            cap_,
            show_perm_av_);
    }

    stat_config() = delete;
    stat_config(const stat_config&) = default;
    stat_config(stat_config&&) = delete;

    ~stat_config() = default;

    stat_config& operator=(const stat_config&) = default;
    stat_config& operator=(stat_config&&) = delete;

private:
    RE::ActorValue actor_;
    std::string display_name_;
    std::string ending_;
    stats_menu_value stats_menu_;
    stats_inventory_menu_value stats_inventory_menu_;
    int64_t value_multiplier_ = const_static_multiplier;
    float cap_ = -1;
    bool show_perm_av_ = false;
};


class stat_setting {
    using stats_map = std::map<stats_value, std::unique_ptr<stat_config>>;
    using actor_value = RE::ActorValue;
    using stats_inventory_menu_value = menu_util::stats_inventory_menu_value;
    using stats_menu_value = menu_util::stats_menu_value;

public:
    static stat_setting* get_singleton() {
        static stat_setting singleton;
        return std::addressof(singleton);
    }

    [[nodiscard]] stats_map load() const {
        stats_map mp;

        const auto game_settings = game_settings::get_singleton();
        if (*settings::show_resistance_cap) {
            game_settings->get_and_set_settings();
        }

        mp[stats_value::name] = std::make_unique<stat_config>(actor_value::kNone,
            *settings::name_string,
            stats_menu_value::m_special,
            stats_inventory_menu_value::m_none);
        mp[stats_value::race] = std::make_unique<stat_config>(actor_value::kNone,
            *settings::race_string,
            stats_menu_value::m_special,
            stats_inventory_menu_value::m_none);
        mp[stats_value::level] = std::make_unique<stat_config>(actor_value::kNone,
            *settings::level_string,
            stats_menu_value::m_special,
            stats_inventory_menu_value::m_none);
        mp[stats_value::perk_count] = std::make_unique<stat_config>(actor_value::kNone,
            *settings::perk_count_string,
            stats_menu_value::m_special,
            stats_inventory_menu_value::m_none);
        mp[stats_value::height] = std::make_unique<stat_config>(actor_value::kNone,
            *settings::height_string,
            *settings::heightStringEnding,
            menu_util::get_stats_menu(*settings::height_menu),
            stats_inventory_menu_value::m_none);
        mp[stats_value::equipped_weight] = std::make_unique<stat_config>(actor_value::kNone,
            *settings::equipped_weight_string,
            *settings::equipedWeightStringEnding,
            menu_util::get_stats_menu(*settings::equiped_weight_menu),
            menu_util::get_stats_inventory_menu(*settings::equiped_weight_menu_inventory));
        mp[stats_value::weight] = std::make_unique<stat_config>(actor_value::kNone,
            *settings::weight_string,
            *settings::weightStringEnding,
            menu_util::get_stats_menu(*settings::weight_menu),
            stats_inventory_menu_value::m_none);
        mp[stats_value::armor] = std::make_unique<stat_config>(actor_value::kDamageResist,
            *settings::armor_string,
            menu_util::get_stats_menu(*settings::armor_menu),
            menu_util::get_stats_inventory_menu(*settings::armor_menu_inventory));
        mp[stats_value::damage] = std::make_unique<stat_config>(actor_value::kNone,
            *settings::damage_string,
            menu_util::get_stats_menu(*settings::damage_menu),
            menu_util::get_stats_inventory_menu(*settings::damage_menu_inventory));
        mp[stats_value::skill_trainings_this_level] = std::make_unique<stat_config>(actor_value::kNone,
            *settings::skill_trainings_this_level_string,
            menu_util::get_stats_menu(*settings::skill_trainings_this_level_menu),
            stats_inventory_menu_value::m_none);
        mp[stats_value::health] = std::make_unique<stat_config>(actor_value::kHealth,
            *settings::health_string,
            menu_util::get_stats_menu(*settings::health_menu),
            menu_util::get_stats_inventory_menu(*settings::health_menu_inventory),
            *settings::display_permanent_av);
        mp[stats_value::health_rate_per] = std::make_unique<stat_config>(actor_value::kNone,
            *settings::health_rate_string,
            *settings::healthRateStringEnding,
            menu_util::get_stats_menu(*settings::health_rate_menu),
            menu_util::get_stats_inventory_menu(*settings::health_rate_menu_inventory));
        mp[stats_value::magicka] = std::make_unique<stat_config>(actor_value::kMagicka,
            *settings::magicka_string,
            menu_util::get_stats_menu(*settings::magicka_menu),
            menu_util::get_stats_inventory_menu(*settings::magicka_menu_inventory),
            *settings::display_permanent_av);
        mp[stats_value::magicka_rate_per] = std::make_unique<stat_config>(actor_value::kNone,
            *settings::magicka_rate_string,
            *settings::magickaRateStringEnding,
            menu_util::get_stats_menu(*settings::magicka_rate_menu),
            menu_util::get_stats_inventory_menu(*settings::magicka_rate_menu_inventory));
        mp[stats_value::stamina] = std::make_unique<stat_config>(actor_value::kStamina,
            *settings::stamina_string,
            menu_util::get_stats_menu(*settings::stamina_menu),
            menu_util::get_stats_inventory_menu(*settings::magicka_rate_menu_inventory),
            *settings::display_permanent_av);
        mp[stats_value::stamina_rate_per] = std::make_unique<stat_config>(actor_value::kNone,
            *settings::stamina_rate_string,
            *settings::staminaRateStringEnding,
            menu_util::get_stats_menu(*settings::stamina_rate_menu),
            menu_util::get_stats_inventory_menu(*settings::stamina_menu_inventory));
        mp[stats_value::resist_damage] = std::make_unique<stat_config>(actor_value::kNone,
            *settings::resist_damage_string,
            *settings::resistDamageStringEnding,
            menu_util::get_stats_menu(*settings::resist_damage_menu),
            menu_util::get_stats_inventory_menu(*settings::resist_damage_menu_inventory),
            const_static_multiplier,
            game_settings->max_armor_resistance);
        mp[stats_value::resist_disease] = std::make_unique<stat_config>(actor_value::kResistDisease,
            *settings::resistDiseaseString,
            *settings::resistDiseaseStringEnding,
            menu_util::get_stats_menu(*settings::resist_disease_menu),
            menu_util::get_stats_inventory_menu(*settings::resist_disease_menu_inventory));
        mp[stats_value::resist_poison] = std::make_unique<stat_config>(actor_value::kPoisonResist,
            *settings::resistPoisonString,
            *settings::resistPoisonStringEnding,
            menu_util::get_stats_menu(*settings::resist_poison_menu),
            menu_util::get_stats_inventory_menu(*settings::resist_poison_menu_inventory),
            const_static_multiplier,
            game_settings->max_resistance);
        mp[stats_value::resist_fire] = std::make_unique<stat_config>(actor_value::kResistFire,
            *settings::resistFireString,
            *settings::resistFireStringEnding,
            menu_util::get_stats_menu(*settings::resist_fire_menu),
            menu_util::get_stats_inventory_menu(*settings::resist_fire_menu_inventory),
            const_static_multiplier,
            game_settings->max_resistance);
        mp[stats_value::resist_shock] = std::make_unique<stat_config>(actor_value::kResistShock,
            *settings::resistShockString,
            *settings::resistShockStringEnding,
            menu_util::get_stats_menu(*settings::resist_shock_menu),
            menu_util::get_stats_inventory_menu(*settings::resist_shock_menu_inventory),
            const_static_multiplier,
            game_settings->max_resistance);
        mp[stats_value::resist_frost] = std::make_unique<stat_config>(actor_value::kResistFrost,
            *settings::resistFrostString,
            *settings::resistFrostStringEnding,
            menu_util::get_stats_menu(*settings::resist_frost_menu),
            menu_util::get_stats_inventory_menu(*settings::resist_frost_menu_inventory),
            const_static_multiplier,
            game_settings->max_resistance);
        mp[stats_value::resist_magic] = std::make_unique<stat_config>(actor_value::kResistMagic,
            *settings::resistMagicString,
            *settings::resistMagicStringEnding,
            menu_util::get_stats_menu(*settings::resist_magic_menu),
            menu_util::get_stats_inventory_menu(*settings::resist_magic_menu_inventory),
            const_static_multiplier,
            game_settings->max_resistance);
        mp[stats_value::one_handed] = std::make_unique<stat_config>(actor_value::kOneHanded,
            *settings::oneHandedString,
            menu_util::get_stats_menu(*settings::one_handed_menu),
            menu_util::get_stats_inventory_menu(*settings::one_handed_menu_inventory),
            *settings::display_permanent_av);
        mp[stats_value::two_handed] = std::make_unique<stat_config>(actor_value::kTwoHanded,
            *settings::twoHandedString,
            menu_util::get_stats_menu(*settings::two_handed_menu),
            menu_util::get_stats_inventory_menu(*settings::two_handed_menu_inventory),
            *settings::display_permanent_av);
        mp[stats_value::archery] = std::make_unique<stat_config>(actor_value::kArchery,
            *settings::archeryString,
            menu_util::get_stats_menu(*settings::archery_menu),
            menu_util::get_stats_inventory_menu(*settings::archery_menu_inventory),
            *settings::display_permanent_av);
        mp[stats_value::block] = std::make_unique<stat_config>(actor_value::kBlock,
            *settings::blockString,
            menu_util::get_stats_menu(*settings::block_menu),
            menu_util::get_stats_inventory_menu(*settings::block_menu_inventory),
            *settings::display_permanent_av);
        mp[stats_value::smithing] = std::make_unique<stat_config>(actor_value::kSmithing,
            *settings::smithingString,
            menu_util::get_stats_menu(*settings::smithing_menu),
            menu_util::get_stats_inventory_menu(*settings::smithing_menu_inventory),
            *settings::display_permanent_av);
        mp[stats_value::heavy_armor] = std::make_unique<stat_config>(actor_value::kHeavyArmor,
            *settings::heavyArmorString,
            menu_util::get_stats_menu(*settings::heavy_armor_menu),
            menu_util::get_stats_inventory_menu(*settings::heavy_armor_menu_inventory),
            *settings::display_permanent_av);
        mp[stats_value::light_armor] = std::make_unique<stat_config>(actor_value::kLightArmor,
            *settings::lightArmorString,
            menu_util::get_stats_menu(*settings::light_armor_menu),
            menu_util::get_stats_inventory_menu(*settings::light_armor_menu_inventory),
            *settings::display_permanent_av);
        mp[stats_value::pickpocket] = std::make_unique<stat_config>(actor_value::kPickpocket,
            *settings::pickpocketString,
            menu_util::get_stats_menu(*settings::pickpocket_menu),
            menu_util::get_stats_inventory_menu(*settings::pickpocket_menu_inventory),
            *settings::display_permanent_av);
        mp[stats_value::lockpicking] = std::make_unique<stat_config>(actor_value::kLockpicking,
            *settings::lockpickingString,
            menu_util::get_stats_menu(*settings::lockpicking_menu),
            menu_util::get_stats_inventory_menu(*settings::lockpicking_menu_inventory),
            *settings::display_permanent_av);
        mp[stats_value::sneak] = std::make_unique<stat_config>(actor_value::kSneak,
            *settings::sneakString,
            menu_util::get_stats_menu(*settings::sneak_menu),
            menu_util::get_stats_inventory_menu(*settings::sneak_menu_inventory),
            *settings::display_permanent_av);
        mp[stats_value::alchemy] = std::make_unique<stat_config>(actor_value::kAlchemy,
            *settings::alchemyString,
            menu_util::get_stats_menu(*settings::alchemy_menu),
            menu_util::get_stats_inventory_menu(*settings::alchemy_menu_inventory),
            *settings::display_permanent_av);
        mp[stats_value::speech] = std::make_unique<stat_config>(actor_value::kSpeech,
            *settings::speechString,
            menu_util::get_stats_menu(*settings::speech_menu),
            menu_util::get_stats_inventory_menu(*settings::speech_menu_inventory),
            *settings::display_permanent_av);
        mp[stats_value::enchanting] = std::make_unique<stat_config>(actor_value::kEnchanting,
            *settings::enchantingString,
            menu_util::get_stats_menu(*settings::enchanting_menu),
            menu_util::get_stats_inventory_menu(*settings::enchanting_menu_inventory),
            *settings::display_permanent_av);
        mp[stats_value::alteration] = std::make_unique<stat_config>(actor_value::kAlteration,
            *settings::alterationString,
            menu_util::get_stats_menu(*settings::alteration_menu),
            menu_util::get_stats_inventory_menu(*settings::alteration_menu_inventory),
            *settings::display_permanent_av);
        mp[stats_value::conjuration] = std::make_unique<stat_config>(actor_value::kConjuration,
            *settings::conjurationString,
            menu_util::get_stats_menu(*settings::conjuration_menu),
            menu_util::get_stats_inventory_menu(*settings::conjuration_menu_inventory),
            *settings::display_permanent_av);
        mp[stats_value::destruction] = std::make_unique<stat_config>(actor_value::kDestruction,
            *settings::destructionString,
            menu_util::get_stats_menu(*settings::destruction_menu),
            menu_util::get_stats_inventory_menu(*settings::destruction_menu_inventory),
            *settings::display_permanent_av);
        mp[stats_value::illusion] = std::make_unique<stat_config>(actor_value::kIllusion,
            *settings::illusionString,
            menu_util::get_stats_menu(*settings::illusion_menu),
            menu_util::get_stats_inventory_menu(*settings::illusion_menu_inventory),
            *settings::display_permanent_av);
        mp[stats_value::restoration] = std::make_unique<stat_config>(actor_value::kRestoration,
            *settings::restorationString,
            menu_util::get_stats_menu(*settings::restoration_menu),
            menu_util::get_stats_inventory_menu(*settings::restoration_menu_inventory),
            *settings::display_permanent_av);
        mp[stats_value::one_handed_power_mod] = std::make_unique<stat_config>(actor_value::kOneHandedPowerModifier,
            *settings::oneHandedPowerModString,
            menu_util::get_stats_menu(*settings::one_handed_power_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::one_handed_power_mod_menu_inventory));
        mp[stats_value::two_handed_power_mod] = std::make_unique<stat_config>(actor_value::kTwoHandedPowerModifier,
            *settings::twoHandedPowerModString,
            menu_util::get_stats_menu(*settings::two_handed_power_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::two_handed_power_mod_menu_inventory));
        mp[stats_value::archery_power_mod] = std::make_unique<stat_config>(actor_value::kMarksmanPowerModifier,
            *settings::archeryPowerModString,
            menu_util::get_stats_menu(*settings::archery_power_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::archery_power_mod_menu_inventory));
        mp[stats_value::block_power_mod] = std::make_unique<stat_config>(actor_value::kBlockPowerModifier,
            *settings::blockPowerModString,
            menu_util::get_stats_menu(*settings::block_power_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::block_power_mod_menu_inventory));
        mp[stats_value::smithing_power_mod] = std::make_unique<stat_config>(actor_value::kSmithingPowerModifier,
            *settings::smithingPowerModString,
            menu_util::get_stats_menu(*settings::smithing_power_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::smithing_power_mod_menu_inventory));
        mp[stats_value::heavy_armor_power_mod] = std::make_unique<stat_config>(actor_value::kHeavyArmorPowerModifier,
            *settings::heavyArmorPowerModString,
            menu_util::get_stats_menu(*settings::heavy_armor_power_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::heavy_armor_power_mod_menu_inventory));
        mp[stats_value::light_armor_power_mod] = std::make_unique<stat_config>(actor_value::kLightArmorPowerModifier,
            *settings::lightArmorPowerModString,
            menu_util::get_stats_menu(*settings::light_armor_power_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::light_armor_power_mod_menu_inventory));
        mp[stats_value::pickpocket_power_mod] = std::make_unique<stat_config>(actor_value::kPickpocketPowerModifier,
            *settings::pickpocketPowerModString,
            menu_util::get_stats_menu(*settings::pickpocket_power_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::pickpocket_power_mod_menu_inventory));
        mp[stats_value::lockpickingPowerMod] = std::make_unique<stat_config>(actor_value::kLockpickingPowerModifier,
            *settings::lockpickingPowerModString,
            menu_util::get_stats_menu(*settings::lockpicking_power_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::lockpicking_power_mod_menu_inventory));
        mp[stats_value::sneak_power_mod] = std::make_unique<stat_config>(actor_value::kSneakingPowerModifier,
            *settings::sneakPowerModString,
            menu_util::get_stats_menu(*settings::sneak_power_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::sneak_power_mod_menu_inventory));
        mp[stats_value::alchemy_power_mod] = std::make_unique<stat_config>(actor_value::kAlchemyPowerModifier,
            *settings::alchemyPowerModString,
            menu_util::get_stats_menu(*settings::alchemy_power_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::alchemy_power_mod_menu_inventory));
        mp[stats_value::speech_power_mod] = std::make_unique<stat_config>(actor_value::kSpeechcraftPowerModifier,
            *settings::speechPowerModString,
            menu_util::get_stats_menu(*settings::speech_power_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::speech_power_mod_menu_inventory));
        mp[stats_value::enchanting_power_mod] = std::make_unique<stat_config>(actor_value::kEnchantingPowerModifier,
            *settings::enchantingPowerModString,
            menu_util::get_stats_menu(*settings::enchanting_power_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::enchanting_power_mod_menu_inventory));
        mp[stats_value::alteration_power_mod] = std::make_unique<stat_config>(actor_value::kAlterationPowerModifier,
            *settings::alterationPowerModString,
            menu_util::get_stats_menu(*settings::alteration_power_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::alteration_power_mod_menu_inventory));
        mp[stats_value::conjuration_power_mod] = std::make_unique<stat_config>(actor_value::kConjurationPowerModifier,
            *settings::conjurationPowerModString,
            menu_util::get_stats_menu(*settings::conjuration_power_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::conjuration_power_mod_menu_inventory));
        mp[stats_value::destruction_power_mod] = std::make_unique<stat_config>(actor_value::kDestructionPowerModifier,
            *settings::destructionPowerModString,
            menu_util::get_stats_menu(*settings::destruction_power_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::destruction_power_mod_menu_inventory));
        mp[stats_value::illusion_power_mod] = std::make_unique<stat_config>(actor_value::kIllusionPowerModifier,
            *settings::illusionPowerModString,
            menu_util::get_stats_menu(*settings::illusion_power_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::illusion_power_mod_menu_inventory));
        mp[stats_value::restoration_power_mod] = std::make_unique<stat_config>(actor_value::kRestorationPowerModifier,
            *settings::restorationPowerModString,
            menu_util::get_stats_menu(*settings::restoration_power_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::restoration_power_mod_menu_inventory));
        mp[stats_value::speed_mult] = std::make_unique<stat_config>(actor_value::kSpeedMult,
            *settings::speedMultString,
            *settings::speedMultStringEnding,
            menu_util::get_stats_menu(*settings::speed_mult_menu),
            menu_util::get_stats_inventory_menu(*settings::speed_mult_menu_inventory));
        mp[stats_value::inventory_weight] = std::make_unique<stat_config>(actor_value::kInventoryWeight,
            *settings::inventoryWeightString,
            *settings::inventoryWeightStringEnding,
            menu_util::get_stats_menu(*settings::inventory_weight_menu),
            menu_util::get_stats_inventory_menu(*settings::inventory_weight_menu_inventory));
        mp[stats_value::carry_weight] = std::make_unique<stat_config>(actor_value::kCarryWeight,
            *settings::carryWeightString,
            *settings::carryWeightStringEnding,
            menu_util::get_stats_menu(*settings::carry_weight_menu),
            menu_util::get_stats_inventory_menu(*settings::carry_weight_menu_inventory));
        mp[stats_value::critical_chance] = std::make_unique<stat_config>(actor_value::kCriticalChance,
            *settings::criticalChanceString,
            *settings::criticalChanceStringEnding,
            menu_util::get_stats_menu(*settings::critical_chance_menu),
            menu_util::get_stats_inventory_menu(*settings::critical_chance_menu_inventory));
        mp[stats_value::melee_damage] = std::make_unique<stat_config>(actor_value::kMeleeDamage,
            *settings::meleeDamageString,
            menu_util::get_stats_menu(*settings::melee_damage_menu),
            menu_util::get_stats_inventory_menu(*settings::melee_damage_menu_inventory));
        mp[stats_value::unarmed_damage] = std::make_unique<stat_config>(actor_value::kUnarmedDamage,
            *settings::unarmedDamageString,
            menu_util::get_stats_menu(*settings::unarmed_damage_menu),
            menu_util::get_stats_inventory_menu(*settings::unarmed_damage_menu_inventory));
        mp[stats_value::absorb_chance] = std::make_unique<stat_config>(actor_value::kAbsorbChance,
            *settings::absorbChanceString,
            *settings::absorbChanceStringEnding,
            menu_util::get_stats_menu(*settings::absorb_chance_menu),
            menu_util::get_stats_inventory_menu(*settings::absorb_chance_menu_inventory));
        //we will not set the actor value kWeaponSpeedMult and kLeftWeaponSpeedMultiply here, because some genius thought it is nice that the value 0 and 1 means 100%
        // https://en.uesp.net/wiki/Skyrim_Mod:Actor_Value_Indices as documented here
        mp[stats_value::weapon_speed_mult] = std::make_unique<stat_config>(actor_value::kNone,
            *settings::weaponSpeedMultString,
            *settings::weaponSpeedMultStringEnding,
            menu_util::get_stats_menu(*settings::weapon_speed_mult_menu),
            menu_util::get_stats_inventory_menu(*settings::weapon_speed_mult_menu_inventory),
            menu_util::get_multiplier(*settings::weapon_speed_mult_mult));
        mp[stats_value::left_weapon_speed_mult] = std::make_unique<stat_config>(actor_value::kNone,
            *settings::leftWeaponSpeedMultString,
            *settings::leftWeaponSpeedMultStringEnding,
            menu_util::get_stats_menu(*settings::left_weapon_speed_mult_menu),
            menu_util::get_stats_inventory_menu(*settings::left_weapon_speed_mult_menu_inventory),
            menu_util::get_multiplier(*settings::left_weapon_speed_mult_mult));
        mp[stats_value::right_item_charge] = std::make_unique<stat_config>(actor_value::kRightItemCharge,
            *settings::rightItemChargeString,
            menu_util::get_stats_menu(*settings::right_item_charge_menu),
            menu_util::get_stats_inventory_menu(*settings::right_item_charge_menu_inventory));
        mp[stats_value::left_item_charge] = std::make_unique<stat_config>(actor_value::kLeftItemCharge,
            *settings::leftItemChargStringe,
            menu_util::get_stats_menu(*settings::left_item_charge_menu),
            menu_util::get_stats_inventory_menu(*settings::left_item_charge_menu_inventory));
        mp[stats_value::armor_perks] = std::make_unique<stat_config>(actor_value::kArmorPerks,
            *settings::armorPerksString,
            *settings::armorPerksStringEnding,
            menu_util::get_stats_menu(*settings::armor_perks_menu),
            menu_util::get_stats_inventory_menu(*settings::armor_perks_menu_inventory),
            menu_util::get_multiplier(*settings::armor_perks_mult));
        mp[stats_value::mass] = std::make_unique<stat_config>(actor_value::kMass,
            *settings::massString,
            menu_util::get_stats_menu(*settings::mass_menu),
            menu_util::get_stats_inventory_menu(*settings::mass_menu_inventory));
        mp[stats_value::bow_stagger_bonus] = std::make_unique<stat_config>(actor_value::kBowStaggerBonus,
            *settings::bowStaggerBonusString,
            menu_util::get_stats_menu(*settings::bow_stagger_bonus_menu),
            menu_util::get_stats_inventory_menu(*settings::bow_stagger_bonus_menu_inventory));
        mp[stats_value::bypass_vendor_keyword_check] =
            std::make_unique<stat_config>(actor_value::kBypassVendorKeywordCheck,
                *settings::bypassVendorKeywordCheckString,
                menu_util::get_stats_menu(*settings::bypass_vendor_keyword_check_menu),
                stats_inventory_menu_value::m_none);
        mp[stats_value::bypass_vendor_stolen_check] =
            std::make_unique<stat_config>(actor_value::kBypassVendorStolenCheck,
                *settings::bypassVendorStolenCheckString,
                menu_util::get_stats_menu(*settings::bypass_vendor_stolen_check_menu),
                stats_inventory_menu_value::m_none);
        mp[stats_value::bow_speed_bonus] = std::make_unique<stat_config>(actor_value::kBowSpeedBonus,
            *settings::bowSpeedBonusString,
            *settings::bowSpeedBonusStringEnding,
            menu_util::get_stats_menu(*settings::bow_speed_bonus_menu),
            menu_util::get_stats_inventory_menu(*settings::bow_speed_bonus_menu_inventory));
        mp[stats_value::shout_recovery_mult] = std::make_unique<stat_config>(actor_value::kShoutRecoveryMult,
            *settings::shoutRecoveryMultString,
            *settings::shoutRecoveryMultStringEnding,
            menu_util::get_stats_menu(*settings::shout_recovery_mult_menu),
            menu_util::get_stats_inventory_menu(*settings::shout_recovery_mult_menu_inventory),
            menu_util::get_multiplier(*settings::shout_recovery_mult_mult));
        mp[stats_value::movement_noise_mult] = std::make_unique<stat_config>(actor_value::kMovementNoiseMult,
            *settings::movementNoiseMultString,
            *settings::movementNoiseMultStringEnding,
            menu_util::get_stats_menu(*settings::movement_noise_mult_menu),
            menu_util::get_stats_inventory_menu(*settings::movement_noise_mult_menu_inventory),
            menu_util::get_multiplier(*settings::movement_noise_mult_mult));
        mp[stats_value::dragon_souls] = std::make_unique<stat_config>(actor_value::kDragonSouls,
            *settings::dragonSoulsString,
            menu_util::get_stats_menu(*settings::dragon_souls_menu),
            stats_inventory_menu_value::m_none);
        mp[stats_value::combat_health_regen_multiply] =
            std::make_unique<stat_config>(actor_value::kCombatHealthRegenMultiply,
                *settings::combatHealthRegenMultiplyString,
                *settings::combatHealthRegenMultiplyStringEnding,
                menu_util::get_stats_menu(*settings::combat_health_regen_multiply_menu),
                stats_inventory_menu_value::m_none,
                menu_util::get_multiplier(*settings::combat_health_regen_multiply_mult));
        mp[stats_value::attack_damage_mult] = std::make_unique<stat_config>(actor_value::kAttackDamageMult,
            *settings::attackDamageMultString,
            *settings::attackDamageMultStringEnding,
            menu_util::get_stats_menu(*settings::attack_damage_mult_menu),
            menu_util::get_stats_inventory_menu(*settings::attack_damage_mult_menu_inventory));
        mp[stats_value::beast] = std::make_unique<stat_config>(actor_value::kNone,
            *settings::beastString,
            stats_menu_value::m_special,
            stats_inventory_menu_value::m_none);
        mp[stats_value::xp] = std::make_unique<stat_config>(actor_value::kNone,
            *settings::xpString,
            stats_menu_value::m_special,
            stats_inventory_menu_value::m_none);
        mp[stats_value::reflect_damage] = std::make_unique<stat_config>(actor_value::kReflectDamage,
            *settings::reflectDamageString,
            *settings::reflectDamageStringEnding,
            menu_util::get_stats_menu(*settings::reflect_damage_menu),
            menu_util::get_stats_inventory_menu(*settings::reflect_damage_menu_inventory));
        mp[stats_value::one_handed_mod] = std::make_unique<stat_config>(actor_value::kOneHandedModifier,
            *settings::oneHandedModString,
            *settings::oneHandedModStringEnding,
            menu_util::get_stats_menu(*settings::one_handed_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::one_handed_mod_menu_inventory));
        mp[stats_value::two_handed_mod] = std::make_unique<stat_config>(actor_value::kTwoHandedModifier,
            *settings::twoHandedModString,
            *settings::twoHandedModStringEnding,
            menu_util::get_stats_menu(*settings::two_handed_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::two_handed_mod_menu_inventory));
        mp[stats_value::marksman_mod] = std::make_unique<stat_config>(actor_value::kMarksmanModifier,
            *settings::archeryModString,
            *settings::archeryModStringEnding,
            menu_util::get_stats_menu(*settings::archery_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::archery_mod_menu_inventory));
        mp[stats_value::block_mod] = std::make_unique<stat_config>(actor_value::kBlockModifier,
            *settings::blockModString,
            *settings::blockModStringEnding,
            menu_util::get_stats_menu(*settings::block_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::block_mod_menu_inventory));
        mp[stats_value::smithing_mod] = std::make_unique<stat_config>(actor_value::kSmithingModifier,
            *settings::smithingModString,
            *settings::smithingModStringEnding,
            menu_util::get_stats_menu(*settings::smithing_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::smithing_mod_menu_inventory));
        mp[stats_value::heavy_armor_mod] = std::make_unique<stat_config>(actor_value::kHeavyArmorModifier,
            *settings::heavyArmorModString,
            *settings::heavyArmorModStringEnding,
            menu_util::get_stats_menu(*settings::heavy_armor_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::heavy_armor_mod_menu_inventory));
        mp[stats_value::light_armor_mod] = std::make_unique<stat_config>(actor_value::kLightArmorModifier,
            *settings::lightArmorModString,
            *settings::lightArmorModStringEnding,
            menu_util::get_stats_menu(*settings::light_armor_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::light_armor_mod_menu_inventory));
        mp[stats_value::pickpocket_mod] = std::make_unique<stat_config>(actor_value::kPickpocketModifier,
            *settings::pickpocketModString,
            *settings::pickpocketModStringEnding,
            menu_util::get_stats_menu(*settings::pickpocket_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::pickpocket_mod_menu_inventory));
        mp[stats_value::lockpicking_mod] = std::make_unique<stat_config>(actor_value::kLockpickingModifier,
            *settings::lockpickingModString,
            *settings::lockpickingModStringEnding,
            menu_util::get_stats_menu(*settings::lockpicking_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::lockpicking_mod_menu_inventory));
        mp[stats_value::sneaking_mod] = std::make_unique<stat_config>(actor_value::kSneakingModifier,
            *settings::sneakModString,
            *settings::sneakModStringEnding,
            menu_util::get_stats_menu(*settings::sneak_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::sneak_mod_menu_inventory));
        mp[stats_value::alchemy_mod] = std::make_unique<stat_config>(actor_value::kAlchemyModifier,
            *settings::alchemyModString,
            *settings::alchemyModStringEnding,
            menu_util::get_stats_menu(*settings::alchemy_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::alchemy_mod_menu_inventory));
        mp[stats_value::speechcraft_mod] = std::make_unique<stat_config>(actor_value::kSpeechcraftModifier,
            *settings::speechModString,
            *settings::speechModStringEnding,
            menu_util::get_stats_menu(*settings::speech_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::speech_mod_menu_inventory));
        mp[stats_value::enchanting_mod] = std::make_unique<stat_config>(actor_value::kEnchantingModifier,
            *settings::enchantingModString,
            *settings::enchantingModStringEnding,
            menu_util::get_stats_menu(*settings::enchanting_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::enchanting_mod_menu_inventory));
        mp[stats_value::alteration_mod] = std::make_unique<stat_config>(actor_value::kAlterationModifier,
            *settings::alterationModString,
            *settings::alterationModStringEnding,
            menu_util::get_stats_menu(*settings::alteration_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::alteration_mod_menu_inventory));
        mp[stats_value::conjuration_mod] = std::make_unique<stat_config>(actor_value::kConjurationModifier,
            *settings::conjurationModString,
            *settings::conjurationModStringEnding,
            menu_util::get_stats_menu(*settings::conjuration_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::conjuration_mod_menu_inventory));
        mp[stats_value::destruction_mod] = std::make_unique<stat_config>(actor_value::kDestructionModifier,
            *settings::destructionModString,
            *settings::destructionModStringEnding,
            menu_util::get_stats_menu(*settings::destruction_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::destruction_mod_menu_inventory));
        mp[stats_value::illusion_mod] = std::make_unique<stat_config>(actor_value::kIllusionModifier,
            *settings::illusionModString,
            *settings::illusionModStringEnding,
            menu_util::get_stats_menu(*settings::illusion_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::illusion_mod_menu_inventory));
        mp[stats_value::restoration_mod] = std::make_unique<stat_config>(actor_value::kRestorationModifier,
            *settings::restorationModString,
            *settings::restorationModStringEnding,
            menu_util::get_stats_menu(*settings::restoration_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::restoration_mod_menu_inventory));
        mp[stats_value::damage_arrow] = std::make_unique<stat_config>(actor_value::kNone,
            *settings::damageArrowString,
            menu_util::get_stats_menu(*settings::damage_arrow_menu),
            menu_util::get_stats_inventory_menu(*settings::damage_arrow_menu_inventory));
        mp[stats_value::damage_left] = std::make_unique<stat_config>(actor_value::kNone,
            *settings::damageLeftString,
            menu_util::get_stats_menu(*settings::damage_left_menu),
            menu_util::get_stats_inventory_menu(*settings::damage_left_menu_inventory));
        mp[stats_value::weapon_reach] = std::make_unique<stat_config>(actor_value::kNone,
            *settings::weaponReachString,
            menu_util::get_stats_menu(*settings::weapon_reach_menu),
            menu_util::get_stats_inventory_menu(*settings::weapon_reach_menu_inventory));
        mp[stats_value::weapon_reach_left] = std::make_unique<stat_config>(actor_value::kNone,
            *settings::weaponReachLeftString,
            menu_util::get_stats_menu(*settings::weapon_reach_left_menu),
            menu_util::get_stats_inventory_menu(*settings::weapon_reach_left_menu_inventory));
        mp[stats_value::weapon_base_damage] = std::make_unique<stat_config>(actor_value::kNone,
            *settings::weaponBaseDamageString,
            menu_util::get_stats_menu(*settings::weapon_base_damage_menu),
            menu_util::get_stats_inventory_menu(*settings::weapon_base_damage_menu_inventory));
        mp[stats_value::weapon_base_damage_left] = std::make_unique<stat_config>(actor_value::kNone,
            *settings::weaponBaseDamageLeftString,
            menu_util::get_stats_menu(*settings::weapon_base_damage_left_menu),
            menu_util::get_stats_inventory_menu(*settings::weapon_base_damage_left_menu_inventory));
        mp[stats_value::weapon_stagger] = std::make_unique<stat_config>(actor_value::kNone,
            *settings::weaponStaggerString,
            menu_util::get_stats_menu(*settings::weapon_stagger_menu),
            menu_util::get_stats_inventory_menu(*settings::weapon_stagger_menu_inventory));
        mp[stats_value::weapon_stagger_left] = std::make_unique<stat_config>(actor_value::kNone,
            *settings::weaponStaggerLeftString,
            menu_util::get_stats_menu(*settings::weapon_stagger_left_menu),
            menu_util::get_stats_inventory_menu(*settings::weapon_stagger_left_menu_inventory));
        mp[stats_value::weapon_crit_damage_rating] = std::make_unique<stat_config>(actor_value::kNone,
            *settings::weaponCritDamageRatingString,
            menu_util::get_stats_menu(*settings::weapon_crit_damage_rating_menu),
            menu_util::get_stats_inventory_menu(*settings::weapon_crit_damage_rating_menu_inventory));
        mp[stats_value::weapon_crit_damage_rating_left] = std::make_unique<stat_config>(actor_value::kNone,
            *settings::weaponCritDamageRatingLeftString,
            menu_util::get_stats_menu(*settings::weapon_crit_damage_rating_left_menu),
            menu_util::get_stats_inventory_menu(*settings::weapon_crit_damage_rating_left_menu_inventory));
        mp[stats_value::fall_damage_mod] = std::make_unique<stat_config>(actor_value::kNone,
            *settings::fallDamageModString,
            *settings::fallDamageModStringEnding,
            menu_util::get_stats_menu(*settings::fall_damage_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::fall_damage_mod_menu_inventory),
            menu_util::get_multiplier(*settings::fall_damage_mod_mult));
        return mp;
    }

    stat_setting() = default;
    stat_setting(const stat_setting&) = default;
    stat_setting(stat_setting&&) = delete;

    ~stat_setting() = default;

    stat_setting& operator=(const stat_setting&) = default;
    stat_setting& operator=(stat_setting&&) = delete;
};
