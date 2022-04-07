// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PalaceWorld.h"
#include "Animation/AnimInstance.h"
#include "RampageAnimInstance.generated.h"

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

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float CurrentPawnSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float CurrentPawnDir;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool bIsDead;  // 죽는 애니메이션 재생 위한 변수
};
