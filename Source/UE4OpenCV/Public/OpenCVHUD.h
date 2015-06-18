// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "OpenCVHUD.generated.h"

/**
 * 
 */
UCLASS()
class UE4OPENCV_API AOpenCVHUD : public AHUD
{
	GENERATED_BODY()

public:
	AOpenCVHUD(const FObjectInitializer& ObjectInitializer);

	virtual void DrawHUD() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = OpenCV)
	class UOpenCVComponent* OpenCVComp;
};
