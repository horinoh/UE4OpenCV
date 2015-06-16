// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.IO;

public class UE4OpenCV : ModuleRules
{
	public UE4OpenCV(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore",
															"RHI", "RenderCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");
		// if ((Target.Platform == UnrealTargetPlatform.Win32) || (Target.Platform == UnrealTargetPlatform.Win64))
		// {
		//		if (UEBuildConfiguration.bCompileSteamOSS == true)
		//		{
		//			DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");
		//		}
		// }

		if(UnrealTargetPlatform.Win64 == Target.Platform)
		{
			var ModulePath = Path.GetDirectoryName(RulesCompiler.GetModuleFilename(GetType().Name));
			var ThirdPartyPath = Path.GetFullPath(Path.Combine(ModulePath, "..", "..", "ThirdParty"));
			var BasePath = Path.Combine(ThirdPartyPath, "opencv", "build");

			var Configuration = (Target.Configuration == UnrealTargetConfiguration.Debug) ? "Debug" : "Release";
			var LibDllConfiguration = (Target.Configuration == UnrealTargetConfiguration.Debug) ? "d" : "";

			var LibPath = Path.Combine(BasePath, "lib", Configuration);
			PublicLibraryPaths.Add(LibPath);

			var LibDllNames = new string[] { 
				  "opencv_calib3d",
				  "opencv_core",
				  "opencv_features2d",
				  "opencv_flann",
				  "opencv_hal",
				  "opencv_highgui",
				  "opencv_imgcodecs",
				  "opencv_imgproc",
				  "opencv_ml",
				  "opencv_objdetect",
				  "opencv_photo",
				  "opencv_shape",
				  "opencv_stitching",
				  "opencv_superres",
				  "opencv_ts",
				  "opencv_video",
				  "opencv_videoio",
				  "opencv_videostab",
			};
			var Version = "300";
			foreach (var i in LibDllNames)
			{
				var LibDllName = i + Version + LibDllConfiguration;
				PublicAdditionalLibraries.Add(Path.Combine(LibPath, LibDllName + ".lib"));
				PublicDelayLoadDLLs.Add(LibDllName + ".dll");
			}
			PublicIncludePaths.Add(Path.Combine(BasePath, "include"));
		}
	}
}
