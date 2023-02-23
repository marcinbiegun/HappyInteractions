// Copyright SpaceCatLabs. All Rights Reserved.

#include "Select/HappySelectActor.h"
#include "Select/HappySelectComponent.h"

AHappySelectActor::AHappySelectActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	
	SelectComponent = CreateDefaultSubobject<UHappySelectComponent>(TEXT("Targetable"));
	SelectComponent->SetupAttachment(RootComponent);
}

void AHappySelectActor::BeginPlay()
{
	Super::BeginPlay();

	if (SelectComponent)
		SelectComponent->OnSelectUsed.AddDynamic(this, &AHappySelectActor::OnSelectActorUsed);
}

void AHappySelectActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (SelectComponent)
		SelectComponent->OnSelectUsed.RemoveAll(this);
}

void AHappySelectActor::OnSelectActorUsed_Implementation(AActor* Executor)
{
}

