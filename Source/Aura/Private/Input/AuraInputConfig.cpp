// Copyright Noroth


#include "Input/AuraInputConfig.h"

const UInputAction* UAuraInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag,
	bool bLogNotFound) const
{
	for (const FAuraInputAction& AbilityAction : AbilityInputActions)
	{
		if (AbilityAction.InputAction && AbilityAction.InputTag.MatchesTagExact(InputTag))
			return AbilityAction.InputAction; 
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not find AbilityInputAction for Tag [%s], on InputConfig [%s]"), *InputTag.ToString(), *GetNameSafe(this));
	}

	return nullptr;
}
