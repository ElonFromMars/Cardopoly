// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Cardopoly : ModuleRules
{
	public Cardopoly(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		OptimizeCode = CodeOptimization.Never;
		
		AddEngineModules();
		AddExternalModules();
		
		PrivateDependencyModuleNames.AddRange(new string[] {  });
		
		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}

	private void AddEngineModules()
	{
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"EnhancedInput",
		});
	}

	private void AddExternalModules()
	{
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"FCTween",
		});
	}
}
