// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "OpenCVGameMode.generated.h"

/**
 * 
 */
UCLASS()
class UE4OPENCV_API AOpenCVGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	AOpenCVGameMode(const FObjectInitializer& ObjectInitializer);
};
