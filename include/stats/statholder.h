#pragma once
#include "constants.h"
#include "settings.h"

namespace StatHolders
{
	class StatItem
	{
	public:

		StatItem(constants::StatsValue p_name,
			RE::ActorValue p_actor,
			string p_display_name,
			string p_ending,
			boolean p_show)
		{
			this->setName(p_name);
			this->setActor(p_actor);
			this->setDisplayName(p_display_name);
			this->setEnding(p_ending);
			this->setShow(p_show);
			this->value.clear();
			this->guiText.clear();
			this->setStaticText(false);
		};

		StatItem(constants::StatsValue p_name,
			RE::ActorValue p_actor,
			string p_display_name,
			string p_ending,
			boolean p_show,
			boolean p_static_text)
		{
			this->setName(p_name);
			this->setActor(p_actor);
			this->setDisplayName(p_display_name);
			this->setEnding(p_ending);
			this->setShow(p_show);
			this->value.clear();
			this->guiText.clear();
			this->setStaticText(p_static_text);
		};

		void setName(constants::StatsValue p_name) { 
			name = p_name; 
		}
		constants::StatsValue getName() { return name; }
		void setActor(RE::ActorValue p_actor) { actor = p_actor; }
		RE::ActorValue getActor() { return actor; }
		void setValue(string p_value)
		{
			value = p_value;
			buildText();
		}
		string getValue() { return value; }
		void setDisplayName(string p_display_name) { displayName = p_display_name; }
		string getDisplayName() { return displayName; }
		void setEnding(string p_ending) { ending = p_ending; }
		string getEnding() { return ending; }
		void setShow(boolean p_show) { show = p_show; }
		boolean getShow() { return show; }
		void setGuiText(string p_gui_text) { p_gui_text = guiText; }
		string getGuiText() { return guiText; }
		void setStaticText(boolean p_static_text) { p_static_text = staticText; }
		boolean getStaticText() { return staticText; }

	private:
		constants::StatsValue name;
		RE::ActorValue actor;
		string value;
		string displayName;
		string ending;
		boolean show;
		string guiText;
		boolean staticText;

		void buildText() {
			if (!value.empty() && !displayName.empty() && !show ) {
				return;
			}

			guiText.clear();

			guiText = displayName;
			if (value.size() > 0) {
				guiText += ": ";
			}
			
			guiText += ( staticText ) ? value : constants::cutString(value);

			guiText += ending;
		}

	};

	class Filler
	{
	public:
		static Filler* GetSingleton(){
			static Filler singleton;
			return addressof(singleton);
		}

		using StatsValue = constants::StatsValue;
		using ActorValue = RE::ActorValue;

		void doVector(vector<StatItem*>& p_vec) {
			p_vec.clear();

			p_vec.push_back(new StatItem(StatsValue::name, ActorValue::kNone, *Settings::nameString, *Settings::nameStringEnding, *Settings::name));
			p_vec.push_back(new StatItem(StatsValue::race, ActorValue::kNone, *Settings::raceString, *Settings::raceStringEnding, *Settings::race));
			p_vec.push_back(new StatItem(StatsValue::level, ActorValue::kNone, *Settings::levelString, *Settings::levelStringEnding, *Settings::level));
			p_vec.push_back(new StatItem(StatsValue::perkCount, ActorValue::kNone, *Settings::perkCountString, *Settings::perkCountStringEnding, *Settings::perkCount));
			p_vec.push_back(new StatItem(StatsValue::height, ActorValue::kNone, *Settings::heightString, *Settings::heightStringEnding, *Settings::height));
			p_vec.push_back(new StatItem(StatsValue::equipedWeight, ActorValue::kNone, *Settings::equipedWeightString, *Settings::equipedWeightStringEnding, *Settings::equipedWeight));
			p_vec.push_back(new StatItem(StatsValue::weight, ActorValue::kNone, *Settings::weightString, *Settings::weightStringEnding, *Settings::weight));
			p_vec.push_back(new StatItem(StatsValue::armor, ActorValue::kNone, *Settings::armorString, *Settings::armorStringEnding, *Settings::armor));
			p_vec.push_back(new StatItem(StatsValue::damage, ActorValue::kNone, *Settings::damageString, *Settings::damageStringEnding, *Settings::damage));
			p_vec.push_back(new StatItem(StatsValue::skillTrainingsThisLevel, ActorValue::kNone, *Settings::skillTrainingsThisLevelString, *Settings::skillTrainingsThisLevelStringEnding, *Settings::skillTrainingsThisLevel));
			p_vec.push_back(new StatItem(StatsValue::health, ActorValue::kHealth, *Settings::healthString, *Settings::healthStringEnding, *Settings::health));
			p_vec.push_back(new StatItem(StatsValue::healthRatePer, ActorValue::kNone, *Settings::healthRateString, *Settings::healthRateStringEnding, *Settings::healthRate));
			p_vec.push_back(new StatItem(StatsValue::magicka, ActorValue::kMagicka, *Settings::magickaString, *Settings::magickaStringEnding, *Settings::magicka));
			p_vec.push_back(new StatItem(StatsValue::magickaRatePer, ActorValue::kNone, *Settings::magickaRateString, *Settings::magickaRateStringEnding, *Settings::magickaRate));
			p_vec.push_back(new StatItem(StatsValue::stamina, ActorValue::kStamina, *Settings::staminaString, *Settings::staminaStringEnding, *Settings::stamina));
			p_vec.push_back(new StatItem(StatsValue::staminaRatePer, ActorValue::kNone, *Settings::staminaRateString, *Settings::staminaRateStringEnding, *Settings::staminaRate));
			p_vec.push_back(new StatItem(StatsValue::resistDamage, ActorValue::kDamageResist, *Settings::resistDamageString, *Settings::resistDamageStringEnding, *Settings::resistDamage));
			p_vec.push_back(new StatItem(StatsValue::resistDisease, ActorValue::kResistDisease, *Settings::resistDiseaseString, *Settings::resistDiseaseStringEnding, *Settings::resistDisease));
			p_vec.push_back(new StatItem(StatsValue::resistPoison, ActorValue::kPoisonResist, *Settings::restorationModString, *Settings::resistPoisonStringEnding, *Settings::resistPoison));
			p_vec.push_back(new StatItem(StatsValue::resistFire, ActorValue::kResistFire, *Settings::resistFireString, *Settings::resistFireStringEnding, *Settings::resistFire));
			p_vec.push_back(new StatItem(StatsValue::resistShock, ActorValue::kResistShock, *Settings::resistShockString, *Settings::resistShockStringEnding, *Settings::resistShock));
			p_vec.push_back(new StatItem(StatsValue::resistFrost, ActorValue::kResistFrost, *Settings::resistFrostString, *Settings::resistFrostStringEnding, *Settings::resistFrost));
			p_vec.push_back(new StatItem(StatsValue::resistMagic, ActorValue::kResistMagic, *Settings::resistMagicString, *Settings::resistMagicStringEnding, *Settings::resistMagic));
			p_vec.push_back(new StatItem(StatsValue::oneHanded, ActorValue::kOneHanded, *Settings::oneHandedString, *Settings::oneHandedStringEnding, *Settings::oneHanded));
			p_vec.push_back(new StatItem(StatsValue::twoHanded, ActorValue::kTwoHanded, *Settings::twoHandedString, *Settings::twoHandedStringEnding, *Settings::twoHanded));
			p_vec.push_back(new StatItem(StatsValue::archery, ActorValue::kArchery, *Settings::archeryString, *Settings::archeryStringEnding, *Settings::archery));
			p_vec.push_back(new StatItem(StatsValue::block, ActorValue::kBlock, *Settings::blockString, *Settings::blockStringEnding, *Settings::block));
			p_vec.push_back(new StatItem(StatsValue::smithing, ActorValue::kSmithing, *Settings::smithingString, *Settings::smithingStringEnding, *Settings::smithing));
			p_vec.push_back(new StatItem(StatsValue::heavyArmor, ActorValue::kHeavyArmor, *Settings::heavyArmorString, *Settings::heavyArmorStringEnding, *Settings::heavyArmor));
			p_vec.push_back(new StatItem(StatsValue::lightArmor, ActorValue::kLightArmor, *Settings::lightArmorString, *Settings::lightArmorStringEnding, *Settings::lightArmor));
			p_vec.push_back(new StatItem(StatsValue::pickpocket, ActorValue::kPickpocket, *Settings::pickpocketString, *Settings::pickpocketStringEnding, *Settings::pickpocket));
			p_vec.push_back(new StatItem(StatsValue::lockpicking, ActorValue::kLockpicking, *Settings::lockpickingString, *Settings::lockpickingStringEnding, *Settings::lockpicking));
			p_vec.push_back(new StatItem(StatsValue::sneak, ActorValue::kSneak, *Settings::sneakString, *Settings::sneakStringEnding, *Settings::sneak));
			p_vec.push_back(new StatItem(StatsValue::alchemy, ActorValue::kAlchemy, *Settings::alchemyString, *Settings::alchemyStringEnding, *Settings::alchemy));
			p_vec.push_back(new StatItem(StatsValue::speech, ActorValue::kSpeech, *Settings::speechString, *Settings::speechStringEnding, *Settings::speech));
			p_vec.push_back(new StatItem(StatsValue::enchanting, ActorValue::kEnchanting, *Settings::enchantingString, *Settings::enchantingStringEnding, *Settings::enchanting));
			p_vec.push_back(new StatItem(StatsValue::alteration, ActorValue::kAlteration, *Settings::alterationString, *Settings::alterationStringEnding, *Settings::alteration));
			p_vec.push_back(new StatItem(StatsValue::conjuration, ActorValue::kConjuration, *Settings::conjurationString, *Settings::conjurationStringEnding, *Settings::conjuration));
			p_vec.push_back(new StatItem(StatsValue::destruction, ActorValue::kDestruction, *Settings::destructionString, *Settings::destructionStringEnding, *Settings::destruction));
			p_vec.push_back(new StatItem(StatsValue::illusion, ActorValue::kIllusion, *Settings::illusionString, *Settings::illusionStringEnding, *Settings::illusion));
			p_vec.push_back(new StatItem(StatsValue::restoration, ActorValue::kRestoration, *Settings::restorationString, *Settings::restorationStringEnding, *Settings::restoration));
			p_vec.push_back(new StatItem(StatsValue::oneHandedPowerMod, ActorValue::kOneHandedPowerModifier, *Settings::oneHandedPowerModString, *Settings::oneHandedPowerModStringEnding, *Settings::oneHandedPowerMod));
			p_vec.push_back(new StatItem(StatsValue::twoHandedPowerMod, ActorValue::kTwoHandedPowerModifier, *Settings::twoHandedPowerModString, *Settings::twoHandedPowerModStringEnding, *Settings::twoHandedPowerMod));
			p_vec.push_back(new StatItem(StatsValue::archeryPowerMod, ActorValue::kMarksmanPowerModifier, *Settings::archeryPowerModString, *Settings::archeryPowerModStringEnding, *Settings::archeryPowerMod));
			p_vec.push_back(new StatItem(StatsValue::blockPowerMod, ActorValue::kBlockPowerModifier, *Settings::blockPowerModString, *Settings::blockPowerModStringEnding, *Settings::blockPowerMod));
			p_vec.push_back(new StatItem(StatsValue::smithingPowerMod, ActorValue::kSmithingPowerModifier, *Settings::smithingPowerModString, *Settings::smithingPowerModStringEnding, *Settings::smithingPowerMod));
			p_vec.push_back(new StatItem(StatsValue::heavyArmorPowerMod, ActorValue::kHeavyArmorPowerModifier, *Settings::heavyArmorPowerModString, *Settings::heavyArmorPowerModStringEnding, *Settings::heavyArmorPowerMod));
			p_vec.push_back(new StatItem(StatsValue::lightArmorPowerMod, ActorValue::kLightArmorPowerModifier, *Settings::lightArmorPowerModString, *Settings::lightArmorPowerModStringEnding, *Settings::lightArmorPowerMod));
			p_vec.push_back(new StatItem(StatsValue::pickpocketPowerMod, ActorValue::kPickpocketPowerModifier, *Settings::pickpocketPowerModString, *Settings::pickpocketPowerModStringEnding, *Settings::pickpocketPowerMod));
			p_vec.push_back(new StatItem(StatsValue::lockpickingPowerMod, ActorValue::kLockpickingPowerModifier, *Settings::lockpickingPowerModString, *Settings::lockpickingPowerModStringEnding, *Settings::lockpickingPowerMod));
			p_vec.push_back(new StatItem(StatsValue::sneakPowerMod, ActorValue::kSneakingPowerModifier, *Settings::sneakPowerModString, *Settings::sneakPowerModStringEnding, *Settings::sneakPowerMod));
			p_vec.push_back(new StatItem(StatsValue::alchemyPowerMod, ActorValue::kAlchemyPowerModifier, *Settings::alchemyPowerModString, *Settings::alchemyPowerModStringEnding, *Settings::alchemyPowerMod));
			p_vec.push_back(new StatItem(StatsValue::speechPowerMod, ActorValue::kSpeechcraftPowerModifier, *Settings::speechPowerModString, *Settings::speechPowerModStringEnding, *Settings::speechPowerMod));
			p_vec.push_back(new StatItem(StatsValue::enchantingPowerMod, ActorValue::kEnchantingPowerModifier, *Settings::enchantingPowerModString, *Settings::enchantingPowerModStringEnding, *Settings::enchantingPowerMod));
			p_vec.push_back(new StatItem(StatsValue::alterationPowerMod, ActorValue::kAlterationPowerModifier, *Settings::alterationPowerModString, *Settings::alterationPowerModStringEnding, *Settings::alterationPowerMod));
			p_vec.push_back(new StatItem(StatsValue::conjurationPowerMod, ActorValue::kConjurationPowerModifier, *Settings::conjurationPowerModString, *Settings::conjurationPowerModStringEnding, *Settings::conjurationPowerMod));
			p_vec.push_back(new StatItem(StatsValue::destructionPowerMod, ActorValue::kDestructionPowerModifier, *Settings::destructionPowerModString, *Settings::destructionPowerModStringEnding, *Settings::destructionPowerMod));
			p_vec.push_back(new StatItem(StatsValue::illusionPowerMod, ActorValue::kIllusionPowerModifier, *Settings::illusionPowerModString, *Settings::illusionPowerModStringEnding, *Settings::illusionPowerMod));
			p_vec.push_back(new StatItem(StatsValue::restorationPowerMod, ActorValue::kRestorationPowerModifier, *Settings::restorationPowerModString, *Settings::restorationPowerModStringEnding, *Settings::restorationPowerMod));
			p_vec.push_back(new StatItem(StatsValue::speedMult, ActorValue::kSpeedMult, *Settings::speedMultString, *Settings::speedMultStringEnding, *Settings::speedMult));
			p_vec.push_back(new StatItem(StatsValue::inventoryWeight, ActorValue::kInventoryWeight, *Settings::inventoryWeightString, *Settings::inventoryWeightStringEnding, *Settings::inventoryWeight));
			p_vec.push_back(new StatItem(StatsValue::carryWeight, ActorValue::kCarryWeight, *Settings::carryWeightString, *Settings::carryWeightStringEnding, *Settings::carryWeight));
			p_vec.push_back(new StatItem(StatsValue::criticalChance, ActorValue::kCriticalChance, *Settings::criticalChanceString, *Settings::criticalChanceStringEnding, *Settings::criticalChance));
			p_vec.push_back(new StatItem(StatsValue::meleeDamage, ActorValue::kMeleeDamage, *Settings::meleeDamageString, *Settings::meleeDamageStringEnding, *Settings::meleeDamage));
			p_vec.push_back(new StatItem(StatsValue::unarmedDamage, ActorValue::kUnarmedDamage, *Settings::unarmedDamageString, *Settings::unarmedDamageStringEnding, *Settings::unarmedDamage));
			p_vec.push_back(new StatItem(StatsValue::absorbChance, ActorValue::kAbsorbChance, *Settings::absorbChanceString, *Settings::absorbChanceStringEnding, *Settings::absorbChance));
			//we will not set the actor value kWeaponSpeedMult and kLeftWeaponSpeedMultiply here, because some genius thought it is nice that the value 0 and 1 means 100%
			// https://en.uesp.net/wiki/Skyrim_Mod:Actor_Value_Indices as documented here
			p_vec.push_back(new StatItem(StatsValue::weaponSpeedMult, ActorValue::kNone, *Settings::weaponSpeedMultString, *Settings::weaponSpeedMultStringEnding, *Settings::weaponSpeedMult));
			p_vec.push_back(new StatItem(StatsValue::leftWeaponSpeedMult, ActorValue::kNone, *Settings::leftWeaponSpeedMultString, *Settings::leftWeaponSpeedMultStringEnding, *Settings::leftWeaponSpeedMult));
			p_vec.push_back(new StatItem(StatsValue::rightItemCharge, ActorValue::kRightItemCharge, *Settings::rightItemChargeString, *Settings::rightItemChargeStringEnding, *Settings::rightItemCharge));
			p_vec.push_back(new StatItem(StatsValue::leftItemCharge, ActorValue::kLeftItemCharge, *Settings::leftItemChargStringe, *Settings::leftItemChargStringeEnding, *Settings::leftItemCharge));
			p_vec.push_back(new StatItem(StatsValue::armorPerks, ActorValue::kArmorPerks, *Settings::armorPerksString, *Settings::damageArrowStringEnding, *Settings::armorPerks));
			p_vec.push_back(new StatItem(StatsValue::mass, ActorValue::kMass, *Settings::massString, *Settings::massStringEnding, *Settings::mass));
			p_vec.push_back(new StatItem(StatsValue::bowStaggerBonus, ActorValue::kBowStaggerBonus, *Settings::bowStaggerBonusString, *Settings::bowStaggerBonusStringEnding, *Settings::bowStaggerBonus));
			p_vec.push_back(new StatItem(StatsValue::bypassVendorKeywordCheck, ActorValue::kBypassVendorKeywordCheck, *Settings::bypassVendorKeywordCheckString, *Settings::bypassVendorKeywordCheckStringEnding, *Settings::bypassVendorKeywordCheck));
			p_vec.push_back(new StatItem(StatsValue::bypassVendorStolenCheck, ActorValue::kBypassVendorStolenCheck, *Settings::bypassVendorStolenCheckString, *Settings::bypassVendorStolenCheckStringEnding, *Settings::bypassVendorStolenCheck));
			p_vec.push_back(new StatItem(StatsValue::bowSpeedBonus, ActorValue::kBowSpeedBonus, *Settings::bowSpeedBonusString, *Settings::bowSpeedBonusStringEnding, *Settings::bowSpeedBonus));
			p_vec.push_back(new StatItem(StatsValue::shoutRecoveryMult, ActorValue::kShoutRecoveryMult, *Settings::shoutRecoveryMultString, *Settings::shoutRecoveryMultStringEnding, *Settings::shoutRecoveryMult));
			p_vec.push_back(new StatItem(StatsValue::movementNoiseMult, ActorValue::kMovementNoiseMult, *Settings::movementNoiseMultString, *Settings::movementNoiseMultStringEnding, *Settings::movementNoiseMult));
			p_vec.push_back(new StatItem(StatsValue::dragonSouls, ActorValue::kDragonSouls, *Settings::dragonSoulsString, *Settings::dragonSoulsStringEnding, *Settings::dragonSouls));
			p_vec.push_back(new StatItem(StatsValue::combatHealthRegenMultiply, ActorValue::kCombatHealthRegenMultiply, *Settings::combatHealthRegenMultiplyString, *Settings::combatHealthRegenMultiplyStringEnding, *Settings::combatHealthRegenMultiply));
			p_vec.push_back(new StatItem(StatsValue::attackDamageMult, ActorValue::kAttackDamageMult, *Settings::attackDamageMultString, *Settings::attackDamageMultStringEnding, *Settings::attackDamageMult));
			p_vec.push_back(new StatItem(StatsValue::beast, ActorValue::kNone, *Settings::beastString, *Settings::beastStringEnding, *Settings::beast));
			p_vec.push_back(new StatItem(StatsValue::xp, ActorValue::kNone, *Settings::xpString, *Settings::xpStringEnding, *Settings::xp, true));
			p_vec.push_back(new StatItem(StatsValue::reflectDamage, ActorValue::kReflectDamage, *Settings::reflectDamageString, *Settings::reflectDamageStringEnding, *Settings::reflectDamage));
			p_vec.push_back(new StatItem(StatsValue::oneHandedMod, ActorValue::kOneHandedModifier, *Settings::oneHandedModString, *Settings::oneHandedModStringEnding, *Settings::oneHandedMod));
			p_vec.push_back(new StatItem(StatsValue::twoHandedMod, ActorValue::kTwoHandedModifier, *Settings::twoHandedModString, *Settings::twoHandedModStringEnding, *Settings::twoHandedMod));
			p_vec.push_back(new StatItem(StatsValue::marksmanMod, ActorValue::kMarksmanModifier, *Settings::archeryModString, *Settings::archeryModStringEnding, *Settings::archeryMod));
			p_vec.push_back(new StatItem(StatsValue::blockMod, ActorValue::kBlockModifier, *Settings::blockModString, *Settings::blockModStringEnding, *Settings::blockMod));
			p_vec.push_back(new StatItem(StatsValue::smithingMod, ActorValue::kSmithingModifier, *Settings::smithingModString, *Settings::smithingModStringEnding, *Settings::smithingMod));
			p_vec.push_back(new StatItem(StatsValue::heavyArmorMod, ActorValue::kHeavyArmorModifier, *Settings::heavyArmorModString, *Settings::heavyArmorModStringEnding, *Settings::heavyArmorMod));
			p_vec.push_back(new StatItem(StatsValue::lightArmorMod, ActorValue::kLightArmorModifier, *Settings::lightArmorModString, *Settings::lightArmorModStringEnding, *Settings::lightArmorMod));
			p_vec.push_back(new StatItem(StatsValue::pickpocketMod, ActorValue::kPickpocketModifier, *Settings::pickpocketModString, *Settings::pickpocketModStringEnding, *Settings::pickpocketMod));
			p_vec.push_back(new StatItem(StatsValue::lockpickingMod, ActorValue::kLockpickingModifier, *Settings::lockpickingModString, *Settings::lockpickingModStringEnding, *Settings::lockpickingMod));
			p_vec.push_back(new StatItem(StatsValue::sneakingMod, ActorValue::kSneakingModifier, *Settings::sneakModString, *Settings::sneakModStringEnding, *Settings::sneakMod));
			p_vec.push_back(new StatItem(StatsValue::alchemyMod, ActorValue::kAlchemyModifier, *Settings::alchemyModString, *Settings::alchemyModStringEnding, *Settings::alchemyMod));
			p_vec.push_back(new StatItem(StatsValue::speechcraftMod, ActorValue::kSpeechcraftModifier, *Settings::speechModString, *Settings::speechModStringEnding, *Settings::speechMod));
			p_vec.push_back(new StatItem(StatsValue::enchantingMod, ActorValue::kEnchantingModifier, *Settings::enchantingModString, *Settings::enchantingModStringEnding, *Settings::enchantingMod));
			p_vec.push_back(new StatItem(StatsValue::alterationMod, ActorValue::kAlterationModifier, *Settings::alterationModString, *Settings::alterationModStringEnding, *Settings::alterationMod));
			p_vec.push_back(new StatItem(StatsValue::conjurationMod, ActorValue::kConjurationModifier, *Settings::conjurationModString, *Settings::conjurationModStringEnding, *Settings::conjurationMod));
			p_vec.push_back(new StatItem(StatsValue::destructionMod, ActorValue::kDestructionModifier, *Settings::destructionModString, *Settings::destructionModStringEnding, *Settings::destructionMod));
			p_vec.push_back(new StatItem(StatsValue::illusionMod, ActorValue::kIllusionModifier, *Settings::illusionModString, *Settings::illusionModStringEnding, *Settings::illusionMod));
			p_vec.push_back(new StatItem(StatsValue::restorationMod, ActorValue::kRestorationModifier, *Settings::restorationModString, *Settings::restorationModStringEnding, *Settings::restorationMod));
			p_vec.push_back(new StatItem(StatsValue::damageArrow, ActorValue::kNone, *Settings::damageArrowString, *Settings::damageArrowStringEnding, *Settings::damageArrow));
			p_vec.push_back(new StatItem(StatsValue::damageLeft, ActorValue::kNone, *Settings::damageLeftString, *Settings::damageLeftStringEnding, *Settings::damageLeft));
			p_vec.push_back(new StatItem(StatsValue::darkbrotherHood, ActorValue::kNone, "", "", false));
			p_vec.push_back(new StatItem(StatsValue::thiefsGuild, ActorValue::kNone, "", "", false));
			p_vec.push_back(new StatItem(StatsValue::orcFriend, ActorValue::kNone, "", "", false));
			p_vec.push_back(new StatItem(StatsValue::collegeOfWinterhold, ActorValue::kNone, "", "", false));
			p_vec.push_back(new StatItem(StatsValue::companions, ActorValue::kNone, "", "", false));
			p_vec.push_back(new StatItem(StatsValue::imperialLegion, ActorValue::kNone, "", "", false));
			p_vec.push_back(new StatItem(StatsValue::stormcloaks, ActorValue::kNone, "", "", false));
			p_vec.push_back(new StatItem(StatsValue::greybeard, ActorValue::kNone, "", "", false));
		}

		void PrintStatsVector(vector<StatItem*>& p_vec) {
			logger::debug("Vector Size is {}"sv, p_vec.size());
			for (auto& element : p_vec) {
				logger::trace("name {}, actor {}, value {}, displayname ({}), ending {}, show {}, guiText ({}), ST {}"sv,
					element->getName(),
					element->getActor(),
					element->getValue(),
					element->getDisplayName(),
					element->getEnding(),
					element->getShow(),
					element->getGuiText(),
					element->getStaticText()
				);
			}
		}
	};
}