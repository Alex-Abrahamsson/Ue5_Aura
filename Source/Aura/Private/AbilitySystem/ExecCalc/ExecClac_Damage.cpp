// Copyright AbraCode


#include "AbilitySystem/ExecCalc/ExecClac_Damage.h"

#include "AbilitySystemComponent.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Interaction/CombatInterface.h"

struct AuraDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitDamage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitResistance);
	
	AuraDamageStatics()
	{
		//Target
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, BlockChance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CriticalHitResistance, Target, false);
		// Source
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, ArmorPenetration, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CriticalHitChance, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CriticalHitDamage, Source, false);
	}
};

static const AuraDamageStatics& DamageStatics()
{
	static AuraDamageStatics DStatics;
	return DStatics;
}

UExecClac_Damage::UExecClac_Damage()
{
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArmorPenetrationDef);
	RelevantAttributesToCapture.Add(DamageStatics().BlockChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitDamageDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitResistanceDef);
}

void UExecClac_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                              FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;
	ICombatInterface* SourceCombat = Cast<ICombatInterface>(SourceAvatar);
	ICombatInterface* TargetCombat = Cast<ICombatInterface>(TargetAvatar);

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvalParams;
	EvalParams.SourceTags = SourceTags;
	EvalParams.TargetTags = TargetTags;

	const UCharacterClassInfo* ClassInfo = UAuraAbilitySystemLibrary::GetCharacterClassInfo(SourceAvatar);
	const FAuraGameplayTags Tags = FAuraGameplayTags::Get();

	const bool bIsSpell = SourceTags->HasTag(Tags.Damage_Type_Spell);
	const bool bIsMelee = SourceTags->HasTag(Tags.Damage_Type_Melee);

	// 1. Base Damage
	float Damage = Spec.GetSetByCallerMagnitude(Tags.Damage);

	// 2. Shared Attributes
	float CritChance = GetAttribute(ExecutionParams, DamageStatics().CriticalHitChanceDef, EvalParams);
	float CritBonus = GetAttribute(ExecutionParams, DamageStatics().CriticalHitDamageDef, EvalParams);
	float CritResist = GetAttributeBonus(ExecutionParams, DamageStatics().CriticalHitResistanceDef, EvalParams);
	float CritResistCoeff = ClassInfo->DamageCalculationCoefficients->FindCurve(FName("CriticalHitResistance"), FString())->Eval(TargetCombat->GetPlayerLevel());
	float EffectiveCritChance = FMath::Clamp(CritChance - CritResist * CritResistCoeff, 0.f, 100.f);
	bool bCrit = FMath::RandRange(1, 100) <= EffectiveCritChance;

	// 3. Melee-specific
	if (bIsMelee)
	{
		float BlockChance = GetAttribute(ExecutionParams, DamageStatics().BlockChanceDef, EvalParams);
		bool bBlocked = FMath::RandRange(1, 100) <= BlockChance;

		if (bBlocked)
		{
			Damage *= 0.1f;
		}
		else if (bCrit)
		{
			Damage = Damage * 2.0f + CritBonus;
		}

		// Armor Reduction
		float Armor = GetAttribute(ExecutionParams, DamageStatics().ArmorDef, EvalParams);
		float ArmorPen = GetAttribute(ExecutionParams, DamageStatics().ArmorPenetrationDef, EvalParams);
		float ArmorPenCoeff = ClassInfo->DamageCalculationCoefficients->FindCurve(FName("ArmorPenetration"), FString())->Eval(SourceCombat->GetPlayerLevel());
		float ArmorCoeff = ClassInfo->DamageCalculationCoefficients->FindCurve(FName("EffectiveArmor"), FString())->Eval(TargetCombat->GetPlayerLevel());

		float ArmorIgnored = ArmorPen * ArmorPenCoeff;
		float EffectiveArmor = Armor * (100.f - ArmorIgnored) / 100.f;
		float ArmorReduction = EffectiveArmor * ArmorCoeff;
		Damage *= (100.f - ArmorReduction) / 100.f;
	}

	// 4. Spell-specific
	else if (bIsSpell)
	{
		// Spells ignorerar block och armor
		if (bCrit)
		{
			Damage = Damage * 2.0f + CritBonus;
		}
		// Du kan lägga till elemental resist här om du vill
	}

	// 5. Apply
	const FGameplayModifierEvaluatedData EvaluatedData(UAuraAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}


float UExecClac_Damage::GetAttribute(const FGameplayEffectCustomExecutionParameters& Params, const FGameplayEffectAttributeCaptureDefinition& Def, const FAggregatorEvaluateParameters& Eval)
{
	float Value = 0.f;
	Params.AttemptCalculateCapturedAttributeMagnitude(Def, Eval, Value);
	return FMath::Max(Value, 0.f);
}

float UExecClac_Damage::GetAttributeBonus(const FGameplayEffectCustomExecutionParameters& Params, const FGameplayEffectAttributeCaptureDefinition& Def, const FAggregatorEvaluateParameters& Eval)
{
	float Value = 0.f;
	Params.AttemptCalculateCapturedAttributeBonusMagnitude(Def, Eval, Value);
	return FMath::Max(Value, 0.f);
}


