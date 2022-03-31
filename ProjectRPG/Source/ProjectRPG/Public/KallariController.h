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
public:

	AKallariController();

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool blnterrupted);

	// Called to bind functionality to input
	virtual void SetupInputComponent() override;


	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

private:


	void Updown(float Value);
	void LeftRight(float Value);
	void Horizontal(float Value);
	void Vertical(float Value);

	void DashStart();
	void DashEnd();
	void Jump();
	void Attack();
	void Evade();
	void OnSkill1();



private:

	UPROPERTY(VisibleInstanceOnly,BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess=true))
	bool bIsAttacking = false;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool bIsUsingSkill = false;

	UPROPERTY()
	class AKallari* MyCharacter;

	UPROPERTY()
	float Skill1_CoolDown_Calc_Sec;
	UPROPERTY()
	float Skill1_CoolDown_Time;

	UPROPERTY()
	float Evade_CoolDown_Calc_Sec;
	UPROPERTY()
	float Evade_CoolDown_Time;
};
