// Copyright SpaceCatLabs. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "HappyAction.generated.h"

/**
 * Base class for HappyActions.
 */
UCLASS(Abstract, Blueprintable, EditInlineNew, CollapseCategories)
class HAPPYINTERACTIONS_API UHappyAction : public UObject
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintNativeEvent)
	void ExecuteAction(const AActor* OwnerActor, const AActor* ExecutorActor);

	// Allow all blueprint functions
	// Taken from: https://forums.unrealengine.com/t/blueprint-functions-not-accessible-from-uobject-derived-classes/356987/10
	virtual UWorld* GetWorld() const override
	{
		if (HasAllFlags(RF_ClassDefaultObject))
		{
			// If we are a CDO, we must return nullptr instead of calling Outer->GetWorld() to fool UObject::ImplementsGetWorld.
			return nullptr;
		}
		return GetOuter()->GetWorld();
	}
	
};

