// Copyright SpaceCatLabs. All Rights Reserved.

#include "Reaction/Activator/HappyOnVariableChangedActivator.h"

#include "Variable/HappyVariableSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Utils/HappyUtils.h"

void UHappyOnVariableChangedActivator::Initialize(AActor* InOwner)
{
	Super::Initialize(InOwner);

	const FName GameVariableName = HappyUtils::GameplayTagToFName(GameVariable);
	if (GameVariableName.IsNone())
		return;
	
	if (const UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(this))
	{
		if (UHappyVariableSubsystem* VariablesSubsystem = GameInstance->GetSubsystem<UHappyVariableSubsystem>())
		{
			VariablesSubsystem->GetOnUpdateDelegate(GameVariableName).AddDynamic(this, &UHappyOnVariableChangedActivator::OnGameVariableUpdate);
		}
	}
}

void UHappyOnVariableChangedActivator::Deinitialize(AActor* InOwner)
{
	Super::Deinitialize(InOwner);

	const FName GameVariableName = HappyUtils::GameplayTagToFName(GameVariable);
	if (GameVariableName.IsNone())
		return;
	
	if (const UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(this))
	{
		if (UHappyVariableSubsystem* VariablesSubsystem = GameInstance->GetSubsystem<UHappyVariableSubsystem>())
		{
			VariablesSubsystem->GetOnUpdateDelegate(GameVariableName).RemoveDynamic(this, &UHappyOnVariableChangedActivator::OnGameVariableUpdate);
		}
	}
}

void UHappyOnVariableChangedActivator::OnGameVariableUpdate(FName InGameplayTagName, int32 InValue)
{
	ExecuteActivator(nullptr);
}
