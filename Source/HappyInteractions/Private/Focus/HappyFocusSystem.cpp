// Copyright SpaceCatLabs. All Rights Reserved.

#include "Focus/HappyFocusSystem.h"

UHappyFocusSystem::UHappyFocusSystem()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHappyFocusSystem::InitializeSystem(UCameraComponent* InCameraComponent)
{
	Camera = InCameraComponent;
}

void UHappyFocusSystem::ActivateSystem(AHappyFocusActor* InFocusActor)
{
	FocusActor = InFocusActor;
	
	OnBeforeSystemActivated.Broadcast(FocusActor);
	InFocusActor->ActivateFocus();
	OnAfterSystemActivated.Broadcast(FocusActor);
}

void UHappyFocusSystem::DeactivateSystem()
{
	if (!FocusActor)
		return;

	OnBeforeSystemDeactivated.Broadcast(FocusActor);
	FocusActor->DeactivateFocus();
	OnAfterSystemDeactivated.Broadcast(FocusActor);
	FocusActor = nullptr;
}

void UHappyFocusSystem::TickComponent(float DeltaTime, ELevelTick Tick, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, Tick, ThisTickFunction);

}

void UHappyFocusSystem::AddControllerYawInput(float InValue)
{
	if (FocusActor)
	{
		FocusActor->OnFocusYawInput(InValue);
	}
}

void UHappyFocusSystem::AddControllerPitchInput(float InValue)
{
	if (FocusActor)
	{
		FocusActor->OnFocusPitchInput(InValue);
	}
}

void UHappyFocusSystem::ControllerFireAction()
{
	if (FocusActor)
	{
		FocusActor->OnFocusClickInput();
	}
}
