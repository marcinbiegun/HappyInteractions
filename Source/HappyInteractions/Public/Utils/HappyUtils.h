// Copyright SpaceCatLabs. All Rights Reserved.
#pragma once

#include "GameplayTagContainer.h"

class UHappyVariableSubsystem;

class HAPPYINTERACTIONS_API HappyUtils
{
public:

	static FName GameplayTagToName(FGameplayTag InGameplayTag);

	static UHappyVariableSubsystem* GetVariableSubsystem(UObject* WorldContextObject);
};
