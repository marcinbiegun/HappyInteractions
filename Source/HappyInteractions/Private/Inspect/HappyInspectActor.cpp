// Copyright SpaceCatLabs. All Rights Reserved.

#include "Inspect/HappyInspectActor.h"
#include "Inspect/HappyInspectSystem.h"
#include "Reaction/Action/HappyAction.h"
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
	SelectComponent->OnSelectUsed.AddDynamic(this, &AHappyInspectActor::OnSelectComponentUsed);
}

void AHappyInspectActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	SelectComponent->OnSelectUsed.RemoveAll(this);
	Super::EndPlay(EndPlayReason);
}

bool AHappyInspectActor::ExecutePreInspectActions(AActor* ExecutorActor)
{
	if (bRunActionsOnce && bPreActionsExecuted)
		return false;

	for (UHappyAction* Action : PreInspectActions)
	{
		if (Action)
			Action->ExecuteAction(this, ExecutorActor);
	}

	bPreActionsExecuted = true;
	return true;
}

bool AHappyInspectActor::ExecutePostInspectActions(AActor* ExecutorActor)
{
	if (bRunActionsOnce && bPostActionsExecuted)
		return false;
	
	for (UHappyAction* Action : PostInspectActions)
	{
		if (Action)
			Action->ExecuteAction(this, ExecutorActor);
	}

	bPostActionsExecuted = true;
	return true;
}

void AHappyInspectActor::OnSelectComponentUsed(AActor* InExecutor)
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

void AHappyInspectActor::SetSelectComponentHidden(bool bInHidden)
{
}
