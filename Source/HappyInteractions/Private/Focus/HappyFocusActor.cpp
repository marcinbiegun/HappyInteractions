// Fill out your copyright notice in the Description page of Project Settings.


#include "Focus/HappyFocusActor.h"
#include "Camera/CameraComponent.h"
#include "Focus/HappyFocusSystem.h"
#include "Select/HappySelectComponent.h"


AHappyFocusActor::AHappyFocusActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SceneRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SceneRootComponent->SetupAttachment(RootComponent);

	FocusCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FocusCamera"));
	FocusCameraComponent->SetupAttachment(SceneRootComponent);

	SelectComponent = CreateDefaultSubobject<UHappySelectComponent>(TEXT("Select"));
	SelectComponent->SetupAttachment(SceneRootComponent);
}

// Called when the game starts or when spawned
void AHappyFocusActor::BeginPlay()
{
	Super::BeginPlay();
	
	SelectComponent->OnUse.AddDynamic(this, &AHappyFocusActor::OnUse);
}

void AHappyFocusActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
	SelectComponent->OnUse.RemoveAll(this);
}

void AHappyFocusActor::OnUse(AActor* InExecutor)
{
	// TODO: try to remove this dependency
	if (UHappyFocusSystem* FocusSystem = Cast<UHappyFocusSystem>(
		InExecutor->GetComponentByClass(UHappyFocusSystem::StaticClass())
	))
	{
		FocusSystem->ActivateSystem(this);
	}
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

