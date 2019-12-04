// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatCharacter.h"
#include "InventoryComponent.h"
#include "Enemy.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BattleAIController.h"

// Sets default values
ACombatCharacter::ACombatCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WeaponInventory = CreateDefaultSubobject<UInventoryComponent>(FName("InventoryComponent"));
	WeaponInventory->SetInventoryOwner(this);
	CurrentHitPoints = MaxHitPoints;
}

// Called when the game starts or when spawned
void ACombatCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACombatCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACombatCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

FString ACombatCharacter::GetName() const
{
	return Name;
}

float ACombatCharacter::GetPercentHP() const
{
	return static_cast<float>(CurrentHitPoints) / static_cast<float>(MaxHitPoints);
}

FLinearColor ACombatCharacter::GetHPColor() const
{
	return FLinearColor(1-GetPercentHP(), GetPercentHP(), 0, 1);
}

UCharacterWeapon* ACombatCharacter::GetEquippedWeapon() const
{
	if (!EquippedWeapon) 
	{
		return nullptr;
	}

	return EquippedWeapon;
}

void ACombatCharacter::EquipWeapon(AWeapon* Weapon)
{
	if (!EquippedWeapon)
	{
		return;
	}

	EquippedWeapon->SetWeapon(Weapon);
}

void ACombatCharacter::UnsheatheWeapon()
{
	EquippedWeapon->UnsheatheWeapon(this);
}

bool ACombatCharacter::IsDead()
{
	return bIsDead;
}

UInventoryComponent* ACombatCharacter::GetInventory() const
{
	return WeaponInventory;
}

AWeapon* ACombatCharacter::GetWeaponFromInventory(int WeaponIndex)
{
	return WeaponInventory->GetWeapon(WeaponIndex);
}

void ACombatCharacter::SetTargetToAttack(ACombatCharacter* Target)
{
	Cast<ABattleAIController>(UAIBlueprintHelperLibrary::GetAIController(this))->SetTarget(Target);
}

void ACombatCharacter::Attack(ACombatCharacter* Target)
{
	Cast<ABattleAIController>(UAIBlueprintHelperLibrary::GetAIController(Target))->SetToReactToDamage();
	EquippedWeapon->Attack(Target);
}

bool ACombatCharacter::IfTimeToSwap(int32 NumberOfTurns, int32 AttackerIndex)
{
	return true;
}

void ACombatCharacter::ReceiveDamage(int32 Amount)
{
	if (CurrentHitPoints - Amount <= 0)
	{
		CurrentHitPoints = 0;
		Die();
	}
	else
	{
		CurrentHitPoints -= Amount;
	}
	UE_LOG(LogTemp, Warning, TEXT("Damage received. Remaining health: %i"), CurrentHitPoints);
}

void ACombatCharacter::Die()
{
	bIsDead = true;
}

int32 ACombatCharacter::GetHitPoints() const
{
	return CurrentHitPoints;
}

