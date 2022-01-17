// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AuroraAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnNextAttackMeleeCheckDelegate);
DECLARE_MULTICAST_DELEGATE(FOnAttackMeleeHitCheckDelegate);
DECLARE_MULTICAST_DELEGATE(FOnFirstAbilityEndDelegate);

/**
 * 
 */
UCLASS()
class PROJECTRPG_API UAuroraAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UAuroraAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void PlayAttackMeleeMontage();
	void JumpToAttackMeleeMontageSection(int32 SectionIndex);

public:
	FOnNextAttackMeleeCheckDelegate OnNextAttackMeleeCheck;
	FOnAttackMeleeHitCheckDelegate OnAttackMeleeHitCheck;
	FOnFirstAbilityEndDelegate OnFirstAbilityEnd;

	void SetHitAnimation() { IsHit  = true; }
	void SetDeadAnimation() { IsDead = true; }
	void SetBeginShieldAnimation() { IsShield = true; }
	void SetEndShieldAnimation() { IsShield = false; }

private:
	UFUNCTION()
	void AnimNotify_AttackMeleeHitCheck();

	UFUNCTION()
	void AnimNotify_NextAttackMeleeCheck();

	FName GetAttackMeleeMontageSectionName(int32 SectionIndex);

	UFUNCTION()
	void AnimNotify_FirstAbilityEnd();

	UFUNCTION()
	void AnimNotify_SecondAbilityEnd();

	UFUNCTION()
	void AnimNotify_ThirdAbilityEnd();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float Direction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsJumping;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsShield;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsHit;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsDead;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	UAnimMontage* AttackMeleeMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ability, Meta = (AllowPrivateAccess = true))
	bool IsFirstAbility;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ability, Meta = (AllowPrivateAccess = true))
	bool IsSecondAbility;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ability, Meta = (AllowPrivateAccess = true))
	bool IsThirdAbility;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	UAnimNotify* Attacsk;
};
