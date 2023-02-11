// Copyright Epic Games, Inc. All Rights Reserved.

#include "HappyInteractions.h"
#include "HappyInteractionsStyle.h"
#include "HappyInteractionsCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

static const FName HappyInteractionsTabName("HappyInteractions");

#define LOCTEXT_NAMESPACE "FHappyInteractionsModule"

void FHappyInteractionsModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FHappyInteractionsStyle::Initialize();
	FHappyInteractionsStyle::ReloadTextures();

	FHappyInteractionsCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FHappyInteractionsCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FHappyInteractionsModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FHappyInteractionsModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(HappyInteractionsTabName, FOnSpawnTab::CreateRaw(this, &FHappyInteractionsModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FHappyInteractionsTabTitle", "HappyInteractions"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FHappyInteractionsModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FHappyInteractionsStyle::Shutdown();

	FHappyInteractionsCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(HappyInteractionsTabName);
}

TSharedRef<SDockTab> FHappyInteractionsModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FHappyInteractionsModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("HappyInteractions.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
		];
}

void FHappyInteractionsModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(HappyInteractionsTabName);
}

void FHappyInteractionsModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FHappyInteractionsCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FHappyInteractionsCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FHappyInteractionsModule, HappyInteractions)