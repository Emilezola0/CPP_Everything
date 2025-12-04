// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BpToCpp_Exemples56 : ModuleRules
{
	public BpToCpp_Exemples56(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"BpToCpp_Exemples56",
			"BpToCpp_Exemples56/Variant_Platforming",
			"BpToCpp_Exemples56/Variant_Platforming/Animation",
			"BpToCpp_Exemples56/Variant_Combat",
			"BpToCpp_Exemples56/Variant_Combat/AI",
			"BpToCpp_Exemples56/Variant_Combat/Animation",
			"BpToCpp_Exemples56/Variant_Combat/Gameplay",
			"BpToCpp_Exemples56/Variant_Combat/Interfaces",
			"BpToCpp_Exemples56/Variant_Combat/UI",
			"BpToCpp_Exemples56/Variant_SideScrolling",
			"BpToCpp_Exemples56/Variant_SideScrolling/AI",
			"BpToCpp_Exemples56/Variant_SideScrolling/Gameplay",
			"BpToCpp_Exemples56/Variant_SideScrolling/Interfaces",
			"BpToCpp_Exemples56/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
