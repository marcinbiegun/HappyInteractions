// Copyright SpaceCatLabs. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "HappyInspectActor.generated.h"

class UHappyAction;
class UHappySelectComponent;

/**
 * Base class for actors that can be inspected.
 */
UCLASS(Abstract, Blueprintable)
class HAPPYINTERACTIONS_API AHappyInspectActor : public AActor
{
	GENERATED_BODY()
	
public:

	AHappyInspectActor();
	
	void ActivateInspect();
	void DeactivateInspect();

	FText GetInspectText() const { return InspectText; }
	bool HasInspectText() const { return !InspectText.IsEmpty(); }
	bool IsTakeAfterInspection() const { return bTakeAfterInspection; }
	bool ExecutePreInspectActions(AActor* ExecutorActor);
	bool ExecutePostInspectActions(AActor* ExecutorActor);

protected:
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnInspectActivated();
	void OnInspectActivated_Implementation();
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnInspectDeactivated();
	void OnInspectDeactivated_Implementation();
	
	UPROPERTY(EditAnywhere)
	bool bTakeAfterInspection = false;
	
	UPROPERTY(EditAnywhere)
	bool bRunPreActionsOnce = true;
	
	UPROPERTY(EditAnywhere)
	bool bRunPostActionsOnce = true;
	
	UPROPERTY(EditAnywhere)
	USceneComponent* SceneRootComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
	TArray<UHappyAction*> PreInspectActions;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
	TArray<UHappyAction*> PostInspectActions;
	
	UPROPERTY(EditAnywhere)
	FText InspectText = FText::GetEmpty();
	
	UPROPERTY(EditAnywhere)
	UHappySelectComponent* SelectComponent = nullptr;

	bool bPreActionsExecuted = false;
	bool bPostActionsExecuted = false;
	
};

