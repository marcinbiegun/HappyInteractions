// Copyright SpaceCatLabs. All Rights Reserved.

#include "HOverlapTriggerActivator.h"

void UHOverlapTriggerActivator::Initialize(AActor* InOwner)
{
	Super::Initialize(InOwner);

	OverlapComponent = Cast<UPrimitiveComponent>(InOwner->GetDefaultSubobjectByName(OverlapComponentName));
	if (OverlapComponent)
	{
		OverlapComponent->OnComponentBeginOverlap.AddDynamic(this, &UHOverlapTriggerActivator::OnBeginOverlap);
	}
}

void UHOverlapTriggerActivator::Deinitialize(AActor* InOwner)
{
	Super::Deinitialize(InOwner);
	
	if (OverlapComponent)
	{
		OverlapComponent->OnComponentBeginOverlap.RemoveAll(this);
	}
}

void UHOverlapTriggerActivator::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	bool bActorFilterPassed = false;
	switch (ActorFilter)
	{
	case EHSubclassFilter::AnyActor:
		bActorFilterPassed = true;
		break;
	case EHSubclassFilter::PawnOnly:
		if (APawn* Pawn = Cast<APawn>(Other))
		{
			bActorFilterPassed = true;
		}
		break;
	}

	if (bActorFilterPassed)
	{
		ActivateActivatorByActor(Other);
	}
}
