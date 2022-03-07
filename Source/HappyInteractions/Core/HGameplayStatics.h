// Copyright SpaceCatLabs, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/HGameVariableSubsystem.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HGameplayStatics.generated.h"

UCLASS()
class UHGameplayStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintPure)
	static UHGameVariableSubsystem* GetGameVariableSubsystem(const UObject* WorldContextObject);
	
};
