// Copyright SpaceCatLabs. All Rights Reserved.

#include "Focus/HappyFocusSystem.h"

UHappyFocusSystem::UHappyFocusSystem()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHappyFocusSystem::BeginPlay()
{
	Super::BeginPlay();

	if (const AActor* Owner = GetOwner())
	{
		Camera = Cast<UCameraComponent>(Owner->GetComponentByClass(UCameraComponent::StaticClass()));
	}
}

void UHappyFocusSystem::ActivateSystem(AHappyFocusActor* InFocusActor)
{
	FocusedActor = InFocusActor;
	
	OnBeforeSystemActivated.Broadcast(FocusedActor);
	InFocusActor->ActivateFocus();
	OnAfterSystemActivated.Broadcast(FocusedActor);
}

void UHappyFocusSystem::DeactivateSystem()
{
	if (!FocusedActor)
		return;

	OnBeforeSystemDeactivated.Broadcast(FocusedActor);
	FocusedActor->DeactivateFocus();
	OnAfterSystemDeactivated.Broadcast(FocusedActor);
	FocusedActor = nullptr;
}

void UHappyFocusSystem::TickComponent(float DeltaTime, ELevelTick Tick, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, Tick, ThisTickFunction);

}

void UHappyFocusSystem::AddControllerYawInput(float InValue)
{
	if (FocusedActor)
	{
		FocusedActor->OnFocusYawInput(InValue);
	}
}

void UHappyFocusSystem::AddControllerPitchInput(float InValue)
{
	if (FocusedActor)
	{
		FocusedActor->OnFocusPitchInput(InValue);
	}
}

void UHappyFocusSystem::ControllerFireAction()
{
	if (FocusedActor)
	{
		FocusedActor->OnFocusClickInput();
	}
}
