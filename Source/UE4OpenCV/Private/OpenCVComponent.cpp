// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4OpenCV.h"
#include "OpenCVComponent.h"

//#define _CRT_SECURE_NO_WARNINGS
#pragma push_macro("check")
#undef check
#pragma warning(push)
#pragma warning(disable : 4946)
#pragma warning(disable : 4996)
#pragma warning(disable : 4668)
#pragma warning(disable : 4265)
#include <opencv2/opencv.hpp>
#pragma  warning(pop)
#pragma pop_macro("check")
#include <opencv2/core/ocl.hpp>

// Sets default values for this component's properties
UOpenCVComponent::UOpenCVComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	//bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	Texture2D = UTexture2D::CreateTransient(256, 256);
	if (nullptr != Texture2D)
	{
		Texture2D->UpdateResource();
	}
}


// Called when the game starts
void UOpenCVComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	if (nullptr != Texture2D)
	{
		if (cv::ocl::haveOpenCL())
		{
			cv::ocl::Context Context;
			if (Context.create(cv::ocl::Device::TYPE_GPU))
			{
				cv::ocl::Device(Context.device(0));

				//!< Simple OpenCL Code
				const cv::String Code = "__kernel void main(__global uchar* dst, const int pitch, const int offset, const int rows, const int cols) {"
					"const int2 uv = { get_global_id(0), get_global_id(1) };"
					"const int2 dim = { rows, cols };"
					"const int2 grid = { 16, 16 };"
					"const int2 repeate = dim / grid;"
					"const int index = mad24(uv.y, pitch, uv.x + offset);"
					"dst[index] = ((uv.x % grid.x) * repeate.x >> 1) + ((uv.y % grid.y) * repeate.y >> 1);"
					"}";
				const cv::ocl::ProgramSource ProgramSource(Code);

				//!< Build OpenCL
				const cv::String Buildopt = "";
				cv::String Errmsg;
				const auto Program = Context.getProg(ProgramSource, Buildopt, Errmsg);

				const auto Width = Texture2D->GetSizeX();
				const auto Height = Texture2D->GetSizeY();
				//!< Result destination
				const auto Mat = cv::UMat(Height, Width, CV_8U, cv::ACCESS_WRITE, cv::USAGE_ALLOCATE_DEVICE_MEMORY);

				//!< OpenCL function name and arguments
				cv::ocl::Kernel Kernel("main", Program);
				Kernel.args(cv::ocl::KernelArg::ReadWrite(Mat));

				//!< Execute OpenCL
				size_t Threads[] = { Width, Height, 1 };
				if (!Kernel.run(ARRAY_COUNT(Threads), Threads, nullptr, true))
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("OpenCL run failed"));
				}

				const auto Result = Mat.getMat(cv::ACCESS_READ);

				//!< Add some OpenCV operations
				cv::putText(Mat, cv::String("Hello OpenCV"), cv::Point(0, 255), CV_FONT_HERSHEY_PLAIN, 2.0, cv::Scalar(0, 127, 127));
				cv::rectangle(Mat, cv::Point(64 + 5, 64 + 5), cv::Point(96 + 5, 96 + 5), cv::Scalar(0, 255, 0));
				cv::circle(Mat, cv::Point(128, 128), 32, cv::Scalar(0, 0, 255));

				//cv::imshow("Result", Result);

				//!< cv::Mat -> TArray<FColor>
				Colors.Empty();
				Colors.Reserve(Width * Height);
				for (auto i = 0; i < Height; ++i)
				{
					for (auto j = 0; j < Width; ++j)
					{
						const auto Value = Result.data[i * Width + j];
						Colors.Add(FColor(Value, Value, Value));
					}
				}

				//!< Update UTexture2D
				ENQUEUE_RENDER_COMMAND(UpdateTexture2D)(
					[Tex = Texture2D, this](FRHICommandListImmediate& RHICmdList)
					{
						const auto TexWidth = Tex->GetSizeX();
						const auto TexHeight = Tex->GetSizeY();
						const auto Pitch = GPixelFormats[Tex->GetPixelFormat()].BlockBytes * TexWidth;
						RHIUpdateTexture2D(Tex->Resource->TextureRHI->GetTexture2D(), 0, FUpdateTextureRegion2D(0, 0, 0, 0, TexWidth, TexHeight), Pitch, reinterpret_cast<const uint8*>(&Colors[0]));
					});
			}
		}
	}
}


// Called every frame
void UOpenCVComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

