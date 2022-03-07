// Copyright SpaceCatLabs. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "HTriggerableActor.generated.h"

class UHTriggerableComponent;
class UHTargetableIconComponent;
class UHTargetableComponent;

/**
 * This is a base class holding TriggerableComponent that can be activated by this actor's targetable component.
 *
 * There is no built in action activating TriggerableComponent, so you need to add at least one activator.
 */
UCLASS(Abstract, Blueprintable)
class AHTriggerableActor : public AActor
{
	GENERATED_BODY()

public:

	AHTriggerableActor();

protected:

	UPROPERTY(EditAnywhere)
	UHTargetableComponent* TargetableComponent = nullptr;
	
	UPROPERTY(EditAnywhere)
	UHTargetableIconComponent* TargetableIconComponent = nullptr;
	
	UPROPERTY(VisibleAnywhere)
	UHTriggerableComponent* TriggerableComponent = nullptr;
};

