// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"
#include "Avatar.h"
#include "Math/Vector2D.h"
#include "Engine/Canvas.h"
#include "Kismet/GameplayStatics.h"

#define OUT

void AMyHUD::DrawHUD()
{
	Super::DrawHUD();

	for (int i = messages.Num() - 1; i >= 0; i--)
	{
		DrawMessages(i);
	}

	DrawHealthBar();
}

void AMyHUD::DrawMessages(int index)
{
	// draw the backround box the right size for the message.
	float outputWidth, outputHeight;
	float pad = 10.0f;
	GetTextSize(messages[index].message, OUT outputWidth, OUT outputHeight,
		HUDFont, 1.f);

	float messageH = outputHeight + 2.0f * pad;
	float x = 0.0f;
	float y = index * messageH;

	// black backing
	DrawRect(FLinearColor::Black, x, y, Canvas->SizeX, messageH);

	// draw face
	DrawTexture(messages[index].face, x, y, messageH, messageH, 0, 0, 1, 1);

	// draw our message using the HUDfont
	DrawText(messages[index].message, messages[index].color, x + pad * 4,
		y + pad, HUDFont);

	// reduce lifetime by the time that passed since last frame.
	messages[index].time -= GetWorld()->GetDeltaSeconds();

	// if the message's time is up, remove it.
	if (messages[index].time < 0)
	{
		messages.RemoveAt(index);
	}
}

void AMyHUD::AddMessage(Message msg)
{
	messages.Add(msg);
}

void AMyHUD::DrawHealthBar()
{
	AAvatar* avatar = Cast<AAvatar>(
		UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	float barWidth = 200, barHeight = 50, barPad = 12, barMargin = 50;
	float HPPercent = 1;// TODO add variable for HP and maxHP in Avatar.h;
	
	// Background
	DrawRect(
		FLinearColor(0, 0, 0, 1),
		Canvas->SizeX - barWidth - barPad - barMargin,
		Canvas->SizeY - barHeight - barPad - barMargin,
		barWidth + 2 * barPad,
		barHeight + 2 * barPad
	);

	// Health
	DrawRect(
		FLinearColor(1 - HPPercent, HPPercent, 0, 1),
		Canvas->SizeX - barWidth - barMargin,
		Canvas->SizeY - barHeight - barMargin,
		barWidth * HPPercent,
		barHeight
	);
}
