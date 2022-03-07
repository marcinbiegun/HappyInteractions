// Copyright SpaceCatLabs. All Rights Reserved.

#include "HTargetableComponent.h"
#include "HTargetableIconUserWidget.h"

UHTargetableComponent::UHTargetableComponent()
{
	BoxExtent = FVector(10.f, 10.f, 10.f);
}

void UHTargetableComponent::BeginPlay()
{
	Super::BeginPlay();

	// Find and store an icon component
	TArray<UHTargetableIconComponent*> IconComponents;
	GetOwner()->GetComponents<UHTargetableIconComponent>(IconComponents);
	for (UHTargetableIconComponent* Icon : IconComponents)
	{
		if (Icon)
			TargetableIconComponent = Icon;
	}
	if (!TargetableIconComponent)
		UE_LOG(LogHUserInterface, Error, TEXT("Unable to find InteractableIconComponent"));
}

void UHTargetableComponent::Use(AActor* InExecutor)
{
	OnUse.Broadcast(InExecutor);
}

UHTargetableIconComponent* UHTargetableComponent::GetTargetableIcon() const
{
	return TargetableIconComponent;
}
