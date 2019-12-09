// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "Avatar.h"
#include "MeleeWeapon.h"
#include "Bullet.h"
#include "Engine/Engine.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMonster::AMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Speed = 20.0f;
	HitPoints = 20.0f;
	ExperiencePoints = 0;
	BPLoot = nullptr;
	BaseAttackDamage = 1.0f;
	AttackTimeout = 2.0f;
	TimeSinceLastStrike = 0.0f;

	SightSphere = CreateDefaultSubobject<USphereComponent>(FName("SightSphere"));
	SightSphere->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	SightSphere->SetSphereRadius(3000.0f);

	AttackRangeSphere = CreateDefaultSubobject<USphereComponent>(FName("AttackRangeSphere"));
	AttackRangeSphere->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	AttackRangeSphere->SetSphereRadius(150.0f);
}

void AMonster::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (MeleeWeapon_BP)
	{
		MeleeWeapon = GetWorld()->SpawnActor<AMeleeWeapon>(MeleeWeapon_BP, FVector(), FRotator());
		Cast<AMeleeWeapon>(MeleeWeapon)->WeaponHolder = this; // Tell the weapon who the owner is
		if (MeleeWeapon)
		{
			const USkeletalMeshSocket* Socket = GetMesh()->GetSocketByName("RightWeaponSocket");
			Socket->AttachActor(MeleeWeapon, GetMesh());
		}
	}
}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// move the monster towards the player
	AAvatar* Player = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (!Player)
	{
		return; // If there's no first player, stop executing
	}

	FVector ToPlayer = Player->GetActorLocation() - GetActorLocation();
	float DistanceToPlayer = ToPlayer.Size();
	if (!IsInSightRange(DistanceToPlayer))
	{
		return; // If player is out of sight range, don't chase
	}

	ToPlayer /= DistanceToPlayer; // Normalizes the vector.

	// Gets you the rotator to turn monster to look in the 'ToPlayer' direction
	FRotator ToPlayerRotation = ToPlayer.Rotation();
	ToPlayerRotation.Pitch = 0; // 0 off the pitch (the up down direction)
	RootComponent->SetWorldRotation(ToPlayerRotation);

	if (IsInAttackRange(DistanceToPlayer))
	{
		// Stop moving and attack player
		if (!TimeSinceLastStrike)
		{
			CanAttack = true;
		}

		TimeSinceLastStrike += DeltaTime;
		if (TimeSinceLastStrike > AttackTimeout)
		{
			TimeSinceLastStrike = 0;
			CanAttack = true;
		}

		return; // nothing else to do	
	}
	else
	{
		// not in attack range, so walk towards player
		AddMovementInput(ToPlayer, Speed * DeltaTime);
	}
}

bool AMonster::IsInSightRange(float DistanceToPlayer)
{
	return DistanceToPlayer < SightSphere->GetScaledSphereRadius();
}

inline bool AMonster::IsInAttackRange(float DistanceToPlayer)
{
	return DistanceToPlayer < AttackRangeSphere->GetScaledSphereRadius();
}

bool AMonster::IsInAttackRangeOfPlayer()
{
	AAvatar* Player = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (!Player)
	{
		return false;
	}

	FVector ToPlayer = Player->GetActorLocation() - GetActorLocation();
	float DistanceToPlayer = ToPlayer.Size();

	return IsInAttackRange(DistanceToPlayer);
}

// Called to bind functionality to input
void AMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMonster::SwordSwung()
{
	if (MeleeWeapon)
	{
		Cast<AMeleeWeapon>(MeleeWeapon)->Swing();
	}
}

void AMonster::Attack(AActor* Target)
{
	if (MeleeWeapon)
	{
		// code for the melee weapon swing, if a melee weapon is used.
		Cast<AMeleeWeapon>(MeleeWeapon)->Swing();
	}
	else if (Bullet_BP)
	{
		// If a blueprint for a bullet to use was assigned, use that.
		// Bullet firing code not executed if melee weapon is equipped.
		FVector Forward = GetActorForwardVector();
		FVector Nozzle = GetMesh()->GetBoneLocation("RightHand");

		// move it forward of the monster so it doesn't collide with monster model
		Nozzle += Forward * 155; 

		FVector toOpponent = Target->GetActorLocation() - Nozzle;
		toOpponent.Normalize();

		ABullet* Bullet = GetWorld()->SpawnActor<ABullet>(Bullet_BP, Nozzle, toOpponent.Rotation());
		if (Bullet)
		{
			Bullet->Firer = this;
			Bullet->ProxSphere->AddImpulse(toOpponent * BulletLaunchImpulse, FName(), true);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(
				0,
				5.f,
				FColor::Yellow,
				"Monster: No bullet actor could be spawned. is the bullet overlapping something?"
			);
		}
	}
}