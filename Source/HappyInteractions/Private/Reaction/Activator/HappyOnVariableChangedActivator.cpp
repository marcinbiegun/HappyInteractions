// Copyright SpaceCatLabs. All Rights Reserved.

#include "Reaction/Activator/HappyOnVariableChangedActivator.h"

#include "Variable/HappyVariableSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Utils/HappyUtils.h"

void UHappyOnVariableChangedActivator::InitializeActivator(AActor* InOwner)
{
	Super::InitializeActivator(InOwner);

	const FName GameVariableName = HappyUtils::GameplayTagToName(GameVariable);
	if (GameVariableName.IsNone())
		return;
	
	if (UHappyVariableSubsystem* VariablesSubsystem = HappyUtils::GetVariableSubsystem(this))
	{
		VariablesSubsystem->GetOnUpdateDelegate(GameVariableName).AddDynamic(this, &UHappyOnVariableChangedActivator::OnGameVariableUpdate);
	}
}

void UHappyOnVariableChangedActivator::DeinitializeActivator(AActor* InOwner)
{
	Super::DeinitializeActivator(InOwner);

	const FName GameVariableName = HappyUtils::GameplayTagToName(GameVariable);
	if (GameVariableName.IsNone())
		return;
	
	if (UHappyVariableSubsystem* VariablesSubsystem = HappyUtils::GetVariableSubsystem(this))
	{
		VariablesSubsystem->GetOnUpdateDelegate(GameVariableName).RemoveDynamic(this, &UHappyOnVariableChangedActivator::OnGameVariableUpdate);
	}
}

void UHappyOnVariableChangedActivator::OnGameVariableUpdate(FName InGameplayTagName, int32 InValue)
{
	ExecuteActivator(nullptr);
}
