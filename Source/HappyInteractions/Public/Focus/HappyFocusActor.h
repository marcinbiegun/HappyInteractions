// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HappyFocusActor.generated.h"

class UHappySelectComponent;
class UCameraComponent;

UCLASS(Abstract, Blueprintable)
class HAPPYINTERACTIONS_API AHappyFocusActor : public AActor
{
	GENERATED_BODY()

public:
	AHappyFocusActor();
	virtual void Tick(float DeltaTime) override;

	void ActivateFocus();
	void DeactivateFocus();
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnFocusActivated();
	void OnFocusActivated_Implementation();
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnFocusDeactivated();
	void OnFocusDeactivated_Implementation();

	UFUNCTION(BlueprintImplementableEvent)
	void OnFocusYawInput(float InValue);
	void OnFocusYawInput_Implementation(float InValue) {}
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnFocusPitchInput(float InValue);
	void OnFocusPitchInput_Implementation(float InValue) {};
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnFocusClickInput();
	void OnFocusClickInput_Implementation() {}

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	UFUNCTION()
	void OnSelectComponentUsed(AActor* InExecutor);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* FocusCameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* SceneRootComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UHappySelectComponent* SelectComponent;
};
