// Copyright AbraCode

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "ExecClac_Damage.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UExecClac_Damage : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	UExecClac_Damage();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;

	static float GetAttribute(const FGameplayEffectCustomExecutionParameters& Params, const FGameplayEffectAttributeCaptureDefinition& Def, const FAggregatorEvaluateParameters& Eval);
	static float GetAttributeBonus(const FGameplayEffectCustomExecutionParameters& Params, const FGameplayEffectAttributeCaptureDefinition& Def, const FAggregatorEvaluateParameters& Eval);

	FGameplayEffectAttributeCaptureDefinition GetResistanceDef(const FGameplayTag& ResTag) const;
};
