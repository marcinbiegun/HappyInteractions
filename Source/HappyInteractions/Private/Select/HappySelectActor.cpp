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
		SelectComponent->OnUse.AddDynamic(this, &AHappySelectActor::OnUse);
}

void AHappySelectActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (SelectComponent)
		SelectComponent->OnUse.RemoveAll(this);
}

void AHappySelectActor::OnUse_Implementation(AActor* Executor)
{
}

