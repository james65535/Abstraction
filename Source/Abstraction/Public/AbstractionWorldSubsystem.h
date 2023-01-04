// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Subsystems/WorldSubsystem.h"
#include "Blueprint/UserWidget.h"
#include "AbstractionWorldSubsystem.generated.h"

/**
 * Created in module 4-5
 */
UCLASS()
class ABSTRACTION_API UAbstractionWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	void CreateObjectiveWidget(TSubclassOf<UUserWidget> ObjectiveWidgetClass);
	void DisplayObjectiveWidget();

private:
	UUserWidget* ObjectiveWidget = nullptr;
};
