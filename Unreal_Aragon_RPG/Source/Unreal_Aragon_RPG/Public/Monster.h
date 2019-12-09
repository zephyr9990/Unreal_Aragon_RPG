// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Monster.generated.h"

// Forward declaration
class USphereComponent;

UCLASS()
class UNREAL_ARAGON_RPG_API AMonster : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonster();

	virtual void PostInitializeComponents() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	inline bool IsInSightRange(float DistanceToPlayer);

	inline bool IsInAttackRange(float DistanceToPlayer);

	UFUNCTION(BlueprintCallable, Category = "Collision")
	bool IsInAttackRangeOfPlayer();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// How fast the monster moves.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster Properties")
	float Speed;
	
	// The health of the monster.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster Properties")
	float HitPoints;

	// The number of experience points this monster grants.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster Properties")
	int32 ExperiencePoints;

	// Blueprint of the type of item dropped by the monster
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster Properties")
	UClass* BPLoot;

	// The amount of damage attacks do
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster Properties")
	float BaseAttackDamage;

	// Amount of time the monster needs to rest in seconds between attacking
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster Properties")
	float AttackTimeout;

	// Time since monster's last strike, readable in blueprints
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Monster Properties")
	float TimeSinceLastStrike;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster Properties")
	bool CanAttack = false;

	// The MeleeWeapon the monster uses
	// If this is not set he uses an unarmed melee attack
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster Properties")
	UClass* MeleeWeapon_BP = nullptr;

	// The MeleeWeapon instance (set if the character is using a melee weapon
	AActor* MeleeWeapon = nullptr;

	// The blueprint of the bullet class he monster uses
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster Properties")
	UClass* Bullet_BP = nullptr;

	// Thrust behind bullets (Speed).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster Properties")
	float BulletLaunchImpulse;

	// Range for his sight
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Collision")
	USphereComponent* SightSphere;

	// Range for his attack. Visualizes as a sphere in editor.
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Collision")
	USphereComponent* AttackRangeSphere;

	UFUNCTION(BlueprintCallable, Category = "Collision")
	void SwordSwung();

	UFUNCTION(BlueprintCallable, Category = "Collision")
	void Attack(AActor* Target);
};
