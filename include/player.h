#pragma once
#include "constants.h"

class Player
{
public:
	static Player* GetSingleton();

	constants::ValueMap getValues();

	std::string getValueName(constants::StatsValue p_val);

private:
	using Stats = constants::StatsValue;

	constants::ValueMap GatherValues();

	void PrintValues(constants::ValueMap& p_map);

	static const inline constants::ActorMap staticValues = {
		{ Stats::health, RE::ActorValue::kHealth },
		{ Stats::magicka, RE::ActorValue::kMagicka },
		{ Stats::stamina, RE::ActorValue::kStamina },

		{ Stats::resistDamage, RE::ActorValue::kDamageResist },
		{ Stats::resistDisease, RE::ActorValue::kResistDisease },
		{ Stats::resistPoison, RE::ActorValue::kPoisonResist },
		{ Stats::resistFire, RE::ActorValue::kResistFire },
		{ Stats::resistShock, RE::ActorValue::kResistShock },
		{ Stats::resistFrost, RE::ActorValue::kResistFrost },
		{ Stats::resistMagic, RE::ActorValue::kResistMagic },

		{ Stats::oneHanded, RE::ActorValue::kOneHanded },
		{ Stats::twoHanded, RE::ActorValue::kTwoHanded },
		{ Stats::archery, RE::ActorValue::kArchery },
		{ Stats::block, RE::ActorValue::kBlock },
		{ Stats::smithing, RE::ActorValue::kSmithing },
		{ Stats::heavyArmor, RE::ActorValue::kHeavyArmor },
		{ Stats::lightArmor, RE::ActorValue::kLightArmor },
		{ Stats::pickpocket, RE::ActorValue::kPickpocket },
		{ Stats::lockpicking, RE::ActorValue::kLockpicking },
		{ Stats::sneak, RE::ActorValue::kSneak },
		{ Stats::alchemy, RE::ActorValue::kAlchemy },
		{ Stats::speech, RE::ActorValue::kSpeech },
		{ Stats::enchanting, RE::ActorValue::kEnchanting },
		{ Stats::alteration, RE::ActorValue::kAlteration },
		{ Stats::conjuration, RE::ActorValue::kConjuration },
		{ Stats::destruction, RE::ActorValue::kDestruction },
		{ Stats::illusion, RE::ActorValue::kIllusion },
		{ Stats::restoration, RE::ActorValue::kRestoration },

		{ Stats::oneHandedPowerMod, RE::ActorValue::kOneHandedPowerModifier },
		{ Stats::twoHandedPowerMod, RE::ActorValue::kTwoHandedPowerModifier },
		{ Stats::archeryPowerMod, RE::ActorValue::kMarksmanPowerModifier },
		{ Stats::blockPowerMod, RE::ActorValue::kBlockPowerModifier },
		{ Stats::smithingPowerMod, RE::ActorValue::kSmithingPowerModifier },
		{ Stats::heavyArmorPowerMod, RE::ActorValue::kHeavyArmorPowerModifier },
		{ Stats::lightArmorPowerMod, RE::ActorValue::kLightArmorPowerModifier },
		{ Stats::pickpocketPowerMod, RE::ActorValue::kPickpocketPowerModifier },
		{ Stats::lockpickingPowerMod, RE::ActorValue::kLockpickingPowerModifier },
		{ Stats::sneakPowerMod, RE::ActorValue::kSneakingPowerModifier },
		{ Stats::alchemyPowerMod, RE::ActorValue::kAlchemyPowerModifier },
		{ Stats::speechPowerMod, RE::ActorValue::kSpeechcraftPowerModifier },
		{ Stats::enchantingPowerMod, RE::ActorValue::kEnchantingPowerModifier },
		{ Stats::alterationPowerMod, RE::ActorValue::kAlterationPowerModifier },
		{ Stats::conjurationPowerMod, RE::ActorValue::kConjurationPowerModifier },
		{ Stats::destructionPowerMod, RE::ActorValue::kDestructionPowerModifier },
		{ Stats::illusionPowerMod, RE::ActorValue::kIllusionPowerModifier },
		{ Stats::restorationPowerMod, RE::ActorValue::kRestorationPowerModifier },

		{ Stats::speedMult, RE::ActorValue::kSpeedMult },
		{ Stats::inventoryWeight, RE::ActorValue::kInventoryWeight },
		{ Stats::carryWeight, RE::ActorValue::kCarryWeight },
		{ Stats::criticalChance, RE::ActorValue::kCriticalChance },
		{ Stats::meleeDamage, RE::ActorValue::kMeleeDamage },
		{ Stats::unarmedDamage, RE::ActorValue::kUnarmedDamage },
		{ Stats::absorbChance, RE::ActorValue::kAbsorbChance },
		{ Stats::weaponSpeedMult, RE::ActorValue::kWeaponSpeedMult },
		{ Stats::bowSpeedBonus, RE::ActorValue::kBowSpeedBonus },
		{ Stats::shoutRecoveryMult, RE::ActorValue::kShoutRecoveryMult },
		{ Stats::movementNoiseMult, RE::ActorValue::kMovementNoiseMult },
		{ Stats::dragonSouls, RE::ActorValue::kDragonSouls },
		{ Stats::combatHealthRegenMultiply, RE::ActorValue::kCombatHealthRegenMultiply },
		{ Stats::attackDamageMult, RE::ActorValue::kAttackDamageMult },
		{ Stats::reflectDamage, RE::ActorValue::kReflectDamage },

		{ Stats::oneHandedMod, RE::ActorValue::kOneHandedModifier },
		{ Stats::twoHandedMod, RE::ActorValue::kTwoHandedModifier },
		{ Stats::marksmanMod, RE::ActorValue::kMarksmanModifier },
		{ Stats::blockMod, RE::ActorValue::kBlockModifier },
		{ Stats::smithingMod, RE::ActorValue::kSmithingModifier },
		{ Stats::heavyArmorMod, RE::ActorValue::kHeavyArmorModifier },
		{ Stats::lightArmorMod, RE::ActorValue::kLightArmorModifier },
		{ Stats::pickpocketMod, RE::ActorValue::kPickpocketModifier },
		{ Stats::lockpickingMod, RE::ActorValue::kLockpickingModifier },
		{ Stats::sneakingMod, RE::ActorValue::kSneakingModifier },
		{ Stats::alchemyMod, RE::ActorValue::kAlchemyModifier },
		{ Stats::speechcraftMod, RE::ActorValue::kSpeechcraftModifier },
		{ Stats::alterationMod, RE::ActorValue::kAlterationModifier },
		{ Stats::conjurationMod, RE::ActorValue::kConjurationModifier },
		{ Stats::destructionMod, RE::ActorValue::kDestructionModifier },
		{ Stats::illusionMod, RE::ActorValue::kIllusionModifier },
		{ Stats::restorationMod, RE::ActorValue::kRestorationModifier },
		{ Stats::enchantingMod, RE::ActorValue::kEnchantingModifier }

	};

	std::string getStringValueFromFloat(float x);

	constants::ShowMap showMap;
	constants::StatsValueMap nameMap;
	void loadSettings();

	boolean showValue(constants::StatsValue p_val);

	void addToValues(constants::ValueMap& p_map, constants::StatsValue p_key, std::string p_value);

	float calculateValue(float p_rm, float p_r);

	std::string getBeast(float p_vamp, float p_were);

	using Lock = std::recursive_mutex;
	using Locker = std::lock_guard<Lock>;

	Player();
	Player(const Player&) = delete;
	Player(Player&&) = delete;
	~Player() = default;

	Player& operator=(const Player&) = delete;
	Player& operator=(Player&&) = delete;

	mutable Lock _lock;
};