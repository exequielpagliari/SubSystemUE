// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SubSystems : ModuleRules
{
	public SubSystems(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "RHI", "GameplayTags" });
	}
}
