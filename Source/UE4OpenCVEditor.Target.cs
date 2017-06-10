// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class UE4OpenCVEditorTarget : TargetRules
{
	public UE4OpenCVEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.Add("UE4OpenCV");
	}
}
