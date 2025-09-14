// Copyright AbraCode


#include "Input/AuraInputConfig.h"

const UInputAction* UAuraInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	for (const auto& Action : AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag == InputTag)
		{
			return  Action.InputAction;
		}
	}

	if (bLogNotFound)
	{
		// LOGGA HÄR?
	}

	return nullptr;
}
