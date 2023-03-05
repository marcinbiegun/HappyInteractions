// Copyright SpaceCatLabs. All Rights Reserved.

#include "Select/HappySelectComponent.h"
#include "Utils/HappyGlobals.h"

DEFINE_LOG_CATEGORY(LogHappyInteractionsSelectComponent)

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
				UE_LOG(LogHappyInteractionsSelectComponent, Error, TEXT("%s: StaticMeshComponent \"%s\" will not highlight, because it has nanite enabled"), *StaticMeshComponent->GetName(), *FString(__FUNCTION__));
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
		UE_LOG(LogHappyInteractionsSelectComponent, Error, TEXT("%s: No highlightable StaticMeshComponents were found"), *FString(__FUNCTION__));
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
