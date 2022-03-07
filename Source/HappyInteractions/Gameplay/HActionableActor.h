// Copyright SpaceCatLabs. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "HActionableActor.generated.h"

class UHTargetableIconComponent;
class UHTargetableComponent;

/**
 * A base clas with single TargetableComponent that fires a blueprint event;
 */
UCLASS(Abstract, Blueprintable)
class AHActionableActor : public AActor
{
	GENERATED_BODY()

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:

	AHActionableActor();

protected:

	UPROPERTY(EditAnywhere)
	UHTargetableComponent* TargetableComponent = nullptr;
	
	UPROPERTY(EditAnywhere)
	UHTargetableIconComponent* TargetableIconComponent = nullptr;
	
	UFUNCTION(BlueprintNativeEvent)
	void OnUse(AActor* Executor);

};

