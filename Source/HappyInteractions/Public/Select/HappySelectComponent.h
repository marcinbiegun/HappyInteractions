// Copyright SpaceCatLabs. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "HappySelectComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHappyOnSelectUsed, AActor*, ExecutorActor);

/**
 * Component that can be selected as a interaction target
 *
 * Box is used for visibility check.
 */
UCLASS(Blueprintable, Meta = (BlueprintSpawnableComponent))
class HAPPYINTERACTIONS_API UHappySelectComponent : public UBoxComponent
{
	GENERATED_BODY()

	UHappySelectComponent();
	
	virtual void BeginPlay() override;
	
public:

	void Use(AActor* InExecutorActor);
	
	UPROPERTY(BlueprintAssignable)
	FHappyOnSelectUsed OnSelectUsed;

	TArray<UStaticMeshComponent*> GetSelectableStaticMeshes() const;
	
	FName GetActionName() const { return ActionName; }

	UPROPERTY(EditAnywhere)
	bool bCheckVisibilityWithOwningActor = false;

protected:
	
	UPROPERTY(EditAnywhere)
	FName ActionName = FName(TEXT("Use"));

	/**
	 * Which static mesh components should highlight when this SelectComponent is selected.
	 * Empty list = all static meshes wil be used
	 */
	UPROPERTY(EditAnywhere)
	TArray<FName> SelectableComponentNames;

	UPROPERTY(Transient)
	TArray<UStaticMeshComponent*> SelectableComponents;

};

