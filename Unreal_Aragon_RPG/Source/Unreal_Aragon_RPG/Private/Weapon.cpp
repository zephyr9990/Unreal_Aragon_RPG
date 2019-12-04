// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon.h"

#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Avatar.h"
#include "InventoryComponent.h"
#include "Components/SphereComponent.h"

AWeapon::AWeapon()
{
	ProxSphere = CreateDefaultSubobject<USphereComponent>(FName("Proximity Sphere"));
	ProxSphere->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ProxSphere->SetSphereRadius(150.0f); // TODO make class variable

	ProxSphere->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::Prox);
}

FString AWeapon::GetWeaponName()
{
	return Name;
}

int32 AWeapon::GetAttackValue()
{
	return AttackValue;
}

USkeletalMesh* AWeapon::GetWeaponMesh()
{
	return WeaponMesh;
}

void AWeapon::Prox_Implementation(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	// if the overlapped actor is not the player
	// you should just simply return from the function
	if (Cast<AAvatar>(OtherActor) == nullptr)
	{
		return;
	}
	
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	if (PController)
	{
		Cast<AAvatar>(OtherActor)->GetInventory()->AddWeapon(this);

		int32 WeaponInventorySize = Cast<AAvatar>(OtherActor)->GetInventory()->GetNumberOfWeapons();
		UE_LOG(LogTemp, Warning, TEXT("Weapon added. Inventory size: %i"), WeaponInventorySize);
	}
}