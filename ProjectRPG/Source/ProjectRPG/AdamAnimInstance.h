// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Animation/AnimInstance.h"
#include "AdamAnimInstance.generated.h"

// 여러개의 함수가 등록되도록 멀티캐스트로 선언
DECLARE_MULTICAST_DELEGATE(FOnNextAttackCheckDelegate);
DECLARE_MULTICAST_DELEGATE(FOnAttackHitCheckDelegate);

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
	void PlayAttackMontage(); // 무기에 따라 다르게 할 예정
	void JumpToAttackMontageSection(int32 NewSection); // 칼 콤보공격
public:
	// 칼 콤보공격 변수들
	FOnNextAttackCheckDelegate OnNextAttackCheck;
	FOnAttackHitCheckDelegate OnAttackHitCheck;
private:
	// 칼 콤보공격 체크 애님 노티파이
	UFUNCTION()
	void AnimNotify_AttackHitCheck(); 

	UFUNCTION()
	void AnimNotify_NextAttackCheck(); 

	FName GetAttackMontageSectionName(int32 Section);
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta=(AllowPrivateAccess=true))
	float CurrentPawnSpeed;
	/*UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float CurrentPawnDir;*/ // 캐릭터 진행 방향

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool bIsFalling;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true)) // DefaultsOnly : 블루프린트 편집 화면에서만 보여짐
	UAnimMontage* AttackMontage;

};
