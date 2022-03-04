
// Fill out your copyright notice in the Description page of Project Settings.


#include "GruxAnimInstance.h"
#include "Grux.h"

UGruxAnimInstance::UGruxAnimInstance()
{
	bIsAttacking = false;
	bIsDead = false;
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

void UGruxAnimInstance::AnimNotify_AttackEnd()
{
	bIsAttacking = false;
	auto Pawn = TryGetPawnOwner();

	if (!IsValid(Pawn)) return;

	auto Grux = Cast<AGrux>(Pawn);
	if(Grux != nullptr)
		Grux->OnAttackEnd.Broadcast();
}
