// Copyright SpaceCatLabs. All Rights Reserved.

#include "Reaction/HappyReactionActivatedComponent.h"
#include "Reaction/Activator/HappyActivator.h"

void UHappyReactionActivatedComponent::BeginPlay()
{
	Super::BeginPlay();
	
	if (AActor* Owner = GetOwner()) {
		for (UHappyActivator* Activator : Activators)
		{
			if (Activator)
			{
				Activator->Initialize(Owner);
				Activator->OnActivated.AddDynamic(this, &UHappyReactionActivatedComponent::ReceiveActivation);
			}
		}
	}
}

void UHappyReactionActivatedComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (AActor* Owner = GetOwner())
	{
		for (UHappyActivator* Activator : Activators)
		{
			if (Activator)
			{
				Activator->OnActivated.RemoveDynamic(this, &UHappyReactionActivatedComponent::ReceiveActivation);
				Activator->Deinitialize(Owner);
			}
		}
	}
	
	Super::EndPlay(EndPlayReason);
}

void UHappyReactionActivatedComponent::ReceiveActivation(AActor* ExecutorActor)
{
	ExecuteReaction(ExecutorActor);
}
