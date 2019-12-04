// Fill out your copyright notice in the Description page of Project Settings.


#include "EncounterEnemy.h"

#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "BattleManager.h"
#include "Engine/TargetPoint.h"
#include "InventoryComponent.h"
#include "Avatar.h"

AEncounterEnemy::AEncounterEnemy()
{
	ProxSphere = CreateDefaultSubobject<USphereComponent>(FName("ProxSphere"));
	ProxSphere->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ProxSphere->SetSphereRadius(150.0f);

	ProxSphere->OnComponentBeginOverlap.AddDynamic(this, &AEncounterEnemy::Prox);
}

void AEncounterEnemy::Prox_Implementation(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{

	// if the overlapped actor is not the player
	// you should just simply return from the function
	if (Cast<AAvatar>(OtherActor) == nullptr)
	{
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Prox fired."));

	if (Cast<AAvatar>(OtherActor)->GetInventory()->GetNumberOfWeapons() < 2)
	{
		UE_LOG(LogTemp, Warning, TEXT("You need two weapons to enter battle!"));
		return;
	}

	// Add player and monsters to a single array to easily access them
	TArray<ACombatCharacter*> CombatCharacters;
	CombatCharacters.Add(Cast<ACombatCharacter>(OtherActor));
	for (AEnemy* Enemy : Monsters)
	{
		CombatCharacters.Add(Enemy);
	}
	ABattleManager::SetCombatants(CombatCharacters);
	
	FLatentActionInfo LatentInfo;

	UGameplayStatics::LoadStreamLevel(this, FName("BattleMap"), true, true, LatentInfo);
	UE_LOG(LogTemp, Warning, TEXT("Battle map loaded."));
}