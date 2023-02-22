// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryComponent.h"
#include "Weapon.h"
#include "Engine/EngineTypes.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

bool UInventoryComponent::AddWeapon(AWeapon* InWeapon)
{
	// Picking up a weapon
	// The Incoming Weapon needs to be attached to this actor(player)
	InWeapon->AttachToActor(GetOwner(), FAttachmentTransformRules::KeepRelativeTransform);
	Weapons.Add(InWeapon);

	return true;
}
