// Copyright SpaceCatLabs. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "HappyActivator.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHappyReactionActivatorActivated, AActor*, ExecutorActor);

UCLASS(Abstract, Blueprintable, EditInlineNew, CollapseCategories)
class HAPPYINTERACTIONS_API UHappyActivator : public UObject
{
	GENERATED_BODY()

public:

	FHappyReactionActivatorActivated OnExecuted;

	virtual void InitializeActivator(AActor* InOwner) {}
	virtual void DeinitializeActivator(AActor* InOwner) {}

protected:

	UFUNCTION(BlueprintCallable)
	void ExecuteActivator(AActor* ExecutorActor) const;
};


