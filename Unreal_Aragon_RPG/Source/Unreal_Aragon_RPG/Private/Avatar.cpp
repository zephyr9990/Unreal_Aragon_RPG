// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Actor.h"
#include "Avatar.h"

// Sets default values
AAvatar::AAvatar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAvatar::BeginPlay()
{
	Super::BeginPlay();
	
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

void AAvatar::MoveForward(float amount)
{
	// Don't enter the body of this function if Controller is not set up yet,
	// or if the amount to move is equal to 0.
	if (Controller && amount)
	{
		FVector forward = GetActorForwardVector();
		// we call AddMovementInput to actually move the
		// player by "amount" in the "forward" direction
		AddMovementInput(forward, amount);
	}
}

void AAvatar::MoveRight(float amount)
{
	// Don't enter the body of this function if Controller is not set up yet,
	// or if the amount to move is equal to 0.
	if (Controller && amount)
	{
		FVector right = GetActorRightVector();
		// we call AddMovementInput to actually move the
		// player by "amount" in the "forward" direction
		AddMovementInput(right, amount);
	}
}

void AAvatar::RotateYaw(float amount)
{
	AddControllerYawInput(LookSensitivity * amount * GetWorld()->GetDeltaSeconds());
}

void AAvatar::RotatePitch(float amount)
{
	AddControllerPitchInput(LookSensitivity * amount * GetWorld()->GetDeltaSeconds());
}

