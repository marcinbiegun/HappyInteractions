// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class HappyInteractions : ModuleRules
{
	public HappyInteractions(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PrivateIncludePaths.AddRange(new string[] { "HappyInteractions" });

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG", "GameplayTags" });
	}
}
