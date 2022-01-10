// Fill out your copyright notice in the Description page of Project Settings.


#include "PalaceGameMode.h"
#include "AdamCharacter.h"
#include "AdamPlayerController.h"

APalaceGameMode::APalaceGameMode() 
{
	DefaultPawnClass = AAdamCharacter::StaticClass();
	PlayerControllerClass = AAdamPlayerController::StaticClass();
}
