// Copyright SpaceCatLabs. All Rights Reserved.

#include "Reaction/Activator/HappyOverlapActivator.h"
#include "GameFramework/Character.h"

void UHappyOverlapActivator::InitializeActivator(AActor* InOwner)
{
	Super::InitializeActivator(InOwner);

	OverlapComponent = Cast<UPrimitiveComponent>(InOwner->GetDefaultSubobjectByName(OverlapComponentName));
	if (OverlapComponent)
	{
		OverlapComponent->OnComponentBeginOverlap.AddDynamic(this, &UHappyOverlapActivator::OnBeginOverlap);
	}
}

void UHappyOverlapActivator::DeinitializeActivator(AActor* InOwner)
{
	Super::DeinitializeActivator(InOwner);
	
	if (OverlapComponent)
	{
		OverlapComponent->OnComponentBeginOverlap.RemoveAll(this);
	}
}

void UHappyOverlapActivator::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Other->GetClass()->IsChildOf(ActorClassFilter))
	{
		ExecuteActivator(Other);
	}
}
