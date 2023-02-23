// Copyright SpaceCatLabs. All Rights Reserved.

#include "Inspect/HappyInspectSystem.h"
#include "Reaction/Action/HappyAction.h"

UHappyInspectSystem::UHappyInspectSystem()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHappyInspectSystem::InitializeSystem(UCameraComponent* InCameraComponent)
{
	Camera = InCameraComponent;
}

void UHappyInspectSystem::ActivatedSystem(AHappyInspectActor* InInspectActor)
{
	if (!InInspectActor)
		return;

	if (!Camera)
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot start InspectionSystem: camera is nullptr!"));
		return;
	}

	OnBeforeSystemActivated.Broadcast(InInspectActor);
	UE_LOG(LogTemp, Log, TEXT("Inspection started"));
	
	InspectedActor = InInspectActor;
	ActivatedAt = GetOwner()->GetGameTimeSinceCreation();
	DeactivatedAt = 0.f;
	State = EHappyInspectSystemState::Activating;
	InspectActorOriginalLocation = InspectedActor->GetActorLocation();
	InspectActorCloseUpLocation = Camera->GetComponentLocation() + Camera->GetForwardVector() * DistanceFromCamera;
	InspectActorTakeLocation = Camera->GetComponentLocation() + Camera->GetUpVector() * DistanceBelowCameraForTake * -1.f;
	InspectActorOriginalTransform = InspectedActor->GetActorTransform();
	InspectedActor->SetSelectComponentHidden(true);
	
	OnBeforeSystemActivated.Broadcast(InInspectActor);
}

void UHappyInspectSystem::DeactivateSystem()
{
	if (!InspectedActor)
		return;

	OnBeforeSystemDeactivated.Broadcast(InspectedActor);
	
	if (State == EHappyInspectSystemState::Activating || State == EHappyInspectSystemState::Activated)
	{
		UE_LOG(LogTemp, Log, TEXT("Inspection ended"));
		State = EHappyInspectSystemState::Deactivating;
		DeactivatedAt = GetOwner()->GetGameTimeSinceCreation();
		InspectActorChangedRotation = InspectedActor->GetActorRotation();
		InspectedActor->SetSelectComponentHidden(false);
	}
	
	OnAfterSystemDeactivated.Broadcast(InspectedActor);
}

void UHappyInspectSystem::TickComponent(float DeltaTime, ELevelTick Tick, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, Tick, ThisTickFunction);

	switch (State) {
		case EHappyInspectSystemState::Activating:
			if (InspectedActor)
			{
				const FVector MoveLeft = InspectedActor->GetActorLocation() - InspectActorCloseUpLocation;
				if (MoveLeft.IsNearlyZero())
				{
					State = EHappyInspectSystemState::Activated;
				}
				else
				{
					const float ElapsedTransitionTime = GetOwner()->GetGameTimeSinceCreation() - ActivatedAt;
					const float Progress = FMath::Clamp(ElapsedTransitionTime / TransitionTime, 0.f, 1.f);
					const FVector NewLoc = FMath::Lerp(InspectActorOriginalLocation, InspectActorCloseUpLocation, Progress);
					InspectedActor->SetActorLocation(NewLoc);
				}
			}
			break;
		case EHappyInspectSystemState::Activated:
			InspectedActor->AddActorLocalRotation(RotationDelta);
			InspectedActor->ExecutePreInspectActions(Camera->GetOwner());
			RotationDelta = FRotator::ZeroRotator;
			break;
		case EHappyInspectSystemState::Deactivating:
			if (InspectedActor)
			{
				const FVector MoveLeft = InspectedActor->GetActorLocation() - GetEndingLocation();

				// Finish transition
				if (MoveLeft.IsNearlyZero())
				{
					InspectedActor->SetActorTransform(InspectActorOriginalTransform);
					InspectedActor->ExecutePostInspectActions(Camera->GetOwner());
					if (InspectedActor->IsTakeAfterInspection())
						InspectedActor->Destroy();
					InspectedActor = nullptr;
					State = EHappyInspectSystemState::Deactivated;
				}
				// Progress transition
				else
				{
					const float ElapsedTransitionTime = GetOwner()->GetGameTimeSinceCreation() - DeactivatedAt;
					float Progress = FMath::Clamp(ElapsedTransitionTime / TransitionTime, 0.f, 1.f);
					
					const FVector NewLoc = FMath::Lerp(InspectActorCloseUpLocation, GetEndingLocation(), Progress);
					InspectedActor->SetActorLocation(NewLoc);
					
					const FRotator NewRot = FMath::Lerp(InspectActorChangedRotation, InspectActorOriginalRotation, Progress);
					InspectedActor->SetActorRotation(NewRot);
				}
			}
			break;
		case EHappyInspectSystemState::Deactivated:
			break;
	}
	
}

FVector UHappyInspectSystem::GetEndingLocation() const
{
	if (InspectedActor && InspectedActor->IsTakeAfterInspection())
		return InspectActorTakeLocation;
	return InspectActorOriginalLocation;
}

void UHappyInspectSystem::AddControllerYawInput(float InValue)
{
	if (State == EHappyInspectSystemState::Activated || State == EHappyInspectSystemState::Activating)
	{
		RotationDelta.Add(0.f, InValue, 0.f);
	}
}

void UHappyInspectSystem::AddControllerPitchInput(float InValue)
{
	if (State == EHappyInspectSystemState::Activated || State == EHappyInspectSystemState::Activating)
	{
		RotationDelta.Add(InValue, 0.f, 0.f);
	}
}