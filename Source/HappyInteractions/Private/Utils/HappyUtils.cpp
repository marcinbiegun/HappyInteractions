// Copyright SpaceCatLabs. All Rights Reserved.

#include "Utils/HappyUtils.h"
#include "Variable/HappyVariableSubsystem.h"

FName HappyUtils::GameplayTagToName(FGameplayTag InGameplayTag)
{
	if (!InGameplayTag.IsValid())
		return FName();

	const FString VariableString = InGameplayTag.ToString();
	if (VariableString.IsEmpty())
		return FName();

	return FName(VariableString);
}

UHappyVariableSubsystem* HappyUtils::GetVariableSubsystem(UObject* WorldContextObject)
{
	if (const UWorld* World = WorldContextObject->GetWorld())
	{
		if (const UGameInstance* GameInstance = World->GetGameInstance())
		{
			return GameInstance->GetSubsystem<UHappyVariableSubsystem>();
		}
	}
	
	return nullptr;
}
