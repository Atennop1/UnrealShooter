// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UnrealShooter : ModuleRules
{
	public UnrealShooter(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDependencyModuleNames.AddRange(new[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "Niagara", "AIModule", "UMG" });
		PrivateDependencyModuleNames.AddRange(new string[] {  });
	}
}
