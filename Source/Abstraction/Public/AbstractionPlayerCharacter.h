// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbstractionPlayerCharacter.generated.h"

class UHealthComponent;

UCLASS()
class ABSTRACTION_API AAbstractionPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAbstractionPlayerCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void FellOutOfWorld(const UDamageType& dmgType) override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
	UFUNCTION(BlueprintCallable)
	const bool IsAlive() const;

	UFUNCTION(BlueprintCallable)
	const float GetCurrentHealth() const;

	UFUNCTION(BlueprintCallable, Category = "Abstraction")
	void SetOnFire(float BaseDamage, float DamageTotalTime, float TakeDamageInterval);
	

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	
	void OnDeath(bool IsFellOut);

	UPROPERTY(EditAnywhere)
	UHealthComponent* HealthComponent;


};