#pragma once

struct settings {
    using i_setting = AutoTOML::ISetting;
    using bool_setting = AutoTOML::bSetting;
    using str_setting = AutoTOML::sSetting;
    using int_setting = AutoTOML::iSetting;

    static void load() {
        try {
            const auto table = toml::parse_file("Data/SKSE/Plugins/ShowStats.toml"s);
            for (const auto& setting : i_setting::get_settings()) { setting->load(table); }
        } catch (const toml::parse_error& ex) {
            std::ostringstream ss;
            ss << "Error parsing file \'" << *ex.source().path << "\':\n"
                << '\t' << ex.description() << '\n'
                << "\t\t(" << ex.source().begin << ')';
            logger::error(ss.str());
            throw std::runtime_error("failed to load settings"s);
        }
    }

    static inline const char* const_undefined = "<undef>";

    //string naming should be removed, we should just save keys in a const file
    //this needs a rework of the flash file, the setter, and the forms, should not be to bad

    static inline int_setting log_level{ "General"s, "logLevel"s, 0 };
    static inline int_setting open_menu_button{ "General"s, "openMenuButton", -1 };
    static inline int_setting open_faction_menu_button{ "General"s, "openNextMenuButton"s, 0 };
    static inline bool_setting pause_game{ "General"s, "pauseGame"s, true };
    static inline bool_setting show_inventory_stats{ "General"s, "showInventoryStats"s, true };
    static inline bool_setting show_inventory_stats_auto_open{ "General"s, "showInventoryStatsAutoOpen"s, true };
    static inline int_setting show_inventory_button{ "General"s, "showInventoryButton"s, 0 };
    static inline bool_setting display_permanent_av{ "General"s, "displayPermanentAV"s, true };

    static inline bool_setting skyrim_unbound{ "Mods"s, "skyrimUnbound"s, true };

    static inline bool_setting show_resistance_cap{ "specialHandling"s, "showResistanceCap"s, true };

    //stat titles
    static inline str_setting show_stats_title_title{ "showStatsTitle"s, "title"s, const_undefined };
    static inline str_setting show_stats_title_player{ "showStatsTitle"s, "player"s, const_undefined };
    static inline str_setting show_stats_title_attack{ "showStatsTitle"s, "attack"s, const_undefined };
    static inline str_setting show_stats_title_defence{ "showStatsTitle"s, "defence"s, const_undefined };
    static inline str_setting show_stats_title_magic{ "showStatsTitle"s, "magic"s, const_undefined };
    static inline str_setting show_stats_title_thief{ "showStatsTitle"s, "thief"s, const_undefined };
    static inline str_setting show_stats_title_warrior{ "showStatsTitle"s, "warrior"s, const_undefined };

    static inline bool_setting show_stat_sdisplay_zero{ "showStatsSpecial"s, "displayZero"s, true };

    //naming
    static inline str_setting name_string{ "showStatsName"s, "name"s, const_undefined };
    static inline str_setting race_string{ "showStatsName"s, "race"s, const_undefined };
    static inline str_setting level_string{ "showStatsName"s, "level"s, const_undefined };
    static inline str_setting perk_count_string{ "showStatsName"s, "perkCount"s, const_undefined };
    static inline str_setting height_string{ "showStatsName"s, "height"s, const_undefined };
    static inline str_setting equipped_weight_string{ "showStatsName"s, "equipedWeight"s, const_undefined };
    static inline str_setting weight_string{ "showStatsName"s, "weight"s, const_undefined };
    static inline str_setting armor_string{ "showStatsName"s, "armor"s, const_undefined };
    static inline str_setting damage_string{ "showStatsName"s, "damage"s, const_undefined };
    static inline str_setting skill_trainings_this_level_string{ "showStatsName"s,
                                                                 "skillTrainingsThisLevel"s,
                                                                 const_undefined };
    static inline str_setting health_string{ "showStatsName"s, "health"s, const_undefined };
    static inline str_setting health_rate_string{ "showStatsName"s, "healthRatePer"s, const_undefined };
    static inline str_setting magicka_string{ "showStatsName"s, "magicka"s, const_undefined };
    static inline str_setting magicka_rate_string{ "showStatsName"s, "magickaRatePer"s, const_undefined };
    static inline str_setting stamina_string{ "showStatsName"s, "stamina"s, const_undefined };
    static inline str_setting stamina_rate_string{ "showStatsName"s, "staminaRatePer"s, const_undefined };
    static inline str_setting resist_damage_string{ "showStatsName"s, "resistDamage"s, const_undefined };
    static inline str_setting resistDiseaseString{ "showStatsName"s, "resistDisease"s, const_undefined };
    static inline str_setting resistPoisonString{ "showStatsName"s, "resistPoison"s, const_undefined };
    static inline str_setting resistFireString{ "showStatsName"s, "resistFire"s, const_undefined };
    static inline str_setting resistShockString{ "showStatsName"s, "resistShock"s, const_undefined };
    static inline str_setting resistFrostString{ "showStatsName"s, "resistFrost"s, const_undefined };
    static inline str_setting resistMagicString{ "showStatsName"s, "resistMagic"s, const_undefined };
    static inline str_setting oneHandedString{ "showStatsName"s, "oneHanded"s, const_undefined };
    static inline str_setting twoHandedString{ "showStatsName"s, "twoHanded"s, const_undefined };
    static inline str_setting archeryString{ "showStatsName"s, "archery"s, const_undefined };
    static inline str_setting blockString{ "showStatsName"s, "block"s, const_undefined };
    static inline str_setting smithingString{ "showStatsName"s, "smithing"s, const_undefined };
    static inline str_setting heavyArmorString{ "showStatsName"s, "heavyArmor"s, const_undefined };
    static inline str_setting lightArmorString{ "showStatsName"s, "lightArmor"s, const_undefined };
    static inline str_setting pickpocketString{ "showStatsName"s, "pickpocket"s, const_undefined };
    static inline str_setting lockpickingString{ "showStatsName"s, "lockpicking"s, const_undefined };
    static inline str_setting sneakString{ "showStatsName"s, "sneak"s, const_undefined };
    static inline str_setting alchemyString{ "showStatsName"s, "alchemy"s, const_undefined };
    static inline str_setting speechString{ "showStatsName"s, "speech"s, const_undefined };
    static inline str_setting enchantingString{ "showStatsName"s, "enchanting"s, const_undefined };
    static inline str_setting alterationString{ "showStatsName"s, "alteration"s, const_undefined };
    static inline str_setting conjurationString{ "showStatsName"s, "conjuration"s, const_undefined };
    static inline str_setting destructionString{ "showStatsName"s, "destruction"s, const_undefined };
    static inline str_setting illusionString{ "showStatsName"s, "illusion"s, const_undefined };
    static inline str_setting restorationString{ "showStatsName"s, "restoration"s, const_undefined };
    static inline str_setting oneHandedPowerModString{ "showStatsName"s, "oneHandedPowerMod"s, const_undefined };
    static inline str_setting twoHandedPowerModString{ "showStatsName"s, "twoHandedPowerMod"s, const_undefined };
    static inline str_setting archeryPowerModString{ "showStatsName"s, "archeryPowerMod"s, const_undefined };
    static inline str_setting blockPowerModString{ "showStatsName"s, "blockPowerMod"s, const_undefined };
    static inline str_setting smithingPowerModString{ "showStatsName"s, "smithingPowerMod"s, const_undefined };
    static inline str_setting heavyArmorPowerModString{ "showStatsName"s, "heavyArmorPowerMod"s, const_undefined };
    static inline str_setting lightArmorPowerModString{ "showStatsName"s, "lightArmorPowerMod"s, const_undefined };
    static inline str_setting pickpocketPowerModString{ "showStatsName"s, "pickpocketPowerMod"s, const_undefined };
    static inline str_setting lockpickingPowerModString{ "showStatsName"s, "lockpickingPowerMod"s, const_undefined };
    static inline str_setting sneakPowerModString{ "showStatsName"s, "sneakPowerMod"s, const_undefined };
    static inline str_setting alchemyPowerModString{ "showStatsName"s, "alchemyPowerMod"s, const_undefined };
    static inline str_setting speechPowerModString{ "showStatsName"s, "speechPowerMod"s, const_undefined };
    static inline str_setting enchantingPowerModString{ "showStatsName"s, "enchantingPowerMod"s, const_undefined };
    static inline str_setting alterationPowerModString{ "showStatsName"s, "alterationPowerMod"s, const_undefined };
    static inline str_setting conjurationPowerModString{ "showStatsName"s, "conjurationPowerMod"s, const_undefined };
    static inline str_setting destructionPowerModString{ "showStatsName"s, "destructionPowerMod"s, const_undefined };
    static inline str_setting illusionPowerModString{ "showStatsName"s, "illusionPowerMod"s, const_undefined };
    static inline str_setting restorationPowerModString{ "showStatsName"s, "restorationPowerMod"s, const_undefined };
    static inline str_setting speedMultString{ "showStatsName"s, "speedMult"s, const_undefined };
    static inline str_setting inventoryWeightString{ "showStatsName"s, "inventoryWeight"s, const_undefined };
    static inline str_setting carryWeightString{ "showStatsName"s, "carryWeight"s, const_undefined };
    static inline str_setting criticalChanceString{ "showStatsName"s, "criticalChance"s, const_undefined };
    static inline str_setting meleeDamageString{ "showStatsName"s, "meleeDamage"s, const_undefined };
    static inline str_setting unarmedDamageString{ "showStatsName"s, "unarmedDamage"s, const_undefined };
    static inline str_setting absorbChanceString{ "showStatsName"s, "absorbChance"s, const_undefined };
    static inline str_setting weaponSpeedMultString{ "showStatsName"s, "weaponSpeedMult"s, const_undefined };
    static inline str_setting bowSpeedBonusString{ "showStatsName"s, "bowSpeedBonus"s, const_undefined };
    static inline str_setting shoutRecoveryMultString{ "showStatsName"s, "shoutRecoveryMult"s, const_undefined };
    static inline str_setting movementNoiseMultString{ "showStatsName"s, "movementNoiseMult"s, const_undefined };
    static inline str_setting dragonSoulsString{ "showStatsName"s, "dragonSouls"s, const_undefined };
    static inline str_setting combatHealthRegenMultiplyString{ "showStatsName"s,
                                                               "combatHealthRegenMultiply"s,
                                                               const_undefined };
    static inline str_setting attackDamageMultString{ "showStatsName"s, "attackDamageMult"s, const_undefined };
    static inline str_setting beastString{ "showStatsName"s, "beast"s, const_undefined };
    static inline str_setting xpString{ "showStatsName"s, "xp"s, const_undefined };
    static inline str_setting reflectDamageString{ "showStatsName"s, "reflectDamage"s, const_undefined };
    static inline str_setting oneHandedModString{ "showStatsName"s, "oneHandedMod"s, const_undefined };
    static inline str_setting twoHandedModString{ "showStatsName"s, "twoHandedMod"s, const_undefined };
    static inline str_setting archeryModString{ "showStatsName"s, "archeryMod"s, const_undefined };
    static inline str_setting blockModString{ "showStatsName"s, "blockMod"s, const_undefined };
    static inline str_setting smithingModString{ "showStatsName"s, "smithingMod"s, const_undefined };
    static inline str_setting heavyArmorModString{ "showStatsName"s, "heavyArmorMod"s, const_undefined };
    static inline str_setting lightArmorModString{ "showStatsName"s, "lightArmorMod"s, const_undefined };
    static inline str_setting pickpocketModString{ "showStatsName"s, "pickpocketMod"s, const_undefined };
    static inline str_setting lockpickingModString{ "showStatsName"s, "lockpickingMod"s, const_undefined };
    static inline str_setting sneakModString{ "showStatsName"s, "sneakMod"s, const_undefined };
    static inline str_setting alchemyModString{ "showStatsName"s, "alchemyMod"s, const_undefined };
    static inline str_setting speechModString{ "showStatsName"s, "speechMod"s, const_undefined };
    static inline str_setting enchantingModString{ "showStatsName"s, "enchantingMod"s, const_undefined };
    static inline str_setting alterationModString{ "showStatsName"s, "alterationMod"s, const_undefined };
    static inline str_setting conjurationModString{ "showStatsName"s, "conjurationMod"s, const_undefined };
    static inline str_setting destructionModString{ "showStatsName"s, "destructionMod"s, const_undefined };
    static inline str_setting illusionModString{ "showStatsName"s, "illusionMod"s, const_undefined };
    static inline str_setting restorationModString{ "showStatsName"s, "restorationMod"s, const_undefined };
    static inline str_setting damageArrowString{ "showStatsName"s, "damageArrow"s, const_undefined };
    static inline str_setting damageLeftString{ "showStatsName"s, "damageLeft"s, const_undefined };
    static inline str_setting leftWeaponSpeedMultString{ "showStatsName"s, "leftWeaponSpeedMult"s, const_undefined };
    static inline str_setting rightItemChargeString{ "showStatsName"s, "rightItemCharge"s, const_undefined };
    static inline str_setting leftItemChargStringe{ "showStatsName"s, "leftItemCharge"s, const_undefined };
    static inline str_setting armorPerksString{ "showStatsName"s, "armorPerks"s, const_undefined };
    static inline str_setting massString{ "showStatsName"s, "mass"s, const_undefined };
    static inline str_setting bowStaggerBonusString{ "showStatsName"s, "bowStaggerBonus"s, const_undefined };
    static inline str_setting bypassVendorKeywordCheckString{ "showStatsName"s,
                                                              "bypassVendorKeywordCheck"s,
                                                              const_undefined };
    static inline str_setting bypassVendorStolenCheckString{ "showStatsName"s,
                                                             "bypassVendorStolenCheck"s,
                                                             const_undefined };
    static inline str_setting weaponReachString{ "showStatsName"s, "weaponReach"s, const_undefined };
    static inline str_setting weaponReachLeftString{ "showStatsName"s, "weaponReachLeft"s, const_undefined };
    static inline str_setting weaponBaseDamageString{ "showStatsName"s, "weaponBaseDamage"s, const_undefined };
    static inline str_setting weaponBaseDamageLeftString{ "showStatsName"s, "weaponBaseDamageLeft"s, const_undefined };
    static inline str_setting weaponStaggerString{ "showStatsName"s, "weaponStagger"s, const_undefined };
    static inline str_setting weaponStaggerLeftString{ "showStatsName"s, "weaponStaggerLeft"s, const_undefined };
    static inline str_setting weaponCritDamageRatingString{ "showStatsName"s,
                                                            "weaponCritDamageRating"s,
                                                            const_undefined };
    static inline str_setting weaponCritDamageRatingLeftString{ "showStatsName"s,
                                                                "weaponCritDamageRatingLeft"s,
                                                                const_undefined };
    static inline str_setting fallDamageModString{ "showStatsName"s, "fallDamageMod"s, const_undefined };

    //stat endings
    static inline str_setting heightStringEnding{ "showStatsEnding"s, "height"s, const_undefined };
    static inline str_setting equipedWeightStringEnding{ "showStatsEnding"s, "equipedWeight"s, const_undefined };
    static inline str_setting weightStringEnding{ "showStatsEnding"s, "weight"s, const_undefined };
    static inline str_setting healthRateStringEnding{ "showStatsEnding"s, "healthRatePer"s, const_undefined };
    static inline str_setting magickaRateStringEnding{ "showStatsEnding"s, "magickaRatePer"s, const_undefined };
    static inline str_setting staminaRateStringEnding{ "showStatsEnding"s, "staminaRatePer"s, const_undefined };
    static inline str_setting resistDamageStringEnding{ "showStatsEnding"s, "resistDamage"s, const_undefined };
    static inline str_setting resistDiseaseStringEnding{ "showStatsEnding"s, "resistDisease"s, const_undefined };
    static inline str_setting resistPoisonStringEnding{ "showStatsEnding"s, "resistPoison"s, const_undefined };
    static inline str_setting resistFireStringEnding{ "showStatsEnding"s, "resistFire"s, const_undefined };
    static inline str_setting resistShockStringEnding{ "showStatsEnding"s, "resistShock"s, const_undefined };
    static inline str_setting resistFrostStringEnding{ "showStatsEnding"s, "resistFrost"s, const_undefined };
    static inline str_setting resistMagicStringEnding{ "showStatsEnding"s, "resistMagic"s, const_undefined };
    static inline str_setting speedMultStringEnding{ "showStatsEnding"s, "speedMult"s, const_undefined };
    static inline str_setting inventoryWeightStringEnding{ "showStatsEnding"s, "inventoryWeight"s, const_undefined };
    static inline str_setting carryWeightStringEnding{ "showStatsEnding"s, "carryWeight"s, const_undefined };
    static inline str_setting criticalChanceStringEnding{ "showStatsEnding"s, "criticalChance"s, const_undefined };
    static inline str_setting absorbChanceStringEnding{ "showStatsEnding"s, "absorbChance"s, const_undefined };
    static inline str_setting weaponSpeedMultStringEnding{ "showStatsEnding"s, "weaponSpeedMult"s, const_undefined };
    static inline str_setting bowSpeedBonusStringEnding{ "showStatsEnding"s, "bowSpeedBonus"s, const_undefined };
    static inline str_setting shoutRecoveryMultStringEnding{ "showStatsEnding"s,
                                                             "shoutRecoveryMult"s,
                                                             const_undefined };
    static inline str_setting movementNoiseMultStringEnding{ "showStatsEnding"s,
                                                             "movementNoiseMult"s,
                                                             const_undefined };
    static inline str_setting combatHealthRegenMultiplyStringEnding{ "showStatsEnding"s,
                                                                     "combatHealthRegenMultiply"s,
                                                                     const_undefined };
    static inline str_setting attackDamageMultStringEnding{ "showStatsEnding"s, "attackDamageMult"s, const_undefined };
    static inline str_setting reflectDamageStringEnding{ "showStatsEnding"s, "reflectDamage"s, const_undefined };
    static inline str_setting oneHandedModStringEnding{ "showStatsEnding"s, "oneHandedMod"s, const_undefined };
    static inline str_setting twoHandedModStringEnding{ "showStatsEnding"s, "twoHandedMod"s, const_undefined };
    static inline str_setting archeryModStringEnding{ "showStatsEnding"s, "archeryMod"s, const_undefined };
    static inline str_setting blockModStringEnding{ "showStatsEnding"s, "blockMod"s, const_undefined };
    static inline str_setting smithingModStringEnding{ "showStatsEnding"s, "smithingMod"s, const_undefined };
    static inline str_setting heavyArmorModStringEnding{ "showStatsEnding"s, "heavyArmorMod"s, const_undefined };
    static inline str_setting lightArmorModStringEnding{ "showStatsEnding"s, "lightArmorMod"s, const_undefined };
    static inline str_setting pickpocketModStringEnding{ "showStatsEnding"s, "pickpocketMod"s, const_undefined };
    static inline str_setting lockpickingModStringEnding{ "showStatsEnding"s, "lockpickingMod"s, const_undefined };
    static inline str_setting sneakModStringEnding{ "showStatsEnding"s, "sneakMod"s, const_undefined };
    static inline str_setting alchemyModStringEnding{ "showStatsEnding"s, "alchemyMod"s, const_undefined };
    static inline str_setting speechModStringEnding{ "showStatsEnding"s, "speechMod"s, const_undefined };
    static inline str_setting enchantingModStringEnding{ "showStatsEnding"s, "enchantingMod"s, const_undefined };
    static inline str_setting alterationModStringEnding{ "showStatsEnding"s, "alterationMod"s, const_undefined };
    static inline str_setting conjurationModStringEnding{ "showStatsEnding"s, "conjurationMod"s, const_undefined };
    static inline str_setting destructionModStringEnding{ "showStatsEnding"s, "destructionMod"s, const_undefined };
    static inline str_setting illusionModStringEnding{ "showStatsEnding"s, "illusionMod"s, const_undefined };
    static inline str_setting restorationModStringEnding{ "showStatsEnding"s, "restorationMod"s, const_undefined };
    static inline str_setting leftWeaponSpeedMultStringEnding{ "showStatsEnding"s,
                                                               "leftWeaponSpeedMult"s,
                                                               const_undefined };
    static inline str_setting armorPerksStringEnding{ "showStatsEnding"s, "armorPerks"s, const_undefined };
    static inline str_setting fallDamageModStringEnding{ "showStatsEnding"s, "fallDamageMod"s, const_undefined };

    //stat menu
    static inline int_setting height_menu{ "showStatsMenu"s, "height"s, 0 };
    static inline int_setting equiped_weight_menu{ "showStatsMenu"s, "equipedWeight"s, 0 };
    static inline int_setting weight_menu{ "showStatsMenu"s, "weight"s, 0 };
    static inline int_setting armor_menu{ "showStatsMenu"s, "armor"s, 0 };
    static inline int_setting damage_menu{ "showStatsMenu"s, "damage"s, 0 };
    static inline int_setting skill_trainings_this_level_menu{ "showStatsMenu"s, "skillTrainingsThisLevel"s, 0 };
    static inline int_setting health_menu{ "showStatsMenu"s, "health"s, 0 };
    static inline int_setting health_rate_menu{ "showStatsMenu"s, "healthRatePer"s, 0 };
    static inline int_setting magicka_menu{ "showStatsMenu"s, "magicka"s, 0 };
    static inline int_setting magicka_rate_menu{ "showStatsMenu"s, "magickaRatePer"s, 0 };
    static inline int_setting stamina_menu{ "showStatsMenu"s, "stamina"s, 0 };
    static inline int_setting stamina_rate_menu{ "showStatsMenu"s, "staminaRatePer"s, 0 };
    static inline int_setting resist_damage_menu{ "showStatsMenu"s, "resistDamage"s, 0 };
    static inline int_setting resist_disease_menu{ "showStatsMenu"s, "resistDisease"s, 0 };
    static inline int_setting resist_poison_menu{ "showStatsMenu"s, "resistPoison"s, 0 };
    static inline int_setting resist_fire_menu{ "showStatsMenu"s, "resistFire"s, 0 };
    static inline int_setting resist_shock_menu{ "showStatsMenu"s, "resistShock"s, 0 };
    static inline int_setting resist_frost_menu{ "showStatsMenu"s, "resistFrost"s, 0 };
    static inline int_setting resist_magic_menu{ "showStatsMenu"s, "resistMagic"s, 0 };
    static inline int_setting one_handed_menu{ "showStatsMenu"s, "oneHanded"s, 0 };
    static inline int_setting two_handed_menu{ "showStatsMenu"s, "twoHanded"s, 0 };
    static inline int_setting archery_menu{ "showStatsMenu"s, "archery"s, 0 };
    static inline int_setting block_menu{ "showStatsMenu"s, "block"s, 0 };
    static inline int_setting smithing_menu{ "showStatsMenu"s, "smithing"s, 0 };
    static inline int_setting heavy_armor_menu{ "showStatsMenu"s, "heavyArmor"s, 0 };
    static inline int_setting light_armor_menu{ "showStatsMenu"s, "lightArmor"s, 0 };
    static inline int_setting pickpocket_menu{ "showStatsMenu"s, "pickpocket"s, 0 };
    static inline int_setting lockpicking_menu{ "showStatsMenu"s, "lockpicking"s, 0 };
    static inline int_setting sneak_menu{ "showStatsMenu"s, "sneak"s, 0 };
    static inline int_setting alchemy_menu{ "showStatsMenu"s, "alchemy"s, 0 };
    static inline int_setting speech_menu{ "showStatsMenu"s, "speech"s, 0 };
    static inline int_setting enchanting_menu{ "showStatsMenu"s, "enchanting"s, 0 };
    static inline int_setting alteration_menu{ "showStatsMenu"s, "alteration"s, 0 };
    static inline int_setting conjuration_menu{ "showStatsMenu"s, "conjuration"s, 0 };
    static inline int_setting destruction_menu{ "showStatsMenu"s, "destruction"s, 0 };
    static inline int_setting illusion_menu{ "showStatsMenu"s, "illusion"s, 0 };
    static inline int_setting restoration_menu{ "showStatsMenu"s, "restoration"s, 0 };
    static inline int_setting one_handed_power_mod_menu{ "showStatsMenu"s, "oneHandedPowerMod"s, 0 };
    static inline int_setting two_handed_power_mod_menu{ "showStatsMenu"s, "twoHandedPowerMod"s, 0 };
    static inline int_setting archery_power_mod_menu{ "showStatsMenu"s, "archeryPowerMod"s, 0 };
    static inline int_setting block_power_mod_menu{ "showStatsMenu"s, "blockPowerMod"s, 0 };
    static inline int_setting smithing_power_mod_menu{ "showStatsMenu"s, "smithingPowerMod"s, 0 };
    static inline int_setting heavy_armor_power_mod_menu{ "showStatsMenu"s, "heavyArmorPowerMod"s, 0 };
    static inline int_setting light_armor_power_mod_menu{ "showStatsMenu"s, "lightArmorPowerMod"s, 0 };
    static inline int_setting pickpocket_power_mod_menu{ "showStatsMenu"s, "pickpocketPowerMod"s, 0 };
    static inline int_setting lockpicking_power_mod_menu{ "showStatsMenu"s, "lockpickingPowerMod"s, 0 };
    static inline int_setting sneak_power_mod_menu{ "showStatsMenu"s, "sneakPowerMod"s, 0 };
    static inline int_setting alchemy_power_mod_menu{ "showStatsMenu"s, "alchemyPowerMod"s, 0 };
    static inline int_setting speech_power_mod_menu{ "showStatsMenu"s, "speechPowerMod"s, 0 };
    static inline int_setting enchanting_power_mod_menu{ "showStatsMenu"s, "enchantingPowerMod"s, 0 };
    static inline int_setting alteration_power_mod_menu{ "showStatsMenu"s, "alterationPowerMod"s, 0 };
    static inline int_setting conjuration_power_mod_menu{ "showStatsMenu"s, "conjurationPowerMod"s, 0 };
    static inline int_setting destruction_power_mod_menu{ "showStatsMenu"s, "destructionPowerMod"s, 0 };
    static inline int_setting illusion_power_mod_menu{ "showStatsMenu"s, "illusionPowerMod"s, 0 };
    static inline int_setting restoration_power_mod_menu{ "showStatsMenu"s, "restorationPowerMod"s, 0 };
    static inline int_setting speed_mult_menu{ "showStatsMenu"s, "speedMult"s, 0 };
    static inline int_setting inventory_weight_menu{ "showStatsMenu"s, "inventoryWeight"s, 0 };
    static inline int_setting carry_weight_menu{ "showStatsMenu"s, "carryWeight"s, 0 };
    static inline int_setting critical_chance_menu{ "showStatsMenu"s, "criticalChance"s, 0 };
    static inline int_setting melee_damage_menu{ "showStatsMenu"s, "meleeDamage"s, 0 };
    static inline int_setting unarmed_damage_menu{ "showStatsMenu"s, "unarmedDamage"s, 0 };
    static inline int_setting absorb_chance_menu{ "showStatsMenu"s, "absorbChance"s, 0 };
    static inline int_setting weapon_speed_mult_menu{ "showStatsMenu"s, "weaponSpeedMult"s, 0 };
    static inline int_setting bow_speed_bonus_menu{ "showStatsMenu"s, "bowSpeedBonus"s, 0 };
    static inline int_setting shout_recovery_mult_menu{ "showStatsMenu"s, "shoutRecoveryMult"s, 0 };
    static inline int_setting movement_noise_mult_menu{ "showStatsMenu"s, "movementNoiseMult"s, 0 };
    static inline int_setting dragon_souls_menu{ "showStatsMenu"s, "dragonSouls"s, 0 };
    static inline int_setting combat_health_regen_multiply_menu{ "showStatsMenu"s, "combatHealthRegenMultiply"s, 0 };
    static inline int_setting attack_damage_mult_menu{ "showStatsMenu"s, "attackDamageMult"s, 0 };
    static inline int_setting reflect_damage_menu{ "showStatsMenu"s, "reflectDamage"s, 0 };
    static inline int_setting one_handed_mod_menu{ "showStatsMenu"s, "oneHandedMod"s, 0 };
    static inline int_setting two_handed_mod_menu{ "showStatsMenu"s, "twoHandedMod"s, 0 };
    static inline int_setting archery_mod_menu{ "showStatsMenu"s, "archeryMod"s, 0 };
    static inline int_setting block_mod_menu{ "showStatsMenu"s, "blockMod"s, 0 };
    static inline int_setting smithing_mod_menu{ "showStatsMenu"s, "smithingMod"s, 0 };
    static inline int_setting heavy_armor_mod_menu{ "showStatsMenu"s, "heavyArmorMod"s, 0 };
    static inline int_setting light_armor_mod_menu{ "showStatsMenu"s, "lightArmorMod"s, 0 };
    static inline int_setting pickpocket_mod_menu{ "showStatsMenu"s, "pickpocketMod"s, 0 };
    static inline int_setting lockpicking_mod_menu{ "showStatsMenu"s, "lockpickingMod"s, 0 };
    static inline int_setting sneak_mod_menu{ "showStatsMenu"s, "sneakMod"s, 0 };
    static inline int_setting alchemy_mod_menu{ "showStatsMenu"s, "alchemyMod"s, 0 };
    static inline int_setting speech_mod_menu{ "showStatsMenu"s, "speechMod"s, 0 };
    static inline int_setting enchanting_mod_menu{ "showStatsMenu"s, "enchantingMod"s, 0 };
    static inline int_setting alteration_mod_menu{ "showStatsMenu"s, "alterationMod"s, 0 };
    static inline int_setting conjuration_mod_menu{ "showStatsMenu"s, "conjurationMod"s, 0 };
    static inline int_setting destruction_mod_menu{ "showStatsMenu"s, "destructionMod"s, 0 };
    static inline int_setting illusion_mod_menu{ "showStatsMenu"s, "illusionMod"s, 0 };
    static inline int_setting restoration_mod_menu{ "showStatsMenu"s, "restorationMod"s, 0 };
    static inline int_setting damage_arrow_menu{ "showStatsMenu"s, "damageArrow"s, 0 };
    static inline int_setting damage_left_menu{ "showStatsMenu"s, "damageLeft"s, 0 };
    static inline int_setting left_weapon_speed_mult_menu{ "showStatsMenu"s, "leftWeaponSpeedMult"s, 0 };
    static inline int_setting right_item_charge_menu{ "showStatsMenu"s, "rightItemCharge"s, 0 };
    static inline int_setting left_item_charge_menu{ "showStatsMenu"s, "leftItemCharge"s, 0 };
    static inline int_setting armor_perks_menu{ "showStatsMenu"s, "armorPerks"s, 0 };
    static inline int_setting mass_menu{ "showStatsMenu"s, "mass"s, 0 };
    static inline int_setting bow_stagger_bonus_menu{ "showStatsMenu"s, "bowStaggerBonus"s, 0 };
    static inline int_setting bypass_vendor_keyword_check_menu{ "showStatsMenu"s, "bypassVendorKeywordCheck"s, 0 };
    static inline int_setting bypass_vendor_stolen_check_menu{ "showStatsMenu"s, "bypassVendorStolenCheck"s, 0 };
    static inline int_setting weapon_reach_menu{ "showStatsMenu"s, "weaponReach"s, 0 };
    static inline int_setting weapon_reach_left_menu{ "showStatsMenu"s, "weaponReachLeft"s, 0 };
    static inline int_setting weapon_base_damage_menu{ "showStatsMenu"s, "weaponBaseDamage"s, 0 };
    static inline int_setting weapon_base_damage_left_menu{ "showStatsMenu"s, "weaponBaseDamageLeft"s, 0 };
    static inline int_setting weapon_stagger_menu{ "showStatsMenu"s, "weaponStagger"s, 0 };
    static inline int_setting weapon_stagger_left_menu{ "showStatsMenu"s, "weaponStaggerLeft"s, 0 };
    static inline int_setting weapon_crit_damage_rating_menu{ "showStatsMenu"s, "weaponCritDamageRating"s, 0 };
    static inline int_setting weapon_crit_damage_rating_left_menu{ "showStatsMenu"s, "weaponCritDamageRatingLeft"s, 0 };
    static inline int_setting fall_damage_mod_menu{ "showStatsMenu"s, "fallDamageMod"s, 0 };

    //multiplier
    static inline int_setting weapon_speed_mult_mult{ "showStatsMultiplier"s, "weaponSpeedMult"s, 1 };
    static inline int_setting shout_recovery_mult_mult{ "showStatsMultiplier"s, "shoutRecoveryMult"s, 1 };
    static inline int_setting movement_noise_mult_mult{ "showStatsMultiplier"s, "movementNoiseMult"s, 1 };
    static inline int_setting combat_health_regen_multiply_mult{ "showStatsMultiplier"s, "combatHealthRegenMultiply"s,
                                                                 1 };
    static inline int_setting left_weapon_speed_mult_mult{ "showStatsMultiplier"s, "leftWeaponSpeedMult"s, 1 };
    static inline int_setting armor_perks_mult{ "showStatsMultiplier"s, "armorPerks"s, 1 };
    static inline int_setting fall_damage_mod_mult{ "showStatsMultiplier"s, "fallDamageMod"s, 1 };

    static inline str_setting vampireString{ "showBeastName"s, "vampire"s, const_undefined };
    static inline str_setting werewolfString{ "showBeastName"s, "werewolf"s, const_undefined };

    //factions title
    static inline str_setting showFactionsTitleTitle{ "showFactionsTitle"s, "title"s, const_undefined };
    static inline str_setting showFactionsTitleFaction{ "showFactionsTitle"s, "faction"s, const_undefined };
    static inline str_setting showFactionsTitleThane{ "showFactionsTitle"s, "thane"s, const_undefined };
    static inline str_setting showFactionsTitleChampion{ "showFactionsTitle"s, "champion"s, const_undefined };

    //faction name
    static inline str_setting companionsString{ "showFactionsFactionNames"s, "companions"s, const_undefined };
    static inline str_setting darkbrotherHoodString{ "showFactionsFactionNames"s, "darkbrotherHood"s, const_undefined };
    static inline str_setting collegeOfWinterholdString{ "showFactionsFactionNames"s,
                                                         "collegeOfWinterhold"s,
                                                         const_undefined };
    static inline str_setting orcFriendString{ "showFactionsFactionNames"s, "orcFriend"s, const_undefined };
    static inline str_setting thiefsGuildString{ "showFactionsFactionNames"s, "thiefsGuild"s, const_undefined };
    static inline str_setting imperialLegionString{ "showFactionsFactionNames"s, "imperialLegion"s, const_undefined };
    static inline str_setting stormcloaksString{ "showFactionsFactionNames"s, "stormcloaks"s, const_undefined };
    static inline str_setting greybeardString{ "showFactionsFactionNames"s, "greybeard"s, const_undefined };
    static inline str_setting bardString{ "showFactionsFactionNames"s, "bard"s, const_undefined };
    static inline str_setting volkiharVampireClanString{ "showFactionsFactionNames"s,
                                                         "volkiharVampireClan"s,
                                                         const_undefined };
    static inline str_setting dawnguardString{ "showFactionsFactionNames"s, "dawnguard"s, const_undefined };
    static inline str_setting houseTelvanniString{ "showFactionsFactionNames"s, "houseTelvanni"s, const_undefined };

    //faction menu
    static inline int_setting factionMenu{ "showFactionsFactionMenu"s, "faction"s, 0 };

    //faction ranks
    static inline str_setting bardRank{ "showFactionsFactionRank"s, "bard"s, const_undefined };
    static inline str_setting assassinRank{ "showFactionsFactionRank"s, "assassin"s, const_undefined };
    static inline str_setting listenerRank{ "showFactionsFactionRank"s, "listener"s, const_undefined };
    static inline str_setting auxiliaryRank{ "showFactionsFactionRank"s, "auxiliary"s, const_undefined };
    static inline str_setting quaestorRank{ "showFactionsFactionRank"s, "quaestor"s, const_undefined };
    static inline str_setting praefectRank{ "showFactionsFactionRank"s, "praefect"s, const_undefined };
    static inline str_setting tribuneRank{ "showFactionsFactionRank"s, "tribune"s, const_undefined };
    static inline str_setting legateRank{ "showFactionsFactionRank"s, "legate"s, const_undefined };
    static inline str_setting unbloodedRank{ "showFactionsFactionRank"s, "unblooded"s, const_undefined };
    static inline str_setting iceVeinsRank{ "showFactionsFactionRank"s, "iceVeins"s, const_undefined };
    static inline str_setting boneBreakerRank{ "showFactionsFactionRank"s, "boneBreaker"s, const_undefined };
    static inline str_setting snowHammerRank{ "showFactionsFactionRank"s, "snowHammer"s, const_undefined };
    static inline str_setting stormbladeRank{ "showFactionsFactionRank"s, "stormblade"s, const_undefined };
    static inline str_setting vampireLordRank{ "showFactionsFactionRank"s, "vampireLord"s, const_undefined };
    static inline str_setting vampireHunterRank{ "showFactionsFactionRank"s, "vampireHunter"s, const_undefined };
    static inline str_setting honoraryMemberRank{ "showFactionsFactionRank"s, "honoraryMember"s, const_undefined };
    static inline str_setting ysmirRank{ "showFactionsFactionRank"s, "ysmir"s, const_undefined };

    //thane menu
    static inline int_setting thaneMenu{ "showFactionsThaneMenu"s, "thane"s, 0 };

    //thane names
    static inline str_setting thaneOfEastmarchName{ "showFactionsThaneName"s, "thaneOfEastmarch"s, const_undefined };
    static inline str_setting thaneOfFalkreathName{ "showFactionsThaneName"s, "thaneOfFalkreath"s, const_undefined };
    static inline str_setting thaneOfHaafingarName{ "showFactionsThaneName"s, "thaneOfHaafingar"s, const_undefined };
    static inline str_setting thaneOfHjaalmarchName{ "showFactionsThaneName"s, "thaneOfHjaalmarch"s, const_undefined };
    static inline str_setting thaneOfThePaleName{ "showFactionsThaneName"s, "thaneOfThePale"s, const_undefined };
    static inline str_setting thaneOfTheReachName{ "showFactionsThaneName"s, "thaneOfTheReach"s, const_undefined };
    static inline str_setting thaneOfTheRiftName{ "showFactionsThaneName"s, "thaneOfTheRift"s, const_undefined };
    static inline str_setting thaneOfWhiterunName{ "showFactionsThaneName"s, "thaneOfWhiterun"s, const_undefined };
    static inline str_setting thaneOfWinterholdName{ "showFactionsThaneName"s, "thaneOfWinterhold"s, const_undefined };

    //champion menu
    static inline int_setting championMenu{ "showFactionsChampionMenu"s, "champion"s, 0 };

    //champion name
    static inline str_setting azuraName{ "showFactionsChampionName"s, "azura"s, const_undefined };
    static inline str_setting boethiahName{ "showFactionsChampionName"s, "boethiah"s, const_undefined };
    static inline str_setting clavicusVileName{ "showFactionsChampionName"s, "clavicusVile"s, const_undefined };
    static inline str_setting hermaeusMoraName{ "showFactionsChampionName"s, "hermaeusMora"s, const_undefined };
    static inline str_setting hircineName{ "showFactionsChampionName"s, "hircine"s, const_undefined };
    static inline str_setting malacathName{ "showFactionsChampionName"s, "malacath"s, const_undefined };
    static inline str_setting mehrunesDagonName{ "showFactionsChampionName"s, "mehrunesDagon"s, const_undefined };
    static inline str_setting mephalaName{ "showFactionsChampionName"s, "mephala"s, const_undefined };
    static inline str_setting meridiaName{ "showFactionsChampionName"s, "meridia"s, const_undefined };
    static inline str_setting molagBalName{ "showFactionsChampionName"s, "molagBal"s, const_undefined };
    static inline str_setting namiraName{ "showFactionsChampionName"s, "namira"s, const_undefined };
    static inline str_setting nocturnalName{ "showFactionsChampionName"s, "nocturnal"s, const_undefined };
    static inline str_setting peryiteName{ "showFactionsChampionName"s, "peryite"s, const_undefined };
    static inline str_setting sanguineName{ "showFactionsChampionName"s, "sanguine"s, const_undefined };
    static inline str_setting sheogorathName{ "showFactionsChampionName"s, "sheogorath"s, const_undefined };
    static inline str_setting vaerminaName{ "showFactionsChampionName"s, "vaermina"s, const_undefined };

    //stats inventory titles
    static inline str_setting show_stats_inventory_title_title{ "showStatsInventoryTitle"s, "title"s, const_undefined };
    static inline str_setting show_stats_inventory_title_equip{ "showStatsInventoryTitle"s, "equip"s, const_undefined };
    static inline str_setting show_stats_inventory_title_armor{ "showStatsInventoryTitle"s, "armor"s, const_undefined };
    static inline str_setting show_stats_inventory_title_weapon{ "showStatsInventoryTitle"s, "weapon"s,
                                                                 const_undefined };
    static inline str_setting show_stats_inventory_title_effect{ "showStatsInventoryTitle"s, "effect"s,
                                                                 const_undefined };

    static inline bool_setting show_stats_inventorydisplay_zero{ "showStatsInventorySpecial"s, "displayZero"s, true };

    //stats inventory menu
    static inline int_setting equiped_weight_menu_inventory{ "showStatsInventoryMenu"s, "equipedWeight"s, 0 };
    static inline int_setting armor_menu_inventory{ "showStatsInventoryMenu"s, "armor"s, 0 };
    static inline int_setting damage_menu_inventory{ "showStatsInventoryMenu"s, "damage"s, 0 };
    static inline int_setting health_menu_inventory{ "showStatsInventoryMenu"s, "health"s, 0 };
    static inline int_setting health_rate_menu_inventory{ "showStatsInventoryMenu"s, "healthRatePer"s, 0 };
    static inline int_setting magicka_menu_inventory{ "showStatsInventoryMenu"s, "magicka"s, 0 };
    static inline int_setting magicka_rate_menu_inventory{ "showStatsInventoryMenu"s, "magickaRatePer"s, 0 };
    static inline int_setting stamina_menu_inventory{ "showStatsInventoryMenu"s, "stamina"s, 0 };
    static inline int_setting stamina_rate_menu_inventory{ "showStatsInventoryMenu"s, "staminaRatePer"s, 0 };
    static inline int_setting resist_damage_menu_inventory{ "showStatsInventoryMenu"s, "resistDamage"s, 0 };
    static inline int_setting resist_disease_menu_inventory{ "showStatsInventoryMenu"s, "resistDisease"s, 0 };
    static inline int_setting resist_poison_menu_inventory{ "showStatsInventoryMenu"s, "resistPoison"s, 0 };
    static inline int_setting resist_fire_menu_inventory{ "showStatsInventoryMenu"s, "resistFire"s, 0 };
    static inline int_setting resist_shock_menu_inventory{ "showStatsInventoryMenu"s, "resistShock"s, 0 };
    static inline int_setting resist_frost_menu_inventory{ "showStatsInventoryMenu"s, "resistFrost"s, 0 };
    static inline int_setting resist_magic_menu_inventory{ "showStatsInventoryMenu"s, "resistMagic"s, 0 };
    static inline int_setting one_handed_menu_inventory{ "showStatsInventoryMenu"s, "oneHanded"s, 0 };
    static inline int_setting two_handed_menu_inventory{ "showStatsInventoryMenu"s, "twoHanded"s, 0 };
    static inline int_setting archery_menu_inventory{ "showStatsInventoryMenu"s, "archery"s, 0 };
    static inline int_setting block_menu_inventory{ "showStatsInventoryMenu"s, "block"s, 0 };
    static inline int_setting smithing_menu_inventory{ "showStatsInventoryMenu"s, "smithing"s, 0 };
    static inline int_setting heavy_armor_menu_inventory{ "showStatsInventoryMenu"s, "heavyArmor"s, 0 };
    static inline int_setting light_armor_menu_inventory{ "showStatsInventoryMenu"s, "lightArmor"s, 0 };
    static inline int_setting pickpocket_menu_inventory{ "showStatsInventoryMenu"s, "pickpocket"s, 0 };
    static inline int_setting lockpicking_menu_inventory{ "showStatsInventoryMenu"s, "lockpicking"s, 0 };
    static inline int_setting sneak_menu_inventory{ "showStatsInventoryMenu"s, "sneak"s, 0 };
    static inline int_setting alchemy_menu_inventory{ "showStatsInventoryMenu"s, "alchemy"s, 0 };
    static inline int_setting speech_menu_inventory{ "showStatsInventoryMenu"s, "speech"s, 0 };
    static inline int_setting enchanting_menu_inventory{ "showStatsInventoryMenu"s, "enchanting"s, 0 };
    static inline int_setting alteration_menu_inventory{ "showStatsInventoryMenu"s, "alteration"s, 0 };
    static inline int_setting conjuration_menu_inventory{ "showStatsInventoryMenu"s, "conjuration"s, 0 };
    static inline int_setting destruction_menu_inventory{ "showStatsInventoryMenu"s, "destruction"s, 0 };
    static inline int_setting illusion_menu_inventory{ "showStatsInventoryMenu"s, "illusion"s, 0 };
    static inline int_setting restoration_menu_inventory{ "showStatsInventoryMenu"s, "restoration"s, 0 };
    static inline int_setting one_handed_power_mod_menu_inventory{ "showStatsInventoryMenu"s, "oneHandedPowerMod"s, 0 };
    static inline int_setting two_handed_power_mod_menu_inventory{ "showStatsInventoryMenu"s, "twoHandedPowerMod"s, 0 };
    static inline int_setting archery_power_mod_menu_inventory{ "showStatsInventoryMenu"s, "archeryPowerMod"s, 0 };
    static inline int_setting block_power_mod_menu_inventory{ "showStatsInventoryMenu"s, "blockPowerMod"s, 0 };
    static inline int_setting smithing_power_mod_menu_inventory{ "showStatsInventoryMenu"s, "smithingPowerMod"s, 0 };
    static inline int_setting heavy_armor_power_mod_menu_inventory{ "showStatsInventoryMenu"s, "heavyArmorPowerMod"s,
                                                                    0 };
    static inline int_setting light_armor_power_mod_menu_inventory{ "showStatsInventoryMenu"s, "lightArmorPowerMod"s,
                                                                    0 };
    static inline int_setting pickpocket_power_mod_menu_inventory
        { "showStatsInventoryMenu"s, "pickpocketPowerMod"s, 0 };
    static inline int_setting lockpicking_power_mod_menu_inventory{ "showStatsInventoryMenu"s, "lockpickingPowerMod"s,
                                                                    0 };
    static inline int_setting sneak_power_mod_menu_inventory{ "showStatsInventoryMenu"s, "sneakPowerMod"s, 0 };
    static inline int_setting alchemy_power_mod_menu_inventory{ "showStatsInventoryMenu"s, "alchemyPowerMod"s, 0 };
    static inline int_setting speech_power_mod_menu_inventory{ "showStatsInventoryMenu"s, "speechPowerMod"s, 0 };
    static inline int_setting enchanting_power_mod_menu_inventory
        { "showStatsInventoryMenu"s, "enchantingPowerMod"s, 0 };
    static inline int_setting alteration_power_mod_menu_inventory
        { "showStatsInventoryMenu"s, "alterationPowerMod"s, 0 };
    static inline int_setting conjuration_power_mod_menu_inventory{ "showStatsInventoryMenu"s, "conjurationPowerMod"s,
                                                                    0 };
    static inline int_setting destruction_power_mod_menu_inventory{ "showStatsInventoryMenu"s, "destructionPowerMod"s,
                                                                    0 };
    static inline int_setting illusion_power_mod_menu_inventory{ "showStatsInventoryMenu"s, "illusionPowerMod"s, 0 };
    static inline int_setting restoration_power_mod_menu_inventory{ "showStatsInventoryMenu"s, "restorationPowerMod"s,
                                                                    0 };
    static inline int_setting speed_mult_menu_inventory{ "showStatsInventoryMenu"s, "speedMult"s, 0 };
    static inline int_setting inventory_weight_menu_inventory{ "showStatsInventoryMenu"s, "inventoryWeight"s, 0 };
    static inline int_setting carry_weight_menu_inventory{ "showStatsInventoryMenu"s, "carryWeight"s, 0 };
    static inline int_setting critical_chance_menu_inventory{ "showStatsInventoryMenu"s, "criticalChance"s, 0 };
    static inline int_setting melee_damage_menu_inventory{ "showStatsInventoryMenu"s, "meleeDamage"s, 0 };
    static inline int_setting unarmed_damage_menu_inventory{ "showStatsInventoryMenu"s, "unarmedDamage"s, 0 };
    static inline int_setting absorb_chance_menu_inventory{ "showStatsInventoryMenu"s, "absorbChance"s, 0 };
    static inline int_setting weapon_speed_mult_menu_inventory{ "showStatsInventoryMenu"s, "weaponSpeedMult"s, 0 };
    static inline int_setting bow_speed_bonus_menu_inventory{ "showStatsInventoryMenu"s, "bowSpeedBonus"s, 0 };
    static inline int_setting shout_recovery_mult_menu_inventory{ "showStatsInventoryMenu"s, "shoutRecoveryMult"s, 0 };
    static inline int_setting movement_noise_mult_menu_inventory{ "showStatsInventoryMenu"s, "movementNoiseMult"s, 0 };
    static inline int_setting attack_damage_mult_menu_inventory{ "showStatsInventoryMenu"s, "attackDamageMult"s, 0 };
    static inline int_setting reflect_damage_menu_inventory{ "showStatsInventoryMenu"s, "reflectDamage"s, 0 };
    static inline int_setting one_handed_mod_menu_inventory{ "showStatsInventoryMenu"s, "oneHandedMod"s, 0 };
    static inline int_setting two_handed_mod_menu_inventory{ "showStatsInventoryMenu"s, "twoHandedMod"s, 0 };
    static inline int_setting archery_mod_menu_inventory{ "showStatsInventoryMenu"s, "archeryMod"s, 0 };
    static inline int_setting block_mod_menu_inventory{ "showStatsInventoryMenu"s, "blockMod"s, 0 };
    static inline int_setting smithing_mod_menu_inventory{ "showStatsInventoryMenu"s, "smithingMod"s, 0 };
    static inline int_setting heavy_armor_mod_menu_inventory{ "showStatsInventoryMenu"s, "heavyArmorMod"s, 0 };
    static inline int_setting light_armor_mod_menu_inventory{ "showStatsInventoryMenu"s, "lightArmorMod"s, 0 };
    static inline int_setting pickpocket_mod_menu_inventory{ "showStatsInventoryMenu"s, "pickpocketMod"s, 0 };
    static inline int_setting lockpicking_mod_menu_inventory{ "showStatsInventoryMenu"s, "lockpickingMod"s, 0 };
    static inline int_setting sneak_mod_menu_inventory{ "showStatsInventoryMenu"s, "sneakMod"s, 0 };
    static inline int_setting alchemy_mod_menu_inventory{ "showStatsInventoryMenu"s, "alchemyMod"s, 0 };
    static inline int_setting speech_mod_menu_inventory{ "showStatsInventoryMenu"s, "speechMod"s, 0 };
    static inline int_setting enchanting_mod_menu_inventory{ "showStatsInventoryMenu"s, "enchantingMod"s, 0 };
    static inline int_setting alteration_mod_menu_inventory{ "showStatsInventoryMenu"s, "alterationMod"s, 0 };
    static inline int_setting conjuration_mod_menu_inventory{ "showStatsInventoryMenu"s, "conjurationMod"s, 0 };
    static inline int_setting destruction_mod_menu_inventory{ "showStatsInventoryMenu"s, "destructionMod"s, 0 };
    static inline int_setting illusion_mod_menu_inventory{ "showStatsInventoryMenu"s, "illusionMod"s, 0 };
    static inline int_setting restoration_mod_menu_inventory{ "showStatsInventoryMenu"s, "restorationMod"s, 0 };
    static inline int_setting damage_arrow_menu_inventory{ "showStatsInventoryMenu"s, "damageArrow"s, 0 };
    static inline int_setting damage_left_menu_inventory{ "showStatsInventoryMenu"s, "damageLeft"s, 0 };
    static inline int_setting left_weapon_speed_mult_menu_inventory{ "showStatsInventoryMenu"s, "leftWeaponSpeedMult"s,
                                                                     0 };
    static inline int_setting right_item_charge_menu_inventory{ "showStatsInventoryMenu"s, "rightItemCharge"s, 0 };
    static inline int_setting left_item_charge_menu_inventory{ "showStatsInventoryMenu"s, "leftItemCharge"s, 0 };
    static inline int_setting armor_perks_menu_inventory{ "showStatsInventoryMenu"s, "armorPerks"s, 0 };
    static inline int_setting mass_menu_inventory{ "showStatsInventoryMenu"s, "mass"s, 0 };
    static inline int_setting bow_stagger_bonus_menu_inventory{ "showStatsInventoryMenu"s, "bowStaggerBonus"s, 0 };
    static inline int_setting weapon_reach_menu_inventory{ "showStatsInventoryMenu"s, "weaponReach"s, 0 };
    static inline int_setting weapon_reach_left_menu_inventory{ "showStatsInventoryMenu"s, "weaponReachLeft"s, 0 };
    static inline int_setting weapon_base_damage_menu_inventory{ "showStatsInventoryMenu"s, "weaponBaseDamage"s, 0 };
    static inline int_setting weapon_base_damage_left_menu_inventory{ "showStatsInventoryMenu"s,
                                                                      "weaponBaseDamageLeft"s,
                                                                      0 };
    static inline int_setting weapon_stagger_menu_inventory{ "showStatsInventoryMenu"s, "weaponStagger"s, 0 };
    static inline int_setting weapon_stagger_left_menu_inventory{ "showStatsInventoryMenu"s, "weaponStaggerLeft"s, 0 };
    static inline int_setting weapon_crit_damage_rating_menu_inventory{ "showStatsInventoryMenu"s,
                                                                        "weaponCritDamageRating"s,
                                                                        0 };
    static inline int_setting weapon_crit_damage_rating_left_menu_inventory{ "showStatsInventoryMenu"s,
                                                                             "weaponCritDamageRatingLeft"s,
                                                                             0 };
    static inline int_setting fall_damage_mod_menu_inventory{ "showStatsInventoryMenu"s, "fallDamageMod"s, 0 };
};
