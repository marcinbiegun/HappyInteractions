// Copyright SpaceCatLabs. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "HappyReactionComponent.h"
#include "HappyReactionActivatorsComponent.generated.h"

UCLASS(BlueprintType, Blueprintable, ClassGroup="HappyInteractions", meta=(DisplayName = "Reaction with Activators Component", BlueprintSpawnableComponent))
class UHappyReactionActivatorsComponent : public UHappyReactionComponent
{
	GENERATED_BODY()
	
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
public:

	void AddActivator(UHappyActivator* InActivator) { Activators.Add(InActivator); }
	
protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category = "Reaction")
	TArray<UHappyActivator*> Activators;
	
	UFUNCTION()
	void ReceiveActivation(AActor* ExecutorActor);
};
