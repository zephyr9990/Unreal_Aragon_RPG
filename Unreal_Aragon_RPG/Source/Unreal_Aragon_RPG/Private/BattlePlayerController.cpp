// Fill out your copyright notice in the Description page of Project Settings.


#include "BattlePlayerController.h"
#include "CombatCharacter.h"
#include "InventoryComponent.h"
#include "Weapon.h"

void ABattlePlayerController::BeginPlay()
{
	Super::BeginPlay();
	PrimaryAvatar = Cast<AAvatar>(GetPawn());
	if (GetControlledAvatar() == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No controlled combat character on %s"), *GetName());
		return;
	}
}

AAvatar* ABattlePlayerController::GetControlledAvatar()
{
	return PrimaryAvatar;
}
