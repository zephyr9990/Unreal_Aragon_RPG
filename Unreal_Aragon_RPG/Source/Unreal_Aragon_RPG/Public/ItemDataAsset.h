// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemDataAsset.generated.h"

// Forward declaration
class UTexture2D;
class UStaticMesh;

/**
 * 
 */
UCLASS()
class UNREAL_ARAGON_RPG_API UItemDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Name; // The name of the item

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Quantity; // The quantity to give to players

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Icon; // The icon of the item
};	
