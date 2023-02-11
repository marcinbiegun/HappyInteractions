// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "HappyInteractionsStyle.h"

class FHappyInteractionsCommands : public TCommands<FHappyInteractionsCommands>
{
public:

	FHappyInteractionsCommands()
		: TCommands<FHappyInteractionsCommands>(TEXT("HappyInteractions"), NSLOCTEXT("Contexts", "HappyInteractions", "HappyInteractions Plugin"), NAME_None, FHappyInteractionsStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};