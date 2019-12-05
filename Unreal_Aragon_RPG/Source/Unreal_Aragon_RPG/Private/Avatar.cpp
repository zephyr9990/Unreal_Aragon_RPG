// Fill out your copyright notice in the Description page of Project Settings.

#include "Avatar.h"

#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "PickupItem.h"
#include "MyHUD.h"

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
	PController = GetWorld()->GetFirstPlayerController();
	HUD = Cast<AMyHUD>(PController->GetHUD());

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

	PlayerInputComponent->BindAction("Inventory", IE_Pressed, this, &AAvatar::ToggleInventory);
	PlayerInputComponent->BindAction("MouseClickedLMB", IE_Pressed, this, &AAvatar::MouseClicked);
}

void AAvatar::MoveForward(float Amount)
{
	if (bInventoryShowing)
	{
		return; // when inventory is showing, player cannot move.
	}

	// Don't enter the body of this function if Controller is not set up yet,
	// or if the amount to move is equal to 0.
	if (Controller && Amount)
	{
		FVector Forward = GetActorForwardVector();
		// we call AddMovementInput to actually move the
		// player by "amount" in the "forward" direction
		AddMovementInput(Forward, Amount);
		
	}
}

void AAvatar::MoveRight(float Amount)
{
	if (bInventoryShowing)
	{
		return; // when inventory is showing, player cannot move.
	}

	// Don't enter the body of this function if Controller is not set up yet,
	// or if the amount to move is equal to 0.
	if (Controller && Amount)
	{
		FVector Right = GetActorRightVector();
		// we call AddMovementInput to actually move the
		// player by "amount" in the "right" direction
		AddMovementInput(Right, Amount);
		
	}
}

void AAvatar::RotateYaw(float Amount)
{
	if (bInventoryShowing)
	{
		// when inventory is showing, pass the input to the HUD
		HUD->MouseMoved();
		return;
	}

	AddControllerYawInput(LookSensitivity * Amount * GetWorld()->GetDeltaSeconds());
}

void AAvatar::RotatePitch(float Amount)
{
	if (bInventoryShowing)
	{
		// when inventory is showing, pass the input to the HUD
		HUD->MouseMoved();
		return;
	}

	AddControllerPitchInput(LookSensitivity * Amount * GetWorld()->GetDeltaSeconds());
}

void AAvatar::ToggleInventory()
{
	// If inventory is displayed, undisplay it.
	if (bInventoryShowing)
	{
		HUD->ClearWidgets();
		bInventoryShowing = false;
		PController->bShowMouseCursor = false;
		return;
	}

	// Otherwise display the player's inventory.
	bInventoryShowing = true;
	PController->bShowMouseCursor = true;
	for (TMap<FString, int32>::TIterator Iterator = BackPack.CreateIterator(); Iterator; ++Iterator)
	{
		// Combine string name of the item, with quantity (e.g. Cow x 5)
		FString ItemXQuanity = Iterator->Key + FString::Printf(TEXT(" x %d"), Iterator->Value);
		UTexture2D* Texture;
		if (Icons.Find(Iterator->Key))
		{
			Texture = Icons[Iterator->Key];
			HUD->AddWidget(ItemWidget(ItemIcon(ItemXQuanity, Texture)));
		}
	}
}

void AAvatar::Pickup(APickupItem* Item)
{
	if (BackPack.Find(Item->Name))
	{
		// the item was already in the pack... increase quanity of it
		BackPack[Item->Name] += Item->Quantity;
	}
	else
	{
		// The item was not in the pack... add it now.
		BackPack.Add(Item->Name, Item->Quantity);
		Icons.Add(Item->Name, Item->Icon);
	}
}

void AAvatar::MouseClicked()
{
	HUD->MouseClicked();
}

