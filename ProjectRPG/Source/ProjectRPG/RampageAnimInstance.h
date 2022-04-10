// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PalaceWorld.h"
#include "Animation/AnimInstance.h"
#include "RampageAnimInstance.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnAttackHitCheckDelegate);

/**
 * 
 */
UCLASS()
class PROJECTRPG_API URampageAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	URampageAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override; // tick
public:
	void PlayRandAttackMontage(); // ���� ��Ÿ�� ���
	void SetRandAtkAnimIdx() { RandAtkAnimIdx = FMath::RandRange(0, 2); }
	void SetDeadAnim() { bIsDead = true; }
public:
	FOnAttackHitCheckDelegate OnAttackHitCheck;
	
private:
	UFUNCTION()
	void AnimNotify_AttackHitCheck();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float CurrentPawnSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float CurrentPawnDir;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool bIsDead;  // �״� �ִϸ��̼� ��� ���� ����
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	int32 RandAtkAnimIdx; // ���� ���� �ִϸ��̼� ���� �ε���

	// Montages
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true)) // DefaultsOnly : �������Ʈ ���� ȭ�鿡���� ������
	UAnimMontage* AttackMontage_1;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true)) // DefaultsOnly : �������Ʈ ���� ȭ�鿡���� ������
	UAnimMontage* AttackMontage_2;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true)) // DefaultsOnly : �������Ʈ ���� ȭ�鿡���� ������
	UAnimMontage* AttackMontage_3;
};
