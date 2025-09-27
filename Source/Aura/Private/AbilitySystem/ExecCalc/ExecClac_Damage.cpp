// Copyright AbraCode


#include "AbilitySystem/ExecCalc/ExecClac_Damage.h"

#include "AbilitySystemComponent.h"
#include "AuraAbilityTypes.h"
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
	RelevantAttributesToCapture.Add(AuraDamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(AuraDamageStatics().ArmorPenetrationDef);
	RelevantAttributesToCapture.Add(AuraDamageStatics().BlockChanceDef);
	RelevantAttributesToCapture.Add(AuraDamageStatics().CriticalHitChanceDef);
	RelevantAttributesToCapture.Add(AuraDamageStatics().CriticalHitDamageDef);
	RelevantAttributesToCapture.Add(AuraDamageStatics().CriticalHitResistanceDef);
}

void UExecClac_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                              FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;
	ICombatInterface* SourceCombatInterface = Cast<ICombatInterface>(SourceAvatar);
	ICombatInterface* TargetCombatInterface = Cast<ICombatInterface>(TargetAvatar);

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	FGameplayEffectContextHandle EffectContextHandle = Spec.GetContext();
	const UCharacterClassInfo* ClassInfo = UAuraAbilitySystemLibrary::GetCharacterClassInfo(SourceAvatar);

	// const FAuraGameplayTags Tags = FAuraGameplayTags::Get();

	// 1. Base Damage
	float Damage = 0.f;
	for (auto& Pair : FAuraGameplayTags::Get().DamageTypesToResistances)
	{
		const float DamageTypeValue = Spec.GetSetByCallerMagnitude(Pair.Key);
		Damage += DamageTypeValue;
	}

	// 2. Shared Attributes
	float CritChance = GetAttribute(ExecutionParams, DamageStatics().CriticalHitChanceDef, EvaluationParameters);
	float CritBonus = GetAttribute(ExecutionParams, DamageStatics().CriticalHitDamageDef, EvaluationParameters);
	float CritResist = GetAttributeBonus(ExecutionParams, DamageStatics().CriticalHitResistanceDef, EvaluationParameters);
	float CritResistCoeff = ClassInfo->DamageCalculationCoefficients->FindCurve(FName("CriticalHitResistance"), FString())->Eval(TargetCombatInterface->GetPlayerLevel());
	float EffectiveCritChance = FMath::Clamp(CritChance - CritResist * CritResistCoeff, 0.f, 100.f);
	bool bCrit = FMath::RandRange(1, 100) <= EffectiveCritChance;
	UAuraAbilitySystemLibrary::SetIsCriticalHit(EffectContextHandle, bCrit);

	const FAuraGameplayTags& Tags = FAuraGameplayTags::Get();

	bool bIsMelee = Spec.GetSetByCallerMagnitude(Tags.SkillType_Melee, false, -1.f) >= 0.f;
	bool bIsSpell = Spec.GetSetByCallerMagnitude(Tags.SkillType_Spell, false, -1.f) >= 0.f;
	bool bIsRanged = Spec.GetSetByCallerMagnitude(Tags.SkillType_Ranged, false, -1.f) >= 0.f;


	// 3. Melee-specific
	if (bIsMelee)
	{
		float BlockChance = GetAttribute(ExecutionParams, DamageStatics().BlockChanceDef, EvaluationParameters);
		bool bBlocked = FMath::RandRange(1, 100) <= BlockChance;
		UAuraAbilitySystemLibrary::SetIsCriticalHit(EffectContextHandle, bBlocked);
		
		if (bBlocked)
		{
			Damage *= 0.1f;
		}
		else if (bCrit)
		{
			Damage = Damage * 2.0f + CritBonus;
		}

		// Armor Reduction
		float Armor = GetAttribute(ExecutionParams, DamageStatics().ArmorDef, EvaluationParameters);
		float ArmorPen = GetAttribute(ExecutionParams, DamageStatics().ArmorPenetrationDef, EvaluationParameters);
		float ArmorPenCoeff = ClassInfo->DamageCalculationCoefficients->FindCurve(FName("ArmorPenetration"), FString())->Eval(SourceCombatInterface->GetPlayerLevel());
		float ArmorCoeff = ClassInfo->DamageCalculationCoefficients->FindCurve(FName("EffectiveArmor"), FString())->Eval(TargetCombatInterface->GetPlayerLevel());

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


