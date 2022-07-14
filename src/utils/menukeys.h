#pragma once

namespace menu_keys {
    //Show Stats
    constexpr auto show_stats_title = "$ShowStatsTitle"sv;
    constexpr auto player_title = "$ShowStatsPlayerTitle"sv;
    constexpr auto attack_title = "$ShowStatsAttackTitle"sv;
    constexpr auto defence_title = "$ShowStatsDefenceTitle"sv;
    constexpr auto magic_title = "$ShowStatsMagicTitle"sv;
    constexpr auto thief_title = "$ShowStatsThiefTitle"sv;
    constexpr auto warrior_title = "$ShowStatsWarriorTitle"sv;

    //Show Factions
    constexpr auto show_factions_title = "$ShowFactionsTitle"sv;
    constexpr auto faction_title = "$ShowFactionsFactionTitle"sv;
    constexpr auto thane_title = "$ShowFactionsThaneTitle"sv;
    constexpr auto champion_title = "$ShowFactionsChampionTitle"sv;

    //Show Stats Inventory
    constexpr auto show_stats_inventory_title = "$ShowStatsInventoryTitle"sv;
    constexpr auto equip_title = "$ShowStatsInventoryEquipmentTitle"sv;
    constexpr auto armor_title = "$ShowStatsInventoryArmorTitle"sv;
    constexpr auto weapon_title = "$ShowStatsInventoryWeaponTitle"sv;
    constexpr auto effect_title = "$ShowStatsInventoryEffectTitle"sv;

    constexpr auto name = "$ShowName"sv;
    constexpr auto race = "$ShowRace"sv;
    constexpr auto level = "$ShowLevel"sv;
    constexpr auto perk = "$ShowPerkCount"sv;
    constexpr auto height = "$ShowHeight"sv;
    constexpr auto equipped_weight = "$ShowEquippedWeight"sv;
    constexpr auto weight = "$ShowWeight"sv;
    constexpr auto armor = "$ShowArmor"sv;
    constexpr auto damage = "$ShowDamage"sv;
    constexpr auto trainings_level = "$ShowSkillTrainingsThisLevel"sv;
    constexpr auto health = "$ShowHealth"sv;
    constexpr auto health_rate = "$ShowHealthRatePer"sv;
    constexpr auto magicka = "$ShowMagicka"sv;
    constexpr auto magicka_rate = "$ShowMagickaRatePer"sv;
    constexpr auto stamina = "$ShowStamina"sv;
    constexpr auto stamina_rate = "$ShowStaminaRatePer"sv;
    constexpr auto resist_damage = "$ShowResistDamage"sv;
    constexpr auto resist_disease = "$ShowResistDisease"sv;
    constexpr auto resist_poison = "$ShowResistPoison"sv;
    constexpr auto resist_fire = "$ShowResistFire"sv;
    constexpr auto resist_shock = "$ShowResistShock"sv;
    constexpr auto resist_frost = "$ShowResistFrost"sv;
    constexpr auto resist_magic = "$ShowResistMagic"sv;
    constexpr auto one_handed = "$ShowOneHanded"sv;
    constexpr auto two_handed = "$ShowTwoHanded"sv;
    constexpr auto archery = "$ShowArchery"sv;
    constexpr auto block = "$ShowBlock"sv;
    constexpr auto smithing = "$ShowSmithing"sv;
    constexpr auto heavy_armor = "$ShowHeavyArmor"sv;
    constexpr auto light_armor = "$ShowLightArmor"sv;
    constexpr auto pickpocket = "$ShowPickpocket"sv;
    constexpr auto lockpicking = "$ShowLockpicking"sv;
    constexpr auto sneak = "$ShowSneak"sv;
    constexpr auto alchemy = "$ShowAlchemy"sv;
    constexpr auto speech = "$ShowSpeech"sv;
    constexpr auto enchanting = "$ShowEnchanting"sv;
    constexpr auto alteration = "$ShowAlteration"sv;
    constexpr auto conjuration = "$ShowConjuration"sv;
    constexpr auto destruction = "$ShowDestruction"sv;
    constexpr auto illusion = "$ShowIllusion"sv;
    constexpr auto restoration = "$ShowRestoration"sv;
    constexpr auto one_handed_power_mod = "$ShowOneHandedPowerMod"sv;
    constexpr auto two_handed_power_mod = "$ShowTwoHandedPowerMod"sv;
    constexpr auto archery_power_mod = "$ShowArcheryPowerMod"sv;
    constexpr auto block_power_mod = "$ShowBlockPowerMod"sv;
    constexpr auto smithing_power_mod = "$ShowSmithingPowerMod"sv;
    constexpr auto heavy_armor_power_mod = "$ShowHeavyArmorPowerMod"sv;
    constexpr auto light_armor_power_mod = "$ShowLightArmorPowerMod"sv;
    constexpr auto pickpocket_power_mod = "$ShowPickpocketPowerMod"sv;
    constexpr auto lockpicking_power_mod = "$ShowLockpickingPowerMod"sv;
    constexpr auto sneak_power_mod = "$ShowSneakPowerMod"sv;
    constexpr auto alchemy_power_mod = "$ShowAlchemyPowerMod"sv;
    constexpr auto speech_power_mod = "$ShowSpeechPowerMod"sv;
    constexpr auto enchanting_power_mod = "$ShowEnchantingPowerMod"sv;
    constexpr auto alteration_power_mod = "$ShowAlterationPowerMod"sv;
    constexpr auto conjuration_power_mod = "$ShowConjurationPowerMod"sv;
    constexpr auto destruction_power_mod = "$ShowDestructionPowerMod"sv;
    constexpr auto illusion_power_mod = "$ShowIllusionPowerMod"sv;
    constexpr auto restoration_power_mod = "$ShowRestorationPowerMod"sv;
    constexpr auto speed_mult = "$ShowSpeedMult"sv;
    constexpr auto inventory_weight = "$ShowInventoryWeight"sv;
    constexpr auto carry_weight = "$ShowCarryWeight"sv;
    constexpr auto critical_chance = "$ShowCriticalChance"sv;
    constexpr auto melee_damage = "$ShowMeleeDamage"sv;
    constexpr auto unarmed_damage = "$ShowUnarmedDamage"sv;
    constexpr auto absorb_chance = "$ShowAbsorbChance"sv;
    constexpr auto weapon_speed_mult = "$ShowWeaponSpeedMult"sv;
    constexpr auto bow_speed_bonus = "$ShowBowSpeedBonus"sv;
    constexpr auto shout_recovery_mult = "$ShowShoutRecoveryMult"sv;
    constexpr auto movement_noise_mult = "$ShowMovementNoiseMult"sv;
    constexpr auto dragon_souls = "$ShowDragonSouls"sv;
    constexpr auto combat_health_regen_mult = "$ShowCombatHealthRegenMultiply"sv;
    constexpr auto attack_damage_mult = "$ShowAttackDamageMult"sv;
    constexpr auto beast = "$ShowBeast"sv;
    constexpr auto xp = "$ShowXp"sv;
    constexpr auto reflect_damage = "$ShowReflectDamage"sv;
    constexpr auto one_handed_mod = "$ShowOneHandedMod"sv;
    constexpr auto two_handed_mod = "$ShowTwoHandedMod"sv;
    constexpr auto archery_mod = "$ShowArcheryMod"sv;
    constexpr auto block_mod = "$ShowBlockMod"sv;
    constexpr auto smithing_mod = "$ShowSmithingMod"sv;
    constexpr auto heavy_armor_mod = "$ShowHeavyArmorMod"sv;
    constexpr auto light_armor_mod = "$ShowLightArmorMod"sv;
    constexpr auto pickpocket_mod = "$ShowPickpocketMod"sv;
    constexpr auto lockpicking_mod = "$ShowLockpickingMod"sv;
    constexpr auto sneak_mod = "$ShowSneakMod"sv;
    constexpr auto alchemy_mod = "$ShowAlchemyMod"sv;
    constexpr auto speech_mod = "$ShowSpeechMod"sv;
    constexpr auto enchanting_mod = "$ShowEnchantingMod"sv;
    constexpr auto alteration_mod = "$ShowAlterationMod"sv;
    constexpr auto conjuration_mod = "$ShowConjurationMod"sv;
    constexpr auto destruction_mod = "$ShowDestructionMod"sv;
    constexpr auto illusion_mod = "$ShowIllusionMod"sv;
    constexpr auto restoration_mod = "$ShowRestorationMod"sv;
    constexpr auto damage_arrow = "$ShowDamageArrow"sv;
    constexpr auto damage_left = "$ShowDamageLeft"sv;
    constexpr auto left_weapon_speed_mult = "$ShowLeftWeaponSpeedMult"sv;
    constexpr auto right_item_charge = "$ShowRightItemCharge"sv;
    constexpr auto left_item_charge = "$ShowLeftItemCharge"sv;
    constexpr auto armor_perks = "$ShowArmorPerks"sv;
    constexpr auto mass = "$ShowMass"sv;
    constexpr auto bow_stagger_bonus = "$ShowBowStaggerBonus"sv;
    constexpr auto bypass_vendor_keyword_check = "$ShowBypassVendorKeywordCheck"sv;
    constexpr auto bypass_vendor_stolen_check = "$ShowBypassVendorStolenCheck"sv;
    constexpr auto weapon_reach = "$ShowWeaponReach"sv;
    constexpr auto weapon_reach_left = "$ShowWeaponReachLeft"sv;
    constexpr auto weapon_base_damage = "$ShowWeaponBaseDamage"sv;
    constexpr auto weapon_base_damage_left = "$ShowWeaponBaseDamageLeft"sv;
    constexpr auto weapon_stagger = "$ShowWeaponStagger"sv;
    constexpr auto weapon_stagger_left = "$ShowWeaponStaggerLeft"sv;
    constexpr auto weapon_crit_damage_rating = "$ShowWeaponCritDamageRating"sv;
    constexpr auto weapon_crit_damage_rating_left = "$ShowWeaponCritDamageRatingLeft"sv;
    constexpr auto fall_damage_mod = "$ShowFallDamageMod"sv;
    constexpr auto warmth = "$ShowWarmth"sv;

    constexpr auto vampire = "$ShowVampire"sv;
    constexpr auto werewolf = "$ShowWerewolf"sv;

    constexpr auto companions = "$ShowCompanions"sv;
    constexpr auto darkbrotherhood = "$ShowDarkbrotherHood"sv;
    constexpr auto college_of_winterhold = "$ShowCollegeOfWinterhold"sv;
    constexpr auto orc_friend = "$ShowOrcFriend"sv;
    constexpr auto thiefs_guild = "$ShowThiefsGuild"sv;
    constexpr auto imperial_legion = "$ShowImperialLegion"sv;
    constexpr auto stormcloaks = "$ShowStormcloaks"sv;
    constexpr auto greybeard = "$ShowGreybeard"sv;
    constexpr auto bard_college = "$ShowBardCollege"sv;
    constexpr auto volkihar_vampire_clan = "$ShowVolkiharVampireClan"sv;
    constexpr auto dawnguard = "$ShowDawnguard"sv;
    constexpr auto house_telvanni = "$ShowHouseTelvanni"sv;

    constexpr auto bard = "$ShowBard"sv;
    constexpr auto assassin = "$ShowAssassin"sv;
    constexpr auto listener = "$ShowListener"sv;
    constexpr auto auxiliary = "$ShowAuxiliary"sv;
    constexpr auto quaestor = "$ShowQuaestor"sv;
    constexpr auto praefect = "$ShowPraefect"sv;
    constexpr auto tribune = "$ShowTribune"sv;
    constexpr auto legate = "$ShowLegate"sv;
    constexpr auto unblooded = "$ShowUnblooded"sv;
    constexpr auto ice_veins = "$ShowIceVeins"sv;
    constexpr auto bone_breaker = "$ShowBoneBreaker"sv;
    constexpr auto snow_hammer = "$ShowSnowHammer"sv;
    constexpr auto stormblade = "$ShowStormblade"sv;
    constexpr auto vampire_lord = "$ShowVampireLord"sv;
    constexpr auto vampire_hunter = "$ShowVampireHunter"sv;
    constexpr auto honoary_member = "$ShowHonoraryMember"sv;
    constexpr auto ysmir = "$ShowYsmir"sv;

    constexpr auto windhelm = "$ShowWindhelm"sv;
    constexpr auto falkreath = "$ShowFalkreath"sv;
    constexpr auto solitude = "$ShowSolitude"sv;
    constexpr auto morthal = "$ShowMorthal"sv;
    constexpr auto dawnstar = "$ShowDawnstar"sv;
    constexpr auto markarth = "$ShowMarkarth"sv;
    constexpr auto riften = "$ShowRiften"sv;
    constexpr auto whiterun = "$ShowWhiterun"sv;
    constexpr auto winterhold = "$ShowWinterhold"sv;

    constexpr auto thane_of_eastmarch = "$ShowThaneOfEastmarch"sv;
    constexpr auto thane_of_falkreath = "$ShowThaneOfFalkreath"sv;
    constexpr auto thane_of_haafinger = "$ShowThaneOfHaafingar"sv;
    constexpr auto thane_of_hjaalmarch = "$ShowThaneOfHjaalmarch"sv;
    constexpr auto thane_of_the_pale = "$ShowThaneOfThePale"sv;
    constexpr auto thane_of_the_reach = "$ShowThaneOfTheReach"sv;
    constexpr auto thane_of_the_rift = "$ShowThaneOfTheRift"sv;
    constexpr auto thane_of_whiterun = "$ShowThaneOfWhiterun"sv;
    constexpr auto thane_of_winterhold = "$ShowThaneOfWinterhold"sv;

    constexpr auto azura = "$ShowAzura"sv;
    constexpr auto boethiah = "$ShowBoethiah"sv;
    constexpr auto clavicus_vile = "$ShowClavicusVile"sv;
    constexpr auto hermaeus_mora = "$ShowHermaeusMora"sv;
    constexpr auto hircine = "$ShowHircine"sv;
    constexpr auto malacath = "$ShowMalacath"sv;
    constexpr auto mehrunes_dagon = "$ShowMehrunesDagon"sv;
    constexpr auto mephala = "$ShowMephala"sv;
    constexpr auto meridia = "$ShowMeridia"sv;
    constexpr auto molag_bal = "$ShowMolagBal"sv;
    constexpr auto namira = "$ShowNamira"sv;
    constexpr auto nocturnal = "$ShowNocturnal"sv;
    constexpr auto peryite = "$ShowPeryite"sv;
    constexpr auto sanguine = "$ShowSanguine"sv;
    constexpr auto sheogorath = "$ShowSheogorath"sv;
    constexpr auto vearmina = "$ShowVaermina"sv;

    constexpr auto count = "$ShowCount"sv;

    //for hand to hand
    constexpr auto hand_to_hand = "$ShowHandToHand"sv;
    constexpr auto security = "$ShowSecurity"sv;
    constexpr auto hand_to_hand_power_mod = "$ShowHandToHandPowerMod"sv;
    constexpr auto security_power_mod = "$ShowSecurityPowerMod"sv;
    constexpr auto hand_to_hand_mod = "$ShowHandToHandMod"sv;
    constexpr auto security_mod = "$ShowSecurityMod"sv;
}
