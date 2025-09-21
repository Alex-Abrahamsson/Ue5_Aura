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

    // Damage
    GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Damage"), FString("Damage"));
}
