// Fill out your copyright notice in the Description page of Project Settings.


#include "AuroraAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UAuroraAnimInstance::UAuroraAnimInstance()
{
	IsJumping = false;
	IsDead = false;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> AttackMelee_Montage(TEXT("AnimMontage'/Game/IceLandWorld/AM_AttackMelee.AM_AttackMelee'"));
	if (AttackMelee_Montage.Succeeded())
	{
		AttackMeleeMontage = AttackMelee_Montage.Object;
	}
}

void UAuroraAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if (IsValid(Pawn))
	{
		MoveSpeed = Pawn->GetVelocity().Size();

		auto Character = Cast<ACharacter>(Pawn);
		if(Character)
		{
			//Direction = CalculateDirection(Character->GetVelocity(), Character->GetActorRotation());
			IsJumping = Character->GetCharacterMovement()->IsFalling();
			if (!IsJumping)
			{
				Direction = CalculateDirection(Character->GetVelocity(), Character->GetActorRotation());
			}
		}
	}
}

void UAuroraAnimInstance::PlayAttackMeleeMontage()
{
	if (!Montage_IsPlaying(AttackMeleeMontage))
	{
		Montage_Play(AttackMeleeMontage, 1.0f);
	}
}

void UAuroraAnimInstance::JumpToAttackMeleeMontageSection(int32 SectionIndex)
{
	Montage_JumpToSection(GetAttackMeleeMontageSectionName(SectionIndex), AttackMeleeMontage);
}

void UAuroraAnimInstance::AnimNotify_AttackMeleeHitCheck()
{
	OnAttackMeleeHitCheck.Broadcast();
}

void UAuroraAnimInstance::AnimNotify_NextAttackMeleeCheck()
{
	OnNextAttackMeleeCheck.Broadcast();
}

FName UAuroraAnimInstance::GetAttackMeleeMontageSectionName(int32 SectionIndex)
{
	return FName(*FString::Printf(TEXT("Attack%d"), SectionIndex));
}
