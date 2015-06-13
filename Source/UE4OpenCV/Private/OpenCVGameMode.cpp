// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4OpenCV.h"
#include "OpenCVGameMode.h"

#include "OpenCVHUD.h"

AOpenCVGameMode::AOpenCVGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	HUDClass = AOpenCVHUD::StaticClass();
}