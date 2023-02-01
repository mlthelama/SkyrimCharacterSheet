#pragma once
#include "settings/gamesettings.h"
#include "utils/constants.h"
#include "utils/iconkeys.h"
#include "utils/utils.h"

class stat_config {
    using stats_inventory_menu_value = menu_util::stats_inventory_menu_value;
    using stats_menu_value = menu_util::stats_menu_value;
    using display_actor_value_type = value_util::display_actor_value_type;

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
        const int a_value_multiplier)
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
        const int a_value_multiplier,
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
        const int a_value_multiplier,
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
        const int a_value_multiplier,
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
        const display_actor_value_type a_display_type)
        : actor_(a_actor)
        , display_name_(a_display_name)
        , stats_menu_(a_stats_menu)
        , stats_inventory_menu_(a_stats_inventory_menu)
        , display_type_(a_display_type) {}

    stat_config(const RE::ActorValue a_actor,
        const std::string_view a_display_name,
        const stats_menu_value a_stats_menu,
        const stats_inventory_menu_value a_stats_inventory_menu,
        const display_actor_value_type a_display_type,
        const std::string_view a_icon)
        : actor_(a_actor)
        , display_name_(a_display_name)
        , stats_menu_(a_stats_menu)
        , stats_inventory_menu_(a_stats_inventory_menu)
        , display_type_(a_display_type)
        , icon_string_(a_icon) {}

    [[nodiscard]] RE::ActorValue get_actor() const { return actor_; }

    [[nodiscard]] std::string_view get_display_name() const { return display_name_; }

    std::string get_ending() { return ending_; }

    [[nodiscard]] stats_menu_value get_stats_menu() const { return stats_menu_; }

    [[nodiscard]] stats_inventory_menu_value get_stats_inventory_menu() const { return stats_inventory_menu_; }

    [[nodiscard]] int get_value_multiplier() const { return value_multiplier_; }

    [[nodiscard]] float get_cap() const { return cap_; }

    [[nodiscard]] display_actor_value_type get_show_base_permanent_value() const { return display_type_; }

    [[nodiscard]] std::string_view get_key_display() const { return display_name_; }

    [[nodiscard]] std::string_view get_icon_string() const { return icon_string_; }

    std::string get_value_display(const std::string& a_value) {
        if (!a_value.empty()) {
            logger::trace("display {} got value {}, building text ..."sv, display_name_, a_value);
            return ending_.empty() ? a_value : menu_util::build_value_string(a_value, ending_);
        }
        return "";
    }

    void log_stat_config([[maybe_unused]] stats_value a_stats_value) {
        logger::trace(
            "name {}, actor {}, displayName {} ending {}, statsMenu {}, statsInventoryMenu {}, valueMultiplier {}, cap {}, showPermAV {}, icon {}"sv,
            string_util::get_int_from_enum(a_stats_value),
            actor_,
            display_name_,
            ending_,
            string_util::get_int_from_enum(stats_menu_),
            string_util::get_int_from_enum(stats_inventory_menu_),
            value_multiplier_,
            cap_,
            string_util::get_int_from_enum(display_type_),
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
    int value_multiplier_ = const_static_multiplier;
    float cap_ = -1;
    value_util::display_actor_value_type display_type_ = display_actor_value_type::m_value;
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
        if (setting::get_show_resistance_cap()) {
            game_settings->get_and_set_settings();
        }

        auto get_display_type = value_util::get_display_actor_value_type(setting::get_display_av_type());

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
            setting::get_height_string_ending(),
            menu_util::get_stats_menu(setting::get_height_menu()),
            stats_inventory_menu_value::m_none);
        mp[stats_value::equipped_weight] = std::make_unique<stat_config>(actor_value::kNone,
            menu_keys::equipped_weight,
            setting::get_equipped_weight_string_ending(),
            menu_util::get_stats_menu(setting::get_equiped_weight_menu()),
            menu_util::get_stats_inventory_menu(setting::get_equiped_weight_menu_inventory()));
        mp[stats_value::weight] = std::make_unique<stat_config>(actor_value::kNone,
            menu_keys::weight,
            setting::get_weight_string_ending(),
            menu_util::get_stats_menu(setting::get_weight_menu()),
            stats_inventory_menu_value::m_none);
        mp[stats_value::armor] = std::make_unique<stat_config>(actor_value::kDamageResist,
            menu_keys::armor,
            menu_util::get_stats_menu(setting::get_armor_menu()),
            menu_util::get_stats_inventory_menu(setting::get_armor_menu_inventory()),
            icon_keys::armor);
        mp[stats_value::damage] = std::make_unique<stat_config>(actor_value::kNone,
            menu_keys::damage,
            menu_util::get_stats_menu(setting::get_damage_menu()),
            menu_util::get_stats_inventory_menu(setting::get_damage_menu_inventory()),
            icon_keys::damage);
        mp[stats_value::skill_trainings_this_level] = std::make_unique<stat_config>(actor_value::kNone,
            menu_keys::trainings_level,
            menu_util::get_stats_menu(setting::get_skill_trainings_this_level_menu()),
            stats_inventory_menu_value::m_none);
        mp[stats_value::health] = std::make_unique<stat_config>(actor_value::kHealth,
            menu_keys::health,
            menu_util::get_stats_menu(setting::get_health_menu()),
            menu_util::get_stats_inventory_menu(setting::get_health_menu_inventory()),
            get_display_type,
            icon_keys::health);
        mp[stats_value::health_rate_per] = std::make_unique<stat_config>(actor_value::kNone,
            menu_keys::health_rate,
            setting::get_health_rate_string_ending(),
            menu_util::get_stats_menu(setting::get_health_rate_menu()),
            menu_util::get_stats_inventory_menu(setting::get_health_rate_menu_inventory()),
            icon_keys::health_rate);
        mp[stats_value::magicka] = std::make_unique<stat_config>(actor_value::kMagicka,
            menu_keys::magicka,
            menu_util::get_stats_menu(setting::get_magicka_menu()),
            menu_util::get_stats_inventory_menu(setting::get_magicka_menu_inventory()),
            get_display_type,
            icon_keys::magicka);
        mp[stats_value::magicka_rate_per] = std::make_unique<stat_config>(actor_value::kNone,
            menu_keys::magicka_rate,
            setting::get_magicka_rate_string_ending(),
            menu_util::get_stats_menu(setting::get_magicka_rate_menu()),
            menu_util::get_stats_inventory_menu(setting::get_magicka_rate_menu_inventory()),
            icon_keys::magicka_rate);
        mp[stats_value::stamina] = std::make_unique<stat_config>(actor_value::kStamina,
            menu_keys::stamina,
            menu_util::get_stats_menu(setting::get_stamina_menu()),
            menu_util::get_stats_inventory_menu(setting::get_magicka_rate_menu_inventory()),
            get_display_type,
            icon_keys::stamina);
        mp[stats_value::stamina_rate_per] = std::make_unique<stat_config>(actor_value::kNone,
            menu_keys::stamina_rate,
            setting::get_stamina_rate_string_ending(),
            menu_util::get_stats_menu(setting::get_stamina_rate_menu()),
            menu_util::get_stats_inventory_menu(setting::get_stamina_menu_inventory()),
            icon_keys::stamina_rate);
        mp[stats_value::resist_damage] = std::make_unique<stat_config>(actor_value::kNone,
            menu_keys::resist_damage,
            setting::get_resist_damage_string_ending(),
            menu_util::get_stats_menu(setting::get_resist_damage_menu()),
            menu_util::get_stats_inventory_menu(setting::get_resist_damage_menu_inventory()),
            const_static_multiplier,
            game_settings->max_armor_resistance,
            icon_keys::resist_damage);
        mp[stats_value::resist_disease] = std::make_unique<stat_config>(actor_value::kResistDisease,
            menu_keys::resist_disease,
            setting::get_resist_disease_string_ending(),
            menu_util::get_stats_menu(setting::get_resist_disease_menu()),
            menu_util::get_stats_inventory_menu(setting::get_resist_disease_menu_inventory()),
            icon_keys::resist_disease);
        mp[stats_value::resist_poison] = std::make_unique<stat_config>(actor_value::kPoisonResist,
            menu_keys::resist_poison,
            setting::get_resist_poison_string_ending(),
            menu_util::get_stats_menu(setting::get_resist_poison_menu()),
            menu_util::get_stats_inventory_menu(setting::get_resist_poison_menu_inventory()),
            const_static_multiplier,
            game_settings->max_resistance,
            icon_keys::resist_poison);
        mp[stats_value::resist_fire] = std::make_unique<stat_config>(actor_value::kResistFire,
            menu_keys::resist_fire,
            setting::get_resist_fire_string_ending(),
            menu_util::get_stats_menu(setting::get_resist_fire_menu()),
            menu_util::get_stats_inventory_menu(setting::get_resist_fire_menu_inventory()),
            const_static_multiplier,
            game_settings->max_resistance,
            icon_keys::resist_fire);
        mp[stats_value::resist_shock] = std::make_unique<stat_config>(actor_value::kResistShock,
            menu_keys::resist_shock,
            setting::get_resist_shock_string_ending(),
            menu_util::get_stats_menu(setting::get_resist_shock_menu()),
            menu_util::get_stats_inventory_menu(setting::get_resist_shock_menu_inventory()),
            const_static_multiplier,
            game_settings->max_resistance,
            icon_keys::resist_shock);
        mp[stats_value::resist_frost] = std::make_unique<stat_config>(actor_value::kResistFrost,
            menu_keys::resist_frost,
            setting::get_resist_frost_string_ending(),
            menu_util::get_stats_menu(setting::get_resist_frost_menu()),
            menu_util::get_stats_inventory_menu(setting::get_resist_frost_menu_inventory()),
            const_static_multiplier,
            game_settings->max_resistance,
            icon_keys::resist_frost);
        mp[stats_value::resist_magic] = std::make_unique<stat_config>(actor_value::kResistMagic,
            menu_keys::resist_magic,
            setting::get_resist_magic_string_ending(),
            menu_util::get_stats_menu(setting::get_resist_magic_menu()),
            menu_util::get_stats_inventory_menu(setting::get_resist_magic_menu_inventory()),
            const_static_multiplier,
            game_settings->max_resistance,
            icon_keys::resist_magic);
        mp[stats_value::one_handed] = std::make_unique<stat_config>(actor_value::kOneHanded,
            menu_keys::one_handed,
            menu_util::get_stats_menu(setting::get_one_handed_menu()),
            menu_util::get_stats_inventory_menu(setting::get_one_handed_menu_inventory()),
            get_display_type,
            icon_keys::one_handed);
        mp[stats_value::two_handed] = std::make_unique<stat_config>(actor_value::kTwoHanded,
            menu_keys::two_handed,
            menu_util::get_stats_menu(setting::get_two_handed_menu()),
            menu_util::get_stats_inventory_menu(setting::get_two_handed_menu_inventory()),
            get_display_type,
            icon_keys::two_handed);
        mp[stats_value::archery] = std::make_unique<stat_config>(actor_value::kArchery,
            menu_keys::archery,
            menu_util::get_stats_menu(setting::get_archery_menu()),
            menu_util::get_stats_inventory_menu(setting::get_archery_menu_inventory()),
            get_display_type,
            icon_keys::archery);
        mp[stats_value::block] = std::make_unique<stat_config>(actor_value::kBlock,
            menu_keys::block,
            menu_util::get_stats_menu(setting::get_block_menu()),
            menu_util::get_stats_inventory_menu(setting::get_block_menu_inventory()),
            get_display_type,
            icon_keys::block);
        mp[stats_value::smithing] = std::make_unique<stat_config>(actor_value::kSmithing,
            menu_keys::smithing,
            menu_util::get_stats_menu(setting::get_smithing_menu()),
            menu_util::get_stats_inventory_menu(setting::get_smithing_menu_inventory()),
            get_display_type,
            icon_keys::smithing);
        mp[stats_value::heavy_armor] = std::make_unique<stat_config>(actor_value::kHeavyArmor,
            menu_keys::heavy_armor,
            menu_util::get_stats_menu(setting::get_heavy_armor_menu()),
            menu_util::get_stats_inventory_menu(setting::get_heavy_armor_menu_inventory()),
            get_display_type,
            icon_keys::heavy_armor);
        mp[stats_value::light_armor] = std::make_unique<stat_config>(actor_value::kLightArmor,
            menu_keys::light_armor,
            menu_util::get_stats_menu(setting::get_light_armor_menu()),
            menu_util::get_stats_inventory_menu(setting::get_light_armor_menu_inventory()),
            get_display_type,
            icon_keys::light_armor);
        if (setting::get_hand_to_hand()) {
            mp[stats_value::pickpocket] = std::make_unique<stat_config>(actor_value::kPickpocket,
                menu_keys::security,
                menu_util::get_stats_menu(setting::get_pickpocket_menu()),
                menu_util::get_stats_inventory_menu(setting::get_pickpocket_menu_inventory()),
                get_display_type,
                icon_keys::security);
            mp[stats_value::lockpicking] = std::make_unique<stat_config>(actor_value::kLockpicking,
                menu_keys::hand_to_hand,
                menu_util::get_stats_menu(setting::get_lockpicking_menu()),
                menu_util::get_stats_inventory_menu(setting::get_lockpicking_menu_inventory()),
                get_display_type,
                icon_keys::hand_to_hand);
        } else {
            mp[stats_value::pickpocket] = std::make_unique<stat_config>(actor_value::kPickpocket,
                menu_keys::pickpocket,
                menu_util::get_stats_menu(setting::get_pickpocket_menu()),
                menu_util::get_stats_inventory_menu(setting::get_pickpocket_menu_inventory()),
                get_display_type,
                icon_keys::pickpocket);
            mp[stats_value::lockpicking] = std::make_unique<stat_config>(actor_value::kLockpicking,
                menu_keys::lockpicking,
                menu_util::get_stats_menu(setting::get_lockpicking_menu()),
                menu_util::get_stats_inventory_menu(setting::get_lockpicking_menu_inventory()),
                get_display_type,
                icon_keys::lockpicking);
        }
        mp[stats_value::sneak] = std::make_unique<stat_config>(actor_value::kSneak,
            menu_keys::sneak,
            menu_util::get_stats_menu(setting::get_sneak_menu()),
            menu_util::get_stats_inventory_menu(setting::get_sneak_menu_inventory()),
            get_display_type,
            icon_keys::sneak);
        mp[stats_value::alchemy] = std::make_unique<stat_config>(actor_value::kAlchemy,
            menu_keys::alchemy,
            menu_util::get_stats_menu(setting::get_alchemy_menu()),
            menu_util::get_stats_inventory_menu(setting::get_alchemy_menu_inventory()),
            get_display_type,
            icon_keys::alchemy);
        mp[stats_value::speech] = std::make_unique<stat_config>(actor_value::kSpeech,
            menu_keys::speech,
            menu_util::get_stats_menu(setting::get_speech_menu()),
            menu_util::get_stats_inventory_menu(setting::get_speech_menu_inventory()),
            get_display_type,
            icon_keys::speech);
        mp[stats_value::enchanting] = std::make_unique<stat_config>(actor_value::kEnchanting,
            menu_keys::enchanting,
            menu_util::get_stats_menu(setting::get_enchanting_menu()),
            menu_util::get_stats_inventory_menu(setting::get_enchanting_menu_inventory()),
            get_display_type);
        mp[stats_value::alteration] = std::make_unique<stat_config>(actor_value::kAlteration,
            menu_keys::alteration,
            menu_util::get_stats_menu(setting::get_alteration_menu()),
            menu_util::get_stats_inventory_menu(setting::get_alteration_menu_inventory()),
            get_display_type,
            icon_keys::alteration);
        mp[stats_value::conjuration] = std::make_unique<stat_config>(actor_value::kConjuration,
            menu_keys::conjuration,
            menu_util::get_stats_menu(setting::get_conjuration_menu()),
            menu_util::get_stats_inventory_menu(setting::get_conjuration_menu_inventory()),
            get_display_type,
            icon_keys::conjuration);
        mp[stats_value::destruction] = std::make_unique<stat_config>(actor_value::kDestruction,
            menu_keys::destruction,
            menu_util::get_stats_menu(setting::get_destruction_menu()),
            menu_util::get_stats_inventory_menu(setting::get_destruction_menu_inventory()),
            get_display_type,
            icon_keys::destruction);
        mp[stats_value::illusion] = std::make_unique<stat_config>(actor_value::kIllusion,
            menu_keys::illusion,
            menu_util::get_stats_menu(setting::get_illusion_menu()),
            menu_util::get_stats_inventory_menu(setting::get_illusion_menu_inventory()),
            get_display_type,
            icon_keys::illusion);
        mp[stats_value::restoration] = std::make_unique<stat_config>(actor_value::kRestoration,
            menu_keys::restoration,
            menu_util::get_stats_menu(setting::get_restoration_menu()),
            menu_util::get_stats_inventory_menu(setting::get_restoration_menu_inventory()),
            get_display_type,
            icon_keys::restoration);
        mp[stats_value::one_handed_power_mod] = std::make_unique<stat_config>(actor_value::kOneHandedPowerModifier,
            menu_keys::one_handed_power_mod,
            menu_util::get_stats_menu(setting::get_one_handed_power_mod_menu()),
            menu_util::get_stats_inventory_menu(setting::get_one_handed_power_mod_menu_inventory()),
            icon_keys::one_handed_power_mod);
        mp[stats_value::two_handed_power_mod] = std::make_unique<stat_config>(actor_value::kTwoHandedPowerModifier,
            menu_keys::two_handed_power_mod,
            menu_util::get_stats_menu(setting::get_two_handed_power_mod_menu()),
            menu_util::get_stats_inventory_menu(setting::get_two_handed_power_mod_menu_inventory()),
            icon_keys::two_handed_power_mod);
        mp[stats_value::archery_power_mod] = std::make_unique<stat_config>(actor_value::kMarksmanPowerModifier,
            menu_keys::archery_power_mod,
            menu_util::get_stats_menu(setting::get_archery_power_mod_menu()),
            menu_util::get_stats_inventory_menu(setting::get_archery_power_mod_menu_inventory()),
            icon_keys::archery_power_mod);
        mp[stats_value::block_power_mod] = std::make_unique<stat_config>(actor_value::kBlockPowerModifier,
            menu_keys::block_power_mod,
            menu_util::get_stats_menu(setting::get_block_power_mod_menu()),
            menu_util::get_stats_inventory_menu(setting::get_block_power_mod_menu_inventory()),
            icon_keys::block_power_mod);
        mp[stats_value::smithing_power_mod] = std::make_unique<stat_config>(actor_value::kSmithingPowerModifier,
            menu_keys::smithing_power_mod,
            menu_util::get_stats_menu(setting::get_smithing_power_mod_menu()),
            menu_util::get_stats_inventory_menu(setting::get_smithing_power_mod_menu_inventory()),
            icon_keys::smithing_power_mod);
        mp[stats_value::heavy_armor_power_mod] = std::make_unique<stat_config>(actor_value::kHeavyArmorPowerModifier,
            menu_keys::heavy_armor_power_mod,
            menu_util::get_stats_menu(setting::get_heavy_armor_power_mod_menu()),
            menu_util::get_stats_inventory_menu(setting::get_heavy_armor_power_mod_menu_inventory()),
            icon_keys::heavy_armor_power_mod);
        mp[stats_value::light_armor_power_mod] = std::make_unique<stat_config>(actor_value::kLightArmorPowerModifier,
            menu_keys::light_armor_power_mod,
            menu_util::get_stats_menu(setting::get_light_armor_power_mod_menu()),
            menu_util::get_stats_inventory_menu(setting::get_light_armor_power_mod_menu_inventory()),
            icon_keys::light_armor_power_mod);
        if (setting::get_hand_to_hand()) {
            mp[stats_value::pickpocket_power_mod] = std::make_unique<stat_config>(actor_value::kPickpocketPowerModifier,
                menu_keys::security_power_mod,
                menu_util::get_stats_menu(setting::get_pickpocket_power_mod_menu()),
                menu_util::get_stats_inventory_menu(setting::get_pickpocket_power_mod_menu_inventory()),
                icon_keys::security_power_mod);
            mp[stats_value::lockpicking_power_mod] =
                std::make_unique<stat_config>(actor_value::kLockpickingPowerModifier,
                    menu_keys::hand_to_hand_power_mod,
                    menu_util::get_stats_menu(setting::get_lockpicking_power_mod_menu()),
                    menu_util::get_stats_inventory_menu(setting::get_lockpicking_power_mod_menu_inventory()),
                    icon_keys::hand_to_hand_power_mod);
        } else {
            mp[stats_value::pickpocket_power_mod] = std::make_unique<stat_config>(actor_value::kPickpocketPowerModifier,
                menu_keys::pickpocket_power_mod,
                menu_util::get_stats_menu(setting::get_pickpocket_power_mod_menu()),
                menu_util::get_stats_inventory_menu(setting::get_pickpocket_power_mod_menu_inventory()),
                icon_keys::pickpocket_power_mod);
            mp[stats_value::lockpicking_power_mod] =
                std::make_unique<stat_config>(actor_value::kLockpickingPowerModifier,
                    menu_keys::lockpicking_power_mod,
                    menu_util::get_stats_menu(setting::get_lockpicking_power_mod_menu()),
                    menu_util::get_stats_inventory_menu(setting::get_lockpicking_power_mod_menu_inventory()),
                    icon_keys::lockpicking_power_mod);
        }
        mp[stats_value::sneak_power_mod] = std::make_unique<stat_config>(actor_value::kSneakingPowerModifier,
            menu_keys::sneak_power_mod,
            menu_util::get_stats_menu(setting::get_sneak_power_mod_menu()),
            menu_util::get_stats_inventory_menu(setting::get_sneak_power_mod_menu_inventory()),
            icon_keys::sneak_power_mod);
        mp[stats_value::alchemy_power_mod] = std::make_unique<stat_config>(actor_value::kAlchemyPowerModifier,
            menu_keys::alchemy_power_mod,
            menu_util::get_stats_menu(setting::get_alchemy_power_mod_menu()),
            menu_util::get_stats_inventory_menu(setting::get_alchemy_power_mod_menu_inventory()),
            icon_keys::alchemy_power_mod);
        mp[stats_value::speech_power_mod] = std::make_unique<stat_config>(actor_value::kSpeechcraftPowerModifier,
            menu_keys::speech_power_mod,
            menu_util::get_stats_menu(setting::get_speech_power_mod_menu()),
            menu_util::get_stats_inventory_menu(setting::get_speech_power_mod_menu_inventory()),
            icon_keys::speech_power_mod);
        mp[stats_value::enchanting_power_mod] = std::make_unique<stat_config>(actor_value::kEnchantingPowerModifier,
            menu_keys::enchanting_power_mod,
            menu_util::get_stats_menu(setting::get_enchanting_power_mod_menu()),
            menu_util::get_stats_inventory_menu(setting::get_enchanting_power_mod_menu_inventory()),
            icon_keys::enchanting_power_mod);
        mp[stats_value::alteration_power_mod] = std::make_unique<stat_config>(actor_value::kAlterationPowerModifier,
            menu_keys::alteration_power_mod,
            menu_util::get_stats_menu(setting::get_alteration_power_mod_menu()),
            menu_util::get_stats_inventory_menu(setting::get_alteration_power_mod_menu_inventory()),
            icon_keys::alteration_power_mod);
        mp[stats_value::conjuration_power_mod] = std::make_unique<stat_config>(actor_value::kConjurationPowerModifier,
            menu_keys::conjuration_power_mod,
            menu_util::get_stats_menu(setting::get_conjuration_power_mod_menu()),
            menu_util::get_stats_inventory_menu(setting::get_conjuration_power_mod_menu_inventory()),
            icon_keys::conjuration_power_mod);
        mp[stats_value::destruction_power_mod] = std::make_unique<stat_config>(actor_value::kDestructionPowerModifier,
            menu_keys::destruction_power_mod,
            menu_util::get_stats_menu(setting::get_destruction_power_mod_menu()),
            menu_util::get_stats_inventory_menu(setting::get_destruction_power_mod_menu_inventory()),
            icon_keys::destruction_power_mod);
        mp[stats_value::illusion_power_mod] = std::make_unique<stat_config>(actor_value::kIllusionPowerModifier,
            menu_keys::illusion_power_mod,
            menu_util::get_stats_menu(setting::get_illusion_power_mod_menu()),
            menu_util::get_stats_inventory_menu(setting::get_illusion_power_mod_menu_inventory()),
            icon_keys::illusion_power_mod);
        mp[stats_value::restoration_power_mod] = std::make_unique<stat_config>(actor_value::kRestorationPowerModifier,
            menu_keys::restoration_power_mod,
            menu_util::get_stats_menu(setting::get_restoration_power_mod_menu()),
            menu_util::get_stats_inventory_menu(setting::get_restoration_power_mod_menu_inventory()),
            icon_keys::restoration_power_mod);
        mp[stats_value::speed_mult] = std::make_unique<stat_config>(actor_value::kSpeedMult,
            menu_keys::speed_mult,
            setting::get_speed_mult_string_ending(),
            menu_util::get_stats_menu(setting::get_speed_mult_menu()),
            menu_util::get_stats_inventory_menu(setting::get_speed_mult_menu_inventory()),
            icon_keys::speed_mult);
        mp[stats_value::inventory_weight] = std::make_unique<stat_config>(actor_value::kInventoryWeight,
            menu_keys::inventory_weight,
            setting::get_inventory_weight_string_ending(),
            menu_util::get_stats_menu(setting::get_inventory_weight_menu()),
            menu_util::get_stats_inventory_menu(setting::get_inventory_weight_menu_inventory()),
            icon_keys::inventory_weight);
        mp[stats_value::carry_weight] = std::make_unique<stat_config>(actor_value::kCarryWeight,
            menu_keys::carry_weight,
            setting::get_carry_weight_string_ending(),
            menu_util::get_stats_menu(setting::get_carry_weight_menu()),
            menu_util::get_stats_inventory_menu(setting::get_carry_weight_menu_inventory()),
            icon_keys::carry_weight);
        mp[stats_value::critical_chance] = std::make_unique<stat_config>(actor_value::kCriticalChance,
            menu_keys::critical_chance,
            setting::get_critical_chance_string_ending(),
            menu_util::get_stats_menu(setting::get_critical_chance_menu()),
            menu_util::get_stats_inventory_menu(setting::get_critical_chance_menu_inventory()),
            icon_keys::critical_chance);
        mp[stats_value::melee_damage] = std::make_unique<stat_config>(actor_value::kMeleeDamage,
            menu_keys::melee_damage,
            menu_util::get_stats_menu(setting::get_melee_damage_menu()),
            menu_util::get_stats_inventory_menu(setting::get_melee_damage_menu_inventory()),
            icon_keys::melee_damage);
        mp[stats_value::unarmed_damage] = std::make_unique<stat_config>(actor_value::kUnarmedDamage,
            menu_keys::unarmed_damage,
            menu_util::get_stats_menu(setting::get_unarmed_damage_menu()),
            menu_util::get_stats_inventory_menu(setting::get_unarmed_damage_menu_inventory()),
            icon_keys::unarmed_damage);
        mp[stats_value::absorb_chance] = std::make_unique<stat_config>(actor_value::kAbsorbChance,
            menu_keys::absorb_chance,
            setting::get_absorb_chance_string_ending(),
            menu_util::get_stats_menu(setting::get_absorb_chance_menu()),
            menu_util::get_stats_inventory_menu(setting::get_absorb_chance_menu_inventory()),
            icon_keys::absorb_chance);
        //we will not set the actor value kWeaponSpeedMult and kLeftWeaponSpeedMultiply here, because some genius thought it is nice that the value 0 and 1 means 100%
        // https://en.uesp.net/wiki/Skyrim_Mod:Actor_Value_Indices as documented here
        mp[stats_value::weapon_speed_mult] = std::make_unique<stat_config>(actor_value::kNone,
            menu_keys::weapon_speed_mult,
            setting::get_weapon_speed_mult_string_ending(),
            menu_util::get_stats_menu(setting::get_weapon_speed_mult_menu()),
            menu_util::get_stats_inventory_menu(setting::get_weapon_speed_mult_menu_inventory()),
            menu_util::get_multiplier(setting::get_weapon_speed_mult_mult()),
            icon_keys::weapon_speed_mult);
        mp[stats_value::left_weapon_speed_mult] = std::make_unique<stat_config>(actor_value::kNone,
            menu_keys::left_weapon_speed_mult,
            setting::get_left_weapon_speed_mult_string_ending(),
            menu_util::get_stats_menu(setting::get_left_weapon_speed_mult_menu()),
            menu_util::get_stats_inventory_menu(setting::get_left_weapon_speed_mult_menu_inventory()),
            menu_util::get_multiplier(setting::get_left_weapon_speed_mult_mult()),
            icon_keys::left_weapon_speed_mult);
        mp[stats_value::right_item_charge] = std::make_unique<stat_config>(actor_value::kRightItemCharge,
            menu_keys::right_item_charge,
            menu_util::get_stats_menu(setting::get_right_item_charge_menu()),
            menu_util::get_stats_inventory_menu(setting::get_right_item_charge_menu_inventory()),
            icon_keys::right_item_charge);
        mp[stats_value::left_item_charge] = std::make_unique<stat_config>(actor_value::kLeftItemCharge,
            menu_keys::left_item_charge,
            menu_util::get_stats_menu(setting::get_left_item_charge_menu()),
            menu_util::get_stats_inventory_menu(setting::get_left_item_charge_menu_inventory()),
            icon_keys::left_item_charge);
        mp[stats_value::armor_perks] = std::make_unique<stat_config>(actor_value::kArmorPerks,
            menu_keys::armor_perks,
            setting::get_armor_perks_string_ending(),
            menu_util::get_stats_menu(setting::get_armor_perks_menu()),
            menu_util::get_stats_inventory_menu(setting::get_armor_perks_menu_inventory()),
            menu_util::get_multiplier(setting::get_armor_perks_mult()),
            icon_keys::armor_perks);
        mp[stats_value::mass] = std::make_unique<stat_config>(actor_value::kMass,
            menu_keys::mass,
            menu_util::get_stats_menu(setting::get_mass_menu()),
            menu_util::get_stats_inventory_menu(setting::get_mass_menu_inventory()),
            icon_keys::mass);
        mp[stats_value::bow_stagger_bonus] = std::make_unique<stat_config>(actor_value::kBowStaggerBonus,
            menu_keys::bow_stagger_bonus,
            menu_util::get_stats_menu(setting::get_bow_stagger_bonus_menu()),
            menu_util::get_stats_inventory_menu(setting::get_bow_stagger_bonus_menu_inventory()),
            icon_keys::bow_stagger_bonus);
        mp[stats_value::bypass_vendor_keyword_check] =
            std::make_unique<stat_config>(actor_value::kBypassVendorKeywordCheck,
                menu_keys::bypass_vendor_keyword_check,
                menu_util::get_stats_menu(setting::get_bypass_vendor_keyword_check_menu()),
                stats_inventory_menu_value::m_none,
                icon_keys::bypass_vendor_keyword_check);
        mp[stats_value::bypass_vendor_stolen_check] =
            std::make_unique<stat_config>(actor_value::kBypassVendorStolenCheck,
                menu_keys::bypass_vendor_stolen_check,
                menu_util::get_stats_menu(setting::get_bypass_vendor_stolen_check_menu()),
                stats_inventory_menu_value::m_none,
                icon_keys::bypass_vendor_stolen_check);
        mp[stats_value::bow_speed_bonus] = std::make_unique<stat_config>(actor_value::kBowSpeedBonus,
            menu_keys::bow_speed_bonus,
            setting::get_bow_speed_bonus_string_ending(),
            menu_util::get_stats_menu(setting::get_bow_speed_bonus_menu()),
            menu_util::get_stats_inventory_menu(setting::get_bow_speed_bonus_menu_inventory()),
            icon_keys::bow_speed_bonus);
        mp[stats_value::shout_recovery_mult] = std::make_unique<stat_config>(actor_value::kShoutRecoveryMult,
            menu_keys::shout_recovery_mult,
            setting::get_shout_recovery_mult_string_ending(),
            menu_util::get_stats_menu(setting::get_shout_recovery_mult_menu()),
            menu_util::get_stats_inventory_menu(setting::get_shout_recovery_mult_menu_inventory()),
            menu_util::get_multiplier(setting::get_shout_recovery_mult_mult()),
            icon_keys::shout_recovery_mult);
        mp[stats_value::movement_noise_mult] = std::make_unique<stat_config>(actor_value::kMovementNoiseMult,
            menu_keys::movement_noise_mult,
            setting::get_movement_noise_mult_string_ending(),
            menu_util::get_stats_menu(setting::get_movement_noise_mult_menu()),
            menu_util::get_stats_inventory_menu(setting::get_movement_noise_mult_menu_inventory()),
            menu_util::get_multiplier(setting::get_movement_noise_mult_mult()),
            icon_keys::movement_noise_mult);
        mp[stats_value::dragon_souls] = std::make_unique<stat_config>(actor_value::kDragonSouls,
            menu_keys::dragon_souls,
            menu_util::get_stats_menu(setting::get_dragon_souls_menu()),
            stats_inventory_menu_value::m_none,
            icon_keys::dragon_souls);
        mp[stats_value::combat_health_regen_multiply] =
            std::make_unique<stat_config>(actor_value::kCombatHealthRegenMultiply,
                menu_keys::combat_health_regen_mult,
                setting::get_combat_health_regen_multiply_string_ending(),
                menu_util::get_stats_menu(setting::get_combat_health_regen_multiply_menu()),
                stats_inventory_menu_value::m_none,
                menu_util::get_multiplier(setting::get_combat_health_regen_multiply_mult()),
                icon_keys::combat_health_regen_mult);
        mp[stats_value::attack_damage_mult] = std::make_unique<stat_config>(actor_value::kAttackDamageMult,
            menu_keys::attack_damage_mult,
            setting::get_attack_damage_mult_string_ending(),
            menu_util::get_stats_menu(setting::get_attack_damage_mult_menu()),
            menu_util::get_stats_inventory_menu(setting::get_attack_damage_mult_menu_inventory()),
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
            setting::get_reflect_damage_string_ending(),
            menu_util::get_stats_menu(setting::get_reflect_damage_menu()),
            menu_util::get_stats_inventory_menu(setting::get_reflect_damage_menu_inventory()),
            icon_keys::reflect_damage);
        mp[stats_value::one_handed_mod] = std::make_unique<stat_config>(actor_value::kOneHandedModifier,
            menu_keys::one_handed_mod,
            setting::get_one_handed_mod_string_ending(),
            menu_util::get_stats_menu(setting::get_one_handed_mod_menu()),
            menu_util::get_stats_inventory_menu(setting::get_one_handed_mod_menu_inventory()),
            icon_keys::one_handed_mod);
        mp[stats_value::two_handed_mod] = std::make_unique<stat_config>(actor_value::kTwoHandedModifier,
            menu_keys::two_handed_mod,
            setting::get_two_handed_mod_string_ending(),
            menu_util::get_stats_menu(setting::get_two_handed_mod_menu()),
            menu_util::get_stats_inventory_menu(setting::get_two_handed_mod_menu_inventory()),
            icon_keys::two_handed_mod);
        mp[stats_value::marksman_mod] = std::make_unique<stat_config>(actor_value::kMarksmanModifier,
            menu_keys::archery_mod,
            setting::get_archery_mod_string_ending(),
            menu_util::get_stats_menu(setting::get_archery_mod_menu()),
            menu_util::get_stats_inventory_menu(setting::get_archery_mod_menu_inventory()),
            icon_keys::archery_mod);
        mp[stats_value::block_mod] = std::make_unique<stat_config>(actor_value::kBlockModifier,
            menu_keys::block_mod,
            setting::get_block_mod_string_ending(),
            menu_util::get_stats_menu(setting::get_block_mod_menu()),
            menu_util::get_stats_inventory_menu(setting::get_block_mod_menu_inventory()),
            icon_keys::block_mod);
        mp[stats_value::smithing_mod] = std::make_unique<stat_config>(actor_value::kSmithingModifier,
            menu_keys::smithing_mod,
            setting::get_smithing_mod_string_ending(),
            menu_util::get_stats_menu(setting::get_smithing_mod_menu()),
            menu_util::get_stats_inventory_menu(setting::get_smithing_mod_menu_inventory()),
            icon_keys::smithing_mod);
        mp[stats_value::heavy_armor_mod] = std::make_unique<stat_config>(actor_value::kHeavyArmorModifier,
            menu_keys::heavy_armor_mod,
            setting::get_heavy_armor_mod_string_ending(),
            menu_util::get_stats_menu(setting::get_heavy_armor_mod_menu()),
            menu_util::get_stats_inventory_menu(setting::get_heavy_armor_mod_menu_inventory()),
            icon_keys::heavy_armor_mod);
        mp[stats_value::light_armor_mod] = std::make_unique<stat_config>(actor_value::kLightArmorModifier,
            menu_keys::light_armor_mod,
            setting::get_light_armor_mod_string_ending(),
            menu_util::get_stats_menu(setting::get_light_armor_mod_menu()),
            menu_util::get_stats_inventory_menu(setting::get_light_armor_mod_menu_inventory()),
            icon_keys::light_armor_mod);
        if (setting::get_hand_to_hand()) {
            mp[stats_value::pickpocket_mod] = std::make_unique<stat_config>(actor_value::kPickpocketModifier,
                menu_keys::security_mod,
                setting::get_pickpocket_mod_string_ending(),
                menu_util::get_stats_menu(setting::get_pickpocket_mod_menu()),
                menu_util::get_stats_inventory_menu(setting::get_pickpocket_mod_menu_inventory()),
                icon_keys::security_mod);
            mp[stats_value::lockpicking_mod] = std::make_unique<stat_config>(actor_value::kLockpickingModifier,
                menu_keys::hand_to_hand_mod,
                setting::get_lockpicking_mod_string_ending(),
                menu_util::get_stats_menu(setting::get_lockpicking_mod_menu()),
                menu_util::get_stats_inventory_menu(setting::get_lockpicking_mod_menu_inventory()),
                icon_keys::hand_to_hand_mod);
        } else {
            mp[stats_value::pickpocket_mod] = std::make_unique<stat_config>(actor_value::kPickpocketModifier,
                menu_keys::pickpocket_mod,
                setting::get_pickpocket_mod_string_ending(),
                menu_util::get_stats_menu(setting::get_pickpocket_mod_menu()),
                menu_util::get_stats_inventory_menu(setting::get_pickpocket_mod_menu_inventory()),
                icon_keys::pickpocket_mod);
            mp[stats_value::lockpicking_mod] = std::make_unique<stat_config>(actor_value::kLockpickingModifier,
                menu_keys::lockpicking_mod,
                setting::get_lockpicking_mod_string_ending(),
                menu_util::get_stats_menu(setting::get_lockpicking_mod_menu()),
                menu_util::get_stats_inventory_menu(setting::get_lockpicking_mod_menu_inventory()),
                icon_keys::lockpicking_mod);
        }
        mp[stats_value::sneaking_mod] = std::make_unique<stat_config>(actor_value::kSneakingModifier,
            menu_keys::sneak_mod,
            setting::get_sneak_mod_string_ending(),
            menu_util::get_stats_menu(setting::get_sneak_mod_menu()),
            menu_util::get_stats_inventory_menu(setting::get_sneak_mod_menu_inventory()),
            icon_keys::sneak_mod);
        mp[stats_value::alchemy_mod] = std::make_unique<stat_config>(actor_value::kAlchemyModifier,
            menu_keys::alchemy_mod,
            setting::get_alchemy_mod_string_ending(),
            menu_util::get_stats_menu(setting::get_alchemy_mod_menu()),
            menu_util::get_stats_inventory_menu(setting::get_alchemy_mod_menu_inventory()),
            icon_keys::alchemy_mod);
        mp[stats_value::speechcraft_mod] = std::make_unique<stat_config>(actor_value::kSpeechcraftModifier,
            menu_keys::speech_mod,
            setting::get_speech_mod_string_ending(),
            menu_util::get_stats_menu(setting::get_speech_mod_menu()),
            menu_util::get_stats_inventory_menu(setting::get_speech_mod_menu_inventory()),
            icon_keys::speech_mod);
        mp[stats_value::enchanting_mod] = std::make_unique<stat_config>(actor_value::kEnchantingModifier,
            menu_keys::enchanting_mod,
            setting::get_enchanting_mod_string_ending(),
            menu_util::get_stats_menu(setting::get_enchanting_mod_menu()),
            menu_util::get_stats_inventory_menu(setting::get_enchanting_mod_menu_inventory()),
            icon_keys::enchanting_mod);
        mp[stats_value::alteration_mod] = std::make_unique<stat_config>(actor_value::kAlterationModifier,
            menu_keys::alteration_mod,
            setting::get_alteration_mod_string_ending(),
            menu_util::get_stats_menu(setting::get_alteration_mod_menu()),
            menu_util::get_stats_inventory_menu(setting::get_alteration_mod_menu_inventory()),
            icon_keys::alteration_mod);
        mp[stats_value::conjuration_mod] = std::make_unique<stat_config>(actor_value::kConjurationModifier,
            menu_keys::conjuration_mod,
            setting::get_conjuration_mod_string_ending(),
            menu_util::get_stats_menu(setting::get_conjuration_mod_menu()),
            menu_util::get_stats_inventory_menu(setting::get_conjuration_mod_menu_inventory()),
            icon_keys::conjuration_mod);
        mp[stats_value::destruction_mod] = std::make_unique<stat_config>(actor_value::kDestructionModifier,
            menu_keys::destruction_mod,
            setting::get_destruction_mod_string_ending(),
            menu_util::get_stats_menu(setting::get_destruction_mod_menu()),
            menu_util::get_stats_inventory_menu(setting::get_destruction_mod_menu_inventory()),
            icon_keys::destruction_mod);
        mp[stats_value::illusion_mod] = std::make_unique<stat_config>(actor_value::kIllusionModifier,
            menu_keys::illusion_mod,
            setting::get_illusion_mod_string_ending(),
            menu_util::get_stats_menu(setting::get_illusion_mod_menu()),
            menu_util::get_stats_inventory_menu(setting::get_illusion_mod_menu_inventory()),
            icon_keys::illusion_mod);
        mp[stats_value::restoration_mod] = std::make_unique<stat_config>(actor_value::kRestorationModifier,
            menu_keys::restoration_mod,
            setting::get_restoration_mod_string_ending(),
            menu_util::get_stats_menu(setting::get_restoration_mod_menu()),
            menu_util::get_stats_inventory_menu(setting::get_restoration_mod_menu_inventory()),
            icon_keys::restoration_mod);
        mp[stats_value::damage_arrow] = std::make_unique<stat_config>(actor_value::kNone,
            menu_keys::damage_arrow,
            menu_util::get_stats_menu(setting::get_damage_arrow_menu()),
            menu_util::get_stats_inventory_menu(setting::get_damage_arrow_menu_inventory()),
            icon_keys::damage_arrow);
        mp[stats_value::damage_left] = std::make_unique<stat_config>(actor_value::kNone,
            menu_keys::damage_left,
            menu_util::get_stats_menu(setting::get_damage_left_menu()),
            menu_util::get_stats_inventory_menu(setting::get_damage_left_menu_inventory()),
            icon_keys::damage_left);
        mp[stats_value::weapon_reach] = std::make_unique<stat_config>(actor_value::kNone,
            menu_keys::weapon_reach,
            menu_util::get_stats_menu(setting::get_weapon_reach_menu()),
            menu_util::get_stats_inventory_menu(setting::get_weapon_reach_menu_inventory()),
            icon_keys::weapon_reach);
        mp[stats_value::weapon_reach_left] = std::make_unique<stat_config>(actor_value::kNone,
            menu_keys::weapon_reach_left,
            menu_util::get_stats_menu(setting::get_weapon_reach_left_menu()),
            menu_util::get_stats_inventory_menu(setting::get_weapon_reach_left_menu_inventory()),
            icon_keys::weapon_reach_left);
        mp[stats_value::weapon_base_damage] = std::make_unique<stat_config>(actor_value::kNone,
            menu_keys::weapon_base_damage,
            menu_util::get_stats_menu(setting::get_weapon_base_damage_menu()),
            menu_util::get_stats_inventory_menu(setting::get_weapon_base_damage_menu_inventory()),
            icon_keys::weapon_base_damage);
        mp[stats_value::weapon_base_damage_left] = std::make_unique<stat_config>(actor_value::kNone,
            menu_keys::weapon_base_damage_left,
            menu_util::get_stats_menu(setting::get_weapon_base_damage_left_menu()),
            menu_util::get_stats_inventory_menu(setting::get_weapon_base_damage_left_menu_inventory()),
            icon_keys::weapon_base_damage_left);
        mp[stats_value::weapon_stagger] = std::make_unique<stat_config>(actor_value::kNone,
            menu_keys::weapon_stagger,
            menu_util::get_stats_menu(setting::get_weapon_stagger_menu()),
            menu_util::get_stats_inventory_menu(setting::get_weapon_stagger_menu_inventory()),
            icon_keys::weapon_stagger);
        mp[stats_value::weapon_stagger_left] = std::make_unique<stat_config>(actor_value::kNone,
            menu_keys::weapon_stagger_left,
            menu_util::get_stats_menu(setting::get_weapon_stagger_left_menu()),
            menu_util::get_stats_inventory_menu(setting::get_weapon_stagger_left_menu_inventory()),
            icon_keys::weapon_stagger_left);
        mp[stats_value::weapon_crit_damage_rating] = std::make_unique<stat_config>(actor_value::kNone,
            menu_keys::weapon_crit_damage_rating,
            menu_util::get_stats_menu(setting::get_weapon_crit_damage_rating_menu()),
            menu_util::get_stats_inventory_menu(setting::get_weapon_crit_damage_rating_menu_inventory()),
            icon_keys::weapon_crit_damage_rating);
        mp[stats_value::weapon_crit_damage_rating_left] = std::make_unique<stat_config>(actor_value::kNone,
            menu_keys::weapon_crit_damage_rating_left,
            menu_util::get_stats_menu(setting::get_weapon_crit_damage_rating_left_menu()),
            menu_util::get_stats_inventory_menu(setting::get_weapon_crit_damage_rating_left_menu_inventory()),
            icon_keys::weapon_crit_damage_rating_left);
        mp[stats_value::fall_damage_mod] = std::make_unique<stat_config>(actor_value::kNone,
            menu_keys::fall_damage_mod,
            setting::get_fall_damage_mod_string_ending(),
            menu_util::get_stats_menu(setting::get_fall_damage_mod_menu()),
            menu_util::get_stats_inventory_menu(setting::get_fall_damage_mod_menu_inventory()),
            menu_util::get_multiplier(setting::get_fall_damage_mod_mult()),
            icon_keys::fall_damage_mod);
        mp[stats_value::warmth] = std::make_unique<stat_config>(actor_value::kNone,
            menu_keys::warmth,
            menu_util::get_stats_menu(setting::get_warmth_menu()),
            menu_util::get_stats_inventory_menu(setting::get_warmth_menu_inventory()),
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
