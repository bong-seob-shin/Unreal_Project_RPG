
// Fill out your copyright notice in the Description page of Project Settings.


#include "GruxAnimInstance.h"
#include "Grux.h"

UGruxAnimInstance::UGruxAnimInstance()
{
	bIsAttacking = false;
	bIsDead = false;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> HIT_MONTAGE(TEXT("AnimMontage'/Game/PolarWorld/ParagonGrux/Anims/Grux_Hit_Montage.Grux_Hit_Montage'"));
	if (HIT_MONTAGE.Succeeded())
	{
		HitMontage = HIT_MONTAGE.Object;
	}
}

void UGruxAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();

	if (!IsValid(Pawn)) return;

	fCurrentSpeed = Pawn->GetVelocity().Size();
}

void UGruxAnimInstance::PlayAttackAnim()
{
	bIsAttacking = true;
}

void UGruxAnimInstance::SetIsDead(bool IsDead)
{
	bIsDead = IsDead;
}

void UGruxAnimInstance::PlayHitMontage()
{
	if (!bIsAttacking)
	{
		int rand = FMath::RandRange(1, 3);
		FName HitMontageSection = FName(*FString::Printf(TEXT("Hit%d"),rand));
		Montage_Play(HitMontage, 1.0f);
		Montage_JumpToSection(HitMontageSection, HitMontage);
	}
}

void UGruxAnimInstance::AnimNotify_AttackEnd()
{
	bIsAttacking = false;
	auto Pawn = TryGetPawnOwner();

	if (!IsValid(Pawn)) return;

	auto Grux = Cast<AGrux>(Pawn);
	if(Grux != nullptr)
		Grux->OnAttackEnd.Broadcast();
}
