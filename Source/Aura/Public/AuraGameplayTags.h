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

	FGameplayTag Abilities_Attack;

	FGameplayTag Montage_Attack_Weapon;
	FGameplayTag Montage_Attack_RightHand;
	FGameplayTag Montage_Attack_LeftHand;

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
