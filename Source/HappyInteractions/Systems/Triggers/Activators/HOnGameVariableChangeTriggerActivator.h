// Copyright SpaceCatLabs. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "HTriggerActivator.h"
#include "HOnGameVariableChangeTriggerActivator.generated.h"

/**
 * This activator subscribes to a single GameVariable and fires when it changes.
 */
UCLASS(meta=(DisplayName = "On Game Variable Change"))
class UHOnGameVariableChangeTriggerActivator : public UHTriggerActivator
{
	GENERATED_BODY()

public:

	virtual void Initialize(AActor* InOwner) override;
	virtual void Deinitialize(AActor* InOwner) override;

protected:
	
	UPROPERTY(EditAnywhere)
	FGameplayTag GameVariable;

	UFUNCTION()
	void OnGameVariableUpdate(FName InGameplayTagName, int32 InValue);
};
