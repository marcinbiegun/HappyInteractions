// Copyright SpaceCatLabs. All Rights Reserved.

#include "Select/HappySelectSystem.h"

#include "Camera/CameraComponent.h"
#include "Select/HappySelectComponent.h"
#include "Utils/HappyGlobals.h"

DEFINE_LOG_CATEGORY(LogHappyInteractionsSelect)

UHappySelectSystem::UHappySelectSystem()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
}

void UHappySelectSystem::BeginPlay()
{
	Super::BeginPlay();
	
	InteractionRangeSquared = FMath::Pow(InteractionRange, 2);
	
	if (const AActor* Owner = GetOwner())
	{
		CameraComponent = Cast<UCameraComponent>(Owner->GetComponentByClass(UCameraComponent::StaticClass()));
	}
}

void UHappySelectSystem::TraceOverlappingComponents(TSet<UPrimitiveComponent*>& OutOverlappingComponents)
{
	if (AActor* Character = GetOwner())
	{
		TArray<FOverlapResult> Results;
		FCollisionQueryParams Query;
		Query.AddIgnoredActor(Character);
		const bool bResult = GetWorld()->OverlapMultiByChannel(
			Results,
			Character->GetActorLocation(),
			FQuat::Identity,
			ECC_WorldDynamic,
			FCollisionShape::MakeSphere(VisibilityRange),
			Query,
			FCollisionResponseParams::DefaultResponseParam
		);
		for (FOverlapResult Result : Results)
		{
			if (UPrimitiveComponent* PrimitiveComponent = Result.Component.Get())
			{
				OutOverlappingComponents.Add(PrimitiveComponent);
			}
		}
	}
}

void UHappySelectSystem::TickComponent(float DeltaTime, ELevelTick Tick, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, Tick, ThisTickFunction);
	
	if (!CameraComponent)
	{
		UE_LOG(LogHappyInteractionsSelect, Error, TEXT("%s: Aborting, Camera is nullptr"), *FString(__FUNCTION__));
		return;
	}

	// Find targetable components in range
	TSet<UPrimitiveComponent*> ComponentsInRange;
	TraceOverlappingComponents(ComponentsInRange);

	TSet<UHappySelectComponent*> NewTargetableComponents;
	for (UPrimitiveComponent* PrimitiveComponent : ComponentsInRange)
	{
		if (UHappySelectComponent* TargetableComponent = Cast<UHappySelectComponent>(PrimitiveComponent))
		{
			NewTargetableComponents.Add(TargetableComponent);
		}
	}

	// Just ensure everything hidden
	if (bSystemDisabled)
	{
		for (const UHappySelectComponent* TargetableComponent : SelectComponents) {
			for (UStaticMeshComponent* StaticMeshComponent : TargetableComponent->GetSelectableStaticMeshes())
			{
				StaticMeshComponent->SetCustomDepthStencilValue(StencilMaskUnselected);
			}
		}
		
		for (const UHappySelectComponent* TargetableComponent : NewTargetableComponents) {
			for (UStaticMeshComponent* StaticMeshComponent : TargetableComponent->GetSelectableStaticMeshes())
			{
				StaticMeshComponent->SetCustomDepthStencilValue(StencilMaskUnselected);
			}
		}
		
		CurrentSelectComponent = nullptr;
		SelectComponents = NewTargetableComponents;
		return;
	}

	// Show/hide targetable components
	TSet<UHappySelectComponent*> AppearedTargetableComponents = NewTargetableComponents.Difference(SelectComponents);
	TSet<UHappySelectComponent*> DisappearedTargetableComponents = SelectComponents.Difference(NewTargetableComponents);

	// First check to eliminated glitches when targetable comes in/out of visibility reach
	for (UHappySelectComponent* AppearedTargetableComponent : AppearedTargetableComponents) {
		ShowSelectable(AppearedTargetableComponent);
	}
	for (UHappySelectComponent* DisappearedTargetableComponent : DisappearedTargetableComponents) {
		HideSelectable(DisappearedTargetableComponent);
	}

	TArray<FHappySelectable> Targetables;
	BuildSelectables(NewTargetableComponents, Targetables);

	// Update icon states
	// Pick selected
	float ClosestDistToPointOnForwardLine = TNumericLimits<float>::Max();
	UHappySelectComponent* BestTargetableComponent = nullptr;

	// Show/hide icons again with complete data (line of sight, etc.)
	for (const FHappySelectable& Targetable : Targetables)
	{
		if (Targetable.bIsVisible)
		{
			ShowSelectable(Targetable.SelectComponent);
		}
		else
		{
			HideSelectable(Targetable.SelectComponent);
		}

		// Again check all conditions and also if it's the best aim
		if (
			// Must be visible (not behind a wall)
			Targetable.bIsVisible &&
			// Must be withing interaction range
			Targetable.DistanceSquared < InteractionRangeSquared &&
			// Must have minimal dist to front-aim-line
			Targetable.DistanceToForwardLine < SelectionSphereRadius &&
			// Must have the best dist to front-aim-line
			Targetable.DistanceToForwardLine < ClosestDistToPointOnForwardLine)
		{
			// BestAim = Targetable.Angle;
			ClosestDistToPointOnForwardLine = Targetable.DistanceToForwardLine;
			BestTargetableComponent = Targetable.SelectComponent;
		}
	}

	// Set appropriate state
	for (const FHappySelectable& Targetable : Targetables)
	{
		if (Targetable.SelectComponent == BestTargetableComponent)
		{
			SetSelectableSelected(Targetable.SelectComponent);
		}
		else
		{
			if (Targetable.DistanceSquared < InteractionRangeSquared)
			{
				SetSelectableUnselected(Targetable.SelectComponent);
			}
			else
			{
				SetSelectableOutOfReach(Targetable.SelectComponent);
			}
		}
	}

	// If something was selected last frame, but his frame nothing is selectedf
	if (CurrentSelectComponent && !BestTargetableComponent)
	{
		OnActionNameChanged.Broadcast(NAME_None);
	}
	
	// Prepare for next tick
	CurrentSelectComponent = BestTargetableComponent;
	SelectComponents = NewTargetableComponents;
}

bool UHappySelectSystem::UseCurrentSelectComponent()
{
	if (CurrentSelectComponent)
	{
		if (AActor* Owner = GetOwner())
		{
			CurrentSelectComponent->UseSelect(Owner);
			return true;
		}
	}
	return false;
}

void UHappySelectSystem::ActivateSystem()
{
	bSystemDisabled = false;
}

void UHappySelectSystem::DeactivateSystem()
{
	bSystemDisabled = true;
}

void UHappySelectSystem::BuildSelectables(const TSet<UHappySelectComponent*> InSelectComponents,
                                         TArray<FHappySelectable>& OutTargetables) const
{
	UWorld* World = GetWorld();
	if (!World)
		return;
	
	for (UHappySelectComponent* SelectComponent : InSelectComponents)
	{
		OutTargetables.Add(BuildSelectable(World, SelectComponent));
	}
}

FHappySelectable UHappySelectSystem::BuildSelectable(UWorld* InWorld, UHappySelectComponent* InSelectComponent) const
{
	// Compute angle
	FVector Location = CameraComponent->GetComponentLocation();
	FVector ForwardVector = CameraComponent->GetForwardVector();
	FVector TargetVector = InSelectComponent->GetComponentLocation() - Location;
	TargetVector.Normalize();

	// Angle is always a positive number
	float TargetAngle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(ForwardVector, TargetVector)));

	const FVector PointOnForwardLine = FVector::ZeroVector;
	const float DistToForwardLine = FMath::PointDistToLine(InSelectComponent->GetComponentLocation(), ForwardVector, Location);

	// Compute distance squared
	const float DistanceSquared = FVector::DistSquared(
		InSelectComponent->GetComponentLocation(),
		Location
	);

	// Check visibility
	FHitResult VisibilityHit;
	FCollisionQueryParams VisibilityQuery;
	VisibilityQuery.AddIgnoredActor(GetOwner());

	if (!InSelectComponent->bCheckVisibilityWithOwningActor)
		VisibilityQuery.AddIgnoredActor(InSelectComponent->GetOwner());

	// Only blocking
	VisibilityQuery.bIgnoreTouches = true;
	
	const bool bVisibilityHit = InWorld->LineTraceSingleByChannel(
		VisibilityHit,
		Location,
		InSelectComponent->GetComponentLocation(),
		SelectVisibilityChannel,
		VisibilityQuery,
		FCollisionResponseParams::DefaultResponseParam
	);

	return FHappySelectable{
		InSelectComponent,
		DistanceSquared,
		TargetAngle,
		DistToForwardLine,
		!bVisibilityHit
	};
}

void UHappySelectSystem::SetSelectableSelected(const UHappySelectComponent* InSelectComponent)
{
	for (UStaticMeshComponent* StaticMeshComponent : InSelectComponent->GetSelectableStaticMeshes())
	{
		StaticMeshComponent->SetCustomDepthStencilValue(StencilMaskSelected);
	}
	
	const FName InteractionText = InSelectComponent->GetActionName();
	OnActionNameChanged.Broadcast(InteractionText);
}

void UHappySelectSystem::SetSelectableUnselected(const UHappySelectComponent* InSelectComponent)
{
	for (UStaticMeshComponent* StaticMeshComponent : InSelectComponent->GetSelectableStaticMeshes())
	{
		StaticMeshComponent->SetCustomDepthStencilValue(StencilMaskUnselected);
	}
}

void UHappySelectSystem::SetSelectableOutOfReach(const UHappySelectComponent* InSelectComponent)
{
	for (UStaticMeshComponent* StaticMeshComponent : InSelectComponent->GetSelectableStaticMeshes())
	{
		StaticMeshComponent->SetCustomDepthStencilValue(StencilMaskOutOfReach);
	}
}

void UHappySelectSystem::ShowSelectable(const UHappySelectComponent* InSelectComponent)
{
	for (UStaticMeshComponent* StaticMeshComponent : InSelectComponent->GetSelectableStaticMeshes())
	{
		StaticMeshComponent->SetCustomDepthStencilValue(StencilMaskUnselected);
	}
}

void UHappySelectSystem::HideSelectable(const UHappySelectComponent* InSelectComponent)
{
	for (UStaticMeshComponent* StaticMeshComponent : InSelectComponent->GetSelectableStaticMeshes())
	{
		StaticMeshComponent->SetCustomDepthStencilValue(StencilMaskNothing);
	}
}
