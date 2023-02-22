// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ABSTRACTION_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	float TakeDamage(float Damage) { return CurrentHealth -= Damage;}
	bool IsDead() { return CurrentHealth <= FLT_EPSILON; }
	const float GetCurrentHealth() const { return CurrentHealth; }
	void SetCurrentHealth(float Health) { CurrentHealth = Health;}

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	float MaxHealth = 100.0f;

	UPROPERTY(VisibleAnywhere)
	float CurrentHealth = 0.0f;
		
};
