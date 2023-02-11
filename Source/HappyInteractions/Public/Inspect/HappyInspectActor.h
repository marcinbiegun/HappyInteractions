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
	
	void SetTargetIconHidden(bool bInHidden);

	FText GetText() const { return Text; }
	bool HasText() const { return !Text.IsEmpty(); }
	bool IsTakeAfterUse() const { return bTakeAfterUse; }
	TArray<UHappyAction*> GetPostInspectionActions() const { return PostInspectionActions; }

protected:
	
	UFUNCTION()
	void OnUse(AActor* InExecutor);
	
	UPROPERTY(EditAnywhere)
	bool bTakeAfterUse = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
	TArray<UHappyAction*> PostInspectionActions;
	
	UPROPERTY(EditAnywhere)
	FText Text = FText::GetEmpty();
	
	UPROPERTY(EditAnywhere)
	UHappySelectComponent* SelectComponent = nullptr;
};

