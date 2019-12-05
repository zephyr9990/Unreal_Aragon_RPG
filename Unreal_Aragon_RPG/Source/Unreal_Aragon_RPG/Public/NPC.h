// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NPC.generated.h"

// Forward Declaration
class USphereComponent;
class APickupItem;

UCLASS()
class UNREAL_ARAGON_RPG_API ANPC : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision)
	//USphereComponent* ProxSphere;
	USphereComponent* ProxSphere;
	UFUNCTION(BlueprintNativeEvent, Category = "Collision")
	void Prox(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPCMessage")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPCMessage")
	FString NpcMessage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPCMessage")
	UTexture2D* Face;

private:
	float ProxSphereRadius = 150.f;
};
