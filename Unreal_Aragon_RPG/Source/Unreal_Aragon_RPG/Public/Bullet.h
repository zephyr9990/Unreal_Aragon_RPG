// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

class USphereComponent;
class AMonster;

UCLASS()
class UNREAL_ARAGON_RPG_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// How much damage the bullet does.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	float Damage;

	// The visible Mesh for the component, so we can see the shooting object.
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Collision")
	UStaticMeshComponent* Mesh;

	// The sphere you collide with to do impact damage
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Collision")
	USphereComponent* ProxSphere;

	// The monster that fires the bullet;
	AMonster* Firer;

	UFUNCTION(BlueprintNativeEvent, Category = "Collision")
	void Prox(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
