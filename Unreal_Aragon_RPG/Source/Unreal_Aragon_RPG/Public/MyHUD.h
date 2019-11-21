// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Engine/Texture2D.h"
#include "MyHUD.generated.h"

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

/**
 * 
 */
UCLASS()
class UNREAL_ARAGON_RPG_API AMyHUD : public AHUD
{
	GENERATED_BODY()

public:
	// The fone used to render the text in the HUD.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUDFont)
	UFont* HUDFont;

	TArray<Message> messages;

	// Draws the HUD
	void DrawHUD() override;

	void DrawMessages(int c);

	// Adds a message to the display
	void AddMessage(Message msg);

	void DrawHealthBar();
};
