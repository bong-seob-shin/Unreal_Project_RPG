// Fill out your copyright notice in the Description page of Project Settings.


#include "KallariAnimInstance.h"
#include "Kallari.h"
#include "GameFramework/PawnMovementComponent.h"



UKallariAnimInstance::UKallariAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> sAtackMontage(TEXT("AnimMontage'/Game/PolarWorld/ParagonKallari/Characters/Heroes/Kallari/AnimationsMontage/BaseAttackMontage.BaseAttackMontage'"));
	if (sAtackMontage.Succeeded())
	{
		AttackMontage = sAtackMontage.Object;
	}

}

void UKallariAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();

	if (IsValid(Pawn))
	{
		fCurrentSpeed = Pawn->GetVelocity().Size();

		auto Character = Cast<AKallari>(Pawn);

		if (Character != nullptr)
		{
			bIsFalling = Character->GetMovementComponent()->IsFalling();
		}
	}
}

void UKallariAnimInstance::PlayAttackMontage()
{
	
	Montage_Play(AttackMontage, 1.0f);
	
}

void UKallariAnimInstance::JumpToAttackMontageSection(int32 index)
{
	Montage_JumpToSection(GetAttackMontageSection(index),AttackMontage);
}

void UKallariAnimInstance::AnimNotify_AttackHit()
{
	OnAttackHitCheck.Broadcast();
}

void UKallariAnimInstance::AnimNotify_NextAttackCheck()
{
	OnNextAttackCheck.Broadcast();
}

void UKallariAnimInstance::AnimNotify_EvadeEnd()
{
	bIsEvading = false;
}

FName UKallariAnimInstance::GetAttackMontageSection(int32 index)
{
	return FName(*FString::Printf(TEXT("Attack%d"),index));
}

void UKallariAnimInstance::SetIsEvading(bool IsEvading)
{
	bIsEvading = IsEvading;
}

