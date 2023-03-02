// Copyright SpaceCatLabs. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "HappySelectSystem.generated.h"

class UCameraComponent;
class UHappySelectComponent;

DECLARE_LOG_CATEGORY_EXTERN(LogHappySelectSystem, Log, All);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHappyOnSelectActionNameChanged, FName, InActionName);

struct FHappySelectable {
	UHappySelectComponent* SelectComponent = nullptr;
	float DistanceSquared = TNumericLimits<float>::Max();
	float Angle = 180.f;
	float DistanceToForwardLine = 0.f;
	bool bIsVisible = false;
};

/**
 * System used for selecting a targetable actor, that then can be activated as an user action.
 *
 * The targetable components will be visible if they are inside the main sphere component.
 */
UCLASS(BlueprintType, Blueprintable, ClassGroup="HappyInteractions", meta=(DisplayName = "HappySelectSystem", BlueprintSpawnableComponent))
class HAPPYINTERACTIONS_API UHappySelectSystem : public UActorComponent
{
	GENERATED_BODY()
	
	virtual void BeginPlay() override;

public:

	UHappySelectSystem();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FHappyOnSelectActionNameChanged OnActionNameChanged;

	UFUNCTION(BlueprintCallable)
	bool UseCurrentSelectComponent();
	
	UFUNCTION(BlueprintCallable)
	UHappySelectComponent* GetCurrentSelectComponent() { return CurrentSelectComponent; }
	
	UFUNCTION(BlueprintCallable)
	void ActivateSystem();
	
	UFUNCTION(BlueprintCallable)
	void DeactivateSystem();

protected:

	UPROPERTY(EditAnywhere, Category="Select System")
	float VisibilityRange = 500.f;
	
	UPROPERTY(EditAnywhere, Category="Select System")
	float InteractionRange = 250.f;
	float InteractionRangeSquared = -1.f;
	
	UPROPERTY(EditAnywhere, Category="Select System")
	float SelectionSphereRadius = 50.f;

	UPROPERTY(EditAnywhere, Category="Select System")
	TEnumAsByte<ECollisionChannel> SelectVisibilityChannel;
	
	UPROPERTY(EditAnywhere, Category="Select System")
	int32 StencilMaskUnselected = 1;
	
	UPROPERTY(EditAnywhere, Category="Select System")
	int32 StencilMaskSelected = 2;
	
	UPROPERTY(EditAnywhere, Category="Select System")
	int32 StencilMaskOutOfReach = 1;
	
	UPROPERTY(EditAnywhere, Category="Select System")
	int32 StencilMaskNothing = 0;

	UPROPERTY()
	UHappySelectComponent* CurrentSelectComponent;
	
	UPROPERTY()
	UCameraComponent* CameraComponent;
	
	bool bSystemDisabled = false;

	FHappySelectable BuildSelectable(UWorld* InWorld, UHappySelectComponent* InSelectComponent) const;

	void BuildSelectables(const TSet<UHappySelectComponent*> InSelectComponents, TArray<FHappySelectable>& OutSelectables) const;
	TSet<UHappySelectComponent*> SelectComponents;

	// Show/hide near targetables
	void SetSelectableSelected(const UHappySelectComponent* InSelectComponent);
	void SetSelectableUnselected(const UHappySelectComponent* InSelectComponent);
	void SetSelectableOutOfReach(const UHappySelectComponent* InSelectComponent);
	void ShowSelectable(const UHappySelectComponent* InSelectComponent);
	void HideSelectable(const UHappySelectComponent* InSelectComponent);
	
	void TraceOverlappingComponents(TSet<UPrimitiveComponent*>& OutOverlappingComponents);
};
