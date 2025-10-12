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

		// Slumpa ett värde mellan min och max
		const float RandomDamage = FMath::RandRange(MinScaledDamage, MaxScaledDamage);
		
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, Pair.Key, RandomDamage);
	}

	GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(
		*SpecHandle.Data.Get(),
		UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor)
	);
}



