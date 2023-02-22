// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FireDamageActor.generated.h"

class UDealDamage;
class UParticleSystemComponent;

UCLASS()
class ABSTRACTION_API AFireDamageActor : public AActor
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	AFireDamageActor();

//	virtual void PostActorCreated() override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UDealDamage* DealDamageComponent;

	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* ParticleSystemComponent;

	UPROPERTY(EditAnywhere)
	float ToggleTime = 5.0f;

	float CurrentTimer = 0.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
