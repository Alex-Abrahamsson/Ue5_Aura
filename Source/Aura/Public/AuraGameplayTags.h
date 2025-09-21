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

	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;
	FGameplayTag InputTag_4;
	FGameplayTag InputTag_5;

	FGameplayTag Damage;

private:
	static FAuraGameplayTags GameplayTags;
};
