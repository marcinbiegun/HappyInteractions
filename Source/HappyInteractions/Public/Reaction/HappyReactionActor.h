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

	AHappyReactionActor();

protected:

	UPROPERTY(EditAnywhere)
	UHappyReactionComponent* ReactionComponent;
};
