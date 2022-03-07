// Copyright SpaceCatLabs. All Rights Reserved.

#include "HActionableActor.h"

#include "Systems/Targeting/HTargetableComponent.h"

AHActionableActor::AHActionableActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	
	TargetableComponent = CreateDefaultSubobject<UHTargetableComponent>(TEXT("Targetable"));
	TargetableComponent->SetupAttachment(RootComponent);
	TargetableIconComponent = CreateDefaultSubobject<UHTargetableIconComponent>(TEXT("TargetableIcon"));
	TargetableIconComponent->SetupAttachment(TargetableComponent);
}

void AHActionableActor::BeginPlay()
{
	Super::BeginPlay();

	if (TargetableComponent)
		TargetableComponent->OnUse.AddDynamic(this, &AHActionableActor::OnUse);
}

void AHActionableActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (TargetableComponent)
		TargetableComponent->OnUse.RemoveAll(this);
}

void AHActionableActor::OnUse_Implementation(AActor* Executor)
{
}

