// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

// Forward Declaration
class UTexture2D;

struct Message
{
	UTexture2D* face;
	FString message;
	float time;	
	FColor color;
	
	Message()
	{
		// Set the default time.
		time = 5.0f;
		color = FColor::White;
		face = nullptr;
	}

	Message(UTexture2D* iFace, FString iMessage, float iTime, FColor iColor)
	{
		face = iFace;
		message = iMessage;
		time = iTime;
		color = iColor;
	}
};

struct ItemIcon
{

	FString Name;

	UTexture2D* Texture;

	ItemIcon()
	{
		Name = "UNKNOWN ICON";
		Texture = 0;
	}

	ItemIcon(FString& Name, UTexture2D* Texture)
	{
		this->Name = Name;
		this->Texture = Texture;
	}
};

struct ItemWidget
{
	ItemIcon Icon;
	FVector2D Position, Size;
	
	ItemWidget(ItemIcon ItemIcon)
	{
		this->Icon = ItemIcon;
	}

	float Left() { return Position.X; }
	float Right() { return Position.X + Size.X; }
	float Top() { return Position.Y; }
	float Bottom() { return Position.Y + Size.Y; }

	bool Hit(FVector2D ClickPoint)
	{
		/* +---+ Top (0)
		   |   |
		   +---+ Bottom (2) (Bottom > Top)
		   L   R */

		// See if click point is within the box
		return ClickPoint.X > Left()
			&& ClickPoint.X < Right() // Horizontal bounds of box
			&& ClickPoint.Y > Top()
			&& ClickPoint.Y < Bottom(); // Vertical Bounds of box
	}
};

/**
 * 
 */
UCLASS()
class UNREAL_ARAGON_RPG_API AMyHUD : public AHUD
{
	GENERATED_BODY()

public:
	// The font used to render the text in the HUD.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUDFont)
	UFont* HUDFont;

	void BeginPlay() override;

	// Draws the HUD
	void DrawHUD() override;

	void DrawMessages(int Index);

	// Adds a message to the display
	void AddMessage(Message Msg);

	void DrawHealthBar();

	void DrawWidgets();

	void AddWidget(ItemWidget ItemWidget);

	void ClearWidgets();
	
	// Searches to see if a widget is clicked.
	void MouseClicked();

	// Checks to see if a widget should be dragged.
	void MouseMoved();
private:
	TArray<ItemWidget> Widgets;
	TArray<Message> Messages;
	FVector2D Dimensions;
	ItemWidget* HeldWidget; // holds the last touched ItemWidget in memory 
	APlayerController* PController;
};
