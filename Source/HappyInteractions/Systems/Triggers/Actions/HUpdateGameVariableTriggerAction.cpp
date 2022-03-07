// Copyright SpaceCatLabs. All Rights Reserved.

#include "HUpdateGameVariableTriggerAction.h"
#include "Core/HGameplayStatics.h"
#include "Utils/HUtils.h"

void UHUpdateGameVariableTriggerAction::ExecuteAction_Implementation(bool bInHasOwner, AActor* InOwner,
                                                                     bool bInHasActivator, AActor* InActivator)
{
	const FName GameVariableName = HUtils::GameplayTagToFName(GameVariable);
	if (GameVariableName.IsNone())
		return;
	
	if (UHGameVariableSubsystem* VariablesSubsystem = UHGameplayStatics::GetGameVariableSubsystem(this))
	{
		switch (Operation) {
		case EHVariableOperation::SetTrue:
			VariablesSubsystem->SetTrue(GameVariableName);
			break;
		case EHVariableOperation::SetFalse:
			VariablesSubsystem->SetFalse(GameVariableName);
			break;
		case EHVariableOperation::SetValue:
			VariablesSubsystem->Set(GameVariableName, Value);
			break;
		case EHVariableOperation::Increment:
			VariablesSubsystem->Increment(GameVariableName);
			break;
		case EHVariableOperation::Decrement:
			VariablesSubsystem->Decrement(GameVariableName);
			break;
		}
	}
}

