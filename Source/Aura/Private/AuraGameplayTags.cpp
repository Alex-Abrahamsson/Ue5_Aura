// Copyright AbraCode

#include "AuraGameplayTags.h"
#include "GameplayTagsManager.h"

FAuraGameplayTags FAuraGameplayTags::GameplayTags;

void FAuraGameplayTags::InitializeGameplayTags()
{
	// Primary Attributes
	GameplayTags.Attributes_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Strength"), FString("Increases physical power and melee damage"));

	GameplayTags.Attributes_Primary_Dexterity = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Dexterity"), FString("Improves accuracy, evasion, and ranged damage"));

	GameplayTags.Attributes_Primary_Vitality = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Vitality"), FString("Boosts health and stamina"));

	GameplayTags.Attributes_Primary_Energy = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Energy"), FString("Enhances mana and magical abilities"));

	// Secondary Attributes
	GameplayTags.Attributes_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxHealth"), FString("Determines maximum health capacity"));

	GameplayTags.Attributes_Secondary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxMana"), FString("Determines maximum mana capacity"));

	GameplayTags.Attributes_Secondary_MaxStamina = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxStamina"), FString("Determines maximum stamina capacity"));

	GameplayTags.Attributes_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.Armor"), FString("Reduces damage taken, improves Block Chance"));

	GameplayTags.Attributes_Secondary_ArmorPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.ArmorPenetration"), FString("Ignores a portion of enemy armor"));

	GameplayTags.Attributes_Secondary_BlockChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.BlockChance"), FString("Chance to block incoming attacks"));

	GameplayTags.Attributes_Secondary_CriticalHitChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalHitChance"), FString("Chance to deal critical damage"));

	GameplayTags.Attributes_Secondary_CriticalHitDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalHitDamage"), FString("Bonus damage dealt on critical hits"));

	GameplayTags.Attributes_Secondary_CriticalHitResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalHitResistance"), FString("Reduces chance and damage of incoming critical hits"));

	GameplayTags.Attributes_Secondary_HealthRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.HealthRegeneration"), FString("Rate at which health regenerates over time"));

	GameplayTags.Attributes_Secondary_ManaRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.ManaRegeneration"), FString("Rate at which mana regenerates over time"));

	GameplayTags.Attributes_Secondary_StaminaRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.StaminaRegeneration"), FString("Rate at which stamina regenerates over time"));

	// Diablo 2 Secondary Attributes
	GameplayTags.Attributes_Secondary_Evasion = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.Evasion"), FString("Chance to dodge incoming attacks"));

	GameplayTags.Attributes_Secondary_AttackRating = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.AttackRating"), FString("Increases chance to hit enemies"));

	GameplayTags.Attributes_Secondary_DefenseRating = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.DefenseRating"), FString("Reduces chance of being hit by enemies"));

	GameplayTags.Attributes_Secondary_FreezeImmunity = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.FreezeImmunity"), FString("Prevents or reduces duration of being frozen"));

	GameplayTags.Attributes_Secondary_StunResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.StunResistance"), FString("Reduces chance and duration of being stunned"));

	GameplayTags.Attributes_Secondary_LifeSteal = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.LifeSteal"), FString("Restores health based on damage dealt"));

	GameplayTags.Attributes_Secondary_ManaSteal = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.ManaSteal"), FString("Restores mana based on damage dealt"));

	GameplayTags.Attributes_Resistance_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Fire"), FString("Reduces damage taken from fire-based attacks"));

	GameplayTags.Attributes_Resistance_Cold = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Cold"), FString("Reduces damage taken from cold-based attacks"));

	GameplayTags.Attributes_Resistance_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Lightning"), FString("Reduces damage taken from lightning-based attacks"));

	GameplayTags.Attributes_Resistance_Poison = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Poison"), FString("Reduces damage taken from poison-based attacks"));

	GameplayTags.Attributes_Resistance_Magic = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Magic"), FString("Reduces damage taken from magic-based attacks"));

	GameplayTags.Attributes_Resistance_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Resistance.Physical"), FString("Reduces damage taken from physical-based attacks"));
	
	// Input Tags
	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.LMB"), FString("Input tag for left mouse button"));

	GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.RMB"), FString("Input tag for right mouse button"));

	GameplayTags.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.1"), FString("Input tag for key 1"));

	GameplayTags.InputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.2"), FString("Input tag for key 2"));

	GameplayTags.InputTag_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.3"), FString("Input tag for key 3"));

	GameplayTags.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.4"), FString("Input tag for key 4"));

	GameplayTags.InputTag_5 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.5"), FString("Input tag for key 5"));

	// Damage Types
	GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage"), FString("Generic damage"));
	
	GameplayTags.Damage_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Fire"), FString("Fire-based damage"));

	GameplayTags.Damage_Cold = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Cold"), FString("Cold-based damage"));

	GameplayTags.Damage_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Lightning"), FString("Lightning-based damage"));

	GameplayTags.Damage_Poison = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Poison"), FString("Poison-based damage"));

	GameplayTags.Damage_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Physical"), FString("Physical-based damage"));

	GameplayTags.Damage_Magic = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Magic"), FString("Magic-based damage"));

	// Abilities
	GameplayTags.Abilities_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Abilities.Attack"), FString("Attack ability tag"));

	// SKillTypes
	GameplayTags.SkillType_Melee = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("SkillType.Melee"), FString("Melee skill"));
	GameplayTags.SkillType_Spell = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("SkillType.Spell"), FString("Spell skill"));
	GameplayTags.SkillType_Ranged = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("SkillType.Ranged"), FString("Ranged skill"));

	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Fire, GameplayTags.Attributes_Resistance_Fire);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Cold, GameplayTags.Attributes_Resistance_Cold);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Lightning, GameplayTags.Attributes_Resistance_Lightning);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Poison, GameplayTags.Attributes_Resistance_Poison);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Physical, GameplayTags.Attributes_Resistance_Physical);

	// Effects
	GameplayTags.Effects_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Effects.HitReact"), FString("Reaction to being hit"));

	GameplayTags.Effects_Poisoned = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Effects.Poisoned"), FString("Applies periodic poison damage"));

	GameplayTags.Effects_Frozen = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Effects.Frozen"), FString("Prevents movement and actions"));

	GameplayTags.Effects_Slowed = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Effects.Slowed"), FString("Reduces movement and attack speed"));

	GameplayTags.Effects_Stunned = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Effects.Stunned"), FString("Temporarily disables actions"));

	GameplayTags.Effects_Burning = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Effects.Burning"), FString("Applies periodic fire damage"));
}