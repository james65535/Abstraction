// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveWorldSubsystem.h"
#include "Kismet/GameplayStatics.h"

void UObjectiveWorldSubsystem::CreateObjectiveWidget(TSubclassOf<UUserWidget> ObjectiveWidgetClass)
{
	if (ObjectiveWidget == nullptr)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		ObjectiveWidget = CreateWidget<UUserWidget>(PlayerController, ObjectiveWidgetClass);
	}
}

void UObjectiveWorldSubsystem::DisplayObjectiveWidget()
{
	ensureAlwaysMsgf(ObjectiveWidget, TEXT("UObjectiveWorldSubsystem::DisplayObjectiveWidget ObjectiveWidget is nullptr")); // ensureAlways is basically an assert, used here instead of if statement
	ObjectiveWidget->AddToViewport();
}

void UObjectiveWorldSubsystem::OnObjectiveCompleted()
{
	DisplayObjectiveWidget();
}
