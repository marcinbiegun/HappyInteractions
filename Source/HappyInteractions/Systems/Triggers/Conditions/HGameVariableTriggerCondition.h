// Copyright SpaceCatLabs. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "HTriggerCondition.h"
#include "HGameVariableTriggerCondition.generated.h"


UENUM(BlueprintType)
enum class EHVariableCheck : uint8
{
	IsTrue = 0,
	IsFalse = 1,
	IsGreater = 2,
	IsGreaterOrEqual = 3,
	IsLess = 4,
	IsLessOrEqual = 5
};

/**
 * Checks value of a GameplayVariable.
 */
UCLASS(meta=(DisplayName = "Gameplay Variable Value"))
class UHGameVariableTriggerCondition : public UHTriggerCondition
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FGameplayTag GameVariable;
	
	UPROPERTY(EditAnywhere)
	EHVariableCheck Check = EHVariableCheck::IsTrue;
	
	UPROPERTY(EditAnywhere, meta = (EditCondition = "Check == EHVariableCheck::IsGreater || Check == EHVariableCheck::IsGreaterOrEqual || Check == EHVariableCheck::IsLess || Check == EHVariableCheck::IsLessOrEqual"))
	int32 Value = 0;

	virtual bool IsConditionPassing_Implementation() override;
	
};
