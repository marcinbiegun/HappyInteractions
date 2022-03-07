// Copyright SpaceCatLabs. All Rights Reserved.

#include "HOnGameVariableChangeTriggerActivator.h"

#include "Core/HGameplayStatics.h"
#include "Utils/HUtils.h"

void UHOnGameVariableChangeTriggerActivator::Initialize(AActor* InOwner)
{
	Super::Initialize(InOwner);

	const FName GameVariableName = HUtils::GameplayTagToFName(GameVariable);
	if (GameVariableName.IsNone())
		return;
	
	if (UHGameVariableSubsystem* VariablesSubsystem = UHGameplayStatics::GetGameVariableSubsystem(this))
	{
		VariablesSubsystem->GetOnUpdateDelegate(GameVariableName).AddDynamic(this, &UHOnGameVariableChangeTriggerActivator::OnGameVariableUpdate);
	}
}

void UHOnGameVariableChangeTriggerActivator::Deinitialize(AActor* InOwner)
{
	Super::Deinitialize(InOwner);

	const FName GameVariableName = HUtils::GameplayTagToFName(GameVariable);
	if (GameVariableName.IsNone())
		return;
	
	if (UHGameVariableSubsystem* VariablesSubsystem = UHGameplayStatics::GetGameVariableSubsystem(this))
	{
		VariablesSubsystem->GetOnUpdateDelegate(GameVariableName).RemoveDynamic(this, &UHOnGameVariableChangeTriggerActivator::OnGameVariableUpdate);
	}
}

void UHOnGameVariableChangeTriggerActivator::OnGameVariableUpdate(FName InGameplayTagName, int32 InValue)
{
	ActivateActivator();
}
