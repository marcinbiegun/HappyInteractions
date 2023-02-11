// Copyright SpaceCatLabs. All Rights Reserved.

#include "Reaction/HappyReactionActivatorsComponent.h"
#include "Reaction/Activator/HappyActivator.h"

void UHappyReactionActivatorsComponent::BeginPlay()
{
	Super::BeginPlay();
	
	if (AActor* Owner = GetOwner()) {
		for (UHappyActivator* Activator : Activators)
		{
			if (Activator)
			{
				Activator->Initialize(Owner);
				Activator->OnActivated.AddDynamic(this, &UHappyReactionActivatorsComponent::ReceiveActivation);
			}
		}
	}
}

void UHappyReactionActivatorsComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (AActor* Owner = GetOwner())
	{
		for (UHappyActivator* Activator : Activators)
		{
			if (Activator)
			{
				Activator->OnActivated.RemoveDynamic(this, &UHappyReactionActivatorsComponent::ReceiveActivation);
				Activator->Deinitialize(Owner);
			}
		}
	}
	
	Super::EndPlay(EndPlayReason);
}

void UHappyReactionActivatorsComponent::ReceiveActivation(AActor* ExecutorActor)
{
	ExecuteReaction(ExecutorActor);
}
