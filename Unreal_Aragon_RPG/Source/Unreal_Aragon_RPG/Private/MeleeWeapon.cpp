// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeWeapon.h"
#include "Monster.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AMeleeWeapon::AMeleeWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	AttackDamage = 1.0f;
	Swinging = false;
	WeaponHolder = nullptr;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));
	RootComponent = Mesh;

	ProxBox = CreateDefaultSubobject<UBoxComponent>(FName("ProxBox"));
	ProxBox->OnComponentBeginOverlap.AddDynamic(this, &AMeleeWeapon::Prox);
	ProxBox->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AMeleeWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMeleeWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMeleeWeapon::Prox_Implementation(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Don't hit non root components
	if (OtherComp != OtherActor->GetRootComponent())
	{
		return;
	}

	// avoid hitting things while sword isn't swinging
	// avoid hitting yourself, and
	// avoid hitting the same OtherActor twice
	if (Swinging && OtherActor != WeaponHolder &&
		!ThingsHit.Contains(OtherActor))
	{
		OtherActor->TakeDamage(AttackDamage + WeaponHolder->BaseAttackDamage,
			FDamageEvent(), nullptr, this);
		ThingsHit.Add(OtherActor);
	}
}

void AMeleeWeapon::Swing()
{
	ThingsHit.Empty(); // empty the list
	Swinging = true;
}

void AMeleeWeapon::Rest()
{
	ThingsHit.Empty();
	Swinging = false;
}