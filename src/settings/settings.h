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

    static inline bool_setting show_stats_display_zero{ "showStatsSpecial"s, "displayZero"s, true };

    //stat endings
    static inline str_setting height_string_ending{ "showStatsEnding"s, "height"s, const_undefined };
    static inline str_setting equipped_weight_string_ending{ "showStatsEnding"s, "equipedWeight"s, const_undefined };
    static inline str_setting weight_string_ending{ "showStatsEnding"s, "weight"s, const_undefined };
    static inline str_setting health_rate_string_ending{ "showStatsEnding"s, "healthRatePer"s, const_undefined };
    static inline str_setting magicka_rate_string_ending{ "showStatsEnding"s, "magickaRatePer"s, const_undefined };
    static inline str_setting stamina_rate_string_ending{ "showStatsEnding"s, "staminaRatePer"s, const_undefined };
    static inline str_setting resist_damage_string_ending{ "showStatsEnding"s, "resistDamage"s, const_undefined };
    static inline str_setting resist_disease_string_ending{ "showStatsEnding"s, "resistDisease"s, const_undefined };
    static inline str_setting resist_poison_string_ending{ "showStatsEnding"s, "resistPoison"s, const_undefined };
    static inline str_setting resist_fire_string_ending{ "showStatsEnding"s, "resistFire"s, const_undefined };
    static inline str_setting resist_shock_string_ending{ "showStatsEnding"s, "resistShock"s, const_undefined };
    static inline str_setting resist_frost_string_ending{ "showStatsEnding"s, "resistFrost"s, const_undefined };
    static inline str_setting resist_magic_string_ending{ "showStatsEnding"s, "resistMagic"s, const_undefined };
    static inline str_setting speed_mult_string_ending{ "showStatsEnding"s, "speedMult"s, const_undefined };
    static inline str_setting inventory_weight_string_ending{ "showStatsEnding"s, "inventoryWeight"s, const_undefined };
    static inline str_setting carry_weight_string_ending{ "showStatsEnding"s, "carryWeight"s, const_undefined };
    static inline str_setting critical_chance_string_ending{ "showStatsEnding"s, "criticalChance"s, const_undefined };
    static inline str_setting absorb_chance_string_ending{ "showStatsEnding"s, "absorbChance"s, const_undefined };
    static inline str_setting weapon_speed_mult_string_ending
        { "showStatsEnding"s, "weaponSpeedMult"s, const_undefined };
    static inline str_setting bow_speed_bonus_string_ending{ "showStatsEnding"s, "bowSpeedBonus"s, const_undefined };
    static inline str_setting shout_recovery_mult_string_ending{ "showStatsEnding"s,
                                                                 "shoutRecoveryMult"s,
                                                                 const_undefined };
    static inline str_setting movement_noise_mult_string_ending{ "showStatsEnding"s,
                                                                 "movementNoiseMult"s,
                                                                 const_undefined };
    static inline str_setting combat_health_regen_multiply_string_ending{ "showStatsEnding"s,
                                                                          "combatHealthRegenMultiply"s,
                                                                          const_undefined };
    static inline str_setting attack_damage_mult_string_ending{ "showStatsEnding"s, "attackDamageMult"s,
                                                                const_undefined };
    static inline str_setting reflect_damage_string_ending{ "showStatsEnding"s, "reflectDamage"s, const_undefined };
    static inline str_setting one_handed_mod_string_ending{ "showStatsEnding"s, "oneHandedMod"s, const_undefined };
    static inline str_setting two_handed_mod_string_ending{ "showStatsEnding"s, "twoHandedMod"s, const_undefined };
    static inline str_setting archery_mod_string_ending{ "showStatsEnding"s, "archeryMod"s, const_undefined };
    static inline str_setting block_mod_string_ending{ "showStatsEnding"s, "blockMod"s, const_undefined };
    static inline str_setting smithing_mod_string_ending{ "showStatsEnding"s, "smithingMod"s, const_undefined };
    static inline str_setting heavy_armor_mod_string_ending{ "showStatsEnding"s, "heavyArmorMod"s, const_undefined };
    static inline str_setting light_armor_mod_string_ending{ "showStatsEnding"s, "lightArmorMod"s, const_undefined };
    static inline str_setting pickpocket_mod_string_ending{ "showStatsEnding"s, "pickpocketMod"s, const_undefined };
    static inline str_setting lockpicking_mod_string_ending{ "showStatsEnding"s, "lockpickingMod"s, const_undefined };
    static inline str_setting sneak_mod_string_ending{ "showStatsEnding"s, "sneakMod"s, const_undefined };
    static inline str_setting alchemy_mod_string_ending{ "showStatsEnding"s, "alchemyMod"s, const_undefined };
    static inline str_setting speech_mod_string_ending{ "showStatsEnding"s, "speechMod"s, const_undefined };
    static inline str_setting enchanting_mod_string_ending{ "showStatsEnding"s, "enchantingMod"s, const_undefined };
    static inline str_setting alteration_mod_string_ending{ "showStatsEnding"s, "alterationMod"s, const_undefined };
    static inline str_setting conjuration_mod_string_ending{ "showStatsEnding"s, "conjurationMod"s, const_undefined };
    static inline str_setting destruction_mod_string_ending{ "showStatsEnding"s, "destructionMod"s, const_undefined };
    static inline str_setting illusion_mod_string_ending{ "showStatsEnding"s, "illusionMod"s, const_undefined };
    static inline str_setting restoration_mod_string_ending{ "showStatsEnding"s, "restorationMod"s, const_undefined };
    static inline str_setting left_weapon_speed_mult_string_ending{ "showStatsEnding"s,
                                                                    "leftWeaponSpeedMult"s,
                                                                    const_undefined };
    static inline str_setting armor_perks_string_ending{ "showStatsEnding"s, "armorPerks"s, const_undefined };
    static inline str_setting fall_damage_mod_string_ending{ "showStatsEnding"s, "fallDamageMod"s, const_undefined };

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
    static inline int_setting warmth_menu{ "showStatsMenu"s, "warmth"s, 0 };

    //multiplier
    static inline int_setting weapon_speed_mult_mult{ "showStatsMultiplier"s, "weaponSpeedMult"s, 1 };
    static inline int_setting shout_recovery_mult_mult{ "showStatsMultiplier"s, "shoutRecoveryMult"s, 1 };
    static inline int_setting movement_noise_mult_mult{ "showStatsMultiplier"s, "movementNoiseMult"s, 1 };
    static inline int_setting combat_health_regen_multiply_mult{ "showStatsMultiplier"s, "combatHealthRegenMultiply"s,
                                                                 1 };
    static inline int_setting left_weapon_speed_mult_mult{ "showStatsMultiplier"s, "leftWeaponSpeedMult"s, 1 };
    static inline int_setting armor_perks_mult{ "showStatsMultiplier"s, "armorPerks"s, 1 };
    static inline int_setting fall_damage_mod_mult{ "showStatsMultiplier"s, "fallDamageMod"s, 1 };

    //faction menu
    static inline int_setting faction_menu{ "showFactionsFactionMenu"s, "faction"s, 0 };

    //thane menu
    static inline int_setting thane_menu{ "showFactionsThaneMenu"s, "thane"s, 0 };

    //champion menu
    static inline int_setting champion_menu{ "showFactionsChampionMenu"s, "champion"s, 0 };

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
    static inline int_setting warmth_menu_inventory{ "showStatsInventoryMenu"s, "warmth"s, 0 };

};
