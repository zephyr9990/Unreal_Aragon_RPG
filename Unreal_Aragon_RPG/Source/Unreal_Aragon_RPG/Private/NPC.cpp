// Fill out your copyright notice in the Description page of Project Settings.

#include "NPC.h"

#include "Components/SphereComponent.h"
#include "Avatar.h"
#include "MyHUD.h"
#include "GameFramework/PlayerController.h"

// Sets default values
ANPC::ANPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProxSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Proximity Sphere"));
	ProxSphere->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ProxSphere->SetSphereRadius(ProxSphereRadius);

	// Code to make ANPC::Prox() run when this proximity sphere
	// overlaps another actor
	ProxSphere->OnComponentBeginOverlap.AddDynamic(this, &ANPC::Prox);
	NpcMessage = NpcMessage; // default message, can be edited in blueprints.
}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// ANPC::Prox() is ANPC::Prox_Implementation here.
void ANPC::Prox_Implementation(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{

	// if the overlapped actor is not th eplayer
	// you should just simply return from the function
	AAvatar* Player = Cast<AAvatar>(OtherActor);
	if (Player == nullptr)
	{
		return;
	}
	
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	if (PController)
	{
		FString FullNPCMessage = Name + FString(": ") + NpcMessage;
		UE_LOG(LogTemp, Warning, TEXT("Prox fired. Full message is: %s"), *FullNPCMessage);

		AMyHUD* HUD = Cast<AMyHUD>(PController->GetHUD());
		HUD->AddMessage(Message(Face, FullNPCMessage, 5.0f, FColor::White));
	}
}