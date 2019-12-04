// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RPGGameMode.generated.h"

class UBehaviorTree;
class UBlackboardData;
/**
 * 
 */
UCLASS()
class UNREAL_ARAGON_RPG_API ARPGGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UBehaviorTree* GetEnemyBehaviorTree();

	UBlackboardData* GetEnemyBlackboard();

private:

	UPROPERTY(EditAnywhere)
	UBehaviorTree* EnemyBehaviorTree;

	UPROPERTY(EditAnywhere)
	UBlackboardData* EnemyBlackboard;
};
