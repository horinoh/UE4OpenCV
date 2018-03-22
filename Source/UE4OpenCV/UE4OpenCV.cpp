// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4OpenCV.h"

class FOpenCVGameModuleImpl : public FDefaultGameModuleImpl
{
public:
	virtual void StartupModule()
	{
		const auto DllRoot = FPaths::ProjectConfigDir() / TEXT("../ThirdParty/opencv/install/x64/vc14/bin/");
#if UE_BUILD_DEBUG
		const auto Configuration = "d";
#else
		const auto Configuration = "";
#endif
		FPlatformProcess::PushDllDirectory(*DllRoot);
		{
			const FString DllNames[] = {
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
			//const auto Version = "310";
			const auto Version = "320";
			for (const auto i : DllNames)
			{
				DllHandles.Add(FPlatformProcess::GetDllHandle(*(DllRoot + i + Version + Configuration + ".dll")));

				DllHandles.Add(FPlatformProcess::GetDllHandle(*(DllRoot + "opencv_ffmpeg" + Version + "_64.dll")));
				
				check(nullptr != DllHandles.Last());
			}
		}
		FPlatformProcess::PopDllDirectory(*DllRoot);
	}
	virtual void ShutdownModule()
	{
		for (auto i : DllHandles)
		{
			FPlatformProcess::FreeDllHandle(i);
		}
	}
	TArray<void*> DllHandles;
};

IMPLEMENT_PRIMARY_GAME_MODULE( FOpenCVGameModuleImpl, UE4OpenCV, "UE4OpenCV" );
