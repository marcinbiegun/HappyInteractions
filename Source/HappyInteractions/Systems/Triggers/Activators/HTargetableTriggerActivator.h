// Copyright SpaceCatLabs. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "HTriggerActivator.h"
#include "Systems/Targeting/HTargetableComponent.h"
#include "HTargetableTriggerActivator.generated.h"


/**
 * Fires when targetable component on owner actor is used.
 */
UCLASS(meta=(DisplayName = "On Targettable Used"))
class UHTargetableTriggerActivator : public UHTriggerActivator
{
	GENERATED_BODY()

public:

	virtual void Initialize(AActor* InOwner) override;
	virtual void Deinitialize(AActor* InOwner) override;
	
	/** The name of a TargetableComponent on owning actor, that will be connected to this activator */
	UPROPERTY(EditAnywhere)
	FName TargetableComponentName;

protected:

	UPROPERTY(EditAnywhere)
	UHTargetableComponent* TargetableComponent;
	
	UFUNCTION()
	void OnTargetableUse(AActor* InExecutor);
};
