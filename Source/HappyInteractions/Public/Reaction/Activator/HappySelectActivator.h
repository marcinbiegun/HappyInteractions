﻿// Copyright SpaceCatLabs. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "HappyActivator.h"
#include "HappySelectActivator.generated.h"

class UHappySelectComponent;

/**
 * Fires when HappySelectComponent on owner actor is used.
 */
UCLASS(meta=(DisplayName = "On Select Used"))
class HAPPYINTERACTIONS_API UHappySelectActivator : public UHappyActivator
{
	GENERATED_BODY()

public:

	virtual void InitializeActivator(AActor* InOwner) override;
	virtual void DeinitializeActivator(AActor* InOwner) override;
	
	/** The name of a HappySelectComponent on owning actor, that will be connected to this activator */
	UPROPERTY(EditAnywhere)
	FName SelectComponentName = TEXT("Select");

protected:

	UPROPERTY(EditAnywhere)
	UHappySelectComponent* SelectComponent;
	
	UFUNCTION()
	void OnSelectComponentUsed(AActor* InExecutor);
};
