// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupItem.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Avatar.h"
#include "MyHUD.h"

// Sets default values
APickupItem::APickupItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Name = "UNKOWN ITEM";
	Quantity = 0;

	// Initialize the unreal objects
	ProxSphere = CreateDefaultSubobject<USphereComponent>(FName("ProxSphere"));
	ProxSphere->SetSphereRadius(ProxSphereRadius);
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));
	Icon = nullptr;


	// Make the root object the Mesh
	RootComponent = Mesh;
	Mesh->SetSimulatePhysics(true);

	/* Code to make APickupItem::Prox() run when this
		object's proximity sphere overlaps another actor. */
	ProxSphere->OnComponentBeginOverlap.AddDynamic(this, &APickupItem::Prox);
	ProxSphere->AttachToComponent(Mesh, FAttachmentTransformRules::KeepRelativeTransform); // very important
}



// Called when the game starts or when spawned
void APickupItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickupItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickupItem::Prox_Implementation(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// if the overlapped actor is NOT the player, you simply should return.
	if (Cast<AAvatar>(OtherActor) == nullptr)
	{
		return;
	}

	// Get a reference to the player avatar, to give him the item.
	AAvatar* Avatar = Cast<AAvatar>(OtherActor);

	// Let the player pickup this item
	Avatar->Pickup(this);

	// Get a reference to the controller
	APlayerController* PController = GetWorld()->GetFirstPlayerController();

	// Get a reference to the HUD from the controller
	AMyHUD* HUD = Cast<AMyHUD>(PController->GetHUD());
	HUD->AddMessage(Message(
		Icon,
		FString("Picked up ") + FString::FromInt(Quantity) + FString(" ") + Name,
		5.f,
		FColor::White)
	);

	UE_LOG(LogTemp, Warning, TEXT("Picked up %i %s"), Quantity, *Name);

	Destroy();
}
