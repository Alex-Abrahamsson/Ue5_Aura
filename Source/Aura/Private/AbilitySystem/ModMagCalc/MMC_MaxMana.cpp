// Copyright AbraCode


#include "AbilitySystem/ModMagCalc/MMC_MaxMana.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxMana::UMMC_MaxMana()
{
	EnergyDef.AttributeToCapture = UAuraAttributeSet::GetEnergyAttribute();
	EnergyDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	EnergyDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(EnergyDef);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	float Energy = 0.f;
	GetCapturedAttributeMagnitude(EnergyDef, Spec, EvaluateParameters, Energy);
	Energy = FMath::Max(Energy, 0.f);

	int32 PlayerLevel = 1;
	if (Spec.GetContext().GetSourceObject()->Implements<UCombatInterface>())
	{
		PlayerLevel = ICombatInterface::Execute_GetPlayerLevel(Spec.GetContext().GetSourceObject());
	}

	return 50.f + 2.f * Energy + 10 * PlayerLevel;
}
