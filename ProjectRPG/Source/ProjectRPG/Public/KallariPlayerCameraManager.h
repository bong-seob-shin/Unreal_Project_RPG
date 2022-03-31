// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "KallariPlayerCameraManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTRPG_API AKallariPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

	AKallariPlayerCameraManager();

public:

	UPROPERTY(VisibleAnywhere)
	float MaxPitchLimit = 15.0f;
	
	UPROPERTY(VisibleAnywhere)
	float MinPitchLimit = -60.0f;
};
