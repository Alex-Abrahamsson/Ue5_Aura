// Copyright AbraCode


#include "AbilitySystem/ExecCalc/ExecCalc_MagicDamage.h"

#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAttributeSet.h"

struct AuraMagicDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(FireResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ColdResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(PoisonResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(LightningResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(MagicResistance);
	
	AuraMagicDamageStatics()
	{
		//Target
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, FireResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, ColdResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, PoisonResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, LightningResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, MagicResistance, Target, false);
		// Source
		// DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, ArmorPenetration, Source, false);
	}
};

static const AuraMagicDamageStatics& DamageStatics()
{
	static AuraMagicDamageStatics DStatics;
	return DStatics;
}

UExecCalc_MagicDamage::UExecCalc_MagicDamage()
{
	RelevantAttributesToCapture.Add(DamageStatics().FireResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().ColdResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().PoisonResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().LightningResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().MagicResistanceDef);
}

// TODO: CHANGE THIS TO HANDLE MAGIC DAMAGE WITH RESISTANCES!!!

void UExecCalc_MagicDamage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                                   FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	const AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	const AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	// Base damage from caller
	const float BaseDamage = Spec.GetSetByCallerMagnitude(FAuraGameplayTags::Get().Damage);

	// Capture resistances
	float TargetFireResist = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().FireResistanceDef, EvaluationParameters, TargetFireResist);
	float TargetColdResist = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ColdResistanceDef, EvaluationParameters, TargetColdResist);
	float TargetLightningResist = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().LightningResistanceDef, EvaluationParameters, TargetLightningResist);
	float TargetPoisonResist = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().PoisonResistanceDef, EvaluationParameters, TargetPoisonResist);
	float TargetMagicResist = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().MagicResistanceDef, EvaluationParameters, TargetMagicResist);

	// Total damage after resistances
	float FinalDamage = 0.f;
	// Apply each damage type if present
	if (SourceTags->HasTag(FAuraGameplayTags::Get().Damage_Fire))
	{
		const float Multiplier = 1.f - (TargetFireResist / 100.f);
		FinalDamage += BaseDamage * Multiplier;
	}
	if (SourceTags->HasTag(FAuraGameplayTags::Get().Damage_Cold))
	{
		const float Multiplier = 1.f - (TargetColdResist / 100.f);
		FinalDamage += BaseDamage * Multiplier;
	}
	if (SourceTags->HasTag(FAuraGameplayTags::Get().Damage_Lightning))
	{
		const float Multiplier = 1.f - (TargetLightningResist / 100.f);
		FinalDamage += BaseDamage * Multiplier;
	}
	if (SourceTags->HasTag(FAuraGameplayTags::Get().Damage_Poison))
	{
		const float Multiplier = 1.f - (TargetPoisonResist / 100.f);
		FinalDamage += BaseDamage * Multiplier;
	}
	if (SourceTags->HasTag(FAuraGameplayTags::Get().Damage_Magic))
	{
		const float Multiplier = 1.f - (TargetMagicResist / 100.f);
		FinalDamage += BaseDamage * Multiplier;
	}
	// Om ingen skadetagg finns, behandla som magic
	if (FinalDamage == 0.f)
	{
		const float Multiplier = 1.f - (TargetMagicResist / 100.f);
		FinalDamage = BaseDamage * Multiplier;
	}
	// Se till att skadan aldrig blir negativ
	FinalDamage = FMath::Max(FinalDamage, 0.f);

	// Applicera skadan
	const FGameplayModifierEvaluatedData EvaluatedData(UAuraAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, FinalDamage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}

