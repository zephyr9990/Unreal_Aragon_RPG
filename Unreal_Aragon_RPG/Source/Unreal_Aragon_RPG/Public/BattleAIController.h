// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BattleAIController.generated.h"

//Forward Declaration
class ACombatCharacter;

UCLASS()
class UNREAL_ARAGON_RPG_API ABattleAIController : public AAIController
{
	GENERATED_BODY()

public:

	ABattleAIController();

	virtual void BeginPlay() override;

	ACombatCharacter* GetControlledCombatCharacter();

	UFUNCTION(BlueprintCallable, Category = "Battle")
	void StartBattle();

	UPROPERTY(BlueprintReadOnly, Category = "Battle")
	bool bIsStartingBattle;

	UFUNCTION(BlueprintCallable, Category = "Battle")
	void SetTarget(ACombatCharacter* TargetToAttack);

	UFUNCTION(BlueprintCallable, Category = "Battle")
	ACombatCharacter* GetTarget() const;

	UFUNCTION(BlueprintCallable, Category = "Battle")
	void StartAIControl();
	
    void SetToReactToDamage();
private:
	ACombatCharacter* Target = nullptr;
	//UBlackboardData* Blackboard;
	UBlackboardComponent* BlackboardComp = nullptr;
	//UBehaviorTree* BehaviorTree;
	UBehaviorTreeComponent* BehaviorTreeComp = nullptr;
};
