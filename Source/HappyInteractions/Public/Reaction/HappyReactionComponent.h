// Copyright SpaceCatLabs. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "HappyReactionComponent.generated.h"

class UHappyCondition;
class UHappyActivator;
class UHappyAction;

/**
 * This important component connects trigger activators, conditions and actions into single piece of logic.
 *
 * When fired manually or by using an activator, it checks all conditions and if they all are satisfied it
 * will run all actions.
 */
UCLASS(BlueprintType, Blueprintable, ClassGroup="HappyInteractions", meta=(DisplayName = "Reaction Component", BlueprintSpawnableComponent))
class HAPPYINTERACTIONS_API UHappyReactionComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Reaction")
	bool ExecuteReaction(AActor* ActivatorActor);
	
	UFUNCTION(BlueprintCallable)
	void SetEnabled(bool bNewEnabled) { bEnabled = bNewEnabled; }
	
	UFUNCTION(BlueprintNativeEvent)
	void OnReactionExecuted(AActor* ExecutorActor);

protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Reaction")
	bool bDisableAfterUse = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Reaction")
	bool bEnabled = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category = "Reaction")
	TArray<UHappyCondition*> Conditions;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category = "Reaction")
	TArray<UHappyAction*> Actions;

	// Internal
	bool DoExecuteReaction(bool bInActivatedByActor, const AActor* InActivator);
};

