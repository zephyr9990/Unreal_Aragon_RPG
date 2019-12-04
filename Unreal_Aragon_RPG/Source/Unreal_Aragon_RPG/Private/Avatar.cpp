// Fill out your copyright notice in the Description page of Project Settings.

#include "Avatar.h"

#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"
#include "BattleManager.h"
#include "InventoryComponent.h"


// Sets default values
AAvatar::AAvatar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AAvatar::BeginPlay()
{
	Super::BeginPlay();
	CurrentHitPoints = MaxHitPoints;

	EquippedWeapon = FindComponentByClass<UCharacterWeapon>();
	if (!EquippedWeapon)
	{
		UE_LOG(LogTemp, Warning, TEXT("Missing weapon component on %s."), *Controller->GetPawn()->GetName());
	}
}

// Called every frame
void AAvatar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AAvatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Forward", this, &AAvatar::MoveForward);
	PlayerInputComponent->BindAxis("Strafe", this, &AAvatar::MoveRight);
	PlayerInputComponent->BindAxis("Pitch", this, &AAvatar::RotatePitch);
	PlayerInputComponent->BindAxis("Yaw", this, &AAvatar::RotateYaw);
}

void AAvatar::MoveForward(float Amount)
{
	// Don't enter the body of this function if Controller is not set up yet,
	// or if the amount to move is equal to 0.
	if (Controller && Amount)
	{
		float ControllerRotationYaw = Controller->GetControlRotation().Yaw;
		FRotator NewRotation = FRotator(0.0f, ControllerRotationYaw, 0.0f);
		FVector Forward = NewRotation.Quaternion().GetForwardVector();
		AddMovementInput(Forward, Amount);
	}
}

void AAvatar::MoveRight(float Amount)
{
	// Don't enter the body of this function if Controller is not set up yet,
	// or if the amount to move is equal to 0.
	if (Controller && Amount)
	{
		float ControllerRotationYaw = Controller->GetControlRotation().Yaw;
		FRotator NewRotation = FRotator(0.0f, ControllerRotationYaw, 0.0f);
		FVector Right = NewRotation.Quaternion().GetRightVector();
		AddMovementInput(Right, Amount);
	}
}

void AAvatar::RotateYaw(float Amount)
{
	AddControllerYawInput(LookSensitivity * Amount * GetWorld()->GetDeltaSeconds());
}

void AAvatar::RotatePitch(float Amount)
{
	AddControllerPitchInput(LookSensitivity * Amount * GetWorld()->GetDeltaSeconds());
}

bool AAvatar::IfTimeToSwap(int32 NumberOfTurns, int32 AttackerIndex)
{
	if (NumberOfTurns >= 3)
	{
		UE_LOG(LogTemp, Warning, TEXT("Swapping Weapons"));
		if (CurrentWeaponIndex < GetInventory()->GetNumberOfWeapons() - 1) 
		{
			CurrentWeaponIndex += 1;
			EquipWeapon(GetWeaponFromInventory(CurrentWeaponIndex));
		}
		else
		{
			CurrentWeaponIndex = 0;
			EquipWeapon(GetWeaponFromInventory(CurrentWeaponIndex));
		}
		ABattleManager::TurnNumbers[AttackerIndex] = 0;
		return true;
	}
	return false;
}
