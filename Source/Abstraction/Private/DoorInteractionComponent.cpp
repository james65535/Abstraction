// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorInteractionComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/TriggerBox.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "ObjectiveWorldSubsystem.h"

// Float for setting relative position for door debug text
constexpr float FLT_METERS(float meters){ return meters * 100.0f;}

static TAutoConsoleVariable<bool> CVarToggleDebugDoor(
	TEXT("Abstraction.DoorInteractionComponent.Debug"),
	false,
	TEXT("Toffle DoorInteractionComponent debug display."),
	ECVF_Default);

// Sets default values for this component's properties
UDoorInteractionComponent::UDoorInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	DoorState = EDoorState::DS_CLOSED; 

	// Setup console callback for debug toggle
	CVarToggleDebugDoor.AsVariable()->SetOnChangedCallback(FConsoleVariableDelegate::CreateStatic((&UDoorInteractionComponent::OnDebugToggled)));
}

void UDoorInteractionComponent::OnDebugToggled(IConsoleVariable* Var)  // Question: is this variable here just to satisfy the interface fingerprint?
{
	UE_LOG(LogTemp, Warning, TEXT("OnDebugToggled"));
}

void UDoorInteractionComponent::DebugDraw()
{
	if (CVarToggleDebugDoor->GetBool())
	{
		FVector Offset(FLT_METERS(-0.75f), 0.0f, FLT_METERS(2.5f));
		FVector StartLocation = GetOwner()->GetActorLocation() + Offset;
		FString EnumAsString = TEXT("Door State: ") + UEnum::GetDisplayValueAsText(DoorState).ToString();
		DrawDebugString(GetWorld(), Offset, EnumAsString, GetOwner(), FColor::Blue, 0.0f);
	}
}

// Called when the game starts
void UDoorInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	StartRotation = GetOwner()->GetActorRotation();
	FinalRotation = GetOwner()->GetActorRotation() + DesiredRotation;
	CurrentRotationTime = 0.0f;

	OnDoorOpenedEvent.AddDynamic(this, &ThisClass::OnDoorOpen);

	// First Rotation Attempt
	// DesiredRotation = FRotator(0.0f,90.0f,0.0f);
	// DeltaRotation = DesiredRotation - GetOwner()->GetActorRotation();
	// FinalRotation = GetOwner()->GetActorRotation() + DesiredRotation;
	
	// GetOwner()->SetActorRotation(DesiredRotation);

	/*
	 *Removed mod4-6
	UObjectiveWorldSubsystem* ObjectiveWorldSubsystem = GetWorld()->GetSubsystem<UObjectiveWorldSubsystem>();
	if (ObjectiveWorldSubsystem)
	{
		OpenedEvent.AddUObject(ObjectiveWorldSubsystem, &UObjectiveWorldSubsystem::OnObjectiveCompleted);
	}
	*/
}

// Called every frame
void UDoorInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (DoorState == EDoorState::DS_CLOSED)
	{
		if (TriggerBox && GetWorld() && GetWorld()->GetFirstPlayerController()) 
		{
			APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
			if (PlayerPawn && TriggerBox->IsOverlappingActor(PlayerPawn))  
			{
				DoorState = EDoorState::DS_OPENING;
				CurrentRotationTime = 0.0f;
			}
		}
	}
	else if (DoorState == EDoorState::DS_OPENING)
	{
		CurrentRotationTime += DeltaTime;
		const float TimeRatio = FMath::Clamp(CurrentRotationTime / TimeToRotate,0.0f,1.0f);
		const float RotationAlpha = OpenCurve.GetRichCurve()->Eval(TimeRatio);
		const FRotator CurrentRotation = FMath::Lerp(StartRotation,FinalRotation,RotationAlpha);
		GetOwner()->SetActorRotation(CurrentRotation);
		if (TimeRatio >= 1.0f)
		{
			OnDoorOpenedEvent.Broadcast();
			/*
			 *Removed mod4-6
			DoorState = EDoorState::DS_OPEN;
			GEngine->AddOnScreenDebugMessage(-1, 3.0f,FColor::Yellow, TEXT("DoorOpened"));
			OpenedEvent.Broadcast();
			*/
		}	
		// Pre - setting up trigger curve in module 2
		// CurrentRotationTime += DeltaTime;
		// const float RotationAlpha = FMath::Clamp(CurrentRotationTime / TimeToRotate,0.0f,1.0f);
		// const FRotator CurrentRotation = FMath::Lerp(StartRotation,FinalRotation,RotationAlpha);
		// GetOwner()->SetActorRotation(CurrentRotation);

		// First Rotation Lesson in Module 2
		// FRotator CurrentRotation = GetOwner()->GetActorRotation();
		// if(!CurrentRotation.Equals(FinalRotation,5.0f))
		// {
		// 	CurrentRotation += DeltaRotation * DeltaTime;
		// 	GetOwner()->SetActorRotation(CurrentRotation);
		// }
	}
	DebugDraw();
}

void UDoorInteractionComponent:: OnDoorOpen()
{
	DoorState = EDoorState::DS_OPEN;
	UObjectiveComponent* ObjectiveComponent = GetOwner()->FindComponentByClass<UObjectiveComponent>();
	if (ObjectiveComponent)
	{
		ObjectiveComponent->SetState(EObjectiveState::OS_Completed);
	}
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, TEXT("DoorOpened"));
}

