// Copyright SpaceCatLabs. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "HMainHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class UHMainHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent)
	void RedrawInventoryIcons(const TArray<UTexture2D*>& VisibleIcons);

};
