// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Curves/CurveFloat.h"
#include "DoorInteractionComponent.generated.h"

class ATriggerBox;  // QUESTION: Does the UE4 build process link the library TriggerBox.H? Seems this is a build time optimisation technique

UDELEGATE(Category = "Door")
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDoorOpened);

UENUM()
enum class EDoorState
{
	DS_CLOSED = 0 UMETA(DisplayName = "Closed"),
	DS_OPENING = 1 UMETA(DisplayName = "Opening"),
	DS_OPEN = 2 UMETA(DisplayName = "Open"),
	DS_LOCKED = 3 UMETA(DisplayName = "Locked"),
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ABSTRACTION_API UDoorInteractionComponent : public UActorComponent
{
	GENERATED_BODY()
public:	
	// Sets default values for this component's properties
	UDoorInteractionComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Event for door being opened
	// UE Macro for callbacks - Delegates
	//DECLARE_EVENT(UDoorInteractionComponent, FOpened) // Question does this macro create the FOpened type? How?

	UPROPERTY(BlueprintAssignable, EditAnywhere, Category="Door")
	FOnDoorOpened OnDoorOpenedEvent;
	
	//FOpened& OnOpened_Implementation() { return OpenedEvent;}

	//UFUNCTION()
	//FOnDoorOpened OpenedEvent;  // Question This probably has to come last due to order forced by macro

	UFUNCTION()
	void OnDoorOpen();

	//void OnDoorOpen_Implementation();// { return OnDoorOpenedEvent;}
	
	// Debug and console toggle
	static void OnDebugToggled(IConsoleVariable* Var);
	void DebugDraw();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintReadOnly)
	EDoorState DoorState = EDoorState::DS_CLOSED;

	// Property Definitions for Door Opening
	UPROPERTY(EditAnywhere)
	ATriggerBox* TriggerBox;
	
	UPROPERTY(EditAnywhere)
	FRotator DesiredRotation = FRotator(0.0f, 90.0f, 0.0f);

	FRotator StartRotation = FRotator::ZeroRotator;
	FRotator FinalRotation = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere)
	float TimeToRotate = 1.0f;

	float CurrentRotationTime = 0.0f;
	
	//  First Rotation Lesson in Mod2
	//FRotator DesiredRotation;
	//FRotator DeltaRotation;
	//FRotator FinalRotation;

	UPROPERTY(EditAnywhere)
	FRuntimeFloatCurve OpenCurve;
};
