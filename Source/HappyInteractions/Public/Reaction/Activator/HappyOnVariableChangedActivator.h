// Copyright SpaceCatLabs. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "HappyActivator.h"
#include "HappyOnVariableChangedActivator.generated.h"

/**
 * This activator subscribes to a single GameVariable and fires when it changes.
 */
UCLASS(meta=(DisplayName = "On Variable Changed"))
class HAPPYINTERACTIONS_API UHappyOnVariableChangedActivator : public UHappyActivator
{
	GENERATED_BODY()

public:

	virtual void InitializeActivator(AActor* InOwner) override;
	virtual void DeinitializeActivator(AActor* InOwner) override;

protected:
	
	UPROPERTY(EditAnywhere)
	FGameplayTag GameVariable;

	UFUNCTION()
	void OnGameVariableUpdate(FName InGameplayTagName, int32 InValue);
};
