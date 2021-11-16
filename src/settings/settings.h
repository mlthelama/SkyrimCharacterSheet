#pragma once

struct Settings {
    using ISetting = AutoTOML::ISetting;
    using bSetting = AutoTOML::bSetting;
    using sSetting = AutoTOML::sSetting;
    using iSetting = AutoTOML::iSetting;

    static void load() {
        try {
            const auto table = toml::parse_file("Data/SKSE/Plugins/ShowStats.toml"s);
            for (const auto& setting : ISetting::get_settings()) { setting->load(table); }
        } catch (const toml::parse_error& ex) {
            std::ostringstream ss;
            ss << "Error parsing file \'" << *ex.source().path << "\':\n"
               << '\t' << ex.description() << '\n'
               << "\t\t(" << ex.source().begin << ')';
            logger::error(ss.str());
            throw std::runtime_error("failed to load settings"s);
        }
    }

    static inline const char* _constUndefined = "<undef>";

    static inline iSetting logLevel{ "General"s, "logLevel"s, 0 };
    static inline iSetting openMenuButton{ "General"s, "openMenuButton", -1 };
    static inline bSetting closeOnOtherMenuOpen{ "General"s, "closeOnOtherMenuOpen"s, true };
    static inline bSetting showFactionMenu{ "General"s, "showFactionMenu"s, true };
    static inline iSetting openFactionMenuButton{ "General"s, "openNextMenuButton"s, 0 };
    static inline bSetting pauseGame{ "General"s, "pauseGame"s, true };
    static inline bSetting showInventoryStats{ "General"s, "showInventoryStats"s, true };
    static inline bSetting showInventoryStatsAutoOpen{ "General"s, "showInventoryStatsAutoOpen"s, true };

    static inline bSetting skyrimUnbound{ "Mods"s, "skyrimUnbound"s, true };

    static inline bSetting showResistanceCap{ "specialHandling"s, "showResistanceCap"s, true };

    static inline sSetting showStatsTitleTitle{ "showStatsTitle"s, "title"s, _constUndefined };
    static inline sSetting showStatsTitlePlayer{ "showStatsTitle"s, "player"s, _constUndefined };
    static inline sSetting showStatsTitleAttack{ "showStatsTitle"s, "attack"s, _constUndefined };
    static inline sSetting showStatsTitleDefence{ "showStatsTitle"s, "defence"s, _constUndefined };
    static inline sSetting showStatsTitleMagic{ "showStatsTitle"s, "magic"s, _constUndefined };
    static inline sSetting showStatsTitleThief{ "showStatsTitle"s, "thief"s, _constUndefined };
    static inline sSetting showStatsTitleWarrior{ "showStatsTitle"s, "warrior"s, _constUndefined };

    static inline bSetting name{ "showStats"s, "name"s, true };
    static inline bSetting race{ "showStats"s, "race"s, true };
    static inline bSetting level{ "showStats"s, "level"s, true };
    static inline bSetting perkCount{ "showStats"s, "perkCount"s, true };
    static inline bSetting height{ "showStats"s, "height"s, true };
    static inline bSetting equipedWeight{ "showStats"s, "equipedWeight"s, true };
    static inline bSetting weight{ "showStats"s, "weight"s, true };
    static inline bSetting armor{ "showStats"s, "armor"s, true };
    static inline bSetting damage{ "showStats"s, "damage"s, true };
    static inline bSetting skillTrainingsThisLevel{ "showStats"s, "skillTrainingsThisLevel"s, true };
    static inline bSetting health{ "showStats"s, "health"s, true };
    static inline bSetting healthRate{ "showStats"s, "healthRatePer"s, true };
    static inline bSetting magicka{ "showStats"s, "magicka"s, true };
    static inline bSetting magickaRate{ "showStats"s, "magickaRatePer"s, true };
    static inline bSetting stamina{ "showStats"s, "stamina"s, true };
    static inline bSetting staminaRate{ "showStats"s, "staminaRatePer"s, true };
    static inline bSetting resistDamage{ "showStats"s, "resistDamage"s, true };
    static inline bSetting resistDisease{ "showStats"s, "resistDisease"s, true };
    static inline bSetting resistPoison{ "showStats"s, "resistPoison"s, true };
    static inline bSetting resistFire{ "showStats"s, "resistFire"s, true };
    static inline bSetting resistShock{ "showStats"s, "resistShock"s, true };
    static inline bSetting resistFrost{ "showStats"s, "resistFrost"s, true };
    static inline bSetting resistMagic{ "showStats"s, "resistMagic"s, true };
    static inline bSetting oneHanded{ "showStats"s, "oneHanded"s, true };
    static inline bSetting twoHanded{ "showStats"s, "twoHanded"s, true };
    static inline bSetting archery{ "showStats"s, "archery"s, true };
    static inline bSetting block{ "showStats"s, "block"s, true };
    static inline bSetting smithing{ "showStats"s, "smithing"s, true };
    static inline bSetting heavyArmor{ "showStats"s, "heavyArmor"s, true };
    static inline bSetting lightArmor{ "showStats"s, "lightArmor"s, true };
    static inline bSetting pickpocket{ "showStats"s, "pickpocket"s, true };
    static inline bSetting lockpicking{ "showStats"s, "lockpicking"s, true };
    static inline bSetting sneak{ "showStats"s, "sneak"s, true };
    static inline bSetting alchemy{ "showStats"s, "alchemy"s, true };
    static inline bSetting speech{ "showStats"s, "speech"s, true };
    static inline bSetting enchanting{ "showStats"s, "enchanting"s, true };
    static inline bSetting alteration{ "showStats"s, "alteration"s, true };
    static inline bSetting conjuration{ "showStats"s, "conjuration"s, true };
    static inline bSetting destruction{ "showStats"s, "destruction"s, true };
    static inline bSetting illusion{ "showStats"s, "illusion"s, true };
    static inline bSetting restoration{ "showStats"s, "restoration"s, true };
    static inline bSetting oneHandedPowerMod{ "showStats"s, "oneHandedPowerMod"s, true };
    static inline bSetting twoHandedPowerMod{ "showStats"s, "twoHandedPowerMod"s, true };
    static inline bSetting archeryPowerMod{ "showStats"s, "archeryPowerMod"s, true };
    static inline bSetting blockPowerMod{ "showStats"s, "blockPowerMod"s, true };
    static inline bSetting smithingPowerMod{ "showStats"s, "smithingPowerMod"s, true };
    static inline bSetting heavyArmorPowerMod{ "showStats"s, "heavyArmorPowerMod"s, true };
    static inline bSetting lightArmorPowerMod{ "showStats"s, "lightArmorPowerMod"s, true };
    static inline bSetting pickpocketPowerMod{ "showStats"s, "pickpocketPowerMod"s, true };
    static inline bSetting lockpickingPowerMod{ "showStats"s, "lockpickingPowerMod"s, true };
    static inline bSetting sneakPowerMod{ "showStats"s, "sneakPowerMod"s, true };
    static inline bSetting alchemyPowerMod{ "showStats"s, "alchemyPowerMod"s, true };
    static inline bSetting speechPowerMod{ "showStats"s, "speechPowerMod"s, true };
    static inline bSetting enchantingPowerMod{ "showStats"s, "enchantingPowerMod"s, true };
    static inline bSetting alterationPowerMod{ "showStats"s, "alterationPowerMod"s, true };
    static inline bSetting conjurationPowerMod{ "showStats"s, "conjurationPowerMod"s, true };
    static inline bSetting destructionPowerMod{ "showStats"s, "destructionPowerMod"s, true };
    static inline bSetting illusionPowerMod{ "showStats"s, "illusionPowerMod"s, true };
    static inline bSetting restorationPowerMod{ "showStats"s, "restorationPowerMod"s, true };
    static inline bSetting speedMult{ "showStats"s, "speedMult"s, true };
    static inline bSetting inventoryWeight{ "showStats"s, "inventoryWeight"s, true };
    static inline bSetting carryWeight{ "showStats"s, "carryWeight"s, true };
    static inline bSetting criticalChance{ "showStats"s, "criticalChance"s, true };
    static inline bSetting meleeDamage{ "showStats"s, "meleeDamage"s, true };
    static inline bSetting unarmedDamage{ "showStats"s, "unarmedDamage"s, true };
    static inline bSetting absorbChance{ "showStats"s, "absorbChance"s, true };
    static inline bSetting weaponSpeedMult{ "showStats"s, "weaponSpeedMult"s, true };
    static inline bSetting bowSpeedBonus{ "showStats"s, "bowSpeedBonus"s, true };
    static inline bSetting shoutRecoveryMult{ "showStats"s, "shoutRecoveryMult"s, true };
    static inline bSetting movementNoiseMult{ "showStats"s, "movementNoiseMult"s, true };
    static inline bSetting dragonSouls{ "showStats"s, "dragonSouls"s, true };
    static inline bSetting combatHealthRegenMultiply{ "showStats"s, "combatHealthRegenMultiply"s, true };
    static inline bSetting attackDamageMult{ "showStats"s, "attackDamageMult"s, true };
    static inline bSetting beast{ "showStats"s, "beast"s, true };
    static inline bSetting xp{ "showStats"s, "xp"s, true };
    static inline bSetting reflectDamage{ "showStats"s, "reflectDamage"s, true };
    static inline bSetting oneHandedMod{ "showStats"s, "oneHandedMod"s, true };
    static inline bSetting twoHandedMod{ "showStats"s, "twoHandedMod"s, true };
    static inline bSetting archeryMod{ "showStats"s, "archeryMod"s, true };
    static inline bSetting blockMod{ "showStats"s, "blockMod"s, true };
    static inline bSetting smithingMod{ "showStats"s, "smithingMod"s, true };
    static inline bSetting heavyArmorMod{ "showStats"s, "heavyArmorMod"s, true };
    static inline bSetting lightArmorMod{ "showStats"s, "lightArmorMod"s, true };
    static inline bSetting pickpocketMod{ "showStats"s, "pickpocketMod"s, true };
    static inline bSetting lockpickingMod{ "showStats"s, "lockpickingMod"s, true };
    static inline bSetting sneakMod{ "showStats"s, "sneakMod"s, true };
    static inline bSetting alchemyMod{ "showStats"s, "alchemyMod"s, true };
    static inline bSetting speechMod{ "showStats"s, "speechMod"s, true };
    static inline bSetting enchantingMod{ "showStats"s, "enchantingMod"s, true };
    static inline bSetting alterationMod{ "showStats"s, "alterationMod"s, true };
    static inline bSetting conjurationMod{ "showStats"s, "conjurationMod"s, true };
    static inline bSetting destructionMod{ "showStats"s, "destructionMod"s, true };
    static inline bSetting illusionMod{ "showStats"s, "illusionMod"s, true };
    static inline bSetting restorationMod{ "showStats"s, "restorationMod"s, true };
    static inline bSetting damageArrow{ "showStats"s, "damageArrow"s, true };
    static inline bSetting damageLeft{ "showStats"s, "damageLeft"s, true };
    static inline bSetting leftWeaponSpeedMult{ "showStats"s, "leftWeaponSpeedMult"s, true };
    static inline bSetting rightItemCharge{ "showStats"s, "rightItemCharge"s, true };
    static inline bSetting leftItemCharge{ "showStats"s, "leftItemCharge"s, true };
    static inline bSetting armorPerks{ "showStats"s, "armorPerks"s, true };
    static inline bSetting mass{ "showStats"s, "mass"s, true };
    static inline bSetting bowStaggerBonus{ "showStats"s, "bowStaggerBonus"s, true };
    static inline bSetting bypassVendorKeywordCheck{ "showStats"s, "bypassVendorKeywordCheck"s, true };
    static inline bSetting bypassVendorStolenCheck{ "showStats"s, "bypassVendorStolenCheck"s, true };
    //factions handeled by a general setting

    static inline sSetting nameString{ "showStatsName"s, "name"s, _constUndefined };
    static inline sSetting raceString{ "showStatsName"s, "race"s, _constUndefined };
    static inline sSetting levelString{ "showStatsName"s, "level"s, _constUndefined };
    static inline sSetting perkCountString{ "showStatsName"s, "perkCount"s, _constUndefined };
    static inline sSetting heightString{ "showStatsName"s, "height"s, _constUndefined };
    static inline sSetting equipedWeightString{ "showStatsName"s, "equipedWeight"s, _constUndefined };
    static inline sSetting weightString{ "showStatsName"s, "weight"s, _constUndefined };
    static inline sSetting armorString{ "showStatsName"s, "armor"s, _constUndefined };
    static inline sSetting damageString{ "showStatsName"s, "damage"s, _constUndefined };
    static inline sSetting skillTrainingsThisLevelString{ "showStatsName"s,
        "skillTrainingsThisLevel"s,
        _constUndefined };
    static inline sSetting healthString{ "showStatsName"s, "health"s, _constUndefined };
    static inline sSetting healthRateString{ "showStatsName"s, "healthRatePer"s, _constUndefined };
    static inline sSetting magickaString{ "showStatsName"s, "magicka"s, _constUndefined };
    static inline sSetting magickaRateString{ "showStatsName"s, "magickaRatePer"s, _constUndefined };
    static inline sSetting staminaString{ "showStatsName"s, "stamina"s, _constUndefined };
    static inline sSetting staminaRateString{ "showStatsName"s, "staminaRatePer"s, _constUndefined };
    static inline sSetting resistDamageString{ "showStatsName"s, "resistDamage"s, _constUndefined };
    static inline sSetting resistDiseaseString{ "showStatsName"s, "resistDisease"s, _constUndefined };
    static inline sSetting resistPoisonString{ "showStatsName"s, "resistPoison"s, _constUndefined };
    static inline sSetting resistFireString{ "showStatsName"s, "resistFire"s, _constUndefined };
    static inline sSetting resistShockString{ "showStatsName"s, "resistShock"s, _constUndefined };
    static inline sSetting resistFrostString{ "showStatsName"s, "resistFrost"s, _constUndefined };
    static inline sSetting resistMagicString{ "showStatsName"s, "resistMagic"s, _constUndefined };
    static inline sSetting oneHandedString{ "showStatsName"s, "oneHanded"s, _constUndefined };
    static inline sSetting twoHandedString{ "showStatsName"s, "twoHanded"s, _constUndefined };
    static inline sSetting archeryString{ "showStatsName"s, "archery"s, _constUndefined };
    static inline sSetting blockString{ "showStatsName"s, "block"s, _constUndefined };
    static inline sSetting smithingString{ "showStatsName"s, "smithing"s, _constUndefined };
    static inline sSetting heavyArmorString{ "showStatsName"s, "heavyArmor"s, _constUndefined };
    static inline sSetting lightArmorString{ "showStatsName"s, "lightArmor"s, _constUndefined };
    static inline sSetting pickpocketString{ "showStatsName"s, "pickpocket"s, _constUndefined };
    static inline sSetting lockpickingString{ "showStatsName"s, "lockpicking"s, _constUndefined };
    static inline sSetting sneakString{ "showStatsName"s, "sneak"s, _constUndefined };
    static inline sSetting alchemyString{ "showStatsName"s, "alchemy"s, _constUndefined };
    static inline sSetting speechString{ "showStatsName"s, "speech"s, _constUndefined };
    static inline sSetting enchantingString{ "showStatsName"s, "enchanting"s, _constUndefined };
    static inline sSetting alterationString{ "showStatsName"s, "alteration"s, _constUndefined };
    static inline sSetting conjurationString{ "showStatsName"s, "conjuration"s, _constUndefined };
    static inline sSetting destructionString{ "showStatsName"s, "destruction"s, _constUndefined };
    static inline sSetting illusionString{ "showStatsName"s, "illusion"s, _constUndefined };
    static inline sSetting restorationString{ "showStatsName"s, "restoration"s, _constUndefined };
    static inline sSetting oneHandedPowerModString{ "showStatsName"s, "oneHandedPowerMod"s, _constUndefined };
    static inline sSetting twoHandedPowerModString{ "showStatsName"s, "twoHandedPowerMod"s, _constUndefined };
    static inline sSetting archeryPowerModString{ "showStatsName"s, "archeryPowerMod"s, _constUndefined };
    static inline sSetting blockPowerModString{ "showStatsName"s, "blockPowerMod"s, _constUndefined };
    static inline sSetting smithingPowerModString{ "showStatsName"s, "smithingPowerMod"s, _constUndefined };
    static inline sSetting heavyArmorPowerModString{ "showStatsName"s, "heavyArmorPowerMod"s, _constUndefined };
    static inline sSetting lightArmorPowerModString{ "showStatsName"s, "lightArmorPowerMod"s, _constUndefined };
    static inline sSetting pickpocketPowerModString{ "showStatsName"s, "pickpocketPowerMod"s, _constUndefined };
    static inline sSetting lockpickingPowerModString{ "showStatsName"s, "lockpickingPowerMod"s, _constUndefined };
    static inline sSetting sneakPowerModString{ "showStatsName"s, "sneakPowerMod"s, _constUndefined };
    static inline sSetting alchemyPowerModString{ "showStatsName"s, "alchemyPowerMod"s, _constUndefined };
    static inline sSetting speechPowerModString{ "showStatsName"s, "speechPowerMod"s, _constUndefined };
    static inline sSetting enchantingPowerModString{ "showStatsName"s, "enchantingPowerMod"s, _constUndefined };
    static inline sSetting alterationPowerModString{ "showStatsName"s, "alterationPowerMod"s, _constUndefined };
    static inline sSetting conjurationPowerModString{ "showStatsName"s, "conjurationPowerMod"s, _constUndefined };
    static inline sSetting destructionPowerModString{ "showStatsName"s, "destructionPowerMod"s, _constUndefined };
    static inline sSetting illusionPowerModString{ "showStatsName"s, "illusionPowerMod"s, _constUndefined };
    static inline sSetting restorationPowerModString{ "showStatsName"s, "restorationPowerMod"s, _constUndefined };
    static inline sSetting speedMultString{ "showStatsName"s, "speedMult"s, _constUndefined };
    static inline sSetting inventoryWeightString{ "showStatsName"s, "inventoryWeight"s, _constUndefined };
    static inline sSetting carryWeightString{ "showStatsName"s, "carryWeight"s, _constUndefined };
    static inline sSetting criticalChanceString{ "showStatsName"s, "criticalChance"s, _constUndefined };
    static inline sSetting meleeDamageString{ "showStatsName"s, "meleeDamage"s, _constUndefined };
    static inline sSetting unarmedDamageString{ "showStatsName"s, "unarmedDamage"s, _constUndefined };
    static inline sSetting absorbChanceString{ "showStatsName"s, "absorbChance"s, _constUndefined };
    static inline sSetting weaponSpeedMultString{ "showStatsName"s, "weaponSpeedMult"s, _constUndefined };
    static inline sSetting bowSpeedBonusString{ "showStatsName"s, "bowSpeedBonus"s, _constUndefined };
    static inline sSetting shoutRecoveryMultString{ "showStatsName"s, "shoutRecoveryMult"s, _constUndefined };
    static inline sSetting movementNoiseMultString{ "showStatsName"s, "movementNoiseMult"s, _constUndefined };
    static inline sSetting dragonSoulsString{ "showStatsName"s, "dragonSouls"s, _constUndefined };
    static inline sSetting combatHealthRegenMultiplyString{ "showStatsName"s,
        "combatHealthRegenMultiply"s,
        _constUndefined };
    static inline sSetting attackDamageMultString{ "showStatsName"s, "attackDamageMult"s, _constUndefined };
    static inline sSetting beastString{ "showStatsName"s, "beast"s, _constUndefined };
    static inline sSetting xpString{ "showStatsName"s, "xp"s, _constUndefined };
    static inline sSetting reflectDamageString{ "showStatsName"s, "reflectDamage"s, _constUndefined };
    static inline sSetting oneHandedModString{ "showStatsName"s, "oneHandedMod"s, _constUndefined };
    static inline sSetting twoHandedModString{ "showStatsName"s, "twoHandedMod"s, _constUndefined };
    static inline sSetting archeryModString{ "showStatsName"s, "archeryMod"s, _constUndefined };
    static inline sSetting blockModString{ "showStatsName"s, "blockMod"s, _constUndefined };
    static inline sSetting smithingModString{ "showStatsName"s, "smithingMod"s, _constUndefined };
    static inline sSetting heavyArmorModString{ "showStatsName"s, "heavyArmorMod"s, _constUndefined };
    static inline sSetting lightArmorModString{ "showStatsName"s, "lightArmorMod"s, _constUndefined };
    static inline sSetting pickpocketModString{ "showStatsName"s, "pickpocketMod"s, _constUndefined };
    static inline sSetting lockpickingModString{ "showStatsName"s, "lockpickingMod"s, _constUndefined };
    static inline sSetting sneakModString{ "showStatsName"s, "sneakMod"s, _constUndefined };
    static inline sSetting alchemyModString{ "showStatsName"s, "alchemyMod"s, _constUndefined };
    static inline sSetting speechModString{ "showStatsName"s, "speechMod"s, _constUndefined };
    static inline sSetting enchantingModString{ "showStatsName"s, "enchantingMod"s, _constUndefined };
    static inline sSetting alterationModString{ "showStatsName"s, "alterationMod"s, _constUndefined };
    static inline sSetting conjurationModString{ "showStatsName"s, "conjurationMod"s, _constUndefined };
    static inline sSetting destructionModString{ "showStatsName"s, "destructionMod"s, _constUndefined };
    static inline sSetting illusionModString{ "showStatsName"s, "illusionMod"s, _constUndefined };
    static inline sSetting restorationModString{ "showStatsName"s, "restorationMod"s, _constUndefined };
    static inline sSetting damageArrowString{ "showStatsName"s, "damageArrow"s, _constUndefined };
    static inline sSetting damageLeftString{ "showStatsName"s, "damageLeft"s, _constUndefined };
    static inline sSetting leftWeaponSpeedMultString{ "showStatsName"s, "leftWeaponSpeedMult"s, _constUndefined };
    static inline sSetting rightItemChargeString{ "showStatsName"s, "rightItemCharge"s, _constUndefined };
    static inline sSetting leftItemChargStringe{ "showStatsName"s, "leftItemCharge"s, _constUndefined };
    static inline sSetting armorPerksString{ "showStatsName"s, "armorPerks"s, _constUndefined };
    static inline sSetting massString{ "showStatsName"s, "mass"s, _constUndefined };
    static inline sSetting bowStaggerBonusString{ "showStatsName"s, "bowStaggerBonus"s, _constUndefined };
    static inline sSetting bypassVendorKeywordCheckString{ "showStatsName"s,
        "bypassVendorKeywordCheck"s,
        _constUndefined };
    static inline sSetting bypassVendorStolenCheckString{ "showStatsName"s,
        "bypassVendorStolenCheck"s,
        _constUndefined };

    static inline sSetting nameStringEnding{ "showStatsEnding"s, "name"s, _constUndefined };
    static inline sSetting raceStringEnding{ "showStatsEnding"s, "race"s, _constUndefined };
    static inline sSetting levelStringEnding{ "showStatsEnding"s, "level"s, _constUndefined };
    static inline sSetting perkCountStringEnding{ "showStatsEnding"s, "perkCount"s, _constUndefined };
    static inline sSetting heightStringEnding{ "showStatsEnding"s, "height"s, _constUndefined };
    static inline sSetting equipedWeightStringEnding{ "showStatsEnding"s, "equipedWeight"s, _constUndefined };
    static inline sSetting weightStringEnding{ "showStatsEnding"s, "weight"s, _constUndefined };
    static inline sSetting armorStringEnding{ "showStatsEnding"s, "armor"s, _constUndefined };
    static inline sSetting damageStringEnding{ "showStatsEnding"s, "damage"s, _constUndefined };
    static inline sSetting skillTrainingsThisLevelStringEnding{ "showStatsEnding"s,
        "skillTrainingsThisLevel"s,
        _constUndefined };
    static inline sSetting healthStringEnding{ "showStatsEnding"s, "health"s, _constUndefined };
    static inline sSetting healthRateStringEnding{ "showStatsEnding"s, "healthRatePer"s, _constUndefined };
    static inline sSetting magickaStringEnding{ "showStatsEnding"s, "magicka"s, _constUndefined };
    static inline sSetting magickaRateStringEnding{ "showStatsEnding"s, "magickaRatePer"s, _constUndefined };
    static inline sSetting staminaStringEnding{ "showStatsEnding"s, "stamina"s, _constUndefined };
    static inline sSetting staminaRateStringEnding{ "showStatsEnding"s, "staminaRatePer"s, _constUndefined };
    static inline sSetting resistDamageStringEnding{ "showStatsEnding"s, "resistDamage"s, _constUndefined };
    static inline sSetting resistDiseaseStringEnding{ "showStatsEnding"s, "resistDisease"s, _constUndefined };
    static inline sSetting resistPoisonStringEnding{ "showStatsEnding"s, "resistPoison"s, _constUndefined };
    static inline sSetting resistFireStringEnding{ "showStatsEnding"s, "resistFire"s, _constUndefined };
    static inline sSetting resistShockStringEnding{ "showStatsEnding"s, "resistShock"s, _constUndefined };
    static inline sSetting resistFrostStringEnding{ "showStatsEnding"s, "resistFrost"s, _constUndefined };
    static inline sSetting resistMagicStringEnding{ "showStatsEnding"s, "resistMagic"s, _constUndefined };
    static inline sSetting oneHandedStringEnding{ "showStatsEnding"s, "oneHanded"s, _constUndefined };
    static inline sSetting twoHandedStringEnding{ "showStatsEnding"s, "twoHanded"s, _constUndefined };
    static inline sSetting archeryStringEnding{ "showStatsEnding"s, "archery"s, _constUndefined };
    static inline sSetting blockStringEnding{ "showStatsEnding"s, "block"s, _constUndefined };
    static inline sSetting smithingStringEnding{ "showStatsEnding"s, "smithing"s, _constUndefined };
    static inline sSetting heavyArmorStringEnding{ "showStatsEnding"s, "heavyArmor"s, _constUndefined };
    static inline sSetting lightArmorStringEnding{ "showStatsEnding"s, "lightArmor"s, _constUndefined };
    static inline sSetting pickpocketStringEnding{ "showStatsEnding"s, "pickpocket"s, _constUndefined };
    static inline sSetting lockpickingStringEnding{ "showStatsEnding"s, "lockpicking"s, _constUndefined };
    static inline sSetting sneakStringEnding{ "showStatsEnding"s, "sneak"s, _constUndefined };
    static inline sSetting alchemyStringEnding{ "showStatsEnding"s, "alchemy"s, _constUndefined };
    static inline sSetting speechStringEnding{ "showStatsEnding"s, "speech"s, _constUndefined };
    static inline sSetting enchantingStringEnding{ "showStatsEnding"s, "enchanting"s, _constUndefined };
    static inline sSetting alterationStringEnding{ "showStatsEnding"s, "alteration"s, _constUndefined };
    static inline sSetting conjurationStringEnding{ "showStatsEnding"s, "conjuration"s, _constUndefined };
    static inline sSetting destructionStringEnding{ "showStatsEnding"s, "destruction"s, _constUndefined };
    static inline sSetting illusionStringEnding{ "showStatsEnding"s, "illusion"s, _constUndefined };
    static inline sSetting restorationStringEnding{ "showStatsEnding"s, "restoration"s, _constUndefined };
    static inline sSetting oneHandedPowerModStringEnding{ "showStatsEnding"s, "oneHandedPowerMod"s, _constUndefined };
    static inline sSetting twoHandedPowerModStringEnding{ "showStatsEnding"s, "twoHandedPowerMod"s, _constUndefined };
    static inline sSetting archeryPowerModStringEnding{ "showStatsEnding"s, "archeryPowerMod"s, _constUndefined };
    static inline sSetting blockPowerModStringEnding{ "showStatsEnding"s, "blockPowerMod"s, _constUndefined };
    static inline sSetting smithingPowerModStringEnding{ "showStatsEnding"s, "smithingPowerMod"s, _constUndefined };
    static inline sSetting heavyArmorPowerModStringEnding{ "showStatsEnding"s, "heavyArmorPowerMod"s, _constUndefined };
    static inline sSetting lightArmorPowerModStringEnding{ "showStatsEnding"s, "lightArmorPowerMod"s, _constUndefined };
    static inline sSetting pickpocketPowerModStringEnding{ "showStatsEnding"s, "pickpocketPowerMod"s, _constUndefined };
    static inline sSetting lockpickingPowerModStringEnding{ "showStatsEnding"s,
        "lockpickingPowerMod"s,
        _constUndefined };
    static inline sSetting sneakPowerModStringEnding{ "showStatsEnding"s, "sneakPowerMod"s, _constUndefined };
    static inline sSetting alchemyPowerModStringEnding{ "showStatsEnding"s, "alchemyPowerMod"s, _constUndefined };
    static inline sSetting speechPowerModStringEnding{ "showStatsEnding"s, "speechPowerMod"s, _constUndefined };
    static inline sSetting enchantingPowerModStringEnding{ "showStatsEnding"s, "enchantingPowerMod"s, _constUndefined };
    static inline sSetting alterationPowerModStringEnding{ "showStatsEnding"s, "alterationPowerMod"s, _constUndefined };
    static inline sSetting conjurationPowerModStringEnding{ "showStatsEnding"s,
        "conjurationPowerMod"s,
        _constUndefined };
    static inline sSetting destructionPowerModStringEnding{ "showStatsEnding"s,
        "destructionPowerMod"s,
        _constUndefined };
    static inline sSetting illusionPowerModStringEnding{ "showStatsEnding"s, "illusionPowerMod"s, _constUndefined };
    static inline sSetting restorationPowerModStringEnding{ "showStatsEnding"s,
        "restorationPowerMod"s,
        _constUndefined };
    static inline sSetting speedMultStringEnding{ "showStatsEnding"s, "speedMult"s, _constUndefined };
    static inline sSetting inventoryWeightStringEnding{ "showStatsEnding"s, "inventoryWeight"s, _constUndefined };
    static inline sSetting carryWeightStringEnding{ "showStatsEnding"s, "carryWeight"s, _constUndefined };
    static inline sSetting criticalChanceStringEnding{ "showStatsEnding"s, "criticalChance"s, _constUndefined };
    static inline sSetting meleeDamageStringEnding{ "showStatsEnding"s, "meleeDamage"s, _constUndefined };
    static inline sSetting unarmedDamageStringEnding{ "showStatsEnding"s, "unarmedDamage"s, _constUndefined };
    static inline sSetting absorbChanceStringEnding{ "showStatsEnding"s, "absorbChance"s, _constUndefined };
    static inline sSetting weaponSpeedMultStringEnding{ "showStatsEnding"s, "weaponSpeedMult"s, _constUndefined };
    static inline sSetting bowSpeedBonusStringEnding{ "showStatsEnding"s, "bowSpeedBonus"s, _constUndefined };
    static inline sSetting shoutRecoveryMultStringEnding{ "showStatsEnding"s, "shoutRecoveryMult"s, _constUndefined };
    static inline sSetting movementNoiseMultStringEnding{ "showStatsEnding"s, "movementNoiseMult"s, _constUndefined };
    static inline sSetting dragonSoulsStringEnding{ "showStatsEnding"s, "dragonSouls"s, _constUndefined };
    static inline sSetting combatHealthRegenMultiplyStringEnding{ "showStatsEnding"s,
        "combatHealthRegenMultiply"s,
        _constUndefined };
    static inline sSetting attackDamageMultStringEnding{ "showStatsEnding"s, "attackDamageMult"s, _constUndefined };
    static inline sSetting beastStringEnding{ "showStatsEnding"s, "beast"s, _constUndefined };
    static inline sSetting xpStringEnding{ "showStatsEnding"s, "xp"s, _constUndefined };
    static inline sSetting reflectDamageStringEnding{ "showStatsEnding"s, "reflectDamage"s, _constUndefined };
    static inline sSetting oneHandedModStringEnding{ "showStatsEnding"s, "oneHandedMod"s, _constUndefined };
    static inline sSetting twoHandedModStringEnding{ "showStatsEnding"s, "twoHandedMod"s, _constUndefined };
    static inline sSetting archeryModStringEnding{ "showStatsEnding"s, "archeryMod"s, _constUndefined };
    static inline sSetting blockModStringEnding{ "showStatsEnding"s, "blockMod"s, _constUndefined };
    static inline sSetting smithingModStringEnding{ "showStatsEnding"s, "smithingMod"s, _constUndefined };
    static inline sSetting heavyArmorModStringEnding{ "showStatsEnding"s, "heavyArmorMod"s, _constUndefined };
    static inline sSetting lightArmorModStringEnding{ "showStatsEnding"s, "lightArmorMod"s, _constUndefined };
    static inline sSetting pickpocketModStringEnding{ "showStatsEnding"s, "pickpocketMod"s, _constUndefined };
    static inline sSetting lockpickingModStringEnding{ "showStatsEnding"s, "lockpickingMod"s, _constUndefined };
    static inline sSetting sneakModStringEnding{ "showStatsEnding"s, "sneakMod"s, _constUndefined };
    static inline sSetting alchemyModStringEnding{ "showStatsEnding"s, "alchemyMod"s, _constUndefined };
    static inline sSetting speechModStringEnding{ "showStatsEnding"s, "speechMod"s, _constUndefined };
    static inline sSetting enchantingModStringEnding{ "showStatsEnding"s, "enchantingMod"s, _constUndefined };
    static inline sSetting alterationModStringEnding{ "showStatsEnding"s, "alterationMod"s, _constUndefined };
    static inline sSetting conjurationModStringEnding{ "showStatsEnding"s, "conjurationMod"s, _constUndefined };
    static inline sSetting destructionModStringEnding{ "showStatsEnding"s, "destructionMod"s, _constUndefined };
    static inline sSetting illusionModStringEnding{ "showStatsEnding"s, "illusionMod"s, _constUndefined };
    static inline sSetting restorationModStringEnding{ "showStatsEnding"s, "restorationMod"s, _constUndefined };
    static inline sSetting damageArrowStringEnding{ "showStatsEnding"s, "damageArrow"s, _constUndefined };
    static inline sSetting damageLeftStringEnding{ "showStatsEnding"s, "damageLeft"s, _constUndefined };
    static inline sSetting leftWeaponSpeedMultStringEnding{ "showStatsEnding"s,
        "leftWeaponSpeedMult"s,
        _constUndefined };
    static inline sSetting rightItemChargeStringEnding{ "showStatsEnding"s, "rightItemCharge"s, _constUndefined };
    static inline sSetting leftItemChargStringeEnding{ "showStatsEnding"s, "leftItemCharge"s, _constUndefined };
    static inline sSetting armorPerksStringEnding{ "showStatsEnding"s, "armorPerks"s, _constUndefined };
    static inline sSetting massStringEnding{ "showStatsEnding"s, "mass"s, _constUndefined };
    static inline sSetting bowStaggerBonusStringEnding{ "showStatsEnding"s, "bowStaggerBonus"s, _constUndefined };
    static inline sSetting bypassVendorKeywordCheckStringEnding{ "showStatsEnding"s,
        "bypassVendorKeywordCheck"s,
        _constUndefined };
    static inline sSetting bypassVendorStolenCheckStringEnding{ "showStatsEnding"s,
        "bypassVendorStolenCheck"s,
        _constUndefined };
    //factions do not need a ending

    static inline iSetting heightMenu{ "showStatsMenu"s, "height"s, 0 };
    static inline iSetting equipedWeightMenu{ "showStatsMenu"s, "equipedWeight"s, 0 };
    static inline iSetting weightMenu{ "showStatsMenu"s, "weight"s, 0 };
    static inline iSetting armorMenu{ "showStatsMenu"s, "armor"s, 0 };
    static inline iSetting damageMenu{ "showStatsMenu"s, "damage"s, 0 };
    static inline iSetting skillTrainingsThisLevelMenu{ "showStatsMenu"s, "skillTrainingsThisLevel"s, 0 };
    static inline iSetting healthMenu{ "showStatsMenu"s, "health"s, 0 };
    static inline iSetting healthRateMenu{ "showStatsMenu"s, "healthRatePer"s, 0 };
    static inline iSetting magickaMenu{ "showStatsMenu"s, "magicka"s, 0 };
    static inline iSetting magickaRateMenu{ "showStatsMenu"s, "magickaRatePer"s, 0 };
    static inline iSetting staminaMenu{ "showStatsMenu"s, "stamina"s, 0 };
    static inline iSetting staminaRateMenu{ "showStatsMenu"s, "staminaRatePer"s, 0 };
    static inline iSetting resistDamageMenu{ "showStatsMenu"s, "resistDamage"s, 0 };
    static inline iSetting resistDiseaseMenu{ "showStatsMenu"s, "resistDisease"s, 0 };
    static inline iSetting resistPoisonMenu{ "showStatsMenu"s, "resistPoison"s, 0 };
    static inline iSetting resistFireMenu{ "showStatsMenu"s, "resistFire"s, 0 };
    static inline iSetting resistShockMenu{ "showStatsMenu"s, "resistShock"s, 0 };
    static inline iSetting resistFrostMenu{ "showStatsMenu"s, "resistFrost"s, 0 };
    static inline iSetting resistMagicMenu{ "showStatsMenu"s, "resistMagic"s, 0 };
    static inline iSetting oneHandedMenu{ "showStatsMenu"s, "oneHanded"s, 0 };
    static inline iSetting twoHandedMenu{ "showStatsMenu"s, "twoHanded"s, 0 };
    static inline iSetting archeryMenu{ "showStatsMenu"s, "archery"s, 0 };
    static inline iSetting blockMenu{ "showStatsMenu"s, "block"s, 0 };
    static inline iSetting smithingMenu{ "showStatsMenu"s, "smithing"s, 0 };
    static inline iSetting heavyArmorMenu{ "showStatsMenu"s, "heavyArmor"s, 0 };
    static inline iSetting lightArmorMenu{ "showStatsMenu"s, "lightArmor"s, 0 };
    static inline iSetting pickpocketMenu{ "showStatsMenu"s, "pickpocket"s, 0 };
    static inline iSetting lockpickingMenu{ "showStatsMenu"s, "lockpicking"s, 0 };
    static inline iSetting sneakMenu{ "showStatsMenu"s, "sneak"s, 0 };
    static inline iSetting alchemyMenu{ "showStatsMenu"s, "alchemy"s, 0 };
    static inline iSetting speechMenu{ "showStatsMenu"s, "speech"s, 0 };
    static inline iSetting enchantingMenu{ "showStatsMenu"s, "enchanting"s, 0 };
    static inline iSetting alterationMenu{ "showStatsMenu"s, "alteration"s, 0 };
    static inline iSetting conjurationMenu{ "showStatsMenu"s, "conjuration"s, 0 };
    static inline iSetting destructionMenu{ "showStatsMenu"s, "destruction"s, 0 };
    static inline iSetting illusionMenu{ "showStatsMenu"s, "illusion"s, 0 };
    static inline iSetting restorationMenu{ "showStatsMenu"s, "restoration"s, 0 };
    static inline iSetting oneHandedPowerModMenu{ "showStatsMenu"s, "oneHandedPowerMod"s, 0 };
    static inline iSetting twoHandedPowerModMenu{ "showStatsMenu"s, "twoHandedPowerMod"s, 0 };
    static inline iSetting archeryPowerModMenu{ "showStatsMenu"s, "archeryPowerMod"s, 0 };
    static inline iSetting blockPowerModMenu{ "showStatsMenu"s, "blockPowerMod"s, 0 };
    static inline iSetting smithingPowerModMenu{ "showStatsMenu"s, "smithingPowerMod"s, 0 };
    static inline iSetting heavyArmorPowerModMenu{ "showStatsMenu"s, "heavyArmorPowerMod"s, 0 };
    static inline iSetting lightArmorPowerModMenu{ "showStatsMenu"s, "lightArmorPowerMod"s, 0 };
    static inline iSetting pickpocketPowerModMenu{ "showStatsMenu"s, "pickpocketPowerMod"s, 0 };
    static inline iSetting lockpickingPowerModMenu{ "showStatsMenu"s, "lockpickingPowerMod"s, 0 };
    static inline iSetting sneakPowerModMenu{ "showStatsMenu"s, "sneakPowerMod"s, 0 };
    static inline iSetting alchemyPowerModMenu{ "showStatsMenu"s, "alchemyPowerMod"s, 0 };
    static inline iSetting speechPowerModMenu{ "showStatsMenu"s, "speechPowerMod"s, 0 };
    static inline iSetting enchantingPowerModMenu{ "showStatsMenu"s, "enchantingPowerMod"s, 0 };
    static inline iSetting alterationPowerModMenu{ "showStatsMenu"s, "alterationPowerMod"s, 0 };
    static inline iSetting conjurationPowerModMenu{ "showStatsMenu"s, "conjurationPowerMod"s, 0 };
    static inline iSetting destructionPowerModMenu{ "showStatsMenu"s, "destructionPowerMod"s, 0 };
    static inline iSetting illusionPowerModMenu{ "showStatsMenu"s, "illusionPowerMod"s, 0 };
    static inline iSetting restorationPowerModMenu{ "showStatsMenu"s, "restorationPowerMod"s, 0 };
    static inline iSetting speedMultMenu{ "showStatsMenu"s, "speedMult"s, 0 };
    static inline iSetting inventoryWeightMenu{ "showStatsMenu"s, "inventoryWeight"s, 0 };
    static inline iSetting carryWeightMenu{ "showStatsMenu"s, "carryWeight"s, 0 };
    static inline iSetting criticalChanceMenu{ "showStatsMenu"s, "criticalChance"s, 0 };
    static inline iSetting meleeDamageMenu{ "showStatsMenu"s, "meleeDamage"s, 0 };
    static inline iSetting unarmedDamageMenu{ "showStatsMenu"s, "unarmedDamage"s, 0 };
    static inline iSetting absorbChanceMenu{ "showStatsMenu"s, "absorbChance"s, 0 };
    static inline iSetting weaponSpeedMultMenu{ "showStatsMenu"s, "weaponSpeedMult"s, 0 };
    static inline iSetting bowSpeedBonusMenu{ "showStatsMenu"s, "bowSpeedBonus"s, 0 };
    static inline iSetting shoutRecoveryMultMenu{ "showStatsMenu"s, "shoutRecoveryMult"s, 0 };
    static inline iSetting movementNoiseMultMenu{ "showStatsMenu"s, "movementNoiseMult"s, 0 };
    static inline iSetting dragonSoulsMenu{ "showStatsMenu"s, "dragonSouls"s, 0 };
    static inline iSetting combatHealthRegenMultiplyMenu{ "showStatsMenu"s, "combatHealthRegenMultiply"s, 0 };
    static inline iSetting attackDamageMultMenu{ "showStatsMenu"s, "attackDamageMult"s, 0 };
    static inline iSetting reflectDamageMenu{ "showStatsMenu"s, "reflectDamage"s, 0 };
    static inline iSetting oneHandedModMenu{ "showStatsMenu"s, "oneHandedMod"s, 0 };
    static inline iSetting twoHandedModMenu{ "showStatsMenu"s, "twoHandedMod"s, 0 };
    static inline iSetting archeryModMenu{ "showStatsMenu"s, "archeryMod"s, 0 };
    static inline iSetting blockModMenu{ "showStatsMenu"s, "blockMod"s, 0 };
    static inline iSetting smithingModMenu{ "showStatsMenu"s, "smithingMod"s, 0 };
    static inline iSetting heavyArmorModMenu{ "showStatsMenu"s, "heavyArmorMod"s, 0 };
    static inline iSetting lightArmorModMenu{ "showStatsMenu"s, "lightArmorMod"s, 0 };
    static inline iSetting pickpocketModMenu{ "showStatsMenu"s, "pickpocketMod"s, 0 };
    static inline iSetting lockpickingModMenu{ "showStatsMenu"s, "lockpickingMod"s, 0 };
    static inline iSetting sneakModMenu{ "showStatsMenu"s, "sneakMod"s, 0 };
    static inline iSetting alchemyModMenu{ "showStatsMenu"s, "alchemyMod"s, 0 };
    static inline iSetting speechModMenu{ "showStatsMenu"s, "speechMod"s, 0 };
    static inline iSetting enchantingModMenu{ "showStatsMenu"s, "enchantingMod"s, 0 };
    static inline iSetting alterationModMenu{ "showStatsMenu"s, "alterationMod"s, 0 };
    static inline iSetting conjurationModMenu{ "showStatsMenu"s, "conjurationMod"s, 0 };
    static inline iSetting destructionModMenu{ "showStatsMenu"s, "destructionMod"s, 0 };
    static inline iSetting illusionModMenu{ "showStatsMenu"s, "illusionMod"s, 0 };
    static inline iSetting restorationModMenu{ "showStatsMenu"s, "restorationMod"s, 0 };
    static inline iSetting damageArrowMenu{ "showStatsMenu"s, "damageArrow"s, 0 };
    static inline iSetting damageLeftMenu{ "showStatsMenu"s, "damageLeft"s, 0 };
    static inline iSetting leftWeaponSpeedMultMenu{ "showStatsMenu"s, "leftWeaponSpeedMult"s, 0 };
    static inline iSetting rightItemChargeMenu{ "showStatsMenu"s, "rightItemCharge"s, 0 };
    static inline iSetting leftItemChargeMenu{ "showStatsMenu"s, "leftItemCharge"s, 0 };
    static inline iSetting armorPerksMenu{ "showStatsMenu"s, "armorPerks"s, 0 };
    static inline iSetting massMenu{ "showStatsMenu"s, "mass"s, 0 };
    static inline iSetting bowStaggerBonusMenu{ "showStatsMenu"s, "bowStaggerBonus"s, 0 };
    static inline iSetting bypassVendorKeywordCheckMenu{ "showStatsMenu"s, "bypassVendorKeywordCheck"s, 0 };
    static inline iSetting bypassVendorStolenCheckMenu{ "showStatsMenu"s, "bypassVendorStolenCheck"s, 0 };

    static inline iSetting weaponSpeedMultMult{ "showStatsMultiplier"s, "weaponSpeedMult"s, 1 };
    static inline iSetting shoutRecoveryMultMult{ "showStatsMultiplier"s, "shoutRecoveryMult"s, 1 };
    static inline iSetting movementNoiseMultMult{ "showStatsMultiplier"s, "movementNoiseMult"s, 1 };
    static inline iSetting combatHealthRegenMultiplyMult{ "showStatsMultiplier"s, "combatHealthRegenMultiply"s, 1 };
    static inline iSetting leftWeaponSpeedMultMult{ "showStatsMultiplier"s, "leftWeaponSpeedMult"s, 1 };
    static inline iSetting armorPerksMult{ "showStatsMultiplier"s, "armorPerks"s, 1 };

    static inline sSetting vampireString{ "showBeastName"s, "vampire"s, _constUndefined };
    static inline sSetting werewolfString{ "showBeastName"s, "werewolf"s, _constUndefined };

    static inline sSetting showFactionsTitleTitle{ "showFactionsTitle"s, "title"s, _constUndefined };
    static inline sSetting showFactionsTitleFaction{ "showFactionsTitle"s, "faction"s, _constUndefined };
    static inline sSetting showFactionsTitleThane{ "showFactionsTitle"s, "thane"s, _constUndefined };
    static inline sSetting showFactionsTitleChampion{ "showFactionsTitle"s, "champion"s, _constUndefined };

    static inline bSetting showFactions{ "showFactions"s, "showFactions"s, true };
    static inline bSetting showThanes{ "showFactions"s, "showThane"s, true };
    static inline bSetting showChampion{ "showFactions"s, "showChampion"s, true };

    static inline sSetting companionsString{ "showFactionsFactionNames"s, "companions"s, _constUndefined };
    static inline sSetting darkbrotherHoodString{ "showFactionsFactionNames"s, "darkbrotherHood"s, _constUndefined };
    static inline sSetting collegeOfWinterholdString{ "showFactionsFactionNames"s,
        "collegeOfWinterhold"s,
        _constUndefined };
    static inline sSetting orcFriendString{ "showFactionsFactionNames"s, "orcFriend"s, _constUndefined };
    static inline sSetting thiefsGuildString{ "showFactionsFactionNames"s, "thiefsGuild"s, _constUndefined };
    static inline sSetting imperialLegionString{ "showFactionsFactionNames"s, "imperialLegion"s, _constUndefined };
    static inline sSetting stormcloaksString{ "showFactionsFactionNames"s, "stormcloaks"s, _constUndefined };
    static inline sSetting greybeardString{ "showFactionsFactionNames"s, "greybeard"s, _constUndefined };
    static inline sSetting bardString{ "showFactionsFactionNames"s, "bard"s, _constUndefined };
    static inline sSetting volkiharVampireClanString{ "showFactionsFactionNames"s,
        "volkiharVampireClan"s,
        _constUndefined };
    static inline sSetting dawnguardString{ "showFactionsFactionNames"s, "dawnguard"s, _constUndefined };
    static inline sSetting houseTelvanniString{ "showFactionsFactionNames"s, "houseTelvanni"s, _constUndefined };

    static inline iSetting factionMenu{ "showFactionsFactionMenu"s, "faction"s, 0 };

    static inline sSetting bardRank{ "showFactionsFactionRank"s, "bard"s, _constUndefined };
    static inline sSetting assassinRank{ "showFactionsFactionRank"s, "assassin"s, _constUndefined };
    static inline sSetting listenerRank{ "showFactionsFactionRank"s, "listener"s, _constUndefined };
    static inline sSetting auxiliaryRank{ "showFactionsFactionRank"s, "auxiliary"s, _constUndefined };
    static inline sSetting quaestorRank{ "showFactionsFactionRank"s, "quaestor"s, _constUndefined };
    static inline sSetting praefectRank{ "showFactionsFactionRank"s, "praefect"s, _constUndefined };
    static inline sSetting tribuneRank{ "showFactionsFactionRank"s, "tribune"s, _constUndefined };
    static inline sSetting legateRank{ "showFactionsFactionRank"s, "legate"s, _constUndefined };
    static inline sSetting unbloodedRank{ "showFactionsFactionRank"s, "unblooded"s, _constUndefined };
    static inline sSetting iceVeinsRank{ "showFactionsFactionRank"s, "iceVeins"s, _constUndefined };
    static inline sSetting boneBreakerRank{ "showFactionsFactionRank"s, "boneBreaker"s, _constUndefined };
    static inline sSetting snowHammerRank{ "showFactionsFactionRank"s, "snowHammer"s, _constUndefined };
    static inline sSetting stormbladeRank{ "showFactionsFactionRank"s, "stormblade"s, _constUndefined };
    static inline sSetting vampireLordRank{ "showFactionsFactionRank"s, "vampireLord"s, _constUndefined };
    static inline sSetting vampireHunterRank{ "showFactionsFactionRank"s, "vampireHunter"s, _constUndefined };
    static inline sSetting honoraryMemberRank{ "showFactionsFactionRank"s, "honoraryMember"s, _constUndefined };
    static inline sSetting ysmirRank{ "showFactionsFactionRank"s, "ysmir"s, _constUndefined };

    static inline iSetting thaneMenu{ "showFactionsThaneMenu"s, "thane"s, 0 };

    static inline sSetting thaneOfEastmarchName{ "showFactionsThaneName"s, "thaneOfEastmarch"s, _constUndefined };
    static inline sSetting thaneOfFalkreathName{ "showFactionsThaneName"s, "thaneOfFalkreath"s, _constUndefined };
    static inline sSetting thaneOfHaafingarName{ "showFactionsThaneName"s, "thaneOfHaafingar"s, _constUndefined };
    static inline sSetting thaneOfHjaalmarchName{ "showFactionsThaneName"s, "thaneOfHjaalmarch"s, _constUndefined };
    static inline sSetting thaneOfThePaleName{ "showFactionsThaneName"s, "thaneOfThePale"s, _constUndefined };
    static inline sSetting thaneOfTheReachName{ "showFactionsThaneName"s, "thaneOfTheReach"s, _constUndefined };
    static inline sSetting thaneOfTheRiftName{ "showFactionsThaneName"s, "thaneOfTheRift"s, _constUndefined };
    static inline sSetting thaneOfWhiterunName{ "showFactionsThaneName"s, "thaneOfWhiterun"s, _constUndefined };
    static inline sSetting thaneOfWinterholdName{ "showFactionsThaneName"s, "thaneOfWinterhold"s, _constUndefined };

    static inline iSetting championMenu{ "showFactionsChampionMenu"s, "champion"s, 0 };

    static inline sSetting azuraName{ "showFactionsChampionName"s, "azura"s, _constUndefined };
    static inline sSetting boethiahName{ "showFactionsChampionName"s, "boethiah"s, _constUndefined };
    static inline sSetting clavicusVileName{ "showFactionsChampionName"s, "clavicusVile"s, _constUndefined };
    static inline sSetting hermaeusMoraName{ "showFactionsChampionName"s, "hermaeusMora"s, _constUndefined };
    static inline sSetting hircineName{ "showFactionsChampionName"s, "hircine"s, _constUndefined };
    static inline sSetting malacathName{ "showFactionsChampionName"s, "malacath"s, _constUndefined };
    static inline sSetting mehrunesDagonName{ "showFactionsChampionName"s, "mehrunesDagon"s, _constUndefined };
    static inline sSetting mephalaName{ "showFactionsChampionName"s, "mephala"s, _constUndefined };
    static inline sSetting meridiaName{ "showFactionsChampionName"s, "meridia"s, _constUndefined };
    static inline sSetting molagBalName{ "showFactionsChampionName"s, "molagBal"s, _constUndefined };
    static inline sSetting namiraName{ "showFactionsChampionName"s, "namira"s, _constUndefined };
    static inline sSetting nocturnalName{ "showFactionsChampionName"s, "nocturnal"s, _constUndefined };
    static inline sSetting peryiteName{ "showFactionsChampionName"s, "peryite"s, _constUndefined };
    static inline sSetting sanguineName{ "showFactionsChampionName"s, "sanguine"s, _constUndefined };
    static inline sSetting sheogorathName{ "showFactionsChampionName"s, "sheogorath"s, _constUndefined };
    static inline sSetting vaerminaName{ "showFactionsChampionName"s, "vaermina"s, _constUndefined };

    static inline sSetting showStatsInventoryTitleTitle{ "showStatsInventoryTitle"s, "title"s, _constUndefined };
    static inline sSetting showStatsInventoryTitleArmor{ "showStatsInventoryTitle"s, "armor"s, _constUndefined };
    static inline sSetting showStatsInventoryTitleWeapon{ "showStatsInventoryTitle"s, "weapon"s, _constUndefined };
    static inline sSetting showStatsInventoryTitleEffect{ "showStatsInventoryTitle"s, "effect"s, _constUndefined };
};
