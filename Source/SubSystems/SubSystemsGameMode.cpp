// Copyright Epic Games, Inc. All Rights Reserved.

#include "SubSystemsGameMode.h"
#include "SubSystemsCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASubSystemsGameMode::ASubSystemsGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
