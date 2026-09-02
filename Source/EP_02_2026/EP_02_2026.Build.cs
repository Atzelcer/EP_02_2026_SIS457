// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class EP_02_2026 : ModuleRules
{
	public EP_02_2026(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
