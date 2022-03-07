// Copyright SpaceCatLabs. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "HTriggerableComponent.generated.h"

class UHTriggerCondition;
class UHTriggerActivator;
class UHTriggerAction;

/**
 * This important component connects trigger activators, conditions and actions into single piece of logic.
 *
 * When fired manually or by using an activator, it checks all conditions and if they all are satisfied it
 * will run all actions.
 */
UCLASS(ClassGroup="HappyInteractions", meta=(DisplayName = "Triggerable", BlueprintSpawnableComponent))
class UHTriggerableComponent : public UActorComponent
{
	GENERATED_BODY()

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	
	bool TryToTrigger();
	bool TryToTrigger(AActor* InActivator);

	void AddActivator(UHTriggerActivator* InActivator) { Activators.Add(InActivator); }

protected:

	UFUNCTION()
	void OnActivatorActivated(bool bInActivatedByActor, AActor* InActivator);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Triggerable")
	bool bAllowMultipleUses = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category = "Triggerable")
	TArray<UHTriggerActivator*> Activators;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category = "Triggerable")
	TArray<UHTriggerCondition*> Conditions;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category = "Triggerable")
	TArray<UHTriggerAction*> Actions;
	

	// Internal
	
	bool RunTriggerable(bool bInActivatedByActor, AActor* InActivator);
	bool bDisableTriggering = false;
};

