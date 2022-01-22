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

public:
	virtual void PostInitializeComponents() override;

private:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);

	void Jump();
	void BeginRun();
	void EndRun();
	void BeginShield();
	void EndShield();

	void AttackMelee();
	void FirstAbility();
	void SecondAbility();
	void ThirdAbility();

private:
	UPROPERTY()
	class UAuroraAnimInstance* AuroraAnimInstance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Ability, Meta = (AllowPrivateAccess = true))
	bool IsAbility;
};
