// Copyright SpaceCatLabs. All Rights Reserved.

#include "HTriggerableActor.h"

#include "Systems/Targeting/HTargetableComponent.h"
#include "Systems/Triggers/HTriggerableComponent.h"

AHTriggerableActor::AHTriggerableActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	
	const FName TargetableName = TEXT("Targetable");
	TargetableComponent = CreateDefaultSubobject<UHTargetableComponent>(TargetableName);
	TargetableComponent->SetupAttachment(RootComponent);
	TargetableIconComponent = CreateDefaultSubobject<UHTargetableIconComponent>(TEXT("TargetableIcon"));
	TargetableIconComponent->SetupAttachment(TargetableComponent);
	
	TriggerableComponent = CreateDefaultSubobject<UHTriggerableComponent>(TEXT("Triggerable"));
}
