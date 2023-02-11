// Copyright SpaceCatLabs. All Rights Reserved.

#include "Inspect/HappyInspectActor.h"
#include "Inspect/HappyInspectSystem.h"
#include "Select/HappySelectComponent.h"

AHappyInspectActor::AHappyInspectActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	
	SelectComponent = CreateDefaultSubobject<UHappySelectComponent>(TEXT("HappyTargetableComponent"));
	SelectComponent->SetupAttachment(RootComponent);
}

void AHappyInspectActor::BeginPlay()
{
	Super::BeginPlay();
	
	SelectComponent->OnUse.AddDynamic(this, &AHappyInspectActor::OnUse);
}

void AHappyInspectActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	SelectComponent->OnUse.RemoveAll(this);
}

void AHappyInspectActor::OnUse(AActor* InExecutor)
{
	// TODO: remove this dependency?
	if (UHappyInspectSystem* InspectionSystem = Cast<UHappyInspectSystem>(
		InExecutor->GetComponentByClass(UHappyInspectSystem::StaticClass())
	))
	{
		InspectionSystem->ActivatedSystem(this);
	}
	// if (AHAdventureFirstPersonCharacter* FirstPersonCharacter = Cast<AHAdventureFirstPersonCharacter>(InExecutor))
	// {
	// 	FirstPersonCharacter->StartInspection(this);
	// }
}

void AHappyInspectActor::SetTargetIconHidden(bool bInHidden)
{
}
