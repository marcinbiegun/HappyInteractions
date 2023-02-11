// Fill out your copyright notice in the Description page of Project Settings.


#include "Reaction/HappyReactionActor.h"


// Sets default values
AHappyReactionActor::AHappyReactionActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ReactionComponent = CreateDefaultSubobject<UHappyReactionComponent>(TEXT("Reaction"));
}

// Called when the game starts or when spawned
void AHappyReactionActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHappyReactionActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

