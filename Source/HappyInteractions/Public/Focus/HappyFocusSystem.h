// Copyright SpaceCatLabs. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Focus/HappyFocusActor.h"
#include "Camera/CameraComponent.h"
#include "HappyFocusSystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHappyOnFocusSystemChange, AHappyFocusActor*, FocusActor);

/**
 * This should be placed on a character actor, it is responsible for handling inspection mechanic (looking at actors at close).
 */
UCLASS()
class HAPPYINTERACTIONS_API UHappyFocusSystem : public UActorComponent
{
	GENERATED_BODY()

	UHappyFocusSystem();

public:
	
	FHappyOnFocusSystemChange OnBeforeSystemActivated;
	FHappyOnFocusSystemChange OnAfterSystemActivated;
	
	FHappyOnFocusSystemChange OnBeforeSystemDeactivated;
	FHappyOnFocusSystemChange OnAfterSystemDeactivated;
	
	// System state
	void InitializeSystem(UCameraComponent* InCameraComponent);
	void ActivateSystem(AHappyFocusActor* InFocusActor);
	void DeactivateSystem();
	bool IsSystemActivated() const { return FocusActor == nullptr; }

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Pass player input
	void AddControllerYawInput(float InValue);
	void AddControllerPitchInput(float InValue);
	void ControllerFireAction();

	UPROPERTY()
	UCameraComponent* Camera = nullptr;

protected:

	UPROPERTY()
	AHappyFocusActor* FocusActor;
	
	/** Transition time in seconds */
	UPROPERTY(EditAnywhere)
	float TransitionTime = 1.f;
	
};

