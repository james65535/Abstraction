// Fill out your copyright notice in the Description page of Project Settings.


#include "AbstractionWorldSubsystem.h"
#include "Kismet/GameplayStatics.h"

void UAbstractionWorldSubsystem::CreateObjectiveWidget(TSubclassOf<UUserWidget> ObjectiveWidgetClass)
{
	if (ObjectiveWidget == nullptr)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		ObjectiveWidget = CreateWidget<UUserWidget>(PlayerController, ObjectiveWidgetClass);
	}
}

void UAbstractionWorldSubsystem::DisplayObjectiveWidget()
{
	ensureAlwaysMsgf(ObjectiveWidget, TEXT("UAbstractionWorldSubsystem::DisplayObjectiveWidget ObjectiveWidget is nullptr"));
}

