// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

class USphereComponent;
class USkeletalMesh;

/**
 * A weapon that can be picked up.
 */
UCLASS()
class UNREAL_ARAGON_RPG_API AWeapon : public AActor
{
	GENERATED_BODY()

public:
	AWeapon();

	FString GetWeaponName();

	int32 GetAttackValue();

	USkeletalMesh* GetWeaponMesh();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision)
	USphereComponent* ProxSphere;

	UFUNCTION(BlueprintNativeEvent, Category = "Collision")
	void Prox(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(EditAnywhere)
	FString Name;
	
	UPROPERTY(EditAnywhere)
	int32 AttackValue;

	UPROPERTY(EditAnywhere)
	USkeletalMesh* WeaponMesh;
};
