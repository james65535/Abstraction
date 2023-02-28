// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Curves/CurveFloat.h"
#include "InteractionComponent.h"
#include "DoorInteractionComponent.generated.h"

class IConsoleVariable;
class UTextRenderComponent;

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
class ABSTRACTION_API UDoorInteractionComponent : public UInteractionComponent
{
	GENERATED_BODY()
public:	
	// Sets default values for this component's properties
	UDoorInteractionComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	// Debug and console toggle
	static void OnDebugToggled(IConsoleVariable* Var);

	// Request to open the door
	UFUNCTION(BlueprintCallable)
	void OpenDoor();
	
	virtual void OnOverLapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void OnOverLapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	UPROPERTY()
	UTextRenderComponent* TextRenderComponent;

	UPROPERTY()
	UAudioComponent* AudioComponent;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// TODO added virtual when this was not in the source code
	// Bound to interaction input from player
	virtual void InteractionRequested() override;

	// Called internally when door has finished opening
	void OnDoorOpen();

	UFUNCTION(BlueprintCallable)
	bool IsOpen() { return DoorState == EDoorState::DS_OPEN; }

	void DebugDraw();

	UPROPERTY(EditAnywhere)
	FRotator DesiredRotation = FRotator(0.0f, 90.0f, 0.0f);

	FRotator StartRotation = FRotator::ZeroRotator;
	FRotator FinalRotation = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere)
	float TimeToRotate = 1.0f;

	float CurrentRotationTime = 0.0f;

	UPROPERTY(EditAnywhere)
	FRuntimeFloatCurve OpenCurve;
	
	UPROPERTY(BlueprintReadOnly)
	EDoorState DoorState = EDoorState::DS_CLOSED;

};
