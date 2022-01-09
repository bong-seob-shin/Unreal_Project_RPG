// Copyright Epic Games, Inc. All Rights Reserved.


#include "ProjectRPGGameModeBase.h"
#include "AuroraCharacter.h"

AProjectRPGGameModeBase::AProjectRPGGameModeBase()
{
	DefaultPawnClass = AAuroraCharacter::StaticClass();
}