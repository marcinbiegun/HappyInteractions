// Copyright SpaceCatLabs. All Rights Reserved.

#include "Reaction/Condition/HappyVariableCondition.h"
#include "Variable/HappyVariableSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Utils/HappyUtils.h"

bool UHappyVariableCondition::IsConditionPassing_Implementation()
{
	const FName VariableName = HappyUtils::GameplayTagToName(Variable);
	if (VariableName.IsNone())
		return false;

	if (UHappyVariableSubsystem* VariableSubsystem = HappyUtils::GetVariableSubsystem(this))
	{
		const int32 SubsystemValue = VariableSubsystem->Get(VariableName);
		switch (Check)
		{
			case EHappyVariableCheck::IsTrue:
				return SubsystemValue != 0;
			case EHappyVariableCheck::IsFalse:
				return SubsystemValue == 0;
			case EHappyVariableCheck::IsGreater:
				return SubsystemValue > Value;
			case EHappyVariableCheck::IsGreaterOrEqual:
				return SubsystemValue >= Value;
			case EHappyVariableCheck::IsLess:
				return SubsystemValue < Value;
			case EHappyVariableCheck::IsLessOrEqual:
				return SubsystemValue <= Value;
		}
	}
			
	return false;
}
