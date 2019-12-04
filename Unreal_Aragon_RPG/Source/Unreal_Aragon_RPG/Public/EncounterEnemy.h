// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.h"
#include "EncounterEnemy.generated.h"


class USphereComponent;
class ATargetPoint;

/**
 * 
 */
UCLASS()
class UNREAL_ARAGON_RPG_API AEncounterEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	AEncounterEnemy();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	USphereComponent* ProxSphere;

	UFUNCTION(BlueprintNativeEvent, Category = "Collision")
	void Prox(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY(EditAnywhere, Category = "Encounter")
	TArray<AEnemy*> Monsters;
};
