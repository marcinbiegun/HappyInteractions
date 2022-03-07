// Copyright SpaceCatLabs. All Rights Reserved.

#include "HTriggerableComponent.h"
#include "Actions/HTriggerAction.h"
#include "Activators/HTriggerActivator.h"
#include "Conditions/HTriggerCondition.h"


void UHTriggerableComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	if (!Owner)
		return;

	for (UHTriggerActivator* Activator : Activators)
	{
		if (Activator)
		{
			Activator->Initialize(Owner);
			Activator->OnActivated.AddDynamic(this, &UHTriggerableComponent::OnActivatorActivated);
		}
	}
}

void UHTriggerableComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	AActor* Owner = GetOwner();
	if (!Owner)
		return;
	
	for (UHTriggerActivator* Activator : Activators)
	{
		if (Activator)
		{
			Activator->OnActivated.RemoveDynamic(this, &UHTriggerableComponent::OnActivatorActivated);
			Activator->Deinitialize(Owner);
		}
	}
	
	Super::EndPlay(EndPlayReason);
}

bool UHTriggerableComponent::TryToTrigger()
{
	return RunTriggerable(false, nullptr);
}

bool UHTriggerableComponent::TryToTrigger(AActor* InActivator)
{
	return RunTriggerable(true, InActivator);
}

void UHTriggerableComponent::OnActivatorActivated(bool bInActivatedByActor, AActor* InActivator)
{
	RunTriggerable(bInActivatedByActor, InActivator);
}

bool UHTriggerableComponent::RunTriggerable(bool bInActivatedByActor, AActor* InActivator)
{
	if (bDisableTriggering)
		return false;

	// Check conditions
	bool bAllConditionsPassing = true;
	for (UHTriggerCondition* Condition : Conditions)
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
	for (UHTriggerAction* Action : Actions)
	{
		if (Action)
		{
			Action->ExecuteAction(true, Owner, bInActivatedByActor, InActivator);
		}
	}

	// Mark triggered
	if (!bAllowMultipleUses)
		bDisableTriggering = true;

	return true;
}


