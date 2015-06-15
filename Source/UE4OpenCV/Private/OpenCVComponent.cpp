// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4OpenCV.h"
#include "OpenCVComponent.h"

/**
@note UE4 の check() と被るので opencv2/core/utility.hpp の CommandLineParser::check() をコメントアウトした
@note Because UE4 has check(), I comment out opencv2/core/utility.hpp : CommandLineParser::check()
*/
#pragma warning(push)
#pragma warning(disable : 4946)
#include <opencv2/opencv.hpp>
#pragma  warning(pop)
#include <opencv2/core/ocl.hpp>


// Sets default values for this component's properties
UOpenCVComponent::UOpenCVComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenCVComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	if (cv::ocl::haveOpenCL())
	{
		cv::ocl::Context Context;
		if (Context.create(cv::ocl::Device::TYPE_GPU))
		{
			cv::ocl::Device(Context.device(0));

			//!< シンプルな OpenCL コード
			//!< Simple OpenCL Code
			const cv::String Code = "__kernel void main(__global uchar* dst, const int pitch, const int offset, const int rows, const int cols) {"
				"const int x = get_global_id(0);"
				"const int y = get_global_id(1);"
				"const int index = mad24(y, pitch, x + offset);"
				"dst[index] = ((x % 2) || (y % 2)) ? (((x % 256) >> 1) + ((y % 256) >> 1)) : 0;"
				"}";
			const cv::ocl::ProgramSource ProgramSource(Code);

			//!< OpenCL の ビルド
			//!< Build OpenCL
			const cv::String Buildopt = "";
			cv::String Errmsg;
			const auto Program = Context.getProg(ProgramSource, Buildopt, Errmsg);

			//!< 結果格納用
			//!< Result destination
			const auto Mat = cv::UMat(256, 256, CV_8U, cv::ACCESS_WRITE, cv::USAGE_ALLOCATE_DEVICE_MEMORY);

			//!< OpenCL 関数名と引数
			//!< OpenCL function name and arguments
			cv::ocl::Kernel Kernel("main", Program);
			Kernel.args(cv::ocl::KernelArg::ReadWrite(Mat));

			//!< OpenCL の実行
			//!< Execute OpenCL
			size_t Threads[] = { 256, 256, 1 };
			if (Kernel.run(ARRAY_COUNT(Threads), Threads, nullptr, true))
			{
				const auto Result = Mat.getMat(cv::ACCESS_READ);

				//!< OpenCV の操作を加えてみる
				//!< Add some OpenCV operations
				cv::putText(Mat, cv::String("Hello OpenCV"), cv::Point(0, 255), CV_FONT_HERSHEY_PLAIN, 2.0, cv::Scalar(255, 0, 0));
				cv::rectangle(Mat, cv::Point(64, 64), cv::Point(96, 96), cv::Scalar(0, 255, 0));
				cv::circle(Mat, cv::Point(128, 128), 32, cv::Scalar(0, 0, 255));

				//cv::imshow("Result", Result);

				//!< cv::Mat -> TArray<FColor>
				Colors.Empty();
				Colors.Reserve(256 * 256);
				for (auto i = 0; i < 256; ++i)
				{
					for (auto j = 0; j < 256; ++j)
					{
						const auto Value = Result.data[i * 256 + j];
						Colors.Add(FColor(Value, Value, Value));
					}
				}

				if (nullptr == Texture2D)
				{
					Texture2D = UTexture2D::CreateTransient(256, 256);
					Texture2D->UpdateResource();
				}

				//!< UTexture2Dを更新
				//!< Update UTexture2D
				ENQUEUE_UNIQUE_RENDER_COMMAND_TWOPARAMETER(UpdateTexture2D,
					UOpenCVComponent*, This, this,
					UTexture2D*, Tex, Texture2D,
					{
						const auto Width = Tex->GetSizeX();
						const auto Height = Tex->GetSizeY();
						const auto Pitch = GPixelFormats[Tex->GetPixelFormat()].BlockBytes * Width;
						RHIUpdateTexture2D(Tex->Resource->TextureRHI->GetTexture2D(), 0, FUpdateTextureRegion2D(0, 0, 0, 0, Width, Height), Pitch, reinterpret_cast<const uint8*>(&This->Colors[0]));
					}
				);
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

