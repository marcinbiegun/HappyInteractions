// Copyright SpaceCatLabs. All Rights Reserved.

#include "HGameVariableTriggerCondition.h"
#include "Core/HGameplayStatics.h"
#include "Subsystems/HGameVariableSubsystem.h"
#include "Utils/HUtils.h"

bool UHGameVariableTriggerCondition::IsConditionPassing_Implementation()
{
	const FName GameVariableName = HUtils::GameplayTagToFName(GameVariable);
	if (GameVariableName.IsNone())
		return false;
	
	if (UHGameVariableSubsystem* VariablesSubsystem = UHGameplayStatics::GetGameVariableSubsystem(this))
	{
		const int32 VariableValue = VariablesSubsystem->Get(GameVariableName);
		switch (Check)
		{
			case EHVariableCheck::IsTrue:
				return VariableValue != 0;
			case EHVariableCheck::IsFalse:
				return VariableValue == 0;
			case EHVariableCheck::IsGreater:
				return VariableValue > Value;
			case EHVariableCheck::IsGreaterOrEqual:
				return VariableValue >= Value;
			case EHVariableCheck::IsLess:
				return VariableValue < Value;
			case EHVariableCheck::IsLessOrEqual:
				return VariableValue <= Value;
		}
	}
	
	return false;
}
