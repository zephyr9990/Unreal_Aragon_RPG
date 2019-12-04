// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "CharacterWeapon.generated.h"

// Forward Declaration
class ACombatCharacter;
class USkeletalMesh;
class AWeapon;

/**
 *
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), hidecategories = (StaticMesh))
class UNREAL_ARAGON_RPG_API UCharacterWeapon : public USkeletalMeshComponent
{
	GENERATED_BODY()

public:
	UCharacterWeapon();

	void SetWeapon(AWeapon* Weapon);

	void UnsheatheWeapon(ACombatCharacter* OwnerOfWeapon);

	void Attack(ACombatCharacter* Target);

	FString GetWeaponName() const;

private:
	FString Name;

	int32 AttackValue;

	USkeletalMesh* WeaponMesh;
};
