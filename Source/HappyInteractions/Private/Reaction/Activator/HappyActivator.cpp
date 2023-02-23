// Copyright SpaceCatLabs. All Rights Reserved.

#include "Reaction/Activator/HappyActivator.h"

void UHappyActivator::ExecuteActivator(AActor* ExecutorActor) const
{
	OnActivated.Broadcast(ExecutorActor);
}
