#pragma once

#include <SimpleIni.h>

class setting {
    inline static const char* ini_path_ = R"(.\Data\SKSE\Plugins\ShowStats.ini)";
    inline static const char* const_undefined_ = "<undef>";

    inline static int log_level_;
    inline static int open_menu_button_;
    inline static int open_faction_menu_button_;
    inline static bool pause_game_;
    inline static bool show_inventory_stats_;
    inline static bool show_inventory_stats_auto_open_;
    inline static int show_inventory_button_;
    inline static int display_av_type_;

    inline static bool skyrim_unbound_;
    inline static bool hand_to_hand_;

    inline static bool show_resistance_cap_;

    inline static bool show_stats_display_zero_;


    //stat endings
    inline static std::string height_string_ending_;
    inline static std::string equipped_weight_string_ending_;
    inline static std::string weight_string_ending_;
    inline static std::string health_rate_string_ending_;
    inline static std::string magicka_rate_string_ending_;
    inline static std::string stamina_rate_string_ending_;
    inline static std::string resist_damage_string_ending_;
    inline static std::string resist_disease_string_ending_;
    inline static std::string resist_poison_string_ending_;
    inline static std::string resist_fire_string_ending_;
    inline static std::string resist_shock_string_ending_;
    inline static std::string resist_frost_string_ending_;
    inline static std::string resist_magic_string_ending_;
    inline static std::string speed_mult_string_ending_;
    inline static std::string inventory_weight_string_ending_;
    inline static std::string carry_weight_string_ending_;
    inline static std::string critical_chance_string_ending_;
    inline static std::string absorb_chance_string_ending_;
    inline static std::string weapon_speed_mult_string_ending_;
    inline static std::string bow_speed_bonus_string_ending_;
    inline static std::string shout_recovery_mult_string_ending_;
    inline static std::string movement_noise_mult_string_ending_;
    inline static std::string combat_health_regen_multiply_string_ending_;
    inline static std::string attack_damage_mult_string_ending_;
    inline static std::string reflect_damage_string_ending_;
    inline static std::string one_handed_mod_string_ending_;
    inline static std::string two_handed_mod_string_ending_;
    inline static std::string archery_mod_string_ending_;
    inline static std::string block_mod_string_ending_;
    inline static std::string smithing_mod_string_ending_;
    inline static std::string heavy_armor_mod_string_ending_;
    inline static std::string light_armor_mod_string_ending_;
    inline static std::string pickpocket_mod_string_ending_;
    inline static std::string lockpicking_mod_string_ending_;
    inline static std::string sneak_mod_string_ending_;
    inline static std::string alchemy_mod_string_ending_;
    inline static std::string speech_mod_string_ending_;
    inline static std::string enchanting_mod_string_ending_;
    inline static std::string alteration_mod_string_ending_;
    inline static std::string conjuration_mod_string_ending_;
    inline static std::string destruction_mod_string_ending_;
    inline static std::string illusion_mod_string_ending_;
    inline static std::string restoration_mod_string_ending_;
    inline static std::string left_weapon_speed_mult_string_ending_;
    inline static std::string armor_perks_string_ending_;
    inline static std::string fall_damage_mod_string_ending_;


    inline static int height_menu_;
    inline static int equiped_weight_menu_;
    inline static int weight_menu_;
    inline static int armor_menu_;
    inline static int damage_menu_;
    inline static int skill_trainings_this_level_menu_;
    inline static int health_menu_;
    inline static int health_rate_menu_;
    inline static int magicka_menu_;
    inline static int magicka_rate_menu_;
    inline static int stamina_menu_;
    inline static int stamina_rate_menu_;
    inline static int resist_damage_menu_;
    inline static int resist_disease_menu_;
    inline static int resist_poison_menu_;
    inline static int resist_fire_menu_;
    inline static int resist_shock_menu_;
    inline static int resist_frost_menu_;
    inline static int resist_magic_menu_;
    inline static int one_handed_menu_;
    inline static int two_handed_menu_;
    inline static int archery_menu_;
    inline static int block_menu_;
    inline static int smithing_menu_;
    inline static int heavy_armor_menu_;
    inline static int light_armor_menu_;
    inline static int pickpocket_menu_;
    inline static int lockpicking_menu_;
    inline static int sneak_menu_;
    inline static int alchemy_menu_;
    inline static int speech_menu_;
    inline static int enchanting_menu_;
    inline static int alteration_menu_;
    inline static int conjuration_menu_;
    inline static int destruction_menu_;
    inline static int illusion_menu_;
    inline static int restoration_menu_;
    inline static int one_handed_power_mod_menu_;
    inline static int two_handed_power_mod_menu_;
    inline static int archery_power_mod_menu_;
    inline static int block_power_mod_menu_;
    inline static int smithing_power_mod_menu_;
    inline static int heavy_armor_power_mod_menu_;
    inline static int light_armor_power_mod_menu_;
    inline static int pickpocket_power_mod_menu_;
    inline static int lockpicking_power_mod_menu_;
    inline static int sneak_power_mod_menu_;
    inline static int alchemy_power_mod_menu_;
    inline static int speech_power_mod_menu_;
    inline static int enchanting_power_mod_menu_;
    inline static int alteration_power_mod_menu_;
    inline static int conjuration_power_mod_menu_;
    inline static int destruction_power_mod_menu_;
    inline static int illusion_power_mod_menu_;
    inline static int restoration_power_mod_menu_;
    inline static int speed_mult_menu_;
    inline static int inventory_weight_menu_;
    inline static int carry_weight_menu_;
    inline static int critical_chance_menu_;
    inline static int melee_damage_menu_;
    inline static int unarmed_damage_menu_;
    inline static int absorb_chance_menu_;
    inline static int weapon_speed_mult_menu_;
    inline static int bow_speed_bonus_menu_;
    inline static int shout_recovery_mult_menu_;
    inline static int movement_noise_mult_menu_;
    inline static int dragon_souls_menu_;
    inline static int combat_health_regen_multiply_menu_;
    inline static int attack_damage_mult_menu_;
    inline static int reflect_damage_menu_;
    inline static int one_handed_mod_menu_;
    inline static int two_handed_mod_menu_;
    inline static int archery_mod_menu_;
    inline static int block_mod_menu_;
    inline static int smithing_mod_menu_;
    inline static int heavy_armor_mod_menu_;
    inline static int light_armor_mod_menu_;
    inline static int pickpocket_mod_menu_;
    inline static int lockpicking_mod_menu_;
    inline static int sneak_mod_menu_;
    inline static int alchemy_mod_menu_;
    inline static int speech_mod_menu_;
    inline static int enchanting_mod_menu_;
    inline static int alteration_mod_menu_;
    inline static int conjuration_mod_menu_;
    inline static int destruction_mod_menu_;
    inline static int illusion_mod_menu_;
    inline static int restoration_mod_menu_;
    inline static int damage_arrow_menu_;
    inline static int damage_left_menu_;
    inline static int left_weapon_speed_mult_menu_;
    inline static int right_item_charge_menu_;
    inline static int left_item_charge_menu_;
    inline static int armor_perks_menu_;
    inline static int mass_menu_;
    inline static int bow_stagger_bonus_menu_;
    inline static int bypass_vendor_keyword_check_menu_;
    inline static int bypass_vendor_stolen_check_menu_;
    inline static int weapon_reach_menu_;
    inline static int weapon_reach_left_menu_;
    inline static int weapon_base_damage_menu_;
    inline static int weapon_base_damage_left_menu_;
    inline static int weapon_stagger_menu_;
    inline static int weapon_stagger_left_menu_;
    inline static int weapon_crit_damage_rating_menu_;
    inline static int weapon_crit_damage_rating_left_menu_;
    inline static int fall_damage_mod_menu_;
    inline static int warmth_menu_;


    inline static int weapon_speed_mult_mult_;
    inline static int shout_recovery_mult_mult_;
    inline static int movement_noise_mult_mult_;
    inline static int combat_health_regen_multiply_mult_;
    inline static int left_weapon_speed_mult_mult_;
    inline static int armor_perks_mult_;
    inline static int fall_damage_mod_mult_;


    inline static int faction_menu_;

    //thane menu
    inline static int thane_menu_;

    //champion menu
    inline static int champion_menu_;

    inline static bool show_stats_inventorydisplay_zero_;

    inline static int equiped_weight_menu_inventory_;
    inline static int armor_menu_inventory_;
    inline static int damage_menu_inventory_;
    inline static int health_menu_inventory_;
    inline static int health_rate_menu_inventory_;
    inline static int magicka_menu_inventory_;
    inline static int magicka_rate_menu_inventory_;
    inline static int stamina_menu_inventory_;
    inline static int stamina_rate_menu_inventory_;
    inline static int resist_damage_menu_inventory_;
    inline static int resist_disease_menu_inventory_;
    inline static int resist_poison_menu_inventory_;
    inline static int resist_fire_menu_inventory_;
    inline static int resist_shock_menu_inventory_;
    inline static int resist_frost_menu_inventory_;
    inline static int resist_magic_menu_inventory_;
    inline static int one_handed_menu_inventory_;
    inline static int two_handed_menu_inventory_;
    inline static int archery_menu_inventory_;
    inline static int block_menu_inventory_;
    inline static int smithing_menu_inventory_;
    inline static int heavy_armor_menu_inventory_;
    inline static int light_armor_menu_inventory_;
    inline static int pickpocket_menu_inventory_;
    inline static int lockpicking_menu_inventory_;
    inline static int sneak_menu_inventory_;
    inline static int alchemy_menu_inventory_;
    inline static int speech_menu_inventory_;
    inline static int enchanting_menu_inventory_;
    inline static int alteration_menu_inventory_;
    inline static int conjuration_menu_inventory_;
    inline static int destruction_menu_inventory_;
    inline static int illusion_menu_inventory_;
    inline static int restoration_menu_inventory_;
    inline static int one_handed_power_mod_menu_inventory_;
    inline static int two_handed_power_mod_menu_inventory_;
    inline static int archery_power_mod_menu_inventory_;
    inline static int block_power_mod_menu_inventory_;
    inline static int smithing_power_mod_menu_inventory_;
    inline static int heavy_armor_power_mod_menu_inventory_;
    inline static int light_armor_power_mod_menu_inventory_;
    inline static int pickpocket_power_mod_menu_inventory_;
    inline static int lockpicking_power_mod_menu_inventory_;
    inline static int sneak_power_mod_menu_inventory_;
    inline static int alchemy_power_mod_menu_inventory_;
    inline static int speech_power_mod_menu_inventory_;
    inline static int enchanting_power_mod_menu_inventory_;
    inline static int alteration_power_mod_menu_inventory_;
    inline static int conjuration_power_mod_menu_inventory_;
    inline static int destruction_power_mod_menu_inventory_;
    inline static int illusion_power_mod_menu_inventory_;
    inline static int restoration_power_mod_menu_inventory_;
    inline static int speed_mult_menu_inventory_;
    inline static int inventory_weight_menu_inventory_;
    inline static int carry_weight_menu_inventory_;
    inline static int critical_chance_menu_inventory_;
    inline static int melee_damage_menu_inventory_;
    inline static int unarmed_damage_menu_inventory_;
    inline static int absorb_chance_menu_inventory_;
    inline static int weapon_speed_mult_menu_inventory_;
    inline static int bow_speed_bonus_menu_inventory_;
    inline static int shout_recovery_mult_menu_inventory_;
    inline static int movement_noise_mult_menu_inventory_;
    inline static int attack_damage_mult_menu_inventory_;
    inline static int reflect_damage_menu_inventory_;
    inline static int one_handed_mod_menu_inventory_;
    inline static int two_handed_mod_menu_inventory_;
    inline static int archery_mod_menu_inventory_;
    inline static int block_mod_menu_inventory_;
    inline static int smithing_mod_menu_inventory_;
    inline static int heavy_armor_mod_menu_inventory_;
    inline static int light_armor_mod_menu_inventory_;
    inline static int pickpocket_mod_menu_inventory_;
    inline static int lockpicking_mod_menu_inventory_;
    inline static int sneak_mod_menu_inventory_;
    inline static int alchemy_mod_menu_inventory_;
    inline static int speech_mod_menu_inventory_;
    inline static int enchanting_mod_menu_inventory_;
    inline static int alteration_mod_menu_inventory_;
    inline static int conjuration_mod_menu_inventory_;
    inline static int destruction_mod_menu_inventory_;
    inline static int illusion_mod_menu_inventory_;
    inline static int restoration_mod_menu_inventory_;
    inline static int damage_arrow_menu_inventory_;
    inline static int damage_left_menu_inventory_;
    inline static int left_weapon_speed_mult_menu_inventory_;
    inline static int right_item_charge_menu_inventory_;
    inline static int left_item_charge_menu_inventory_;
    inline static int armor_perks_menu_inventory_;
    inline static int mass_menu_inventory_;
    inline static int bow_stagger_bonus_menu_inventory_;
    inline static int weapon_reach_menu_inventory_;
    inline static int weapon_reach_left_menu_inventory_;
    inline static int weapon_base_damage_menu_inventory_;
    inline static int weapon_base_damage_left_menu_inventory_;
    inline static int weapon_stagger_menu_inventory_;
    inline static int weapon_stagger_left_menu_inventory_;
    inline static int weapon_crit_damage_rating_menu_inventory_;
    inline static int weapon_crit_damage_rating_left_menu_inventory_;
    inline static int fall_damage_mod_menu_inventory_;
    inline static int warmth_menu_inventory_;
public:
    static void load_settings() {
        CSimpleIniA ini;
        ini.SetUnicode();
        ini.LoadFile(ini_path_);

        log_level_ = ini.GetLongValue("General", "iLogLevel", 2);
        open_menu_button_ = ini.GetLongValue("General", "iOpenMenuButton", 22);
        open_faction_menu_button_ = ini.GetLongValue("General", "iOpenNextMenuButton", 49);
        pause_game_ = ini.GetBoolValue("General", "bPauseGame", true); //G
        show_inventory_stats_ = ini.GetBoolValue("General", "bShowInventoryStats", true);
        show_inventory_stats_auto_open_ = ini.GetBoolValue("General", "bShowInventoryStatsAutoOpen", true);
        show_inventory_button_ = ini.GetLongValue("General", "iShowInventoryButton", 11);
        display_av_type_ = ini.GetLongValue("General", "iDisplayBasePermanentActorValue", 0);

        skyrim_unbound_ = ini.GetBoolValue("Mods", "bSkyrimUnbound", true);
        hand_to_hand_ = ini.GetBoolValue("Mods", "bHandToHand", true);

        show_resistance_cap_ = ini.GetBoolValue("specialHandling", "bShowResistanceCap", true);

        show_stats_display_zero_ = ini.GetBoolValue("showStatsSpecial", "bDisplayZero", true);


        height_string_ending_ = ini.GetValue("showStatsEnding", "sHeight", const_undefined_);
        equipped_weight_string_ending_ = ini.GetValue("showStatsEnding", "sEquipedWeight", const_undefined_);
        weight_string_ending_ = ini.GetValue("showStatsEnding", "sWeight", const_undefined_);
        health_rate_string_ending_ = ini.GetValue("showStatsEnding", "sHealthRatePer", const_undefined_);
        magicka_rate_string_ending_ = ini.GetValue("showStatsEnding", "sMagickaRatePer", const_undefined_);
        stamina_rate_string_ending_ = ini.GetValue("showStatsEnding", "sStaminaRatePer", const_undefined_);
        resist_damage_string_ending_ = ini.GetValue("showStatsEnding", "sResistDamage", const_undefined_);
        resist_disease_string_ending_ = ini.GetValue("showStatsEnding", "sResistDisease", const_undefined_);
        resist_poison_string_ending_ = ini.GetValue("showStatsEnding", "sResistPoison", const_undefined_);
        resist_fire_string_ending_ = ini.GetValue("showStatsEnding", "sResistFire", const_undefined_);
        resist_shock_string_ending_ = ini.GetValue("showStatsEnding", "sResistShock", const_undefined_);
        resist_frost_string_ending_ = ini.GetValue("showStatsEnding", "sResistFrost", const_undefined_);
        resist_magic_string_ending_ = ini.GetValue("showStatsEnding", "sResistMagic", const_undefined_);
        speed_mult_string_ending_ = ini.GetValue("showStatsEnding", "sSpeedMult", const_undefined_);
        inventory_weight_string_ending_ = ini.GetValue("showStatsEnding", "sInventoryWeight", const_undefined_);
        carry_weight_string_ending_ = ini.GetValue("showStatsEnding", "sCarryWeight", const_undefined_);
        critical_chance_string_ending_ = ini.GetValue("showStatsEnding", "sCriticalChance", const_undefined_);
        absorb_chance_string_ending_ = ini.GetValue("showStatsEnding", "sAbsorbChance", const_undefined_);
        weapon_speed_mult_string_ending_ = ini.GetValue("showStatsEnding", "sWeaponSpeedMult", const_undefined_);
        bow_speed_bonus_string_ending_ = ini.GetValue("showStatsEnding", "sBowSpeedBonus", const_undefined_);
        shout_recovery_mult_string_ending_ = ini.GetValue("showStatsEnding", "sShoutRecoveryMult", const_undefined_);
        movement_noise_mult_string_ending_ = ini.GetValue("showStatsEnding", "sMovementNoiseMult", const_undefined_);
        combat_health_regen_multiply_string_ending_ = ini.GetValue("showStatsEnding",
            "sCombatHealthRegenMultiply",
            const_undefined_);
        attack_damage_mult_string_ending_ = ini.GetValue("showStatsEnding", "sAttackDamageMult", const_undefined_);
        reflect_damage_string_ending_ = ini.GetValue("showStatsEnding", "sReflectDamage", const_undefined_);
        one_handed_mod_string_ending_ = ini.GetValue("showStatsEnding", "sOneHandedMod", const_undefined_);
        two_handed_mod_string_ending_ = ini.GetValue("showStatsEnding", "sTwoHandedMod", const_undefined_);
        archery_mod_string_ending_ = ini.GetValue("showStatsEnding", "sArcheryMod", const_undefined_);
        block_mod_string_ending_ = ini.GetValue("showStatsEnding", "sBlockMod", const_undefined_);
        smithing_mod_string_ending_ = ini.GetValue("showStatsEnding", "sSmithingMod", const_undefined_);
        heavy_armor_mod_string_ending_ = ini.GetValue("showStatsEnding", "sHeavyArmorMod", const_undefined_);
        light_armor_mod_string_ending_ = ini.GetValue("showStatsEnding", "sLightArmorMod", const_undefined_);
        pickpocket_mod_string_ending_ = ini.GetValue("showStatsEnding", "sPickpocketMod", const_undefined_);
        lockpicking_mod_string_ending_ = ini.GetValue("showStatsEnding", "sLockpickingMod", const_undefined_);
        sneak_mod_string_ending_ = ini.GetValue("showStatsEnding", "sSneakMod", const_undefined_);
        alchemy_mod_string_ending_ = ini.GetValue("showStatsEnding", "sAlchemyMod", const_undefined_);
        speech_mod_string_ending_ = ini.GetValue("showStatsEnding", "sSpeechMod", const_undefined_);
        enchanting_mod_string_ending_ = ini.GetValue("showStatsEnding", "sEnchantingMod", const_undefined_);
        alteration_mod_string_ending_ = ini.GetValue("showStatsEnding", "sAlterationMod", const_undefined_);
        conjuration_mod_string_ending_ = ini.GetValue("showStatsEnding", "sConjurationMod", const_undefined_);
        destruction_mod_string_ending_ = ini.GetValue("showStatsEnding", "sDestructionMod", const_undefined_);
        illusion_mod_string_ending_ = ini.GetValue("showStatsEnding", "sIllusionMod", const_undefined_);
        restoration_mod_string_ending_ = ini.GetValue("showStatsEnding", "sRestorationMod", const_undefined_);
        left_weapon_speed_mult_string_ending_ = ini.
            GetValue("showStatsEnding", "sLeftWeaponSpeedMult", const_undefined_);
        armor_perks_string_ending_ = ini.GetValue("showStatsEnding", "sArmorPerks", const_undefined_);
        fall_damage_mod_string_ending_ = ini.GetValue("showStatsEnding", "sFallDamageMod", const_undefined_);


        height_menu_ = ini.GetLongValue("showStatsMenu", "iHeight", 0);
        equiped_weight_menu_ = ini.GetLongValue("showStatsMenu", "iEquipedWeight", 0);
        weight_menu_ = ini.GetLongValue("showStatsMenu", "iWeight", 0);
        armor_menu_ = ini.GetLongValue("showStatsMenu", "iArmor", 0);
        damage_menu_ = ini.GetLongValue("showStatsMenu", "iDamage", 0);
        skill_trainings_this_level_menu_ = ini.GetLongValue("showStatsMenu", "iSkillTrainingsThisLevel", 0);
        health_menu_ = ini.GetLongValue("showStatsMenu", "iHealth", 0);
        health_rate_menu_ = ini.GetLongValue("showStatsMenu", "iHealthRatePer", 0);
        magicka_menu_ = ini.GetLongValue("showStatsMenu", "iMagicka", 0);
        magicka_rate_menu_ = ini.GetLongValue("showStatsMenu", "iNagickaRatePer", 0);
        stamina_menu_ = ini.GetLongValue("showStatsMenu", "iStamina", 0);
        stamina_rate_menu_ = ini.GetLongValue("showStatsMenu", "iStaminaRatePer", 0);
        resist_damage_menu_ = ini.GetLongValue("showStatsMenu", "iResistDamage", 0);
        resist_disease_menu_ = ini.GetLongValue("showStatsMenu", "iResistDisease", 0);
        resist_poison_menu_ = ini.GetLongValue("showStatsMenu", "iResistPoison", 0);
        resist_fire_menu_ = ini.GetLongValue("showStatsMenu", "iResistFire", 0);
        resist_shock_menu_ = ini.GetLongValue("showStatsMenu", "iResistShock", 0);
        resist_frost_menu_ = ini.GetLongValue("showStatsMenu", "iResistFrost", 0);
        resist_magic_menu_ = ini.GetLongValue("showStatsMenu", "iResistMagic", 0);
        one_handed_menu_ = ini.GetLongValue("showStatsMenu", "iOneHanded", 0);
        two_handed_menu_ = ini.GetLongValue("showStatsMenu", "iTwoHanded", 0);
        archery_menu_ = ini.GetLongValue("showStatsMenu", "iArchery", 0);
        block_menu_ = ini.GetLongValue("showStatsMenu", "iNlock", 0);
        smithing_menu_ = ini.GetLongValue("showStatsMenu", "iSmithing", 0);
        heavy_armor_menu_ = ini.GetLongValue("showStatsMenu", "iHeavyArmor", 0);
        light_armor_menu_ = ini.GetLongValue("showStatsMenu", "iLightArmor", 0);
        pickpocket_menu_ = ini.GetLongValue("showStatsMenu", "iPickpocket", 0);
        lockpicking_menu_ = ini.GetLongValue("showStatsMenu", "iLockpicking", 0);
        sneak_menu_ = ini.GetLongValue("showStatsMenu", "iSneak", 0);
        alchemy_menu_ = ini.GetLongValue("showStatsMenu", "iAlchemy", 0);
        speech_menu_ = ini.GetLongValue("showStatsMenu", "iSpeech", 0);
        enchanting_menu_ = ini.GetLongValue("showStatsMenu", "iEnchanting", 0);
        alteration_menu_ = ini.GetLongValue("showStatsMenu", "iAlteration", 0);
        conjuration_menu_ = ini.GetLongValue("showStatsMenu", "iConjuration", 0);
        destruction_menu_ = ini.GetLongValue("showStatsMenu", "iDestruction", 0);
        illusion_menu_ = ini.GetLongValue("showStatsMenu", "iIllusion", 0);
        restoration_menu_ = ini.GetLongValue("showStatsMenu", "iRestoration", 0);
        one_handed_power_mod_menu_ = ini.GetLongValue("showStatsMenu", "iOneHandedPowerMod", 0);
        two_handed_power_mod_menu_ = ini.GetLongValue("showStatsMenu", "iTwoHandedPowerMod", 0);
        archery_power_mod_menu_ = ini.GetLongValue("showStatsMenu", "iArcheryPowerMod", 0);
        block_power_mod_menu_ = ini.GetLongValue("showStatsMenu", "iBlockPowerMod", 0);
        smithing_power_mod_menu_ = ini.GetLongValue("showStatsMenu", "iSmithingPowerMod", 0);
        heavy_armor_power_mod_menu_ = ini.GetLongValue("showStatsMenu", "iHeavyArmorPowerMod", 0);
        light_armor_power_mod_menu_ = ini.GetLongValue("showStatsMenu", "iLightArmorPowerMod", 0);
        pickpocket_power_mod_menu_ = ini.GetLongValue("showStatsMenu", "iPickpocketPowerMod", 0);
        lockpicking_power_mod_menu_ = ini.GetLongValue("showStatsMenu", "iLockpickingPowerMod", 0);
        sneak_power_mod_menu_ = ini.GetLongValue("showStatsMenu", "iSneakPowerMod", 0);
        alchemy_power_mod_menu_ = ini.GetLongValue("showStatsMenu", "iAlchemyPowerMod", 0);
        speech_power_mod_menu_ = ini.GetLongValue("showStatsMenu", "iSpeechPowerMod", 0);
        enchanting_power_mod_menu_ = ini.GetLongValue("showStatsMenu", "iEnchantingPowerMod", 0);
        alteration_power_mod_menu_ = ini.GetLongValue("showStatsMenu", "iAlterationPowerMod", 0);
        conjuration_power_mod_menu_ = ini.GetLongValue("showStatsMenu", "iConjurationPowerMod", 0);
        destruction_power_mod_menu_ = ini.GetLongValue("showStatsMenu", "iDestructionPowerMod", 0);
        illusion_power_mod_menu_ = ini.GetLongValue("showStatsMenu", "iIllusionPowerMod", 0);
        restoration_power_mod_menu_ = ini.GetLongValue("showStatsMenu", "iRestorationPowerMod", 0);
        speed_mult_menu_ = ini.GetLongValue("showStatsMenu", "iSpeedMult", 0);
        inventory_weight_menu_ = ini.GetLongValue("showStatsMenu", "iInventoryWeight", 0);
        carry_weight_menu_ = ini.GetLongValue("showStatsMenu", "iCarryWeight", 0);
        critical_chance_menu_ = ini.GetLongValue("showStatsMenu", "iCriticalChance", 0);
        melee_damage_menu_ = ini.GetLongValue("showStatsMenu", "iMeleeDamage", 0);
        unarmed_damage_menu_ = ini.GetLongValue("showStatsMenu", "iUnarmedDamage", 0);
        absorb_chance_menu_ = ini.GetLongValue("showStatsMenu", "iAbsorbChance", 0);
        weapon_speed_mult_menu_ = ini.GetLongValue("showStatsMenu", "iWeaponSpeedMult", 0);
        bow_speed_bonus_menu_ = ini.GetLongValue("showStatsMenu", "iNowSpeedBonus", 0);
        shout_recovery_mult_menu_ = ini.GetLongValue("showStatsMenu", "iShoutRecoveryMult", 0);
        movement_noise_mult_menu_ = ini.GetLongValue("showStatsMenu", "iMovementNoiseMult", 0);
        dragon_souls_menu_ = ini.GetLongValue("showStatsMenu", "iDragonSouls", 0);
        combat_health_regen_multiply_menu_ = ini.GetLongValue("showStatsMenu", "iCombatHealthRegenMultiply", 0);
        attack_damage_mult_menu_ = ini.GetLongValue("showStatsMenu", "iAttackDamageMult", 0);
        reflect_damage_menu_ = ini.GetLongValue("showStatsMenu", "iReflectDamage", 0);
        one_handed_mod_menu_ = ini.GetLongValue("showStatsMenu", "iOneHandedMod", 0);
        two_handed_mod_menu_ = ini.GetLongValue("showStatsMenu", "iTwoHandedMod", 0);
        archery_mod_menu_ = ini.GetLongValue("showStatsMenu", "iArcheryMod", 0);
        block_mod_menu_ = ini.GetLongValue("showStatsMenu", "iBlockMod", 0);
        smithing_mod_menu_ = ini.GetLongValue("showStatsMenu", "iSmithingMod", 0);
        heavy_armor_mod_menu_ = ini.GetLongValue("showStatsMenu", "iHeavyArmorMod", 0);
        light_armor_mod_menu_ = ini.GetLongValue("showStatsMenu", "iLightArmorMod", 0);
        pickpocket_mod_menu_ = ini.GetLongValue("showStatsMenu", "iPickpocketMod", 0);
        lockpicking_mod_menu_ = ini.GetLongValue("showStatsMenu", "iLockpickingMod", 0);
        sneak_mod_menu_ = ini.GetLongValue("showStatsMenu", "iSneakMod", 0);
        alchemy_mod_menu_ = ini.GetLongValue("showStatsMenu", "iAlchemyMod", 0);
        speech_mod_menu_ = ini.GetLongValue("showStatsMenu", "iSpeechMod", 0);
        enchanting_mod_menu_ = ini.GetLongValue("showStatsMenu", "iEnchantingMod", 0);
        alteration_mod_menu_ = ini.GetLongValue("showStatsMenu", "iAlterationMod", 0);
        conjuration_mod_menu_ = ini.GetLongValue("showStatsMenu", "iConjurationMod", 0);
        destruction_mod_menu_ = ini.GetLongValue("showStatsMenu", "iDestructionMod", 0);
        illusion_mod_menu_ = ini.GetLongValue("showStatsMenu", "iIllusionMod", 0);
        restoration_mod_menu_ = ini.GetLongValue("showStatsMenu", "iRestorationMod", 0);
        damage_arrow_menu_ = ini.GetLongValue("showStatsMenu", "iDamageArrow", 0);
        damage_left_menu_ = ini.GetLongValue("showStatsMenu", "iDamageLeft", 0);
        left_weapon_speed_mult_menu_ = ini.GetLongValue("showStatsMenu", "iLeftWeaponSpeedMult", 0);
        right_item_charge_menu_ = ini.GetLongValue("showStatsMenu", "iRightItemCharge", 0);
        left_item_charge_menu_ = ini.GetLongValue("showStatsMenu", "iLeftItemCharge", 0);
        armor_perks_menu_ = ini.GetLongValue("showStatsMenu", "iArmorPerks", 0);
        mass_menu_ = ini.GetLongValue("showStatsMenu", "iMass", 0);
        bow_stagger_bonus_menu_ = ini.GetLongValue("showStatsMenu", "iBowStaggerBonus", 0);
        bypass_vendor_keyword_check_menu_ = ini.GetLongValue("showStatsMenu", "iBypassVendorKeywordCheck", 0);
        bypass_vendor_stolen_check_menu_ = ini.GetLongValue("showStatsMenu", "iBypassVendorStolenCheck", 0);
        weapon_reach_menu_ = ini.GetLongValue("showStatsMenu", "iWeaponReach", 0);
        weapon_reach_left_menu_ = ini.GetLongValue("showStatsMenu", "iWeaponReachLeft", 0);
        weapon_base_damage_menu_ = ini.GetLongValue("showStatsMenu", "iWeaponBaseDamage", 0);
        weapon_base_damage_left_menu_ = ini.GetLongValue("showStatsMenu", "iWeaponBaseDamageLeft", 0);
        weapon_stagger_menu_ = ini.GetLongValue("showStatsMenu", "iWeaponStagger", 0);
        weapon_stagger_left_menu_ = ini.GetLongValue("showStatsMenu", "iWeaponStaggerLeft", 0);
        weapon_crit_damage_rating_menu_ = ini.GetLongValue("showStatsMenu", "iWeaponCritDamageRating", 0);
        weapon_crit_damage_rating_left_menu_ = ini.GetLongValue("showStatsMenu", "iWeaponCritDamageRatingLeft", 0);
        fall_damage_mod_menu_ = ini.GetLongValue("showStatsMenu", "iFallDamageMod", 0);
        warmth_menu_ = ini.GetLongValue("showStatsMenu", "iWarmth", 0);


        weapon_speed_mult_mult_ = ini.GetLongValue("showStatsMultiplier", "iWeaponSpeedMult", 1);
        shout_recovery_mult_mult_ = ini.GetLongValue("showStatsMultiplier", "iShoutRecoveryMult", 1);
        movement_noise_mult_mult_ = ini.GetLongValue("showStatsMultiplier", "iMovementNoiseMult", 1);
        combat_health_regen_multiply_mult_ = ini.GetLongValue("showStatsMultiplier", "iCombatHealthRegenMultiply", 1);
        left_weapon_speed_mult_mult_ = ini.GetLongValue("showStatsMultiplier", "iLeftWeaponSpeedMult", 1);
        armor_perks_mult_ = ini.GetLongValue("showStatsMultiplier", "iArmorPerks", 1);
        fall_damage_mod_mult_ = ini.GetLongValue("showStatsMultiplier", "iFallDamageMod", 1);

        //faction menu
        faction_menu_ = ini.GetLongValue("showFactionsFactionMenu", "iFaction", 0);

        //thane menu
        thane_menu_ = ini.GetLongValue("showFactionsThaneMenu", "iThane", 0);

        //champion menu
        champion_menu_ = ini.GetLongValue("showFactionsChampionMenu", "iChampion", 0);

        show_stats_inventorydisplay_zero_ = ini.GetBoolValue("showStatsInventorySpecial", "bDisplayZero", true);

        //stats inventory menu
        equiped_weight_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iEquipedWeight", 0);
        armor_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iArmor", 0);
        damage_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iDamage", 0);
        health_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iHealth", 0);
        health_rate_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iHealthRatePer", 0);
        magicka_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iMagicka", 0);
        magicka_rate_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iMagickaRatePer", 0);
        stamina_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iStamina", 0);
        stamina_rate_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iStaminaRatePer", 0);
        resist_damage_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iResistDamage", 0);
        resist_disease_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iResistDisease", 0);
        resist_poison_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iResistPoison", 0);
        resist_fire_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iResistFire", 0);
        resist_shock_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iResistShock", 0);
        resist_frost_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iResistFrost", 0);
        resist_magic_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iResistMagic", 0);
        one_handed_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iOneHanded", 0);
        two_handed_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iTwoHanded", 0);
        archery_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iArchery", 0);
        block_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iBlock", 0);
        smithing_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iSmithing", 0);
        heavy_armor_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iHeavyArmor", 0);
        light_armor_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iLightArmor", 0);
        pickpocket_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iPickpocket", 0);
        lockpicking_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iLockpicking", 0);
        sneak_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iSneak", 0);
        alchemy_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iAlchemy", 0);
        speech_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iSpeech", 0);
        enchanting_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iEnchanting", 0);
        alteration_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iAlteration", 0);
        conjuration_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iConjuration", 0);
        destruction_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iDestruction", 0);
        illusion_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iIllusion", 0);
        restoration_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iRestoration", 0);
        one_handed_power_mod_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iOneHandedPowerMod", 0);
        two_handed_power_mod_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iTwoHandedPowerMod", 0);
        archery_power_mod_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iArcheryPowerMod", 0);
        block_power_mod_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iBlockPowerMod", 0);
        smithing_power_mod_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iSmithingPowerMod", 0);
        heavy_armor_power_mod_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iHeavyArmorPowerMod", 0);
        light_armor_power_mod_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iLightArmorPowerMod", 0);
        pickpocket_power_mod_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iPickpocketPowerMod", 0);
        lockpicking_power_mod_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iLockpickingPowerMod", 0);
        sneak_power_mod_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iSneakPowerMod", 0);
        alchemy_power_mod_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iAlchemyPowerMod", 0);
        speech_power_mod_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iSpeechPowerMod", 0);
        enchanting_power_mod_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iEnchantingPowerMod", 0);
        alteration_power_mod_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iAlterationPowerMod", 0);
        conjuration_power_mod_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iConjurationPowerMod", 0);
        destruction_power_mod_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iDestructionPowerMod", 0);
        illusion_power_mod_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iIllusionPowerMod", 0);
        restoration_power_mod_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iRestorationPowerMod", 0);
        speed_mult_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iSpeedMult", 0);
        inventory_weight_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iInventoryWeight", 0);
        carry_weight_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iCarryWeight", 0);
        critical_chance_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iCriticalChance", 0);
        melee_damage_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iMeleeDamage", 0);
        unarmed_damage_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iUnarmedDamage", 0);
        absorb_chance_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iAbsorbChance", 0);
        weapon_speed_mult_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iWeaponSpeedMult", 0);
        bow_speed_bonus_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iBowSpeedBonus", 0);
        shout_recovery_mult_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iShoutRecoveryMult", 0);
        movement_noise_mult_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iMovementNoiseMult", 0);
        attack_damage_mult_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iAttackDamageMult", 0);
        reflect_damage_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iReflectDamage", 0);
        one_handed_mod_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iOneHandedMod", 0);
        two_handed_mod_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iTwoHandedMod", 0);
        archery_mod_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iArcheryMod", 0);
        block_mod_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iBlockMod", 0);
        smithing_mod_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iSmithingMod", 0);
        heavy_armor_mod_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iHeavyArmorMod", 0);
        light_armor_mod_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iLightArmorMod", 0);
        pickpocket_mod_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iPickpocketMod", 0);
        lockpicking_mod_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iLockpickingMod", 0);
        sneak_mod_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iSneakMod", 0);
        alchemy_mod_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iAlchemyMod", 0);
        speech_mod_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iSpeechMod", 0);
        enchanting_mod_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iEnchantingMod", 0);
        alteration_mod_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iAlterationMod", 0);
        conjuration_mod_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iConjurationMod", 0);
        destruction_mod_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iDestructionMod", 0);
        illusion_mod_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iIllusionMod", 0);
        restoration_mod_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iRestorationMod", 0);
        damage_arrow_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iDamageArrow", 0);
        damage_left_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iDamageLeft", 0);
        left_weapon_speed_mult_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iLeftWeaponSpeedMult", 0);
        right_item_charge_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iRightItemCharge", 0);
        left_item_charge_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iLeftItemCharge", 0);
        armor_perks_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iArmorPerks", 0);
        mass_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iMass", 0);
        bow_stagger_bonus_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iBowStaggerBonus", 0);
        weapon_reach_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iWeaponReach", 0);
        weapon_reach_left_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iWeaponReachLeft", 0);
        weapon_base_damage_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iWeaponBaseDamage", 0);
        weapon_base_damage_left_menu_inventory_ = ini.
            GetLongValue("showStatsInventoryMenu", "iWeaponBaseDamageLeft", 0);
        weapon_stagger_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iWeaponStagger", 0);
        weapon_stagger_left_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iWeaponStaggerLeft", 0);
        weapon_crit_damage_rating_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu",
            "iWeaponCritDamageRating",
            0);
        weapon_crit_damage_rating_left_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu",
            "iWeaponCritDamageRatingLeft",
            0);
        fall_damage_mod_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iFallDamageMod", 0);
        warmth_menu_inventory_ = ini.GetLongValue("showStatsInventoryMenu", "iWarmth", 0);
    }

    /*static void set_show_window(const bool a_show_value) {
        logger::debug("setting new value for {} is {}"sv, "bShowWindow", a_show_value);
        show_window_ = a_show_value;

        CSimpleIniA ini;
        ini.SetUnicode();
        ini.LoadFile(ini_path_);

        ini.SetBoolValue("Toggle", "bShowWindow", a_show_value);

        (void)ini.SaveFile(ini_path_);
    }*/

    static int get_log_level() { return log_level_; }
    static int get_open_menu_button() { return open_menu_button_; }
    static bool get_open_faction_menu_button() { return open_faction_menu_button_; }
    static bool get_pause_game() { return pause_game_; }
    static bool get_show_inventory_stats() { return show_inventory_stats_; }
    static bool get_show_inventory_stats_auto_open() { return show_inventory_stats_auto_open_; }
    static int get_show_inventory_button() { return show_inventory_button_; }
    static int get_display_av_type() { return display_av_type_; }
    static bool get_skyrim_unbound() { return skyrim_unbound_; }
    static bool get_hand_to_hand() { return hand_to_hand_; }
    static bool get_show_resistance_cap() { return show_resistance_cap_; }
    static bool get_show_stats_display_zero() { return show_stats_display_zero_; }
    static std::string get_height_string_ending() { return height_string_ending_; }
    static std::string get_equipped_weight_string_ending() { return equipped_weight_string_ending_; }
    static std::string get_weight_string_ending() { return weight_string_ending_; }
    static std::string get_health_rate_string_ending() { return health_rate_string_ending_; }
    static std::string get_magicka_rate_string_ending() { return magicka_rate_string_ending_; }
    static std::string get_stamina_rate_string_ending() { return stamina_rate_string_ending_; }
    static std::string get_resist_damage_string_ending() { return resist_damage_string_ending_; }
    static std::string get_resist_disease_string_ending() { return resist_disease_string_ending_; }
    static std::string get_resist_poison_string_ending() { return resist_poison_string_ending_; }
    static std::string get_resist_fire_string_ending() { return resist_fire_string_ending_; }
    static std::string get_resist_shock_string_ending() { return resist_shock_string_ending_; }
    static std::string get_resist_frost_string_ending() { return resist_frost_string_ending_; }
    static std::string get_resist_magic_string_ending() { return resist_magic_string_ending_; }
    static std::string get_speed_mult_string_ending() { return speed_mult_string_ending_; }
    static std::string get_inventory_weight_string_ending() { return inventory_weight_string_ending_; }
    static std::string get_carry_weight_string_ending() { return carry_weight_string_ending_; }
    static std::string get_critical_chance_string_ending() { return critical_chance_string_ending_; }
    static std::string get_absorb_chance_string_ending() { return absorb_chance_string_ending_; }
    static std::string get_weapon_speed_mult_string_ending() { return weapon_speed_mult_string_ending_; }
    static std::string get_bow_speed_bonus_string_ending() { return bow_speed_bonus_string_ending_; }
    static std::string get_shout_recovery_mult_string_ending() { return shout_recovery_mult_string_ending_; }
    static std::string get_movement_noise_mult_string_ending() { return movement_noise_mult_string_ending_; }

    static std::string get_combat_health_regen_multiply_string_ending() {
        return combat_health_regen_multiply_string_ending_;
    }

    static std::string get_attack_damage_mult_string_ending() { return attack_damage_mult_string_ending_; }
    static std::string get_reflect_damage_string_ending() { return reflect_damage_string_ending_; }
    static std::string get_one_handed_mod_string_ending() { return one_handed_mod_string_ending_; }
    static std::string get_two_handed_mod_string_ending() { return two_handed_mod_string_ending_; }
    static std::string get_archery_mod_string_ending() { return archery_mod_string_ending_; }
    static std::string get_block_mod_string_ending() { return block_mod_string_ending_; }
    static std::string get_smithing_mod_string_ending() { return smithing_mod_string_ending_; }
    static std::string get_heavy_armor_mod_string_ending() { return heavy_armor_mod_string_ending_; }
    static std::string get_light_armor_mod_string_ending() { return light_armor_mod_string_ending_; }
    static std::string get_pickpocket_mod_string_ending() { return pickpocket_mod_string_ending_; }
    static std::string get_lockpicking_mod_string_ending() { return lockpicking_mod_string_ending_; }
    static std::string get_sneak_mod_string_ending() { return sneak_mod_string_ending_; }
    static std::string get_alchemy_mod_string_ending() { return alchemy_mod_string_ending_; }
    static std::string get_speech_mod_string_ending() { return speech_mod_string_ending_; }
    static std::string get_enchanting_mod_string_ending() { return enchanting_mod_string_ending_; }
    static std::string get_alteration_mod_string_ending() { return alteration_mod_string_ending_; }
    static std::string get_conjuration_mod_string_ending() { return conjuration_mod_string_ending_; }
    static std::string get_destruction_mod_string_ending() { return destruction_mod_string_ending_; }
    static std::string get_illusion_mod_string_ending() { return illusion_mod_string_ending_; }
    static std::string get_restoration_mod_string_ending() { return restoration_mod_string_ending_; }
    static std::string get_left_weapon_speed_mult_string_ending() { return left_weapon_speed_mult_string_ending_; }
    static std::string get_armor_perks_string_ending() { return armor_perks_string_ending_; }
    static std::string get_fall_damage_mod_string_ending() { return fall_damage_mod_string_ending_; }

    static int get_height_menu() { return height_menu_; }
    static int get_equiped_weight_menu() { return equiped_weight_menu_; }
    static int get_weight_menu() { return weight_menu_; }
    static int get_armor_menu() { return armor_menu_; }
    static int get_damage_menu() { return damage_menu_; }
    static int get_skill_trainings_this_level_menu() { return skill_trainings_this_level_menu_; }
    static int get_health_menu() { return health_menu_; }
    static int get_health_rate_menu() { return health_rate_menu_; }
    static int get_magicka_menu() { return magicka_menu_; }
    static int get_magicka_rate_menu() { return magicka_rate_menu_; }
    static int get_stamina_menu() { return stamina_menu_; }
    static int get_stamina_rate_menu() { return stamina_rate_menu_; }
    static int get_resist_damage_menu() { return resist_damage_menu_; }
    static int get_resist_disease_menu() { return resist_disease_menu_; }
    static int get_resist_poison_menu() { return resist_poison_menu_; }
    static int get_resist_fire_menu() { return resist_fire_menu_; }
    static int get_resist_shock_menu() { return resist_shock_menu_; }
    static int get_resist_frost_menu() { return resist_frost_menu_; }
    static int get_resist_magic_menu() { return resist_magic_menu_; }
    static int get_one_handed_menu() { return one_handed_menu_; }
    static int get_two_handed_menu() { return two_handed_menu_; }
    static int get_archery_menu() { return archery_menu_; }
    static int get_block_menu() { return block_menu_; }
    static int get_smithing_menu() { return smithing_menu_; }
    static int get_heavy_armor_menu() { return heavy_armor_menu_; }
    static int get_light_armor_menu() { return light_armor_menu_; }
    static int get_pickpocket_menu() { return pickpocket_menu_; }
    static int get_lockpicking_menu() { return lockpicking_menu_; }
    static int get_sneak_menu() { return sneak_menu_; }
    static int get_alchemy_menu() { return alchemy_menu_; }
    static int get_speech_menu() { return speech_menu_; }
    static int get_enchanting_menu() { return enchanting_menu_; }
    static int get_alteration_menu() { return alteration_menu_; }
    static int get_conjuration_menu() { return conjuration_menu_; }
    static int get_destruction_menu() { return destruction_menu_; }
    static int get_illusion_menu() { return illusion_menu_; }
    static int get_restoration_menu() { return restoration_menu_; }
    static int get_one_handed_power_mod_menu() { return one_handed_power_mod_menu_; }
    static int get_two_handed_power_mod_menu() { return two_handed_power_mod_menu_; }
    static int get_archery_power_mod_menu() { return archery_power_mod_menu_; }
    static int get_block_power_mod_menu() { return block_power_mod_menu_; }
    static int get_smithing_power_mod_menu() { return smithing_power_mod_menu_; }
    static int get_heavy_armor_power_mod_menu() { return heavy_armor_power_mod_menu_; }
    static int get_light_armor_power_mod_menu() { return light_armor_power_mod_menu_; }
    static int get_pickpocket_power_mod_menu() { return pickpocket_power_mod_menu_; }
    static int get_lockpicking_power_mod_menu() { return lockpicking_power_mod_menu_; }
    static int get_sneak_power_mod_menu() { return sneak_power_mod_menu_; }
    static int get_alchemy_power_mod_menu() { return alchemy_power_mod_menu_; }
    static int get_speech_power_mod_menu() { return speech_power_mod_menu_; }
    static int get_enchanting_power_mod_menu() { return enchanting_power_mod_menu_; }
    static int get_alteration_power_mod_menu() { return alteration_power_mod_menu_; }
    static int get_conjuration_power_mod_menu() { return conjuration_power_mod_menu_; }
    static int get_destruction_power_mod_menu() { return destruction_power_mod_menu_; }
    static int get_illusion_power_mod_menu() { return illusion_power_mod_menu_; }
    static int get_restoration_power_mod_menu() { return restoration_power_mod_menu_; }
    static int get_speed_mult_menu() { return speed_mult_menu_; }
    static int get_inventory_weight_menu() { return inventory_weight_menu_; }
    static int get_carry_weight_menu() { return carry_weight_menu_; }
    static int get_critical_chance_menu() { return critical_chance_menu_; }
    static int get_melee_damage_menu() { return melee_damage_menu_; }
    static int get_unarmed_damage_menu() { return unarmed_damage_menu_; }
    static int get_absorb_chance_menu() { return absorb_chance_menu_; }
    static int get_weapon_speed_mult_menu() { return weapon_speed_mult_menu_; }
    static int get_bow_speed_bonus_menu() { return bow_speed_bonus_menu_; }
    static int get_shout_recovery_mult_menu() { return shout_recovery_mult_menu_; }
    static int get_movement_noise_mult_menu() { return movement_noise_mult_menu_; }
    static int get_dragon_souls_menu() { return dragon_souls_menu_; }
    static int get_combat_health_regen_multiply_menu() { return combat_health_regen_multiply_menu_; }
    static int get_attack_damage_mult_menu() { return attack_damage_mult_menu_; }
    static int get_reflect_damage_menu() { return reflect_damage_menu_; }
    static int get_one_handed_mod_menu() { return one_handed_mod_menu_; }
    static int get_two_handed_mod_menu() { return two_handed_mod_menu_; }
    static int get_archery_mod_menu() { return archery_mod_menu_; }
    static int get_block_mod_menu() { return block_mod_menu_; }
    static int get_smithing_mod_menu() { return smithing_mod_menu_; }
    static int get_heavy_armor_mod_menu() { return heavy_armor_mod_menu_; }
    static int get_light_armor_mod_menu() { return light_armor_mod_menu_; }
    static int get_pickpocket_mod_menu() { return pickpocket_mod_menu_; }
    static int get_lockpicking_mod_menu() { return lockpicking_mod_menu_; }
    static int get_sneak_mod_menu() { return sneak_mod_menu_; }
    static int get_alchemy_mod_menu() { return alchemy_mod_menu_; }
    static int get_speech_mod_menu() { return speech_mod_menu_; }
    static int get_enchanting_mod_menu() { return enchanting_mod_menu_; }
    static int get_alteration_mod_menu() { return alteration_mod_menu_; }
    static int get_conjuration_mod_menu() { return conjuration_mod_menu_; }
    static int get_destruction_mod_menu() { return destruction_mod_menu_; }
    static int get_illusion_mod_menu() { return illusion_mod_menu_; }
    static int get_restoration_mod_menu() { return restoration_mod_menu_; }
    static int get_damage_arrow_menu() { return damage_arrow_menu_; }
    static int get_damage_left_menu() { return damage_left_menu_; }
    static int get_left_weapon_speed_mult_menu() { return left_weapon_speed_mult_menu_; }
    static int get_right_item_charge_menu() { return right_item_charge_menu_; }
    static int get_left_item_charge_menu() { return left_item_charge_menu_; }
    static int get_armor_perks_menu() { return armor_perks_menu_; }
    static int get_mass_menu() { return mass_menu_; }
    static int get_bow_stagger_bonus_menu() { return bow_stagger_bonus_menu_; }
    static int get_bypass_vendor_keyword_check_menu() { return bypass_vendor_keyword_check_menu_; }
    static int get_bypass_vendor_stolen_check_menu() { return bypass_vendor_stolen_check_menu_; }
    static int get_weapon_reach_menu() { return weapon_reach_menu_; }
    static int get_weapon_reach_left_menu() { return weapon_reach_left_menu_; }
    static int get_weapon_base_damage_menu() { return weapon_base_damage_menu_; }
    static int get_weapon_base_damage_left_menu() { return weapon_base_damage_left_menu_; }
    static int get_weapon_stagger_menu() { return weapon_stagger_menu_; }
    static int get_weapon_stagger_left_menu() { return weapon_stagger_left_menu_; }
    static int get_weapon_crit_damage_rating_menu() { return weapon_crit_damage_rating_menu_; }
    static int get_weapon_crit_damage_rating_left_menu() { return weapon_crit_damage_rating_left_menu_; }
    static int get_fall_damage_mod_menu() { return fall_damage_mod_menu_; }
    static int get_warmth_menu() { return warmth_menu_; }
    static int get_weapon_speed_mult_mult() { return weapon_speed_mult_mult_; }
    static int get_shout_recovery_mult_mult() { return shout_recovery_mult_mult_; }
    static int get_movement_noise_mult_mult() { return movement_noise_mult_mult_; }
    static int get_combat_health_regen_multiply_mult() { return combat_health_regen_multiply_mult_; }
    static int get_left_weapon_speed_mult_mult() { return left_weapon_speed_mult_mult_; }
    static int get_armor_perks_mult() { return armor_perks_mult_; }
    static int get_fall_damage_mod_mult() { return fall_damage_mod_mult_; }

    static int get_faction_menu() { return faction_menu_; }
    static int get_thane_menu() { return thane_menu_; }
    static int get_champion_menu() { return champion_menu_; }
    static int get_show_stats_inventorydisplay_zero() { return show_stats_inventorydisplay_zero_; }
    static int get_equiped_weight_menu_inventory() { return equiped_weight_menu_inventory_; }
    static int get_armor_menu_inventory() { return armor_menu_inventory_; }
    static int get_damage_menu_inventory() { return damage_menu_inventory_; }
    static int get_health_menu_inventory() { return health_menu_inventory_; }
    static int get_health_rate_menu_inventory() { return health_rate_menu_inventory_; }
    static int get_magicka_menu_inventory() { return magicka_menu_inventory_; }
    static int get_magicka_rate_menu_inventory() { return magicka_rate_menu_inventory_; }
    static int get_stamina_menu_inventory() { return stamina_menu_inventory_; }
    static int get_stamina_rate_menu_inventory() { return stamina_rate_menu_inventory_; }
    static int get_resist_damage_menu_inventory() { return resist_damage_menu_inventory_; }
    static int get_resist_disease_menu_inventory() { return resist_disease_menu_inventory_; }
    static int get_resist_poison_menu_inventory() { return resist_poison_menu_inventory_; }
    static int get_resist_fire_menu_inventory() { return resist_fire_menu_inventory_; }
    static int get_resist_shock_menu_inventory() { return resist_shock_menu_inventory_; }
    static int get_resist_frost_menu_inventory() { return resist_frost_menu_inventory_; }
    static int get_resist_magic_menu_inventory() { return resist_magic_menu_inventory_; }
    static int get_one_handed_menu_inventory() { return one_handed_menu_inventory_; }
    static int get_two_handed_menu_inventory() { return two_handed_menu_inventory_; }
    static int get_archery_menu_inventory() { return archery_menu_inventory_; }
    static int get_block_menu_inventory() { return block_menu_inventory_; }
    static int get_smithing_menu_inventory() { return smithing_menu_inventory_; }
    static int get_heavy_armor_menu_inventory() { return heavy_armor_menu_inventory_; }
    static int get_light_armor_menu_inventory() { return light_armor_menu_inventory_; }
    static int get_pickpocket_menu_inventory() { return pickpocket_menu_inventory_; }
    static int get_lockpicking_menu_inventory() { return lockpicking_menu_inventory_; }
    static int get_sneak_menu_inventory() { return sneak_menu_inventory_; }
    static int get_alchemy_menu_inventory() { return alchemy_menu_inventory_; }
    static int get_speech_menu_inventory() { return speech_menu_inventory_; }
    static int get_enchanting_menu_inventory() { return enchanting_menu_inventory_; }
    static int get_alteration_menu_inventory() { return alteration_menu_inventory_; }
    static int get_conjuration_menu_inventory() { return conjuration_menu_inventory_; }
    static int get_destruction_menu_inventory() { return destruction_menu_inventory_; }
    static int get_illusion_menu_inventory() { return illusion_menu_inventory_; }
    static int get_restoration_menu_inventory() { return restoration_menu_inventory_; }
    static int get_one_handed_power_mod_menu_inventory() { return one_handed_power_mod_menu_inventory_; }
    static int get_two_handed_power_mod_menu_inventory() { return two_handed_power_mod_menu_inventory_; }
    static int get_archery_power_mod_menu_inventory() { return archery_power_mod_menu_inventory_; }
    static int get_block_power_mod_menu_inventory() { return block_power_mod_menu_inventory_; }
    static int get_smithing_power_mod_menu_inventory() { return smithing_power_mod_menu_inventory_; }
    static int get_heavy_armor_power_mod_menu_inventory() { return heavy_armor_power_mod_menu_inventory_; }
    static int get_light_armor_power_mod_menu_inventory() { return light_armor_power_mod_menu_inventory_; }
    static int get_pickpocket_power_mod_menu_inventory() { return pickpocket_power_mod_menu_inventory_; }
    static int get_lockpicking_power_mod_menu_inventory() { return lockpicking_power_mod_menu_inventory_; }
    static int get_sneak_power_mod_menu_inventory() { return sneak_power_mod_menu_inventory_; }
    static int get_alchemy_power_mod_menu_inventory() { return alchemy_power_mod_menu_inventory_; }
    static int get_speech_power_mod_menu_inventory() { return speech_power_mod_menu_inventory_; }
    static int get_enchanting_power_mod_menu_inventory() { return enchanting_power_mod_menu_inventory_; }
    static int get_alteration_power_mod_menu_inventory() { return alteration_power_mod_menu_inventory_; }
    static int get_conjuration_power_mod_menu_inventory() { return conjuration_power_mod_menu_inventory_; }
    static int get_destruction_power_mod_menu_inventory() { return destruction_power_mod_menu_inventory_; }
    static int get_illusion_power_mod_menu_inventory() { return illusion_power_mod_menu_inventory_; }
    static int get_restoration_power_mod_menu_inventory() { return restoration_power_mod_menu_inventory_; }
    static int get_speed_mult_menu_inventory() { return speed_mult_menu_inventory_; }
    static int get_inventory_weight_menu_inventory() { return inventory_weight_menu_inventory_; }
    static int get_carry_weight_menu_inventory() { return carry_weight_menu_inventory_; }
    static int get_critical_chance_menu_inventory() { return critical_chance_menu_inventory_; }
    static int get_melee_damage_menu_inventory() { return melee_damage_menu_inventory_; }
    static int get_unarmed_damage_menu_inventory() { return unarmed_damage_menu_inventory_; }
    static int get_absorb_chance_menu_inventory() { return absorb_chance_menu_inventory_; }
    static int get_weapon_speed_mult_menu_inventory() { return weapon_speed_mult_menu_inventory_; }
    static int get_bow_speed_bonus_menu_inventory() { return bow_speed_bonus_menu_inventory_; }
    static int get_shout_recovery_mult_menu_inventory() { return shout_recovery_mult_menu_inventory_; }
    static int get_movement_noise_mult_menu_inventory() { return movement_noise_mult_menu_inventory_; }
    static int get_attack_damage_mult_menu_inventory() { return attack_damage_mult_menu_inventory_; }
    static int get_reflect_damage_menu_inventory() { return reflect_damage_menu_inventory_; }
    static int get_one_handed_mod_menu_inventory() { return one_handed_mod_menu_inventory_; }
    static int get_two_handed_mod_menu_inventory() { return two_handed_mod_menu_inventory_; }
    static int get_archery_mod_menu_inventory() { return archery_mod_menu_inventory_; }
    static int get_block_mod_menu_inventory() { return block_mod_menu_inventory_; }
    static int get_smithing_mod_menu_inventory() { return smithing_mod_menu_inventory_; }
    static int get_heavy_armor_mod_menu_inventory() { return heavy_armor_mod_menu_inventory_; }
    static int get_light_armor_mod_menu_inventory() { return light_armor_mod_menu_inventory_; }
    static int get_pickpocket_mod_menu_inventory() { return pickpocket_mod_menu_inventory_; }
    static int get_lockpicking_mod_menu_inventory() { return lockpicking_mod_menu_inventory_; }
    static int get_sneak_mod_menu_inventory() { return sneak_mod_menu_inventory_; }
    static int get_alchemy_mod_menu_inventory() { return alchemy_mod_menu_inventory_; }
    static int get_speech_mod_menu_inventory() { return speech_mod_menu_inventory_; }
    static int get_enchanting_mod_menu_inventory() { return enchanting_mod_menu_inventory_; }
    static int get_alteration_mod_menu_inventory() { return alteration_mod_menu_inventory_; }
    static int get_conjuration_mod_menu_inventory() { return conjuration_mod_menu_inventory_; }
    static int get_destruction_mod_menu_inventory() { return destruction_mod_menu_inventory_; }
    static int get_illusion_mod_menu_inventory() { return illusion_mod_menu_inventory_; }
    static int get_restoration_mod_menu_inventory() { return restoration_mod_menu_inventory_; }
    static int get_damage_arrow_menu_inventory() { return damage_arrow_menu_inventory_; }
    static int get_damage_left_menu_inventory() { return damage_left_menu_inventory_; }
    static int get_left_weapon_speed_mult_menu_inventory() { return left_weapon_speed_mult_menu_inventory_; }
    static int get_right_item_charge_menu_inventory() { return right_item_charge_menu_inventory_; }
    static int get_left_item_charge_menu_inventory() { return left_item_charge_menu_inventory_; }
    static int get_armor_perks_menu_inventory() { return armor_perks_menu_inventory_; }
    static int get_mass_menu_inventory() { return mass_menu_inventory_; }
    static int get_bow_stagger_bonus_menu_inventory() { return bow_stagger_bonus_menu_inventory_; }
    static int get_weapon_reach_menu_inventory() { return weapon_reach_menu_inventory_; }
    static int get_weapon_reach_left_menu_inventory() { return weapon_reach_left_menu_inventory_; }
    static int get_weapon_base_damage_menu_inventory() { return weapon_base_damage_menu_inventory_; }
    static int get_weapon_base_damage_left_menu_inventory() { return weapon_base_damage_left_menu_inventory_; }
    static int get_weapon_stagger_menu_inventory() { return weapon_stagger_menu_inventory_; }
    static int get_weapon_stagger_left_menu_inventory() { return weapon_stagger_left_menu_inventory_; }
    static int get_weapon_crit_damage_rating_menu_inventory() { return weapon_crit_damage_rating_menu_inventory_; }

    static int get_weapon_crit_damage_rating_left_menu_inventory() {
        return weapon_crit_damage_rating_left_menu_inventory_;
    }

    static int get_fall_damage_mod_menu_inventory() { return fall_damage_mod_menu_inventory_; }
    static int get_warmth_menu_inventory() { return warmth_menu_inventory_; }
};
