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

	OnBeforeSystemActivated.Broadcast(InInspectActor);
	UE_LOG(LogTemp, Log, TEXT("Inspection started"));
	
	InspectActor = InInspectActor;
	ActivatedAt = GetOwner()->GetGameTimeSinceCreation();
	DeactivatedAt = 0.f;
	State = EHappyInspectSystemState::Activating;
	InspectActorOriginalLocation = InspectActor->GetActorLocation();
	InspectActorCloseUpLocation = Camera->GetComponentLocation() + Camera->GetForwardVector() * DistanceFromCamera;
	InspectActorTakeLocation = Camera->GetComponentLocation() + Camera->GetUpVector() * DistanceBelowCameraForTake * -1.f;
	InspectActorOriginalTransform = InspectActor->GetActorTransform();
	InspectActor->SetTargetIconHidden(true);
	
	OnBeforeSystemActivated.Broadcast(InInspectActor);
}

void UHappyInspectSystem::DeactivateSystem()
{
	if (!InspectActor)
		return;

	OnBeforeSystemDeactivated.Broadcast(InspectActor);
	
	if (State == EHappyInspectSystemState::Activating || State == EHappyInspectSystemState::Activated)
	{
		UE_LOG(LogTemp, Log, TEXT("Inspection ended"));
		State = EHappyInspectSystemState::Deactivating;
		DeactivatedAt = GetOwner()->GetGameTimeSinceCreation();
		InspectActorChangedRotation = InspectActor->GetActorRotation();
		InspectActor->SetTargetIconHidden(false);
	}
	
	OnAfterSystemDeactivated.Broadcast(InspectActor);
}

void UHappyInspectSystem::TickComponent(float DeltaTime, ELevelTick Tick, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, Tick, ThisTickFunction);

	switch (State) {
		case EHappyInspectSystemState::Activating:
			if (InspectActor)
			{
				const FVector MoveLeft = InspectActor->GetActorLocation() - InspectActorCloseUpLocation;
				if (MoveLeft.IsNearlyZero())
				{
					State = EHappyInspectSystemState::Activated;
				}
				else
				{
					const float ElapsedTransitionTime = GetOwner()->GetGameTimeSinceCreation() - ActivatedAt;
					const float Progress = FMath::Clamp(ElapsedTransitionTime / TransitionTime, 0.f, 1.f);
					const FVector NewLoc = FMath::Lerp(InspectActorOriginalLocation, InspectActorCloseUpLocation, Progress);
					InspectActor->SetActorLocation(NewLoc);
				}
			}
			break;
		case EHappyInspectSystemState::Activated:
			InspectActor->AddActorLocalRotation(RotationDelta);
			RotationDelta = FRotator::ZeroRotator;
			break;
		case EHappyInspectSystemState::Deactivating:
			if (InspectActor)
			{
				const FVector MoveLeft = InspectActor->GetActorLocation() - GetEndingLocation();

				// Finish transition
				if (MoveLeft.IsNearlyZero())
				{
					InspectActor->SetActorTransform(InspectActorOriginalTransform);
					for (UHappyAction* Action : InspectActor->GetPostInspectionActions())
					{
						if (Action)
							Action->ExecuteAction(GetOwner(), nullptr);
					}
					if (InspectActor->IsTakeAfterUse())
						InspectActor->Destroy();
					InspectActor = nullptr;
					State = EHappyInspectSystemState::Deactivated;
				}
				// Progress transition
				else
				{
					const float ElapsedTransitionTime = GetOwner()->GetGameTimeSinceCreation() - DeactivatedAt;
					float Progress = FMath::Clamp(ElapsedTransitionTime / TransitionTime, 0.f, 1.f);
					
					const FVector NewLoc = FMath::Lerp(InspectActorCloseUpLocation, GetEndingLocation(), Progress);
					InspectActor->SetActorLocation(NewLoc);
					
					const FRotator NewRot = FMath::Lerp(InspectActorChangedRotation, InspectActorOriginalRotation, Progress);
					InspectActor->SetActorRotation(NewRot);
				}
			}
			break;
		case EHappyInspectSystemState::Deactivated:
			break;
	}
	
}

FVector UHappyInspectSystem::GetEndingLocation() const
{
	if (InspectActor && InspectActor->IsTakeAfterUse())
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