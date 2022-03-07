// Copyright SpaceCatLabs. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HTargetableIconUserWidget.generated.h"

/**
 * UserWidget displaying interaction icon.
 */
UCLASS()
class UHTargetableIconUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent)
	void OnShow();
	void OnShow_Implementation() {}
	
	UFUNCTION(BlueprintNativeEvent)
	void OnHide();
	void OnHide_Implementation() {}
	
	UFUNCTION(BlueprintNativeEvent)
	void OnUnselected();
	void OnUnselected_Implementation() {}
	
	UFUNCTION(BlueprintNativeEvent)
	void OnSelected();
	void OnSelected_Implementation() {}
	
	UFUNCTION(BlueprintNativeEvent)
	void OnOutOfReach();
	void OnOutOfReach_Implementation() {}
	
	UFUNCTION(BlueprintNativeEvent)
	void OnSetForceHidden(const bool bInHidden);
	void OnSetForceHidden_Implementation(const bool bInHidden) {}

protected:

	
};

