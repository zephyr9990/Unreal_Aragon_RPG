// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"
#include "Avatar.h"
#include "Math/Vector2D.h"
#include "Engine/Canvas.h"
#include "Kismet/GameplayStatics.h"
#include "BattlePlayerController.h"

#define OUT

void AMyHUD::DrawHUD()
{
	Super::DrawHUD();

	for (int i = Messages.Num() - 1; i >= 0; i--)
	{
		DrawMessages(i);
	}

	DrawHealthBar();
}

void AMyHUD::DrawMessages(int Index)
{
	// draw the backround box the right size for the message.
	float OutputWidth, OutputHeight;
	float pad = 10.0f;
	GetTextSize(Messages[Index].message, OUT OutputWidth, OUT OutputHeight,
		HUDFont, 1.f);

	float MessageH = OutputHeight + 2.0f * pad;
	float x = 0.0f;
	float y = Index * MessageH;

	// black backing
	DrawRect(FLinearColor::Black, x, y, Canvas->SizeX, MessageH);

	// draw face
	DrawTexture(Messages[Index].face, x, y, MessageH, MessageH, 0, 0, 1, 1);

	// draw our message using the HUDfont
	DrawText(Messages[Index].message, Messages[Index].color, x + pad * 4,
		y + pad, HUDFont);

	// reduce lifetime by the time that passed since last frame.
	Messages[Index].time -= GetWorld()->GetDeltaSeconds();

	// if the message's time is up, remove it.
	if (Messages[Index].time < 0)
	{
		Messages.RemoveAt(Index);
	}
}

void AMyHUD::AddMessage(Message Msg)
{
	Messages.Add(Msg);
}

void AMyHUD::DrawHealthBar()
{
	ABattlePlayerController* Player = Cast<ABattlePlayerController>(
		UGameplayStatics::GetPlayerController(GetWorld(), 0));
	AAvatar* Avatar = Player->GetControlledAvatar();
	float BarWidth = 200, BarHeight = 50, BarPad = 12, BarMargin = 50;
	float HPPercent = Avatar->GetPercentHP();

	// Background
	DrawRect(
		FLinearColor(0, 0, 0, 1),
		Canvas->SizeX - BarWidth - BarPad - BarMargin,
		Canvas->SizeY - BarHeight - BarPad - BarMargin,
		BarWidth + 2 * BarPad,
		BarHeight + 2 * BarPad
	);

	// Health
	DrawRect(
		FLinearColor(1 - HPPercent, HPPercent, 0, 1),
		Canvas->SizeX - BarWidth - BarMargin,
		Canvas->SizeY - BarHeight - BarMargin,
		BarWidth * HPPercent,
		BarHeight
	);
}
