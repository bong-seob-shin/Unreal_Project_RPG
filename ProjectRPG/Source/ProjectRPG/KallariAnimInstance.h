// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "KallariAnimInstance.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnNextAttackCheck);
DECLARE_MULTICAST_DELEGATE(FOnAttackHitCheck);
/**
 * 
 */
UCLASS()
class PROJECTRPG_API UKallariAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UKallariAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
	void SetIsEvading(bool IsEvading);

	void PlayAttackMontage();
	void JumpToAttackMontageSection(int32 index);
private:
	UFUNCTION()
	void AnimNotify_AttackHit();

	UFUNCTION()
	void AnimNotify_NextAttackCheck();

	UFUNCTION()
	void AnimNotify_EvadeEnd();

	FName GetAttackMontageSection(int32 index);


public:
	FOnNextAttackCheck OnNextAttackCheck;
	FOnAttackHitCheck OnAttackHitCheck;

	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Kallari, Meta = (AllowPrivateAccess = true))
	float fCurrentSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Kallari, Meta = (AllowPrivateAccess = true))
	bool bIsFalling;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Kallari, Meta = (AllowPrivateAccess = true))
	bool bIsEvading;
	

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	UAnimMontage* AttackMontage;

};
