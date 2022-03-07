// Copyright SpaceCatLabs. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "HTriggerActivator.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHTriggerActivatorActivated, bool, bActivatedByActor, AActor*, InActivator);

UCLASS(Abstract, Blueprintable, EditInlineNew, CollapseCategories)
class UHTriggerActivator : public UObject
{
	GENERATED_BODY()

public:

	FHTriggerActivatorActivated OnActivated;

	virtual void Initialize(AActor* InOwner) {}
	virtual void Deinitialize(AActor* InOwner) {}

protected:

	UFUNCTION(BlueprintCallable)
	void ActivateActivator() const;
	
	UFUNCTION(BlueprintCallable)
	void ActivateActivatorByActor(AActor* InActivator) const;
};


