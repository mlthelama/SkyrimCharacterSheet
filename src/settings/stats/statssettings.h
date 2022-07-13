#pragma once
#include "settings/gamesettings.h"
#include "utils/constants.h"
#include "utils/iconkeys.h"
#include "utils/utils.h"

class stat_config {
    using stats_inventory_menu_value = menu_util::stats_inventory_menu_value;
    using stats_menu_value = menu_util::stats_menu_value;

public:
    stat_config(const RE::ActorValue a_actor,
        const std::string_view a_display_name,
        const stats_menu_value a_stats_menu,
        const stats_inventory_menu_value a_stats_inventory_menu)
        : actor_(a_actor)
        , display_name_(a_display_name)
        , stats_menu_(a_stats_menu)
        , stats_inventory_menu_(a_stats_inventory_menu) {}

    stat_config(const RE::ActorValue a_actor,
        const std::string_view a_display_name,
        const stats_menu_value a_stats_menu,
        const stats_inventory_menu_value a_stats_inventory_menu,
        const std::string_view a_icon)
        : actor_(a_actor)
        , display_name_(a_display_name)
        , stats_menu_(a_stats_menu)
        , stats_inventory_menu_(a_stats_inventory_menu)
        , icon_string_(a_icon) {}

    stat_config(const RE::ActorValue a_actor,
        const std::string_view a_display_name,
        std::string a_ending,
        const stats_menu_value a_stats_menu,
        const stats_inventory_menu_value a_stats_inventory_menu)
        : actor_(a_actor)
        , display_name_(a_display_name)
        , ending_(std::move(a_ending))
        , stats_menu_(a_stats_menu)
        , stats_inventory_menu_(a_stats_inventory_menu) {}

    stat_config(const RE::ActorValue a_actor,
        const std::string_view a_display_name,
        std::string a_ending,
        const stats_menu_value a_stats_menu,
        const stats_inventory_menu_value a_stats_inventory_menu,
        const std::string_view a_icon)
        : actor_(a_actor)
        , display_name_(a_display_name)
        , ending_(std::move(a_ending))
        , stats_menu_(a_stats_menu)
        , stats_inventory_menu_(a_stats_inventory_menu)
        , icon_string_(a_icon) {}

    stat_config(const RE::ActorValue a_actor,
        const std::string_view a_display_name,
        std::string a_ending,
        const stats_menu_value a_stats_menu,
        const stats_inventory_menu_value a_stats_inventory_menu,
        const int64_t a_value_multiplier)
        : actor_(a_actor)
        , display_name_(a_display_name)
        , ending_(std::move(a_ending))
        , stats_menu_(a_stats_menu)
        , stats_inventory_menu_(a_stats_inventory_menu)
        , value_multiplier_(a_value_multiplier) {}

    stat_config(const RE::ActorValue a_actor,
        const std::string_view a_display_name,
        std::string a_ending,
        const stats_menu_value a_stats_menu,
        const stats_inventory_menu_value a_stats_inventory_menu,
        const int64_t a_value_multiplier,
        const std::string_view a_icon)
        : actor_(a_actor)
        , display_name_(a_display_name)
        , ending_(std::move(a_ending))
        , stats_menu_(a_stats_menu)
        , stats_inventory_menu_(a_stats_inventory_menu)
        , value_multiplier_(a_value_multiplier)
        , icon_string_(a_icon) {}

    stat_config(const RE::ActorValue a_actor,
        const std::string_view a_display_name,
        std::string a_ending,
        const stats_menu_value a_stats_menu,
        const stats_inventory_menu_value a_stats_inventory_menu,
        const int64_t a_value_multiplier,
        const float a_cap)
        : actor_(a_actor)
        , display_name_(a_display_name)
        , ending_(std::move(a_ending))
        , stats_menu_(a_stats_menu)
        , stats_inventory_menu_(a_stats_inventory_menu)
        , value_multiplier_(a_value_multiplier)
        , cap_(a_cap) {}

    stat_config(const RE::ActorValue a_actor,
        const std::string_view a_display_name,
        std::string a_ending,
        const stats_menu_value a_stats_menu,
        const stats_inventory_menu_value a_stats_inventory_menu,
        const int64_t a_value_multiplier,
        const float a_cap,
        const std::string_view a_icon)
        : actor_(a_actor)
        , display_name_(a_display_name)
        , ending_(std::move(a_ending))
        , stats_menu_(a_stats_menu)
        , stats_inventory_menu_(a_stats_inventory_menu)
        , value_multiplier_(a_value_multiplier)
        , cap_(a_cap)
        , icon_string_(a_icon) {}

    stat_config(const RE::ActorValue a_actor,
        const std::string_view a_display_name,
        const stats_menu_value a_stats_menu,
        const stats_inventory_menu_value a_stats_inventory_menu,
        const bool a_perm_av)
        : actor_(a_actor)
        , display_name_(a_display_name)
        , stats_menu_(a_stats_menu)
        , stats_inventory_menu_(a_stats_inventory_menu)
        , show_perm_av_(a_perm_av) {}

    stat_config(const RE::ActorValue a_actor,
        const std::string_view a_display_name,
        const stats_menu_value a_stats_menu,
        const stats_inventory_menu_value a_stats_inventory_menu,
        const bool a_perm_av,
        const std::string_view a_icon)
        : actor_(a_actor)
        , display_name_(a_display_name)
        , stats_menu_(a_stats_menu)
        , stats_inventory_menu_(a_stats_inventory_menu)
        , show_perm_av_(a_perm_av)
        , icon_string_(a_icon) {}

    [[nodiscard]] RE::ActorValue get_actor() const { return actor_; }

    [[nodiscard]] std::string_view get_display_name() const { return display_name_; }

    std::string get_ending() { return ending_; }

    [[nodiscard]] stats_menu_value get_stats_menu() const { return stats_menu_; }

    [[nodiscard]] stats_inventory_menu_value get_stats_inventory_menu() const { return stats_inventory_menu_; }

    [[nodiscard]] int64_t get_value_multiplier() const { return value_multiplier_; }

    [[nodiscard]] float get_cap() const { return cap_; }

    [[nodiscard]] bool get_show_perm_av() const { return show_perm_av_; }

    [[nodiscard]] std::string_view get_key_display() const { return display_name_; }

    [[nodiscard]] std::string_view get_icon_string() const { return icon_string_; }

    std::string get_value_display(const std::string& a_value) {
        if (!a_value.empty()) {
            logger::trace("display {} got value {}, building text ..."sv, display_name_, a_value);
            return ending_.empty() ? a_value : menu_util::build_value_string(a_value, ending_);
        }
        return "";
    }

    void log_stat_config(stats_value a_stats_value) {
        logger::trace(
            "name {}, actor {}, displayName {} ending {}, statsMenu {}, statsInventoryMenu {}, valueMultiplier {}, cap {}, showPermAV {}, icon {}"sv,
            a_stats_value,
            actor_,
            display_name_,
            ending_,
            stats_menu_,
            stats_inventory_menu_,
            value_multiplier_,
            cap_,
            show_perm_av_,
            icon_string_);
    }

    stat_config() = delete;
    stat_config(const stat_config&) = default;
    stat_config(stat_config&&) = delete;

    ~stat_config() = default;

    stat_config& operator=(const stat_config&) = default;
    stat_config& operator=(stat_config&&) = delete;

private:
    RE::ActorValue actor_;
    std::string_view display_name_;
    std::string ending_;
    stats_menu_value stats_menu_;
    stats_inventory_menu_value stats_inventory_menu_;
    int64_t value_multiplier_ = const_static_multiplier;
    float cap_ = -1;
    bool show_perm_av_ = false;
    std::string_view icon_string_;
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
            menu_keys::name,
            stats_menu_value::m_special,
            stats_inventory_menu_value::m_none);
        mp[stats_value::race] = std::make_unique<stat_config>(actor_value::kNone,
            menu_keys::race,
            stats_menu_value::m_special,
            stats_inventory_menu_value::m_none);
        mp[stats_value::level] = std::make_unique<stat_config>(actor_value::kNone,
            menu_keys::level,
            stats_menu_value::m_special,
            stats_inventory_menu_value::m_none);
        mp[stats_value::perk_count] = std::make_unique<stat_config>(actor_value::kNone,
            menu_keys::perk,
            stats_menu_value::m_special,
            stats_inventory_menu_value::m_none);
        mp[stats_value::height] = std::make_unique<stat_config>(actor_value::kNone,
            menu_keys::height,
            *settings::height_string_ending,
            menu_util::get_stats_menu(*settings::height_menu),
            stats_inventory_menu_value::m_none);
        mp[stats_value::equipped_weight] = std::make_unique<stat_config>(actor_value::kNone,
            menu_keys::equipped_weight,
            *settings::equipped_weight_string_ending,
            menu_util::get_stats_menu(*settings::equiped_weight_menu),
            menu_util::get_stats_inventory_menu(*settings::equiped_weight_menu_inventory));
        mp[stats_value::weight] = std::make_unique<stat_config>(actor_value::kNone,
            menu_keys::weight,
            *settings::weight_string_ending,
            menu_util::get_stats_menu(*settings::weight_menu),
            stats_inventory_menu_value::m_none);
        mp[stats_value::armor] = std::make_unique<stat_config>(actor_value::kDamageResist,
            menu_keys::armor,
            menu_util::get_stats_menu(*settings::armor_menu),
            menu_util::get_stats_inventory_menu(*settings::armor_menu_inventory),
            icon_keys::armor);
        mp[stats_value::damage] = std::make_unique<stat_config>(actor_value::kNone,
            menu_keys::damage,
            menu_util::get_stats_menu(*settings::damage_menu),
            menu_util::get_stats_inventory_menu(*settings::damage_menu_inventory),
            icon_keys::damage);
        mp[stats_value::skill_trainings_this_level] = std::make_unique<stat_config>(actor_value::kNone,
            menu_keys::trainings_level,
            menu_util::get_stats_menu(*settings::skill_trainings_this_level_menu),
            stats_inventory_menu_value::m_none);
        mp[stats_value::health] = std::make_unique<stat_config>(actor_value::kHealth,
            menu_keys::health,
            menu_util::get_stats_menu(*settings::health_menu),
            menu_util::get_stats_inventory_menu(*settings::health_menu_inventory),
            *settings::display_permanent_av,
            icon_keys::health);
        mp[stats_value::health_rate_per] = std::make_unique<stat_config>(actor_value::kNone,
            menu_keys::health_rate,
            *settings::health_rate_string_ending,
            menu_util::get_stats_menu(*settings::health_rate_menu),
            menu_util::get_stats_inventory_menu(*settings::health_rate_menu_inventory),
            icon_keys::health_rate);
        mp[stats_value::magicka] = std::make_unique<stat_config>(actor_value::kMagicka,
            menu_keys::magicka,
            menu_util::get_stats_menu(*settings::magicka_menu),
            menu_util::get_stats_inventory_menu(*settings::magicka_menu_inventory),
            *settings::display_permanent_av,
            icon_keys::magicka);
        mp[stats_value::magicka_rate_per] = std::make_unique<stat_config>(actor_value::kNone,
            menu_keys::magicka_rate,
            *settings::magicka_rate_string_ending,
            menu_util::get_stats_menu(*settings::magicka_rate_menu),
            menu_util::get_stats_inventory_menu(*settings::magicka_rate_menu_inventory),
            icon_keys::magicka_rate);
        mp[stats_value::stamina] = std::make_unique<stat_config>(actor_value::kStamina,
            menu_keys::stamina,
            menu_util::get_stats_menu(*settings::stamina_menu),
            menu_util::get_stats_inventory_menu(*settings::magicka_rate_menu_inventory),
            *settings::display_permanent_av,
            icon_keys::stamina);
        mp[stats_value::stamina_rate_per] = std::make_unique<stat_config>(actor_value::kNone,
            menu_keys::stamina_rate,
            *settings::stamina_rate_string_ending,
            menu_util::get_stats_menu(*settings::stamina_rate_menu),
            menu_util::get_stats_inventory_menu(*settings::stamina_menu_inventory),
            icon_keys::stamina_rate);
        mp[stats_value::resist_damage] = std::make_unique<stat_config>(actor_value::kNone,
            menu_keys::resist_damage,
            *settings::resist_damage_string_ending,
            menu_util::get_stats_menu(*settings::resist_damage_menu),
            menu_util::get_stats_inventory_menu(*settings::resist_damage_menu_inventory),
            const_static_multiplier,
            game_settings->max_armor_resistance,
            icon_keys::resist_damage);
        mp[stats_value::resist_disease] = std::make_unique<stat_config>(actor_value::kResistDisease,
            menu_keys::resist_disease,
            *settings::resist_disease_string_ending,
            menu_util::get_stats_menu(*settings::resist_disease_menu),
            menu_util::get_stats_inventory_menu(*settings::resist_disease_menu_inventory),
            icon_keys::resist_disease);
        mp[stats_value::resist_poison] = std::make_unique<stat_config>(actor_value::kPoisonResist,
            menu_keys::resist_poison,
            *settings::resist_poison_string_ending,
            menu_util::get_stats_menu(*settings::resist_poison_menu),
            menu_util::get_stats_inventory_menu(*settings::resist_poison_menu_inventory),
            const_static_multiplier,
            game_settings->max_resistance,
            icon_keys::resist_poison);
        mp[stats_value::resist_fire] = std::make_unique<stat_config>(actor_value::kResistFire,
            menu_keys::resist_fire,
            *settings::resist_fire_string_ending,
            menu_util::get_stats_menu(*settings::resist_fire_menu),
            menu_util::get_stats_inventory_menu(*settings::resist_fire_menu_inventory),
            const_static_multiplier,
            game_settings->max_resistance,
            icon_keys::resist_fire);
        mp[stats_value::resist_shock] = std::make_unique<stat_config>(actor_value::kResistShock,
            menu_keys::resist_shock,
            *settings::resist_shock_string_ending,
            menu_util::get_stats_menu(*settings::resist_shock_menu),
            menu_util::get_stats_inventory_menu(*settings::resist_shock_menu_inventory),
            const_static_multiplier,
            game_settings->max_resistance,
            icon_keys::resist_shock);
        mp[stats_value::resist_frost] = std::make_unique<stat_config>(actor_value::kResistFrost,
            menu_keys::resist_frost,
            *settings::resist_frost_string_ending,
            menu_util::get_stats_menu(*settings::resist_frost_menu),
            menu_util::get_stats_inventory_menu(*settings::resist_frost_menu_inventory),
            const_static_multiplier,
            game_settings->max_resistance,
            icon_keys::resist_frost);
        mp[stats_value::resist_magic] = std::make_unique<stat_config>(actor_value::kResistMagic,
            menu_keys::resist_magic,
            *settings::resist_magic_string_ending,
            menu_util::get_stats_menu(*settings::resist_magic_menu),
            menu_util::get_stats_inventory_menu(*settings::resist_magic_menu_inventory),
            const_static_multiplier,
            game_settings->max_resistance,
            icon_keys::resist_magic);
        mp[stats_value::one_handed] = std::make_unique<stat_config>(actor_value::kOneHanded,
            menu_keys::one_handed,
            menu_util::get_stats_menu(*settings::one_handed_menu),
            menu_util::get_stats_inventory_menu(*settings::one_handed_menu_inventory),
            *settings::display_permanent_av,
            icon_keys::one_handed);
        mp[stats_value::two_handed] = std::make_unique<stat_config>(actor_value::kTwoHanded,
            menu_keys::two_handed,
            menu_util::get_stats_menu(*settings::two_handed_menu),
            menu_util::get_stats_inventory_menu(*settings::two_handed_menu_inventory),
            *settings::display_permanent_av,
            icon_keys::two_handed);
        mp[stats_value::archery] = std::make_unique<stat_config>(actor_value::kArchery,
            menu_keys::archery,
            menu_util::get_stats_menu(*settings::archery_menu),
            menu_util::get_stats_inventory_menu(*settings::archery_menu_inventory),
            *settings::display_permanent_av,
            icon_keys::archery);
        mp[stats_value::block] = std::make_unique<stat_config>(actor_value::kBlock,
            menu_keys::block,
            menu_util::get_stats_menu(*settings::block_menu),
            menu_util::get_stats_inventory_menu(*settings::block_menu_inventory),
            *settings::display_permanent_av,
            icon_keys::block);
        mp[stats_value::smithing] = std::make_unique<stat_config>(actor_value::kSmithing,
            menu_keys::smithing,
            menu_util::get_stats_menu(*settings::smithing_menu),
            menu_util::get_stats_inventory_menu(*settings::smithing_menu_inventory),
            *settings::display_permanent_av,
            icon_keys::smithing);
        mp[stats_value::heavy_armor] = std::make_unique<stat_config>(actor_value::kHeavyArmor,
            menu_keys::heavy_armor,
            menu_util::get_stats_menu(*settings::heavy_armor_menu),
            menu_util::get_stats_inventory_menu(*settings::heavy_armor_menu_inventory),
            *settings::display_permanent_av,
            icon_keys::heavy_armor);
        mp[stats_value::light_armor] = std::make_unique<stat_config>(actor_value::kLightArmor,
            menu_keys::light_armor,
            menu_util::get_stats_menu(*settings::light_armor_menu),
            menu_util::get_stats_inventory_menu(*settings::light_armor_menu_inventory),
            *settings::display_permanent_av,
            icon_keys::light_armor);
        mp[stats_value::pickpocket] = std::make_unique<stat_config>(actor_value::kPickpocket,
            menu_keys::pickpocket,
            menu_util::get_stats_menu(*settings::pickpocket_menu),
            menu_util::get_stats_inventory_menu(*settings::pickpocket_menu_inventory),
            *settings::display_permanent_av,
            icon_keys::pickpocket);
        mp[stats_value::lockpicking] = std::make_unique<stat_config>(actor_value::kLockpicking,
            menu_keys::lockpicking,
            menu_util::get_stats_menu(*settings::lockpicking_menu),
            menu_util::get_stats_inventory_menu(*settings::lockpicking_menu_inventory),
            *settings::display_permanent_av,
            icon_keys::lockpicking);
        mp[stats_value::sneak] = std::make_unique<stat_config>(actor_value::kSneak,
            menu_keys::sneak,
            menu_util::get_stats_menu(*settings::sneak_menu),
            menu_util::get_stats_inventory_menu(*settings::sneak_menu_inventory),
            *settings::display_permanent_av,
            icon_keys::sneak);
        mp[stats_value::alchemy] = std::make_unique<stat_config>(actor_value::kAlchemy,
            menu_keys::alchemy,
            menu_util::get_stats_menu(*settings::alchemy_menu),
            menu_util::get_stats_inventory_menu(*settings::alchemy_menu_inventory),
            *settings::display_permanent_av,
            icon_keys::alchemy);
        mp[stats_value::speech] = std::make_unique<stat_config>(actor_value::kSpeech,
            menu_keys::speech,
            menu_util::get_stats_menu(*settings::speech_menu),
            menu_util::get_stats_inventory_menu(*settings::speech_menu_inventory),
            *settings::display_permanent_av,
            icon_keys::speech);
        mp[stats_value::enchanting] = std::make_unique<stat_config>(actor_value::kEnchanting,
            menu_keys::enchanting,
            menu_util::get_stats_menu(*settings::enchanting_menu),
            menu_util::get_stats_inventory_menu(*settings::enchanting_menu_inventory),
            *settings::display_permanent_av);
        mp[stats_value::alteration] = std::make_unique<stat_config>(actor_value::kAlteration,
            menu_keys::alteration,
            menu_util::get_stats_menu(*settings::alteration_menu),
            menu_util::get_stats_inventory_menu(*settings::alteration_menu_inventory),
            *settings::display_permanent_av,
            icon_keys::alteration);
        mp[stats_value::conjuration] = std::make_unique<stat_config>(actor_value::kConjuration,
            menu_keys::conjuration,
            menu_util::get_stats_menu(*settings::conjuration_menu),
            menu_util::get_stats_inventory_menu(*settings::conjuration_menu_inventory),
            *settings::display_permanent_av,
            icon_keys::conjuration);
        mp[stats_value::destruction] = std::make_unique<stat_config>(actor_value::kDestruction,
            menu_keys::destruction,
            menu_util::get_stats_menu(*settings::destruction_menu),
            menu_util::get_stats_inventory_menu(*settings::destruction_menu_inventory),
            *settings::display_permanent_av,
            icon_keys::destruction);
        mp[stats_value::illusion] = std::make_unique<stat_config>(actor_value::kIllusion,
            menu_keys::illusion,
            menu_util::get_stats_menu(*settings::illusion_menu),
            menu_util::get_stats_inventory_menu(*settings::illusion_menu_inventory),
            *settings::display_permanent_av,
            icon_keys::illusion);
        mp[stats_value::restoration] = std::make_unique<stat_config>(actor_value::kRestoration,
            menu_keys::restoration,
            menu_util::get_stats_menu(*settings::restoration_menu),
            menu_util::get_stats_inventory_menu(*settings::restoration_menu_inventory),
            *settings::display_permanent_av,
            icon_keys::restoration);
        mp[stats_value::one_handed_power_mod] = std::make_unique<stat_config>(actor_value::kOneHandedPowerModifier,
            menu_keys::one_handed_power_mod,
            menu_util::get_stats_menu(*settings::one_handed_power_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::one_handed_power_mod_menu_inventory),
            icon_keys::one_handed_power_mod);
        mp[stats_value::two_handed_power_mod] = std::make_unique<stat_config>(actor_value::kTwoHandedPowerModifier,
            menu_keys::two_handed_power_mod,
            menu_util::get_stats_menu(*settings::two_handed_power_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::two_handed_power_mod_menu_inventory),
            icon_keys::two_handed_power_mod);
        mp[stats_value::archery_power_mod] = std::make_unique<stat_config>(actor_value::kMarksmanPowerModifier,
            menu_keys::archery_power_mod,
            menu_util::get_stats_menu(*settings::archery_power_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::archery_power_mod_menu_inventory),
            icon_keys::archery_power_mod);
        mp[stats_value::block_power_mod] = std::make_unique<stat_config>(actor_value::kBlockPowerModifier,
            menu_keys::block_power_mod,
            menu_util::get_stats_menu(*settings::block_power_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::block_power_mod_menu_inventory),
            icon_keys::block_power_mod);
        mp[stats_value::smithing_power_mod] = std::make_unique<stat_config>(actor_value::kSmithingPowerModifier,
            menu_keys::smithing_power_mod,
            menu_util::get_stats_menu(*settings::smithing_power_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::smithing_power_mod_menu_inventory),
            icon_keys::smithing_power_mod);
        mp[stats_value::heavy_armor_power_mod] = std::make_unique<stat_config>(actor_value::kHeavyArmorPowerModifier,
            menu_keys::heavy_armor_power_mod,
            menu_util::get_stats_menu(*settings::heavy_armor_power_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::heavy_armor_power_mod_menu_inventory),
            icon_keys::heavy_armor_power_mod);
        mp[stats_value::light_armor_power_mod] = std::make_unique<stat_config>(actor_value::kLightArmorPowerModifier,
            menu_keys::light_armor_power_mod,
            menu_util::get_stats_menu(*settings::light_armor_power_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::light_armor_power_mod_menu_inventory),
            icon_keys::light_armor_power_mod);
        mp[stats_value::pickpocket_power_mod] = std::make_unique<stat_config>(actor_value::kPickpocketPowerModifier,
            menu_keys::pickpocket_power_mod,
            menu_util::get_stats_menu(*settings::pickpocket_power_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::pickpocket_power_mod_menu_inventory),
            icon_keys::pickpocket_power_mod);
        mp[stats_value::lockpicking_power_mod] = std::make_unique<stat_config>(actor_value::kLockpickingPowerModifier,
            menu_keys::lockpicking_power_mod,
            menu_util::get_stats_menu(*settings::lockpicking_power_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::lockpicking_power_mod_menu_inventory),
            icon_keys::lockpicking_power_mod);
        mp[stats_value::sneak_power_mod] = std::make_unique<stat_config>(actor_value::kSneakingPowerModifier,
            menu_keys::sneak_power_mod,
            menu_util::get_stats_menu(*settings::sneak_power_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::sneak_power_mod_menu_inventory),
            icon_keys::sneak_power_mod);
        mp[stats_value::alchemy_power_mod] = std::make_unique<stat_config>(actor_value::kAlchemyPowerModifier,
            menu_keys::alchemy_power_mod,
            menu_util::get_stats_menu(*settings::alchemy_power_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::alchemy_power_mod_menu_inventory),
            icon_keys::alchemy_power_mod);
        mp[stats_value::speech_power_mod] = std::make_unique<stat_config>(actor_value::kSpeechcraftPowerModifier,
            menu_keys::speech_power_mod,
            menu_util::get_stats_menu(*settings::speech_power_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::speech_power_mod_menu_inventory),
            icon_keys::speech_power_mod);
        mp[stats_value::enchanting_power_mod] = std::make_unique<stat_config>(actor_value::kEnchantingPowerModifier,
            menu_keys::enchanting_power_mod,
            menu_util::get_stats_menu(*settings::enchanting_power_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::enchanting_power_mod_menu_inventory),
            icon_keys::enchanting_power_mod);
        mp[stats_value::alteration_power_mod] = std::make_unique<stat_config>(actor_value::kAlterationPowerModifier,
            menu_keys::alteration_power_mod,
            menu_util::get_stats_menu(*settings::alteration_power_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::alteration_power_mod_menu_inventory),
            icon_keys::alteration_power_mod);
        mp[stats_value::conjuration_power_mod] = std::make_unique<stat_config>(actor_value::kConjurationPowerModifier,
            menu_keys::conjuration_power_mod,
            menu_util::get_stats_menu(*settings::conjuration_power_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::conjuration_power_mod_menu_inventory),
            icon_keys::conjuration_power_mod);
        mp[stats_value::destruction_power_mod] = std::make_unique<stat_config>(actor_value::kDestructionPowerModifier,
            menu_keys::destruction_power_mod,
            menu_util::get_stats_menu(*settings::destruction_power_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::destruction_power_mod_menu_inventory),
            icon_keys::destruction_power_mod);
        mp[stats_value::illusion_power_mod] = std::make_unique<stat_config>(actor_value::kIllusionPowerModifier,
            menu_keys::illusion_power_mod,
            menu_util::get_stats_menu(*settings::illusion_power_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::illusion_power_mod_menu_inventory),
            icon_keys::illusion_power_mod);
        mp[stats_value::restoration_power_mod] = std::make_unique<stat_config>(actor_value::kRestorationPowerModifier,
            menu_keys::restoration_power_mod,
            menu_util::get_stats_menu(*settings::restoration_power_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::restoration_power_mod_menu_inventory),
            icon_keys::restoration_power_mod);
        mp[stats_value::speed_mult] = std::make_unique<stat_config>(actor_value::kSpeedMult,
            menu_keys::speed_mult,
            *settings::speed_mult_string_ending,
            menu_util::get_stats_menu(*settings::speed_mult_menu),
            menu_util::get_stats_inventory_menu(*settings::speed_mult_menu_inventory),
            icon_keys::speed_mult);
        mp[stats_value::inventory_weight] = std::make_unique<stat_config>(actor_value::kInventoryWeight,
            menu_keys::inventory_weight,
            *settings::inventory_weight_string_ending,
            menu_util::get_stats_menu(*settings::inventory_weight_menu),
            menu_util::get_stats_inventory_menu(*settings::inventory_weight_menu_inventory),
            icon_keys::inventory_weight);
        mp[stats_value::carry_weight] = std::make_unique<stat_config>(actor_value::kCarryWeight,
            menu_keys::carry_weight,
            *settings::carry_weight_string_ending,
            menu_util::get_stats_menu(*settings::carry_weight_menu),
            menu_util::get_stats_inventory_menu(*settings::carry_weight_menu_inventory),
            icon_keys::carry_weight);
        mp[stats_value::critical_chance] = std::make_unique<stat_config>(actor_value::kCriticalChance,
            menu_keys::critical_chance,
            *settings::critical_chance_string_ending,
            menu_util::get_stats_menu(*settings::critical_chance_menu),
            menu_util::get_stats_inventory_menu(*settings::critical_chance_menu_inventory),
            icon_keys::critical_chance);
        mp[stats_value::melee_damage] = std::make_unique<stat_config>(actor_value::kMeleeDamage,
            menu_keys::melee_damage,
            menu_util::get_stats_menu(*settings::melee_damage_menu),
            menu_util::get_stats_inventory_menu(*settings::melee_damage_menu_inventory),
            icon_keys::melee_damage);
        mp[stats_value::unarmed_damage] = std::make_unique<stat_config>(actor_value::kUnarmedDamage,
            menu_keys::unarmed_damage,
            menu_util::get_stats_menu(*settings::unarmed_damage_menu),
            menu_util::get_stats_inventory_menu(*settings::unarmed_damage_menu_inventory),
            icon_keys::unarmed_damage);
        mp[stats_value::absorb_chance] = std::make_unique<stat_config>(actor_value::kAbsorbChance,
            menu_keys::absorb_chance,
            *settings::absorb_chance_string_ending,
            menu_util::get_stats_menu(*settings::absorb_chance_menu),
            menu_util::get_stats_inventory_menu(*settings::absorb_chance_menu_inventory),
            icon_keys::absorb_chance);
        //we will not set the actor value kWeaponSpeedMult and kLeftWeaponSpeedMultiply here, because some genius thought it is nice that the value 0 and 1 means 100%
        // https://en.uesp.net/wiki/Skyrim_Mod:Actor_Value_Indices as documented here
        mp[stats_value::weapon_speed_mult] = std::make_unique<stat_config>(actor_value::kNone,
            menu_keys::weapon_speed_mult,
            *settings::weapon_speed_mult_string_ending,
            menu_util::get_stats_menu(*settings::weapon_speed_mult_menu),
            menu_util::get_stats_inventory_menu(*settings::weapon_speed_mult_menu_inventory),
            menu_util::get_multiplier(*settings::weapon_speed_mult_mult),
            icon_keys::weapon_speed_mult);
        mp[stats_value::left_weapon_speed_mult] = std::make_unique<stat_config>(actor_value::kNone,
            menu_keys::left_weapon_speed_mult,
            *settings::left_weapon_speed_mult_string_ending,
            menu_util::get_stats_menu(*settings::left_weapon_speed_mult_menu),
            menu_util::get_stats_inventory_menu(*settings::left_weapon_speed_mult_menu_inventory),
            menu_util::get_multiplier(*settings::left_weapon_speed_mult_mult),
            icon_keys::left_weapon_speed_mult);
        mp[stats_value::right_item_charge] = std::make_unique<stat_config>(actor_value::kRightItemCharge,
            menu_keys::right_item_charge,
            menu_util::get_stats_menu(*settings::right_item_charge_menu),
            menu_util::get_stats_inventory_menu(*settings::right_item_charge_menu_inventory),
            icon_keys::right_item_charge);
        mp[stats_value::left_item_charge] = std::make_unique<stat_config>(actor_value::kLeftItemCharge,
            menu_keys::left_item_charge,
            menu_util::get_stats_menu(*settings::left_item_charge_menu),
            menu_util::get_stats_inventory_menu(*settings::left_item_charge_menu_inventory),
            icon_keys::left_item_charge);
        mp[stats_value::armor_perks] = std::make_unique<stat_config>(actor_value::kArmorPerks,
            menu_keys::armor_perks,
            *settings::armor_perks_string_ending,
            menu_util::get_stats_menu(*settings::armor_perks_menu),
            menu_util::get_stats_inventory_menu(*settings::armor_perks_menu_inventory),
            menu_util::get_multiplier(*settings::armor_perks_mult),
            icon_keys::armor_perks);
        mp[stats_value::mass] = std::make_unique<stat_config>(actor_value::kMass,
            menu_keys::mass,
            menu_util::get_stats_menu(*settings::mass_menu),
            menu_util::get_stats_inventory_menu(*settings::mass_menu_inventory),
            icon_keys::mass);
        mp[stats_value::bow_stagger_bonus] = std::make_unique<stat_config>(actor_value::kBowStaggerBonus,
            menu_keys::bow_stagger_bonus,
            menu_util::get_stats_menu(*settings::bow_stagger_bonus_menu),
            menu_util::get_stats_inventory_menu(*settings::bow_stagger_bonus_menu_inventory),
            icon_keys::bow_stagger_bonus);
        mp[stats_value::bypass_vendor_keyword_check] =
            std::make_unique<stat_config>(actor_value::kBypassVendorKeywordCheck,
                menu_keys::bypass_vendor_keyword_check,
                menu_util::get_stats_menu(*settings::bypass_vendor_keyword_check_menu),
                stats_inventory_menu_value::m_none,
                icon_keys::bypass_vendor_keyword_check);
        mp[stats_value::bypass_vendor_stolen_check] =
            std::make_unique<stat_config>(actor_value::kBypassVendorStolenCheck,
                menu_keys::bypass_vendor_stolen_check,
                menu_util::get_stats_menu(*settings::bypass_vendor_stolen_check_menu),
                stats_inventory_menu_value::m_none,
                icon_keys::bypass_vendor_stolen_check);
        mp[stats_value::bow_speed_bonus] = std::make_unique<stat_config>(actor_value::kBowSpeedBonus,
            menu_keys::bow_speed_bonus,
            *settings::bow_speed_bonus_string_ending,
            menu_util::get_stats_menu(*settings::bow_speed_bonus_menu),
            menu_util::get_stats_inventory_menu(*settings::bow_speed_bonus_menu_inventory),
            icon_keys::bow_speed_bonus);
        mp[stats_value::shout_recovery_mult] = std::make_unique<stat_config>(actor_value::kShoutRecoveryMult,
            menu_keys::shout_recovery_mult,
            *settings::shout_recovery_mult_string_ending,
            menu_util::get_stats_menu(*settings::shout_recovery_mult_menu),
            menu_util::get_stats_inventory_menu(*settings::shout_recovery_mult_menu_inventory),
            menu_util::get_multiplier(*settings::shout_recovery_mult_mult),
            icon_keys::shout_recovery_mult);
        mp[stats_value::movement_noise_mult] = std::make_unique<stat_config>(actor_value::kMovementNoiseMult,
            menu_keys::movement_noise_mult,
            *settings::movement_noise_mult_string_ending,
            menu_util::get_stats_menu(*settings::movement_noise_mult_menu),
            menu_util::get_stats_inventory_menu(*settings::movement_noise_mult_menu_inventory),
            menu_util::get_multiplier(*settings::movement_noise_mult_mult),
            icon_keys::movement_noise_mult);
        mp[stats_value::dragon_souls] = std::make_unique<stat_config>(actor_value::kDragonSouls,
            menu_keys::dragon_souls,
            menu_util::get_stats_menu(*settings::dragon_souls_menu),
            stats_inventory_menu_value::m_none,
            icon_keys::dragon_souls);
        mp[stats_value::combat_health_regen_multiply] =
            std::make_unique<stat_config>(actor_value::kCombatHealthRegenMultiply,
                menu_keys::combat_health_regen_mult,
                *settings::combat_health_regen_multiply_string_ending,
                menu_util::get_stats_menu(*settings::combat_health_regen_multiply_menu),
                stats_inventory_menu_value::m_none,
                menu_util::get_multiplier(*settings::combat_health_regen_multiply_mult),
                icon_keys::combat_health_regen_mult);
        mp[stats_value::attack_damage_mult] = std::make_unique<stat_config>(actor_value::kAttackDamageMult,
            menu_keys::attack_damage_mult,
            *settings::attack_damage_mult_string_ending,
            menu_util::get_stats_menu(*settings::attack_damage_mult_menu),
            menu_util::get_stats_inventory_menu(*settings::attack_damage_mult_menu_inventory),
            icon_keys::attack_damage_mult);
        mp[stats_value::beast] = std::make_unique<stat_config>(actor_value::kNone,
            menu_keys::beast,
            stats_menu_value::m_special,
            stats_inventory_menu_value::m_none);
        mp[stats_value::xp] = std::make_unique<stat_config>(actor_value::kNone,
            menu_keys::xp,
            stats_menu_value::m_special,
            stats_inventory_menu_value::m_none);
        mp[stats_value::reflect_damage] = std::make_unique<stat_config>(actor_value::kReflectDamage,
            menu_keys::reflect_damage,
            *settings::reflect_damage_string_ending,
            menu_util::get_stats_menu(*settings::reflect_damage_menu),
            menu_util::get_stats_inventory_menu(*settings::reflect_damage_menu_inventory),
            icon_keys::reflect_damage);
        mp[stats_value::one_handed_mod] = std::make_unique<stat_config>(actor_value::kOneHandedModifier,
            menu_keys::one_handed_mod,
            *settings::one_handed_mod_string_ending,
            menu_util::get_stats_menu(*settings::one_handed_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::one_handed_mod_menu_inventory),
            icon_keys::one_handed_mod);
        mp[stats_value::two_handed_mod] = std::make_unique<stat_config>(actor_value::kTwoHandedModifier,
            menu_keys::two_handed_mod,
            *settings::two_handed_mod_string_ending,
            menu_util::get_stats_menu(*settings::two_handed_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::two_handed_mod_menu_inventory),
            icon_keys::two_handed_mod);
        mp[stats_value::marksman_mod] = std::make_unique<stat_config>(actor_value::kMarksmanModifier,
            menu_keys::archery_mod,
            *settings::archery_mod_string_ending,
            menu_util::get_stats_menu(*settings::archery_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::archery_mod_menu_inventory),
            icon_keys::archery_mod);
        mp[stats_value::block_mod] = std::make_unique<stat_config>(actor_value::kBlockModifier,
            menu_keys::block_mod,
            *settings::block_mod_string_ending,
            menu_util::get_stats_menu(*settings::block_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::block_mod_menu_inventory),
            icon_keys::block_mod);
        mp[stats_value::smithing_mod] = std::make_unique<stat_config>(actor_value::kSmithingModifier,
            menu_keys::smithing_mod,
            *settings::smithing_mod_string_ending,
            menu_util::get_stats_menu(*settings::smithing_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::smithing_mod_menu_inventory),
            icon_keys::smithing_mod);
        mp[stats_value::heavy_armor_mod] = std::make_unique<stat_config>(actor_value::kHeavyArmorModifier,
            menu_keys::heavy_armor_mod,
            *settings::heavy_armor_mod_string_ending,
            menu_util::get_stats_menu(*settings::heavy_armor_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::heavy_armor_mod_menu_inventory),
            icon_keys::heavy_armor_mod);
        mp[stats_value::light_armor_mod] = std::make_unique<stat_config>(actor_value::kLightArmorModifier,
            menu_keys::light_armor_mod,
            *settings::light_armor_mod_string_ending,
            menu_util::get_stats_menu(*settings::light_armor_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::light_armor_mod_menu_inventory),
            icon_keys::light_armor_mod);
        mp[stats_value::pickpocket_mod] = std::make_unique<stat_config>(actor_value::kPickpocketModifier,
            menu_keys::pickpocket_mod,
            *settings::pickpocket_mod_string_ending,
            menu_util::get_stats_menu(*settings::pickpocket_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::pickpocket_mod_menu_inventory),
            icon_keys::pickpocket_mod);
        mp[stats_value::lockpicking_mod] = std::make_unique<stat_config>(actor_value::kLockpickingModifier,
            menu_keys::lockpicking_mod,
            *settings::lockpicking_mod_string_ending,
            menu_util::get_stats_menu(*settings::lockpicking_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::lockpicking_mod_menu_inventory),
            icon_keys::lockpicking_mod);
        mp[stats_value::sneaking_mod] = std::make_unique<stat_config>(actor_value::kSneakingModifier,
            menu_keys::sneak_mod,
            *settings::sneak_mod_string_ending,
            menu_util::get_stats_menu(*settings::sneak_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::sneak_mod_menu_inventory),
            icon_keys::sneak_mod);
        mp[stats_value::alchemy_mod] = std::make_unique<stat_config>(actor_value::kAlchemyModifier,
            menu_keys::alchemy_mod,
            *settings::alchemy_mod_string_ending,
            menu_util::get_stats_menu(*settings::alchemy_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::alchemy_mod_menu_inventory),
            icon_keys::alchemy_mod);
        mp[stats_value::speechcraft_mod] = std::make_unique<stat_config>(actor_value::kSpeechcraftModifier,
            menu_keys::speech_mod,
            *settings::speech_mod_string_ending,
            menu_util::get_stats_menu(*settings::speech_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::speech_mod_menu_inventory),
            icon_keys::speech_mod);
        mp[stats_value::enchanting_mod] = std::make_unique<stat_config>(actor_value::kEnchantingModifier,
            menu_keys::enchanting_mod,
            *settings::enchanting_mod_string_ending,
            menu_util::get_stats_menu(*settings::enchanting_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::enchanting_mod_menu_inventory),
            icon_keys::enchanting_mod);
        mp[stats_value::alteration_mod] = std::make_unique<stat_config>(actor_value::kAlterationModifier,
            menu_keys::alteration_mod,
            *settings::alteration_mod_string_ending,
            menu_util::get_stats_menu(*settings::alteration_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::alteration_mod_menu_inventory),
            icon_keys::alteration_mod);
        mp[stats_value::conjuration_mod] = std::make_unique<stat_config>(actor_value::kConjurationModifier,
            menu_keys::conjuration_mod,
            *settings::conjuration_mod_string_ending,
            menu_util::get_stats_menu(*settings::conjuration_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::conjuration_mod_menu_inventory),
            icon_keys::conjuration_mod);
        mp[stats_value::destruction_mod] = std::make_unique<stat_config>(actor_value::kDestructionModifier,
            menu_keys::destruction_mod,
            *settings::destruction_mod_string_ending,
            menu_util::get_stats_menu(*settings::destruction_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::destruction_mod_menu_inventory),
            icon_keys::destruction_mod);
        mp[stats_value::illusion_mod] = std::make_unique<stat_config>(actor_value::kIllusionModifier,
            menu_keys::illusion_mod,
            *settings::illusion_mod_string_ending,
            menu_util::get_stats_menu(*settings::illusion_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::illusion_mod_menu_inventory),
            icon_keys::illusion_mod);
        mp[stats_value::restoration_mod] = std::make_unique<stat_config>(actor_value::kRestorationModifier,
            menu_keys::restoration_mod,
            *settings::restoration_mod_string_ending,
            menu_util::get_stats_menu(*settings::restoration_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::restoration_mod_menu_inventory),
            icon_keys::restoration_mod);
        mp[stats_value::damage_arrow] = std::make_unique<stat_config>(actor_value::kNone,
            menu_keys::damage_arrow,
            menu_util::get_stats_menu(*settings::damage_arrow_menu),
            menu_util::get_stats_inventory_menu(*settings::damage_arrow_menu_inventory),
            icon_keys::damage_arrow);
        mp[stats_value::damage_left] = std::make_unique<stat_config>(actor_value::kNone,
            menu_keys::damage_left,
            menu_util::get_stats_menu(*settings::damage_left_menu),
            menu_util::get_stats_inventory_menu(*settings::damage_left_menu_inventory),
            icon_keys::damage_left);
        mp[stats_value::weapon_reach] = std::make_unique<stat_config>(actor_value::kNone,
            menu_keys::weapon_reach,
            menu_util::get_stats_menu(*settings::weapon_reach_menu),
            menu_util::get_stats_inventory_menu(*settings::weapon_reach_menu_inventory),
            icon_keys::weapon_reach);
        mp[stats_value::weapon_reach_left] = std::make_unique<stat_config>(actor_value::kNone,
            menu_keys::weapon_reach_left,
            menu_util::get_stats_menu(*settings::weapon_reach_left_menu),
            menu_util::get_stats_inventory_menu(*settings::weapon_reach_left_menu_inventory),
            icon_keys::weapon_reach_left);
        mp[stats_value::weapon_base_damage] = std::make_unique<stat_config>(actor_value::kNone,
            menu_keys::weapon_base_damage,
            menu_util::get_stats_menu(*settings::weapon_base_damage_menu),
            menu_util::get_stats_inventory_menu(*settings::weapon_base_damage_menu_inventory),
            icon_keys::weapon_base_damage);
        mp[stats_value::weapon_base_damage_left] = std::make_unique<stat_config>(actor_value::kNone,
            menu_keys::weapon_base_damage_left,
            menu_util::get_stats_menu(*settings::weapon_base_damage_left_menu),
            menu_util::get_stats_inventory_menu(*settings::weapon_base_damage_left_menu_inventory),
            icon_keys::weapon_base_damage_left);
        mp[stats_value::weapon_stagger] = std::make_unique<stat_config>(actor_value::kNone,
            menu_keys::weapon_stagger,
            menu_util::get_stats_menu(*settings::weapon_stagger_menu),
            menu_util::get_stats_inventory_menu(*settings::weapon_stagger_menu_inventory),
            icon_keys::weapon_stagger);
        mp[stats_value::weapon_stagger_left] = std::make_unique<stat_config>(actor_value::kNone,
            menu_keys::weapon_stagger_left,
            menu_util::get_stats_menu(*settings::weapon_stagger_left_menu),
            menu_util::get_stats_inventory_menu(*settings::weapon_stagger_left_menu_inventory),
            icon_keys::weapon_stagger_left);
        mp[stats_value::weapon_crit_damage_rating] = std::make_unique<stat_config>(actor_value::kNone,
            menu_keys::weapon_crit_damage_rating,
            menu_util::get_stats_menu(*settings::weapon_crit_damage_rating_menu),
            menu_util::get_stats_inventory_menu(*settings::weapon_crit_damage_rating_menu_inventory),
            icon_keys::weapon_crit_damage_rating);
        mp[stats_value::weapon_crit_damage_rating_left] = std::make_unique<stat_config>(actor_value::kNone,
            menu_keys::weapon_crit_damage_rating_left,
            menu_util::get_stats_menu(*settings::weapon_crit_damage_rating_left_menu),
            menu_util::get_stats_inventory_menu(*settings::weapon_crit_damage_rating_left_menu_inventory),
            icon_keys::weapon_crit_damage_rating_left);
        mp[stats_value::fall_damage_mod] = std::make_unique<stat_config>(actor_value::kNone,
            menu_keys::fall_damage_mod,
            *settings::fall_damage_mod_string_ending,
            menu_util::get_stats_menu(*settings::fall_damage_mod_menu),
            menu_util::get_stats_inventory_menu(*settings::fall_damage_mod_menu_inventory),
            menu_util::get_multiplier(*settings::fall_damage_mod_mult),
            icon_keys::fall_damage_mod);
        mp[stats_value::warmth] = std::make_unique<stat_config>(actor_value::kNone,
            menu_keys::warmth,
            menu_util::get_stats_menu(*settings::warmth_menu),
            menu_util::get_stats_inventory_menu(*settings::warmth_menu_inventory),
            icon_keys::warmth);
        return mp;
    }

    stat_setting() = default;
    stat_setting(const stat_setting&) = default;
    stat_setting(stat_setting&&) = delete;

    ~stat_setting() = default;

    stat_setting& operator=(const stat_setting&) = default;
    stat_setting& operator=(stat_setting&&) = delete;
};
