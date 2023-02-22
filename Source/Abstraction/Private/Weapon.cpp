// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "InteractionComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AWeapon::AWeapon() : Super()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>("InteractionComponent");
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	RootComponent = StaticMeshComponent;

	if (InteractionComponent->GetTriggerCapsule())
	{
		InteractionComponent->GetTriggerCapsule()->SetupAttachment(RootComponent);
	}
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
}

