// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatCharacter.h"
#include "Avatar.h"

#include "Enemy.generated.h"

class AWeapon;
class USkeletalMesh;
class ATargetPoint;
/**
 * 
 */
UCLASS()
class UNREAL_ARAGON_RPG_API AEnemy : public ACombatCharacter
{
	GENERATED_BODY()

public:
	AEnemy();

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, Category = "Character Info")
	ATargetPoint* StartingPosition;

	FString GetEnemyName() const;

	bool IfTimeToSwap(int32 NumberOfTurns, int32 AttackerIndex) override;

	UPROPERTY(BlueprintReadOnly)
	AAvatar* Player;
private:
	UPROPERTY(EditAnywhere, Category = "Character Info")
	FString Name;

	UPROPERTY(EditAnywhere, Category = "Character Info")
	USkeletalMesh* SkeletalMesh;

	UPROPERTY(EditAnywhere, Category = "Character Info")
	TArray<AWeapon*> EnemyWeapons;

	int32 CurrentWeaponIndex = 0;
};
