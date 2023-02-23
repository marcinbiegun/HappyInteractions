// Copyright SpaceCatLabs. All Rights Reserved.

#include "Utils/HappyUtils.h"

FName HappyUtils::GameplayTagToName(FGameplayTag InGameplayTag)
{
	if (!InGameplayTag.IsValid())
		return FName();

	const FString VariableString = InGameplayTag.ToString();
	if (VariableString.IsEmpty())
		return FName();

	return FName(VariableString);
}
