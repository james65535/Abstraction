// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorInteractionComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/TriggerBox.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UDoorInteractionComponent::UDoorInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	StartRotation = GetOwner()->GetActorRotation();
	FinalRotation = GetOwner()->GetActorRotation() = DesiredRotation;
	CurrentRotationTime = 0.0f;

	// First Rotation Attempt
	// DesiredRotation = FRotator(0.0f,90.0f,0.0f);
	// DeltaRotation = DesiredRotation - GetOwner()->GetActorRotation();
	// FinalRotation = GetOwner()->GetActorRotation() + DesiredRotation;
	
	// GetOwner()->SetActorRotation(DesiredRotation);

	// ...
	
}


// Called every frame
void UDoorInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(CurrentRotationTime < TimeToRotate)
	{
		if (TriggerBox && GetWorld() && GetWorld()->GetFirstPlayerController()) // QUESTION Why first GetWorld? Wouldn't second GetWorld return false if unassigned? Is this a resource optimisation pattern?
		{
			APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
			if (PlayerPawn && TriggerBox->IsOverlappingActor(PlayerPawn))  // QUESTION Why first check on PlayerPawn?  Wouldn't IsOverlapping return false anyways if PlayerPawn was unassigned anyways? Is this a resource optimisation pattern?
			{
				CurrentRotationTime += DeltaTime;
				const float TimeRatio = FMath::Clamp(CurrentRotationTime / TimeToRotate,0.0f,1.0f);
				const float RotationAlpha = OpenCurve.GetRichCurve()->Eval(TimeRatio);
				const FRotator CurrentRotation = FMath::Lerp(StartRotation,FinalRotation,RotationAlpha);
				GetOwner()->SetActorRotation(CurrentRotation);
				
				// Pre trigger curve
				// CurrentRotationTime += DeltaTime;
				// const float RotationAlpha = FMath::Clamp(CurrentRotationTime / TimeToRotate,0.0f,1.0f);
				// const FRotator CurrentRotation = FMath::Lerp(StartRotation,FinalRotation,RotationAlpha);
				// GetOwner()->SetActorRotation(CurrentRotation);
			}
		}
	}

	
	// First Rotation Attempt
	// FRotator CurrentRotation = GetOwner()->GetActorRotation();
	// if(!CurrentRotation.Equals(FinalRotation,5.0f))
	// {
	// 	CurrentRotation += DeltaRotation * DeltaTime;
	// 	GetOwner()->SetActorRotation(CurrentRotation);
	// }

	// ...
}

