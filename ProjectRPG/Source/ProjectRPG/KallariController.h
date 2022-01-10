// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "KallariController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTRPG_API AKallariController : public APlayerController
{
	GENERATED_BODY()

	AKallariController();

private:

	// Called to bind functionality to input
	virtual void SetupInputComponent() override;

	UFUNCTION()
	void Updown(float Value);

	UFUNCTION()
	void LeftRight(float Value);

	UFUNCTION()
	void Horizontal(float Value);

	UFUNCTION()
	void Vertical(float Value);

	UFUNCTION()
	void Jump();
};
