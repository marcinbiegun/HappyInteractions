// Copyright SpaceCatLabs. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Inspect/HappyInspectActor.h"
#include "Camera/CameraComponent.h"
#include "HappyInspectSystem.generated.h"

enum class EHappyInspectSystemState : uint8
{
	Activating = 0,
	Activated = 1,
	Deactivating = 2,
	Deactivated = 3,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHappyOnInspectSystemChange, AHappyInspectActor*, InspectActor);

/**
 * This should be placed on a character actor, it is responsible for handling inspection mechanic (looking at actors at close).
 */
UCLASS(BlueprintType, Blueprintable, ClassGroup="HappyInteractions", meta=(DisplayName = "HappyInspectSystem", BlueprintSpawnableComponent))
class HAPPYINTERACTIONS_API UHappyInspectSystem : public UActorComponent
{
	GENERATED_BODY()

	UHappyInspectSystem();

	virtual void BeginPlay() override;
	
public:

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable)
	FHappyOnInspectSystemChange OnBeforeSystemActivated;
	UPROPERTY(BlueprintAssignable)
	FHappyOnInspectSystemChange OnAfterSystemActivated;
	
	UPROPERTY(BlueprintAssignable)
	FHappyOnInspectSystemChange OnBeforeSystemDeactivated;
	UPROPERTY(BlueprintAssignable)
	FHappyOnInspectSystemChange OnAfterSystemDeactivated;

	// System state
	UFUNCTION(BlueprintCallable)
	void ActivateSystem(AHappyInspectActor* InInspectActor);
	UFUNCTION(BlueprintCallable)
	void DeactivateSystem();
	UFUNCTION(BlueprintCallable)
	bool IsSystemActivated() const { return InspectedActor == nullptr; }

	// Player input
	UFUNCTION(BlueprintCallable)
	void AddControllerYawInput(float InValue);
	UFUNCTION(BlueprintCallable)
	void AddControllerPitchInput(float InValue);

	float GetDistanceFromCamera() const { return DistanceFromCamera; }
	
protected:
	
	UPROPERTY()
	UCameraComponent* Camera = nullptr;

	UPROPERTY()
	AHappyInspectActor* InspectedActor;
	
	UPROPERTY(EditAnywhere)
	float DistanceFromCamera = 100.f;
	
	UPROPERTY(EditAnywhere)
	float DistanceBelowCameraForTake = 50.f;

	/** Transition time in seconds */
	UPROPERTY(EditAnywhere)
	float TransitionTime = 1.f;
	
	FVector GetEndingLocation() const;
	
	FTransform InspectActorOriginalTransform = FTransform::Identity;
	
	FVector InspectActorCloseUpLocation = FVector::ZeroVector;
	FVector InspectActorTakeLocation = FVector::ZeroVector;
	FVector InspectActorOriginalLocation = FVector::ZeroVector;
	
	FRotator InspectActorOriginalRotation = FRotator::ZeroRotator;
	FRotator InspectActorChangedRotation = FRotator::ZeroRotator;
	
	EHappyInspectSystemState State = EHappyInspectSystemState::Deactivated;
	float ActivatedAt = 0.f;
	float DeactivatedAt = 0.f;

	FRotator RotationDelta = FRotator::ZeroRotator;
};

