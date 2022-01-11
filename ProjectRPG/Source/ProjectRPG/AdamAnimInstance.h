// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Animation/AnimInstance.h"
#include "AdamAnimInstance.generated.h"

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
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta=(AllowPrivateAccess=true))
	float CurrentPawnSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float CurrentPawnDir;
};
