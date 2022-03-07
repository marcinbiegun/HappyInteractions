// Copyright SpaceCatLabs. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "HTargetingSystem.generated.h"

class UHTargetableComponent;

DECLARE_LOG_CATEGORY_EXTERN(LogHTargetingSystem, Log, All);

struct FHTargetable {
	UHTargetableComponent* Targetable = nullptr;
	float DistanceSquared = TNumericLimits<float>::Max();
	float Angle = 180.f;
	bool bIsVisible = false;
};

/**
 * System used for selecting a targetable actor, that then can be activated as an user action.
 *
 * The targetable components will be visible if they are inside the main sphere component.
 */
UCLASS()
class UHTargetingSystem : public USphereComponent
{
	GENERATED_BODY()

public:

	UHTargetingSystem();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void Use();
	void SetSystemDisabled(bool bInDisabled);

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="Targeting System")
	float InteractionRange = 200.f;
	
	float InteractionRangeSquared = -1.f;

	UPROPERTY(EditAnywhere, Category="Targeting System")
	TEnumAsByte<ECollisionChannel> TargetVisibilityChannel;

	UPROPERTY()
	UHTargetableComponent* CurrentTargetableComponent;
	
	bool bSystemDisabled = false;

	FHTargetable BuildTargetable(UWorld* InWorld, UHTargetableComponent* TargetableComponent) const;
	void BuildTargetables(const TSet<UHTargetableComponent*> InTargetableComponents, TArray<FHTargetable>& OutTargetables) const;

	TSet<UHTargetableComponent*> TargetableComponents;
};

