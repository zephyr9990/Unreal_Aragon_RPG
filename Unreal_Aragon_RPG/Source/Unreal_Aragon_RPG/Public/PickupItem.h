// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupItem.generated.h"

// Forward Declaration
class USphereComponent;

UCLASS()
class UNREAL_ARAGON_RPG_API APickupItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// When something comes inside ProxSphere, this function runs
	UFUNCTION(BlueprintNativeEvent, Category = "Collision")
	void Prox(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Name of the pickup item
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FString Name;

	// Quanity of item to be picked up
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 Quantity;

	// The sphere you collide with to pick item up
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Item")
	USphereComponent* ProxSphere;

	// The mesh of the item
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Item")
	UStaticMeshComponent* Mesh;

	// The icon that represents the object in the UI/canvas
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	UTexture2D* Icon;

private:
	float ProxSphereRadius = 150.f;
};
