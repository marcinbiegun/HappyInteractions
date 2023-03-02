// Copyright SpaceCatLabs. All Rights Reserved.

#include "Select/HappySelectComponent.h"

UHappySelectComponent::UHappySelectComponent()
{
	BoxExtent = FVector(5.f, 5.f, 5.f);
	ShapeColor = FColor::Green;
}

void UHappySelectComponent::BeginPlay()
{
	Super::BeginPlay();

	// Find and store a static mesh components to highlight
	TArray<UStaticMeshComponent*> StaticMeshComponents;
	GetOwner()->GetComponents<UStaticMeshComponent>(StaticMeshComponents);
	for (UStaticMeshComponent* StaticMeshComponent : StaticMeshComponents)
	{
		// Use if there is no component names provided (then use all), or if component name matches provided names
		if (SelectableComponentNames.IsEmpty() || SelectableComponentNames.Contains(FName(StaticMeshComponent->GetName())))
		{
			SelectableComponents.Add(StaticMeshComponent);
		}
		
		// Nanite check - stencil outline will does not work currently with Nanite :( as in 5.1
		TObjectPtr<UStaticMesh> StaticMeshPtr = StaticMeshComponent->GetStaticMesh();
		if (const UStaticMesh* StaticMesh = StaticMeshPtr.Get())
		{
			if (StaticMesh->NaniteSettings.bEnabled)
			{
				// TODO: LogTemp
				UE_LOG(LogTemp, Error, TEXT("Desired selectable static mesh component of name %s will not highlight, because it has nanite enabled"), *StaticMeshComponent->GetName());
			}
		}
	}
	
	// Ensure CustomDepth render is enabled
	for (UStaticMeshComponent* StaticMeshComponent : SelectableComponents)
	{
		StaticMeshComponent->SetRenderCustomDepth(true);
	}
		
	if (SelectableComponents.IsEmpty())
	{
		// TODO: LogTemp
		UE_LOG(LogTemp, Error, TEXT("Unable to find StaticMeshComponents parented by this, it's not be possible to display that the object is selected"));
	}
}

void UHappySelectComponent::UseSelect(AActor* InExecutorActor)
{
	OnSelectUsed.Broadcast(InExecutorActor);
}

TArray<UStaticMeshComponent*> UHappySelectComponent::GetSelectableStaticMeshes() const
{
	return SelectableComponents;
}
