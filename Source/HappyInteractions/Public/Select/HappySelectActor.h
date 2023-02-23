// Copyright SpaceCatLabs. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "HappySelectActor.generated.h"

class UHappySelectComponent;

/**
 * Base class with single HappySelectComponent which fires a blueprint event on use.
 */
UCLASS(Abstract, Blueprintable)
class AHappySelectActor : public AActor
{
	GENERATED_BODY()

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:

	AHappySelectActor();

protected:

	UPROPERTY(EditAnywhere)
	UHappySelectComponent* SelectComponent = nullptr;
	
	UFUNCTION(BlueprintNativeEvent)
	void OnSelectActorUsed(AActor* Executor);

};

