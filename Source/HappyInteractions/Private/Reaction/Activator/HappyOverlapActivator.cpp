// Copyright SpaceCatLabs. All Rights Reserved.

#include "Reaction/Activator/HappyOverlapActivator.h"
#include "GameFramework/Character.h"

void UHappyOverlapActivator::Initialize(AActor* InOwner)
{
	Super::Initialize(InOwner);

	OverlapComponent = Cast<UPrimitiveComponent>(InOwner->GetDefaultSubobjectByName(OverlapComponentName));
	if (OverlapComponent)
	{
		OverlapComponent->OnComponentBeginOverlap.AddDynamic(this, &UHappyOverlapActivator::OnBeginOverlap);
	}
}

void UHappyOverlapActivator::Deinitialize(AActor* InOwner)
{
	Super::Deinitialize(InOwner);
	
	if (OverlapComponent)
	{
		OverlapComponent->OnComponentBeginOverlap.RemoveAll(this);
	}
}

void UHappyOverlapActivator::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	bool bActorFilterPassed = false;
	switch (ActorFilter)
	{
	case EHappySubclassFilter::AnyActor:
		bActorFilterPassed = true;
		break;
	case EHappySubclassFilter::PawnOnly:
		if (APawn* Pawn = Cast<APawn>(Other))
		{
			bActorFilterPassed = true;
		}
		break;
	case EHappySubclassFilter::CharacterOnly:
		if (ACharacter* Character = Cast<ACharacter>(Other))
		{
			bActorFilterPassed = true;
		}
	}

	if (bActorFilterPassed)
	{
		ExecuteActivator(Other);
	}

	// // TODO FIX ME: allow to set class dynamically in blueprints
	//	
	// TSubclassOf<AActor>::TClassType* SubclassOf = OnlySubclassOf.Get();
	//
	// auto Dupa = Cast<OnlySubclassOf->ClassWithin->StaticClass()>(Other);
	// auto Dupa = Cast<OnlySubclassOf->StaticClass()>(Other);
	// auto Dupa = Cast<OnlySubclassOf.Get()>(Other);
	// auto Dupa = Cast<OnlySubclassOf>(Other);
	//
	// OnlySubclassOf->StaticClass().cast
}
