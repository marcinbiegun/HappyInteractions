// Copyright SpaceCatLabs. All Rights Reserved.
#pragma once

#include "GameplayTagContainer.h"

class HAPPYINTERACTIONS_API HappyUtils
{
public:

	static FName GameplayTagToFName(FGameplayTag InGameplayTag);
	static bool IsComponentParentedBy(const USceneComponent* InCheckedComponent, const USceneComponent* InParentComponent,
							 const bool bInCheckWholeChain = true);
};
