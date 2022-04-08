// Fill out your copyright notice in the Description page of Project Settings.


#include "AdamAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"


UAdamAnimInstance::UAdamAnimInstance()
{
	CurrentPawnSpeed = 0.0f;
	bIsFalling = false;
	bIsSprinting = false;
	bIsDead = false;
	bUsingShield = false;
	bAimingArrow = false;
	bIsChangingWeapon = false;
	// ���� ���� �ִϸ��̼� �ε��� ����
	RandDeathAnimIdx = FMath::RandRange(0, 1);
	static ConstructorHelpers::FObjectFinder<UAnimMontage> SWORDATTACK_MTG(TEXT("/Game/PalaceWorld/Blueprints/Animations/AdamSwordComboMTG.AdamSwordComboMTG"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> BOWATTACK_MTG(TEXT("/Game/PalaceWorld/Blueprints/Animations/AdamBowBasicAttackMTG.AdamBowBasicAttackMTG"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> CHANGETO_SWORD_MTG(TEXT("/Game/PalaceWorld/Blueprints/Animations/SS_WeaponOutMTG.SS_WeaponOutMTG"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> CHANGETO_BOW_MTG(TEXT("/Game/PalaceWorld/Blueprints/Animations/B_WeaponOutMTG.B_WeaponOutMTG"));


	if (SWORDATTACK_MTG.Succeeded())
	{
		AttackMontage = SWORDATTACK_MTG.Object;
	}
	if (BOWATTACK_MTG.Succeeded())
	{
		BowAttackMontage = BOWATTACK_MTG.Object;
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
		//CurrentPawnDir = CalculateDirection(Pawn->GetVelocity(), FRotator(0.0f, Pawn->GetControlRotation().Yaw, 0.0f)); // pawn�� ������� ���ϴ� �ڵ�
		auto Character = Cast<ACharacter>(Pawn);
		if (Character)
		{
			bIsFalling = Character->GetMovementComponent()->IsFalling(); // ĳ���� ������Ʈ������ ��� ����
		}
	}

}

void UAdamAnimInstance::PlayAttackMontage(EWeaponType curWeapon)
{
	if (bIsDead)
		return;
	if (curWeapon == EWeaponType::E_SWORDSHIELD)
	{
		Montage_Play(AttackMontage, 1.0f);
	}
	else if (curWeapon == EWeaponType::E_BOW)
	{
		Montage_Play(BowAttackMontage, 1.0f);
	}
	
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
		if (Montage_IsPlaying(AttackMontage)) // Į �޺� ���� ��Ÿ�ְ� ������̶��
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

void UAdamAnimInstance::AnimNotify_PickArrow()
{
	OnBowPickArrowCheck.Broadcast();
}

void UAdamAnimInstance::AnimNotify_ShootArrow()
{
	OnBowShootArrowCheck.Broadcast();
}

void UAdamAnimInstance::AnimNotify_AttackHitCheck()
{
	OnAttackHitCheck.Broadcast(); // ��Ƽĳ��Ʈ ��������Ʈ�� ��ϵ� ��� �Լ��� ȣ���ϴ� ���
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
