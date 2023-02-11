// Copyright Epic Games, Inc. All Rights Reserved.

#include "HappyInteractionsCommands.h"

#define LOCTEXT_NAMESPACE "FHappyInteractionsModule"

void FHappyInteractionsCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "HappyInteractions", "Bring up HappyInteractions window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
