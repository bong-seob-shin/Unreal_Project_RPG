// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "AuroraPlayerCameraManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTRPG_API AAuroraPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()
	
public:
	AAuroraPlayerCameraManager();

private:
	UPROPERTY(VisibleAnywhere)
	float PitchMax = 10.0f;

	UPROPERTY(VisibleAnywhere)
	float PitchMin = -50.0f;
};
