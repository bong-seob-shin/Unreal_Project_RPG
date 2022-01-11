// Fill out your copyright notice in the Description page of Project Settings.


#include "IceLandGameModeBase.h"
#include "AuroraCharacter.h"
#include "AuroraPlayerController.h"

AIceLandGameModeBase::AIceLandGameModeBase()
{
	DefaultPawnClass = AAuroraCharacter::StaticClass();
	PlayerControllerClass = AAuroraPlayerController::StaticClass();
}