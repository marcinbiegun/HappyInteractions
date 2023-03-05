// Copyright SpaceCatLabs. All Rights Reserved.

#include "Reaction/Activator/HappySelectActivator.h"
#include "Select/HappySelectComponent.h"

void UHappySelectActivator::InitializeActivator(AActor* InOwner)
{
	Super::InitializeActivator(InOwner);

	SelectComponent = Cast<UHappySelectComponent>(InOwner->GetDefaultSubobjectByName(SelectComponentName));
	if (SelectComponent)
		SelectComponent->OnSelectUsed.AddDynamic(this, &UHappySelectActivator::OnSelectComponentUsed);
}

void UHappySelectActivator::DeinitializeActivator(AActor* InOwner)
{
	if (SelectComponent)
	{
		SelectComponent->OnSelectUsed.RemoveDynamic(this, &UHappySelectActivator::OnSelectComponentUsed);
		SelectComponent = nullptr;
	}
	
	Super::DeinitializeActivator(InOwner);
}

void UHappySelectActivator::OnSelectComponentUsed(AActor* InExecutor)
{
	ExecuteActivator(InExecutor);
}
