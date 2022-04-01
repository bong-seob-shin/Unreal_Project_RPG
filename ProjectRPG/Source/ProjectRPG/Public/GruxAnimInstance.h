// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GruxAnimInstance.generated.h"


UENUM(BlueprintType)
enum class GruxHitMontageType : uint8
{
    Hit_1 = 0,
    Hit_2 = 1,
    Hit_3 = 2
};

/**
 * 
 */
UCLASS()
class PROJECTRPG_API UGruxAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
    UGruxAnimInstance();
    virtual void NativeUpdateAnimation(float DeltaSeconds) override;

    void PlayAttackAnim();

    void SetIsDead(bool IsDead);

    void PlayHitMontage();

private:
    UFUNCTION()
    void AnimNotify_AttackEnd();

private:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Grux, Meta = (AllowPrivateAccess = true))
    float fCurrentSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Grux, Meta = (AllowPrivateAccess = true))
    bool bIsAttacking;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Grux, Meta = (AllowPrivateAccess = true))
    bool bIsDead;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Hit, Meta = (AllowPrivateAccess = true))
    UAnimMontage* HitMontage;

   
};


