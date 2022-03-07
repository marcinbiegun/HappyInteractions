// Copyright SpaceCatLabs, Inc. All Rights Reserved.

#include "HGameplayStatics.h"

#include "Subsystems/HGameVariableSubsystem.h"
#include "Kismet/GameplayStatics.h"

UHGameVariableSubsystem* UHGameplayStatics::GetGameVariableSubsystem(const UObject* WorldContextObject)
{
	if (!WorldContextObject)
		return nullptr;

	if (const UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(WorldContextObject))
		return GameInstance->GetSubsystem<UHGameVariableSubsystem>();

	return nullptr;
}

