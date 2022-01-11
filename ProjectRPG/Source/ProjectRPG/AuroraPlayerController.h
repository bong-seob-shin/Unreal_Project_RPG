// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuroraPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTRPG_API AAuroraPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AAuroraPlayerController();

private:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);

	void Jump();
	void StopJumping();
	void BeginRun();
	void EndRun();
};
