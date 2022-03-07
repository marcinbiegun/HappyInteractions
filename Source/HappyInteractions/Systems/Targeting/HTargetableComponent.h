// Copyright SpaceCatLabs. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "HTargetableIconComponent.h"
#include "Components/BoxComponent.h"
#include "HTargetableComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHOnTargetableUse, AActor*, InExecutor);

/**
 * Component that can be selected as a interaction target
 *
 * Box is used for visibility check.
 * Requires TargetableIconComponent as a child component to work properly.
 */
UCLASS(Blueprintable)
class UHTargetableComponent : public UBoxComponent
{
	GENERATED_BODY()

	UHTargetableComponent();
	
	virtual void BeginPlay() override;

public:
	
	void Use(AActor* InExecutor);
	
	UPROPERTY()
	FHOnTargetableUse OnUse;

	UHTargetableIconComponent* GetTargetableIcon() const;

protected:

	UPROPERTY(Transient)
	UHTargetableIconComponent* TargetableIconComponent;

};

