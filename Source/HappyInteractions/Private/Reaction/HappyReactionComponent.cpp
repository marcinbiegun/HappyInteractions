// Copyright SpaceCatLabs. All Rights Reserved.

#include "Reaction/HappyReactionComponent.h"
#include "Reaction/Action/HappyAction.h"
#include "Reaction/Activator/HappyActivator.h"
#include "Reaction/Condition/HappyCondition.h"

void UHappyReactionComponent::OnReactionExecuted_Implementation(AActor* ExecutorActor)
{
}

bool UHappyReactionComponent::ExecuteReaction(AActor* ExecutorActor)
{
	if (ExecutorActor)
		return DoExecuteReaction(true, ExecutorActor);
	else
		return DoExecuteReaction(false, ExecutorActor);
}

// bool UHappyReactionComponent::TryToExecuteReaction()
// {
// 	return DoExecuteReaction(false, nullptr);
// }
//
// bool UHappyReactionComponent::TryToExecuteReaction(AActor* InActivator)
// {
// 	return DoExecuteReaction(true, InActivator);
// }

// void UHappyReactionComponent::ExecuteReactionFromBlueprint(const AActor* ActivatorActor)
// {
// }
//
// void UHappyReactionComponent::OnReactionExecuted(bool bInActivatedByActor, AActor* InActivator)
// {
// 	DoExecuteReaction(bInActivatedByActor, InActivator);
// }

bool UHappyReactionComponent::DoExecuteReaction(bool bExecutorActorExists, const AActor* ExecutorActor)
{
	if (!bEnabled)
		return false;

	// Check conditions
	bool bAllConditionsPassing = true;
	for (UHappyCondition* Condition : Conditions)
	{
		if (Condition)
		{
			if (!Condition->IsConditionPassing())
			{
				bAllConditionsPassing = false;
				break;
			}
		}
	}
	if (!bAllConditionsPassing)
		return false;

	AActor* Owner = GetOwner();
	if (!Owner)
		return false;
	
	// Run actions
	for (UHappyAction* Action : Actions)
	{
		if (Action)
		{
			Action->ExecuteAction(Owner, ExecutorActor);
		}
	}

	if (bDisableAfterUse)
		bEnabled = false;

	return true;
}


