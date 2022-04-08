// Fill out your copyright notice in the Description page of Project Settings.


#include "RampageAnimInstance.h"

URampageAnimInstance::URampageAnimInstance()
{
	bIsDead = false;
	CurrentPawnSpeed = 0.0f;
	CurrentPawnDir = 0.0f;
	RandAtkAnimIdx = FMath::RandRange(0, 2);
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MTG_1(TEXT("/Game/PalaceWorld/Blueprints/Animations/AdamSwordComboMTG.AdamSwordComboMTG"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MTG_2(TEXT("/Game/PalaceWorld/Blueprints/Animations/AdamSwordComboMTG.AdamSwordComboMTG"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MTG_3(TEXT("/Game/PalaceWorld/Blueprints/Animations/AdamSwordComboMTG.AdamSwordComboMTG"));

}


void URampageAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	auto Pawn = TryGetPawnOwner();
	if (!::IsValid(Pawn))
		return;

	if (!bIsDead)
	{
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
		CurrentPawnDir = CalculateDirection(Pawn->GetVelocity(), FRotator(0.0f, Pawn->GetControlRotation().Yaw, 0.0f)); // pawn의 진행방향 구하는 코드
	}
}

void URampageAnimInstance::PlayRandAttackMontage()
{
	switch (RandAtkAnimIdx)
	{
	case 0:
		Montage_Play(AttackMontage_1, 1.0f);
		break;
	case 1:
		Montage_Play(AttackMontage_2, 1.0f);
		break;
	case 2:
		Montage_Play(AttackMontage_3, 1.0f);
		break;
	default:
		break;
	}
}
