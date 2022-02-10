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

	bIsFalling = false;
	bIsDead = false;

}

void UKallariAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();

	if (!IsValid(Pawn)) return;

	if (!bIsDead)
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

bool UKallariAnimInstance::GetIsEvading()
{
	return bIsEvading;
}

void UKallariAnimInstance::SetIsSkill_1_Playing(bool IsSkillPlaying)
{
	bIsSkill_1_Playing = IsSkillPlaying;
}

bool UKallariAnimInstance::GetIsSkill_1_Playing()
{
	return bIsSkill_1_Playing;
}

void UKallariAnimInstance::SetIsDead(bool bInIsDead)
{
	bIsDead = bInIsDead;
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

void UKallariAnimInstance::AnimNotify_Skill1()
{
	OnSkill1.Broadcast();
}

FName UKallariAnimInstance::GetAttackMontageSection(int32 index)
{
	return FName(*FString::Printf(TEXT("Attack%d"),index));
}

void UKallariAnimInstance::SetIsEvading(bool IsEvading)
{
	bIsEvading = IsEvading;
}

