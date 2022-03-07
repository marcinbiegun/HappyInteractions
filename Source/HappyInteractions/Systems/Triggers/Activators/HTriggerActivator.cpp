// Copyright SpaceCatLabs. All Rights Reserved.

#include "HTriggerActivator.h"

void UHTriggerActivator::ActivateActivator() const
{
	OnActivated.Broadcast(false, nullptr);
}

void UHTriggerActivator::ActivateActivatorByActor(AActor* InActivator) const
{
	OnActivated.Broadcast(true, InActivator);
}
