// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GruxAnimInstance.generated.h"

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


private:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Grux, Meta = (AllowPrivateAccess = true))
    float fCurrentSpeed;
};
