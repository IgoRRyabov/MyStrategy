// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MyStrategy : ModuleRules
{
	public MyStrategy(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });

		//PrivateDependencyModuleNames.AddRange(new string[] { "Eigen" });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		PrivateIncludePaths.AddRange(new string[] {"MyStrategy/Public/Player","MyStrategy/Public/Widget", "MyStrategy/Public/Components", "MyStrategy/Public/Building"});
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
