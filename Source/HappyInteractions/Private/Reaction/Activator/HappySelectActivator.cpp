// Copyright SpaceCatLabs. All Rights Reserved.

#include "Reaction/Activator/HappySelectActivator.h"
#include "Select/HappySelectComponent.h"

void UHappySelectActivator::Initialize(AActor* InOwner)
{
	Super::Initialize(InOwner);

	SelectComponent = Cast<UHappySelectComponent>(InOwner->GetDefaultSubobjectByName(SelectComponentName));
	if (SelectComponent)
		SelectComponent->OnSelectUsed.AddDynamic(this, &UHappySelectActivator::OnSelectComponentUsed);
}

void UHappySelectActivator::Deinitialize(AActor* InOwner)
{
	if (SelectComponent)
	{
		SelectComponent->OnSelectUsed.RemoveDynamic(this, &UHappySelectActivator::OnSelectComponentUsed);
		SelectComponent = nullptr;
	}
	
	Super::Deinitialize(InOwner);
}

void UHappySelectActivator::OnSelectComponentUsed(AActor* InExecutor)
{
	ExecuteActivator(InExecutor);
}
