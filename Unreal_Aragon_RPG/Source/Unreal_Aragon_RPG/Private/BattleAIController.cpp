// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleAIController.h"

#include "CombatCharacter.h"
#include "Enemy.h"
#include "InventoryComponent.h"
#include "Weapon.h"
#include "RPGGameMode.h"

ABattleAIController::ABattleAIController()
{
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(FName("EnemyBlackboard"));

	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(FName("EnemyBehaviorTree"));
}

void ABattleAIController::BeginPlay()
{
	Super::BeginPlay();


	auto ControlledCharacter = GetControlledCombatCharacter();
	if (!ControlledCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("No controlled combat character on %s"), *GetName());
		return;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controller possessing %s"), *GetControlledCombatCharacter()->GetName());
	}

	UBlackboardData* EnemyBlackBoard = Cast<ARPGGameMode>(GetWorld()->GetAuthGameMode())->GetEnemyBlackboard();
	BlackboardComp->InitializeBlackboard(*EnemyBlackBoard);

	UBehaviorTree* EnemyBehaviorTree = Cast<ARPGGameMode>(GetWorld()->GetAuthGameMode())->GetEnemyBehaviorTree();
	BehaviorTreeComp->StartTree(*EnemyBehaviorTree);
}



ACombatCharacter* ABattleAIController::GetControlledCombatCharacter()
{
	return Cast<ACombatCharacter>(GetPawn());
}

void ABattleAIController::StartBattle()
{
	bIsStartingBattle = true;
	BlackboardComp->SetValueAsBool(FName("IsStartingBattle"), bIsStartingBattle);
}

void ABattleAIController::SetTarget(ACombatCharacter* TargetToAttack)
{
 	this->Target = TargetToAttack;
	UE_LOG(LogTemp, Warning, TEXT("Broadcasted event"));
}

ACombatCharacter* ABattleAIController::GetTarget() const
{
	return Target;
}

void ABattleAIController::StartAIControl()
{
	UBlackboardData* EnemyBlackBoard = Cast<ARPGGameMode>(GetWorld()->GetAuthGameMode())->GetEnemyBlackboard();
	BlackboardComp->InitializeBlackboard(*EnemyBlackBoard);

	UBehaviorTree* EnemyBehaviorTree = Cast<ARPGGameMode>(GetWorld()->GetAuthGameMode())->GetEnemyBehaviorTree();
	BehaviorTreeComp->StartTree(*EnemyBehaviorTree);
}

void ABattleAIController::SetToReactToDamage()
{
	 BlackboardComp->SetValueAsBool(FName("IsTakingDamage"), true);
}
