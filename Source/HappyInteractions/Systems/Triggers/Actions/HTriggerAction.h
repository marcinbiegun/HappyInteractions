// Copyright SpaceCatLabs. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "HTriggerAction.generated.h"


/**
 * Base class for trigger actions.
 */
UCLASS(Abstract, Blueprintable, EditInlineNew, CollapseCategories)
class UHTriggerAction : public UObject
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintNativeEvent)
	void ExecuteAction(bool bInHasOwner, AActor* InOwner, bool bInHasActivator, AActor* InActivator);
};

