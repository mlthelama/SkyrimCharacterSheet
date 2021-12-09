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
    static inline iSetting openFactionMenuButton{ "General"s, "openNextMenuButton"s, 0 };
    static inline bSetting pauseGame{ "General"s, "pauseGame"s, true };
    static inline bSetting showInventoryStats{ "General"s, "showInventoryStats"s, true };
    static inline bSetting showInventoryStatsAutoOpen{ "General"s, "showInventoryStatsAutoOpen"s, true };
    static inline iSetting showInventoryButton{ "General"s, "showInventoryButton"s, 0 };
    static inline bSetting displayPermanentAV{ "General"s, "displayPermanentAV"s, true };

    static inline bSetting skyrimUnbound{ "Mods"s, "skyrimUnbound"s, true };

    static inline bSetting showResistanceCap{ "specialHandling"s, "showResistanceCap"s, true };

    //stat titles
    static inline sSetting showStatsTitleTitle{ "showStatsTitle"s, "title"s, _constUndefined };
    static inline sSetting showStatsTitlePlayer{ "showStatsTitle"s, "player"s, _constUndefined };
    static inline sSetting showStatsTitleAttack{ "showStatsTitle"s, "attack"s, _constUndefined };
    static inline sSetting showStatsTitleDefence{ "showStatsTitle"s, "defence"s, _constUndefined };
    static inline sSetting showStatsTitleMagic{ "showStatsTitle"s, "magic"s, _constUndefined };
    static inline sSetting showStatsTitleThief{ "showStatsTitle"s, "thief"s, _constUndefined };
    static inline sSetting showStatsTitleWarrior{ "showStatsTitle"s, "warrior"s, _constUndefined };

    static inline bSetting showStatsdisplayZero{ "showStatsSpecial"s, "displayZero"s, true };

    //naming
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
    static inline sSetting weaponReachString{ "showStatsName"s, "weaponReach"s, _constUndefined };
    static inline sSetting weaponReachLeftString{ "showStatsName"s, "weaponReachLeft"s, _constUndefined };
    static inline sSetting weaponBaseDamageString{ "showStatsName"s, "weaponBaseDamage"s, _constUndefined };
    static inline sSetting weaponBaseDamageLeftString{ "showStatsName"s, "weaponBaseDamageLeft"s, _constUndefined };
    static inline sSetting weaponStaggerString{ "showStatsName"s, "weaponStagger"s, _constUndefined };
    static inline sSetting weaponStaggerLeftString{ "showStatsName"s, "weaponStaggerLeft"s, _constUndefined };
    static inline sSetting weaponCritDamageRatingString{ "showStatsName"s, "weaponCritDamageRating"s, _constUndefined };
    static inline sSetting weaponCritDamageRatingLeftString{ "showStatsName"s,
        "weaponCritDamageRatingLeft"s,
        _constUndefined };
    static inline sSetting fallDamageModString{ "showStatsName"s, "fallDamageMod"s, _constUndefined };

    //stat endings
    static inline sSetting heightStringEnding{ "showStatsEnding"s, "height"s, _constUndefined };
    static inline sSetting equipedWeightStringEnding{ "showStatsEnding"s, "equipedWeight"s, _constUndefined };
    static inline sSetting weightStringEnding{ "showStatsEnding"s, "weight"s, _constUndefined };
    static inline sSetting healthRateStringEnding{ "showStatsEnding"s, "healthRatePer"s, _constUndefined };
    static inline sSetting magickaRateStringEnding{ "showStatsEnding"s, "magickaRatePer"s, _constUndefined };
    static inline sSetting staminaRateStringEnding{ "showStatsEnding"s, "staminaRatePer"s, _constUndefined };
    static inline sSetting resistDamageStringEnding{ "showStatsEnding"s, "resistDamage"s, _constUndefined };
    static inline sSetting resistDiseaseStringEnding{ "showStatsEnding"s, "resistDisease"s, _constUndefined };
    static inline sSetting resistPoisonStringEnding{ "showStatsEnding"s, "resistPoison"s, _constUndefined };
    static inline sSetting resistFireStringEnding{ "showStatsEnding"s, "resistFire"s, _constUndefined };
    static inline sSetting resistShockStringEnding{ "showStatsEnding"s, "resistShock"s, _constUndefined };
    static inline sSetting resistFrostStringEnding{ "showStatsEnding"s, "resistFrost"s, _constUndefined };
    static inline sSetting resistMagicStringEnding{ "showStatsEnding"s, "resistMagic"s, _constUndefined };
    static inline sSetting speedMultStringEnding{ "showStatsEnding"s, "speedMult"s, _constUndefined };
    static inline sSetting inventoryWeightStringEnding{ "showStatsEnding"s, "inventoryWeight"s, _constUndefined };
    static inline sSetting carryWeightStringEnding{ "showStatsEnding"s, "carryWeight"s, _constUndefined };
    static inline sSetting criticalChanceStringEnding{ "showStatsEnding"s, "criticalChance"s, _constUndefined };
    static inline sSetting absorbChanceStringEnding{ "showStatsEnding"s, "absorbChance"s, _constUndefined };
    static inline sSetting weaponSpeedMultStringEnding{ "showStatsEnding"s, "weaponSpeedMult"s, _constUndefined };
    static inline sSetting bowSpeedBonusStringEnding{ "showStatsEnding"s, "bowSpeedBonus"s, _constUndefined };
    static inline sSetting shoutRecoveryMultStringEnding{ "showStatsEnding"s, "shoutRecoveryMult"s, _constUndefined };
    static inline sSetting movementNoiseMultStringEnding{ "showStatsEnding"s, "movementNoiseMult"s, _constUndefined };
    static inline sSetting combatHealthRegenMultiplyStringEnding{ "showStatsEnding"s,
        "combatHealthRegenMultiply"s,
        _constUndefined };
    static inline sSetting attackDamageMultStringEnding{ "showStatsEnding"s, "attackDamageMult"s, _constUndefined };
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
    static inline sSetting leftWeaponSpeedMultStringEnding{ "showStatsEnding"s,
        "leftWeaponSpeedMult"s,
        _constUndefined };
    static inline sSetting armorPerksStringEnding{ "showStatsEnding"s, "armorPerks"s, _constUndefined };
    static inline sSetting fallDamageModStringEnding{ "showStatsEnding"s, "fallDamageMod"s, _constUndefined };

    //stat menu
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
    static inline iSetting weaponReachMenu{ "showStatsMenu"s, "weaponReach"s, 0 };
    static inline iSetting weaponReachLeftMenu{ "showStatsMenu"s, "weaponReachLeft"s, 0 };
    static inline iSetting weaponBaseDamageMenu{ "showStatsMenu"s, "weaponBaseDamage"s, 0 };
    static inline iSetting weaponBaseDamageLeftMenu{ "showStatsMenu"s, "weaponBaseDamageLeft"s, 0 };
    static inline iSetting weaponStaggerMenu{ "showStatsMenu"s, "weaponStagger"s, 0 };
    static inline iSetting weaponStaggerLeftMenu{ "showStatsMenu"s, "weaponStaggerLeft"s, 0 };
    static inline iSetting weaponCritDamageRatingMenu{ "showStatsMenu"s, "weaponCritDamageRating"s, 0 };
    static inline iSetting weaponCritDamageRatingLeftMenu{ "showStatsMenu"s, "weaponCritDamageRatingLeft"s, 0 };
    static inline iSetting fallDamageModMenu{ "showStatsMenu"s, "fallDamageMod"s, 0 };

    //multiplier
    static inline iSetting weaponSpeedMultMult{ "showStatsMultiplier"s, "weaponSpeedMult"s, 1 };
    static inline iSetting shoutRecoveryMultMult{ "showStatsMultiplier"s, "shoutRecoveryMult"s, 1 };
    static inline iSetting movementNoiseMultMult{ "showStatsMultiplier"s, "movementNoiseMult"s, 1 };
    static inline iSetting combatHealthRegenMultiplyMult{ "showStatsMultiplier"s, "combatHealthRegenMultiply"s, 1 };
    static inline iSetting leftWeaponSpeedMultMult{ "showStatsMultiplier"s, "leftWeaponSpeedMult"s, 1 };
    static inline iSetting armorPerksMult{ "showStatsMultiplier"s, "armorPerks"s, 1 };
    static inline iSetting fallDamageModMult{ "showStatsMultiplier"s, "fallDamageMod"s, 1 };

    static inline sSetting vampireString{ "showBeastName"s, "vampire"s, _constUndefined };
    static inline sSetting werewolfString{ "showBeastName"s, "werewolf"s, _constUndefined };

    //factions title
    static inline sSetting showFactionsTitleTitle{ "showFactionsTitle"s, "title"s, _constUndefined };
    static inline sSetting showFactionsTitleFaction{ "showFactionsTitle"s, "faction"s, _constUndefined };
    static inline sSetting showFactionsTitleThane{ "showFactionsTitle"s, "thane"s, _constUndefined };
    static inline sSetting showFactionsTitleChampion{ "showFactionsTitle"s, "champion"s, _constUndefined };

    //faction name
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

    //faction menu
    static inline iSetting factionMenu{ "showFactionsFactionMenu"s, "faction"s, 0 };

    //faction ranks
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

    //thane menu
    static inline iSetting thaneMenu{ "showFactionsThaneMenu"s, "thane"s, 0 };

    //thane names
    static inline sSetting thaneOfEastmarchName{ "showFactionsThaneName"s, "thaneOfEastmarch"s, _constUndefined };
    static inline sSetting thaneOfFalkreathName{ "showFactionsThaneName"s, "thaneOfFalkreath"s, _constUndefined };
    static inline sSetting thaneOfHaafingarName{ "showFactionsThaneName"s, "thaneOfHaafingar"s, _constUndefined };
    static inline sSetting thaneOfHjaalmarchName{ "showFactionsThaneName"s, "thaneOfHjaalmarch"s, _constUndefined };
    static inline sSetting thaneOfThePaleName{ "showFactionsThaneName"s, "thaneOfThePale"s, _constUndefined };
    static inline sSetting thaneOfTheReachName{ "showFactionsThaneName"s, "thaneOfTheReach"s, _constUndefined };
    static inline sSetting thaneOfTheRiftName{ "showFactionsThaneName"s, "thaneOfTheRift"s, _constUndefined };
    static inline sSetting thaneOfWhiterunName{ "showFactionsThaneName"s, "thaneOfWhiterun"s, _constUndefined };
    static inline sSetting thaneOfWinterholdName{ "showFactionsThaneName"s, "thaneOfWinterhold"s, _constUndefined };

    //champion menu
    static inline iSetting championMenu{ "showFactionsChampionMenu"s, "champion"s, 0 };

    //champion name
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

    //stats inventory titles
    static inline sSetting showStatsInventoryTitleTitle{ "showStatsInventoryTitle"s, "title"s, _constUndefined };
    static inline sSetting showStatsInventoryTitleEquip{ "showStatsInventoryTitle"s, "equip"s, _constUndefined };
    static inline sSetting showStatsInventoryTitleArmor{ "showStatsInventoryTitle"s, "armor"s, _constUndefined };
    static inline sSetting showStatsInventoryTitleWeapon{ "showStatsInventoryTitle"s, "weapon"s, _constUndefined };
    static inline sSetting showStatsInventoryTitleEffect{ "showStatsInventoryTitle"s, "effect"s, _constUndefined };

    static inline bSetting showStatsInventorydisplayZero{ "showStatsInventorySpecial"s, "displayZero"s, true };

    //stats inventory menu
    static inline iSetting equipedWeightMenuInventory{ "showStatsInventoryMenu"s, "equipedWeight"s, 0 };
    static inline iSetting armorMenuInventory{ "showStatsInventoryMenu"s, "armor"s, 0 };
    static inline iSetting damageMenuInventory{ "showStatsInventoryMenu"s, "damage"s, 0 };
    static inline iSetting healthMenuInventory{ "showStatsInventoryMenu"s, "health"s, 0 };
    static inline iSetting healthRateMenuInventory{ "showStatsInventoryMenu"s, "healthRatePer"s, 0 };
    static inline iSetting magickaMenuInventory{ "showStatsInventoryMenu"s, "magicka"s, 0 };
    static inline iSetting magickaRateMenuInventory{ "showStatsInventoryMenu"s, "magickaRatePer"s, 0 };
    static inline iSetting staminaMenuInventory{ "showStatsInventoryMenu"s, "stamina"s, 0 };
    static inline iSetting staminaRateMenuInventory{ "showStatsInventoryMenu"s, "staminaRatePer"s, 0 };
    static inline iSetting resistDamageMenuInventory{ "showStatsInventoryMenu"s, "resistDamage"s, 0 };
    static inline iSetting resistDiseaseMenuInventory{ "showStatsInventoryMenu"s, "resistDisease"s, 0 };
    static inline iSetting resistPoisonMenuInventory{ "showStatsInventoryMenu"s, "resistPoison"s, 0 };
    static inline iSetting resistFireMenuInventory{ "showStatsInventoryMenu"s, "resistFire"s, 0 };
    static inline iSetting resistShockMenuInventory{ "showStatsInventoryMenu"s, "resistShock"s, 0 };
    static inline iSetting resistFrostMenuInventory{ "showStatsInventoryMenu"s, "resistFrost"s, 0 };
    static inline iSetting resistMagicMenuInventory{ "showStatsInventoryMenu"s, "resistMagic"s, 0 };
    static inline iSetting oneHandedMenuInventory{ "showStatsInventoryMenu"s, "oneHanded"s, 0 };
    static inline iSetting twoHandedMenuInventory{ "showStatsInventoryMenu"s, "twoHanded"s, 0 };
    static inline iSetting archeryMenuInventory{ "showStatsInventoryMenu"s, "archery"s, 0 };
    static inline iSetting blockMenuInventory{ "showStatsInventoryMenu"s, "block"s, 0 };
    static inline iSetting smithingMenuInventory{ "showStatsInventoryMenu"s, "smithing"s, 0 };
    static inline iSetting heavyArmorMenuInventory{ "showStatsInventoryMenu"s, "heavyArmor"s, 0 };
    static inline iSetting lightArmorMenuInventory{ "showStatsInventoryMenu"s, "lightArmor"s, 0 };
    static inline iSetting pickpocketMenuInventory{ "showStatsInventoryMenu"s, "pickpocket"s, 0 };
    static inline iSetting lockpickingMenuInventory{ "showStatsInventoryMenu"s, "lockpicking"s, 0 };
    static inline iSetting sneakMenuInventory{ "showStatsInventoryMenu"s, "sneak"s, 0 };
    static inline iSetting alchemyMenuInventory{ "showStatsInventoryMenu"s, "alchemy"s, 0 };
    static inline iSetting speechMenuInventory{ "showStatsInventoryMenu"s, "speech"s, 0 };
    static inline iSetting enchantingMenuInventory{ "showStatsInventoryMenu"s, "enchanting"s, 0 };
    static inline iSetting alterationMenuInventory{ "showStatsInventoryMenu"s, "alteration"s, 0 };
    static inline iSetting conjurationMenuInventory{ "showStatsInventoryMenu"s, "conjuration"s, 0 };
    static inline iSetting destructionMenuInventory{ "showStatsInventoryMenu"s, "destruction"s, 0 };
    static inline iSetting illusionMenuInventory{ "showStatsInventoryMenu"s, "illusion"s, 0 };
    static inline iSetting restorationMenuInventory{ "showStatsInventoryMenu"s, "restoration"s, 0 };
    static inline iSetting oneHandedPowerModMenuInventory{ "showStatsInventoryMenu"s, "oneHandedPowerMod"s, 0 };
    static inline iSetting twoHandedPowerModMenuInventory{ "showStatsInventoryMenu"s, "twoHandedPowerMod"s, 0 };
    static inline iSetting archeryPowerModMenuInventory{ "showStatsInventoryMenu"s, "archeryPowerMod"s, 0 };
    static inline iSetting blockPowerModMenuInventory{ "showStatsInventoryMenu"s, "blockPowerMod"s, 0 };
    static inline iSetting smithingPowerModMenuInventory{ "showStatsInventoryMenu"s, "smithingPowerMod"s, 0 };
    static inline iSetting heavyArmorPowerModMenuInventory{ "showStatsInventoryMenu"s, "heavyArmorPowerMod"s, 0 };
    static inline iSetting lightArmorPowerModMenuInventory{ "showStatsInventoryMenu"s, "lightArmorPowerMod"s, 0 };
    static inline iSetting pickpocketPowerModMenuInventory{ "showStatsInventoryMenu"s, "pickpocketPowerMod"s, 0 };
    static inline iSetting lockpickingPowerModMenuInventory{ "showStatsInventoryMenu"s, "lockpickingPowerMod"s, 0 };
    static inline iSetting sneakPowerModMenuInventory{ "showStatsInventoryMenu"s, "sneakPowerMod"s, 0 };
    static inline iSetting alchemyPowerModMenuInventory{ "showStatsInventoryMenu"s, "alchemyPowerMod"s, 0 };
    static inline iSetting speechPowerModMenuInventory{ "showStatsInventoryMenu"s, "speechPowerMod"s, 0 };
    static inline iSetting enchantingPowerModMenuInventory{ "showStatsInventoryMenu"s, "enchantingPowerMod"s, 0 };
    static inline iSetting alterationPowerModMenuInventory{ "showStatsInventoryMenu"s, "alterationPowerMod"s, 0 };
    static inline iSetting conjurationPowerModMenuInventory{ "showStatsInventoryMenu"s, "conjurationPowerMod"s, 0 };
    static inline iSetting destructionPowerModMenuInventory{ "showStatsInventoryMenu"s, "destructionPowerMod"s, 0 };
    static inline iSetting illusionPowerModMenuInventory{ "showStatsInventoryMenu"s, "illusionPowerMod"s, 0 };
    static inline iSetting restorationPowerModMenuInventory{ "showStatsInventoryMenu"s, "restorationPowerMod"s, 0 };
    static inline iSetting speedMultMenuInventory{ "showStatsInventoryMenu"s, "speedMult"s, 0 };
    static inline iSetting inventoryWeightMenuInventory{ "showStatsInventoryMenu"s, "inventoryWeight"s, 0 };
    static inline iSetting carryWeightMenuInventory{ "showStatsInventoryMenu"s, "carryWeight"s, 0 };
    static inline iSetting criticalChanceMenuInventory{ "showStatsInventoryMenu"s, "criticalChance"s, 0 };
    static inline iSetting meleeDamageMenuInventory{ "showStatsInventoryMenu"s, "meleeDamage"s, 0 };
    static inline iSetting unarmedDamageMenuInventory{ "showStatsInventoryMenu"s, "unarmedDamage"s, 0 };
    static inline iSetting absorbChanceMenuInventory{ "showStatsInventoryMenu"s, "absorbChance"s, 0 };
    static inline iSetting weaponSpeedMultMenuInventory{ "showStatsInventoryMenu"s, "weaponSpeedMult"s, 0 };
    static inline iSetting bowSpeedBonusMenuInventory{ "showStatsInventoryMenu"s, "bowSpeedBonus"s, 0 };
    static inline iSetting shoutRecoveryMultMenuInventory{ "showStatsInventoryMenu"s, "shoutRecoveryMult"s, 0 };
    static inline iSetting movementNoiseMultMenuInventory{ "showStatsInventoryMenu"s, "movementNoiseMult"s, 0 };
    static inline iSetting attackDamageMultMenuInventory{ "showStatsInventoryMenu"s, "attackDamageMult"s, 0 };
    static inline iSetting reflectDamageMenuInventory{ "showStatsInventoryMenu"s, "reflectDamage"s, 0 };
    static inline iSetting oneHandedModMenuInventory{ "showStatsInventoryMenu"s, "oneHandedMod"s, 0 };
    static inline iSetting twoHandedModMenuInventory{ "showStatsInventoryMenu"s, "twoHandedMod"s, 0 };
    static inline iSetting archeryModMenuInventory{ "showStatsInventoryMenu"s, "archeryMod"s, 0 };
    static inline iSetting blockModMenuInventory{ "showStatsInventoryMenu"s, "blockMod"s, 0 };
    static inline iSetting smithingModMenuInventory{ "showStatsInventoryMenu"s, "smithingMod"s, 0 };
    static inline iSetting heavyArmorModMenuInventory{ "showStatsInventoryMenu"s, "heavyArmorMod"s, 0 };
    static inline iSetting lightArmorModMenuInventory{ "showStatsInventoryMenu"s, "lightArmorMod"s, 0 };
    static inline iSetting pickpocketModMenuInventory{ "showStatsInventoryMenu"s, "pickpocketMod"s, 0 };
    static inline iSetting lockpickingModMenuInventory{ "showStatsInventoryMenu"s, "lockpickingMod"s, 0 };
    static inline iSetting sneakModMenuInventory{ "showStatsInventoryMenu"s, "sneakMod"s, 0 };
    static inline iSetting alchemyModMenuInventory{ "showStatsInventoryMenu"s, "alchemyMod"s, 0 };
    static inline iSetting speechModMenuInventory{ "showStatsInventoryMenu"s, "speechMod"s, 0 };
    static inline iSetting enchantingModMenuInventory{ "showStatsInventoryMenu"s, "enchantingMod"s, 0 };
    static inline iSetting alterationModMenuInventory{ "showStatsInventoryMenu"s, "alterationMod"s, 0 };
    static inline iSetting conjurationModMenuInventory{ "showStatsInventoryMenu"s, "conjurationMod"s, 0 };
    static inline iSetting destructionModMenuInventory{ "showStatsInventoryMenu"s, "destructionMod"s, 0 };
    static inline iSetting illusionModMenuInventory{ "showStatsInventoryMenu"s, "illusionMod"s, 0 };
    static inline iSetting restorationModMenuInventory{ "showStatsInventoryMenu"s, "restorationMod"s, 0 };
    static inline iSetting damageArrowMenuInventory{ "showStatsInventoryMenu"s, "damageArrow"s, 0 };
    static inline iSetting damageLeftMenuInventory{ "showStatsInventoryMenu"s, "damageLeft"s, 0 };
    static inline iSetting leftWeaponSpeedMultMenuInventory{ "showStatsInventoryMenu"s, "leftWeaponSpeedMult"s, 0 };
    static inline iSetting rightItemChargeMenuInventory{ "showStatsInventoryMenu"s, "rightItemCharge"s, 0 };
    static inline iSetting leftItemChargeMenuInventory{ "showStatsInventoryMenu"s, "leftItemCharge"s, 0 };
    static inline iSetting armorPerksMenuInventory{ "showStatsInventoryMenu"s, "armorPerks"s, 0 };
    static inline iSetting massMenuInventory{ "showStatsInventoryMenu"s, "mass"s, 0 };
    static inline iSetting bowStaggerBonusMenuInventory{ "showStatsInventoryMenu"s, "bowStaggerBonus"s, 0 };
    static inline iSetting weaponReachMenuInventory{ "showStatsInventoryMenu"s, "weaponReach"s, 0 };
    static inline iSetting weaponReachLeftMenuInventory{ "showStatsInventoryMenu"s, "weaponReachLeft"s, 0 };
    static inline iSetting weaponBaseDamageMenuInventory{ "showStatsInventoryMenu"s, "weaponBaseDamage"s, 0 };
    static inline iSetting weaponBaseDamageLeftMenuInventory{ "showStatsInventoryMenu"s, "weaponBaseDamageLeft"s, 0 };
    static inline iSetting weaponStaggerMenuInventory{ "showStatsInventoryMenu"s, "weaponStagger"s, 0 };
    static inline iSetting weaponStaggerLeftMenuInventory{ "showStatsInventoryMenu"s, "weaponStaggerLeft"s, 0 };
    static inline iSetting weaponCritDamageRatingMenuInventory{ "showStatsInventoryMenu"s,
        "weaponCritDamageRating"s,
        0 };
    static inline iSetting weaponCritDamageRatingLeftMenuInventory{ "showStatsInventoryMenu"s,
        "weaponCritDamageRatingLeft"s,
        0 };
    static inline iSetting fallDamageModMenuInventory{ "showStatsInventoryMenu"s, "fallDamageMod"s, 0 };
};
