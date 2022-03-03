// Fill out your copyright notice in the Description page of Project Settings.


#include "AdamAnimInstance.h"



UAdamAnimInstance::UAdamAnimInstance()
{
	CurrentPawnSpeed = 0.0f;
	bIsFalling = false;
	bIsSprinting = false;
	bIsDead = false;
	bUsingShield = false;
	bAimingArrow = false;
	// 랜덤 죽음 애니메이션 인덱스 세팅
	RandDeathAnimIdx = FMath::RandRange(0, 1);
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MTG(TEXT("/Game/PalaceWorld/Blueprints/Animations/AdamSwordComboMTG.AdamSwordComboMTG"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> CHANGETO_SWORD_MTG(TEXT("/Game/PalaceWorld/Blueprints/Animations/SS_WeaponOutMTG.SS_WeaponOutMTG"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> CHANGETO_BOW_MTG(TEXT("/Game/PalaceWorld/Blueprints/Animations/B_WeaponOutMTG.B_WeaponOutMTG"));


	if (ATTACK_MTG.Succeeded())
	{
		AttackMontage = ATTACK_MTG.Object;
	}
	if (CHANGETO_SWORD_MTG.Succeeded())
	{
		ChangeToSwordMontage = CHANGETO_SWORD_MTG.Object;
	}
	if (CHANGETO_BOW_MTG.Succeeded())
	{
		ChangeToBowMontage = CHANGETO_BOW_MTG.Object;
	}
	
}


void UAdamAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if (!::IsValid(Pawn))
		return;

	if (!bIsDead)
	{
		CurrentPawnSpeed = Pawn->GetVelocity().Size();
		//CurrentPawnDir = CalculateDirection(Pawn->GetVelocity(), FRotator(0.0f, Pawn->GetControlRotation().Yaw, 0.0f)); // pawn의 진행방향 구하는 코드
		auto Character = Cast<ACharacter>(Pawn);
		if (Character)
		{
			bIsFalling = Character->GetMovementComponent()->IsFalling(); // 캐릭터 컴포넌트에서만 사용 가능
		}
	}

}

void UAdamAnimInstance::PlayAttackMontage()
{
	if(!bIsDead)
		Montage_Play(AttackMontage, 1.0f);
}

void UAdamAnimInstance::PlayChangeWeaponMontage(EWeaponType nextWeapon)
{
	if (nextWeapon == EWeaponType::E_SWORDSHIELD)
	{
		Montage_Play(ChangeToSwordMontage, 1.0f);
	}
	else if (nextWeapon == EWeaponType::E_BOW)
	{
		Montage_Play(ChangeToBowMontage, 1.0f);
	}
}

void UAdamAnimInstance::JumpToAttackMontageSection(int32 NewSection)
{
	if (!bIsDead)
	{
		if (Montage_IsPlaying(AttackMontage)) // 칼 콤보 공격 몽타주가 재생중이라면
		{
			Montage_JumpToSection(GetAttackMontageSectionName(NewSection), AttackMontage);
		}
	}
}

void UAdamAnimInstance::AnimNotify_TookOutSword()
{
	OnSwordTookOutCheck.Broadcast();
}

void UAdamAnimInstance::AnimNotify_TookOutBow()
{
	OnBowTookOutCheck.Broadcast();
}

void UAdamAnimInstance::AnimNotify_AttackHitCheck()
{
	OnAttackHitCheck.Broadcast(); // 멀티캐스트 델리게이트에 등록된 모든 함수를 호출하는 명령
}

void UAdamAnimInstance::AnimNotify_NextAttackCheck()
{
	OnNextAttackCheck.Broadcast();
}

FName UAdamAnimInstance::GetAttackMontageSectionName(int32 Section)
{
	if (FMath::IsWithinInclusive<int32>(Section, 1, 5))
		return FName(*FString::Printf(TEXT("Attack%d"), Section));
	else
		return NAME_None;
	
}
