// Copyright SpaceCatLabs. All Rights Reserved.

#pragma once

#include "HappyAction.h"

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "HappyUpdateVariableAction.generated.h"

UENUM(BlueprintType)
enum class EHappyVariableOperation : uint8
{
	SetTrue = 0,
	SetFalse = 1,
	SetValue = 2,
	Increment = 3,
	Decrement = 4,
};

UCLASS(meta=(DisplayName = "Update Variable"))
class HAPPYINTERACTIONS_API UHappyUpdateVariableAction : public UHappyAction
{
	
	GENERATED_BODY()
	
public:

	virtual void ExecuteAction_Implementation(const AActor* OwnerActor, const AActor* ExecutorActor);

protected:

	UPROPERTY(EditAnywhere)
	EHappyVariableOperation Operation = EHappyVariableOperation::SetTrue;
	
	UPROPERTY(EditAnywhere)
	FGameplayTag Variable;
	
	UPROPERTY(EditAnywhere, meta = (EditCondition = "Operation == EHappyVariableOperation::SetValue"))
	int32 Value = 0;
};
