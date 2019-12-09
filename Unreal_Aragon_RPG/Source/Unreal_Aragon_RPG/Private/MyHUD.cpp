// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"
#include "Avatar.h"
#include "Math/Vector2D.h"
#include "Engine/Canvas.h"
#include "Kismet/GameplayStatics.h"

#define OUT

void AMyHUD::BeginPlay()
{
	Super::BeginPlay();

	PController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
}

void AMyHUD::DrawHUD()
{
	Super::DrawHUD();

	for (int i = Messages.Num() - 1; i >= 0; i--)
	{
		DrawMessages(i);
	}

	Dimensions.X = Canvas->SizeX;
	Dimensions.Y = Canvas->SizeY;
	DrawHealthBar();
	DrawWidgets();
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
	AAvatar* Avatar = Cast<AAvatar>(
		UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	float BarWidth = 200, BarHeight = 50, BarPad = 12, BarMargin = 50;
	float HPPercent = Avatar->Health / Avatar->MaxHealth;
	
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

void AMyHUD::DrawWidgets()
{
	for (int32 Index = 0; Index < Widgets.Num(); Index++)
	{
		DrawTexture(
			Widgets[Index].Icon.Texture,
			Widgets[Index].Position.X,
			Widgets[Index].Position.Y,
			Widgets[Index].Size.X,
			Widgets[Index].Size.Y,
			0, 0, 1, 1
		);

		DrawText(
			Widgets[Index].Icon.Name,
			FLinearColor::Black,
			Widgets[Index].Position.X,
			Widgets[Index].Position.Y,
			HUDFont
		);
	}
}

void AMyHUD::AddWidget(ItemWidget ItemWidget)
{
	// Find the position of the widget based on the grid.
	// draw the icons.
	FVector2D Start(200, 200), Pad(12, 12);
	ItemWidget.Size = FVector2D(100, 100);
	ItemWidget.Position = Start;

	// Compute the position here.
	for (int Index = 0; Index < Widgets.Num(); Index++)
	{
		// Move the position to the right a bit.
		ItemWidget.Position.X += ItemWidget.Size.X + Pad.X;
		// If there is no more room to the right then jump to the next line
		if (ItemWidget.Position.X + ItemWidget.Size.X > Dimensions.X)
		{
			ItemWidget.Position.X = Start.X;
			ItemWidget.Position.Y = Start.Y + Pad.Y;
		}
	}
	Widgets.Add(ItemWidget);
}

void AMyHUD::ClearWidgets()
{
	Widgets.Empty();
}

void AMyHUD::MouseClicked()
{
	FVector2D Mouse;
	PController->GetMousePosition(Mouse.X, Mouse.Y);
	HeldWidget = nullptr; // Clear handle on last held widget.

	// go and see if mouse xy click position hits any widgets.
	for (int Index = 0; Index < Widgets.Num(); Index++)
	{
		if (Widgets[Index].Hit(Mouse))
		{
			HeldWidget = &Widgets[Index]; // save widget
			return; // Stop checking
		}
	}
}

void AMyHUD::MouseMoved()
{
	static FVector2D LastMouse;
	FVector2D ThisMouse, DeltaMouse;
	PController->GetMousePosition(ThisMouse.X, ThisMouse.Y);
	DeltaMouse = ThisMouse - LastMouse;

	// See if the left mouse has been held down for more than 0 seconds.
	// If it has been held down, then the drag can commence
	float Time = PController->GetInputKeyTimeDown(EKeys::LeftMouseButton);
	
	if (Time > 0.0f && HeldWidget)
	{
		// the mouse is being held down
		// move the widget by displacement amount
		HeldWidget->Position.X += DeltaMouse.X;
		HeldWidget->Position.Y += DeltaMouse.Y; // y inverted
	}
	LastMouse = ThisMouse;
}
