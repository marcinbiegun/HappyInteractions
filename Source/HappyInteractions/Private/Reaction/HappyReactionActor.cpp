// Fill out your copyright notice in the Description page of Project Settings.

#include "Reaction/HappyReactionActor.h"

AHappyReactionActor::AHappyReactionActor()
{
	PrimaryActorTick.bCanEverTick = true;

	ReactionComponent = CreateDefaultSubobject<UHappyReactionComponent>(TEXT("Reaction"));
}
