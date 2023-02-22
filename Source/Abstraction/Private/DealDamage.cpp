// Fill out your copyright notice in the Description page of Project Settings.


#include "DealDamage.h"
#include "Components/CapsuleComponent.h"
#include "AbstractionPlayerCharacter.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values for this component's properties
UDealDamage::UDealDamage()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	
	TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger Capsule"));
	TriggerCapsule->OnComponentBeginOverlap.AddDynamic(this, &UDealDamage::OnOverlapBegin);
	TriggerCapsule->OnComponentEndOverlap.AddDynamic(this, &UDealDamage::UDealDamage::OnOverlapEnd);
}

// Called when the game starts
void UDealDamage::BeginPlay()
{
	Super::BeginPlay();
}

void UDealDamage::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("UDealDamage::OnOverlapBegin"));
	
	if (OtherActor == GetOwner())
	{
		return;
	}

	if (!IsDamageActive())
	{
		return;
	}

	AAbstractionPlayerCharacter* PlayerCharacter = Cast<AAbstractionPlayerCharacter>(OtherActor);
	if (PlayerCharacter)
	{
		PlayerCharacter->SetOnFire(BaseDamage, DamageTotalTime, TakeDamageInterval);
	}
}

void UDealDamage::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("UDealDamage::OnOverlapEnd"));
}



