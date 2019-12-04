// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "InventoryComponent.h"
#include "BattleManager.h"
#include "GameFramework/PlayerController.h"


AEnemy::AEnemy()
{
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	CurrentHitPoints = MaxHitPoints;
	EquippedWeapon = FindComponentByClass<UCharacterWeapon>();
	if (!EquippedWeapon)
	{
		UE_LOG(LogTemp, Warning, TEXT("No character weapon component on %s"), *Name);
	}

	for (AWeapon* EnemyWeapon : EnemyWeapons)
	{
		WeaponInventory->AddWeapon(EnemyWeapon);
	}

	Player = Cast<AAvatar>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

FString AEnemy::GetEnemyName() const
{
	return Name;
}

bool AEnemy::IfTimeToSwap(int32 NumberOfTurns, int32 AttackerIndex)
{
	if (NumberOfTurns >= 5)
	{
		UE_LOG(LogTemp, Warning, TEXT("Swapping Weapons"));
		if (CurrentWeaponIndex == 0)
		{
			CurrentWeaponIndex = 1;
			EquipWeapon(GetWeaponFromInventory(CurrentWeaponIndex));
		}
		else
		{
			CurrentWeaponIndex = 0; 
			EquipWeapon(GetWeaponFromInventory(CurrentWeaponIndex));
		}
		ABattleManager::TurnNumbers[AttackerIndex] = 0;
	}
	return false;
}

