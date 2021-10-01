#pragma once
#include "stats/statfiller.h"

using StatsValue = constants::StatsValue;
using ActorValue = RE::ActorValue;
using Menu = constants::MenuValue;

Filler* Filler::GetSingleton() {
	static Filler singleton;
	return addressof(singleton);
}

vector<StatItem> Filler::getData() {
	logger::debug("Vector Size is {}"sv, Filler::statList.size());
	Filler::statList = {
		{ StatsValue::name, ActorValue::kNone, *Settings::nameString, *Settings::nameStringEnding, *Settings::name },
		{ StatsValue::race, ActorValue::kNone, *Settings::raceString, *Settings::raceStringEnding, *Settings::race },
		{ StatsValue::level, ActorValue::kNone, *Settings::levelString, *Settings::levelStringEnding, *Settings::level },
		{ StatsValue::perkCount, ActorValue::kNone, *Settings::perkCountString, *Settings::perkCountStringEnding, *Settings::perkCount },
		{ StatsValue::height, ActorValue::kNone, *Settings::heightString, *Settings::heightStringEnding, *Settings::height, getMenu(*Settings::heightMenu) },
		{ StatsValue::equipedWeight, ActorValue::kNone, *Settings::equipedWeightString, *Settings::equipedWeightStringEnding, *Settings::equipedWeight, getMenu(*Settings::equipedWeightMenu) },
		{ StatsValue::weight, ActorValue::kNone, *Settings::weightString, *Settings::weightStringEnding, *Settings::weight, getMenu(*Settings::weightMenu) },
		{ StatsValue::armor, ActorValue::kNone, *Settings::armorString, *Settings::armorStringEnding, *Settings::armor, getMenu(*Settings::armorMenu) },
		{ StatsValue::damage, ActorValue::kNone, *Settings::damageString, *Settings::damageStringEnding, *Settings::damage, getMenu(*Settings::damageMenu) },
		{ StatsValue::skillTrainingsThisLevel, ActorValue::kNone, *Settings::skillTrainingsThisLevelString, *Settings::skillTrainingsThisLevelStringEnding, *Settings::skillTrainingsThisLevel, getMenu(*Settings::skillTrainingsThisLevelMenu) },
		{ StatsValue::health, ActorValue::kHealth, *Settings::healthString, *Settings::healthStringEnding, *Settings::health, getMenu(*Settings::healthMenu) },
		{ StatsValue::healthRatePer, ActorValue::kNone, *Settings::healthRateString, *Settings::healthRateStringEnding, *Settings::healthRate, getMenu(*Settings::healthRateMenu) },
		{ StatsValue::magicka, ActorValue::kMagicka, *Settings::magickaString, *Settings::magickaStringEnding, *Settings::magicka, getMenu(*Settings::magickaMenu) },
		{ StatsValue::magickaRatePer, ActorValue::kNone, *Settings::magickaRateString, *Settings::magickaRateStringEnding, *Settings::magickaRate, getMenu(*Settings::magickaRateMenu) },
		{ StatsValue::stamina, ActorValue::kStamina, *Settings::staminaString, *Settings::staminaStringEnding, *Settings::stamina, getMenu(*Settings::staminaMenu) },
		{ StatsValue::staminaRatePer, ActorValue::kNone, *Settings::staminaRateString, *Settings::staminaRateStringEnding, *Settings::staminaRate, getMenu(*Settings::staminaRateMenu) },
		{ StatsValue::resistDamage, ActorValue::kDamageResist, *Settings::resistDamageString, *Settings::resistDamageStringEnding, *Settings::resistDamage, getMenu(*Settings::resistDamageMenu) },
		{ StatsValue::resistDisease, ActorValue::kResistDisease, *Settings::resistDiseaseString, *Settings::resistDiseaseStringEnding, *Settings::resistDisease, getMenu(*Settings::resistDiseaseMenu) },
		{ StatsValue::resistPoison, ActorValue::kPoisonResist, *Settings::restorationModString, *Settings::resistPoisonStringEnding, *Settings::resistPoison, getMenu(*Settings::resistPoisonMenu) },
		{ StatsValue::resistFire, ActorValue::kResistFire, *Settings::resistFireString, *Settings::resistFireStringEnding, *Settings::resistFire, getMenu(*Settings::resistFireMenu) },
		{ StatsValue::resistShock, ActorValue::kResistShock, *Settings::resistShockString, *Settings::resistShockStringEnding, *Settings::resistShock, getMenu(*Settings::resistShockMenu) },
		{ StatsValue::resistFrost, ActorValue::kResistFrost, *Settings::resistFrostString, *Settings::resistFrostStringEnding, *Settings::resistFrost, getMenu(*Settings::resistFrostMenu) },
		{ StatsValue::resistMagic, ActorValue::kResistMagic, *Settings::resistMagicString, *Settings::resistMagicStringEnding, *Settings::resistMagic, getMenu(*Settings::resistMagicMenu) },
		{ StatsValue::oneHanded, ActorValue::kOneHanded, *Settings::oneHandedString, *Settings::oneHandedStringEnding, *Settings::oneHanded, getMenu(*Settings::oneHandedMenu) },
		{ StatsValue::twoHanded, ActorValue::kTwoHanded, *Settings::twoHandedString, *Settings::twoHandedStringEnding, *Settings::twoHanded, getMenu(*Settings::twoHandedMenu) },
		{ StatsValue::archery, ActorValue::kArchery, *Settings::archeryString, *Settings::archeryStringEnding, *Settings::archery, getMenu(*Settings::archeryMenu) },
		{ StatsValue::block, ActorValue::kBlock, *Settings::blockString, *Settings::blockStringEnding, *Settings::block, getMenu(*Settings::blockMenu) },
		{ StatsValue::smithing, ActorValue::kSmithing, *Settings::smithingString, *Settings::smithingStringEnding, *Settings::smithing, getMenu(*Settings::smithingMenu) },
		{ StatsValue::heavyArmor, ActorValue::kHeavyArmor, *Settings::heavyArmorString, *Settings::heavyArmorStringEnding, *Settings::heavyArmor, getMenu(*Settings::heavyArmorMenu) },
		{ StatsValue::lightArmor, ActorValue::kLightArmor, *Settings::lightArmorString, *Settings::lightArmorStringEnding, *Settings::lightArmor, getMenu(*Settings::lightArmorMenu) },
		{ StatsValue::pickpocket, ActorValue::kPickpocket, *Settings::pickpocketString, *Settings::pickpocketStringEnding, *Settings::pickpocket, getMenu(*Settings::pickpocketMenu) },
		{ StatsValue::lockpicking, ActorValue::kLockpicking, *Settings::lockpickingString, *Settings::lockpickingStringEnding, *Settings::lockpicking, getMenu(*Settings::lockpickingMenu) },
		{ StatsValue::sneak, ActorValue::kSneak, *Settings::sneakString, *Settings::sneakStringEnding, *Settings::sneak, getMenu(*Settings::sneakMenu) },
		{ StatsValue::alchemy, ActorValue::kAlchemy, *Settings::alchemyString, *Settings::alchemyStringEnding, *Settings::alchemy, getMenu(*Settings::alchemyMenu) },
		{ StatsValue::speech, ActorValue::kSpeech, *Settings::speechString, *Settings::speechStringEnding, *Settings::speech, getMenu(*Settings::speechMenu) },
		{ StatsValue::enchanting, ActorValue::kEnchanting, *Settings::enchantingString, *Settings::enchantingStringEnding, *Settings::enchanting, getMenu(*Settings::enchantingMenu) },
		{ StatsValue::alteration, ActorValue::kAlteration, *Settings::alterationString, *Settings::alterationStringEnding, *Settings::alteration, getMenu(*Settings::alterationMenu) },
		{ StatsValue::conjuration, ActorValue::kConjuration, *Settings::conjurationString, *Settings::conjurationStringEnding, *Settings::conjuration, getMenu(*Settings::conjurationMenu) },
		{ StatsValue::destruction, ActorValue::kDestruction, *Settings::destructionString, *Settings::destructionStringEnding, *Settings::destruction, getMenu(*Settings::destructionMenu) },
		{ StatsValue::illusion, ActorValue::kIllusion, *Settings::illusionString, *Settings::illusionStringEnding, *Settings::illusion, getMenu(*Settings::illusionMenu) },
		{ StatsValue::restoration, ActorValue::kRestoration, *Settings::restorationString, *Settings::restorationStringEnding, *Settings::restoration, getMenu(*Settings::restorationMenu) },
		{ StatsValue::oneHandedPowerMod, ActorValue::kOneHandedPowerModifier, *Settings::oneHandedPowerModString, *Settings::oneHandedPowerModStringEnding, *Settings::oneHandedPowerMod, getMenu(*Settings::oneHandedPowerModMenu) },
		{ StatsValue::twoHandedPowerMod, ActorValue::kTwoHandedPowerModifier, *Settings::twoHandedPowerModString, *Settings::twoHandedPowerModStringEnding, *Settings::twoHandedPowerMod, getMenu(*Settings::twoHandedPowerModMenu) },
		{ StatsValue::archeryPowerMod, ActorValue::kMarksmanPowerModifier, *Settings::archeryPowerModString, *Settings::archeryPowerModStringEnding, *Settings::archeryPowerMod, getMenu(*Settings::archeryPowerModMenu) },
		{ StatsValue::blockPowerMod, ActorValue::kBlockPowerModifier, *Settings::blockPowerModString, *Settings::blockPowerModStringEnding, *Settings::blockPowerMod, getMenu(*Settings::blockPowerModMenu) },
		{ StatsValue::smithingPowerMod, ActorValue::kSmithingPowerModifier, *Settings::smithingPowerModString, *Settings::smithingPowerModStringEnding, *Settings::smithingPowerMod, getMenu(*Settings::smithingPowerModMenu) },
		{ StatsValue::heavyArmorPowerMod, ActorValue::kHeavyArmorPowerModifier, *Settings::heavyArmorPowerModString, *Settings::heavyArmorPowerModStringEnding, *Settings::heavyArmorPowerMod, getMenu(*Settings::heavyArmorPowerModMenu) },
		{ StatsValue::lightArmorPowerMod, ActorValue::kLightArmorPowerModifier, *Settings::lightArmorPowerModString, *Settings::lightArmorPowerModStringEnding, *Settings::lightArmorPowerMod, getMenu(*Settings::lightArmorPowerModMenu) },
		{ StatsValue::pickpocketPowerMod, ActorValue::kPickpocketPowerModifier, *Settings::pickpocketPowerModString, *Settings::pickpocketPowerModStringEnding, *Settings::pickpocketPowerMod, getMenu(*Settings::pickpocketPowerModMenu) },
		{ StatsValue::lockpickingPowerMod, ActorValue::kLockpickingPowerModifier, *Settings::lockpickingPowerModString, *Settings::lockpickingPowerModStringEnding, *Settings::lockpickingPowerMod, getMenu(*Settings::lockpickingPowerModMenu) },
		{ StatsValue::sneakPowerMod, ActorValue::kSneakingPowerModifier, *Settings::sneakPowerModString, *Settings::sneakPowerModStringEnding, *Settings::sneakPowerMod, getMenu(*Settings::sneakPowerModMenu) },
		{ StatsValue::alchemyPowerMod, ActorValue::kAlchemyPowerModifier, *Settings::alchemyPowerModString, *Settings::alchemyPowerModStringEnding, *Settings::alchemyPowerMod, getMenu(*Settings::alchemyPowerModMenu) },
		{ StatsValue::speechPowerMod, ActorValue::kSpeechcraftPowerModifier, *Settings::speechPowerModString, *Settings::speechPowerModStringEnding, *Settings::speechPowerMod, getMenu(*Settings::speechPowerModMenu) },
		{ StatsValue::enchantingPowerMod, ActorValue::kEnchantingPowerModifier, *Settings::enchantingPowerModString, *Settings::enchantingPowerModStringEnding, *Settings::enchantingPowerMod, getMenu(*Settings::enchantingPowerModMenu) },
		{ StatsValue::alterationPowerMod, ActorValue::kAlterationPowerModifier, *Settings::alterationPowerModString, *Settings::alterationPowerModStringEnding, *Settings::alterationPowerMod, getMenu(*Settings::alterationPowerModMenu) },
		{ StatsValue::conjurationPowerMod, ActorValue::kConjurationPowerModifier, *Settings::conjurationPowerModString, *Settings::conjurationPowerModStringEnding, *Settings::conjurationPowerMod, getMenu(*Settings::conjurationPowerModMenu) },
		{ StatsValue::destructionPowerMod, ActorValue::kDestructionPowerModifier, *Settings::destructionPowerModString, *Settings::destructionPowerModStringEnding, *Settings::destructionPowerMod, getMenu(*Settings::destructionPowerModMenu) },
		{ StatsValue::illusionPowerMod, ActorValue::kIllusionPowerModifier, *Settings::illusionPowerModString, *Settings::illusionPowerModStringEnding, *Settings::illusionPowerMod, getMenu(*Settings::illusionPowerModMenu) },
		{ StatsValue::restorationPowerMod, ActorValue::kRestorationPowerModifier, *Settings::restorationPowerModString, *Settings::restorationPowerModStringEnding, *Settings::restorationPowerMod, getMenu(*Settings::restorationPowerModMenu) },
		{ StatsValue::speedMult, ActorValue::kSpeedMult, *Settings::speedMultString, *Settings::speedMultStringEnding, *Settings::speedMult, getMenu(*Settings::speedMultMenu) },
		{ StatsValue::inventoryWeight, ActorValue::kInventoryWeight, *Settings::inventoryWeightString, *Settings::inventoryWeightStringEnding, *Settings::inventoryWeight, getMenu(*Settings::inventoryWeightMenu) },
		{ StatsValue::carryWeight, ActorValue::kCarryWeight, *Settings::carryWeightString, *Settings::carryWeightStringEnding, *Settings::carryWeight, getMenu(*Settings::carryWeightMenu) },
		{ StatsValue::criticalChance, ActorValue::kCriticalChance, *Settings::criticalChanceString, *Settings::criticalChanceStringEnding, *Settings::criticalChance, getMenu(*Settings::criticalChanceMenu) },
		{ StatsValue::meleeDamage, ActorValue::kMeleeDamage, *Settings::meleeDamageString, *Settings::meleeDamageStringEnding, *Settings::meleeDamage, getMenu(*Settings::meleeDamageMenu) },
		{ StatsValue::unarmedDamage, ActorValue::kUnarmedDamage, *Settings::unarmedDamageString, *Settings::unarmedDamageStringEnding, *Settings::unarmedDamage, getMenu(*Settings::unarmedDamageMenu) },
		{ StatsValue::absorbChance, ActorValue::kAbsorbChance, *Settings::absorbChanceString, *Settings::absorbChanceStringEnding, *Settings::absorbChance, getMenu(*Settings::absorbChanceMenu) },
		//we will not set the actor value kWeaponSpeedMult and kLeftWeaponSpeedMultiply here, because some genius thought it is nice that the value 0 and 1 means 100%
		// https://en.uesp.net/wiki/Skyrim_Mod:Actor_Value_Indices as documented here
		{ StatsValue::weaponSpeedMult, ActorValue::kNone, *Settings::weaponSpeedMultString, *Settings::weaponSpeedMultStringEnding, *Settings::weaponSpeedMult, getMenu(*Settings::weaponSpeedMultMenu) },
		{ StatsValue::leftWeaponSpeedMult, ActorValue::kNone, *Settings::leftWeaponSpeedMultString, *Settings::leftWeaponSpeedMultStringEnding, *Settings::leftWeaponSpeedMult, getMenu(*Settings::leftWeaponSpeedMultMenu) },
		{ StatsValue::rightItemCharge, ActorValue::kRightItemCharge, *Settings::rightItemChargeString, *Settings::rightItemChargeStringEnding, *Settings::rightItemCharge, getMenu(*Settings::rightItemChargeMenu) },
		{ StatsValue::leftItemCharge, ActorValue::kLeftItemCharge, *Settings::leftItemChargStringe, *Settings::leftItemChargStringeEnding, *Settings::leftItemCharge, getMenu(*Settings::leftItemChargeMenu) },
		{ StatsValue::armorPerks, ActorValue::kArmorPerks, *Settings::armorPerksString, *Settings::damageArrowStringEnding, *Settings::armorPerks, getMenu(*Settings::armorPerksMenu) },
		{ StatsValue::mass, ActorValue::kMass, *Settings::massString, *Settings::massStringEnding, *Settings::mass, getMenu(*Settings::massMenu) },
		{ StatsValue::bowStaggerBonus, ActorValue::kBowStaggerBonus, *Settings::bowStaggerBonusString, *Settings::bowStaggerBonusStringEnding, *Settings::bowStaggerBonus, getMenu(*Settings::bowStaggerBonusMenu) },
		{ StatsValue::bypassVendorKeywordCheck, ActorValue::kBypassVendorKeywordCheck, *Settings::bypassVendorKeywordCheckString, *Settings::bypassVendorKeywordCheckStringEnding, *Settings::bypassVendorKeywordCheck, getMenu(*Settings::bypassVendorKeywordCheckMenu) },
		{ StatsValue::bypassVendorStolenCheck, ActorValue::kBypassVendorStolenCheck, *Settings::bypassVendorStolenCheckString, *Settings::bypassVendorStolenCheckStringEnding, *Settings::bypassVendorStolenCheck, getMenu(*Settings::bypassVendorStolenCheckMenu) },
		{ StatsValue::bowSpeedBonus, ActorValue::kBowSpeedBonus, *Settings::bowSpeedBonusString, *Settings::bowSpeedBonusStringEnding, *Settings::bowSpeedBonus, getMenu(*Settings::bowSpeedBonusMenu) },
		{ StatsValue::shoutRecoveryMult, ActorValue::kShoutRecoveryMult, *Settings::shoutRecoveryMultString, *Settings::shoutRecoveryMultStringEnding, *Settings::shoutRecoveryMult, getMenu(*Settings::shoutRecoveryMultMenu) },
		{ StatsValue::movementNoiseMult, ActorValue::kMovementNoiseMult, *Settings::movementNoiseMultString, *Settings::movementNoiseMultStringEnding, *Settings::movementNoiseMult, getMenu(*Settings::movementNoiseMultMenu) },
		{ StatsValue::dragonSouls, ActorValue::kDragonSouls, *Settings::dragonSoulsString, *Settings::dragonSoulsStringEnding, *Settings::dragonSouls, getMenu(*Settings::dragonSoulsMenu) },
		{ StatsValue::combatHealthRegenMultiply, ActorValue::kCombatHealthRegenMultiply, *Settings::combatHealthRegenMultiplyString, *Settings::combatHealthRegenMultiplyStringEnding, *Settings::combatHealthRegenMultiply, getMenu(*Settings::combatHealthRegenMultiplyMenu) },
		{ StatsValue::attackDamageMult, ActorValue::kAttackDamageMult, *Settings::attackDamageMultString, *Settings::attackDamageMultStringEnding, *Settings::attackDamageMult, getMenu(*Settings::attackDamageMultMenu) },
		{ StatsValue::beast, ActorValue::kNone, *Settings::beastString, *Settings::beastStringEnding, *Settings::beast },
		{ StatsValue::xp, ActorValue::kNone, *Settings::xpString, *Settings::xpStringEnding, *Settings::xp, constants::MenuValue::mNone, true },
		{ StatsValue::reflectDamage, ActorValue::kReflectDamage, *Settings::reflectDamageString, *Settings::reflectDamageStringEnding, *Settings::reflectDamage, getMenu(*Settings::reflectDamageMenu) },
		{ StatsValue::oneHandedMod, ActorValue::kOneHandedModifier, *Settings::oneHandedModString, *Settings::oneHandedModStringEnding, *Settings::oneHandedMod, getMenu(*Settings::oneHandedModMenu) },
		{ StatsValue::twoHandedMod, ActorValue::kTwoHandedModifier, *Settings::twoHandedModString, *Settings::twoHandedModStringEnding, *Settings::twoHandedMod, getMenu(*Settings::twoHandedModMenu) },
		{ StatsValue::marksmanMod, ActorValue::kMarksmanModifier, *Settings::archeryModString, *Settings::archeryModStringEnding, *Settings::archeryMod, getMenu(*Settings::archeryModMenu) },
		{ StatsValue::blockMod, ActorValue::kBlockModifier, *Settings::blockModString, *Settings::blockModStringEnding, *Settings::blockMod, getMenu(*Settings::blockModMenu) },
		{ StatsValue::smithingMod, ActorValue::kSmithingModifier, *Settings::smithingModString, *Settings::smithingModStringEnding, *Settings::smithingMod, getMenu(*Settings::smithingModMenu) },
		{ StatsValue::heavyArmorMod, ActorValue::kHeavyArmorModifier, *Settings::heavyArmorModString, *Settings::heavyArmorModStringEnding, *Settings::heavyArmorMod, getMenu(*Settings::heavyArmorModMenu) },
		{ StatsValue::lightArmorMod, ActorValue::kLightArmorModifier, *Settings::lightArmorModString, *Settings::lightArmorModStringEnding, *Settings::lightArmorMod, getMenu(*Settings::lightArmorModMenu) },
		{ StatsValue::pickpocketMod, ActorValue::kPickpocketModifier, *Settings::pickpocketModString, *Settings::pickpocketModStringEnding, *Settings::pickpocketMod, getMenu(*Settings::pickpocketModMenu) },
		{ StatsValue::lockpickingMod, ActorValue::kLockpickingModifier, *Settings::lockpickingModString, *Settings::lockpickingModStringEnding, *Settings::lockpickingMod, getMenu(*Settings::lockpickingModMenu) },
		{ StatsValue::sneakingMod, ActorValue::kSneakingModifier, *Settings::sneakModString, *Settings::sneakModStringEnding, *Settings::sneakMod, getMenu(*Settings::sneakModMenu) },
		{ StatsValue::alchemyMod, ActorValue::kAlchemyModifier, *Settings::alchemyModString, *Settings::alchemyModStringEnding, *Settings::alchemyMod, getMenu(*Settings::alchemyModMenu) },
		{ StatsValue::speechcraftMod, ActorValue::kSpeechcraftModifier, *Settings::speechModString, *Settings::speechModStringEnding, *Settings::speechMod, getMenu(*Settings::speechModMenu) },
		{ StatsValue::enchantingMod, ActorValue::kEnchantingModifier, *Settings::enchantingModString, *Settings::enchantingModStringEnding, *Settings::enchantingMod, getMenu(*Settings::enchantingModMenu) },
		{ StatsValue::alterationMod, ActorValue::kAlterationModifier, *Settings::alterationModString, *Settings::alterationModStringEnding, *Settings::alterationMod, getMenu(*Settings::alterationModMenu) },
		{ StatsValue::conjurationMod, ActorValue::kConjurationModifier, *Settings::conjurationModString, *Settings::conjurationModStringEnding, *Settings::conjurationMod, getMenu(*Settings::conjurationModMenu) },
		{ StatsValue::destructionMod, ActorValue::kDestructionModifier, *Settings::destructionModString, *Settings::destructionModStringEnding, *Settings::destructionMod, getMenu(*Settings::destructionModMenu) },
		{ StatsValue::illusionMod, ActorValue::kIllusionModifier, *Settings::illusionModString, *Settings::illusionModStringEnding, *Settings::illusionMod, getMenu(*Settings::illusionModMenu) },
		{ StatsValue::restorationMod, ActorValue::kRestorationModifier, *Settings::restorationModString, *Settings::restorationModStringEnding, *Settings::restorationMod, getMenu(*Settings::restorationModMenu) },
		{ StatsValue::damageArrow, ActorValue::kNone, *Settings::damageArrowString, *Settings::damageArrowStringEnding, *Settings::damageArrow, getMenu(*Settings::damageArrowMenu) },
		{ StatsValue::damageLeft, ActorValue::kNone, *Settings::damageLeftString, *Settings::damageLeftStringEnding, *Settings::damageLeft, getMenu(*Settings::damageLeftMenu) },
		{ StatsValue::darkbrotherHood, ActorValue::kNone, "", "", false, constants::MenuValue::mNone, false },
		{ StatsValue::thiefsGuild, ActorValue::kNone, "", "", false, constants::MenuValue::mNone, false },
		{ StatsValue::orcFriend, ActorValue::kNone, "", "", false, constants::MenuValue::mNone, false },
		{ StatsValue::collegeOfWinterhold, ActorValue::kNone, "", "", false, constants::MenuValue::mNone, false },
		{ StatsValue::companions, ActorValue::kNone, "", "", false, constants::MenuValue::mNone, false },
		{ StatsValue::imperialLegion, ActorValue::kNone, "", "", false, constants::MenuValue::mNone, false },
		{ StatsValue::stormcloaks, ActorValue::kNone, "", "", false, constants::MenuValue::mNone, false },
		{ StatsValue::greybeard, ActorValue::kNone, "", "", false, constants::MenuValue::mNone, false },
	};
	logger::debug("Vector Size is {}"sv, Filler::statList.size());
	return Filler::statList;
}

void Filler::PrintStatsVector(vector<StatItem>& p_vec) {
	logger::debug("Vector Size is {}"sv, p_vec.size());
	for (auto& element : p_vec) {
		logger::trace("name {}, actor {}, value {}, displayname ({}), ending {}, show {}, guiText ({}), ST {}, menu {}"sv,
			element.getName(),
			element.getActor(),
			element.getValue(),
			element.getDisplayName(),
			element.getEnding(),
			element.getShow(),
			element.getGuiText(),
			element.getStaticText(),
			element.getMenu()
		);
	}
}

constants::MenuValue Filler::getMenu(int64_t p_menu_id) {
	//in case the config value does not match 
	if (constants::configMenu.find(p_menu_id) == constants::configMenu.end()) {
		logger::warn("can not find Menu {}"sv, p_menu_id);
		return constants::MenuValue::mNone;
	} else {
		return constants::configMenu.find(p_menu_id)->second;
	}
}