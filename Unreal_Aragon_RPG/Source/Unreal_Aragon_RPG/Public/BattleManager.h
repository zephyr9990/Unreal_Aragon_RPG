// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BattleManager.generated.h"

///Forward Declaration
class AEnemy;

UCLASS()
class UNREAL_ARAGON_RPG_API ABattleManager : public AActor
{
	GENERATED_UCLASS_BODY()

public:	
	ABattleManager();

	virtual void Tick(float DeltaTime) override;

	static void SetCombatants(TArray<ACombatCharacter*> CombatCharacters);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	static TArray<ACombatCharacter*> GetCombatants();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	static void StartTurnBasedBattle();

	static ACombatCharacter* GetNextCombatant(int32 Index);

	static void SetToAttack(ACombatCharacter* Attacker);

	UFUNCTION(BlueprintCallable, Category = "Battle")
	static void FinishTurn();

	static TArray<int32> TurnNumbers;
private:
	static TArray<ACombatCharacter*> Combatants;
	static ACombatCharacter* ActiveCombatant;
	static int32 CurrentIndex;
	static int32 ActiveCombatantIndex;
	static bool Battling;
	static bool HasFinishedTurn;
};
