#pragma once
#include "constants.h"

class Player
{
public:
	static Player* GetSingleton();

	constants::ValueMap getValues();

	std::string getValueName(constants::StatsValue p_val);

private:
	constants::ValueMap GatherValues();
	void PrintValues(constants::ValueMap& p_map);

	static const inline constants::ActorMap staticValues = {
		{ constants::health, RE::ActorValue::kHealth },
		{ constants::healthRate, RE::ActorValue::kHealRate },
		{ constants::healthRateMult, RE::ActorValue::kHealRateMult },
		{ constants::magicka, RE::ActorValue::kMagicka },
		{ constants::magickaRate, RE::ActorValue::kMagickaRate },
		{ constants::magickaRateMult, RE::ActorValue::kMagickaRateMult },
		{ constants::stamina, RE::ActorValue::kStamina },
		{ constants::staminaRate, RE::ActorValue::kStaminaRateMult },
		{ constants::staminaRateMult, RE::ActorValue::kStaminaRateMult },

		{ constants::resistDamage, RE::ActorValue::kDamageResist },
		{ constants::resistDisease, RE::ActorValue::kResistDisease },
		{ constants::resistPoison, RE::ActorValue::kPoisonResist },
		{ constants::resistFire, RE::ActorValue::kResistFire },
		{ constants::resistShock, RE::ActorValue::kResistShock },
		{ constants::resistFrost, RE::ActorValue::kResistFrost },
		{ constants::resistMagic, RE::ActorValue::kResistMagic },

		{ constants::oneHanded, RE::ActorValue::kOneHanded },
		{ constants::twoHanded, RE::ActorValue::kTwoHanded },
		{ constants::archery, RE::ActorValue::kArchery },
		{ constants::block, RE::ActorValue::kBlock },
		{ constants::smithing, RE::ActorValue::kSmithing },
		{ constants::heavyArmor, RE::ActorValue::kHeavyArmor },
		{ constants::lightArmor, RE::ActorValue::kLightArmor },
		{ constants::pickpocket, RE::ActorValue::kPickpocket },
		{ constants::lockpicking, RE::ActorValue::kLockpicking },
		{ constants::sneak, RE::ActorValue::kSneak },
		{ constants::alchemy, RE::ActorValue::kAlchemy },
		{ constants::speech, RE::ActorValue::kSpeech },
		{ constants::enchanting, RE::ActorValue::kEnchanting },
		{ constants::alteration, RE::ActorValue::kAlteration },
		{ constants::conjuration, RE::ActorValue::kConjuration },
		{ constants::destruction, RE::ActorValue::kDestruction },
		{ constants::illusion, RE::ActorValue::kIllusion },
		{ constants::restoration, RE::ActorValue::kRestoration },

		{ constants::oneHandedPowerMod, RE::ActorValue::kOneHandedPowerModifier },
		{ constants::twoHandedPowerMod, RE::ActorValue::kTwoHandedPowerModifier },
		{ constants::archeryPowerMod, RE::ActorValue::kMarksmanPowerModifier },
		{ constants::blockPowerMod, RE::ActorValue::kBlockPowerModifier },
		{ constants::smithingPowerMod, RE::ActorValue::kSmithingPowerModifier },
		{ constants::heavyArmorPowerMod, RE::ActorValue::kHeavyArmorPowerModifier },
		{ constants::lightArmorPowerMod, RE::ActorValue::kLightArmorPowerModifier },
		{ constants::pickpocketPowerMod, RE::ActorValue::kPickpocketPowerModifier },
		{ constants::lockpickingPowerMod, RE::ActorValue::kLockpickingPowerModifier },
		{ constants::sneakPowerMod, RE::ActorValue::kSneakingPowerModifier },
		{ constants::alchemyPowerMod, RE::ActorValue::kAlchemyPowerModifier },
		{ constants::speechPowerMod, RE::ActorValue::kSpeechcraftPowerModifier },
		{ constants::enchantingPowerMod, RE::ActorValue::kEnchantingPowerModifier },
		{ constants::alterationPowerMod, RE::ActorValue::kAlterationPowerModifier },
		{ constants::conjurationPowerMod, RE::ActorValue::kConjurationPowerModifier },
		{ constants::destructionPowerMod, RE::ActorValue::kDestructionPowerModifier },
		{ constants::illusionPowerMod, RE::ActorValue::kIllusionPowerModifier },
		{ constants::restorationPowerMod, RE::ActorValue::kRestorationPowerModifier },

		{ constants::speedMult, RE::ActorValue::kSpeedMult },
		{ constants::inventoryWeight, RE::ActorValue::kInventoryWeight },
		{ constants::carryWeight, RE::ActorValue::kCarryWeight },
		{ constants::criticalChance, RE::ActorValue::kCriticalChance },
		{ constants::meleeDamage, RE::ActorValue::kMeleeDamage },
		{ constants::unarmedDamage, RE::ActorValue::kUnarmedDamage },
		{ constants::absorbChance, RE::ActorValue::kAbsorbChance },
		{ constants::weaponSpeedMult, RE::ActorValue::kWeaponSpeedMult },
		{ constants::bowSpeedBonus, RE::ActorValue::kBowSpeedBonus },
		{ constants::shoutRecoveryMult, RE::ActorValue::kShoutRecoveryMult },
		{ constants::movementNoiseMult, RE::ActorValue::kMovementNoiseMult },
		{ constants::dragonSouls, RE::ActorValue::kDragonSouls },
		{ constants::combatHealthRegenMultiply, RE::ActorValue::kCombatHealthRegenMultiply },
		{ constants::attackDamageMult, RE::ActorValue::kAttackDamageMult }
	};

	std::string getStringValueFromFloat(float x);

	constants::ShowMap showMap;
	constants::StatsValueMap nameMap;
	void loadSettings();

	boolean showValue(constants::StatsValue p_val);

	void addToValues(constants::ValueMap& p_map, constants::StatsValue p_key, std::string p_value);

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