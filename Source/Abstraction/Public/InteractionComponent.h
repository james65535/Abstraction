// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"

class AActor;
class UCapsuleComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractionSuccess);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ABSTRACTION_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractionComponent();

	// Broadcasted from children, they know when an interaction has successfull finished
	UPROPERTY(BlueprintAssignable, Category = "Door")
	FOnInteractionSuccess InteractionSuccess;

	UFUNCTION()
	virtual void OnOverLapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnOverLapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UCapsuleComponent* GetTriggerCapsule() const { return TriggerCapsule; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	virtual void InteractionStart();

	UPROPERTY(EditAnywhere)
	FText InteractionPrompt;

	UPROPERTY(EditAnywhere, NoClear)
	UCapsuleComponent* TriggerCapsule = nullptr;

	AActor* InteractingActor = nullptr;
		
};
