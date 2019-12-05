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
	// The name of the item
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Name; 

	// The quantity to give to players
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Quantity; 

	// The icon of the item
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Icon; 
};	
