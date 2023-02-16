// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageHandlerComponent.h"
#include "AbstractionPlayerCharacter.h"
#include "GameFramework/DamageType.h"
#include "Particles/ParticleSystemComponent.h"
#include "Misc/ScopeLock.h"


// Sets default values for this component's properties
//UDamageHandlerComponent::UDamageHandlerComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
UDamageHandlerComponent::UDamageHandlerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDamageHandlerComponent::BeginPlay()
{
	Super::BeginPlay();

	//PlayerCharacter = Cast<AAbstractionPlayerCharacter>(GetOwner());
	
}


// Called every frame
void UDamageHandlerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// if (PlayerCharacter)
	// {
	// 	FScopeLock Lock(&CriticalSection);
	// 	if (ActiveDamageInfo.IsSet())
	// 	{
	// 		if (ActiveDamageInfo.GetValue().AccumulatedTime > ActiveDamageInfo.GetValue().LifeTime)
	// 		{
	// 			if (PlayerCharacter->ParticleSystemComponent)
	// 			{
	// 				PlayerCharacter->ParticleSystemComponent->Deactivated();
	// 				PlayerCharacter->ParticleSystemComponent->SetTemplate(nullptr);
	// 			}
	// 			ActiveDamageInfo.Reset();
	// 		}
	// 	}
	// }
}

