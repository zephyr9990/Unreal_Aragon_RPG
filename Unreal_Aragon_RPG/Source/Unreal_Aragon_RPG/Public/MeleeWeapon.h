// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MeleeWeapon.generated.h"

class AMonster;
class UBoxComponent;

UCLASS()
class UNREAL_ARAGON_RPG_API AMeleeWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMeleeWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// The amount of damage this weapon inflicts.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Melee Weapon")
	float AttackDamage;

	// A list of things the melee weapon already hit this swing
	// Ensures each thing weapon passes thru only gets hit once
	TArray<AActor*> ThingsHit;

	// Prevents damage from occurring in frames where the sword is not swining
	bool Swinging;

	// "Stop hitting yourself" - used to check if the actor
	// holding the weapon is hitting themself.
	AMonster* WeaponHolder;

	// Bounding box that determines when melee weapon hit
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Melee Weapon")
	UBoxComponent* ProxBox;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Melee Weapon")
	UStaticMeshComponent* Mesh;

	UFUNCTION(BlueprintNativeEvent, Category = "Collision")
	void Prox(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void Swing();

	void Rest();
};
