// Copyright SpaceCatLabs. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/HUD.h"
#include "HHUD.generated.h"


class UHMainHUDWidget;

/**
 * 
 */
UCLASS()
class AHHUD : public AHUD
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

protected:
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UHMainHUDWidget> MainWidgetClass = nullptr;
	
	UPROPERTY(BlueprintReadOnly)
	UHMainHUDWidget* MainWidget = nullptr;
	
	UPROPERTY(EditAnywhere)	
	FGameplayTag InventoryParentTag;

	UPROPERTY(EditAnywhere)
	TMap<FGameplayTag, UTexture2D*> InventoryIcons;
	
	UFUNCTION()
	void OnGameVariableUpdate(const FName InKey, const int32 InValue);
	
	TArray<UTexture2D*> TexturesForCollectedItems(FGameplayTagContainer InInventoryItemTags);
};

