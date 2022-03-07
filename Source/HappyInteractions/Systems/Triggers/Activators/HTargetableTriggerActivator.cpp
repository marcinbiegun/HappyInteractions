// Copyright SpaceCatLabs. All Rights Reserved.

#include "HTargetableTriggerActivator.h"

void UHTargetableTriggerActivator::Initialize(AActor* InOwner)
{
	Super::Initialize(InOwner);

	TargetableComponent = Cast<UHTargetableComponent>(InOwner->GetDefaultSubobjectByName(TargetableComponentName));
	if (TargetableComponent)
		TargetableComponent->OnUse.AddDynamic(this, &UHTargetableTriggerActivator::OnTargetableUse);
}

void UHTargetableTriggerActivator::Deinitialize(AActor* InOwner)
{
	if (TargetableComponent)
	{
		TargetableComponent->OnUse.RemoveDynamic(this, &UHTargetableTriggerActivator::OnTargetableUse);
		TargetableComponent = nullptr;
	}
	
	Super::Deinitialize(InOwner);
}

void UHTargetableTriggerActivator::OnTargetableUse(AActor* InExecutor)
{
	ActivateActivatorByActor(InExecutor);
}
