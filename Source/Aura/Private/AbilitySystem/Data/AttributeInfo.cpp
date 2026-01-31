// Copyright AbraCode


#include "AbilitySystem/Data/AttributeInfo.h"

#include "Aura/AuraLogChannels.h"

FAuraAttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogFound) const
{
	for (const FAuraAttributeInfo& Info : AttributeInformation)
	{
		if (Info.AttributeTag == AttributeTag)
		{
			return Info;
		}
	}

	if (bLogFound)
	{
		UE_LOG(LogAura,Error, TEXT("Can´t find info for attributetag [%s] on AttributeInfo [%s]"), *AttributeTag.ToString(), *GetNameSafe(this));
	}

	return FAuraAttributeInfo();
}
