// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CombatCharacter.generated.h"

// Forward Declaration
class AWeapon;
class UCharacterWeapon;
class UInventoryComponent;

UCLASS()
class UNREAL_ARAGON_RPG_API ACombatCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACombatCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FString Name;

	UPROPERTY(EditAnywhere, Category = "Character Info")
	int32 MaxHitPoints = 100;

	int32 CurrentHitPoints;

	UCharacterWeapon* EquippedWeapon = nullptr;

	UInventoryComponent* WeaponInventory = nullptr;

	bool bIsDead = false;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Character Info")
	FString GetName() const;

	UFUNCTION(BlueprintCallable, Category = "Character Info")
	int32 GetHitPoints() const;

	UFUNCTION(BlueprintCallable, Category = "Character Info")
	float GetPercentHP() const;

	UFUNCTION(BlueprintCallable, Category = "Character Info")
	FLinearColor GetHPColor() const;

	UCharacterWeapon* GetEquippedWeapon() const;

	void EquipWeapon(AWeapon* Weapon);

	UFUNCTION(BlueprintCallable, Category = "Battle")
	void UnsheatheWeapon();

	UFUNCTION(BlueprintCallable, Category = "Battle")
	bool IsDead();

	UInventoryComponent* GetInventory() const;

	AWeapon* GetWeaponFromInventory(int WeaponIndex);

	void SetTargetToAttack(ACombatCharacter* Target);

	UFUNCTION(BlueprintCallable, Category = "Battle")
	void Attack(ACombatCharacter* Target);

	void ReceiveDamage(int32 Amount);

	virtual bool IfTimeToSwap(int32 NumberOfTurns, int32 AttackerIndex);

	void Die();
};
