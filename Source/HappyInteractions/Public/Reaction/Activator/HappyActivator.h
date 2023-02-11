// Copyright SpaceCatLabs. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "HappyActivator.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHappyTriggerActivatorActivated, AActor*, ExecutorActor);

UCLASS(Abstract, Blueprintable, EditInlineNew, CollapseCategories)
class HAPPYINTERACTIONS_API UHappyActivator : public UObject
{
	GENERATED_BODY()
	

public:

	FHappyTriggerActivatorActivated OnActivated;

	virtual void Initialize(AActor* InOwner) {}
	virtual void Deinitialize(AActor* InOwner) {}

protected:

	// UFUNCTION(BlueprintCallable)
	// void ExecuteActivator() const;
	
	UFUNCTION(BlueprintCallable)
	void ExecuteActivator(AActor* ExecutorActor) const;
};


