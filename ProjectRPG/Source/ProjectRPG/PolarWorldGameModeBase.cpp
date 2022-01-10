// Fill out your copyright notice in the Description page of Project Settings.


#include "PolarWorldGameModeBase.h"
#include "Kallari.h"
#include "KallariController.h"
APolarWorldGameModeBase::APolarWorldGameModeBase()
{
	DefaultPawnClass = AKallari::StaticClass();
	PlayerControllerClass = AKallariController::StaticClass();
	

}