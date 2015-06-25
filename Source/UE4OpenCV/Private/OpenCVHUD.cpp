// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4OpenCV.h"
#include "OpenCVHUD.h"

#include "OpenCVComponent.h"

AOpenCVHUD::AOpenCVHUD(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	OpenCVComp = ObjectInitializer.CreateDefaultSubobject<UOpenCVComponent>(this, TEXT("OpenCVComp"));
}

void AOpenCVHUD::DrawHUD()
{
	Super::DrawHUD();

	if (nullptr != Canvas)
	{
		const FVector2D ScreenSize(Canvas->SizeX, Canvas->SizeY);
		if (nullptr != OpenCVComp)
		{
			const auto Texture = OpenCVComp->Texture2D;
			if (nullptr != Texture)
			{
#if 0
				const FVector2D TextureSize(Texture->GetSurfaceWidth(), Texture->GetSurfaceHeight());
				FCanvasTileItem Item((ScreenSize - TextureSize) * 0.5f, Texture->Resource, FLinearColor::White);
#else
				FCanvasTileItem Item(FVector2D::ZeroVector, Texture->Resource, ScreenSize, FLinearColor::White);
#endif
				Item.BlendMode = SE_BLEND_Opaque;
				Canvas->DrawItem(Item);
			}
		}
	}
}