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

	DECLARE_ATTRIBUTE_CAPTUREDEF(FireResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ColdResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(LightningResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(PoisonResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(MagicResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalResistance);
	
	AuraDamageStatics()
	{
		//Target
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, BlockChance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CriticalHitResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, FireResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, ColdResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, LightningResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, PoisonResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, MagicResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, PhysicalResistance, Target, false);
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

	RelevantAttributesToCapture.Add(AuraDamageStatics().FireResistanceDef);
	RelevantAttributesToCapture.Add(AuraDamageStatics().ColdResistanceDef);
	RelevantAttributesToCapture.Add(AuraDamageStatics().LightningResistanceDef);
	RelevantAttributesToCapture.Add(AuraDamageStatics().PoisonResistanceDef);
	RelevantAttributesToCapture.Add(AuraDamageStatics().MagicResistanceDef);
	RelevantAttributesToCapture.Add(AuraDamageStatics().PhysicalResistanceDef);
}

void UExecClac_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                              FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
    const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
    const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

    AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
    AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	int32 SourcePlayerLevel = 1;
	if (SourceAvatar->Implements<UCombatInterface>())
	{
		SourcePlayerLevel = ICombatInterface::Execute_GetPlayerLevel(SourceAvatar);
	}
	int32 TargetPlayerLevel = 1;
	if (TargetAvatar->Implements<UCombatInterface>())
	{
		TargetPlayerLevel = ICombatInterface::Execute_GetPlayerLevel(TargetAvatar);
	}

    const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

    const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
    const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
    FAggregatorEvaluateParameters EvaluationParameters;
    EvaluationParameters.SourceTags = SourceTags;
    EvaluationParameters.TargetTags = TargetTags;

    FGameplayEffectContextHandle EffectContextHandle = Spec.GetContext();
    const UCharacterClassInfo* ClassInfo = UAuraAbilitySystemLibrary::GetCharacterClassInfo(SourceAvatar);

    const FAuraGameplayTags& Tags = FAuraGameplayTags::Get();

    // 1. Collect base damage per type (instead of summing early, to apply resistances per type like in D2)
    TMap<FGameplayTag, float> TypeDamages;
    for (const auto& Pair : Tags.DamageTypesToResistances)
    {
        const float DamageTypeValue = Spec.GetSetByCallerMagnitude(Pair.Key, false, 0.f);
        if (DamageTypeValue > 0.f)
        {
            TypeDamages.Add(Pair.Key, DamageTypeValue);
        }
    }

    // 2. Shared Attributes (crit chance applies to all types)
    float CritChance = GetAttribute(ExecutionParams, DamageStatics().CriticalHitChanceDef, EvaluationParameters);
    float CritBonus = GetAttribute(ExecutionParams, DamageStatics().CriticalHitDamageDef, EvaluationParameters);
    float CritResist = GetAttributeBonus(ExecutionParams, DamageStatics().CriticalHitResistanceDef, EvaluationParameters);
    float CritResistCoeff = ClassInfo->DamageCalculationCoefficients->FindCurve(FName("CriticalHitResistance"), FString())->Eval(SourcePlayerLevel);
    float EffectiveCritChance = FMath::Clamp(CritChance - CritResist * CritResistCoeff, 0.f, 100.f);
    bool bCrit = FMath::RandRange(1, 100) <= EffectiveCritChance;
    UAuraAbilitySystemLibrary::SetIsCriticalHit(EffectContextHandle, bCrit);

    bool bIsMelee = Spec.GetSetByCallerMagnitude(Tags.SkillType_Melee, false, -1.f) >= 0.f;
    bool bIsSpell = Spec.GetSetByCallerMagnitude(Tags.SkillType_Spell, false, -1.f) >= 0.f;
    bool bIsRanged = Spec.GetSetByCallerMagnitude(Tags.SkillType_Ranged, false, -1.f) >= 0.f;

    bool bBlocked = false;

    // 3. Melee-specific (apply to all types, but armor only to physical like in D2-inspired physical reduction)
    if (bIsMelee)
    {
        float BlockChance = GetAttribute(ExecutionParams, DamageStatics().BlockChanceDef, EvaluationParameters);
        bBlocked = FMath::RandRange(1, 100) <= BlockChance;
        UAuraAbilitySystemLibrary::SetIsBlockedHit(EffectContextHandle, bBlocked);  // Fixed assumed typo: use SetIsBlockedHit instead of overwriting crit

        if (bBlocked)
        {
            // Block reduces all damage (like in D2, blocks entire attack)
            for (auto& DamagePair : TypeDamages)
            {
                DamagePair.Value *= 0.1f;
            }
        }
    }

    // Apply crit if applicable (after block check for melee)
    if ((bIsMelee && !bBlocked) || bIsSpell)
    {
        if (bCrit)
        {
            for (auto& DamagePair : TypeDamages)
            {
                DamagePair.Value = DamagePair.Value * 2.0f + CritBonus;
            }
        }
    }
    // Note: If ranged should crit, add || bIsRanged above

    // Armor Reduction (only for melee and only apply to physical damage type, to separate from elemental res)
    if (bIsMelee)
    {
        float Armor = GetAttribute(ExecutionParams, DamageStatics().ArmorDef, EvaluationParameters);
        float ArmorPen = GetAttribute(ExecutionParams, DamageStatics().ArmorPenetrationDef, EvaluationParameters);
        float ArmorPenCoeff = ClassInfo->DamageCalculationCoefficients->FindCurve(FName("ArmorPenetration"), FString())->Eval(SourcePlayerLevel);
        float ArmorCoeff = ClassInfo->DamageCalculationCoefficients->FindCurve(FName("EffectiveArmor"), FString())->Eval(TargetPlayerLevel);

        float ArmorIgnored = ArmorPen * ArmorPenCoeff;
        float EffectiveArmor = Armor * (100.f - ArmorIgnored) / 100.f;
        float ArmorReduction = EffectiveArmor * ArmorCoeff;
        float ArmorMultiplier = (100.f - ArmorReduction) / 100.f;

        // Assume physical damage tag is Damage_Physical (adjust if different)
        const FGameplayTag PhysicalDamageTag = Tags.Damage_Physical;  // Add this tag if not exists
        if (TypeDamages.Contains(PhysicalDamageTag))
        {
            TypeDamages[PhysicalDamageTag] *= ArmorMultiplier;
        }
    }

    // 4. Spell-specific (no changes, but you can add more here if needed)
    else if (bIsSpell)
    {
        // Spells ignore block and armor (as in your original)
    }

    // 5. Resistances (D2-style per type, applied last)
    for (auto& DamagePair : TypeDamages)
    {
        const FGameplayTag DamageType = DamagePair.Key;
        float& TypeDamage = DamagePair.Value;

        const FGameplayTag ResTag = Tags.DamageTypesToResistances.FindChecked(DamageType);
        const FGameplayEffectAttributeCaptureDefinition ResDef = GetResistanceDef(ResTag);

        if (ResDef.AttributeToCapture.IsValid())
        {
            float Resistance = GetAttribute(ExecutionParams, ResDef, EvaluationParameters);
            // Optional: Clamp like D2 base (adjust or remove if you want no limits)
            // Resistance = FMath::Clamp(Resistance, -100.f, 75.f);

            float Multiplier = 1.f - (Resistance / 100.f);
            Multiplier = FMath::Max(Multiplier, 0.f);  // Prevent negative (immunity if res >=100)
            TypeDamage *= Multiplier;
        }
    }

    // Sum final damage
    float Damage = 0.f;
    for (const auto& DamagePair : TypeDamages)
    {
        Damage += DamagePair.Value;
    }

    // 6. Apply
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

FGameplayEffectAttributeCaptureDefinition UExecClac_Damage::GetResistanceDef(const FGameplayTag& ResTag) const
{
	const FAuraGameplayTags& Tags = FAuraGameplayTags::Get();

	if (ResTag.MatchesTagExact(Tags.Attributes_Resistance_Fire)) return DamageStatics().FireResistanceDef;
	if (ResTag.MatchesTagExact(Tags.Attributes_Resistance_Cold)) return DamageStatics().ColdResistanceDef;
	if (ResTag.MatchesTagExact(Tags.Attributes_Resistance_Lightning)) return DamageStatics().LightningResistanceDef;
	if (ResTag.MatchesTagExact(Tags.Attributes_Resistance_Poison)) return DamageStatics().PoisonResistanceDef;
	if (ResTag.MatchesTagExact(Tags.Attributes_Resistance_Magic)) return DamageStatics().MagicResistanceDef;
	if (ResTag.MatchesTagExact(Tags.Attributes_Resistance_Physical)) return DamageStatics().PhysicalResistanceDef;

	// Fallback om invalid
	return FGameplayEffectAttributeCaptureDefinition();
}


