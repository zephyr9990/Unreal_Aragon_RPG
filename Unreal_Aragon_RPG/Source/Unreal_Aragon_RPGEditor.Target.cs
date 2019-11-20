// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class Unreal_Aragon_RPGEditorTarget : TargetRules
{
	public Unreal_Aragon_RPGEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "Unreal_Aragon_RPG" } );
	}
}
