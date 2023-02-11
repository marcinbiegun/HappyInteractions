// Copyright SpaceCatLabs. All Rights Reserved.

#include "Reaction/Action/HappyUpdateVariableAction.h"
#include "Utils/HappyUtils.h"
#include "Variable/HappyVariableSubsystem.h"
#include "Kismet/GameplayStatics.h"

void UHappyUpdateVariableAction::ExecuteAction_Implementation(const AActor* OwnerActor, const AActor* ExecutorActor)
{
	const FName GameVariableName = HappyUtils::GameplayTagToFName(Variable);
	if (GameVariableName.IsNone())
		return;

	if (const UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(this))
	{
		if (UHappyVariableSubsystem* VariablesSubsystem = GameInstance->GetSubsystem<UHappyVariableSubsystem>())
		{
			switch (Operation)
			{
			case EHappyVariableOperation::SetTrue:
				VariablesSubsystem->SetTrue(GameVariableName);
				break;
			case EHappyVariableOperation::SetFalse:
				VariablesSubsystem->SetFalse(GameVariableName);
				break;
			case EHappyVariableOperation::SetValue:
				VariablesSubsystem->Set(GameVariableName, Value);
				break;
			case EHappyVariableOperation::Increment:
				VariablesSubsystem->Increment(GameVariableName);
				break;
			case EHappyVariableOperation::Decrement:
				VariablesSubsystem->Decrement(GameVariableName);
				break;
			}
		}
	}
}

