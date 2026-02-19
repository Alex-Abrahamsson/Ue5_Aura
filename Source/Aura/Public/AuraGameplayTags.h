// Copyright AbraCode

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * AuraGameplayTags
 *
 * Sigleton containing native gameplay Tags
 */


struct  FAuraGameplayTags
{
public:
	static const FAuraGameplayTags& Get() { return  GameplayTags; }
	static void InitializeGameplayTags();

	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Dexterity;
	FGameplayTag Attributes_Primary_Vitality;
	FGameplayTag Attributes_Primary_Energy;

	FGameplayTag Attributes_Secondary_MaxHealth;
	FGameplayTag Attributes_Secondary_MaxMana;
	FGameplayTag Attributes_Secondary_MaxStamina;
	FGameplayTag Attributes_Secondary_Armor;
	FGameplayTag Attributes_Secondary_ArmorPenetration;
	FGameplayTag Attributes_Secondary_BlockChance;
	FGameplayTag Attributes_Secondary_CriticalHitChance;
	FGameplayTag Attributes_Secondary_CriticalHitDamage;
	FGameplayTag Attributes_Secondary_CriticalHitResistance;
	FGameplayTag Attributes_Secondary_HealthRegeneration;
	FGameplayTag Attributes_Secondary_ManaRegeneration;
	FGameplayTag Attributes_Secondary_StaminaRegeneration;
	//Diablo2
	FGameplayTag Attributes_Secondary_Evasion;
	FGameplayTag Attributes_Secondary_AttackRating;
	FGameplayTag Attributes_Secondary_DefenseRating;
	FGameplayTag Attributes_Secondary_FreezeImmunity;
	FGameplayTag Attributes_Secondary_StunResistance;
	FGameplayTag Attributes_Secondary_LifeSteal;
	FGameplayTag Attributes_Secondary_ManaSteal;
	
	FGameplayTag Attributes_Resistance_Fire;
	FGameplayTag Attributes_Resistance_Cold;
	FGameplayTag Attributes_Resistance_Lightning;
	FGameplayTag Attributes_Resistance_Poison;
	FGameplayTag Attributes_Resistance_Magic;
	FGameplayTag Attributes_Resistance_Physical;

	//Meta Attributes
	FGameplayTag Attributes_Meta_IncomingXP;

	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;
	FGameplayTag InputTag_4;
	FGameplayTag InputTag_5;

	FGameplayTag Damage;
	//Diablo 2
	FGameplayTag Damage_Fire;
	FGameplayTag Damage_Cold;
	FGameplayTag Damage_Lightning;
	FGameplayTag Damage_Poison;
	FGameplayTag Damage_Physical;
	FGameplayTag Damage_Magic;

	/* Ability Tags */
	FGameplayTag Abilities_Attack;
	FGameplayTag Abilities_Summon;
	FGameplayTag Abilities_Fire_FireBolt;
	/* Cooldown Tags */
	FGameplayTag Cooldown_Cold_Blizzard;
	FGameplayTag Cooldown_Cold_Frozen_Orb;
	FGameplayTag Cooldown_Fire_Firewall;
	FGameplayTag Cooldown_Fire_Meteor;
	FGameplayTag Cooldown_Poison_Poison_Javelin;
	FGameplayTag Cooldown_Poison_Plague_Javelin;
	FGameplayTag Cooldown_Fire_Immolation_Arrow;
	FGameplayTag Cooldown_Summon_Valkyrie;
	FGameplayTag Cooldown_Shadow_Shadow_Warrior;
	FGameplayTag Cooldown_Shadow_Shadow_Master;
	FGameplayTag Cooldown_Lightning_Shock_Web;
	FGameplayTag Cooldown_Trap_Blade_Sentinel;
	FGameplayTag Cooldown_Fire_Firestorm;
	FGameplayTag Cooldown_Fire_Molten_Boulder;
	FGameplayTag Cooldown_Fire_Fissure;
	FGameplayTag Cooldown_Fire_Volcano;
	FGameplayTag Cooldown_Holy_Fist_of_the_Heavens;

	FGameplayTag CombatSocket_Weapon;
	FGameplayTag CombatSocket_RightHand;
	FGameplayTag CombatSocket_LeftHand;
	FGameplayTag CombatSocket_Tail;

	FGameplayTag Montage_Attack_1;
	FGameplayTag Montage_Attack_2;
	FGameplayTag Montage_Attack_3;
	FGameplayTag Montage_Attack_4;

	TMap<FGameplayTag, FGameplayTag> DamageTypesToResistances;

	FGameplayTag SkillType_Melee;
	FGameplayTag SkillType_Spell;
	FGameplayTag SkillType_Ranged;


	FGameplayTag Effects_HitReact;
	// Diablo 2
	FGameplayTag Effects_Poisoned;
	FGameplayTag Effects_Frozen;
	FGameplayTag Effects_Slowed;
	FGameplayTag Effects_Stunned;
	FGameplayTag Effects_Burning;


private:
	static FAuraGameplayTags GameplayTags;
};
