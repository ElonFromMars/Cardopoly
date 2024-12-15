using UnrealBuildTool;

public class Cardopoly : ModuleRules
{
	public Cardopoly(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		OptimizeCode = CodeOptimization.Never;
		
		AddEngineModules();
		AddExternalModules();
	}

	private void AddEngineModules()
	{
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"EnhancedInput",
			"UMG",
		});
	}

	private void AddExternalModules()
	{
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"FCTween",
			"FlecsLibrary",
			"SDFutureExtensions",
		});
	}
}
