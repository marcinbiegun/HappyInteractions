// Copyright SpaceCatLabs. All Rights Reserved.

#include "HHUD.h"

#include "GameplayTagsManager.h"
#include "HMainHUDWidget.h"
#include "Core/HGameplayStatics.h"
#include "Subsystems/HGameVariableSubsystem.h"
#include "Utils/HUtils.h"

void AHHUD::BeginPlay()
{
	Super::BeginPlay();
	
	if (MainWidgetClass) 
	{
		MainWidget = CreateWidget<UHMainHUDWidget>(GetOwningPlayerController(), MainWidgetClass);
		MainWidget->AddToViewport();
		MainWidget->SetVisibility(ESlateVisibility::Visible);
	}
	
    if (UHGameVariableSubsystem* GameVariableSubsystem = UHGameplayStatics::GetGameVariableSubsystem(this))
    {
	    GameVariableSubsystem->GetOnAnyUpdateDelegate().AddDynamic(this, &AHHUD::OnGameVariableUpdate);
    }
}

void AHHUD::OnGameVariableUpdate(const FName InKey, const int32 InValue)
{
	// Convert changed variable to GameplayTag
	const UGameplayTagsManager& TagManager = UGameplayTagsManager::Get();
	const FGameplayTag ChangedTag = TagManager.RequestGameplayTag(InKey, false);
	if (!ChangedTag.IsValid())
		return;

	// Check if changed tag is inventory tag
	if (!ChangedTag.MatchesTag(InventoryParentTag))
		return;

	// Crate array with textures of inventory items that are currently collected
	const FGameplayTagContainer InventoryItemTags = TagManager.RequestGameplayTagChildren(InventoryParentTag);
	const TArray<UTexture2D*> NewInventoryIcons = TexturesForCollectedItems(InventoryItemTags);

	if (MainWidget)
	{
		MainWidget->RedrawInventoryIcons(NewInventoryIcons);
	}
}

TArray<UTexture2D*> AHHUD::TexturesForCollectedItems(FGameplayTagContainer InInventoryItemTags)
{
	TArray<UTexture2D*> NewInventoryIcons;
    if (UHGameVariableSubsystem* GameVariableSubsystem = UHGameplayStatics::GetGameVariableSubsystem(this))
    {
		for (FGameplayTag InventoryTag : InInventoryItemTags)
		{
			if (GameVariableSubsystem->IsTrue(HUtils::GameplayTagToFName(InventoryTag)))
			{
				if (InventoryIcons.Contains(InventoryTag))
				{
					 NewInventoryIcons.Add(InventoryIcons[InventoryTag]);
				}
			}
		}
    }
	return NewInventoryIcons;
}
