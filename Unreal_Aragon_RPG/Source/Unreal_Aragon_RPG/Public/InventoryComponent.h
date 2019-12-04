// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterWeapon.h"
#include "InventoryComponent.generated.h"


class AWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREAL_ARAGON_RPG_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();
	UInventoryComponent(TArray<AWeapon*> Weapons);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	AWeapon* GetWeapon(int index);

	int32 GetNumberOfWeapons() const;

	void AddWeapon(AWeapon* WeaponToAdd);

	void SetInventoryOwner(ACombatCharacter* Owner);

	ACombatCharacter* GetInventoryOwner() const;
private:
	UPROPERTY(EditAnywhere)
	TArray<AWeapon*> Weapons;

	ACombatCharacter* Owner;
};
