// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Avatar.generated.h"

UCLASS()
class UNREAL_ARAGON_RPG_API AAvatar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAvatar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Move player forward
	void MoveForward(float Amount);

	// Move player right
	void MoveRight(float Amount);

	// Controls player yaw 
	void RotateYaw(float Amount);

	// Controls player pitch
	void RotatePitch(float Amount);

private:
	float LookSensitivity = 200.0f;
};
