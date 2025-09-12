// Copyright AbraCode

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * AuraGameplayTags
 *
 * Sigleton containing native gameplay Tags
 */


struct  FAuraGameplayTags
{
public:
	static const FAuraGameplayTags& Get() { return  GameplayTags; }
	static void InitializeGameplayTags();
protected:

private:
	static FAuraGameplayTags GameplayTags;
};
