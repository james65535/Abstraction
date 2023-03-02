// Copyright Epic Games, Inc. All Rights Reserved.

#include "AbstractionGameMode.h"
#include "AbstractionCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAbstractionGameMode::AAbstractionGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
