// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PalaceWorld.h"
#include "Animation/AnimInstance.h"
#include "AdamAnimInstance.generated.h"

// �������� �Լ��� ��ϵǵ��� ��Ƽĳ��Ʈ�� ����
DECLARE_MULTICAST_DELEGATE(FOnNextAttackCheckDelegate);
DECLARE_MULTICAST_DELEGATE(FOnAttackHitCheckDelegate);
DECLARE_MULTICAST_DELEGATE(FOnSwordTookOutDelegate);
DECLARE_MULTICAST_DELEGATE(FOnBowTookOutDelegate);
DECLARE_MULTICAST_DELEGATE(FOnBowAttackPickArrowDelegate);
DECLARE_MULTICAST_DELEGATE(FOnBowAttackShootArrowDelegate);




/**
 * 
 */
UCLASS()
class PROJECTRPG_API UAdamAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UAdamAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override; // tick
	void PlayAttackMontage(EWeaponType curWeapon); // ���� ��Ÿ�� ���
	void PlayChangeWeaponMontage(EWeaponType nextWeapon);
	void JumpToAttackMontageSection(int32 NewSection); // Į �޺�����

public:
	FOnNextAttackCheckDelegate OnNextAttackCheck;
	FOnAttackHitCheckDelegate OnAttackHitCheck;
	FOnSwordTookOutDelegate OnSwordTookOutCheck; // Į,���з� ���� ��ü
	FOnBowTookOutDelegate OnBowTookOutCheck; // Ȱ�� ���� ��ü
	FOnBowAttackPickArrowDelegate OnBowPickArrowCheck;
	FOnBowAttackShootArrowDelegate OnBowShootArrowCheck;

	void SetDeadAnim() { bIsDead = true; }
	void SetSprintAnim(bool bPressedShift) { bIsSprinting = bPressedShift; }
	void SetUsingShieldAnim(bool bPressedRightClick) { bUsingShield = bPressedRightClick; }
	void SetAimingArrowAnim(bool bPressedRightClick) { bAimingArrow = bPressedRightClick; }
	void SetChangingWeapon(bool bPressedNumKey) { bIsChangingWeapon = bPressedNumKey; }
	bool GetbUsingShield() { return bUsingShield; }
	bool GetbAimingArrow() { return bAimingArrow; }
	bool GetbIsSprinting() { return bIsSprinting; }
	bool GetbIsChangingWeapon() { return bIsChangingWeapon; }
	

private:
	// Į,���з� ���� ��ü
	UFUNCTION()
	void AnimNotify_TookOutSword();
	// Ȱ�� ���� ��ü
	UFUNCTION()
	void AnimNotify_TookOutBow();
	// Ȱ �⺻���� ��Ƽ����
	UFUNCTION()
	void AnimNotify_PickArrow();
	UFUNCTION()
	void AnimNotify_ShootArrow();
	// Į �޺����� üũ �ִ� ��Ƽ����
	UFUNCTION()
	void AnimNotify_AttackHitCheck(); 

	UFUNCTION()
	void AnimNotify_NextAttackCheck(); 

	FName GetAttackMontageSectionName(int32 Section);
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta=(AllowPrivateAccess=true))
	float CurrentPawnSpeed;
	/*UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float CurrentPawnDir;*/ // ĳ���� ���� ����

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool bIsDead;  // �״� �ִϸ��̼� ��� ���� ����
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	int32 RandDeathAnimIdx; // ���� ���� �ִϸ��̼� ���� �ε���

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool bIsFalling;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool bIsSprinting; // toggle shift

	// ���� ��ȯ ����
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool bIsChangingWeapon;

	// ���⿡ ���� �ٸ� Ư����� - state machine���� ó��
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool bUsingShield; // right click
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool bAimingArrow; // right click

	

	// ��Ÿ�ֵ�
	// SwordAndShield
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true)) // DefaultsOnly : �������Ʈ ���� ȭ�鿡���� ������
	UAnimMontage* AttackMontage; // ��Ŭ�� �⺻����

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = WeaponChange, Meta = (AllowPrivateAccess = true)) // DefaultsOnly : �������Ʈ ���� ȭ�鿡���� ������
	UAnimMontage* ChangeToSwordMontage;

	// Bow
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = WeaponChange, Meta = (AllowPrivateAccess = true)) // DefaultsOnly : �������Ʈ ���� ȭ�鿡���� ������
	UAnimMontage* ChangeToBowMontage;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = WeaponChange, Meta = (AllowPrivateAccess = true)) // DefaultsOnly : �������Ʈ ���� ȭ�鿡���� ������
	UAnimMontage* BowAttackMontage; // ��Ŭ�� �⺻����
};
