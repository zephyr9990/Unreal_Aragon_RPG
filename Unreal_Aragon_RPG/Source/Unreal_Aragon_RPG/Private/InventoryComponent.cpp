// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "Weapon.h"
#include "CombatCharacter.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

UInventoryComponent::UInventoryComponent(TArray<AWeapon*> Weapons)
{
	PrimaryComponentTick.bCanEverTick = false;
	this->Weapons = Weapons;
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

AWeapon* UInventoryComponent::GetWeapon(int index)
{
	return Weapons[index];
}

int32 UInventoryComponent::GetNumberOfWeapons() const
{
	return Weapons.Num();
}

void UInventoryComponent::AddWeapon(AWeapon* WeaponToAdd)
{
	Weapons.Add(WeaponToAdd);
// TODO Delete	UE_LOG(LogTemp, Warning, TEXT("%s added. Size of Weapons: %i"), *WeaponToAdd->GetName(), Weapons.Num()); 

	if (Weapons.Num() == 1)
	{
		Owner->EquipWeapon(WeaponToAdd);
	}
}

void UInventoryComponent::SetInventoryOwner(ACombatCharacter* OwnerOfInventory)
{
	Owner = OwnerOfInventory;
}

ACombatCharacter* UInventoryComponent::GetInventoryOwner() const
{
	return Owner;
}
