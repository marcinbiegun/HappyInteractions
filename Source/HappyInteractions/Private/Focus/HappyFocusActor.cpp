// Fill out your copyright notice in the Description page of Project Settings.

#include "Focus/HappyFocusActor.h"
#include "Camera/CameraComponent.h"
#include "Select/HappySelectComponent.h"

AHappyFocusActor::AHappyFocusActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SceneRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("FocusRoot"));
	SceneRootComponent->SetupAttachment(RootComponent);

	FocusCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FocusCamera"));
	FocusCameraComponent->SetupAttachment(SceneRootComponent);

	SelectComponent = CreateDefaultSubobject<UHappySelectComponent>(TEXT("Select"));
	SelectComponent->SetupAttachment(SceneRootComponent);
}

void AHappyFocusActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHappyFocusActor::ActivateFocus()
{
	OnFocusActivated();
}

void AHappyFocusActor::DeactivateFocus()
{
	OnFocusDeactivated();
}

