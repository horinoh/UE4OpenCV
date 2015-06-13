// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4OpenCV.h"

class FOpenCVGameModuleImpl : public FDefaultGameModuleImpl
{
public:
	virtual void StartupModule()
	{
#if UE_BUILD_DEBUG
		const auto DllRoot = FPaths::GameContentDir() / TEXT("../ThirdParty/opencv/build/bin") / TEXT("Debug/");
#else
		const auto DllRoot = FPaths::GameContentDir() / TEXT("../ThirdParty/opencv/build/bin") / TEXT("Release/");
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
			const auto Version = "300";
			for (const auto i : DllNames)
			{
#if UE_BUILD_DEBUG
				DllHandles.Add(FPlatformProcess::GetDllHandle(*(DllRoot + i + Version + "d.dll")));
#else
				DllHandles.Add(FPlatformProcess::GetDllHandle(*(DllRoot + i + Version + ".dll")));
#endif
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
