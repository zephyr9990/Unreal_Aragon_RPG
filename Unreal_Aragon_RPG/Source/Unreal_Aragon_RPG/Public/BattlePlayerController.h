// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Avatar.h"

#include "BattlePlayerController.generated.h"

// Forward Declaration
class ACombatCharacter;

/**
 * 
 */
UCLASS()
class UNREAL_ARAGON_RPG_API ABattlePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	AAvatar* GetControlledAvatar();

private:
	AAvatar* PrimaryAvatar;
};
