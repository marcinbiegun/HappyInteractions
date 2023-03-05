// Copyright SpaceCatLabs. All Rights Reserved.

#include "Inspect/HappyInspectActor.h"
#include "Inspect/HappyInspectSystem.h"
#include "Reaction/Action/HappyAction.h"
#include "Select/HappySelectComponent.h"

AHappyInspectActor::AHappyInspectActor()
{
	SceneRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("InspectRoot"));
	SceneRootComponent->SetupAttachment(RootComponent);

	SelectComponent = CreateDefaultSubobject<UHappySelectComponent>(TEXT("Select"));
	SelectComponent->SetupAttachment(SceneRootComponent);
}

bool AHappyInspectActor::ExecutePreInspectActions(AActor* ExecutorActor)
{
	if (bRunPreActionsOnce && bPreActionsExecuted)
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
	if (bRunPostActionsOnce && bPostActionsExecuted)
		return false;
	
	for (UHappyAction* Action : PostInspectActions)
	{
		if (Action)
			Action->ExecuteAction(this, ExecutorActor);
	}

	bPostActionsExecuted = true;
	return true;
}

void AHappyInspectActor::ActivateInspect()
{
	OnInspectActivated();
}

void AHappyInspectActor::DeactivateInspect()
{
	OnInspectDeactivated();
}
