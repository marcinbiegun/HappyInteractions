// Copyright SpaceCatLabs. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "HappyCondition.generated.h"

UCLASS(Abstract, Blueprintable, EditInlineNew, CollapseCategories)
class HAPPYINTERACTIONS_API UHappyCondition : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent)
	bool IsConditionPassing();
	
};

