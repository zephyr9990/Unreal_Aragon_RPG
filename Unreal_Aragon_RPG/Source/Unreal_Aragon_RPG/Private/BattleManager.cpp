// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleManager.h"
#include "CombatCharacter.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Math/UnrealMathUtility.h"

TArray<ACombatCharacter*> ABattleManager::Combatants;
TArray<int32> ABattleManager::TurnNumbers;
ACombatCharacter* ABattleManager::ActiveCombatant = nullptr;
int32 ABattleManager::CurrentIndex = 0; // TODO change to 0 so player can start turn
bool ABattleManager::Battling = false;
bool ABattleManager::HasFinishedTurn = false;
int32 ABattleManager::ActiveCombatantIndex = 0;

ABattleManager::ABattleManager()
{
}

ABattleManager::ABattleManager(const FObjectInitializer &ObjectInitializer) 
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

}

void ABattleManager::Tick(float DeltaTime)
{
	if (!ActiveCombatant && Battling)
	{
		if (!(CurrentIndex >= Combatants.Num() - 1))
		{
			ActiveCombatant = GetNextCombatant(CurrentIndex);
			SetToAttack(ActiveCombatant);
		}
		else
		{
			CurrentIndex = 0;
		}
	}

	if (HasFinishedTurn && Battling)
	{
		if (CurrentIndex < Combatants.Num())
		{
			UE_LOG(LogTemp, Warning, TEXT("Finished Turn"));
			ActiveCombatant = GetNextCombatant(CurrentIndex);
			SetToAttack(ActiveCombatant);
		}
		else
		{
			CurrentIndex = 0;
			ActiveCombatant = nullptr;
		}
	}
}

void ABattleManager::SetCombatants(TArray<ACombatCharacter*> CombatCharacters)
{
	Combatants = CombatCharacters;
	UE_LOG(LogTemp, Warning, TEXT("Number of Combatants: %i"), Combatants.Num())
}

TArray<ACombatCharacter*> ABattleManager::GetCombatants()
{
	UE_LOG(LogTemp, Warning, TEXT("Number of Combatants: %i"), Combatants.Num())
	return Combatants;
}

void ABattleManager::StartTurnBasedBattle()
{
	TurnNumbers.Init(0, Combatants.Num());
	CurrentIndex = 0;
	ActiveCombatantIndex = CurrentIndex;
	UE_LOG(LogTemp, Warning, TEXT("Starting battle"));
	Battling = true;
	ActiveCombatant = nullptr;
}

ACombatCharacter* ABattleManager::GetNextCombatant(int32 Index)
{
	UE_LOG(LogTemp, Warning, TEXT("Getting Combatant"));
	HasFinishedTurn = false;
	ActiveCombatantIndex = Index;
	CurrentIndex += 1;
	return Combatants[Index];
}

void ABattleManager::SetToAttack(ACombatCharacter* Attacker)
{
	TArray<ACombatCharacter*> Targets;

	TurnNumbers[ActiveCombatantIndex] += 1;
	UE_LOG(LogTemp, Warning, TEXT("Current turn: %i"), TurnNumbers[ActiveCombatantIndex]);
	if (Attacker->IfTimeToSwap(TurnNumbers[ActiveCombatantIndex], ActiveCombatantIndex))
	{
		UE_LOG(LogTemp, Warning, TEXT("Player turn skipped"));
		FinishTurn();
		return;
	}
	
	if (Attacker->IsDead())
	{
		FinishTurn();
		return;
	}

	for (ACombatCharacter* Combatant : Combatants)
	{
		if (Combatant != Attacker && !Combatant->IsDead())
		{
			Targets.Add(Combatant);
		}
	}

	int32 TargetIndex = FMath::RandRange(0, Targets.Num() - 1);
	UE_LOG(LogTemp, Warning, TEXT("Set to attack index: %i"), TargetIndex);

	if (Targets.Num() == 0)
	{
		// End battle
		Battling = false;
	}
	else
	{
		Attacker->SetTargetToAttack(Targets[TargetIndex]);
	}
}

void ABattleManager::FinishTurn()
{
	HasFinishedTurn = true;
}
