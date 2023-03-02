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
UCLASS(BlueprintType, Blueprintable, ClassGroup="HappyInteractions", meta=(DisplayName = "HappyFocusSystem", BlueprintSpawnableComponent))
class HAPPYINTERACTIONS_API UHappyFocusSystem : public UActorComponent
{
	GENERATED_BODY()

	UHappyFocusSystem();

public:

	virtual void BeginPlay() override;;
	
	UPROPERTY(BlueprintAssignable)
	FHappyOnFocusSystemChange OnBeforeSystemActivated;
	UPROPERTY(BlueprintAssignable)
	FHappyOnFocusSystemChange OnAfterSystemActivated;
	
	UPROPERTY(BlueprintAssignable)
	FHappyOnFocusSystemChange OnBeforeSystemDeactivated;
	UPROPERTY(BlueprintAssignable)
	FHappyOnFocusSystemChange OnAfterSystemDeactivated;
	
	// System state
	UFUNCTION(BlueprintCallable)
	void ActivateSystem(AHappyFocusActor* InFocusActor);
	UFUNCTION(BlueprintCallable)
	void DeactivateSystem();
	UFUNCTION(BlueprintCallable)
	bool IsSystemActivated() const { return FocusedActor == nullptr; }

	// Pass player input
	UFUNCTION(BlueprintCallable)
	void AddControllerYawInput(float InValue);
	UFUNCTION(BlueprintCallable)
	void AddControllerPitchInput(float InValue);
	UFUNCTION(BlueprintCallable)
	void ControllerFireAction();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY()
	UCameraComponent* Camera = nullptr;

protected:

	UPROPERTY()
	AHappyFocusActor* FocusedActor;
	
	/** Transition time in seconds */
	UPROPERTY(EditAnywhere)
	float TransitionTime = 1.f;
	
};

