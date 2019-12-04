// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGGameMode.h"

UBehaviorTree* ARPGGameMode::GetEnemyBehaviorTree()
{
	return EnemyBehaviorTree;
}

UBlackboardData* ARPGGameMode::GetEnemyBlackboard()
{
	return EnemyBlackboard;
}
