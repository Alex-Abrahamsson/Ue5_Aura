// Copyright AbraCode


#include "AbilitySystem/Abilities/AuraDamageGameplayAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

void UAuraDamageGameplayAbility::CauseDamage(AActor* TargetActor)
{
	FGameplayEffectSpecHandle SpecHandle = MakeOutgoingGameplayEffectSpec(DamageEffectClass, 1.f);

	for (const TPair<FGameplayTag, FDamageRange>& Pair : DamageRanges)
	{
		const float MinScaledDamage = Pair.Value.MinDamage.GetValueAtLevel(GetAbilityLevel());
		const float MaxScaledDamage = Pair.Value.MaxDamage.GetValueAtLevel(GetAbilityLevel());

		// Skicka in båda som SetByCaller med olika taggar
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, Pair.Key, MinScaledDamage);
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, Pair.Key, MaxScaledDamage);
	}

	GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(
		*SpecHandle.Data.Get(),
		UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor)
	);
}



