// Copyright SpaceCatLabs. All Rights Reserved.

#include "Select/HappySelectComponent.h"

UHappySelectComponent::UHappySelectComponent()
{
	BoxExtent = FVector(10.f, 10.f, 10.f);
}

void UHappySelectComponent::BeginPlay()
{
	Super::BeginPlay();

	// Find and store a static mesh component
	
	// A: Connect all static meshes
	if (SelectableComponentNames.IsEmpty())
	{
		TArray<UStaticMeshComponent*> StaticMeshComponents;
		GetOwner()->GetComponents<UStaticMeshComponent>(StaticMeshComponents);
		for (UStaticMeshComponent* StaticMeshComponent : StaticMeshComponents)
		{
			if (StaticMeshComponent)
				SelectableComponents.Add(StaticMeshComponent);
		}
	}
	// B: Connect only selected static meshes
	else
	{
		if (AActor* Owner = GetOwner())
		{
			for (const FName& StaticMeshComponentName : SelectableComponentNames)
			{
				if (UStaticMeshComponent* StaticMeshComponent = Cast<UStaticMeshComponent>(Owner->GetDefaultSubobjectByName(StaticMeshComponentName)))
				{
					SelectableComponents.Add(StaticMeshComponent);
				}
			}
		}
	}

	// Enable CustomDepth pass for post-process to be able to display the selection outline
	for (UStaticMeshComponent* StaticMeshComponent : SelectableComponents)
		StaticMeshComponent->SetRenderCustomDepth(true);
	
	if (SelectableComponents.IsEmpty())
	{
		// TODO: LogTemp
		UE_LOG(LogTemp, Error, TEXT("Unable to find StaticMeshComponents parented by this, it's not be possible to display that the object is selected"));
	}
}

void UHappySelectComponent::Use(AActor* InExecutor)
{
	OnUse.Broadcast(InExecutor);
}

TArray<UStaticMeshComponent*> UHappySelectComponent::GetSelectableStaticMeshes() const
{
	return SelectableComponents;
}
