// Copyright AbraCode

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "DmgTextComponent.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UDmgTextComponent : public UWidgetComponent
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetDmgText(float Damage);
};
