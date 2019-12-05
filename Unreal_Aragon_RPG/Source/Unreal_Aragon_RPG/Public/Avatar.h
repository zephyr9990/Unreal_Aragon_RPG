// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Avatar.generated.h"


// Forward Declaration
class APickupItem;
class AMyHUD;

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

	// Toggle the inventory display
	void ToggleInventory();

	// member function for letting the avatar have an item
	void Pickup(APickupItem* PickupItem);
	void Pickup(FString ItemName, int32 ItemQuantity, UTexture2D* ItemIcon);

	// Passes click point information to the HUD when mouse is clicked.
	void MouseClicked();
private:
	float LookSensitivity = 200.0f;

	// A map for the player's backpack
	TMap<FString, int> BackPack;

	// The icons for the items in the backpack, lookup by string.
	TMap<FString, UTexture2D*> Icons;

	// A flag alerting us the UI is showing
	bool bInventoryShowing;

	// Reference to the player controller.
	APlayerController* PController;

	// Reference to the player's HUD
	AMyHUD* HUD;

};
