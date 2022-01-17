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

	UFUNCTION()
	void OnAttackMeleeMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	void AttackMeleeStartComboState();
	void AttackMeleeEndComboState();

private:
	UPROPERTY(VisibleAnywhere, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool IsAttackingMelee;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool canNextCombo;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool IsComboInputOn;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	int32 CurrentCombo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	int32 MaxCombo;

	UPROPERTY()
	class UAuroraAnimInstance* AuroraAnimInstance;
};
