// Copyright SpaceCatLabs. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "HTriggerCondition.generated.h"

UCLASS(Abstract, Blueprintable, EditInlineNew, CollapseCategories)
class UHTriggerCondition : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent)
	bool IsConditionPassing();
	
};

