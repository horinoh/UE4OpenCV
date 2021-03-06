// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.IO;
using Tools.DotNETCommon;

public class UE4OpenCV : ModuleRules
{
	 private string ThirdPartyPath
    {
        get { return Path.GetFullPath(Path.Combine(ModuleDirectory, "..", "..", "ThirdParty")); }
    }

	public UE4OpenCV(ReadOnlyTargetRules Target) : base(Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore",
															"RHI", "RenderCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

        PrivatePCHHeaderFile = "UE4OpenCV.h";

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

        if (UnrealTargetPlatform.Win64 == Target.Platform)
		{
			var BasePath = Path.Combine(ThirdPartyPath, "opencv", "install");

			var Configuration = (Target.Configuration == UnrealTargetConfiguration.Debug) ? "d" : "";

			var LibPath = Path.Combine(BasePath, "x64", "vc14", "lib");
			var DllPath = Path.Combine(BasePath, "x64", "vc14", "bin");
			PublicLibraryPaths.Add(LibPath);

			var Names = new string[] { 
				  "opencv_calib3d",
				  "opencv_core",
				  "opencv_features2d",
				  "opencv_flann",
				  //"opencv_hal",
				  "opencv_highgui",
				  "opencv_imgcodecs",
				  "opencv_imgproc",
				  "opencv_ml",
				  "opencv_objdetect",
				  "opencv_photo",
				  "opencv_shape",
				  "opencv_stitching",
				  "opencv_superres",
				  //"opencv_ts",
				  "opencv_video",
				  "opencv_videoio",
				  "opencv_videostab",
			};
			//var Version = "310";
			var Version = "320";
			foreach (var i in Names)
			{
				var Name = i + Version + Configuration;
				PublicAdditionalLibraries.Add(Path.Combine(LibPath, Name + ".lib"));
				PublicDelayLoadDLLs.Add(Name + ".dll");
			}

			//PublicAdditionalLibraries.Add(Path.Combine(LibPath, "opencv_ts" + Version + Configuration + ".lib"));
			PublicDelayLoadDLLs.Add("opencv_ffmpeg"+ Version + "_64" + ".dll");

			PublicIncludePaths.Add(Path.Combine(BasePath, "include"));
		}
	}
}
