// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HappyReactionComponent.h"
#include "GameFramework/Actor.h"
#include "HappyReactionActor.generated.h"

UCLASS()
class HAPPYINTERACTIONS_API AHappyReactionActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHappyReactionActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UHappyReactionComponent* ReactionComponent;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
