// Copyright SpaceCatLabs. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "HappyCondition.h"
#include "HappyVariableCondition.generated.h"


UENUM(BlueprintType)
enum class EHappyVariableCheck : uint8
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
UCLASS(meta=(DisplayName = "Check Variable"))
class HAPPYINTERACTIONS_API UHappyVariableCondition : public UHappyCondition
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FGameplayTag Variable;
	
	UPROPERTY(EditAnywhere)
	EHappyVariableCheck Check = EHappyVariableCheck::IsTrue;
	
	UPROPERTY(EditAnywhere, meta = (EditCondition = "Check == EHappyVariableCheck::IsGreater || Check == EHappyVariableCheck::IsGreaterOrEqual || Check == EHappyVariableCheck::IsLess || Check == EHappyVariableCheck::IsLessOrEqual"))
	int32 Value = 0;

	virtual bool IsConditionPassing_Implementation() override;
	
};
