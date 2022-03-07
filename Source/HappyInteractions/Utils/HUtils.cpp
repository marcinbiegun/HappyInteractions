// Copyright SpaceCatLabs. All Rights Reserved.

#include "HUtils.h"

FName HUtils::GameplayTagToFName(FGameplayTag InGameplayTag)
{
	if (!InGameplayTag.IsValid())
		return FName();

	const FString VariableString = InGameplayTag.ToString();
	if (VariableString.IsEmpty())
		return FName();

	return FName(VariableString);
}
