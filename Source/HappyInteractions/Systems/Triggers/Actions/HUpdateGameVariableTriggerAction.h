// Copyright SpaceCatLabs. All Rights Reserved.

#pragma once

#include "HTriggerAction.h"

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "HUpdateGameVariableTriggerAction.generated.h"

UENUM(BlueprintType)
enum class EHVariableOperation : uint8
{
	SetTrue = 0,
	SetFalse = 1,
	SetValue = 2,
	Increment = 3,
	Decrement = 4,
};

UCLASS(meta=(DisplayName = "Update Game Variable"))
class UHUpdateGameVariableTriggerAction : public UHTriggerAction
{
	
	GENERATED_BODY()
	
public:

	virtual void ExecuteAction_Implementation(bool bInHasOwner, AActor* InOwner, bool bInHasActivator, AActor* InActivator) override;

protected:

	UPROPERTY(EditAnywhere)
	EHVariableOperation Operation = EHVariableOperation::SetTrue;
	
	UPROPERTY(EditAnywhere)
	FGameplayTag GameVariable;
	
	UPROPERTY(EditAnywhere, meta = (EditCondition = "Operation == EHVariableOperation::SetValue"))
	int32 Value = 0.f;
};
