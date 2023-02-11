// Copyright SpaceCatLabs. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "HappyActivator.h"
#include "HappyOverlapActivator.generated.h"


UENUM(BlueprintType)
enum class EHappySubclassFilter : uint8
{
	AnyActor = 0,
	PawnOnly = 1,
	CharacterOnly = 2,
};

/**
 * Fires on overlap.
 */
UCLASS(meta=(DisplayName = "On Self Overlap"))
class HAPPYINTERACTIONS_API UHappyOverlapActivator : public UHappyActivator
{
	GENERATED_BODY()

public:

	virtual void Initialize(AActor* InOwner) override;
	virtual void Deinitialize(AActor* InOwner) override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
protected:

	/** The name of component on actor, that is owning this action, that will be used for detecting overlaps */
	UPROPERTY(EditAnywhere)
	FName OverlapComponentName;
	
	UPROPERTY()
	UPrimitiveComponent* OverlapComponent = nullptr;
	
	// TODO: see cpp file
	// UPROPERTY(EditAnywhere)
	// TSubclassOf<AActor> OnlySubclassOf = AActor::StaticClass();
	
	/** Set which kinds of actors will fire the activation. */
	UPROPERTY(EditAnywhere)
	EHappySubclassFilter ActorFilter = EHappySubclassFilter::CharacterOnly;
	
};
