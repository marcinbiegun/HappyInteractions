// Copyright SpaceCatLabs. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "HappyActivator.h"
#include "HappyOverlapActivator.generated.h"


/**
 * Fires on overlap.
 */
UCLASS(meta=(DisplayName = "On Overlap"))
class HAPPYINTERACTIONS_API UHappyOverlapActivator : public UHappyActivator
{
	GENERATED_BODY()

public:

	virtual void InitializeActivator(AActor* InOwner) override;
	virtual void DeinitializeActivator(AActor* InOwner) override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
protected:

	/** The name of component on actor, that is owning this action, that will be used for detecting overlaps */
	UPROPERTY(EditAnywhere)
	FName OverlapComponentName;
	
	UPROPERTY()
	UPrimitiveComponent* OverlapComponent = nullptr;
	
	/** Set which kinds of actors will fire the activation. */
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ActorClassFilter = AActor::StaticClass();
	
};
