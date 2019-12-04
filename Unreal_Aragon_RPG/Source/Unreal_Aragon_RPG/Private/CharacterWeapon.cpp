// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterWeapon.h"
#include "CombatCharacter.h"
#include "Weapon.h"

UCharacterWeapon::UCharacterWeapon()
{
	Name = "";
	AttackValue = 0;
	WeaponMesh = nullptr;
}

void UCharacterWeapon::SetWeapon(AWeapon* Weapon)
{
	Name = Weapon->GetWeaponName();
	AttackValue = Weapon->GetAttackValue();
	WeaponMesh = Weapon->GetWeaponMesh();

	SetSkeletalMesh(WeaponMesh);
	UE_LOG(LogTemp, Warning, TEXT("Set Mesh to Equipped Weapon")); //TODO delete 
}

void UCharacterWeapon::UnsheatheWeapon(ACombatCharacter* OwnerOfWeapon)
{
	AttachToComponent(OwnerOfWeapon->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("EquippedWeapon"));
}

void UCharacterWeapon::Attack(ACombatCharacter* Target)
{
	Target->ReceiveDamage(AttackValue);
}

FString UCharacterWeapon::GetWeaponName() const
{
	return Name;
}

