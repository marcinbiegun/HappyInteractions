// Copyright SpaceCatLabs. All Rights Reserved.

#include "HTargetingSystem.h"

#include "HTargetableComponent.h"

DEFINE_LOG_CATEGORY(LogHTargetingSystem);

UHTargetingSystem::UHTargetingSystem()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
}

void UHTargetingSystem::BeginPlay()
{
	Super::BeginPlay();
	InteractionRangeSquared = FMath::Pow(InteractionRange, 2);
}

void UHTargetingSystem::TickComponent(float DeltaTime, ELevelTick Tick, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, Tick, ThisTickFunction);

	// Find targetable components in range
	TSet<UPrimitiveComponent*> ComponentsInRange;
	GetOverlappingComponents(ComponentsInRange);
	TSet<UHTargetableComponent*> NewTargetableComponents;
	for (UPrimitiveComponent* PrimitiveComponent : ComponentsInRange)
	{
		if (UHTargetableComponent* TargetableComponent = Cast<UHTargetableComponent>(PrimitiveComponent))
		{
			NewTargetableComponents.Add(TargetableComponent);
		}
	}

	// Just ensure everything hidden
	if (bSystemDisabled)
	{
		for (const UHTargetableComponent* TargetableComponent : TargetableComponents) {
			if (UHTargetableIconComponent* TargetableIcon = TargetableComponent->GetTargetableIcon())
			{
				TargetableIcon->Hide();
			}
		}
		
		for (const UHTargetableComponent* TargetableComponent : NewTargetableComponents) {
			if (UHTargetableIconComponent* TargetableIcon = TargetableComponent->GetTargetableIcon())
			{
				TargetableIcon->Hide();
			}
		}

		CurrentTargetableComponent = nullptr;
		TargetableComponents = NewTargetableComponents;
		return;
	}

	// Show/hide targetable components
	TSet<UHTargetableComponent*> AppearedTargetableComponents = NewTargetableComponents.Difference(TargetableComponents);
	TSet<UHTargetableComponent*> DisappearedTargetableComponents = TargetableComponents.Difference(NewTargetableComponents);

	for (UHTargetableComponent* AppearedTargetableComponent : AppearedTargetableComponents) {
		if (UHTargetableIconComponent* TargetableIcon = AppearedTargetableComponent->GetTargetableIcon())
		{
			// TargetableIcon->Show();
		}
	}

	for (const UHTargetableComponent* DisappearedTargetableComponent : DisappearedTargetableComponents) {
		if (UHTargetableIconComponent* TargetableIcon = DisappearedTargetableComponent->GetTargetableIcon())
		{
			TargetableIcon->Hide();
		}
	}

	TArray<FHTargetable> Targetables;
	BuildTargetables(NewTargetableComponents, Targetables);

	// Update icon states
	// Pick selected
	float BestAim = TNumericLimits<float>::Max();
	UHTargetableComponent* BestTargetableComponent = nullptr;
	
	for (const FHTargetable& Targetable : Targetables)
	{
		UHTargetableIconComponent* TargetableIcon = Targetable.Targetable->GetTargetableIcon();
		if (!TargetableIcon)
			continue;

		// Again check visibility, now with complete data
		if (Targetable.bIsVisible)
		{
			TargetableIcon->Show();
		}
		else
		{
			TargetableIcon->Hide();
		}

		// Again check all conditions and also if it's the best aim
		if (Targetable.bIsVisible && Targetable.DistanceSquared < InteractionRangeSquared && Targetable.Angle < BestAim)
		{
			BestAim = Targetable.Angle;
			BestTargetableComponent = Targetable.Targetable;
		}
	}

	for (const FHTargetable& Targetable : Targetables)
	{
		UHTargetableIconComponent* TargetableIcon = Targetable.Targetable->GetTargetableIcon();
		if (!TargetableIcon)
			continue;
		
		if (Targetable.Targetable == BestTargetableComponent)
		{
			TargetableIcon->Selected();
		}
		else
		{
			if (Targetable.DistanceSquared < InteractionRangeSquared)
			{
				TargetableIcon->Unselected();
			}
			else
			{
				TargetableIcon->OutOfReach();
			}
		}
	}

	// Store active target
	CurrentTargetableComponent = BestTargetableComponent;
	
	// Prepare for next tick
	TargetableComponents = NewTargetableComponents;
}

void UHTargetingSystem::Use()
{
	if (CurrentTargetableComponent)
	{
		if (APawn* OwnerPawn = Cast<APawn>(GetOwner()))
		{
			CurrentTargetableComponent->Use(OwnerPawn);
		}
	}
}

void UHTargetingSystem::SetSystemDisabled(bool bInDisabled)
{
	bSystemDisabled = bInDisabled;
}

void UHTargetingSystem::BuildTargetables(const TSet<UHTargetableComponent*> InTargetableComponents,
                                         TArray<FHTargetable>& OutTargetables) const
{
	UWorld* World = GetWorld();
	if (!World)
		return;
	
	for (UHTargetableComponent* TargetableComponent : InTargetableComponents)
	{
		OutTargetables.Add(BuildTargetable(World, TargetableComponent));
	}
}

FHTargetable UHTargetingSystem::BuildTargetable(UWorld* InWorld, UHTargetableComponent* InTargetableComponent) const
{
	// Compute angle
	FVector ForwardVector = GetForwardVector();
	FVector TargetVector = InTargetableComponent->GetComponentLocation() - GetComponentLocation();
	TargetVector.Normalize();

	// Angle is always a positive number
	float TargetAngle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(ForwardVector, TargetVector)));

	// Compute Distance
	const float DistanceSquared = FVector::DistSquared(
		InTargetableComponent->GetComponentLocation(),
		GetComponentLocation()
	);

	// Check visibility
	FHitResult VisibilityHit;
	FCollisionQueryParams VisibilityQuery;
	VisibilityQuery.AddIgnoredActor(GetOwner());
	VisibilityQuery.AddIgnoredActor(InTargetableComponent->GetOwner());

	// Only blocking
	VisibilityQuery.bIgnoreTouches = true;
	
	const bool bVisibilityHit = InWorld->LineTraceSingleByChannel(
		VisibilityHit,
		GetComponentLocation(),
		InTargetableComponent->GetComponentLocation(),
		TargetVisibilityChannel,
		VisibilityQuery,
		FCollisionResponseParams::DefaultResponseParam
	);

	return FHTargetable{
		InTargetableComponent,
		DistanceSquared,
		TargetAngle,
		!bVisibilityHit
	};
}

