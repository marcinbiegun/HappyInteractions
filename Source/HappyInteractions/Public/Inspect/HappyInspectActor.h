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
	
protected:
	
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:

	AHappyInspectActor();
	
	void SetSelectComponentHidden(bool bInHidden);

	FText GetInspectText() const { return InspectText; }
	bool HasInspectText() const { return !InspectText.IsEmpty(); }
	bool IsTakeAfterInspection() const { return bTakeAfterInspection; }
	bool ExecutePreInspectActions(AActor* ExecutorActor);
	bool ExecutePostInspectActions(AActor* ExecutorActor);

protected:
	
	UFUNCTION()
	void OnSelectComponentUsed(AActor* InExecutor);
	
	UPROPERTY(EditAnywhere)
	bool bTakeAfterInspection = false;
	
	UPROPERTY(EditAnywhere)
	bool bRunActionsOnce = true;
	
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

